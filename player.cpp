#include "player.h"
#include "gameLogic.h"
#include <iostream>
#include "dice.h"


Player::Player(int forHealth, int forStrength, int forLuck){
    bool test = false;
    
    name = "";
    health = 0;
    strength = 0;
    luck = 0;
    money = 0;
    level = 0;
    itemCurIndex = 0; //This is going to be used for checking all items in inventory and adding new items to the array
    evasion = 0;
    thorns = 0;
    teddy = false;
    fishingRod = false;
    fluteUse = false;
    matches = 0;
    setPlayerStats(forHealth, forStrength, forLuck);
    curHealth = health;
    if(test == true){
        itemArr[0].itemOverride("Book of Magic", 3, false, false, false, false); 
        itemCurIndex = 1;
    }
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

int Player::takeDamage(int damageToTake, int playerDefence, int passiveDefence){
    int fulldefence = playerDefence + passiveDefence;

    if(isDefending == true && damageToTake - fulldefence > 0){
        curHealth -= damageToTake - playerDefence;
    }
    else if(isDefending == true && damageToTake - fulldefence <= 0){
        curHealth = curHealth;
    }
    else if(isDefending == false && damageToTake > passiveDefence){
        curHealth -= damageToTake - passiveDefence;
    }
    else{
        damageToTake = 0;
    }
    return damageToTake - fulldefence;
}

void Player::display(){
    std::cout << name << std::endl << "\033[1;95m" << "Current Level: " << level << std::endl << "\033[1;91m" << "Health: " << curHealth << "/" << health << std::endl << "\033[1;94m" << "Strength: " << strength << std::endl << "\033[1;93m" << "Money: " << money << std::endl << "\033[1;92m" << "Luck: " << luck << "\033[1;0m" << std::endl; 
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

void Player::adjustLevel(int amountToAdjustBy){
    level += amountToAdjustBy;
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
    if(selection < 4){
        itemArr[itemCurIndex] = choices[selection-1];
        if(itemArr[itemCurIndex].getId() == 10){
            fishingRod = true;
        }
        itemCurIndex++;
    }
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
// 0 = pre
// 1 = post
// 2 = active
// 3 = outside
void Player::checkItems(Enemy* allEnemies, int curPhase){
    int i = 0;
    //We skip this whole function if there's nothing in the inventory
    while(itemArr[i].getId() != 0){
        //I should probably pass this into an Item function that activates items
        //PreItems
        if(itemArr[i].getPreItem() == true && curPhase == 0){
            if(itemArr[i].getId() == 1){
                bonusAttack += 2;   
            }
            if(itemArr[i].getId() == 2){
                bonusDef += 4;
            }
            if(itemArr[i].getId() == 5){
                bonusAttack += 3; 
                bonusDef += 3;
            }
            if(itemArr[i].getId() == 6 && teddy == false){
                bonusDef += 1000; //This one's gonna be a bit tricky because I only want it to activate once per turn
            }
            if(itemArr[i].getId() == 7){
                evasion += 3;
            }
            if(itemArr[i].getId() == 23){
                bonusDef += 10;
            }
            if(itemArr[i].getId() == 24){
                thorns += 3;
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

            activateMessage(itemArr[i]);
        }

        //PostItems
        else if(itemArr[i].getPostItem() == true && curPhase == 1){
            if(itemArr[i].getId() == 8){
                matches += 1;
            }
            if(itemArr[i].getId() == 9){
                //This hurts ALL lions and tigers at the end of the turn
                //I might end up splitting enemies into certain subtypes that are effected by things like this
                activateMessage(itemArr[i]);
                whistleItemLogic(allEnemies);
            }
        }

        //ActiveItems
        else if(itemArr[i].getActiveItem() == true && curPhase == 2){
            if(itemArr[i].getId() == 21){
                //Ugh, logic for reroll goes here. I'll figure that out when I get to it
            }
            std::cout << itemArr[i].getName() << " activates!" << std::endl;
        }

        //OutsideItems
        else if(itemArr[i].getOutsideItem() == true && curPhase == 3){
            if(itemArr[i].getId() == 3){
                bookOfMagic();
            } //I don't think I need this
            if(itemArr[i].getId() == 4){
                if(itemArr[i].getFluteCharge() > 0){
                    setFluteUse(fluteLogic());                    
                }
                if(fluteUse == true){
                    activateMessage(itemArr[i]);
                    itemArr[i].setFluteCharge(1);
                }
            }
            if(itemArr[i].getId() == 10){
                if(roll10() < 3){
                    heal(1);
                    activateMessage(itemArr[i]);
                }
            }
            if(itemArr[i].getId() == 22){
                if(fishingRod == true){
                    heal(5);
                    activateMessage(itemArr[i]);
                }
                else{
                    heal(3);
                    activateMessage(itemArr[i]);
                }
            }
            if(itemArr[i].getId() == 34){
                luck += 1;
            }
            if(itemArr[i].getId() == 41){
                strength += 1;
                activateMessage(itemArr[i]);
            }
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
    matches = 0;
    bonusAttack = 0;
    bonusDef = 0;
    evasion = 0;
    thorns = 0;
    setFluteUse(false);
}

int Player::getBonusAttack(){
    return bonusAttack;
}

int Player::getBonusDef() const{
    return bonusDef;
}

void Player::bookOfMagic(){
    for(int i = 0; i < 2; i++){
        int selectedStat = roll100()%3;
        if(selectedStat == 0){
            health++;
        }
        else if(selectedStat == 1){
            strength++;
        }
        else if(selectedStat == 2){
            luck++;
        }
    }
}

bool Player::fluteLogic(){
    bool rc = false;
    int userInput;
    std::cout << "Would you like to use your flute to reroll the current islands? 1 = Yes, 2 = No: " << std::endl;
    userInput = selectionFunction(*this, 0, 2);
    if(userInput == 1){
        rc = true;
    }
    return rc;
}

void Player::setFluteUse(bool toSet){
    fluteUse = toSet;
}

bool Player::getFluteUse(){
    return fluteUse;
}

void Player::activateMessage(Item activateItem){
    std::cout << "\033[1;34m" << activateItem.getName() << " activates!" << "\033[1;0m" << std::endl;
}

int Player::getEvasion(){
    return evasion;
}

int Player::getThorns(){
    return thorns;
}

int Player::getMatches(){
    return matches;
}

void Player::whistleItemLogic(Enemy* passedEnemy){ 
    if(passedEnemy->getIsCat() == true){
        passedEnemy->takeDamage(2); 
        std::cout << "\033[1;34m" << passedEnemy->getName() << " takes 2 damage from " << name << "'s whistle!" << "\033[1;34m" <<  std::endl;
    }
}