#ifndef TOPIC_H
#define TOPIC_H


#include <string>
#include <vector>

using namespace std;

class Subscriber;    // << declaración adelantada necesaria para usar punteros a Subscriber

class Topic
{
public:

    Topic(string topicName);
    void subscribe(Subscriber*);
    void notify(string message);
    bool isSubscribed(string name);
    string getTopicName();
    void publish(const std::string& message);

private:
    string topicName;
    vector <Subscriber*> subscribers;

};

#endif // TOPIC_H
