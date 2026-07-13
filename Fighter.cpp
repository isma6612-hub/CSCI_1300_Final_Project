#include "Fighter.h"


Fighter::Fighter(string n, int h, int p) {
    name = n;
    health = h;
    power = p;
}

//getters
string Fighter::getName() {
    return name;
}
int Fighter::getHealth() {
    return health;
}
int Fighter::getPower() {
    return power;
}


//setter
void Fighter::setName(string n) {
    name = n;
}
void Fighter::setHealth(int h) {
    health = h;
}
void Fighter::setPower(int p) {
    power = p;
}
