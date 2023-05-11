
#define SDL_MAIN_HANDLED




#include <iostream>
#include <tuple>
#include <memory>
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
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


    auto surface = IMG_Load(("assets/" + texture_name).c_str());
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

bool handle_events(SDL_Rect &rect){
    SDL_Event e;
    auto *key_state = SDL_GetKeyboardState(nullptr);

    while (SDL_PollEvent(&e) != 0) {
        switch(e.type){
            case SDL_QUIT:
                std::cout << "Quit" << std::endl;
                return false;
            case SDL_KEYDOWN:
                if(e.key.keysym.sym == SDLK_q)
                {
                    std::cout << "lag......" << std::endl;
                    SDL_Delay(500);
                }

        }
    }

    if(key_state[SDL_SCANCODE_UP]) rect.y--;
    if(key_state[SDL_SCANCODE_DOWN]) rect.y++;
    if(key_state[SDL_SCANCODE_LEFT]) rect.x--;
    if(key_state[SDL_SCANCODE_RIGHT]) rect.x++;

    return true;
}

int main(int argc, char const *argv[])
{
    std::cout << "Dupa" << std::endl;
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
            {"#", "W","#", "#","#", " ","#", "#","#", "M"},
            {"M", "M","M", "M","M", " ","M", "M","M", "M"},
            {" ", " "," ", " "," ", " "," ", " "," ", " "}
    };

    std::vector<std::vector<std::string>> tileMapCollision{
            {" ", " "," ", " "," ", " "," ", " "," ", " "},
            {" ", " "," ", " "," ", " "," ", " "," ", " "},
            {" ", " "," ", " "," ", " "," ", " "," ", " "},
            {" ", " "," ", " "," ", " "," ", " "," ", " "},
            {" ", " "," ", " "," ", " "," ", " "," ", " "},
            {"#", "#","#", "#","#", " "," ", " "," ", " "},
            {" ", " "," ", " "," ", " "," ", " "," ", " "},
            {" ", " "," ", " "," ", " "," ", " "," ", " "}
    };

    std::vector<std::vector<std::string>> tileMapObject{
            {" ", " "," ", " "," ", " "," ", " "," ", " "},
            {" ", " "," ", " "," ", " "," ", " "," ", " "},
            {" ", " "," ", " "," ", " "," ", " "," ", " "},
            {" ", " "," ", " "," ", " "," ", " "," ", " "},
            {" ", "P","o", "o"," ", " "," ", " "," ", " "},
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
            id++;

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
        }
    }

    std::vector<Entity> elementListObjects;

    id = 0;

    for(int row = 0; row < tileMapObject.size() ; row++)
    {
        for(int column = 0; column < tileMapObject[row].size() ; column++)
        {
            id++;

            if(tileMapObject[row][column] == "P")
            {
                Entity newEntity;
                newEntity.id = id;
                newEntity.x = column*64;
                newEntity.y = row*64;
                newEntity.w = 33*2;
                newEntity.h = 32*2;
                newEntity.entityType = Entity::OBJECT;
                newEntity.entityModel = "player";
                elementListObjects.push_back(newEntity);
            }
        }
    }

    auto prev_tick = SDL_GetTicks();
    int frame_dropped = 0;
    while (handle_events(rect)) {

        if(!frame_dropped)
        {
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
                        SDL_Rect player_rect = {elementListObjects[i].x, elementListObjects[i].y,elementListObjects[i].w, elementListObjects[i].h };

                        if(elementListObjects[i].entityModel == "player")
                        {
                            SDL_RenderCopy(renderer_p.get(), player.get(), nullptr, &player_rect);
                        }
                    }
                }

            }



            SDL_SetRenderDrawColor(renderer_p.get(), 255, 100, 50, 255);

            SDL_RenderFillRect(renderer_p.get(), &rect);
            SDL_RenderPresent(renderer_p.get());
        }

        auto ticks = SDL_GetTicks();
        if ((ticks - prev_tick) < 33)
        {
            SDL_Delay(33 - (ticks - prev_tick));
            frame_dropped = 0;
        }
        else{
            prev_tick += 33;
        }
    }

    SDL_Quit();
    return 0;
}
