#ifndef VIDEOFOLLOWER_H
#define VIDEOFOLLOWER_H

#include "subscriber.h"
#include <QWidget>
#include <QPushButton>
#include <QString>
#include <string>
#include <QMediaPlayer>
#include <QVideoWidget>

class VideoFollower : public QWidget, public Subscriber
{
    Q_OBJECT
public:
    explicit VideoFollower(std::string name, std::string topicName, QWidget* parent = nullptr);

public slots:
    // Sobrescribe el método update para cambiar el texto del botón
    void update(const std::string& message);
private slots:
    void reproducirVideo();  
signals:
    void abrirPestanaVideo(const QString& url);

private:
    QPushButton* boton;
    QString ultimoUrl;
};

#endif // VIDEOFOLLOWER_H
