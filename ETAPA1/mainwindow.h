#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "videopublisher.h"
#include "videofollower.h"
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
};
#endif // MAINWINDOW_H
