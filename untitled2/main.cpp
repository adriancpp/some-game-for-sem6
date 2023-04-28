#include "head.hpp"

Texture Game::texturen;

int main( )
{
    srand( time( NULL ) );
	//Start up SDL and create window
	if( !Game::init() )
	{
		SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error", "Initialize error", NULL );
	}
	else
	{
		//Load media
		if( !Game::loadMedia() )
		{
			SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error", "Failed to load media!", NULL );
		}
		else
        {
            SDL_Event event;

            Element eHero( &Game::texturen, 120, 140, 40, 40, 40, 40, 10 );

            while( true )
            {
                // <--- tu start fps
                //keystate = SDL_GetKeyboardState( NULL );

                while( SDL_PollEvent( &event ))
                {
                    if( event.type == SDL_QUIT )
                    {
                        exit( 0 );
                    }
                    eHero.handleEvent( event );
                }

                {//events by player

                }

                {//events by period time

                }

                {//ai events

                }

                {//control

                }

                {//physic

                }

                {//render

                    SDL_RenderClear( Game::renderer );

                    {//background

                    }

                    {//map
                        eHero.render();
                    }

                    {//player

                    }

                    {//enemy

                    }

                    {//items

                    }

                    {//texts

                    }

                    {//menu

                    }

                    SDL_RenderPresent( Game::renderer );
                }

                SDL_Delay(20);
                // <--- tu koniec fps
            }
        }
	}
	//Free resources and close SDL
	Game::close();

	return 0;
}
