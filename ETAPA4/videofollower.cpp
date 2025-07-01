#include "videofollower.h"
#include <QVBoxLayout>
#include <QString>
#include <QLabel>
#include "subscriber.h"
// Constructor por defecto de la clase VideoFollower
VideoFollower::VideoFollower(std::string name, std::string topicName, QWidget *parent)
    : QWidget(parent), Subscriber(name, topicName)
{
    QLabel* nameLabel = new QLabel(QString("Subscriber: %1").arg(QString::fromStdString(name)), this);

    boton = new QPushButton("Esperando URL", this);
    //buton->setFixedSize(10, 10, 200, 50);
    boton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    // Crear y configurar el layout vertical
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(boton);
    setLayout(layout);

    // Conectar el botón para reproducir el video al hacer clic
    connect(boton, &QPushButton::clicked, this, &VideoFollower::reproducirVideo);
    
}
    // Sobrescribe el método update para cambiar el texto del botón
void VideoFollower::update(const std::string& message)
{   
    QString qmsg = QString::fromStdString(message);
    boton->setText(qmsg);
    ultimoUrl = qmsg; // Guarda el último URL recibido
}

void VideoFollower::reproducirVideo()
{
    if (!ultimoUrl.isEmpty()) {
        emit abrirPestanaVideo(ultimoUrl);
    }
}

