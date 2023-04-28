#include "head.hpp"

Texture::Texture( string path )
{
    if( path.empty() )
    {
        texture = NULL;
    }
	else
    {
        loadFromFile( path );
    }
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	//Deallocate
	free();
}

bool Texture::loadFromFile( string path )
{
	//Get rid of preexisting texture
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( Game::renderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	texture = newTexture;
	return texture != NULL;
}

void Texture::free()
{
	//Free texture if it exists
	if( texture != NULL )
	{
		SDL_DestroyTexture( texture );
		texture = NULL;
		width = 0;
		height = 0;
	}
}

void Texture::render( int bx, int by, int x, int y, int bw, int bh )
{
    SDL_Rect srcrect, dstrect;
    srcrect.x = x;
    srcrect.y = y;
    srcrect.w = bw;
    srcrect.h = bh;
    dstrect.x = bx;
    dstrect.y = by;
    dstrect.w = bw;
    dstrect.h = bh;
    SDL_RenderCopy( Game::renderer, texture, &srcrect, &dstrect );
}

int Texture::getWidth()
{
	return width;
}

int Texture::getHeight()
{
	return height;
}
/*
void Texture::renderMap()
{
    for( int a = 0 ; a < allElements ; a++ )
    {
        if( element[a].rodzaj == "mur" )
        {
            drawBmp( imageSurface, element[a].x, element[a].y, wymiaryKafelki * 1, wymiaryKafelki * 0, wymiaryKafelki, wymiaryKafelki );
        }
        else if( element[a].rodzaj == "trawa" )
        {
            drawBmp( imageSurface, element[a].x, element[a].y, wymiaryKafelki * 1, wymiaryKafelki * 2, wymiaryKafelki, wymiaryKafelki );
        }
        else if( element[a].rodzaj == "pusto" )
        {
            drawRect( element[a].x, element[a].y, wymiaryKafelki, wymiaryKafelki, 0x00, 0x00, 0x00);
        }
    }
    for( int a = 0 ; a < allElements ; a++ )
    {
        if( element[a].rodzaj == "moneta" )
        {
            drawBmp( imageSurface, element[a].x, element[a].y, wymiaryKafelki * 2, wymiaryKafelki * 1, wymiaryKafelki, wymiaryKafelki );
        }
        else if( element[a].rodzaj == "klucz" )
        {
            drawBmp( imageSurface, element[a].x, element[a].y, wymiaryKafelki * 0, wymiaryKafelki * 1, wymiaryKafelki, wymiaryKafelki );
        }
        else if( element[a].rodzaj == "kluczEnd" )
        {
            drawBmp( imageSurface, element[a].x, element[a].y, wymiaryKafelki * 2, wymiaryKafelki * 3, wymiaryKafelki, wymiaryKafelki );
        }
        else if( element[a].rodzaj == "domek" )
        {
            drawBmp( imageSurface, element[a].x, element[a].y, wymiaryKafelki * 2, wymiaryKafelki * 0, wymiaryKafelki, wymiaryKafelki );
        }
        else if( element[a].rodzaj == "brama" )
        {
            if( element[a].stan == "open" )
            {
                 drawBmp( imageSurface, element[a].x, element[a].y, wymiaryKafelki * 4, wymiaryKafelki * 0, wymiaryKafelki, wymiaryKafelki );
            }
            else if( element[a].stan == "close" )
            {
                 drawBmp( imageSurface, element[a].x, element[a].y, wymiaryKafelki * 3, wymiaryKafelki * 0, wymiaryKafelki, wymiaryKafelki );
            }
        }
        else if( element[a].rodzaj == "bramaEnd" )
        {
            if( element[a].stan == "open" )
            {
                 drawBmp( imageSurface, element[a].x, element[a].y, wymiaryKafelki * 4, wymiaryKafelki * 3, wymiaryKafelki, wymiaryKafelki );
            }
            else if( element[a].stan == "close" )
            {
                 drawBmp( imageSurface, element[a].x, element[a].y, wymiaryKafelki * 3, wymiaryKafelki * 3, wymiaryKafelki, wymiaryKafelki );
            }
        }
        else if( element[a].rodzaj == "glaz" )
        {
            drawBmp( imageSurface, element[a].x, element[a].y, wymiaryKafelki * 3, wymiaryKafelki * 1, wymiaryKafelki, wymiaryKafelki );
        }
    }

    drawBmp( gracz.bitmapa, gracz.x, gracz.y, gracz.w * gracz.grafX, gracz.h * gracz.grafY, gracz.w, gracz.h );
}
*/
