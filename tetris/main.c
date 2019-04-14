#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "initial.h"
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 700;
const int bsize=35;
const int bnumberx=15;
const int bnumbery=20;

SDL_Window* gwindow=NULL;
SDL_Renderer* grender=NULL;
int main( int argc, char* args[]){
    if(!init(gwindow,grender,"Tetris Game by SDL + C",SCREEN_WIDTH,SCREEN_HEIGHT)){
        printf( "Failed to initialize!\n" );
    }
    else
    {
        int quit = 0;

        //Event handler
        SDL_Event e;

        //While application is running
        while( !quit )
        {
            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    quit = 1;
                }
            }
            SDL_RenderClear( grender );
            SDL_SetRenderDrawColor( grender,0, 0, 0, 0);
            SDL_RenderPresent( grender );
        }

    }

}

