#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Fighter.h"
#include "Player.h"
#include "Friend.h"
using namespace std;

string locationName(int l) {
    //takes the location code and translates it to a location name
    
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


int calcDistance(int l, int d) {
    //where l is the player's current location code and d is the destination
    
    // creating arrays to store the x and y coordinates of each spot on the map
    int currentCoords[2];
    int destinationCoords[2];

    //assigning coordinates to current coordinate array
    if (l == 1) {
        currentCoords[0] = 1;
        currentCoords[1] = 0;
    } else if (l ==2) {
        currentCoords[0] = 2;
        currentCoords[1] = 1;
    } else if (l == 3) {
        currentCoords[0] = 0;
        currentCoords[1] = 1;
    } else {
        currentCoords[0] = 1;
        currentCoords[1] = 1;
    }

    //assigning coordinates to destination coordinate array
    if (d == 1) {
        destinationCoords[0] = 1;
        destinationCoords[1] = 0;
    } else if (d ==2) {
        destinationCoords[0] = 2;
        destinationCoords[1] = 1;
    } else if (d == 3) {
        destinationCoords[0] = 0;
        destinationCoords[1] = 1;
    } else {
        destinationCoords[0] = 1;
        destinationCoords[1] = 1;
    }

    int a = (currentCoords[0] - destinationCoords[0]);
    int b = (currentCoords[1] - destinationCoords[1]);

    int distance = sqrt(a*a + b*b);

    return distance;
}





void displayMenu(int t, int l, int h, int m, int c) {
    //inputs: time, location, health, money, heart containers

    //header
    cout << "----------------------------" << endl;
    cout << "            Menu            " << endl;
    cout << "----------------------------" << endl;
    
    //info
    cout << "Time left: " << t << " hours" << endl;
    cout << "Health: " << h << "/" << c << endl;
    cout << "Money: " << m << " rupees" << endl;

    //location and map
    cout << "" << endl;
    cout << "Current location: " << locationName(l) << endl;
    cout << "Map:" << endl;
    cout << "" << endl;
    cout << "[Lake Hylia] - [Castle Town] - [Eldin]" << endl;
    cout << "                      |" << endl;
    cout << "                   [Faron]" << endl;
    cout << "" << endl;
    
    
    //options
    cout << "Options:" << endl;

    cout << "Display Inventory (input 1)" << endl;
    cout << "Leave Area (input 2)" << endl;
    cout << "Do something in " << locationName(l) << " (input 3)" << endl;
    cout << "Ask Midna for advice (input 4)" << endl;

    cout << "----------------------------" << endl;

}


void displayInventory(string i[10], int a) {
    //where i is the inventory and a is the number of arrows

    string inventory = "Inventory:\n";

    for (int j = 0; j < 10; j++) {
        inventory += i[j];
        inventory += "\n";
    }

    cout << inventory << endl;


}


void midnaAdvice(string i[10], int a) {
    //where i is inventory and a is number of arrows
    //checks inventory and gives advice on what to do next

    //booleans to check if player has item

    //triforce
    bool power = false;
    bool courage = false;
    bool wisdom = false;

    //other
    bool sword = false;
    bool bow = false;
    bool potion = false;

    for (int j = 0; j < 10; j++) {
        if (i[j] == "Triforce of Power") {
            power = true;
        }
    }

    for (int j = 0; j < 10; j++) {
        if (i[j] == "Triforce of Courage") {
            courage = true;
        }
    }

    for (int j = 0; j < 10; j++) {
        if (i[j] == "Triforce of Wisdom") {
            wisdom = true;
        }
    }

    for (int j = 0; j < 10; j++) {
        if (i[j] == "Sword") {
            sword = true;
        }
    }

    for (int j = 0; j < 10; j++) {
        if (i[j] == "Bow") {
            bow = true;
        }
    }

    for (int j = 0; j < 10; j++) {
        if (i[j] == "Health Potion") {
            potion = true;
        }
    }


    cout << "Midna:" << endl;

    if (power && wisdom && courage) {
        cout << "You have all three pieces of the Triforce! Go to Hyrule Castle and fight Ganon." << endl;
    } else {
        cout << "You are missing part of the Triforce!" << endl;

        if (power == false) {
            cout << "Go to the dungeon in Eldin to get the Triforce of Power." << endl;
        }

        if (courage == false) {
            cout << "Go to the dungeon in Faron to get the Triforce of Courage." << endl;
        }

        if (wisdom == false) {
            cout << "Go to the dungeon in Lake Hylia to get the Triforce of Wisdom." << endl;
        }
    }

    if (sword == false) {
        cout << "You should probably look for a sword first." << endl;
    }

    if (bow == false) {
        cout << "A bow would be useful." << endl;
        
        if (a <= 0) {
            cout << "Make sure to buy arrows, too." << endl;
        }
    }

    if ((bow == true) && (a<=0)) {
        cout << "You'll need some arrows for your bow." << endl;
    }

    if (potion == false) {
        cout << "It would be handy to have a healing potion." << endl;
    }

}


bool fight(int l, int h, int p, int c, int a) {
    //l is location, h is player health, p is player power, c is number of heart containers, a is number of arrows
    //this function will return true if the player wins the fight

    bool win;

    //create the monster
    Fighter monster("Monster", 10, 10);

    //defence counter that goes up if you use your bow and arrow (since you will be farther away from the enemy)
    int defence = 0;

    //advice for fighting monster
    
    //setting specific monster based on location
    if (l == 1) {
        monster.setName("Bokoblin");
        monster.setHealth(5);
        monster.setPower(2);
    } else if (l ==2) {
        monster.setName("Chu");
        monster.setHealth(5);
        monster.setPower(1);
    } else if (l == 3) {
        monster.setName("Keese");
        monster.setHealth(5);
        monster.setPower(5);
    } else {
        monster.setName("ReDead");
        monster.setHealth(10);
        monster.setPower(10);
    } 

    cout << "A " << monster.getName() << " is attacking!" << endl;
    
    int choice;
    
    //fight loop
    while ((h > 0) && (monster.getHealth() > 0)) {
        cout << "Current health: " << h << endl;
        cout << "What will you do?" << endl;
        cout << "Use sword (input 1)" << endl;
        cout << "Use bow (input 2)" << endl;
        cout << "Use health potion (input 3)" << endl;

        cout << "Input: ";
        cin >> choice;

        if (choice == 1) {
            monster.setHealth(monster.getHealth() - 2);
            defence -= 1;
        }

        if (choice == 2) {
            monster.setHealth(monster.getHealth() - 1);
            defence += 1;
            a -= 1;
        }

        if (choice == 3) {
            h = c;
            defence += 1;
            a -= 1;
        }

        if (monster.getHealth() > 0) {
            h -= (monster.getPower() - defence);
            cout << "The " << monster.getName() << " attacks, dealing " << (monster.getPower() - defence) << " damage" << endl;
        }
        
    }

    if (h > 0) {
        win = true;
    } else {
        win = false;
    }

    return win;
}


bool faronDungeon() {
    return true;
}

bool eldinDungeon() {
    return true;
}

bool lakeDungeon() {
    return true;
}

bool finalBoss() {
    return true;
}

bool faronShop(bool sword) {
    //bool sword checks if the store contains a sword

    bool buyingASword;

    if (sword) {
        cout << "Shopkeeper: We're closing forever. Do you want this sword for free? It's not very powerful." << endl;
        cout << "You got a sword!" << endl;
        buyingASword = true;
    } else {
        cout << "The door is locked..." << endl;
        buyingASword = false;
    }

    return buyingASword;

}

bool eldinShop() {
    return true;
}

bool lakeShop() {
    return true;
}


int main () {
    //store stock information
    //bool sword = true; //signifies that the store has a sword
    //int potions = 5; //five potions in stock
    //int arrow = 100; //100 arrows in stock
    //bool bow = true; //signifies that the store has a bow

    //used to store player input
    int choice;

    int arrows = 0;
    string inventory[10];

    //int prevLocation;
    int location = 1;
    int time = 72; //hours left
    

    bool lost = false;



    //make characters

    Player link("Link", 10, 10);




    //intro information
    ifstream inFile("intro.txt");
    string line;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
        std::cout << line << '\n';
        }

        inFile.close();
    } 






    //game loop
    while(lost == false) {
        //display menu
        displayMenu(time, location, link.getHealth(), link.getMoney(), link.getHeartContainers());
        cout << "Input: ";
        cin >> choice;

        if (choice == 1) {
            displayInventory(inventory, arrows);

        } else if (choice == 2) {
            //changing locations

            //prevLocation = location;

            cout << "Where do you want to go?" << endl;
            cout << "Faron (input 1)" << endl;
            cout << "Eldin (input 2)" << endl;
            cout << "Lake Hylia (input 3)" << endl;
            cout << "Castle Town (input 4)" << endl;

            cin >> location;


        } else if (choice == 3) {
            //selecting activity

            int activity;

            cout << "What do you want to do?" << endl;
            cout << "Fight monsters (input 1)" << endl;
            cout << "Go to the store (input 2)" << endl;
            cout << "Go to the dungeon (input 3)" << endl;

            cin >> activity;

        } else if (choice == 4) {
            midnaAdvice(inventory, arrows);
        }


        //check win/lose condition and update the lost bool if necessary


    }


    

    return 0;
}