#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL.h"
#include "font.h"
#include <stdio.h>
int showfont(SDL_Texture* TextTexture,SDL_Renderer* grender,int x,int y,int w,int h,char* text)
{
    SDL_Surface * TextSurface = NULL;//text surface
    if( TTF_Init() == -1 )
		return -1;
	//open the font
	TTF_Font *font;
	font=TTF_OpenFont("Arial CE.ttf", 30);
	if(!font)
	{
		printf("TTF_OpenFont: Open lazy.ttf %s\n", TTF_GetError());

	}

	SDL_Rect textrect;
	textrect.x=x;
	textrect.y=y;
	textrect.w=w;
	textrect.h=h;
	SDL_Color color2={255,255,255};
	TextSurface = TTF_RenderText_Blended(font,text,color2);
	//create text texture
	TextTexture = SDL_CreateTextureFromSurface(grender, TextSurface);


    //copy the texture to the window renderer
	SDL_RenderCopy(grender, TextTexture, NULL, &textrect);  // NULL means that use all texture( and renderer)

    // free the extra variable
    SDL_DestroyTexture(TextTexture);
    SDL_FreeSurface(TextSurface);
    return 1;
}
