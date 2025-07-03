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
    Publisher(string name, Broker* broker, string topicName);
    void publicar(const std::string& message);

protected:
    Broker* broker;
    Topic* topic;
};
#endif // PUBLISHER_H
