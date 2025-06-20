#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H
#include "Component.h"
#include<string>


using namespace std;

class Subscriber : public Component{

    public:
        Subscriber();
        Subscriber(string name, string topicName);
        void update(string message);
};
#endif // SUBSCRIBER_H
