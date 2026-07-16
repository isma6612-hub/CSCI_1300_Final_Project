#include "Player.h"



Player::Player(string n, int h, int p) : Fighter(n, h, p) {
    heartContainers = 5;
    money = 0;
    inventory = {Item("Empty Slot"), Item("Empty Slot"), Item("Empty Slot"), Item("Empty Slot"), Item("Empty Slot"), Item("Empty Slot"), Item("Empty Slot"), Item("Empty Slot"), Item("Empty Slot"), Item("Empty Slot")};
 
}



int Player::getHeartContainers() {
    return heartContainers;
}

int Player::getMoney() {
    return money;
}

vector<Item> Player::getInventory() {
    return inventory;
}


    
void Player::setHeartContainers(int c) {
    heartContainers = c;
}

void Player::setMoney(int m) {
    money = m;
}

void Player::setInventory(Item n) {
    //where n is the item to be added and i is the index
    for (int i = 0; i < 6; i++) {
        if (inventory[i].getName() == "Empty Slot") {
            inventory[i] = n;
            break;
        }
    }
    
}

void Player::removeInventory(Item n) {
    //where i is the index to be cleared
    for (int i = 0; i < 6; i++) {
        if (inventory[i].getName() == n.getName())
        inventory[i] = Item("Empty Slot");
        break;
    }
}