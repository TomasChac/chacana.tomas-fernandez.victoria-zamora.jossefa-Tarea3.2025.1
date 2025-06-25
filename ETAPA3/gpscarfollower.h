#ifndef GPSCARFOLLOWER_H
#define GPSCARFOLLOWER_H

#include "subscriber.h"
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QObject>
#include <QPushButton>  
#include <QVector>
#include <QPointF>


class GPSCarFollower : public QWidget, public Subscriber
{
    Q_OBJECT
public:
    explicit GPSCarFollower(std::string name, std::string topicName, QWidget* parent = nullptr);

public slots:
    void update(const QString& message); // Slot para recibir mensajes

signals:
    void abrirVentanaGPS(const QVector<QPointF>& posiciones);

private slots:
    void mostrarRecorrido();

private:
    QLabel* infoLabel;
    QPushButton* botonMostrar;
    QVector<QPointF> posiciones; // Guarda las posiciones recibidas
};

#endif // GPSCARFOLLOWER_H
