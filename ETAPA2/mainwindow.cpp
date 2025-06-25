#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "videopublisher.h"
#include "videofollower.h"
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

    tabWidget = new QTabWidget(this); // Crear el QTabWidget
    QWidget* central = new QWidget(this); // Crear un widget central para la ventana principal
    QVBoxLayout* layout = new QVBoxLayout(central); // Usar QVBoxLayout para organizar los widgets verticalmente
    layout->addWidget(videoPublisher);
    layout->addWidget(videoFollower);
    layout->addWidget(tabWidget);

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



    central->setLayout(layout);
    setCentralWidget(central);

    connect(videoPublisher, &VideoPublisher::urlPublicada, videoFollower, &VideoFollower::update);
}

MainWindow::~MainWindow()
{
    delete ui;
}