#include <iostream>
#include <stdlib.h>
#include "dice.h"
#include "islands.h"
#include "player.h"
#include "enemy.h"


//randomly generate number of islands to land on
//Return the number of islands
int generateAmountOfIslands();

void startGame();
int selectIsland(int maxIslandNum, Player &mc);
void goToIslandInstance(Islands selectedIslands, Player& mc, bool *gameEnd);
void combatInstance(Islands selectedIsland, Player& mc, bool *gameEnd);
void playerTurn(Enemy* enemy, Player& mc, int numOfEnemies, bool* escape);
void enemyTurn(Enemy* enemy, Player& mc, int numOfEnemies);
void playerAttackLogic(int numOfEnemies, Enemy* enemy, Player mc);
void shopInstance(Islands selectedIsland, Player& mc, bool* gameEnd);
int checkNumOfDeadEnemies(Enemy* enemy, int numOfEnemies);
