#include "publisher.h"
#include <string>
#include "topic.h"
#include "publisher.h"
#include "broker.h"
#include "component.h"

using namespace std;
Publisher::Publisher() {
    // Constructor por defecto
}

Publisher::Publisher(string name, Broker* broker, string topicName) : Component(name, topicName) {
    this->broker = broker; 
    this->topic = broker->createOrGetTopic(topicName);
}

void Publisher::publicar(const std::string& mensaje) {
    if (broker) {
        broker->publish(topicName, mensaje);
    }
}
