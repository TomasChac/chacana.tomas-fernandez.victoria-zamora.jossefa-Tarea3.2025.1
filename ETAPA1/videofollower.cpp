#include "videofollower.h"
#include <QVBoxLayout>
#include <QString>
#include <QSisePolicy>

// Constructor por defecto de la clase VideoFollower
VideoFollower::VideoFollower(string name, QWidget *parent)
    : QWidget(parent), Subscriber(name, topicName)
{

    buton = new QPushButton("Esperando URL", this);
    //buton->setFixedSize(10, 10, 200, 50);
    boton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    // Crear y configurar el layout vertical
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(boton);
    setLayout(layout);
}
    // Sobrescribe el método update para cambiar el texto del botón
void VideoFollower::update(string message)
{
boton->setText(QString::fromStdString(message));
}

