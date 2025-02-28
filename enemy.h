#pragma once
#include <string>

//Let's start by making an enemy class
class Enemy{

    //Enemies will need name, health, damage, defense, and maybe a drop table?
    std::string m_name;
    int m_health;
    int m_damage;
    int m_defense;

    int levelMod; //This handles all the changes based on the incoming level value

    //The curHealth will keep track of health while the battle commences, this should not be confused with m_health which represents max health
    int curHealth;
    bool isDead;
    bool m_isDefending;
    bool isCat;


    //These will track loot. As of right now we only have money as a reward 
    bool willDrop;
    int moneyToDrop;

    public:

        //We're going to create a no argument constructor
        Enemy(int level = 0, int override = 0);

        //We're going to create an enemy generator here
        void setEnemy(std::string enemyName, int level);

        //This will give us a name of the enemy which will determine the stats of the enemy going forward 
        std::string setEnemyName(int override = 0);
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
        int getDropMoney();
        bool getIsCat();
        void setLevelMod(int passedLevelMod);

        void display();

};