#pragma once
#include "items.h"
#include "enemy.h"
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
        bool isDefending;

        //These exist as item modifiers
        int bonusDef;
        int bonusAttack;
        int evasion;
        bool teddy;
        bool fishingRod;
        bool fluteUse;
        
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
            int takeDamage(int damageToTake, int playerDefense, int passiveDefence);
            bool getIsDefending();
            bool fleeAttempt();
            void gatherLoot(int lootValue);
            void turnReset();

            //Shop methods
            void heal(int hpToHeal);
            void increaseMaxHealth(int healthToIncreaseBy);
            void increaseStrength(int strengthToIncreaseBy);
            bool buy(int choice);

            //Item methods;
            void attainItem(Item choices[], int selection);
            void showInventory();

            //currentPhase is so the game will activate items at appropriate times
            //0 = pre
            //1 = post
            //2 = active
            //3 = outside
            //Maybe this will work?
            void checkItems(Enemy* allEnemies, int curPhase);
            bool getTeddy();
            void setTeddy(bool newState);
            int getBonusDef() const;
            int getBonusAttack();
            void bookOfMagic();
            bool fluteLogic();
            void setFluteUse(bool toSet);
            bool getFluteUse();
            int getEvasion();

            void activateMessage(Item ActivateItem);

            
    };
