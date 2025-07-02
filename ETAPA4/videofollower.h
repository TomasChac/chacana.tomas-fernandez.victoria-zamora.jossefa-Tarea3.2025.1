#ifndef VIDEOFOLLOWER_H
#define VIDEOFOLLOWER_H

#include <QWidget>
#include <QMediaPlayer>

class QPushButton;
class QVideoWidget;

class VideoFollower : public QWidget
{
    Q_OBJECT

public:
    explicit VideoFollower(const QString& topic, QWidget *parent = nullptr);

public slots:
    // Slot que reacciona a los mensajes del broker
    void onNewMessage(const QString& topic, const QString& message);

private slots:
    // Slot que se activa al presionar el botón de play
    void onPlayVideo();

private:
    QString topicName;
    QString lastUrl;
    QPushButton *playButton;
    
    // Miembros para la reproducción de video
    QMediaPlayer* mediaPlayer;
    QVideoWidget* videoWidget;
};

#endif