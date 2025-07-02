#include "gpscarfollower.h"
#include "drawingwidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QStringList>

GPSCarFollower::GPSCarFollower(QWidget *parent) : QWidget(parent) {
    infoLabel = new QLabel("Esperando posición...");
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("<b>Suscriptor (Tópico: GPS)</b>"));
    layout->addWidget(infoLabel);
    mapaWindow = new QWidget();
    mapaWindow->setWindowTitle("Car Tracker (GPS)");
    mapaWindow->setAttribute(Qt::WA_DeleteOnClose); // Se destruye al cerrar
    mapaWidget = new DrawingWidget();
    QVBoxLayout *mapaLayout = new QVBoxLayout(mapaWindow);
    mapaLayout->addWidget(mapaWidget);
}

void GPSCarFollower::onNewMessage(const QString& topic, const QString& message) {
    if (topic != "GPS") return;

    QStringList parts = message.split(' ');
    if (parts.size() < 3) return;

    double t = parts[0].toDouble();
    double x = parts[1].toDouble();
    double y = parts[2].toDouble();

    infoLabel->setText(QString("t: %1, x: %2, y: %3").arg(t).arg(x).arg(y));
    mapaWidget->actualizarPosicion(QPointF(x, y));
    if (!mapaWindow->isVisible()) {
        mapaWindow->show();
    }
}