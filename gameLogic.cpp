#include "gameLogic.h"
#include <iostream>
#include <stdlib.h>
#include "dice.h"

/* Colour Cheat Sheet
Name            FG  BG
Black           30  40
Red             31  41
Green           32  42
Yellow          33  43
Blue            34  44
Magenta         35  45
Cyan            36  46
White           37  47
Bright Black    90  100
Bright Red      91  101
Bright Green    92  102
Bright Yellow   93  103
Bright Blue     94  104
Bright Magenta  95  105
Bright Cyan     96  106
Bright White    97  107
*/



int generateAmountOfIslands(){
    int rc = 0;
    int numOfTries = 0;
    while(numOfTries == 0){
        numOfTries = roll20();
    }
    for(int i = 0; i < numOfTries; i++){
        rc += roll5050();
    }
    while(rc == 0){
        rc = roll20();
    }
    return rc;
}

void startGame(){
    bool gameEnd = false;
    int chosenIsland;
    //I really hate how I made this
    Player mc(roll20(), roll20(), roll10());
    mc.setName();

    while(gameEnd == false){
        std::cout << "\033[1;36m" << "gameEnd value is " << gameEnd << "\033[1;0m" << std::endl;
        
        int numUpcomingIslands = generateAmountOfIslands();

        Islands* upcomingIslands = displayIslands(numUpcomingIslands);
        mc.turnReset();

        mc.checkItems(NULL, 3);
        if(mc.getFluteUse() == true){
            delete [] upcomingIslands;
            numUpcomingIslands = generateAmountOfIslands();
            upcomingIslands = displayIslands(numUpcomingIslands);
        }
        //Here we get the int value of the island the player wants to explore
        chosenIsland = selectIsland(numUpcomingIslands, mc);

        //I have to subtract one to the chosenIsland because the player is going to select one above the internal number they want
        goToIslandInstance(upcomingIslands[chosenIsland-1], mc, &gameEnd);

        //delete [] upcomingIslands;
    }
    std::cout << "\033[1;36m" << "Game Over! " << gameEnd << "\033[1;0m" << std::endl;
}

int selectIsland(int maxIslandNum, Player& mc){
    int userChoice;
    std::cout << "\033[1;33m" << "Please select which island number you would like to explore. " << std::endl << "Additionally you can input 0 to see your stats or 21 to see your inventory: " << "\033[1;0m";
    userChoice = selectionFunction(mc, 0, maxIslandNum);
    return userChoice;
}


//Here is a function that exists to bridge the selected island to the correct type of instance
void goToIslandInstance(Islands selectedIslands, Player& mc, bool* gameEnd){
    if(selectedIslands.getIslandType() == "Combat"){
        //This will go to the combat instance
        combatInstance(selectedIslands, mc, gameEnd, mc.getLevel());
    }
    else if(selectedIslands.getIslandType() == "Shop"){
        //This goes to shop instance
        shopInstance(selectedIslands, mc, gameEnd);
    }
    else if(selectedIslands.getIslandType() == "Hard Enemy"){
        //In hardEnemy instances we need to send in an override to guarantee output
        int override = 0;
        if(mc.getLevel() == 0){
            override = 1;
        }
        //This goes to Hard Enemy instance
        combatInstance(selectedIslands, mc, gameEnd, mc.getLevel(), override);
    }
    else if(selectedIslands.getIslandType() == "Item Room"){
        //This goes to Item Room instance
        //I guess I need to create items
        itemInstance(selectedIslands, mc, gameEnd);
    }
    else if(selectedIslands.getIslandType() == "Boss"){
        //This goes to Boss instance
        //I guess Boss instance can be an override combat like the hardEnemies
    }
    else{
        //This goes to special what instance (nothing as of now)
    }
}

