#include "Friend.h"



Friend::Friend(std::string n, std::string d) {
    name = n;
    dialogue = d;

}


void Friend::speak() {
    cout << dialogue << endl;
}