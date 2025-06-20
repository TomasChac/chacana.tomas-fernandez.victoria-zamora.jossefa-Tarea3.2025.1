#include "videofollower.h"
#include <QVBoxLayout>
#include <QString>
#include "subscriber.h"
// Constructor por defecto de la clase VideoFollower
VideoFollower::VideoFollower(std::string name, std::string topicName, QWidget *parent)
    : QWidget(parent), Subscriber(name, topicName)
{

    boton = new QPushButton("Esperando URL", this);
    //buton->setFixedSize(10, 10, 200, 50);
    boton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    // Crear el reproductor de video
    mediaPlayer = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);

    // Crear y configurar el layout vertical
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(boton);
    layout->addWidget(videoWidget);
    setLayout(layout);

    // Conectar el botón para reproducir el video al hacer clic
    connect(boton, &QPushButton::clicked, this, &VideoFollower::reproducirVideo);
}
    // Sobrescribe el método update para cambiar el texto del botón
void VideoFollower::update(const QString& message)
{
    boton->setText(message);
    ultimoUrl = message;
}

void VideoFollower::reproducirVideo()
{
    if (!ultimoUrl.isEmpty()) {
        mediaPlayer->setSource(QUrl::fromUserInput(ultimoUrl));
        mediaPlayer->play();
    }
}

