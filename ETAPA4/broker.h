#ifndef BROKER_H
#define BROKER_H
#include <QObject>
#include <QString>

class Broker : public QObject {
    Q_OBJECT
private:
    Broker(QObject *parent = nullptr);
public:
    Broker(const Broker&) = delete;
    void operator=(const Broker&) = delete;
    static Broker& getInstance();
public slots:
    void publish(const QString& topic, const QString& message);
signals:
    void newMessage(const QString& topic, const QString& message);
};
#endif