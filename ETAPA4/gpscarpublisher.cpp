#include "gpscarpublisher.h"
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

GPSCarPublisher::GPSCarPublisher(QWidget *parent)
    : QWidget(parent), currentIndex(0)
{
    loadButton = new QPushButton("Cargar Archivo GPS");
    timer = new QTimer(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("<b>Publicador (Tópico: GPS)</b>"));
    layout->addWidget(loadButton);

    connect(loadButton, &QPushButton::clicked, this, &GPSCarPublisher::onCargarArchivo);
    connect(timer, &QTimer::timeout, this, &GPSCarPublisher::onPublicarSiguientePunto);
}

void GPSCarPublisher::onCargarArchivo() {
    QString filePath = QFileDialog::getOpenFileName(this, "Abrir archivo de posiciones", "", "Archivos de Texto (*.txt)");
    if (filePath.isEmpty()) return;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo.");
        return;
    }

    std::vector<GPSData> datosOriginales;
    QTextStream in(&file);
    while (!in.atEnd()) {
        double t, x, y;
        in >> t >> x >> y;
        if (in.status() == QTextStream::Ok) {
            datosOriginales.push_back({t, x, y});
        }
    }
    file.close();

    if(datosOriginales.size() < 2){
        QMessageBox::warning(this, "Error", "El archivo debe contener al menos dos puntos de datos para interpolar.");
        return;
    }

    // AHORA LLAMAMOS AL MÉTODO DE INTERPOLACIÓN
    interpolarDatos(datosOriginales);

    // Reiniciamos el índice y comenzamos a publicar
    currentIndex = 0;
    timer->start(1000); // Publicar cada segundo
}

void GPSCarPublisher::interpolarDatos(const std::vector<GPSData>& datosOriginales) {
    datosInterpolados.clear();
    
    // Recorremos los segmentos (del punto i al i+1)
    for (size_t i = 0; i < datosOriginales.size() - 1; ++i) {
        const auto& p1 = datosOriginales[i];
        const auto& p2 = datosOriginales[i+1];

        int t_start = static_cast<int>(p1.tiempo);
        int t_end = static_cast<int>(p2.tiempo);

        // Agregamos el punto de inicio del segmento
        datosInterpolados.push_back(p1);

        // Calculamos los puntos intermedios para cada segundo
        for (int t = t_start + 1; t < t_end; ++t) {
            double ratio = (double)(t - t_start) / (double)(t_end - t_start);
            double x_interp = p1.x + ratio * (p2.x - p1.x);
            double y_interp = p1.y + ratio * (p2.y - p1.y);
            datosInterpolados.push_back({(double)t, x_interp, y_interp});
        }
    }
    // Agregamos el último punto del recorrido
    datosInterpolados.push_back(datosOriginales.back());
}

void GPSCarPublisher::onPublicarSiguientePunto() {
    if (currentIndex >= datosInterpolados.size()) {
        timer->stop();
        QMessageBox::information(this, "Info", "Transmisión de GPS finalizada.");
        return;
    }

    const auto& dato = datosInterpolados[currentIndex];
    QString message = QString("%1 %2 %3").arg(dato.tiempo).arg(dato.x).arg(dato.y);
    emit wantsToPublish("GPS", message);
    currentIndex++;
}