#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include <vector>
#include "Fighter.h"
#include "Item.h"
using namespace std;

class Player : public Fighter {
    private:
        int heartContainers;
        int money;
        vector<Item> inventory;
        


    public:

        //string inventory[10];
        
        //constructor
        Player(string n, int h, int p);

        //getters
        int getHeartContainers();
        int getMoney();
        vector<Item> getInventory();

        //setters
        void setHeartContainers(int c);
        void setMoney(int m);
        void setInventory(Item n);
        void removeInventory(Item n);
};




#endif