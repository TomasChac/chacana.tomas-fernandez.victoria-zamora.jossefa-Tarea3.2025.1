#include "topic.h"
#include "subscriber.h"
#include <string>
#include "videofollower.h"
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

void Topic::notify(string message) {
    // Notifica a todos los suscriptores con el mensaje
    for (Subscriber* subscriber : subscribers) {
        subscriber->update(message);
    }
}

string Topic::getTopicName(){
    // Devuelve el nombre del topic
    return topicName;
}

void Topic::publish(const std::string& message) {
    for (Subscriber* sub : subscribers) {
        sub->update(message);
    }
}
