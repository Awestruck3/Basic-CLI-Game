#include "dice.h"

//REMINDER FOR USING DICE
//ALL DICE WILL BE 0-ONE BELOW INTENDED TOP DIGIT. EG. ON D6 IT ROLLS 0-5

//50/50 dice
int roll5050(){
    return rand()%2;
}

//4 sided dice
int roll4(){
    return rand()%4;
}

//6 sided dice
int roll6(){
    return rand()%6;
}

//10 sided dice
int roll10(){
    return rand()%10;
}

int roll20(){
    return rand()%20;
}