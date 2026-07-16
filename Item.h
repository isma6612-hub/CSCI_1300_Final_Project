#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <string>
using namespace std;


class Item {
    private:
        string name;

    public:
        Item(string n);

        //getter
        string getName();

        //setter
        void setName(string n);

        bool have(vector<Item> i);

        int haveIndex(vector<Item> i);
        
};


#endif
