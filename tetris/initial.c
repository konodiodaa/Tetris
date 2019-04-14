#include "initial.h"
int init(char* title)
{
	//Initialization flag
	int success = 1;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = 0;
	}
	else
	{
		//Create window

        extern gwindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,0);
		if( gwindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = 0;
		}
		else
		{
			//Create renderer for window
			extern grender = SDL_CreateRenderer( gwindow, -1, SDL_RENDERER_ACCELERATED );
			if( grender == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = 0;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( grender, 0, 0, 0, 0);
			}
		}
	}

	return success;
}
