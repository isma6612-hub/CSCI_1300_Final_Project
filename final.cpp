#include <iostream>
#include <string>
#include <vector>
using namespace std;

string locationName(int l) {
    string location; 

    if (l == 1) {
        location = "Faron";
    } else if (l ==2) {
        location = "Eldin";
    } else if (l == 3) {
        location = "Lake Hylia";
    } else {
        location = "Castle Town";
    }
    
    return location;
}


void displayMenu(int t, int l) {
    cout << "-------Menu-------" << endl;
    cout << "Time left: " << t << " hours" << endl;
    cout << "Location: " << locationName(l) << endl;

    cout << "Options:" << endl;

    cout << "Leave Area (input 1)" << endl;
    cout << "Do something in " << locationName(l) << " (input 2)" << endl;

    cout << "------------------" << endl;

}


int main () {

    //used to store player input
    int choice;

    int location = 1;
    int time = 72; //hours left
    

    bool lost = false;

    //game loop
    while(lost == false) {
        //display menu
        displayMenu(time, location);
        cin >> choice;

        if (choice == 1) {
            //changing locations

            cout << "Where do you want to go?" << endl;
            cout << "Faron (input 1)" << endl;
            cout << "Eldin (input 2)" << endl;
            cout << "Lake Hylia (input 3)" << endl;
            cout << "Castle Town (input 4)" << endl;

            cin >> location;

        } else if (choice == 2) {
            //selecting activity

            int activity;

            cout << "What do you want to do?" << endl;
            cout << "Fight monsters (input 1)" << endl;
            cout << "Go to the store (input 2)" << endl;
            cout << "Go to the dungeon (input 3)" << endl;

            cin >> activity;


        }


        //check win/lose condition and update the lost bool if necessary


    }


    

    return 0;
}