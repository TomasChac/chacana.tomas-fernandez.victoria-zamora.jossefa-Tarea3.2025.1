#include "publisher.h"
#include <string>

using namespace std;
//Publisher::Publisher() {
    // Constructor por defecto
//}

Publisher::Publisher(std::string name, std::string topicName) : Component() {

    this->topic= broker->createOrGetTopic(topicName);
}

void Publisher::publicar(std::string message) {

    topic->notify(message);
}
