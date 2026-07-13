#ifndef FIGHTER_H
#define FIGHTER_H
#include <iostream>
#include <string>
using namespace std;

class Fighter {
private:
    string name;
    int health;
    int power;

public:
    //constructor
    Fighter(string n, int h, int p);

    //getters
    string getName();
    int getHealth();
    int getPower();

    //setters
    void setName(string n);
    void setHealth(int h);
    void setPower(int p);

};



#endif