#include <iostream>
#include "dice.h"
#include "islands.h"
#include "player.h"
#include "enemy.h"

//randomly generate number of islands to land on
//Return the number of islands
int generateAmountOfIslands();

void startGame();
int selectIsland(int maxIslandNum);
void goToIslandInstance(Islands selectedIslands, Player mc);
void combatInstance(Islands selectedIsland, Player mc);
void playerTurn(Enemy& enemy, Player& mc, int numOfEnemies);
