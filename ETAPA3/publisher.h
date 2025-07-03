#ifndef PUBLISHER_H
#define PUBLISHER_H
#include "Component.h"  // << necesario para que conozca la clase Component
#include "Publisher.h"   // << necesario para que conozca la clase Publisher
#include "Broker.h"
#include "Topic.h"
#include <string>

using namespace std;

class Publisher : public Component{

    public:
        Publisher();
        Publisher(string name, Broker* borker, string topicName);
        void publicar(std::string message);
    private:
        Topic* topic; // Puntero al topic al que publica

};
#endif // PUBLISHER_H
