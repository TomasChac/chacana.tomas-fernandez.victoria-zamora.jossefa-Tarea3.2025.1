#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "videopublisher.h"
#include "videofollower.h"
#include "gpscarpublisher.h"
#include "gpscarfollower.h"
#include "broker.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Broker* broker; // Instancia del broker
    VideoPublisher* videoPublisher;
    VideoFollower* videoFollower;
    GPSCarPublisher* gpsPublisher;
    GPSCarFollower* gpsFollower;
};
#endif // MAINWINDOW_H
