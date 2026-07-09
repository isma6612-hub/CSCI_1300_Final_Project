#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include <vector>
#include "Fighter.h"
using namespace std;

class Player : public Fighter {
    private:
        int heartContainers;
        int money;


    public:
        
        //constructor
        Player(string n, int h, int p);

        //getters
        int getHeartContainers();

        //setters
        void setHeartContainers(int c);
};




#endif