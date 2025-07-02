#ifndef GPSCARFOLLOWER_H
#define GPSCARFOLLOWER_H
#include <QWidget>
class QLabel;
class DrawingWidget;

class GPSCarFollower : public QWidget {
    Q_OBJECT
public:
    explicit GPSCarFollower(QWidget *parent = nullptr);
public slots:
    void onNewMessage(const QString& topic, const QString& message);
private:
    QLabel* infoLabel;
    DrawingWidget* mapaWidget;
    QWidget* mapaWindow;
};
#endif