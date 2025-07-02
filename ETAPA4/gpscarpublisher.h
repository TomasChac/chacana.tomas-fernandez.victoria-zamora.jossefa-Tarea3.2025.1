#ifndef GPSCARPUBLISHER_H
#define GPSCARPUBLISHER_H

#include <QWidget>
#include <vector>

class QPushButton;
class QTimer;

class GPSCarPublisher : public QWidget
{
    Q_OBJECT

private:
    // Definimos la estructura aquí para que sea privada a esta clase
    struct GPSData { double tiempo, x, y; };

public:
    explicit GPSCarPublisher(QWidget *parent = nullptr);

signals:
    void wantsToPublish(const QString& topic, const QString& message);

private slots:
    void onCargarArchivo();
    void onPublicarSiguientePunto();

private:
    // La declaración ahora coincide con la implementación en el .cpp
    void interpolarDatos(const std::vector<GPSData>& datosOriginales);

    QPushButton *loadButton;
    QTimer *timer;
    std::vector<GPSData> datosInterpolados;
    int currentIndex;
};

#endif