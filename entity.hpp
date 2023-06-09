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
#include "SDL.h"

class Entity
{
public:
    Entity();
    bool isCollision( SDL_Rect cord1, SDL_Rect cord2 );
    Entity move(int x, int y);

public:
    int id;

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
    SDL_Rect cord;

    //physic
    bool isFalling;
    bool isRising;
    bool isMovingRight;
    bool isMovingLeft;
    int maxJumpHeight;
    int currentJumpHeigth;

    //texture
    bool faceRight;


    int getX() const;
    void setX(int newX);
};
#endif /* entity_hpp */
