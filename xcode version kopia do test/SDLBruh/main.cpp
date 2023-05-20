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

        // rows: 10, cols: 5
        std::vector<std::vector<std::string>> tileMapGraphic{
                {" ", " "," ", " "," ", " "," ", " "," ", " "},
                {" ", " "," ", " "," ", " "," ", " "," ", " "},
                {" ", " "," ", " "," ", " "," ", " "," ", " "},
                {" ", " "," ", " "," ", " "," ", " "," ", " "},
                {" ", " "," ", " "," ", " "," ", " ","#", "#"},
                {"#", "W","#", "#","#", " "," ", "#","#", "M"},
                {"M", "M","M", "M","M", " ","#", "M","M", "M"},
                {" ", " "," ", " "," ", " "," ", " "," ", " "}
        };

        std::vector<std::vector<std::string>> tileMapCollision{
                {" ", " "," ", " "," ", " "," ", " "," ", " "},
                {" ", " "," ", " "," ", " "," ", " "," ", " "},
                {" ", " "," ", " "," ", " "," ", " "," ", " "},
                {" ", " "," ", " "," ", " "," ", " "," ", " "},
                {" ", " "," ", " "," ", " "," ", " ","#", "#"},
                {"#", "#","#", "#","#", " "," ", "#","#", "#"},
                {"#", "#","#", "#","#", " ","#", "#","#", "#"},
                {" ", " "," ", " "," ", " "," ", " "," ", " "}
        };

        std::vector<std::vector<std::string>> tileMapObject{
                {" ", " "," ", " "," ", " "," ", " "," ", " "},
                {" ", " "," ", " "," ", " "," ", " "," ", " "},
                {" ", " "," ", " "," ", " "," ", " "," ", " "},
                {" ", "P"," ", " "," ", " "," ", " "," ", "o"},
                {" ", " ","o", "o"," ", " "," ", " "," ", " "},
                {" ", " "," ", " "," ", " "," ", " "," ", " "},
                {" ", " "," ", " "," ", " "," ", " "," ", " "},
                {" ", " "," ", " "," ", " "," ", " "," ", " "}
        };


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

        auto prev_tick = SDL_GetTicks();
        int frame_dropped = 0;
    
        SDL_Event e;
    auto *key_state = SDL_GetKeyboardState(nullptr);
    bool gaming = true;
    
    
    int deltaTime =0;
    float deltaTimeTest = 0;
    
    //fun
    bool gemGravity = false;
    int collectedGems = 0;
    Uint32 lastUpdate = SDL_GetTicks();
    
    // test AAA.01 !!!==============
    int poczatek;
        int koniec;
        int roznica;
        float delay;
        static const int klatka = 0;
        static const int fps = 60;
    
    
    int klatkaIn = 0;
    float velY = 0;
    //==================================
    
    
    
    
        while (gaming)
        {
            poczatek = SDL_GetTicks(); //test AAA.01
            klatkaIn++; //test AAA.01
            
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
            
            //======================================

            if(key_state[SDL_SCANCODE_UP])
            {
                //elementListObjects[playerId].cord.y -= 10;
                if( elementListObjects[playerId].isFalling == false )
                {
                    elementListObjects[playerId].isRising = true;
                }
            }
            else
            {
                
            }
//            if(key_state[SDL_SCANCODE_DOWN])
//            {
//                elementListObjects[playerId].cord.y += 10;
//            }
            if(key_state[SDL_SCANCODE_LEFT])
            {
                if( velY > -5 )
                {
                    velY = velY - 0.6;
                }
            }
            velY = velY * 0.45; //0.95
                
            if(key_state[SDL_SCANCODE_RIGHT])
            {
                std::cout << elementListObjects[playerId].x << std::endl;
                elementListObjects[playerId].isMovingRight = true;
            }
                
            else
                elementListObjects[playerId].isMovingRight = false;
            
            elementListObjects[playerId].cord.x = elementListObjects[playerId].cord.x + velY*10;

                //physic
                {
                    
                    
                
                    Uint32 current = SDL_GetTicks();
                    float dT = (current - lastUpdate) / 1000.0f;
                    //object moveing
                    if(elementListObjects[playerId].isMovingRight)
                    {
                        //int s = deltaTime*0.2;
                        
                        const float PLAYER_VELOCITY = 200.0f;
                        float distanceToMove = PLAYER_VELOCITY * dT;
                            
                        elementListObjects[playerId].faceRight = true;
                        elementListObjects[playerId].cord.x += static_cast<int>(distanceToMove);
                    }
                    if(elementListObjects[playerId].isMovingLeft)
                    {
                        int s = deltaTime*0.2;
                        
                        elementListObjects[playerId].faceRight = false;
                        elementListObjects[playerId].cord.x -= s;
                    }
                    lastUpdate = current;
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

                        }
                    }
        

                }

                SDL_RenderPresent(renderer_p.get());
            
            
            koniec = SDL_GetTicks();
            roznica = koniec - poczatek;
            delay = ( 1000.0 /(float)fps) - roznica;
            if( delay > 0 )
            {
                SDL_Delay( delay );
            }
            
            
        }

        SDL_Quit();
        return 0;
    }