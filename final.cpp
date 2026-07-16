#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "Fighter.h"
#include "Player.h"
#include "Item.h"
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
    cout << "" << endl;
    cout << "----------------------------" << endl;
    cout << "            Menu            " << endl;
    cout << "----------------------------" << endl;
    cout << "" << endl;
    
    //info
    cout << "Time left: " << t << " hours" << endl;
    cout << "Health: " << h << "/" << c << endl;
    cout << "Money: " << m << " rupees" << endl;
    cout << "" << endl;

    //location and map
    cout << "" << endl;
    cout << "Current location: " << locationName(l) << endl;
    cout << "" << endl;
    cout << "Map:" << endl;
    cout << "" << endl;
    cout << "[Lake Hylia] - [Castle Town] - [Eldin]" << endl;
    cout << "                      |" << endl;
    cout << "                   [Faron]" << endl;
    cout << "" << endl;
    cout << "" << endl;
    
    
    //options
    cout << "Options:" << endl;

    cout << "Display Inventory (input 1)" << endl;
    cout << "Leave Area (input 2)" << endl;
    cout << "Do something in " << locationName(l) << " (input 3)" << endl;
    cout << "Ask Midna for advice (input 4)" << endl;

    cout << "----------------------------" << endl;
    cout << "" << endl;
    cout << "" << endl;

}


void displayInventory(vector<Item> i, int a) {
    //where i is the inventory and a is the number of arrows

    string inventory = "Inventory:\n";

    for (int j = 0; j < 6; j++) {
        inventory += i[j].getName();
        inventory += "\n";
    }

    cout << inventory << endl;


}


void midnaAdvice(vector<Item> i, int a) {
    //where i is inventory and a is number of arrows
    //checks inventory and gives advice on what to do next

    //booleans to check if player has item

    //triforce
    bool power = Item("Triforce of Power").have(i);
    bool courage = Item("Triforce of Courage").have(i);
    bool wisdom = Item("Triforce of Wisdom").have(i);

    //other
    bool sword = Item("Sword").have(i);
    bool bow = Item("Bow").have(i);
    bool potion = Item("Health Potion").have(i);

    

    cout << "" << endl;
    cout << "" << endl;
    cout << "Midna:" << endl;

    //checking which triforce you have
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

    cout << "" << endl;
    cout << "" << endl;

}


