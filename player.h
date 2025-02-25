#pragma once
#include "items.h"
#include <string>

    class Player{
        std::string name;
        int health;
        int strength;
        int luck;
        int money;
        int curHealth;
        int level;
        int itemCurIndex;
        bool ailment[5];
        bool boone[5];
        bool isDefending;
        Item itemArr[100];

        public:
            //Constructor
            Player(int forHealth, int forStrength, int forLuck);
            
            //Basic Setters and getters
            void setName();
            std::string getName();
            void setHealth(int randoHealth);
            int getHealth();
            void setStrength(int randoStrength);
            int getStrength();
            void setLuck( int randoLuck);
            int getLuck();
            void setPlayerStats(int forHealth, int forStrength, int forLuck);
            int getCurHealth();
            void display();
            int getLevel();
            

            //Combat methods
            void setIsDefending(bool updatedStatus);
            int takeDamage(int damageToTake, int playerDefense);
            bool getIsDefending();
            bool fleeAttempt();
            void gatherLoot(int lootValue);

            //Shop methods
            void heal(int hpToHeal);
            void increaseMaxHealth(int healthToIncreaseBy);
            void increaseStrength(int strengthToIncreaseBy);
            bool buy(int choice);
    };
