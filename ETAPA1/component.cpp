#include "component.h"
#include <iostream>


Component::Component() {
    name = "";
    topicName = "";
}
Component::Component(string name, string topicName) {
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