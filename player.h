#pragma once
#include <iostream>
#include <cstring>
    class Player{
        char name[100];
        int health;
        int strength;
        int luck;
        bool ailment[5];
        bool boone[5];
        int money;
        int curHealth;

        public:
            Player(int forHealth, int forStrength, int forLuck){
                health = 0;
                strength = 0;
                luck = 0;
                setPlayerStats(forHealth, forStrength, forLuck);
                curHealth = health;
            }
            

        
            void setName();
            char* getName();
            void setHealth(int randoHealth);
            int getHealth();
            void setStrength(int randoStrength);
            int getStrength();
            void setLuck( int randoLuck);
            int getLuck();
            void setPlayerStats(int forHealth, int forStrength, int forLuck);

            int takeDamage(int damageToTake);
    };
