#ifndef GPSCARPUBLISHER_H
#define GPSCARPUBLISHER_H
#include "publisher.h"
#include <QWidget>
#include <QTimer>
#include <QPushButton>
#include <QFileDialog>
#include <vector>
#include <string>

using namespace std;

class GPSCarPublisher : public QWidget, public Publisher
{
    Q_OBJECT
public:
    explicit GPSCarPublisher(string name, Broker* broker, string topicName, QWidget* parent = nullptr);

private slots:
    void publicarDatosGPS(); // Slot para publicar los datos GPS
    void cargarDatosDesdeArchivo(); // Slot para cargar datos desde un archivo

private:
    void interpolarDatos(); // Slot para interpolar datos GPS
private:

    struct GPSData {
    double tiempo;
    double x;
    double y;
    };

    std::vector<GPSData> gpsData; // Datos GPS del coche
    std::vector<GPSData> datosInterpolados; // Datos GPS interpolados
    QPushButton* botonCargar; // Botón para cargar datos desde un archivo
    QPushButton* botonPublicar; // Botón para publicar los datos GPS
    int currentIndex; // Índice del dato GPS actual a publicar
    double elapsedTime; // Tiempo transcurrido desde el último envío


};

#endif // GPSCARPUBLISHER_H
