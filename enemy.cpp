#include "enemy.h"
#include <iostream>
#include "dice.h"

Enemy::Enemy(int level, int override){
    m_name = "nullptr";
    m_damage = -1;
    m_health = -1;
    m_defense = -1;
    m_isDefending = false;
    isDead = false;
    isCat = false;
    //No level or override to the defaul constructor. This will be changed in future constructors
    setEnemy(m_name, level);
}

//I suspect I'm really gonna need to rework this one
void Enemy::setEnemy(std::string enemyName, int level){
    m_name = enemyName;
    levelMod = level;
    m_isDefending = false; //I put isDefending up here because I may make certain enemies begin defending depending on how I feel
    moneyToDrop = 0;
    willDrop = roll5050();
    if(willDrop == true){
        moneyToDrop = roll20() + 1;
        moneyToDrop += roll20();
    }
    if(enemyName == "Snake"){
        m_defense = roll4() + 1;
        m_damage = roll10()%5 + 1 + (levelMod+1/2);
        m_health = 8 + roll4();
    }
    else if(enemyName == "Rat"){
        m_defense = roll4() + 2;
        m_damage = roll10()%5 + 1 + (levelMod+1/2);
        m_health = 8 + roll4();
    }
    else if(enemyName == "Glob"){
        m_defense = roll4();
        m_damage = roll10()%3 + 1+ (levelMod+1/2);
        m_health = 16 + roll4();
    }
    else if(enemyName == "Tiger"){
        m_defense = roll4();
        m_damage = roll10()%10 + 4 + (levelMod+1/2);
        m_health = 8 + roll6();
        isCat = true;
    }
    else if(enemyName == "Lion"){
        m_defense = roll5050()+5;
        m_damage = roll10() + 3 + (levelMod+1);
        m_health = 50;
        moneyToDrop = 30;
        isCat = true;
    }
    else{
        m_defense = roll20()+1;
        m_damage = roll20()+1;
        m_health = roll20()+1;
    }
    curHealth = m_health;
}

//This is just setting the enemy name. In the future I will add the level the player is at to generate harder enemies.
//Additionally override can be used to guarantee certain styles of enemies (bosses/haunted) depending on context
//These are not currently implimented beyond arguments
void Enemy::setEnemyName(std::string name){
//    std::string rc;
//    int enemyNum = roll6();
//    Override will be for boos and hardEnemies
//    if(override >= 1){
//        return rc = "Lion";
//    }
//    For now I'm just making all the hard enemy overrides Lions but I'll add more later
//    else if(enemyNum == 0 || enemyNum == 1){
//        return rc = "Snake";
//    }
//    else if(enemyNum == 2 || enemyNum == 3){
//        return rc = "Rat";
//    }
//    else if(enemyNum == 4){
//        return rc = "Glob";
//    }
//    else if(enemyNum == 5){
//        return rc = "Tiger";
//    }
//    else{
//        return rc = "What";
//    }
    m_name = name;

}

void Enemy::display(){
    std::cout << m_name << ": Health: " << curHealth << "/" << m_health << " Damage: " << m_damage << " Defense " << m_defense << std::endl;
}

int Enemy::getCurHealth(){
    return curHealth;
}

std::string Enemy::getName(){
    return m_name;
}

bool Enemy::gotKilled(){
    return isDead = true;
}

int Enemy::takeDamage(int damageToTake){
    int rc = 0; //The return value exists only for the display back in the gameLogic
    if(m_isDefending == true && damageToTake - m_defense > 0){
        rc = damageToTake - m_defense;
        curHealth -= damageToTake - m_defense;
    }
    else if(m_isDefending == true && damageToTake - m_defense >= 0){
        curHealth = curHealth;
    }
    else{
        rc = damageToTake;
        curHealth -= damageToTake;
    }
    return rc;
}

bool Enemy::getIsDead(){
    return isDead;
}

int Enemy::attack(){
    return m_damage;
}

bool Enemy::defenseStatus(){
    return m_isDefending;
}

bool Enemy::curDefending(){
    return m_isDefending = true;
}

bool Enemy::noLongerDefending(){
    return m_isDefending = false;
}

int Enemy::getDefense(){
    return m_defense;
}

int Enemy::actionChoice(){
    if(curHealth > m_health/2){
        return roll4() + 1;
    }
    else{
        return roll5050() + 1;
    }
}

int Enemy::getDropMoney(){
    return moneyToDrop;
}

bool Enemy::getIsCat(){
    return isCat;
}

void Enemy::setLevelMod(int passedLevelMod){
    levelMod = passedLevelMod;
}




//From here we're doing snake logic
Snake::Snake(int level, int override):Enemy(level, override){  
    setEnemyName("Snake");
}

int Snake::attack(){
    int rc = Enemy::attack();
    int actionChoice = roll5050();
    if(actionChoice <= 1){
        std::cout << "\033[1;41m" << "Snake attacks with a poison lunge!" << std::endl;
        rc += 2;
    }
    return rc;
}


//From here we're doing the Rat logic
Rat::Rat(int level, int override):Enemy(level, override){
    setEnemyName("Rat");
}


//From here we're donig the Glob logic

Glob::Glob(int level, int override):Enemy(level, override){
    setEnemyName("Glob");
}

//From here we're doing the Tiger logic

Tiger::Tiger(int level, int override):Enemy(level, override){
    setEnemyName("Tiger");
}
//From here we're doing the Lion logic
Lion::Lion(int level, int override):Enemy(level, override){
    setEnemyName("Lion");
}