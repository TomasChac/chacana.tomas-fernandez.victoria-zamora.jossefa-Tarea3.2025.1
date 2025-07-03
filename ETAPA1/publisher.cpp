#include "publisher.h"
#include <string>
#include "topic.h"
#include "publisher.h"
#include "broker.h"

using namespace std;
Publisher::Publisher() {
    // Constructor por defecto
}

Publisher::Publisher(string name, Broker* broker, string topicName) : Component() {

    this->topic= broker->createOrGetTopic(topicName);
}

void Publisher::publicar(std::string message) {

    topic->notify(message);
}
