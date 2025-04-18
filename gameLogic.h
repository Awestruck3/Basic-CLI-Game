#include "player.h"
#include "enemy.h"
#include "islands.h"
//randomly generate number of islands to land on
//Return the number of islands
int generateAmountOfIslands();

void startGame();
int selectIsland(int maxIslandNum, Player &mc);
int selectionFunction(Player mc, int low, int high);
Islands* displayIslands(int numUpcomingIslands);
void goToIslandInstance(Islands selectedIslands, Player& mc, bool *gameEnd);
void combatInstance(Islands selectedIsland, Player& mc, bool *gameEnd, int level = 0, int override = 0);
void playerTurn(iEnemy* enemy[], Player& mc, int numOfEnemies, bool* escape);
void enemyTurn(iEnemy* enemy[], Player& mc, int numOfEnemies);
void playerAttackLogic(int numOfEnemies, iEnemy* enemy[], Player mc);
void shopInstance(Islands selectedIsland, Player& mc, bool* gameEnd);
void itemInstance(Islands selectedIsland, Player& mc, bool* gameEnd);
int checkNumOfDeadEnemies(iEnemy* enemy[], int numOfEnemies);