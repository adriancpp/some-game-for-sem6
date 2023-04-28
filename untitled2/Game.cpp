#include "head.hpp"

SDL_Window *Game::window;
SDL_Renderer *Game::renderer;

bool Game::init()
{
	bool success = true;
	string error = "";

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
	    error = "SDL could not initialize! SDL Error: \n" + string( SDL_GetError() );
		SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error", error.c_str(), NULL );
		success = false;
	}
	else
	{
		window = SDL_CreateWindow( GAME_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

		if( window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			if( renderer == NULL )
			{
				error = "Renderer could not be created! SDL Error: \n" + string( SDL_GetError() );
                SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error", error.c_str(), NULL );
                success = false;
			}
		}
	}

	return success;
}

bool Game::loadMedia()
{
	bool success = true;
    if( !texturen.loadFromFile( "../bitmap/texture.bmp" ) )
	{
		printf( "Failed to load 1/1 texture!\n" );
		success = false;
	}

	return success;
}

void Game::close()
{
    texturen.free();
	//Destroy window
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
