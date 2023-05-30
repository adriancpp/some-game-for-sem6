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
    this->rectFrom = {0,0,0,0};
}

bool Entity::isCollision( SDL_Rect cord1, SDL_Rect cord2 )
{
    bool collision = false;
    
    float r1x = cord1.x;
    float r1y = cord1.y;
    float r1w = cord1.w;
    float r1h = cord1.h;
    
    float r2x = cord2.x;
    float r2y = cord2.y;
    float r2w = cord2.w;
    float r2h = cord2.h;
    
    if (r1x + r1w >= r2x &&
          r1x <= r2x + r2w &&
          r1y + r1h >= r2y &&
          r1y <= r2y + r2h)
    {
        collision = true;
    }

    return collision;
}


Entity Entity::move(int x, int y)
{
    this->x += x;
    this->y += y;
    
    return *this;
}

void Entity::render(std::shared_ptr<SDL_Renderer> *renderer_p)
{
    if(this->entityModel == "player")
    {
        if(this->faceRight == true)
            SDL_RenderCopyEx(renderer_p->get(), this->mainTexture.get(), nullptr, &this->cord, 0, NULL, SDL_FLIP_NONE);
        else
            SDL_RenderCopyEx(renderer_p->get(), this->mainTexture.get(), nullptr, &this->cord, 0, NULL, SDL_FLIP_HORIZONTAL);
    }
    else
    {
        if(SDL_RectEmpty(&this->rectFrom))
            SDL_RenderCopyEx(renderer_p->get(), this->mainTexture.get(), nullptr, &this->cord, 0, NULL, SDL_FLIP_NONE);
        else
            SDL_RenderCopyEx(renderer_p->get(), this->mainTexture.get(), &this->rectFrom, &this->cord, 0, NULL, SDL_FLIP_NONE);
    }
}

