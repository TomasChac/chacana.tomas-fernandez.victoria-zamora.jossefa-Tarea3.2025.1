#ifndef VIDEOFOLLOWER_H
#define VIDEOFOLLOWER_H

#include "subscriber.h"
#include <QWidget>
#include <QPushButton>
#include <QString>
#include <string>

class VideoFollower : public QWidget, public Subscriber
{
    Q_OBJECT
public:
    explicit VideoFollower(std::string name, std::string topicName, QWidget* parent = nullptr);

public slots:
    // Sobrescribe el método update para cambiar el texto del botón
    void update(const QString& message);

private:
    QPushButton* boton;
};

#endif // VIDEOFOLLOWER_H