//This is the combatInstance
//Curhealth is not staying saved
void combatInstance(Islands selectedIsland, Player& mc, bool* gameEnd, int level, int override){
    bool escape = false;
    bool isPlayerTurn = true;
    int lootMoney = 0;
    mc.setTeddy(false); //It should be fine to always set the teddy to false in every combat because it won't work unless the TB is in the inventory

    if(override == 0){
        int numOfEnemies = roll5050()+1;    
        Enemy newEnemies[numOfEnemies];

        for(int i = 0; i < numOfEnemies; i++){
            lootMoney += newEnemies[i].getDropMoney();
        }

        while(escape == false && mc.getCurHealth() > 0){
            int numOfDeadEnemies = checkNumOfDeadEnemies(newEnemies, numOfEnemies);
            std::cout <<  "\033[1;32m"; mc.display(); std::cout << "\033[1;0m";
            for(int i = 0; i < numOfEnemies; i++){
                if(newEnemies[i].getIsDead() == false){
                   std::cout <<  "\033[1;31m"; newEnemies[i].display(); std::cout << "\033[1;0m";
                }
            }

            if(numOfDeadEnemies == numOfEnemies){
                break;
            }
            playerTurn(newEnemies, mc, numOfEnemies, &escape);
            
            if(escape == true){
                break;
            }
            for(int i = 0; i < numOfEnemies; i++){
                newEnemies[i].noLongerDefending();
            }
            //Without this check the game will allow a dead enemy to attack despite being dead
            checkNumOfDeadEnemies(newEnemies, numOfEnemies);

            enemyTurn(newEnemies, mc, numOfEnemies);
        }
    }
    //This else is the hardEnemy fight conbat logic
    else{
        Enemy hardEnemy(mc.getLevel(), override);
        lootMoney = hardEnemy.getDropMoney();
        while(escape == false && mc.getCurHealth() > 0 && hardEnemy.getIsDead() == false){
            //Because the hard enemy is only one enemy, we have to use slightly custom logic to check if it's dead
            if(hardEnemy.getCurHealth() <= 0){
                break;
            }
            std::cout << "\033[1;31m"; hardEnemy.display(); std::cout << "\033[1;0m";
        
            playerTurn(&hardEnemy, mc, 1, &escape);
            if(escape == true){
                break;
            }
            hardEnemy.noLongerDefending();

            if(hardEnemy.getCurHealth() <= 0){
                break;
            }

            enemyTurn(&hardEnemy, mc, 1);
        }
    }

    if(escape == false){
        mc.gatherLoot(lootMoney);
    }

    if(mc.getCurHealth() <= 0){
        *gameEnd = true;
    }
}

//Due to my own foolishness, in the following function the enemy selected by the player will always be enemy[playerAction-1]
void playerTurn(Enemy* enemy, Player& mc, int numOfEnemies, bool* escape){
    int playerAction;
    bool escapeAttempt = false;
    mc.turnReset();
    //This should confirm all active items
    mc.checkItems(enemy, 0);
    
    std::cout << "\033[1;32m" << "It is your turn. Would you like to:" << "\033[1;0m" << std::endl;
    std::cout << "1. Attack" << std::endl << "2. Defend" << std::endl << "3. Flee" << std::endl;
    playerAction = selectionFunction(mc, 0, 4);
    if(playerAction == 1){
        playerAttackLogic(numOfEnemies, enemy, mc);
    }
    if(playerAction == 2){
        //defense logic will go here
        mc.setIsDefending(true);
    }
    if(playerAction == 3){
        //TEMPORARY: FLEE LOGIC IN HERE. THIS IS SUBJECT TO CHANGE
        *escape = mc.fleeAttempt();
    }
}

void enemyTurn(Enemy* enemy, Player& mc, int numOfEnemies){
    int playerDefense = mc.getStrength();
    int playerPassiveDef = mc.getBonusDef();
    
    //Enemys move in order and go from first to third
    for(int i = 0; i < numOfEnemies; i++){
        //If an enemy is dead they cannot move
        if(enemy[i].getIsDead() == false){
            if(enemy[i].actionChoice() > 1){
                int damageTaken;
                int playerEvade = roll10()+1; //I'm rolling the evade per enemy
                //Hypothetically this will skip the entire attack if the player evades
                if(playerEvade > mc.getEvasion()){
                    if(mc.getIsDefending() == true && playerDefense > 0){
                        damageTaken = mc.takeDamage(enemy[i].attack(), playerDefense, playerPassiveDef);
                        playerDefense -= enemy[i].attack();
                    }
                    else{
                        damageTaken = mc.takeDamage(enemy[i].attack(), 0, playerPassiveDef);
                    }
                    if(damageTaken > 0){
                        std::cout << "\033[1;41m" << enemy[i].getName() << " attacks for " << enemy[i].attack() << " damage!" << "\033[0m" << std::endl << "\033[1;31m" << mc.getName() << " takes " << damageTaken << " damage!" << "\033[0m" << std::endl;
                    }
                    else{
                        std::cout << "\033[1;41m" << enemy[i].getName() << " attacks for " << enemy[i].attack() << " damage!" << "\033[0m" << std::endl << "\033[1;31m" << mc.getName() << " takes " << 0 << " damage!" << "\033[0m" << std::endl;
                    }
                    //std::cout << "\033[1;36m" << mc.getBonusDef() << "\033[1;0m"; //This prints passive damage for debug reasons. Might need in the future
                    mc.setTeddy(true); //As of right now this will make the teddy a one time use item. Need to make a post-battle function
                }
                else{
                    std::cout << "\033[1;32m" << mc.getName() << " evades!" << "\033[1;0m" << std::endl;
                }
            }
            //Okay so here defending takes an additional turn to apply. This must be fixed
            else{
                enemy[i].curDefending();
                std::cout << "\033[1;41m" << enemy[i].getName() << " is defending!" << "\033[0m" << std::endl;
            }
        }
    }
}

