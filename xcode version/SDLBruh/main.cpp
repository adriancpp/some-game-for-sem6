//
//  main.cpp
//  SDLBruh
//
//  Created by Adrian Witkowski on 09/05/2023.
//

#include <stdio.h>
// Author: Joshua Rose
// Date Created: 9/11/22
//
// This is some starter code to get your project going. I found SDL setup on Mac to be needlessly frustrating so I hope this helps.
// If you enjoy it please consider subscribing to my YouTube channel: @jrose.me
//
// I coded this and got it working on  MacOS Monterey 12.4, using SDL 2.24.0 and compiled with Clang++

#include <iostream>
#include <tuple>
#include <memory>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "entity.hpp"
#include "map.hpp"

std::pair<std::shared_ptr<SDL_Window>,std::shared_ptr<SDL_Renderer>> create_context()
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_CreateWindowAndRenderer(640,480,SDL_WINDOW_SHOWN, &window, &renderer);

    std::shared_ptr<SDL_Window> w (window, [](SDL_Window *window){
        std::cout << "Destroy window" << std::endl;
        SDL_DestroyWindow(window);
    });

    std::shared_ptr<SDL_Renderer> r (renderer, [](SDL_Renderer *renderer) {
        std::cout << "Destroy renderer" << std::endl;
        SDL_DestroyRenderer(renderer);
    });

    return {w,r};
}

std::shared_ptr<SDL_Texture> load_texture(std::shared_ptr<SDL_Renderer> renderer,std::string texture_name)
{
    std::cout << "path: " << SDL_GetBasePath() << std::endl;
    
    
    auto surface = IMG_Load(("" + texture_name).c_str());
    if(!surface)
    {
        throw std::invalid_argument(SDL_GetError());
    }

    SDL_SetColorKey(surface,SDL_TRUE, SDL_MapRGB(surface->format, 0x0ff,0x0,0x0ff));

    auto texture = SDL_CreateTextureFromSurface(renderer.get(), surface);
    if(!texture)
    {
        throw std::invalid_argument(SDL_GetError());
    }

    SDL_FreeSurface(surface);
    return std::shared_ptr<SDL_Texture>(texture, [](auto *p){ SDL_DestroyTexture(p);});
}

bool handle_events(Entity* entity){
    return false;
}

