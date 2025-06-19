#define PUBLISHER_H
#ifndef PUBLISHER_H
#include "Component.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <iostream>
using namespace std;
#include "topic.h"

class Publisher : public Component{

    public:
        Publisher();
        void publicar(string message);
    private:
        Topic* topic; // Puntero al topic al que publica
}
#endif // PUBLISHER_H