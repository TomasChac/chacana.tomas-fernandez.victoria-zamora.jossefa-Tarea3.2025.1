#include "topic.h"
#include "subscriber.h"
using namespace std;

//Constructor por defecto de la clase Topic
Topic::Topic(string topicName) {

    this->topicName = topicName;
    // Inicializa el vector de suscriptores
}

void Topic::subscribe(Subscriber* s) {
    // Agrega un suscriptor al vector de suscriptores
    subscribers.push_back(s);
}

void Topic::notify(string message) {
    // Notifica a todos los suscriptores con el mensaje
    for (Subscriber* subscriber : subscribers) {
        subscriber->update(message);
    }
}