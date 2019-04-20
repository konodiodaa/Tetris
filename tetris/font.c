#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL.h"
#include "font.h"
void showfont(SDL_Texture* TextTexture,SDL_Renderer* grender,int x,int y,int w,int h,char* text)
{
    SDL_Surface * TextSurface = NULL;//�ı�����
    if( TTF_Init() == -1 )
		return -1;
	//������
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
	//�����ı�����
	TextTexture = SDL_CreateTextureFromSurface(grender, TextSurface);

	//��������Ⱦ��
	//SDL_RenderClear(grender);
	//���ı������Ƶ�������Ⱦ��
	SDL_RenderCopy(grender, TextTexture, NULL, &textrect);  // NULL means that use all texture( and renderer)
	//ˢ�´�����Ⱦ������ʾ

    SDL_DestroyTexture(TextTexture);
    SDL_FreeSurface(TextSurface);

}