void playerAttackLogic(int numOfEnemies, Enemy* enemy, Player mc){
    int playerAction; 
    if(numOfEnemies > 1){
        std::cout << "\033[1;32m" << "Select target: " << "\033[1;0m" << std::endl;;
        for(int i=0; i<numOfEnemies; i++){
            if(enemy[i].getIsDead() == false){
                std::cout << i + 1 << ": "; 
                enemy[i].display();
            }
        }

        //Now we select the target
        //I'm not updating this one to the selectionFunction only because this involves calculating dead enemies as well
        std::cin >> playerAction;
        
        //Currently dead enemies have the same error message as an invalid option
        while(playerAction <= 0 || playerAction > numOfEnemies + 1 || enemy[playerAction-1].getIsDead() == true){
            std::cin.clear();
            std::cin.ignore(100, '\n');
            std::cout << "Invalid choice, please use numbers provided: ";
            std::cin >> playerAction;
        }
        std::cout << "\033[1;34m" << enemy[playerAction-1].getName() << " takes " << enemy[playerAction-1].takeDamage(mc.getStrength() + mc.getBonusAttack()) << " damage!" << "\033[1;0m" << std::endl;   
    }
    else{
        std::cout << "\033[1;34m" << enemy[0].getName() << " takes " << enemy[0].takeDamage(mc.getStrength() + mc.getBonusAttack()) << " damage!" << "\033[1;0m" << std::endl;
    }
}

int checkNumOfDeadEnemies(Enemy* enemy, int numOfEnemies){
    int numOfDeadEnemies = 0;
    for(int i = 0; i < numOfEnemies; i++){
        if(enemy[i].getCurHealth() <= 0){
            enemy[i].gotKilled();
            numOfDeadEnemies++;
        }
    }
    return numOfDeadEnemies;
}

void shopInstance(Islands selectedIsland, Player& mc, bool* gameEnd){
    //As of right now the shop can be used to heal 5 hp, increase max hp by 3, increase strength by 1.
    int userChoice;
    mc.display();
    std::cout << "\033[1;35m" << "A shopkeeper looks at you." << std::endl << "\033[1;31m" << "1. Heal 5 HP (15 money)" << std::endl << "\033[1;32m" << "2. Increase Max HP by 3 (25 money)" << std::endl << "\033[1;36m" << "3. Increase Strenght by 1 (30 money)" << std::endl << "4. Skip" << std::endl << "\033[1;33m" << "\"Choose...\" " << "\033[1;0m" << std::endl;
    userChoice = selectionFunction(mc, 0, 4);
    while(mc.buy(userChoice) == false){
    std::cin.clear();
    std::cin.ignore(100, '\n');
    std::cin >> userChoice;
    }
}

void itemInstance(Islands selectedIsland, Player& mc, bool* gameEnd){
    Item choices[3];
    int userChoice;

    for(int i = 0; i < 3; i++){
        choices[i].generateItem();
        std::cout << i+1;
        choices[i].display();
    }
    std::cout << "Select and item to take or use 4 to skip: ";
    userChoice = selectionFunction(mc, 0, 4);
    if(choices[userChoice-1].getId() == 3){
        mc.bookOfMagic();
    }
    else{
        mc.attainItem(choices, userChoice);
    }
}

//With how often I use this logic for choice making I figured this was easiest
int selectionFunction(Player mc, int low, int high){
    int userChoice = 0;
    std::cin >> userChoice;
    while(userChoice <= low || userChoice > high){
        if(userChoice == 0){
            mc.display();
            std::cin.clear();
            std::cin.ignore(100, '\n');
            std::cout << "\033[1;33m" << "Make selection: " << "\033[1;0m";
            //std::cin >> userChoice;
        }
        else if(userChoice == 21){
            mc.showInventory();
            std::cin.clear();
            std::cin.ignore(100, '\n');
            //std::cin >> userChoice;
            std::cout << "\033[1;33m" << "Make selection: " << "\033[1;0m";
        }
        else{
            std::cin.clear();
            std::cin.ignore(100, '\n');
            std::cout << "\033[1;31m" << "Invalid choice, please use numbers " << low+1 << "-" << high << ": " << "\033[1;0m";
            //std::cin >> userChoice;
        }
        std::cin >> userChoice;
    }
    return userChoice;
}

Islands* displayIslands(int numUpcomingIslands){

    std::cout << numUpcomingIslands << " Island(s) coming up." << std::endl;
    Islands* upcomingIslands = new Islands[numUpcomingIslands];
    
    //This for loop sets the attributes of all the islands then displays them for the player to see.
    //It also assigns numeric value to each island for the player to select
    for(int i=0; i<numUpcomingIslands; i++){
        upcomingIslands[i].setIslands();
        std::cout << "Island #" << i+1 << std::endl;
        upcomingIslands[i].display();
        std::cout << std::endl;
    }
    return upcomingIslands;
}