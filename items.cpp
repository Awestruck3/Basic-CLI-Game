#include <iostream>
#include <string>
#include "items.h"
#include "dice.h"

Item::Item(){
    name = "NULL";
    id = 0;
    rarity = 0;
    preItem = false;
    postItem = false;
    activeItem = false;
    outsideItem = false;
    fluteCharge = 0;
    //curActive = false;
}

Item::~Item(){
    name = "";
    id = 0;
    rarity = 0;
}

void Item::setRarity(){
    rarity = rollForRarity();
}


//Thi sets the internal item id which is rolled based on the rarity passed in
//10 common, 4 uncommon, 4 rare, 2 legendary
void Item::setIDAndName(int rarity){
    int item;
    if(rarity == 1){
        item = roll10()+1;
        switch(item){
            case 1:
                //Strength +2
                id = 1;
                name = "Sword"; //TODO Test
                preItem = true;
                break;
            case 2:
                //When defending strength increases by 4
                id = 2;
                name = "Shield"; //Works
                preItem = true;
                break;
            case 3:
                id = 3;
                //Randomly increases 2 stats by 1 level (this can be the same stat twice)
                name = "Book of Magic";
                //TODO Test to ensure it only works once. This SHOULD be the case
                break;
            case 4:
                id = 4;
                //Can be used three times to reroll islands
                name = "Flute";
                outsideItem = true; //Seemingly works
                fluteCharge = 3;
                break;
            case 5:
                id = 5;
                //Lower enemy strength by 3
                name = "Scary Mask"; //Seemingly fine
                preItem = true;
                break;
            case 6:
                id = 6;
                //First attack per fight is defended against
                name = "Teddy Bear"; //Working
                preItem = true;
                break;
            case 7:
                id = 7;
                //Give chance to enemy to miss attack
                name = "Pepper spray"; //TODO WIP
                preItem = true;
                break;
            case 8:
                id = 8;
                //Enemies take one damage at the end of every turn
                name = "Matches"; //TODO WIP
                postItem = true;
                break;
            case 9:
                id = 9;
                //Tigers and lions take +2 every attack
                name = "Whistle"; //TODO WIP
                preItem = true;
                break;
            case 10:
                id = 10;
                //Chance to heal 1hp between islands 
                name = "Fishing Rod"; //TODO WIP
                outsideItem = true;
                break;
            default:
                id = 666;
                name = "What";
                preItem = true;
                postItem = true;
                activeItem = true;
                outsideItem = true;
                break;
        }
    }
    else if(rarity == 2){
        item = roll4()+1;
        switch(item){
            case 1:
                id = 21;
                //All dice rolls in combat occur twice, giving player the better option
                name = "Dice"; //TODO WIP
                activeItem = true; 
                break;
            case 2:
                id = 22;
                //Heals 3 hp between islands, up to 5 if you have fishing rod
                name = "Cookbook"; //TODO WIP
                outsideItem = true;
                break;
            case 3:
                id = 23;
                //Defend +5 
                name = "Armour"; //TODO Test
                preItem = true;
                break;
            case 4:
                id = 24;
                //Thorns, 2 damage to enemy when attacked
                name = "Fire Potion"; //TODO WIP
                preItem = true;
                break;
            default:
                id = 666;
                name = "What";
                preItem = true;
                postItem = true;
                activeItem = true;
                outsideItem = true;
                break;
        }
    }
    else if(rarity == 3){
        item = roll4()+1;
        switch(item){
            case 1:
                id = 31;
                //Player attacks twice per turn
                name = "Claws"; //TODO WIP
                preItem = true;
                break;
            case 2:
                id = 32;
                //Randomly activates an item twice
                name = "Question Mark"; //TODO WIP
                preItem = true;
                postItem = true;
                activeItem = true;
                outsideItem = true;
                break;
            case 3:
                id = 33;
                //Ten damage defence
                name = "Barrier"; //TODO Test
                preItem = true;
                break;
            case 4:
                id = 34;
                //Incerase luck by 10 (Also I should include luck elements maybe)
                name = "Clover";
                outsideItem = true; //TODO WIP
                break;
            default:
                id = 666;
                name = "What";
                preItem = true;
                postItem = true;
                activeItem = true;
                outsideItem = true;
                break;
        }
    }
    else if(rarity == 4){
        item = roll5050()+1;
        switch(item){
            case 1:
                id = 41;
                //Increase strength by 1 point per island
                name = "Barbell"; //TODO WIP
                outsideItem = true;
                break;
            case 2:
                id = 42;
                //Shoots for 50 damage. Once per turn
                name = "Gun"; //TODO Test
                preItem = true;
                break;
            default:
                id = 666;
                name = "What";
                preItem = true;
                postItem = true;
                activeItem = true;
                outsideItem = true;
                break;
        }
    }
    else{
        id = 666;
        name = "What";
    }
}

void Item::display() const{
    std::cout << " " << name << std::endl;
}

void Item::generateItem(){
    setRarity();
    setIDAndName(rarity);
}

int Item::getId(){
    return id;
}

std::string Item::getName(){
    return name;
}

bool Item::getPreItem(){
    return preItem;
}

bool Item::getPostItem(){
    return postItem;
}

bool Item::getActiveItem(){
    return activeItem;
}

bool Item::getOutsideItem(){
    return outsideItem;
}

int Item::getFluteCharge(){
    return fluteCharge;
}

void Item::setFluteCharge(int decreaseAmount){
    fluteCharge -= decreaseAmount;
}