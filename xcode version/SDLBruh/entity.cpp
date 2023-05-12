//
//  entity.cpp
//  SDLBruh
//
//  Created by Adrian Witkowski on 11/05/2023.
//

#include "entity.hpp"


// 1. clikc right
    // 2. check if moving will not collide with eny element in map
        // 3. if no collision then make move
Entity::Entity()
{
    
}

bool Entity::isCollision( SDL_Rect newCoordinates, std::vector<std::vector<std::string>> collisionMap )
{
    bool collision = false;
    
    float r1x = newCoordinates.x;
    float r1y = newCoordinates.y;
    float r1w = newCoordinates.w;
    float r1h = newCoordinates.h;
    
    for(int row = 0; row < collisionMap.size() ; row++)
    {
        for(int column = 0; column < collisionMap[row].size() ; column++)
        {
            float r2x = row*64;
            float r2y = column*64;
            float r2w = 64;
            float r2h = 64;
            
            if (r1x + r1w >= r2x &&
                  r1x <= r2x + r2w &&
                  r1y + r1h >= r2y &&
                  r1y <= r2y + r2h)
            {
                collision = true;
                
                //check if there is object like coin???
            }
        }
    }

    return collision;
}


Entity Entity::move(int x, int y)
{
    this->x += x;
    this->y += y;
    
    return *this;
}

// Getter for x
    int Entity::getX() const {
        return x;
    }

    // Setter for x
    void Entity::setX(int newX) {
        this->x = newX;
    }
