#include "player.h"


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

//This will take in random numbers and assign them to the player's stats
void Player::setPlayerStats(int forHealth, int forStrength, int forLuck){
    setHealth(forHealth);
    setStrength(forStrength);
    setLuck(forLuck);
}

int Player::takeDamage(int damageToTake){
    if(damageToTake - strength > 0){
        curHealth -= damageToTake - strength;
    }
    return damageToTake - strength;
}

void Player::display(){
    std::cout << name << " Health " << curHealth << "/" << health << " Strength: " << strength << std::endl; 
}