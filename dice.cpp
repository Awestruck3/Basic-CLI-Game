#include "dice.h"
#include <random>


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

int roll100(){
    return rand()%100;
}

int rollForRarity(){
    //Good spot to start learning random distribution
    int fullRoll = roll100()+1;
    if(fullRoll <= 90){
        return 1;
    }
    else if(fullRoll > 90 && fullRoll <= 95){
        return 2;
    }
    else if(fullRoll > 95 && fullRoll <=98){
        return 3;
    }
    else if(fullRoll > 98){
        return 4;
    }
    else{
     return 0;
    }
}