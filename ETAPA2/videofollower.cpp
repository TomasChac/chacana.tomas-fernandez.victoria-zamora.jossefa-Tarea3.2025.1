#include "videofollower.h"
#include <QVBoxLayout>
#include <QString>
#include <QMediaPlayer>

#include "subscriber.h"
// Constructor por defecto de la clase VideoFollower
VideoFollower::VideoFollower(std::string name, std::string topicName, QWidget *parent)
    : QWidget(parent), Subscriber(name, topicName)
{

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
void VideoFollower::update(const QString& message)
{
    boton->setText(message);
    ultimoUrl = message; // Guarda el último URL recibido
}

void VideoFollower::reproducirVideo()
{
    if (!ultimoUrl.isEmpty()) {
        emit abrirPestanaVideo(ultimoUrl);
    }
}

