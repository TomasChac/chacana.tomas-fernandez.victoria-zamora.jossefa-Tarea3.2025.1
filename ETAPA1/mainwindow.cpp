#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "videopublisher.h"
#include "videofollower.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Crear una instancia del Broker
    broker = new Broker();
    // Crear instancias de VideoPublisher y VideoFollower
    videoPublisher = new VideoPublisher("VideoPublisher", broker, "video_topic", this);
    videoFollower = new VideoFollower("VideoFollower", "video_topic", this);

   // Crear un layout vertical
    QVBoxLayout* layout = new QVBoxLayout;

    // Agregar los widgets al layout
    layout->addWidget(videoPublisher);
    layout->addWidget(videoFollower);

    // Crear un widget central y asignarle el layout
    QWidget* central = new QWidget(this);
    central->setLayout(layout);
    setCentralWidget(central);

    // Conectar la señal urlPublicada del VideoPublisher al slot update del VideoFollower
    connect(videoPublisher, &VideoPublisher::urlPublicada, videoFollower, &VideoFollower::update);
}   

MainWindow::~MainWindow()
{
    delete ui;
}
