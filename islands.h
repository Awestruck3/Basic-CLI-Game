#pragma once
#include <iostream>
#include <string>

class Islands{
    

        
        //What properties do Islands need?

        //Type of island needs to be  
        //0 = combat
        //1 = shop
        //2 = item room
        //3 = harder enemy
        //4 = Boss (can't be rolled randomly)
        int typeOfIsland;

        //Islands have attributes with different effects
        //0 = Sunny: Positive effects are doubled
        //1 = Rainy: Negative effects are doubled
        //2 = Snowy: Do not heal after leaing island
        //3 = Sandy: Chance to find buried trasure, or fake treasure/combat
        //4 = Rocky: Lose strength upon arrival to island
        //5 = Haunted: Special spectral enemies appear. Chance to find haunted treasure
        //6 = Jungle: Risk of contact illness upon arrival - illness can carry bad effects forward
        //7-9 = Normal
        int islandAttribute[2];

        std::string islandTypeName;
        std::string islandAttributesNames[2];
    
        public:
            //Default constructor
            Islands(){
                typeOfIsland = 0;
                islandAttribute[0] = 0;
                islandAttribute[1] = 0;
            }
        
            //One arg constructor, use for bosses
            Islands(int b){
                typeOfIsland = b;
                islandAttribute[0] = 0;
                islandAttribute[1] = 0;
            }
        
            ~Islands(){
                typeOfIsland = 0;
                islandAttribute[0] = 0;
                islandAttribute[1] = 0;
            }
            Islands& setIslands();
            void display();
            std::string setTypeName(int typeName);
            std::string setAttributes(int attribute);
            std::string getIslandType() const;
};