bool fight(int l, int h, int p, int c, bool b, bool po, int a[], int potion[], bool boss) {
    //l is location, h is player health, p is player power, c is number of heart containers
    //b is true if the player has a bow, po is true if the player has a potion, a[0] is number of arrows, potion[0] is the number of potions
    //boss is true if this is the boss fight
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
        monster.setHealth(6);
        monster.setPower(2);
    } else if (l ==2) {
        monster.setName("Chu");
        monster.setHealth(6);
        monster.setPower(1);
    } else if (l == 3) {
        monster.setName("Keese");
        monster.setHealth(6);
        monster.setPower(3);
    } else if ((l == 4) && (!boss)) {
        monster.setName("ReDead");
        monster.setHealth(10);
        monster.setPower(3);
    } else {
        monster.setName("Ganon");
        monster.setHealth(10);
        monster.setPower(3);
    }

    //advice section
    cout << "" << endl;
    cout << monster.getName() << " is attacking!" << endl;
    cout << "" << endl;
    cout << "Midna: Remember, when you attack with a sword, your defensive abilities will decrease." << endl;
    cout << "You'll take more damage each round you use your sword, but your sword is more powerful than a bow." << endl;
    cout << "But if you use a bow or a health potion, your defensive abilities will increase," << endl;
    cout << "causing you to take less damage from your opponent." << endl;
    cout << "" << endl;
    
    
    
    //fight loop
    while ((h > 0) && (monster.getHealth() > 0)) {
        int choice;
        bool valid = false; //checks if the input is valid


        while (valid == false) {
            
            if (!b && !po) {
                //case: the player has a sword only
                cout << "" << endl;
                cout << "Current health: " << h << "/" << c << endl;
                cout << "What will you do?" << endl;
                cout << "Use sword (input 1)" << endl;
                cout << "Input: ";
                cin >> choice;

                if (cin.fail()) {
                    cout << "Invalid number, pick again" << endl;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } else if (choice != 1) {
                    cout << "Invalid number, pick again" << endl;
                } else {
                    valid = true;
                }
            } else if (!b && po) {
                //case: player has a sword and a potion
                cout << "" << endl;
                cout << "Current health: " << h << "/" << c << endl;
                cout << "What will you do?" << endl;
                cout << "Use sword (input 1)" << endl;
                cout << "Use health potion (input 3)" << endl;
                cout << "Input: ";
                cin >> choice;

                if (cin.fail()) {
                    cout << "Invalid number, pick again" << endl;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } else if ((choice != 1) && (choice != 3)) {
                    cout << "Invalid number, pick again" << endl;
                } else if (potion[0] <=0) {
                    cout << "You don't have a potion right now, pick again" << endl;
                } else {
                    valid = true;
                }
            } else if (b && !po) {
                //case: player has a sword and bow
                cout << "" << endl;
                cout << "Current health: " << h << "/" << c << endl;
                cout << "What will you do?" << endl;
                cout << "Use sword (input 1)" << endl;
                cout << "Use bow (input 2)" << endl;
                cout << "Input: ";
                cin >> choice;

                if (cin.fail()) {
                    cout << "Invalid number, pick again" << endl;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } else if ((choice != 1) && (choice != 2)) {
                    cout << "Invalid number, pick again" << endl;
                } else if ((choice == 2) && (a[0] <= 0)) {
                    cout << "You don't have any arrows, pick again" << endl;
                } else {
                    valid = true;
                }
            } else if (b && po) {
                //case: player has a sword, bow, and potion
                cout << "" << endl;
                cout << "Current health: " << h << "/" << c << endl;
                cout << "What will you do?" << endl;
                cout << "Use sword (input 1)" << endl;
                cout << "Use bow (input 2)" << endl;
                cout << "Use health potion (input 3)" << endl;
                cout << "Input: ";
                cin >> choice;

                if (cin.fail()) {
                    cout << "Invalid number, pick again" << endl;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } else if ((choice != 1) && (choice != 2) && (choice != 3)) {
                    cout << "Invalid number, pick again" << endl;
                } else if (potion[0] <=0) {
                    cout << "You don't have a potion right now, pick again" << endl;
                } else if (a[0] <= 0) {
                    cout << "You don't have any arrows, pick again" << endl;
                } else {
                    valid = true;
                }
            }


        }
        

        if (choice == 1) {
            monster.setHealth(monster.getHealth() - p);
            cout << "" << endl;
            cout << "You attack, dealing " << p << " damage" << endl;
            cout << "" << endl;
            defence -= 1;
            if (defence < 0) {
                defence = 0;
            }
        }

        //arrows
        if (choice == 2) {
            monster.setHealth(monster.getHealth() - 1);
            cout << "" << endl;
            cout << "You attack, dealing 1 damage" << endl;
            cout << "" << endl;
            defence += 1;
            a[0] -= 1;
        }

        //potion
        if (choice == 3) {
            h = c;
            defence += 1;
            potion[0] -= 1;
        }

        //monster attack
        if (monster.getHealth() > 0) {
            int monsterAttack = (monster.getPower() - defence);
            if (monsterAttack < 0) {
                monsterAttack = 0;
            }
            h -= monsterAttack;
            cout << "" << endl;
            cout << "The " << monster.getName() << " attacks, dealing " << (monster.getPower() - defence) << " damage" << endl;
            cout << "" << endl;
        }
        
    }

    if (h > 0) {
        win = true;
    } else {
        win = false;
    }

    return win;
}


