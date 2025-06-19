#define SUBSCRIBER_H
#ifndef SUBSCRIBER_H
#include "Component.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <iostream>
#include <vector>
using namespace std;

class Subscriber : public Component{

    public:
        Subscriber();
        void update(string message);
};
#endif // SUBSCRIBER_H