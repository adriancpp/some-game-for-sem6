#ifndef Game_hpp
#define Game_hpp

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"
#include <sstream>
#include <time.h>
#include "AEW_Tools.cpp"

#include <iostream>
#include <typeinfo>

using namespace std;

const string GAME_NAME = "AitM 3 Return";
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Texture
{
    private:
        SDL_Texture* texture;

		int width;
		int height;

    public:
        Texture( string path = "" );
		~Texture();

		bool loadFromFile( string path );

		void free();
		void render( int x, int y, int bx, int by, int bw, int bh );

		int getWidth();
		int getHeight();
};

class Game
{
    public:		//some variables
        static SDL_Window* window;
        static SDL_Renderer* renderer;

        static Texture texturen;

    public:
        static bool init();		//main init function
        static bool loadMedia();	//main loop function
        static void close();    //main close functio
};

class Element
{
    private:
        int vel;

    public:
        int posX, posY;
        int texturePosX, texturePosY;
        int width, height;
        Texture texture;

    public:
        Element( Texture *texture, int ZposX = 0, int ZposY = 0, int ZtexturePosX = 0, int ZtexturePosY = 0, int Zwidth = 0, int Zheight = 0, int Zvel = 0 );

        void handleEvent( SDL_Event& e );
        void changePosition();
        void render();
};

class Building : public Element
{
    int hp;
};

class Unit : public Element
{
    int damage;
};

class Map
{
    public:
        //vector<>Map[][];
};

#endif
