#include "Player.h"



Player::Player(string n, int h, int p) : Fighter(n, h, p) {
    heartContainers = 3;
    money = 0;
}



int Player::getHeartContainers() {
    return heartContainers;
}

    
void Player::setHeartContainers(int c) {
    heartContainers = c;
}