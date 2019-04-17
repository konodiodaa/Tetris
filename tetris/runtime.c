#include "runtime.h"
void rungame()
{

    //Main loop flag
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
        //Clear screen
        SDL_SetRenderDrawColor( grender, 0, 0, 0, 0 );
        SDL_RenderClear( grender );
        //Update screen
        SDL_RenderPresent( grender );
    }
}
