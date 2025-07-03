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

    // Conectar botón para reproducir
    connect(playButton, &QPushButton::clicked, this, &VideoFollower::onPlayVideo);


    connect(mediaPlayer, &QMediaPlayer::errorOccurred, this, [this](QMediaPlayer::Error error) {
        qDebug() << "--- ERROR DEL REPRODUCTOR ---";
        qDebug() << "Codigo:" << error;
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
        mediaPlayer->setSource(QUrl(lastUrl));
        videoWidget->show();
        mediaPlayer->play();
    }
}
