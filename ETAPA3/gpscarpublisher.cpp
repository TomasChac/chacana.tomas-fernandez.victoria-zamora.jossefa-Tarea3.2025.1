#include "gpscarpublisher.h"
#include "gpsdata.h"
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QStringList>
#include <QRegularExpression>
#include <QDebug>
#include <QWidget>


GPSCarPublisher::GPSCarPublisher(std::string name, Broker* broker, std::string topicName, QWidget* parent)
    : QWidget(parent), Publisher(name, broker, topicName), currentIndex(0)
{
    // Crear botones
    botonCargar = new QPushButton("Cargar archivo GPS", this);
    botonPublicar = new QPushButton("Iniciar publicación", this);
    botonPublicar->setEnabled(false);

    // Crear timer
    timer = new QTimer(this);

    // Layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(botonCargar);
    layout->addWidget(botonPublicar);
    setLayout(layout);

    // Conexiones
    connect(botonCargar, &QPushButton::clicked, this, &GPSCarPublisher::cargarArchivoGPS);
    connect(botonPublicar, &QPushButton::clicked, [this]() {
        currentIndex = 0;
        timer->start(1000); // Publicar cada 1 segundo
    });
    connect(timer, &QTimer::timeout, this, &GPSCarPublisher::publicarDatoGPS);
}

void GPSCarPublisher::interpolarDatos()
{
    datosInterpolados.clear();
    if (gpsData.empty()) return;

    for (size_t i = 0; i + 1 < gpsData.size(); ++i) {
        const auto& a = gpsData[i];
        const auto& b = gpsData[i + 1];

        // Agrega el punto inicial
        if (datosInterpolados.empty())
            datosInterpolados.push_back(a);

        int t0 = static_cast<int>(a.tiempo);
        int t1 = static_cast<int>(b.tiempo);

        for (int t = t0 + 1; t < t1; ++t) {
            double alpha = (t - a.tiempo) / (b.tiempo - a.tiempo);
            double x = a.x + alpha * (b.x - a.x);
            double y = a.y + alpha * (b.y - a.y);
            datosInterpolados.push_back({static_cast<double>(t), x, y});
        }
        // Agrega el punto final del segmento
        datosInterpolados.push_back(b);
    }
}

void GPSCarPublisher::cargarArchivoGPS()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Selecciona archivo GPS", "", "Archivos de texto (*.txt);;Todos los archivos (*)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo.");
        return;
    }

    gpsData.clear();
    QTextStream in(&file);

    // Leer el archivo línea por línea
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        if (parts.size() == 3) {
            bool ok1, ok2, ok3;
            double t = parts[0].toDouble(&ok1);
            double x = parts[1].toDouble(&ok2);
            double y = parts[2].toDouble(&ok3);
            if (ok1 && ok2 && ok3) {
                gpsData.push_back({t, x, y});
            }
        }
    }
    file.close();

    // Interpolar después de cargar
    interpolarDatos();
    currentIndex = 0;

    if (!datosInterpolados.empty()) {
        botonPublicar->setEnabled(true);
        QMessageBox::information(this, "Éxito", "Archivo cargado e interpolado correctamente.");
    } else {
        botonPublicar->setEnabled(false);
        QMessageBox::warning(this, "Error", "No se encontraron datos válidos en el archivo.");
    }
}


void GPSCarPublisher::publicarDatoGPS() {
    if (currentIndex < datosInterpolados.size()) {
        const auto& dato = datosInterpolados[currentIndex];
        QString mensaje = QString("%1 %2 %3").arg(dato.tiempo).arg(dato.x).arg(dato.y);
        qDebug() << "Publicando:" << mensaje; // <-- Esto te mostrará en la consola cada dato publicado
        publicar(mensaje.toStdString());
        emit datoPublicado(mensaje);
        currentIndex++;
    } else {
        timer->stop();
    }
}
