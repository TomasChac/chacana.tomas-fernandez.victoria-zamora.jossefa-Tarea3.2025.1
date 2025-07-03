#include "mainwindow.h"
#include "broker.h"
#include "videopublisher.h"
#include "videofollower.h"
#include "gpscarpublisher.h"
#include "gpscarfollower.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Simulador Pub/Sub Tarea 3 - Etapa 4");
    resize(800, 400);

    Broker& broker = Broker::getInstance();
    
    // Crear los widgets
    VideoPublisher* videoPub = new VideoPublisher();
    
    // --- CORRECCIÓN AQUÍ: Pasamos el tópico al constructor ---
    VideoFollower* videoSub = new VideoFollower("Video"); 
    
    GPSCarPublisher* gpsPub = new GPSCarPublisher();
    GPSCarFollower* gpsSub = new GPSCarFollower();

    // Conectar todo a través del BROKER
    connect(videoPub, &VideoPublisher::wantsToPublish, &broker, &Broker::publish);
    connect(gpsPub, &GPSCarPublisher::wantsToPublish, &broker, &Broker::publish);
    
    connect(&broker, &Broker::newMessage, videoSub, &VideoFollower::onNewMessage);
    connect(&broker, &Broker::newMessage, gpsSub, &GPSCarFollower::onNewMessage);

    // Organizar la Interfaz
    QWidget *centralWidget = new QWidget;
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    QVBoxLayout *pubLayout = new QVBoxLayout();
    pubLayout->addWidget(videoPub);
    pubLayout->addWidget(gpsPub);
    pubLayout->addStretch();
    QVBoxLayout *subLayout = new QVBoxLayout();
    subLayout->addWidget(videoSub);
    subLayout->addWidget(gpsSub);
    subLayout->addStretch();
    mainLayout->addLayout(pubLayout);
    mainLayout->addLayout(subLayout);
    setCentralWidget(centralWidget);
}