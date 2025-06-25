#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "videopublisher.h"
#include "videofollower.h"
#include "gpscarpublisher.h"
#include "gpscarfollower.h"
#include "broker.h"
#include <QVBoxLayout>

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


    tabWidget = new QTabWidget(this); // Crear el QTabWidget
    QWidget* central = new QWidget(this); // Crear un widget central para la ventana principal
    QVBoxLayout* layout = new QVBoxLayout(central); // Usar QVBoxLayout para organizar los widgets verticalmente
    layout->addWidget(videoPublisher); // <-- Agrega el publicador de video
    layout->addWidget(videoFollower);   // <-- Agrega el publicador de video
    layout->addWidget(gpsCarPublisher);   // <-- Agrega el publicador de GPS
    layout->addWidget(gpsCarFollower);  // <-- Agrega el seguidor de GPS
    layout->addWidget(tabWidget);   // <-- Agrega el QTabWidget

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

    connect(gpsCarFollower, &GPSCarFollower::abrirVentanaGPS, this, [this](const QVector<QPointF>& posiciones){
    QWidget* gpsWindow = new QWidget();
    gpsWindow->setAttribute(Qt::WA_DeleteOnClose);
    gpsWindow->setWindowTitle("Recorrido GPS");
    gpsWindow->resize(500, 500);

    QVBoxLayout* layout = new QVBoxLayout(gpsWindow);

    QGraphicsScene* scene = new QGraphicsScene(gpsWindow);
    QGraphicsView* view = new QGraphicsView(scene, gpsWindow);

    // Dibuja las posiciones como puntos y líneas
    for (int i = 0; i < posiciones.size(); ++i) {
        scene->addEllipse(posiciones[i].x(), posiciones[i].y(), 4, 4, QPen(Qt::red), QBrush(Qt::red));
        if (i > 0) {
            scene->addLine(posiciones[i-1].x(), posiciones[i-1].y(), posiciones[i].x(), posiciones[i].y(), QPen(Qt::blue));
        }
    }

    layout->addWidget(view);
    gpsWindow->setLayout(layout);
    gpsWindow->show();
});



    central->setLayout(layout);
    setCentralWidget(central);

    connect(videoPublisher, &VideoPublisher::urlPublicada, videoFollower, &VideoFollower::update);
}

MainWindow::~MainWindow()
{
    delete ui;
}
