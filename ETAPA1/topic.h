#ifndef TOPIC_H
#define TOPIC_H


#include <string>
#include <vector>

using namespace std;


class Topic
{
public:
    Topic();
    void suscribe(Subscriber* s);
    void notify(string message);
    bool isSubscribed(string name);

private:
    string topicName;
    vector <Subscriber*> subscribers;

};

#endif // TOPIC_H
