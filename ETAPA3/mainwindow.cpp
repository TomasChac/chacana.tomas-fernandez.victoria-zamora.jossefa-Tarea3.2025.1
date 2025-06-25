#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "videopublisher.h"
#include "videofollower.h"
#include "gpscarpublisher.h"
#include "gpscarfollower.h"
#include "broker.h"
#include "gpsdata.h"
#include <QVBoxLayout>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    broker = new Broker();
 

    videoPublisher = new VideoPublisher("VideoPublisher", broker, "video_topic", this);
    videoFollower = new VideoFollower("VideoFollower", "video_topic", this);
    gpsCarPublisher = new GPSCarPublisher("GPSCarPublisher", broker, "gps_topic", this);
    gpsCarFollower = new GPSCarFollower("GPSCarFollower", "gps_topic", this);


    //tabWidget = new QTabWidget(this); // Crear el QTabWidget
    QWidget* central = new QWidget(this); // Crear un widget central para la ventana principal
    QVBoxLayout* layout = new QVBoxLayout(central); // Usar QVBoxLayout para organizar los widgets verticalmente
    layout->addWidget(videoPublisher); // <-- Agrega el publicador de video
    layout->addWidget(videoFollower);   // <-- Agrega el publicador de video
    layout->addWidget(gpsCarPublisher);   // <-- Agrega el publicador de GPS
    layout->addWidget(gpsCarFollower);  // <-- Agrega el seguidor de GPS
    //layout->addWidget(tabWidget);   // <-- Agrega el QTabWidget

    // Conectar la señal 
    connect(videoFollower, &VideoFollower::abrirPestanaVideo, this, [this](const QString& url){
        QWidget* videoWindow = new QWidget();
        videoWindow->setAttribute(Qt::WA_DeleteOnClose);
        videoWindow->setWindowTitle("Reproductor de Video");
        videoWindow->resize(800, 600);

        QVBoxLayout* layout = new QVBoxLayout(videoWindow);
        QVideoWidget* videoWidget = new QVideoWidget(videoWindow);
        QMediaPlayer* player = new QMediaPlayer(videoWindow);
        player->setVideoOutput(videoWidget);
        player->setSource(QUrl::fromUserInput(url));
        player->play();
        layout->addWidget(videoWidget);
        videoWindow->setLayout(layout);

        videoWindow->show();
    });

    connect(gpsCarFollower, &GPSCarFollower::abrirVentanaGPS, this, [this](const QVector<GPSData>& posiciones){
        QWidget* gpsWindow = new QWidget();
        gpsWindow->setAttribute(Qt::WA_DeleteOnClose);
        gpsWindow->setWindowTitle("Recorrido GPS");
        gpsWindow->resize(500, 500);

        QVBoxLayout* layout = new QVBoxLayout(gpsWindow);

        QTextEdit* textEdit = new QTextEdit(gpsWindow);
        textEdit->setReadOnly(true);

        QStringList lines;
        for (const auto& pos : posiciones) {
            lines << QString("%1 %2 %3").arg(pos.tiempo).arg(pos.x).arg(pos.y);
        }
        textEdit->setText(lines.join("\n"));

        layout->addWidget(textEdit);
        gpsWindow->setLayout(layout);
        gpsWindow->show();
});



    central->setLayout(layout);
    setCentralWidget(central);

    connect(videoPublisher, &VideoPublisher::urlPublicada, videoFollower, &VideoFollower::update);
    connect(gpsCarPublisher, &GPSCarPublisher::datoPublicado, gpsCarFollower, &GPSCarFollower::update);
}

MainWindow::~MainWindow()
{
    delete ui;
}
