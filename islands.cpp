#include "islands.h"
#include "dice.h"


Islands& Islands::setIslands(){
        typeOfIsland = roll4();
        islandTypeName = setTypeName(typeOfIsland);
        while(islandAttribute[0] == islandAttribute[1]){
            islandAttribute[0] = roll10();
            islandAttribute[1] = roll10();
        }
        islandAttributesNames[0] = setAttributes(islandAttribute[0]);
        islandAttributesNames[1] = setAttributes(islandAttribute[1]);
        return *this;
}

void Islands::display(){
    std::cout.width(13); 
    std::cout << std::left << islandTypeName << std::left << "Atrribute 1: " << std::left << islandAttributesNames[0] << std::left << " Attribute 2: " << std::left << islandAttributesNames[1] << std::endl;
}

std::string Islands::setTypeName(int typeName){
    std::string rc;
    //0 = combat
    if(typeName == 0){
        return rc = "Combat";
    }
    //1 = shop
    else if(typeName == 1){
        return rc = "Shop";
    }
    //2 = item room
    else if(typeName == 2){
        return rc = "Item Room";
    }
    //3 = harder enemy
    else if(typeName == 3){
        return rc = "Hard Enemy";
    }
    //4 = Boss (can't be rolled randomly)
    else if(typeName == 4){
        return rc = "Boss";
    }
    else{
        return rc = "What";
    }
}

std::string Islands::setAttributes(int attribute){
    std::string rc;
    //0 = Sunny: Positive effects are doubled
    if(attribute == 0){
        return rc = "Sunny";
    }
    //1 = Rainy: Negative effects are doubled
    else if(attribute == 1){
        return rc = "Rainy";
    }
    //2 = Snowy: Do not heal after leaing island
    else if(attribute == 2){
        return rc = "Snowy";
    }
    //3 = Sandy: Chance to find buried trasure, or fake treasure/combat
    else if(attribute == 3){
        return rc = "Sandy";
    }
    //4 = Rocky: Lose strength upon arrival to island
    else if(attribute == 4){
        return rc = "Rocky";
    }
    //5 = Haunted: Special spectral enemies appear. Chance to find haunted treasure
    else if(attribute == 5){
        return rc = "Haunted";
    }
    //6 = Jungle: Risk of contact illness upon arrival - illness can carry bad effects forward
    else if(attribute == 6){
        return rc = "Jungle";
    }
    //7-9 = Normal
    else if(attribute>=7){
        return rc = "Normal";
    }
    else{
        return rc = "fug"; 
    }
}

std::string Islands::getIslandType() const{
    return islandTypeName;
}

