#include "font.h"
/*int drawtext(char * textureText,SDL_Color textColor)
{
    TTF_Init();
   // TTF_Font *font= TTF_OpenFont("lazy.ttf",fontsize);
    int w,h;
    TTF_SizeText(font,S,&w,&h);
    if(font == NULL)
    {
       fprintf(stderr,"font open failure %s\n",SDL_GetError());
    }
    SDL_Color textColor = { (unsigned char)(color>>16), (unsigned char)(color>>8), (unsigned char)(color) };
    SDL_Surface * text = TTF_RenderText_Solid( font, S, textColor );
    bl.h=h;
    bl.w=w;
    bl.x=x;
    bl.y=y;
    SDL_FillRect(s, &bl,bkcolor);
    SDL_UpperBlit(text,NULL,s,&bl);
}
*/
