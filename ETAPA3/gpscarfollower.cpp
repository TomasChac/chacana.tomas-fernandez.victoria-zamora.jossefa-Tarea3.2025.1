#include "gpscarfollower.h"
#include "gpsdata.h"
#include <QDateTime>
#include <QRegularExpression>
#include <QVBoxLayout>

GPSCarFollower::GPSCarFollower(std::string name, std::string topicName, QWidget* parent)
    : QWidget(parent), Subscriber(name, topicName)
{
    infoLabel = new QLabel("Esperando posición...", this);
    botonMostrar = new QPushButton("Mostrar Recorrido", this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel(QString("Seguimiento GPS de: %1").arg(QString::fromStdString(name)), this));
    layout->addWidget(infoLabel);
    layout->addWidget(botonMostrar);
    setLayout(layout);
    connect(botonMostrar, &QPushButton::clicked, this, &GPSCarFollower::mostrarRecorrido);
}

void GPSCarFollower::update(const QString& message)
{
    qDebug() << "Follower recibió:" << message;
    // Espera mensajes en formato: "<tiempo> <x> <y>"
    QStringList parts = message.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    if (parts.size() >= 3) {
        bool ok1, ok2, ok3;
        double t = parts[0].toDouble(&ok1);
        double x = parts[1].toDouble(&ok2);
        double y = parts[2].toDouble(&ok3);

        if (ok1 && ok2 && ok3) {
            posiciones.append({t, x, y}); // Guardar la posición
            qDebug() << "Posición guardada:" << t << x << y;
            QString tiempo = QTime::currentTime().toString("HH:mm:ss");
            infoLabel->setText(QString("[%1] Posición: %2, %3 (t=%4)")
                               .arg(tiempo)
                               .arg(x)
                               .arg(y)
                               .arg(t));
            // --- ACTUALIZA LA VENTANA AQUÍ ---
            if (gpsWindow && textEdit) {
                QStringList lines;
                for (const auto& pos : posiciones) {
                    lines << QString("%1 %2 %3").arg(pos.tiempo).arg(pos.x).arg(pos.y);
                }
                textEdit->setText(lines.join("\n"));
            }
            return;
        }
    }

    infoLabel->setText("Error en mensaje: " + message);
}

// gpscarfollower.cpp
void GPSCarFollower::mostrarRecorrido()
{
    if (!gpsWindow) {
        gpsWindow = new QWidget();
        gpsWindow->setAttribute(Qt::WA_DeleteOnClose);
        gpsWindow->setWindowTitle("Recorrido GPS");
        gpsWindow->resize(500, 500);

        QVBoxLayout* layout = new QVBoxLayout(gpsWindow);

        textEdit = new QTextEdit(gpsWindow);
        textEdit->setReadOnly(true);

        layout->addWidget(textEdit);
        gpsWindow->setLayout(layout);

        connect(gpsWindow, &QWidget::destroyed, this, [this]() {
            gpsWindow = nullptr;
            textEdit = nullptr;
        });
    }
    // Actualiza el contenido
    QStringList lines;
    for (const auto& pos : posiciones) {
        lines << QString("%1 %2 %3").arg(pos.tiempo).arg(pos.x).arg(pos.y);
    }
    textEdit->setText(lines.join("\n"));
    gpsWindow->show();
}