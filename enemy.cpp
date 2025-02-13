#include "enemy.h"

void Enemy::setEnemy(std::string enemyName){
    m_name = enemyName;
    m_isDefending = false; //I put isDefending up here because I may make certain enemies begin defending depending on how I feel
    if(enemyName == "Snake"){
        m_defense = roll4();
        m_damage = roll10()%5 + 1;
        m_health = 5 + roll4();
    }
    else if(enemyName == "Rat"){
        m_defense = roll4() + 2;
        m_damage = roll10()%5 + 1;
        m_health = 8 + roll4();
    }
    else if(enemyName == "Glob"){
        m_defense = roll4();
        m_damage = roll10()%3 + 1;
        m_health = 16 + roll4();
    }
    else if(enemyName == "Tiger"){
        m_defense = roll4();
        m_damage = roll20()%10 + 4;
        m_health = 8 + roll6();
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
std::string Enemy::setEnemyName(int level, int override){
    std::string rc;
    int enemyNum = roll6();
    if(enemyNum == 0 || enemyNum == 1){
        return rc = "Snake";
    }
    else if(enemyNum == 2 || enemyNum == 3){
        return rc = "Rat";
    }
    else if(enemyNum == 4){
        return rc = "Glob";
    }
    else if(enemyNum == 5){
        return rc = "Tiger";
    }
    else{
        return rc = "What";
    }

}

void Enemy::display(){
    std::cout << m_name << ": Health: " << curHealth << " Damage: " << m_damage << " Defense " << m_defense << std::endl;
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

void Enemy::takeDamage(int damageToTake){
    if(m_isDefending == true && damageToTake - m_defense > 0){
        curHealth -= damageToTake - m_defense;
    }
    else if(m_isDefending == true && damageToTake - m_defense >= 0){
        curHealth = curHealth;
    }
    else{
        curHealth -= damageToTake;
    }
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