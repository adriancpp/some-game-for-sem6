//
//  entity.hpp
//  SDLBruh
//
//  Created by Adrian Witkowski on 11/05/2023.
//

#ifndef entity_hpp
#define entity_hpp

#include <iostream>
#include <tuple>
#include <memory>
#include <vector>
#include <string>
#include <SDL2/SDL.h>

class Entity
{
public:
    Entity();
    bool isCollision( SDL_Rect newCoordinates, std::vector<std::vector<std::string>> collisionMap );
    void move();
    
public:
    int x, y, w, h;
    int speed;
    enum entityTypes
    {
        GRAPHIC = 0,
        COLLISION = 1,
        OBJECT = 2
    };
    entityTypes entityType;
    std::string entityModel;
    SDL_Rect rectFrom;
    
};

#endif /* entity_hpp */