int main(int argc, char const *argv[])
{
    //init all
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL could not be initialized: " << SDL_GetError() << std::endl;
        return 1;
    }

    if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) )
    {
        std::cout << "SDL_image could not be initialized: "<< IMG_GetError( ) << std::endl;
        return 1;
    }

    auto [window_p, renderer_p] = create_context();
    //int gaming = true;

    auto player = load_texture(renderer_p, "Sprites/player/idle/player-idle-1.png");
    auto clouds = load_texture(renderer_p, "clouds.bmp");
    auto background = load_texture(renderer_p, "Environment/back.png");
    auto envirnomentTileset = load_texture(renderer_p, "Environment/Tileset/tileset-sliced.png");
    auto gem_Texture = load_texture(renderer_p, "Sprites/Items/gem/gem-1.png");

    SDL_Rect rect = {10, 10, 100, 100};


        //game part -- move it to other file in future
        //map
    
    
    //load maps
    Map map1;
    std::vector<std::vector<std::string>> tileMapGraphic = map1.tileMapGraphic;
    std::vector<std::vector<std::string>> tileMapCollision = map1.tileMapCollision;
    std::vector<std::vector<std::string>> tileMapObject = map1.tileMapObject;

        //transformMapsIntoObjects

        std::vector<Entity> entities;

        int id = 0;

        for(int row = 0; row < tileMapGraphic.size() ; row++)
        {
            for(int column = 0; column < tileMapGraphic[row].size() ; column++)
            {
                if(tileMapGraphic[row][column] == "#")
                {
                    Entity newEntity;
                    newEntity.id = id;
                    newEntity.x = column*64;
                    newEntity.y = row*64;
                    newEntity.w = 64;
                    newEntity.h = 64;
                    newEntity.entityType = Entity::GRAPHIC;
                    newEntity.entityModel = "tile0";
                    newEntity.rectFrom = {16, (368-16)-336, 16, 16 };
                    entities.push_back(newEntity);
                }
                else if(tileMapGraphic[row][column] == "W")
                {
                    Entity newEntity;
                    newEntity.id = id;
                    newEntity.x = column*64;
                    newEntity.y = row*64;
                    newEntity.w = 64;
                    newEntity.h = 64;
                    newEntity.entityType = Entity::GRAPHIC;
                    newEntity.entityModel = "tile1";
                    newEntity.rectFrom = {16+32, (368-16)-336, 16, 16 };
                    entities.push_back(newEntity);
                }
                else if(tileMapGraphic[row][column] == "M")
                {
                    Entity newEntity;
                    newEntity.id = id;
                    newEntity.x = column*64;
                    newEntity.y = row*64;
                    newEntity.w = 64;
                    newEntity.h = 64;
                    newEntity.entityType = Entity::GRAPHIC;
                    newEntity.entityModel = "tile2";
                    newEntity.rectFrom = {16, (368-16)-336+32, 16, 16 };
                    entities.push_back(newEntity);
                }
                id++;
            }
        }

        std::vector<Entity> elementListObjects;

        id = 0;

        int playerId = 0;

        for(int row = 0; row < tileMapObject.size() ; row++)
        {
            for(int column = 0; column < tileMapObject[row].size() ; column++)
            {

                if(tileMapObject[row][column] == "P")
                {
                    Entity newEntity;
                    newEntity.id = id;
                    newEntity.entityType = Entity::OBJECT;
                    newEntity.entityModel = "player";
                    newEntity.faceRight = true;
                    newEntity.isMovingLeft = false;
                    newEntity.isMovingRight = false;
                    newEntity.isFalling = true;
                    newEntity.isRising = true;
                    newEntity.maxJumpHeight = 100;
                    newEntity.currentJumpHeigth = 100;
                    newEntity.cord = {
                        column*64,
                        row*64,
                        33*2,
                        32*2
                    };
                    elementListObjects.emplace_back(newEntity);
                
                    
                    playerId = id;
                    id++;
                }
                if(tileMapObject[row][column] == "o")
                {
                    Entity newEntity;
                    newEntity.id = id;
                    newEntity.entityType = Entity::OBJECT;
                    newEntity.entityModel = "gem";
                    newEntity.cord = {
                        (column*64)+16,
                        (row*64)+16,
                        32,
                        32
                    };
                    elementListObjects.emplace_back(newEntity);
                
                    id++;
                }
                
            
            }
        }
    
    std::vector<Entity> elementListCollision;

    id = 0;

    for(int row = 0; row < tileMapCollision.size() ; row++)
    {
        for(int column = 0; column < tileMapCollision[row].size() ; column++)
        {
            if(tileMapCollision[row][column] == "#")
            {
                Entity newEntity;
                newEntity.id = id;
                newEntity.entityType = Entity::COLLISION;
                newEntity.cord = {
                    column*64,
                    row*64,
                    33*2,
                    32*2
                };
                elementListCollision.emplace_back(newEntity);

                id++;
            }
            
        
        }
    }
    
    elementListObjects[playerId].x = 20;

    
        SDL_Event e;
    auto *key_state = SDL_GetKeyboardState(nullptr);
    bool gaming = true;
    
    
    //fun
    bool gemGravity = false;
    int collectedGems = 0;
    
    //newTime
    static const int fps = 60;
    float delay;
    int prev_tick;
    int ticks;
    int deltaTime;
    //newPlayerVel
    float velY = 0;
    float velAddSpeed = 3;
    float velMaxSpeed = 10;
    float gForceSpeed = 1;

        while (gaming)
        {
            prev_tick = SDL_GetTicks();
            //*key_state = SDL_GetKeyboardState(nullptr);
            while (SDL_PollEvent(&e) != 0) {
                switch(e.type){
                    case SDL_QUIT:
                        std::cout << "Quit" << std::endl;
                        gaming = false;
                        break;
                    case SDL_KEYDOWN:
                        if(e.key.keysym.sym == SDLK_q)
                        {
                            std::cout << "lag......" << std::endl;
                            SDL_Delay(500);
                        }
                        else if(e.key.keysym.sym == SDLK_g)
                        {
                            if(gemGravity==false)
                                gemGravity=true;
                            else
                                gemGravity=false;
                        }

                }
            }
            
            //player entity

            if(key_state[SDL_SCANCODE_UP])
            {
                //elementListObjects[playerId].cord.y -= 10;
                if( elementListObjects[playerId].isFalling == false )
                {
                    elementListObjects[playerId].isRising = true;
                }
            }
            
            velMaxSpeed = 8;
            velAddSpeed = 2;
            
            if(key_state[SDL_SCANCODE_LEFT])
            {
                if( velY > -velMaxSpeed )
                {
                    velY = velY - velAddSpeed;
                }
                elementListObjects[playerId].faceRight = false;
            }
                
            if(key_state[SDL_SCANCODE_RIGHT])
            {
                if( velY < velMaxSpeed )
                {
                    velY = velY + velAddSpeed;
                    //velY = velY + 0.6;
                }
                elementListObjects[playerId].faceRight = true;
            }
            
            
            
            elementListObjects[playerId].cord.x += (int)velY;
            velY = velY * 0.65; //0.95
            //SDL_Delay(100);

                //physic
                {
                    
                    //player jumping
                    if(elementListObjects[playerId].isRising)
                    {
                        if(elementListObjects[playerId].currentJumpHeigth < elementListObjects[playerId].maxJumpHeight)
                        {
                        
                            elementListObjects[playerId].currentJumpHeigth+=10;
                            elementListObjects[playerId].cord.y-=10;
                        }
                        else
                        {
                            elementListObjects[playerId].isRising = false;
                            elementListObjects[playerId].isFalling = true;
                            elementListObjects[playerId].currentJumpHeigth=0;
                        }
                    }
                    
                    //objects gravity
                    for(int i = 0; i < elementListObjects.size() ; i++)
                    {
                        if(elementListObjects[i].entityType == Entity::OBJECT)
                        {
                            if(elementListObjects[i].entityModel == "player")
                            {
                                //if no collision in Y - move player down;
                                
                                bool playerBottomCollision = false;
                                
                                gForceSpeed+=0.45;
                                
                                SDL_Rect newCord = {
                                    elementListObjects[playerId].cord.x,
                                    elementListObjects[playerId].cord.y+(int)gForceSpeed,
                                    elementListObjects[playerId].cord.w,
                                    elementListObjects[playerId].cord.h
                                };
                                //check collisions
                                for(int j = 0; j < elementListCollision.size() ; j++)
                                {
                                    bool collision = elementListObjects[playerId].isCollision(newCord, elementListCollision[j].cord);
                                    if(collision)
                                    {
                                        playerBottomCollision = true;
                                    }
                                
                                }
                                
                                if(playerBottomCollision == false)
                                {
                                    //move player down
                                    elementListObjects[playerId].isFalling = true;
                                    elementListObjects[playerId].cord.y += (int)gForceSpeed;
                                }
                                else
                                {
                                    gForceSpeed = 1;
                                    elementListObjects[playerId].isFalling = false;
                                }
                                
                                
                                
                            }
                            if(elementListObjects[i].entityModel == "gem" && gemGravity == true)
                            {
                                bool playerBottomCollision = false;
                                
                                SDL_Rect newCord = {
                                    elementListObjects[i].cord.x,
                                    elementListObjects[i].cord.y+1,
                                    elementListObjects[i].cord.w,
                                    elementListObjects[i].cord.h
                                };
                                //check collisions
                                for(int j = 0; j < elementListCollision.size() ; j++)
                                {
                                    bool collision = elementListObjects[i].isCollision(newCord, elementListCollision[j].cord);
                                    if(collision)
                                    {
                                        playerBottomCollision = true;
                                    }
                                
                                }
                                
                                if(playerBottomCollision == false)
                                {
                                    //move player down
                                    elementListObjects[i].cord.y += 1;
                                }
                                
                                
                                
                            }
                        }
                    }
                    
//                    if(elementListObjects[playerId].isMovingLeft)
//                    {
//                        int s = deltaTime*0.2;
//
//                        elementListObjects[playerId].faceRight = false;
//                        elementListObjects[playerId].cord.x -= s;
//                    }
//                    lastUpdate = current;
                }
                
                //collisions with object
                {
                    for(int j = 0; j < elementListObjects.size() ; j++)
                    {
                        bool collision = elementListObjects[playerId].isCollision(elementListObjects[playerId].cord, elementListObjects[j].cord);
                        if(collision)
                        {
                            if(elementListObjects[j].entityModel == "gem")
                            {
                                collectedGems++;
                                elementListObjects.erase(elementListObjects.begin() + j);
                            }
                        }
                    
                    }
                }
                
                SDL_RenderCopy(renderer_p.get(), background.get(), nullptr, nullptr);

                {

                    int w,h;
                    SDL_QueryTexture(clouds.get(),
                                     NULL, NULL,
                                     &w, &h);

                    SDL_Rect clouds_rect = {rect.x/2 - 200, rect.y/2 -100,w,h };
                    SDL_RenderCopy(renderer_p.get(), clouds.get(), nullptr, &clouds_rect);

                    //middle
                    // tileset graph

                    for(int i = 0; i < entities.size() ; i++)
                    {
                        if(entities[i].entityType == Entity::GRAPHIC)
                        {
                            SDL_Rect envirnomentTileset_rect = {entities[i].x, entities[i].y,entities[i].w, entities[i].h };
                        

                            if(entities[i].entityModel == "tile0")
                            {
                                SDL_RenderCopy(renderer_p.get(), envirnomentTileset.get(), &entities[i].rectFrom, &envirnomentTileset_rect);
                            }
                            if(entities[i].entityModel == "tile1")
                            {
                                SDL_RenderCopy(renderer_p.get(), envirnomentTileset.get(), &entities[i].rectFrom, &envirnomentTileset_rect);
                            }
                            if(entities[i].entityModel == "tile2")
                            {
                                SDL_RenderCopy(renderer_p.get(), envirnomentTileset.get(), &entities[i].rectFrom, &envirnomentTileset_rect);
                            }
                        }
                    }

                    for(int i = 0; i < elementListObjects.size() ; i++)
                    {
                        if(elementListObjects[i].entityType == Entity::OBJECT)
                        {
                                
                            if(elementListObjects[i].entityModel == "player")
                            {
                                if(elementListObjects[i].faceRight == true)
                                {
                                    SDL_RendererFlip flipType = SDL_FLIP_NONE;
                                    SDL_RenderCopyEx(renderer_p.get(), player.get(), nullptr, &elementListObjects[i].cord, 0, NULL, flipType);
                                }
                                else
                                {
                                    SDL_RendererFlip flipType = SDL_FLIP_HORIZONTAL;
                                    SDL_RenderCopyEx(renderer_p.get(), player.get(), nullptr, &elementListObjects[i].cord, 0, NULL, flipType);
                                }
                            
                                
                            }
                            if(elementListObjects[i].entityModel == "gem")
                            {
                                SDL_RenderCopy(renderer_p.get(), gem_Texture.get(), nullptr, &elementListObjects[i].cord);
                            }

                        }
                    }
        

                }
                
                // gui
                {
                    for(int a = 0 ; a < collectedGems; a++)
                    {
                        SDL_Rect gemGuiRect;
                        gemGuiRect.x = 10+(26*a);
                        gemGuiRect.y = 450;
                        gemGuiRect.w = 28;
                        gemGuiRect.h = 28;
                        SDL_RenderCopy(renderer_p.get(), gem_Texture.get(), nullptr, &gemGuiRect);
                    }
                }

                SDL_RenderPresent(renderer_p.get());
            
            
            ticks = SDL_GetTicks();
            deltaTime = ticks - prev_tick;
            delay = ( 1000.0 /(float)fps) - deltaTime;
            if( delay > 0 )
                SDL_Delay( delay );
            
        }

        SDL_Quit();
        return 0;
    }
