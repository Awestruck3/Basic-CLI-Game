#include <iostream>
#include <ctime>
#include "dice.h"
#include "player.h"
#include "gameLogic.h"
#include "islands.h"
#include "enemy.h"

using namespace std;

#define SEED 45678

int main(){
    srand(SEED);
    startGame();
    
}
