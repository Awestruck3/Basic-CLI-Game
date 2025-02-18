#include "player.h"


Player::Player(int forHealth, int forStrength, int forLuck){
    health = 0;
    strength = 0;
    luck = 0;
    money = 0;
    level = 0;
    setPlayerStats(forHealth, forStrength, forLuck);
    curHealth = health;
}

void Player::setName(){
    char* input;
    std::cout << "Enter your name: ";
    std::cin >> input;
    strcpy(name, input);
}
char* Player::getName(){
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