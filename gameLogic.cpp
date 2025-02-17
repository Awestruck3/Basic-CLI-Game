#include "gameLogic.h"

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

    int numUpcomingIslands = generateAmountOfIslands();
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

    //Here we get the int value of the island the player wants to explore
    chosenIsland = selectIsland(numUpcomingIslands);

    //I have to subtract one to the chosenIsland because the player is going to select one above the internal number they want
    goToIslandInstance(upcomingIslands[chosenIsland-1], mc);

    delete [] upcomingIslands;
}

int selectIsland(int maxIslandNum){
    int userChoice;
    std::cout << "Please select which island number you would like to explore: ";
    std::cin >> userChoice;
    while(userChoice < 1 || userChoice > maxIslandNum){
        std::cin.clear();
        std::cin.ignore(100, '\n');
        std::cout << "Invalid choice, please use numbers provided: ";
        std::cin >> userChoice;
    }
    return userChoice;
}


//Here is a function that exists to bridge the selected island to the correct type of instance
void goToIslandInstance(Islands selectedIslands, Player mc){
    if(selectedIslands.getIslandType() == "Combat"){
        //This will go to the combat instance
        combatInstance(selectedIslands, mc);
    }
    else if(selectedIslands.getIslandType() == "Shop"){
        //This goes to shop instance
    }
    else if(selectedIslands.getIslandType() == "Hard Enemy"){
        //This goes to Hard Enemy instance
    }
    else if(selectedIslands.getIslandType() == "Item Room"){
        //This goes to Item Room instance
    }
    else if(selectedIslands.getIslandType() == "Boss"){
        //This goes to Boss instance
    }
    else{
        //This goes to special what instance (nothing as of now)
    }
}

//This is the combatInstance
void combatInstance(Islands selectedIsland, Player mc){
    int numOfEnemies = roll5050()+1;
    bool isPlayerTurn = true;
    Enemy newEnemies[numOfEnemies];

    //How do I read a full array at once?
    while(mc.getCurHealth() > 0){
        mc.display();
        for(int i = 0; i < numOfEnemies; i++){
            if(newEnemies[i].getCurHealth() <= 0){
                newEnemies[i].gotKilled();
            }
            if(newEnemies[i].getIsDead() == false){
                newEnemies[i].display();
            }
        }
        playerTurn(newEnemies, mc, numOfEnemies);
        for(int i = 0; i < numOfEnemies; i++){
            newEnemies[i].noLongerDefending();
        }
        enemyTurn(newEnemies, mc, numOfEnemies);
    }
}

//Due to my own foolishness, in the following function the enemy selected by the player will always be enemy[playerAction-1]
void playerTurn(Enemy* enemy, Player& mc, int numOfEnemies){
    int playerAction;

    mc.setIsDefending(false);
    std::cout << "It is your turn. Would you like to:" << std::endl;
    std::cout << "1. Attack" << std::endl << "2. Defend" << std::endl << "3. Flee" << std::endl;
    std::cin >> playerAction;
    while(playerAction <= 0 || playerAction >= 4){
        std::cin.clear();
        std::cin.ignore(100, '\n');
        std::cout << "Invalid choice, please use numbers provided: ";
    }
    //This is if the player chooses attack
    if(playerAction == 1){
        playerAttackLogic(numOfEnemies, enemy, mc);
    }
    if(playerAction == 2){
        //defense logic will go here
        mc.setIsDefending(true);
    }
}

void enemyTurn(Enemy* enemy, Player& mc, int numOfEnemies){
    int playerDefense = mc.getStrength();
    //Enemys move in order and go from first to third
    for(int i = 0; i < numOfEnemies; i++){
        //If an enemy is dead they cannot move
        if(enemy[i].getIsDead() == false){
            if(enemy[i].actionChoice() > 1){
                int damageTaken;
                if(mc.getIsDefending() == true && playerDefense > 0){
                    damageTaken = mc.takeDamage(enemy[i].attack(), playerDefense);
                    playerDefense -= enemy[i].attack();
                }
                else{
                    damageTaken = mc.takeDamage(enemy[i].attack(), 0);
                }

                std::cout << enemy[i].getName() << " attacks for " << enemy[i].attack() << " damage!" << std::endl << mc.getName() << " takes " << damageTaken << " damage!" << std::endl;
            }
            //Okay so here defending takes an additional turn to apply. This must be fixed
            else{
                enemy[i].curDefending();
                std::cout << enemy[i].getName() << " is defending!" << std::endl;
            }
        }
    }
}

void playerAttackLogic(int numOfEnemies, Enemy* enemy, Player mc){
    int playerAction;
    if(numOfEnemies > 1){
        std::cout << "Select target: " << std::endl;;
        for(int i=0; i<numOfEnemies; i++){
            if(enemy[i].getIsDead() == false){
                std::cout << i + 1 << ": "; 
                enemy[i].display();
            }
        }
        //Now we select the target
        std::cin >> playerAction;
        
        //Currently dead enemies have the same error message as an invalid option
        while(playerAction <= 0 || playerAction > numOfEnemies + 1 || enemy[playerAction-1].getIsDead() == true){
            std::cin.clear();
            std::cin.ignore(100, '\n');
            std::cout << "Invalid choice, please use numbers provided: ";
            std::cin >> playerAction;
        }
        std::cout << enemy[playerAction-1].getName() << " takes " << enemy[playerAction-1].takeDamage(mc.getStrength()) << " damage!" << std::endl;
        
    }
}