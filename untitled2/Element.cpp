#include "head.hpp"

Element::Element( Texture* texture, int ZposX, int ZposY, int ZtexturePosX, int ZtexturePosY, int Zwidth, int Zheight, int Zvel )
{
    this->texture = *texture;
    //Initialize the offsets
    posX = ZposX;
    posY = ZposY;

    texturePosX = ZtexturePosX;
    texturePosY = ZtexturePosY;

    width = Zwidth;
    height = Zheight;

    //Initialize the velocity
    vel = Zvel;
}

void Element::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
                {

                } break;
            case SDLK_DOWN:
                {

                } break;
            case SDLK_LEFT:
                {

                } break;
            case SDLK_RIGHT:
                {

                } break;
            case SDLK_x:
                {

                } break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
                {
                    posX+=1;
                    cout << posX << endl;
                } break;
            case SDLK_DOWN:
                {

                } break;
            case SDLK_LEFT:
                {

                } break;
            case SDLK_RIGHT:
                {

                } break;
            case SDLK_x:
                {

                } break;
        }
    }
}

/*                        ///                   CHYBA TUTAJ MUSZE DAC W PARAMETRZE KIERUNEK, EWENTUALNIE W OSOBNEJ FUNKCJI USTAWIAC KIERUNEK
void Element::changePosition()
{
    //Move the dot left or right
    posX += vel;

    //If the dot went too far to the left or right
    if( ( posX < 0 ) || ( posX + DOT_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        posX -= vel;
    }

    //Move the dot up or down
    posY += mVelY;

    //If the dot went too far up or down
    //if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) )
    if( ( mPosY < 280 ) || ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        mPosY -= mVelY;
    }
}
*/
void Element::render()
{
    texture.render( posX, posY,texturePosX,texturePosY,width,height );
}
