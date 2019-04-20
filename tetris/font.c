#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL.h"
#include "font.h"
void showfont(SDL_Texture* TextTexture,SDL_Renderer* grender,int x,int y,int w,int h,char* text)
{
    SDL_Surface * TextSurface = NULL;//文本表面
    if( TTF_Init() == -1 )
		return -1;
	//打开字体
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
	//创建文本纹理
	TextTexture = SDL_CreateTextureFromSurface(grender, TextSurface);

	//清理窗口渲染器
	//SDL_RenderClear(grender);
	//将文本纹理复制到窗口渲染器
	SDL_RenderCopy(grender, TextTexture, NULL, &textrect);  // NULL means that use all texture( and renderer)
	//刷新窗口渲染器的显示

    SDL_DestroyTexture(TextTexture);
    SDL_FreeSurface(TextSurface);

}
