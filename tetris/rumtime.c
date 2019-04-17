#include "runtime.h"
#include "rotatebrick.h"

int piece[7][2][4] = {
	{{0,1,1,0},{0,1,1,0}},
	{{1,1,1,1},{0,0,0,0}},
	{{0,0,1,1},{0,1,1,0}},
	{{0,1,1,0},{0,0,1,1}},
	{{0,1,1,1},{0,0,1,0}},
	{{0,1,1,1},{0,1,0,0}},
	{{0,1,1,1},{0,0,0,1}}
};

int piece_color[7][3] = {
	{0, 200, 0},
	{200, 0, 0},
	{156, 85, 211},
	{219, 112, 147},
	{0, 100, 250},
	{230, 197, 92},
	{0, 128, 128},
};

void rungame(SDL_Renderer* grender,int bsize,int bnumberx,int bnumbery)
{

    //Main loop flag
    int quit = 0;
    //Event handler
    SDL_Event e;
    //Grid
    SDL_Rect box;
    //An array to store grids
    int *board = malloc(bnumberx*bnumbery*sizeof(int));
	memset(board, 0, bnumberx*bnumbery*sizeof(int));
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

        //Clear screen
        SDL_SetRenderDrawColor( grender, 0, 0, 0, 0 );
        SDL_RenderClear( grender );
        //Draw blue horizontal line
        SDL_SetRenderDrawColor( grender, 255, 255, 255, 255 );
        SDL_RenderDrawLine( grender, bsize*bnumberx, 0, bsize*bnumberx, bsize*bnumbery);
        box.w = bsize - 1;
        box.h = bsize - 1;
        SDL_SetRenderDrawColor(grender, 50, 50, 50, 0);
        for (int y=0; y<bnumbery; y++)
        {
				for (int x=0; x<bnumberx; x++)
                {
					box.x = x*bsize;
					box.y = y*bsize;
                    SDL_RenderDrawRect(grender, &box);
                }

        }

        //Update screen
        SDL_RenderPresent( grender );
    }
}
