#ifndef FRIEND_H
#define FRIEND_H
#include <iostream>
#include <string>
using namespace std;


class Friend {
    private:
        string name;
        string dialogue;

    public:
        Friend(string n, string d);
        void speak();
};


#endif
