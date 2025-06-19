#ifndef BROKER_H
#define BROKER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <iostream>
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