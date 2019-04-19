#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "runtime.h"
SDL_Window* gwindow=NULL;
SDL_Renderer* grender=NULL;
const int bsize=35;
const int bnumberx=15;
const int bnumbery=20;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 700;

int init(char* title);

void close();

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

        gwindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,0);
		if( gwindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = 0;
		}
		else
		{
			//Create renderer for window
        grender = SDL_CreateRenderer( gwindow, -1, SDL_RENDERER_ACCELERATED );
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

void close()
{
   	//Destroy window
	SDL_DestroyRenderer( grender );
	SDL_DestroyWindow( gwindow );
	gwindow = NULL;
	grender = NULL;

	//Quit SDL subsystems

	SDL_Quit();
}

int main( int argc, char* args[]){
    if(!init("Tetris Game by SDL + C"))
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        rungame(gwindow,grender,bsize,bnumberx,bnumbery);
        close();
    }
return 0;
}

