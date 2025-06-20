#ifndef BROKER_H
#define BROKER_H

#include <string>
#include <vector>
#include "Topic.h"
#include "Subscriber.h"
using namespace std;

class Broker {

    public:
        Broker();
        Topic* createOrGetTopic(string topicName);
        bool suscribe(Subscriber* s);
    
    private:
        vector<Topic*> topics;
}
#endif // BROKER_H