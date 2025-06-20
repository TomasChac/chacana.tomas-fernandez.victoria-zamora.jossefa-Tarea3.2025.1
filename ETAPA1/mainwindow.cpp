#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Crear instancias de VideoPublisher y VideoFollower
    videoPublisher = new VideoPublisher("VideoPublisher", "video_topic", this);
    videoFollower = new VideoFollower("VideoFollower", "video_topic", this);

    // Agregarlas al layout del archivo .ui
    ui->layoutPrincipal->addWidget(videoPublisher);
    ui->layoutPrincipal->addWidget(videoFollower);

    // Conectar la señal urlPublicada del VideoPublisher al slot update del VideoFollower
    connect(videoPublisher, &VideoPublisher::urlPublicada, videoFollower, &VideoFollower::update);
}   

MainWindow::~MainWindow()
{
    delete ui;
}
