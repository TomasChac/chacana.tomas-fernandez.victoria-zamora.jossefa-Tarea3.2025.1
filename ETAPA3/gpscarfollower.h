#ifndef GPSCARFOLLOWER_H
#define GPSCARFOLLOWER_H

#include "subscriber.h"
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>

class GPSCarFollower : public QWidget, public Subscriber
{
    Q_OBJECT
public:
    explicit GPSCarFollower(std::string name, std::string topicName, QWidget* parent = nullptr);

public slots:
    void update(const QString& message); // Slot para recibir mensajes

private:
    QLabel* infoLabel;
};

#endif // GPSCARFOLLOWER_H