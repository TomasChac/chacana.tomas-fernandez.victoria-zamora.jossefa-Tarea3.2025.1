#include "publisher.h"


Publisher::Publisher() {
    // Constructor por defecto
}

Publisher::Publisher(string name, string topicName) : Component() {

    this->topic= broker->createOrGetTopic(topicName);
}

void Publisher::publicar(string message) {

    topic->notify(message);
}