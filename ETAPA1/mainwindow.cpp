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
    // Crear una instancia del Broker
    broker = new Broker();
    // Crear instancias de VideoPublisher y VideoFollower
    videoPublisher = new VideoPublisher("VideoPublisher", broker, "video_topic", this);
    videoFollower = new VideoFollower("VideoFollower", "video_topic", this);

    QWidget* central = new QWidget(this);

    // Configurar el layout de la ventana principal
    QVBoxLayout* layout = new QVBoxLayout(central);
    layout->addWidget(videoPublisher); // Agregar el VideoPublisher al layout 
    layout->addWidget(videoFollower); // Agregar el VideoFollower al layout
    central->setLayout(layout);
    setCentralWidget(central); // Establecer el widget central de la ventana principal

    // Conectar la señal urlPublicada del VideoPublisher al slot update del VideoFollower
    connect(videoPublisher, &VideoPublisher::urlPublicada, videoFollower, &VideoFollower::update);
}   

MainWindow::~MainWindow()
{
    delete ui;
}
