#include "videofollower.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QUrl>
#include <QVideoWidget>
#include <QDebug>

VideoFollower::VideoFollower(const QString& topic, QWidget *parent)
    : QWidget(parent), topicName(topic)
{
    // Crear los widgets
    playButton = new QPushButton("Esperando URL...");
    mediaPlayer = new QMediaPlayer(this);
    videoWidget = new QVideoWidget;
    mediaPlayer->setVideoOutput(videoWidget);

    // Crear el layout y añadir los widgets
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("<b>Suscriptor (Tópico: " + topic + ")</b>"));
    layout->addWidget(playButton);


    // Conectar el clic del botón a la función que reproduce el video
    connect(playButton, &QPushButton::clicked, this, &VideoFollower::onPlayVideo);

    // especificar la señal 'error'
    connect(mediaPlayer, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), this,
        [this](QMediaPlayer::Error error) {
            qDebug() << "--- ERROR DEL REPRODUCTOR ---";
            qDebug() << "Código:" << error;
            // Obtenemos el texto del error llamando a un método del reproductor.
            qDebug() << "Mensaje:" << mediaPlayer->errorString();
            qDebug() << "-----------------------------";
    });
}

void VideoFollower::onNewMessage(const QString& topic, const QString& message)
{
    if (this->topicName == topic) {
        lastUrl = message;
        playButton->setText(lastUrl);
    }
}

void VideoFollower::onPlayVideo()
{
    if (!lastUrl.isEmpty()) {
        videoWidget->setWindowTitle("Reproduciendo Video");
        videoWidget->resize(800, 600);
        videoWidget->setAttribute(Qt::WA_DeleteOnClose);
        mediaPlayer->setMedia(QUrl(lastUrl));
        videoWidget->show();
        mediaPlayer->play();
    }
}