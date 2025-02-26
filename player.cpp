#include "player.h"
#include <iostream>
#include "dice.h"


Player::Player(int forHealth, int forStrength, int forLuck){
    name = "";
    health = 0;
    strength = 0;
    luck = 0;
    money = 0;
    level = 0;
    itemCurIndex = 0; //This is going to be used for checking all items in inventory and adding new items to the array
    evasion = 0;
    teddy = false;
    fishingRod = false;
    setPlayerStats(forHealth, forStrength, forLuck);
    curHealth = health;
}

void Player::setName(){
    std::string input;
    std::cout << "Enter your name: ";
    std::cin >> input;
    name = input;
}
std::string Player::getName(){
    return name;
}
void Player::setHealth(int randoHealth){
    health = randoHealth;
}
int Player::getHealth(){
    return health;
}
void Player::setStrength(int randoStrength){
    strength = randoStrength;
}
int Player::getStrength(){
    return strength;
}
void Player::setLuck(int randoLuck){
    luck = randoLuck;
}
int Player::getLuck(){
    return luck;
}
int Player::getCurHealth(){
    return curHealth;
}

bool Player::getIsDefending(){
    return isDefending;
}

void Player::setIsDefending(bool updatedStatus){
    isDefending = updatedStatus;
}

//This will take in random numbers and assign them to the player's stats
void Player::setPlayerStats(int forHealth, int forStrength, int forLuck){
    setHealth(forHealth);
    setStrength(forStrength);
    setLuck(forLuck);
}

int Player::takeDamage(int damageToTake, int playerDefense){
    if(isDefending == true && damageToTake - playerDefense > 0){
        curHealth -= damageToTake - playerDefense;
    }
    else if(isDefending == true && damageToTake - playerDefense <= 0){
        curHealth = curHealth;
    }
    else{
        curHealth -= damageToTake;
    }
    return damageToTake - playerDefense;
}

void Player::display(){
    std::cout << name << " Health " << curHealth << "/" << health << " Strength: " << strength << " Money " << money << std::endl; 
}

bool Player::fleeAttempt(){
    bool success = false;
    std::cout << name << " attempts to escape!" << std::endl << "." << std::endl << "." << std::endl << "." << std::endl;
    if(roll20() < 5){
        std::cout << name << "'s escape was successful!" << std::endl;
        success = true;
    }
    else{
        std::cout << name << "'s escape was not successful!" << std::endl;
    }
    return success;
}

void Player::gatherLoot(int lootValue){
    money += lootValue;
}

void Player::heal(int hpToHeal){
    curHealth += hpToHeal;
    if(curHealth > health){
        curHealth = health;
    }
}

void Player::increaseMaxHealth(int healthToIncreaseBy){
    health += healthToIncreaseBy;
}

void Player::increaseStrength(int strengthToIncreaseBy){
    strength += strengthToIncreaseBy;
}

bool Player::buy(int choice){
    bool successfulBuy = false;
    if(choice == 1 && money > 15){
        heal(5);
        successfulBuy = true;
        money -= 15;
    }
    else if(choice == 2 && money > 25){
        increaseMaxHealth(3);
        successfulBuy = true;
        money -= 15;
    }
    else if(choice == 3 && money > 30){
        increaseStrength(1);
        successfulBuy = true;
        money -= 30;
    }
    //I need a thing for not enough money here
    else if(choice == 4){
        successfulBuy = true;
    }
    else{
        std::cout << "\033[1;33m" << "Not enough money" << "\033[1;0m" << std::endl;
    }
    
    return successfulBuy;
}

int Player::getLevel(){
    return level;
}

void Player::attainItem(Item choices[], int selection){
    itemArr[itemCurIndex] = choices[selection-1];
    itemCurIndex++;
}

void Player::showInventory(){
    int i = 0;
    std::cout << "Inventory:" << std::endl;
    if(itemArr[0].getId() == 0){
        std::cout << "Empty" << std::endl;
    }
    while(itemArr[i].getId() != 0){
        std::cout << i+1 << ": " << itemArr[i].getName() << std::endl; 
        i++;       
    }
    std::cout << "\033[1;33m" << "Make selection: " << "\033[1;0m";
}

//This checks the inventory for items and activates them if necessary

void Player::checkItems(Enemy* allEnemies){
    int i = 0;
    //We skip this whole function if there's nothing in the inventory
    while(itemArr[i].getId() != 0){
        //I should probably pass this into an Item function that activates items
        //PreItems
        if(itemArr[i].getPreItem() == true){
            if(itemArr[i].getId() == 1){
                bonusAttack += 2;   
            }
            if(itemArr[i].getId() == 2){
                bonusDef += 4;
            }
            if(itemArr[i].getId() == 5){
                bonusAttack += 3; //I know this technically lowers enemy defense but a little bit of flavour text will make it do that 
            }
            if(itemArr[i].getId() == 6 && teddy == false){
                bonusDef += 1000; //This one's gonna be a bit tricky because I only want it to activate once per turn
            }
            if(itemArr[i].getId() == 7){
                evasion += 3;
            }
            if(itemArr[i].getId() == 9){
                //Okay I need to really reconsider this one. It might not end up being a post item because I want it to activate after selecting enemy
            }
            if(itemArr[i].getId() == 23){
                bonusDef += 10;
            }
            if(itemArr[i].getId() == 24){
                //Oh Christ, how will I get thorns working?
            }
            if(itemArr[i].getId() == 31){
                //Double attack logic here
            }
            if(itemArr[i].getId() == 32){
                //Okay here I need my reroll logic
            }
            if(itemArr[i].getId() == 33){
                bonusDef += 10;
            }
            if(itemArr[i].getId() == 42){
                bonusAttack += 50;
            }

            std::cout << itemArr[i].getName() << " activates!" << std::endl;
        }

        //PostItems
        else if(itemArr[i].getPostItem() == true){
            if(itemArr[i].getId() == 8){
                //I have no idea if this will work lmao
                allEnemies->takeDamage(3);
            }
            std::cout << itemArr[i].getName() << " activates!" << std::endl;
        }

        //ActiveItems
        else if(itemArr[i].getActiveItem() == true){
            if(itemArr[i].getId() == 21){
                //Ugh, logic for reroll goes here. I'll figure that out when I get to it
            }
            std::cout << itemArr[i].getName() << " activates!" << std::endl;
        }

        //OutsideItems
        else if(itemArr[i].getOutsideItem() == true){
            if(itemArr[i].getId() == 3){
                //Increase random stats once
            }
            if(itemArr[i].getId() == 10){
                if(roll10() < 3){
                    heal(1);
                }
            }
            if(itemArr[i].getId() == 22){
                if(fishingRod == true){
                    heal(5);
                }
                else{
                    heal(3);
                }
            }
            if(itemArr[i].getId() == 34){
                luck += 1;
            }
            if(itemArr[i].getId() == 41){
                strength += 1;
            }

            std::cout << itemArr[i].getName() << " activates!" << std::endl;
        }
        i++;
    }
}

//Teddy to be figured out as I go
bool Player::getTeddy(){
    return teddy;
}

void Player::setTeddy(bool newState){
    teddy = newState;
}

void Player::turnReset(){
    isDefending = false;
    bonusAttack = 0;
    bonusDef = 0;
}

int Player::getBonusAttack(){
    return bonusAttack;
}

int Player::getBonusDef(){
    return bonusDef;
}