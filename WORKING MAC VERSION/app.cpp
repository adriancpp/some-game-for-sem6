#include <iostream>
#include "vector"
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <tuple>
#include <memory>

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
    auto surface = SDL_LoadBMP(("assets/" + texture_name).c_str());
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

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    {
        auto [window_p, renderer_p] = create_context();
        int gaming = true;

        auto clouds = load_texture(renderer_p, "clouds.bmp");
        auto background = load_texture(renderer_p, "background.bmp");


        SDL_Rect rect = {10, 10, 300, 100};

        auto prev_tick = SDL_GetTicks();
        int frame_dropped = 0;
        while (handle_events(rect)) {

            if(!frame_dropped)
            {

                //SDL_SetRenderDrawColor(renderer_p.get(), 0, 0, 0, 255);
                //SDL_RenderClear(renderer_p.get());

                SDL_RenderCopy(renderer_p.get(), background.get(), nullptr, nullptr);

                {

                    int w,h;
                    SDL_QueryTexture(clouds.get(),
                                     NULL, NULL,
                                     &w, &h);

                    SDL_Rect clouds_rect = {rect.x/2 - 200, rect.y/2 -100,w,h };
                    SDL_RenderCopy(renderer_p.get(), clouds.get(), nullptr, &clouds_rect);
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
    }

    SDL_Quit();
    return 0;
}