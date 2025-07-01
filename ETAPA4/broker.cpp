#include "broker.h"
#include "Topic.h"
#include <string>

using namespace std;

Broker::Broker() {
    // El vector topics se inicializa automáticamente como vacío
}

Topic* Broker::createOrGetTopic(std::string topicName) {
    // Busca si el topic ya existe
    for (Topic* topic : topics) {
        if (topic->getTopicName() == topicName) {
            return topic; // Retorna el topic existente
        }
    }
    
    // Si no existe, crea un nuevo topic
    Topic* newTopic = new Topic(topicName);
    // Agrega el nuevo topic al vector de topics
    topics.push_back(newTopic);
    // Retorna el nuevo topic
    return newTopic;
}

bool Broker::suscribe(Subscriber* s) {
    // Obtiene el topic del suscriptor
    string topicName = s->getTopicName();
    
    // Crea o obtiene el topic correspondiente
    Topic* topic = createOrGetTopic(topicName);
    // Si el topic ya existe, suscribe al suscriptor
//        if (topic != null) {
//            topic.subscribe(sub);
//        return true;
//        } else {
//            return false; // Retorna false si no se pudo crear o obtener el topic
//        }
    // Suscribe al suscriptor al topic
    topic->subscribe(s);
    return true; // Retorna true si la suscripción fue exitosa
}

void Broker::publish(const std::string& topicName, const std::string& message) {
    Topic* topic = createOrGetTopic(topicName);
    if (topic) {
        topic->publish(message);
    }
}
