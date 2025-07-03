#ifndef COMPONENT_H
#define COMPONENT_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <iostream>
using namespace std;


class Component{
    public:
        Component();
        Component(string name, string topicName);
        virtual ~Component();
        
        string getName();
        string getTopicName();

    protected:
        string name;
        string topicName;

};
#endif // COMPONENT_H