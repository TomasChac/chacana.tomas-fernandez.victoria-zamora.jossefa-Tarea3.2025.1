#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gpscarpublisher.h"
#include "gpscarfollower.h"
#include "videopublisher.h"
#include "videofollower.h"
#include "broker.h"
#include <QVBoxLayout>
#include <QMenu>
#include <QScrollArea>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Crear una instancia del Broker
    broker = new Broker();

    // Configurar la ventana principal
    QMenuBar* menuBar = new QMenuBar(this);
    QMenu* pubMenu = menuBar->addMenu("Publisher");
    QMenu* subMenu = menuBar->addMenu("Subscriber");
    QAction* addVideoPub = pubMenu->addAction("Video");
    QAction* addGPSPub = pubMenu->addAction("Car's GPS");
    QAction* addVideoSub = subMenu->addAction("Video");
    QAction* addGPSSub = subMenu->addAction("Car's GPS");
    setMenuBar(menuBar);

    // Conectar las acciones del menú a los slots correspondientes

    connect(addVideoPub, &QAction::triggered, this, &MainWindow::addVideoPublisher);
    connect(addGPSPub, &QAction::triggered, this, &MainWindow::addGPSCarPublisher);
    connect(addVideoSub, &QAction::triggered, this, &MainWindow::addVideoFollower);
    connect(addGPSSub, &QAction::triggered, this, &MainWindow::addGPSCarFollower);


    // Layouts
    QWidget* central = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(central);

    // Inicializar los layouts y widgets
    pubLayout = new QVBoxLayout();
    subLayout = new QVBoxLayout();


    // Crear widgets para los publishers y subscribers
    pubWidget = new QWidget();
    subWidget = new QWidget();
    pubWidget->setLayout(pubLayout);
    subWidget->setLayout(subLayout);

    // Configurar los scroll areas
    QScrollArea* pubScroll = new QScrollArea();
    QScrollArea* subScroll = new QScrollArea();
    pubScroll->setWidget(pubWidget);
    subScroll->setWidget(subWidget);
    pubScroll->setWidgetResizable(true);
    subScroll->setWidgetResizable(true);

    // Añadir los scroll areas al layout principal
    mainLayout->addWidget(pubScroll);
    mainLayout->addWidget(subScroll);

    setCentralWidget(central);
    setWindowTitle("");
    
}   

void MainWindow::addVideoPublisher() {
    bool ok;
    QString name = QInputDialog::getText(this, "Video Publisher Name", "Nombre:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;
    QString topic = QInputDialog::getText(this, "Video Publisher Topic", "Tópico:", QLineEdit::Normal, "", &ok);
    if (!ok || topic.isEmpty()) return;

    auto* pub = new VideoPublisher(name.toStdString(), broker, topic.toStdString(), this);
    videoPublishers.append(pub);
    pubLayout->addWidget(pub);
}

void MainWindow::addVideoFollower() {
    bool ok;
    QString name = QInputDialog::getText(this, "Video Subscriber Name", "Nombre:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;
    QString topic = QInputDialog::getText(this, "Video Subscriber Topic", "Tópico:", QLineEdit::Normal, "", &ok);
    if (!ok || topic.isEmpty()) return;

    auto* sub = new VideoFollower(name.toStdString(), topic.toStdString(), this);
    if (broker->suscribe(sub)) {
        videoFollowers.append(sub);
        subLayout->addWidget(sub);
    } else {
        QMessageBox::warning(this, "Error", "Tópico no encontrado");
        delete sub;
    }
}

void MainWindow::addGPSCarPublisher() {
    bool ok;
    QString name = QInputDialog::getText(this, "GPS Publisher Name", "Nombre:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;
    QString topic = QInputDialog::getText(this, "GPS Publisher Topic", "Tópico:", QLineEdit::Normal, "", &ok);
    if (!ok || topic.isEmpty()) return;

    auto* pub = new GPSCarPublisher(name.toStdString(), broker, topic.toStdString(), this);
    gpsPublishers.append(pub);
    pubLayout->addWidget(pub);
}

void MainWindow::addGPSCarFollower() {
    bool ok;
    QString name = QInputDialog::getText(this, "GPS Subscriber Name", "Nombre:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;
    QString topic = QInputDialog::getText(this, "GPS Subscriber Topic", "Tópico:", QLineEdit::Normal, "", &ok);
    if (!ok || topic.isEmpty()) return;

    auto* sub = new GPSCarFollower(name.toStdString(), topic.toStdString(), this);
    if (broker->suscribe(sub)) {
        gpsFollowers.append(sub);
        subLayout->addWidget(sub);
    } else {
        QMessageBox::warning(this, "Error", "Tópico no encontrado");
        delete sub;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
