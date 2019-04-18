#include <SDL2/SDL.h>
#include "eventhandle.h"
#include "OperateBrick.h"
int screenhandle(SDL_Renderer* grender,SDL_Event event)
{
    int key
    int end
    switch (event.type)
    {
        case SDL_QUIT:
            end = 1;
            break;
        case SDL_WINDOWEVENT:
            SDL_RenderPresent(renderer);
            break;
        case SDL_KEYDOWN:
            key = event.key.keysym.sym;

            switch(key)
            {


            }
    }
    return end;
}
