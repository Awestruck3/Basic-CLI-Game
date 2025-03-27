#include <iostream>
#include <ctime>
#include "dice.h"
#include "player.h"
#include "gameLogic.h"
#include "islands.h"
#include "enemy.h"

using namespace std;

#define SEED 45678 //After updating logic, SEED generates 2 hard enemies that CAN be taken down by just attacking
//SEED2 currently guarantees a 2 enemy spawn on first combat
#define SEED2 123456


int main(){
    srand(SEED2);
    startGame();
    return 0;
}
