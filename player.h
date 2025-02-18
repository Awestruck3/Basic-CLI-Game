#pragma once
#include <iostream>
#include <cstring>
#include "dice.h"

    class Player{
        char name[100];
        int health;
        int strength;
        int luck;
        int money;
        int curHealth;
        bool ailment[5];
        bool boone[5];
        bool isDefending;

        public:
            //Constructor
            Player(int forHealth, int forStrength, int forLuck);
            
            //Basic Setters and getters
            void setName();
            char* getName();
            void setHealth(int randoHealth);
            int getHealth();
            void setStrength(int randoStrength);
            int getStrength();
            void setLuck( int randoLuck);
            int getLuck();
            void setPlayerStats(int forHealth, int forStrength, int forLuck);
            int getCurHealth();
            void display();
            

            //Combat methods
            void setIsDefending(bool updatedStatus);
            int takeDamage(int damageToTake, int playerDefense);
            bool getIsDefending();
            bool fleeAttempt();
            void gatherLoot(int lootValue);
    };
