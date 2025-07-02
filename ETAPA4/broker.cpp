#include "broker.h"

Broker& Broker::getInstance() {
    static Broker instance;
    return instance;
}

Broker::Broker(QObject *parent) : QObject(parent) {}

void Broker::publish(const QString& topic, const QString& message) {
    emit newMessage(topic, message);
}