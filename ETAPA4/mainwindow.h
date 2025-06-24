#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QScrollArea>
#include <QWidget>
#include <QList>
#include "videopublisher.h"
#include "videofollower.h"
#include "gpscarpublisher.h"
#include "gpscarfollower.h"
#include "broker.h"

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

private slots:
    void addVideoPublisher();
    void addVideoFollower();
    void addGPSCarPublisher();
    void addGPSCarFollower();

private:
    Ui::MainWindow *ui;
    Broker* broker;
    QVBoxLayout* pubLayout;
    QVBoxLayout* subLayout;
    QWidget* pubWidget;
    QWidget* subWidget;
    QList<VideoPublisher*> videoPublishers;
    QList<VideoFollower*> videoFollowers;
    QList<GPSCarPublisher*> gpsPublishers;
    QList<GPSCarFollower*> gpsFollowers;
};
#endif // MAINWINDOW_H
