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
    //void actualizarBoton(const string& url); //Qstring o string?
    void update(string message) override;
private:
    QPushButton* boton;
};

#endif // VIDEOFOLLOWER_H
