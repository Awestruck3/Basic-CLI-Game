#pragma once
#include <iostream>
#include <string>
#include "dice.h"

//Let's start by making an enemy class
class Enemy{

    //Enemies will need name, health, damage, defense, and maybe a drop table?
    std::string m_name;
    int m_health;
    int m_damage;
    int m_defense;

    //The curHealth will keep track of health while the battle commences, this should not be confused with m_health which represents max health
    int curHealth;
    bool isDead;
    bool m_isDefending;

    public:

        //We're going to create a no argument constructor
        Enemy(){
            m_name = "Nothing";
            m_damage = -1;
            m_health = -1;
            m_defense = -1;
            m_isDefending = false;
            isDead = false;
            //No level or override to the defaul constructor. This will be changed in future constructors
            m_name = setEnemyName();
            setEnemy(m_name);
        }
        //We're going to create an enemy generator here
        void setEnemy(std::string enemyName);

        //This will give us a name of the enemy which will determine the stats of the enemy going forward 
        std::string setEnemyName(int level = 0, int override = 0);
        int getCurHealth();
        std::string getName();
        bool gotKilled();
        bool getIsDead();
        int takeDamage(int damageToTake);
        int attack();
        bool curDefending();
        bool noLongerDefending();
        int actionChoice();
        int getDefense();
        bool defenseStatus();

        void display();

};