//
//  map.hpp
//  SDLBruh
//
//  Created by Adrian Witkowski on 20/05/2023.
//

#ifndef map_hpp
#define map_hpp

#include <iostream>
#include <tuple>
#include <memory>
#include <vector>
#include <string>
#include <SDL2/SDL.h>

class Map
{
public:
    
    std::vector<std::vector<std::string>> tileMapGraphic{
            {" ", " "," ", " "," ", " "," ", " "," ", " "},
            {" ", " "," ", " "," ", " "," ", " "," ", " "},
            {" ", " "," ", " "," ", " "," ", " "," ", " "},
            {" ", " "," ", " "," ", " "," ", " "," ", " "},
            {" ", " "," ", " "," ", " "," ", " ","#", "#"},
            {"#", "W","#", "#","#", " "," ", "#","#", "M"},
            {"M", "M","M", "M","M", " ","#", "M","M", "M"},
            {" ", " ","M", " "," ", " "," ", " "," ", " "}
    };
};

#endif /* map_hpp */
