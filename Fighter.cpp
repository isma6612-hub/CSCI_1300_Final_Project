#include "Fighter.h"


Fighter::Fighter(string n, int h, int p) {
    name = n;
    health = h;
    power = p;
}


int Fighter::getHealth() {
    return health;
}
int Fighter::getPower() {
    return power;
}


void Fighter::setHealth(int h) {
    health = h;
}