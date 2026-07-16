#include "Item.h"



Item::Item(string n) {
    name = n;

}



 //getter
string Item::getName() {
    return name;
}

//setter
void Item::setName(string n) {
    name = n;
}

bool Item::have(vector<Item> i) {
    //checks if the item is in an array
    bool included;

    for (int j = 0; j < 10; j++) {
        if (i[j].getName() == name) {
            included = true;
        }
    }

    return included;
}


int Item::haveIndex(vector<Item> i) {
    int index = 0;

    for (int j = 0; j < 10; j++) {
        if (i[j].getName() == name) {
            index = j;
            break;
        }
    }

    return index;
}