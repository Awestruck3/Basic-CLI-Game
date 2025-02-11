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
    bool playerTurn = true;
    Enemy newEnemies[numOfEnemies];
    for(int i = 0; i < numOfEnemies; i++){
        newEnemies[i].display();
    }


}