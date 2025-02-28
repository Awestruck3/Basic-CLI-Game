#include <iostream>
#include <ctime>
#include "dice.h"
#include "player.h"
#include "gameLogic.h"
#include "islands.h"
#include "enemy.h"

using namespace std;

#define SEED 45678
//SEED2 currently guarantees a 2 enemy spawn on first combat
#define SEED2 123456

int main(){
    srand(SEED);
    startGame();
    return 0;
}
