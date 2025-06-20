#include "topic.h"
#include "subscriber.h"
#include <string>
using namespace std;

//Constructor por defecto de la clase Topic
Topic::Topic(std::string topicName) {

    this->topicName = topicName;
    // Inicializa el vector de suscriptores
}

void Topic::subscribe(Subscriber* s) {
    // Agrega un suscriptor al vector de suscriptores
    subscribers.push_back(s);
}

void Topic::notify(std::string message) {
    // Notifica a todos los suscriptores con el mensaje
    for (Subscriber* subscriber : subscribers) {
        subscriber->update(message);
    }
}
