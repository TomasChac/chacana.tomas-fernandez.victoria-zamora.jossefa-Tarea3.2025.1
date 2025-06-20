#include"subscriber.h"
#include "broker.h"
#include <string>

using namespace std;

Subscriber::Subscriber() {
    // Constructor por defecto
}

Subscriber::Subscriber(std::string name, std::string topicName) : Component() {

}

void Subscriber::update(std::string message) {
    // Puedes dejarlo vacío si es una clase base
}