bool faronDungeon(int rounds[]) {
    bool win = false;

    cout << "" << endl;
    cout << "Entering the dungeon..." << endl;
    cout << "" << endl;

    //need to pick the right door three times in a row to win
    while (win == false) {
        //first door
        int door1;
        cout << "" << endl;
        cout << "There are three doors. Pick one (Enter 1, 2, or 3)" << endl;
        cin >> door1;
        


        if (cin.fail()) {
            cout << "Invalid number, pick again" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else if ((door1 < 1) || (door1 > 3)) {
            cout << "Invalid number, pick again" << endl;
        } else if ((door1 == 2) || (door1 == 3)) {
            rounds[0] += 1;
            cout << "" << endl;
            cout << "It kind of looks like we're back at the beginning..." << endl;
        } else if (door1 == 1) {
            rounds[0] += 1; //more rounds = more time elapsed

            //door 2
            bool valid = false;
            int door2;

            while (valid == false) {
                
                cout << "" << endl;
                cout << "There are more three doors. Pick one (Enter 1, 2, or 3)" << endl;
                cin >> door2;

                if (cin.fail()) {
                    cout << "Invalid number, pick again" << endl;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } else if ((door2 < 1) || (door2 > 3)) {
                    cout << "Invalid number, pick again" << endl;
                } else {
                    valid = true;
                }
            }

            if ((door2 == 1) || (door2 == 2)) {
                rounds[0] += 1;
                cout << "" << endl;
                cout << "It kind of looks like we're back at the beginning..." << endl;

            } else if (door2 == 3) {
                rounds[0] += 1;

                //door 3
                valid = false;
                int door3;


                while (valid == false) {
                    cout << "" << endl;
                    cout << "There are more three doors. Pick one (Enter 1, 2, or 3)" << endl;
                    cin >> door3;

                    if (cin.fail()) {
                        cout << "Invalid number, pick again" << endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    } else if ((door3 < 1) || (door3 > 3)) {
                        cout << "Invalid number, pick again" << endl;
                    } else {
                        valid = true;
                    }
                }
                
                if ((door2 == 1) || (door2 == 2)) {
                    rounds[0] += 1;
                    cout << "" << endl;
                    cout << "It kind of looks like we're back at the beginning..." << endl;

                } else if (door2 == 3) {
                    rounds[0] += 1;
                    win = true;
                }

        
            }
        }
    }

    return win;
}

bool eldinDungeon(int h) {
    //complete the dungeon if you dodge correctly twice in a row
    //h is the player's health
    bool win;
    int dodgeCount = 0;

    cout << "" << endl;
    cout << "Entering the dungeon..." << endl;
    cout << "" << endl;

    cout << "There's a dragon! Try to dodge it." << endl;

    while ((h > 0) && (dodgeCount < 2)) {
        int randomNum = rand();
        int dragonDirection;

        if ((randomNum % 2) == 0) {
            dragonDirection = 1;
        } else {
            dragonDirection = 2;
        }

        bool valid = false;
        int userDirection = 0;
        

        if (valid == false) {
            
            cout << "" << endl;
            cout << "Which direction do you want to dodge?" << endl;
            cout << "Right (input 1)" << endl;
            cout << "Left (input 2)" << endl;

            cin >> userDirection;

            if (cin.fail()) {
                cout << "Invalid number, pick again" << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else if ((userDirection < 1) || (userDirection > 2)) {
                cout << "Invalid number, pick again" << endl;
            } else {
                valid = true;
            }
        }

        if (dragonDirection == userDirection) {
            cout << "" << endl;
            cout << "The dragon hit you!" << endl;
            h -= 1;
            dodgeCount = 0;
        } else {
            cout << "" << endl;
            cout << "You dodged!" << endl;
            dodgeCount += 1;
        }
        
    }

    if (h < 1) {
        win = false;
    } else {
        cout << "" << endl;
        cout << "You have an opening to kill the dragon!" << endl;
        cout << "" << endl;
        win = true;
    }

    return win;  
}

bool lakeDungeon(int rounds[]) {
    //answer the riddle
    bool win = false;

    cout << "" << endl;
    cout << "Entering the dungeon..." << endl;
    cout << "" << endl;

    cout << "There is a door with an inscription on it:" << endl;
    cout << "Which word in the dictionary is spelled incorrectly?" << endl;

    while (win == false) {
        string answer;
        
        cin >> answer;
        rounds[0] += 1;

        //correcting for capitalization
        for (int i = 0; i < (answer.length()); i++) {
            if ((answer[i] >= 65) && (answer[i] <= 90)) {
                answer[i] += 32;
            }
        }

        if (answer == "incorrectly") {
            win = true;
        } else {
            cout << "" << endl;
            cout << "The door is still locked. Try again" << endl;
            cout << "" << endl;
        }
    }

    return win;
}




int faronChoice() {
    int activity;
    bool valid = false;

    while (valid == false) {
        cout << "" << endl;
        cout << "What do you want to do?" << endl;
        cout << "Fight monsters (input 1)" << endl;
        cout << "Go to the dungeon (input 2)" << endl;
        cout << "Go to the store (input 3)" << endl;

        cin >> activity;

        if (cin.fail()) {
            cout << "Invalid number, pick again" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else if ((activity == 1) || (activity == 2) || (activity == 3)) {
            valid = true;
        } else {
            cout << "Invalid number. Enter a number 1-3." << endl;
        }
    }
    
    return activity;
}

int eldinChoice() {
    int activity;
    bool valid = false;

    while (valid == false) {
        cout << "" << endl;
        cout << "What do you want to do?" << endl;
        cout << "Fight monsters (input 1)" << endl;
        cout << "Go to the dungeon (input 2)" << endl;
        cout << "Go to the store (input 3)" << endl;
        

        cin >> activity;

        if (cin.fail()) {
            cout << "Invalid number, pick again" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else if ((activity == 1) || (activity == 2) || (activity == 3)) {
            valid = true;
        } else {
            cout << "Invalid number. Enter a number 1-3." << endl;
        }
    }
    
    return activity;
}

int lakeChoice() {
    int activity;
    bool valid = false;

    while (valid == false) {
        cout << "" << endl;
        cout << "What do you want to do?" << endl;
        cout << "Fight monsters (input 1)" << endl;
        cout << "Go to the dungeon (input 2)" << endl;
        cout << "Go to the store (input 3)" << endl;

        cin >> activity;

        if (cin.fail()) {
            cout << "Invalid number, pick again" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else if ((activity == 1) || (activity == 2) || (activity == 3)) {
            valid = true;
        } else {
            cout << "Invalid number. Enter a number 1-3." << endl;
        }
    }
    
    return activity;
}


int castleChoice() {
    int activity;
    bool valid = false;

    while (valid == false) {
        cout << "" << endl;
        cout << "What do you want to do?" << endl;
        cout << "Fight monsters (input 1)" << endl;
        cout << "Go to Hyrule Castle (input 2)" << endl;

        cin >> activity;

        if (cin.fail()) {
            cout << "Invalid number, pick again" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else if ((activity == 1) || (activity == 2)) {
            valid = true;
        } else {
            cout << "Invalid number. Enter a number 1-2." << endl;
        }
    }
    
    return activity;
}

bool mogmaSkip() {
    bool skip;
    //option to skip dungeon

    cout << "" << endl;
    cout << "A mole-man appears out of the ground." << endl;
    cout << "" << endl;
    cout << "Bronzi: What's up pal? Name's Bronzi. What's a guy like you doing here?" << endl;
    cout << "" << endl;
    cout << "...What?! You're trying to get to the end of this dungeon to get the Triforce?" << endl;
    cout << "That'll take you forever! Of course, I could let you borrow my digging mitts and tunnel right to the end..." << endl;
    cout << "But I'll need something in return. How about one of your heart containers?" << endl;
    cout << "If you agree, your maximum hearts will decrease by one. What do you say?" << endl;
    cout << "" << endl;

    bool valid = false;
    int option;

    while (valid == false) {
        cout << "Okay (input 1)" << endl;
        cout << "No way (input 2)" << endl;

        cin >> option;

        if (cin.fail()) {
            cout << "Invalid number, pick again" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else if ((option < 1) || (option > 2)) {
            cout << "Invalid number, pick again" << endl;
        } else {
            valid = true;
        }

    }

    if (option == 1) {
        skip = true;
    } else {
        skip = false;
    }

    return skip;
}















int main () {
    //store information
    bool storeSword = true; //signifies that the store has a sword
    bool storePotion = true; //one potion in stock
    int storeArrow = 100; //100 arrows in stock
    bool storeBow = true; //signifies that the store has a bow
    int bowPrice = 20;
    int arrowPrice = 1;
    int potionPrice = 10;

    //used to store player input
    int choice;
    int arrows = 0; //number of arrows the player has

    
    

    int prevLocation;
    int location = 1;
    int time = 72; //hours left
    

    bool lost = false;
    bool won = false;



    //make characters

    Player link("Link", 5, 5);
    
    




    //intro information
    cout << "" << endl;
    cout << "" << endl;
    ifstream inFile("intro.txt");
    string line;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
        std::cout << line << '\n';
        }

        inFile.close();
    } 

    string proceed;
    bool validProceed = false;
    cout << "Continue? (enter 1)";
    while (validProceed == false) {
        cin >> proceed;

        if (proceed != "1") {
            cout << "Invalid input, enter 1" << endl;
        } else {
            validProceed = true;
        }
    }

    




    //game loop
    while((lost == false) && (won == false)) {
        //display menu
        displayMenu(time, location, link.getHealth(), link.getMoney(), link.getHeartContainers());
        
        bool valid = false;
        while (valid == false) {
            cout << "Input: ";
            cin >> choice;

            if (cin.fail()) {
                cout << "Invalid number, pick again" << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else if ((choice < 1) || (choice > 4)) {
                cout << "Invalid number, pick again" << endl;
            } else {
                valid = true;
            }


            
        }
        

        if (choice == 1) {
            displayInventory(link.getInventory(), arrows);

            string proceed;
            bool validProceed = false;
            cout << "Continue? (enter 1)";
            while (validProceed == false) {
                cin >> proceed;

                if (proceed != "1") {
                    cout << "Invalid input, enter 1" << endl;
                } else {
                    validProceed = true;
                }
            }

        } else if (choice == 2) {
            //changing locations

            prevLocation = location;

            cout << "Where do you want to go?" << endl;
            cout << "Faron (input 1)" << endl;
            cout << "Eldin (input 2)" << endl;
            cout << "Lake Hylia (input 3)" << endl;
            cout << "Castle Town (input 4)" << endl;

            bool locationValid = false;
            while (locationValid == false) {
                cin >> location;

                if (cin.fail()) {
                    cout << "Invalid number, pick again" << endl;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } else if ((location < 1) || (location > 4)) {
                    cout << "Invalid number, pick again" << endl;
                } else {
                    locationValid = true;
                }

            }


            int distance = calcDistance(prevLocation, location);
            time -= (distance * 5);

            string proceed;
            bool validProceed = false;
            cout << "Continue? (enter 1)";
            while (validProceed == false) {
                cin >> proceed;

                if (proceed != "1") {
                    cout << "Invalid input, enter 1" << endl;
                } else {
                    validProceed = true;
                }
    }


        } else if (choice == 3) {
            //selecting activity

            int activity = 0;

            if (location == 1) {
                activity = faronChoice();
            } else if (location == 2) {
                activity = eldinChoice();
            } else if (location == 3) {
                activity = lakeChoice();
            } else if (location == 4) {
                activity = castleChoice();
            }

            
            if (activity == 1) {
                if (Item("Sword").have(link.getInventory())) {
                    
                    int arrowArray[1] = {arrows};
                    int potionsUsed[1] = {0};

                    bool haveBow = Item("Bow").have(link.getInventory());
                    bool havePotion = Item("Health Potion").have(link.getInventory());

                    bool boss = false;

                    bool win = fight(location, link.getHealth(), link.getPower(), link.getHeartContainers(), haveBow, havePotion, arrowArray, potionsUsed, boss);

                    if (win == true) {
                        link.setHealth(link.getHeartContainers());
                        link.setMoney(link.getMoney() + 20);
                        arrows = arrowArray[0];
                        if (potionsUsed[0] == 1) {
                            link.removeInventory(Item("Health Potion"));
                        }

                        time -= 2;

                        cout << "Health is replenished! You got 20 rupees!" << endl;
                    } else {
                        lost = true;
                        cout << "You died" << endl;
                    }
                } else {
                    cout << "You should probably have a sword before fighting" << endl;
                }
                






            } else if ((activity == 2) && (location == 1)) {
                if (Item("Triforce of Courage").have(link.getInventory())) {
                    cout << "You have already completed this" << endl;
                } else {
                
                    bool skipFaron = mogmaSkip();
                    bool dungeon = false;
                
                    if (!skipFaron) {
                        int rounds[1] = {0};
                        dungeon = faronDungeon(rounds);
                        time -= rounds[0];
                    }

                    if (skipFaron) {
                        link.setHeartContainers(link.getHeartContainers() - 1);
                    }

                    if ((dungeon == true) || (skipFaron == true)) {
                        cout << "You enter the inner room and open a chest" << endl;
                        link.setInventory(Item("Triforce of Courage"));
                        link.setHeartContainers(link.getHeartContainers() + 1);
                        link.setHealth(link.getHeartContainers());
                        link.setPower(link.getPower() + 1);

                        cout << "You pick up a heart container. Now your max health is " << link.getHeartContainers() << endl;
                        cout << "Your health is reset" << endl;
                        cout << "You have aquired the Triforce of Courage. Your sword glows as if it can feel the energy" << endl;
                        cout << "Your sword's power has increased" << endl;
                    }
                }

            } else if ((activity == 2) && (location == 2)) {
                if (Item("Triforce of Power").have(link.getInventory())) {
                    cout << "You have already completed this" << endl;
                } else {

                    bool skipEldin = mogmaSkip();
                    bool dungeon = false;

                    if (!skipEldin) {
                        dungeon = eldinDungeon(link.getHealth());
                        time -= 8;
                    }

                    if (skipEldin) {
                        link.setHeartContainers(link.getHeartContainers() - 1);
                        if (dungeon == false) {
                            link.setHealth(0);
                            cout << "You died" << endl;
                        }
                    }

                
                    if ((dungeon == true) || (skipEldin == true)) {
                        cout << "You enter the inner room and open a chest" << endl;
                        link.setInventory(Item("Triforce of Power"));
                        link.setHeartContainers(link.getHeartContainers() + 1);
                        link.setHealth(link.getHeartContainers());
                        link.setPower(link.getPower() + 1);

                        cout << "You pick up a heart container. Now your max health is " << link.getHeartContainers() << endl;
                        cout << "Your health is reset" << endl;
                        cout << "You have aquired the Triforce of Power. Your sword glows as if it can feel the energy" << endl;
                        cout << "Your sword's power has increased" << endl;
                    }
                }


            } else if ((activity == 2) && (location == 3)) {
                if (Item("Triforce of Wisdom").have(link.getInventory())) {
                    cout << "You have already completed this" << endl;
                } else {
                    bool skipLake = mogmaSkip();
                    bool dungeon = false;
    
                    if (!skipLake) {
                        int rounds[1] = {0};
                        dungeon = lakeDungeon(rounds);
                        time -= (2 * rounds[0]);
                    }

                    if ((dungeon == true) || (skipLake == true)) {
                        cout << "You enter the inner room and open a chest" << endl;
                        link.setInventory(Item("Triforce of Wisdom"));
                        link.setHeartContainers(link.getHeartContainers() + 1);
                        link.setHealth(link.getHeartContainers());
                        link.setPower(link.getPower() + 1);

                        cout << "You pick up a heart container. Now your max health is " << link.getHeartContainers() << endl;
                        cout << "Your health is reset" << endl;
                        cout << "You have aquired the Triforce of Wisdom. Your sword glows as if it can feel the energy" << endl;
                        cout << "Your sword's power has increased" << endl;
                    }
                }





            } else if ((activity == 2) && (location == 4)) {
                
                if (Item("Triforce of Courage").have(link.getInventory()) && Item("Triforce of Power").have(link.getInventory()) && Item("Triforce of Wisdom").have(link.getInventory())) {
                    int arrowArray[1] = {arrows};
                    int potionsUsed[1] = {0};

                    bool haveBow = Item("Bow").have(link.getInventory());
                    bool havePotion = Item("Health Potion").have(link.getInventory());
                    
                    bool boss = true;

                    bool bossBattle = fight(location, link.getHealth(), link.getPower(), link.getHeartContainers(), haveBow, havePotion, arrowArray, potionsUsed, boss);
                    if (bossBattle == true) {
                        won = true;
                    } else {
                        lost = true;
                        cout << "You died" << endl;
                    }
                } else {
                    cout << "You do not have all pieces of the Triforce" << endl;
                }


    


            } else if ((activity == 3) && (location == 1)) {
                //Faron sword store
                if (storeSword) {
                    cout << "" << endl;
                    cout << "Shopkeeper: We're closing forever. Do you want this sword for free?" << endl;
                    cout << "It's not very powerful, but the woods are dangerous these days." << endl;
                    cout << "I also heard that if you kill a monster, you might get some money..." << endl;
                    cout << "" << endl;
                    cout << "You got a sword!" << endl;

                    link.setInventory(Item("Sword"));

                    storeSword = false;
                    time -= 1;

                } else if (storeSword == false) {
                    cout << "The door is locked..." << endl;
                }
          
            } else if ((activity == 3) && (location == 2)) {
                //Eldin bow and arrow store
                if (storeBow) {
                    cout << "Shopkeeper: We sell bows and arrows. Would you like to buy a bow for 20 rupees?" << endl;
                    cout << "" << endl;

                    int buyBow;
                    bool validBuyBow = false;

                    while (validBuyBow == false) {
                        cout << "Yes (input 1)" << endl;
                        cout << "No (input 2)" << endl;

                        cin >> buyBow;

                        if (cin.fail()) {
                            cout << "Invalid number, pick again" << endl;
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        } else if ((buyBow < 1) || (buyBow > 2)) {
                            cout << "Invalid number, pick again" << endl;
                        } else {
                            validBuyBow = true;
                        }
                    }

                    if ((buyBow == 1) && (link.getMoney() >= bowPrice)) {
                        link.setInventory(Item("Bow"));
                        link.setMoney(link.getMoney() - bowPrice);
                        storeBow = false;
                    } else if ((buyBow == 1) && (link.getMoney() < bowPrice)) {
                        cout << "You don't have enough money" << endl;
                    }
                }


                if (storeArrow > 0) {
                    

                    cout << "Shopkeeper: Would you like to buy some arrows? They're one rupee apiece." << endl;
                    cout << "We have " << storeArrow << " left." << endl;

                    int numberBuyArrow;
                    bool validBuyArrow = false;


                    while (validBuyArrow == false) {
                        cout << "Enter how many arrows you want (0 to " << storeArrow << ")" << endl;

                        cin >> numberBuyArrow;

                        if (cin.fail()) {
                            cout << "Invalid number, pick again" << endl;
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        } else if ((numberBuyArrow < 0) || (numberBuyArrow > storeArrow)) {
                            cout << "Invalid number, pick again" << endl;
                        } else {
                            validBuyArrow = true;
                        }
                    }

                    if ((numberBuyArrow > 0) && (link.getMoney() >= (arrowPrice * numberBuyArrow))) {
                        arrows += numberBuyArrow;
                        storeArrow -= numberBuyArrow;
                        link.setMoney(link.getMoney() - (arrowPrice * numberBuyArrow));
                    } else if ((numberBuyArrow > 0) && (link.getMoney() < (arrowPrice * numberBuyArrow))) {
                        cout << "You don't have enough money" << endl;
                    }

                }

                if (!storeBow && (storeArrow <= 0)) {
                    cout << "Shopkeeper: We're out of inventory." << endl;
                }
            
            } else if ((activity == 3) && (location == 3)) {
                //Lake Hylia potion store
                if (storePotion) {
                    cout << "Shopkeeper: We sell health potions that replenish all of your hearts." << endl;
                    cout << "We have one in stock. Would you like to buy it for " << potionPrice << " rupees?" << endl;

                    bool validBuyPotion = false;
                    int buyPotion;

                    while (validBuyPotion == false) {
                        cout << "Yes (input 1)" << endl;
                        cout << "No (input 2)" << endl;

                        cin >> buyPotion;

                        if (cin.fail()) {
                            cout << "Invalid number, pick again" << endl;
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        } else if ((buyPotion < 1) || (buyPotion > 2)) {
                            cout << "Invalid number, pick again" << endl;
                        } else {
                            validBuyPotion = true;
                        }
                    }

                    if ((buyPotion == 1) && (link.getMoney() >= potionPrice)) {
                        link.setInventory(Item("Potion"));
                        link.setMoney(link.getMoney() - potionPrice);
                        storePotion = false;
                    } else if ((buyPotion == 1) && (link.getMoney() < potionPrice)) {
                        cout << "You don't have enough money" << endl;
                    }

                } else {
                    cout << "We are out of stock" << endl;
                }
                
            } 


            string proceed;
            bool validProceed = false;
            cout << "Continue? (enter 1)";
            while (validProceed == false) {
                cin >> proceed;

                if (proceed != "1") {
                    cout << "Invalid input, enter 1" << endl;
                } else {
                    validProceed = true;
                }

            }

    
        } else if (choice == 4) {
            midnaAdvice(link.getInventory(), arrows);

            string proceed;
            bool validProceed = false;
            cout << "Continue? (enter 1)";
            while (validProceed == false) {
                cin >> proceed;

                if (proceed != "1") {
                    cout << "Invalid input, enter 1" << endl;
                } else {
                    validProceed = true;
                }
            }
        }

        

    

        if (time <= 0) {
            lost = true;
            cout << "You ran out of time" << endl;
        }


    }

    if (lost == true) {
        cout << "Game over" << endl;
    }

    if (won == true) {
        cout << "You saved Princess Zelda!" << endl;
    }


    

    return 0;
}