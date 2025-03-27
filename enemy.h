#pragma once
#include <string>

//This is our parent parent or whatever. The big boy
class iEnemy{
    //Make the pure data types I think
    std::string name = "";
    int m_health = 0;
    int m_damage = 0;
    int m_defense = 0;
    int levelMod = 0;
    int curHealth = 0;
    bool isDead = false;
    bool m_isDefending = false;
    bool isCat = false; //Using parent/child relationship this might be an obsolete bool

    //These will track loot. As of right now we only have money as a reward 
    bool willDrop;
    int moneyToDrop;

    public:

        
        //iEnemy(int level = 0, int override = 0);

        virtual ~iEnemy() {};
//I am only testing the virtual thing here so I may be wrong going forward
        virtual void setEnemyName(std::string name) = 0;
        virtual int getCurHealth() = 0;
        virtual std::string getName() = 0;
        virtual bool gotKilled() = 0;
        virtual bool getIsDead() = 0;
        virtual int takeDamage(int damageToTake) = 0;
        virtual int attack() = 0;
        virtual bool curDefending()= 0;
        virtual bool noLongerDefending() = 0;
        virtual int actionChoice() = 0;
        virtual int getDefense() = 0;
        virtual bool defenseStatus() = 0;
        virtual int getDropMoney() = 0;
        virtual bool getIsCat() = 0;
        virtual void setLevelMod(int passedLevelMod) = 0;

        virtual void display() = 0;
//I THINK that's everything I need right now. I'm going to make the specific enemy types from here
};


//Let's start by making an enemy class
class Enemy:public iEnemy{

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

        Enemy(int level = 0, int override = 0);

        //We're going to create an enemy generator here
        void setEnemy(std::string enemyName, int level);

        void setEnemyName(std::string name);
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


class Snake:public Enemy{
    public:
        Snake(int level = 0, int override = 0):Enemy(level, override){  
            setEnemyName("Snake");
        }
};

class Rat:public Enemy{
    public:
        Rat(int level = 0, int override = 0):Enemy(level, override){
            setEnemyName("Rat");
        }
};

class Glob:public Enemy{
    public:
        Glob(int level = 0, int override = 0):Enemy(level, override){
            setEnemyName("Glob");
        }
};

class Tiger:public Enemy{
    public:
        Tiger(int level = 0, int override = 0):Enemy(level, override){
            setEnemyName("Tiger");
        }
};

class Lion:public Enemy{
    public:
        Lion(int level = 0, int override = 0):Enemy(level, override){
            setEnemyName("Lion");
        }
};