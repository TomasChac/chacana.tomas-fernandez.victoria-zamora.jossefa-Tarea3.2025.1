#include "component.h"
#include <iostream>
#include <string>

using namespace std;

Component::Component() {
    name = "";
    topicName = "";
}
Component::Component(std::string name, std::string topicName) {
    this->name = name;
    this->topicName = topicName;
}

// Destructor
Component::~Component() {
    // No hay recursos dinámicos que liberar
}
string Component::getName() {
    return name;
}

string Component::getTopicName() {
    return topicName;
}
