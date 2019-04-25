#include "runtime.h"
#include "time.h"
#include <stdlib.h>
#include "OperateBrick.h"
#include "eventhandle.h"
#include "font.h"
#include <stdio.h>
#include <string.h>
//brick shape
int piece[7][2][4] = {
	{{0,1,1,0},{0,1,1,0}},
	{{1,1,1,1},{0,0,0,0}},
	{{0,0,1,1},{0,1,1,0}},
	{{0,1,1,0},{0,0,1,1}},
	{{0,1,1,1},{0,0,1,0}},
	{{0,1,1,1},{0,1,0,0}},
	{{0,1,1,1},{0,0,0,1}}
};

//brick color
int piece_color[7][3] = {
	{0, 200, 0},
	{200, 0, 0},
	{156, 85, 211},
	{219, 112, 147},
	{0, 100, 250},
	{230, 197, 92},
	{0, 128, 128},
};

void rungame(SDL_Window* gwindow,SDL_Renderer* grender,int bsize,int bnumberx,int bnumbery)
{

   	int end = 0;    //decide if game is end
    int redraw = 1;     //whether render the screen
    int  put = 0;   //whether place the brick
	int key;    // store the keyboard event
	int speed = 1, line = 0;    //current speed and current score
	int pause = 0;      //whether pause the game
	int startx =(bnumberx-4)/2;     //the start x position of brick,and it`s at the middle of the screen
	int bricktype, positionx, positiony, rot_case;  //basic elements of brick
	int xshift, yshift; //the change on x position and y position when rotated.
	int clearlinenum;   //number of lines cleaned
	char currentSpeed[100];     // current speed display text
	char score[100];    //current score display text
	snprintf(currentSpeed,100,"Current speed: %d",speed);   //update the current speed text
    snprintf(score, 255, "Score: %d", line);    //update the current score text

    //Texture used for display font and text
    SDL_Texture* pauseText=NULL;
    SDL_Texture* speedupText=NULL;
    SDL_Texture* speedownText=NULL;
    SDL_Texture* currentSpeedText=NULL;
    SDL_Texture* scoreText=NULL;

	//array used for display grid and brick
	int *board = malloc(bnumberx*bnumbery*sizeof(int));
	memset(board, 0, bnumberx*bnumbery*sizeof(int));

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Rect box;   // a sdl rectangle used for grid


	SDL_Event event;    //a pointer to event occur

	srand(time(NULL));      //create random value

	//set initial brick`s shape position and rotate case
	bricktype = rand() % 7;
	positionx = startx;
	positiony = 0;
	rot_case= 0;

	int t = SDL_GetTicks();     //get time since the game start
	while (!end) {
		if (SDL_GetTicks() - t > 10*(101-speed) && !pause) // control of speed
        {
            //brick drop one space
			if (rotatedValid(board,piece,bricktype, positionx, positiony + 1, rot_case,bnumberx,bnumbery))
				positiony++;
			else
                put = 1;

			t = SDL_GetTicks();     // fresh time
			redraw = 1;
		}

		// place the brick
		if (put) {

			if (rotatedValid(board,piece,bricktype, positionx, positiony, rot_case,bnumberx,bnumbery)) {
				clearlinenum = placeBrick(board,piece,bricktype, positionx, positiony, rot_case,bnumberx,bnumbery);
				if (clearlinenum) {
					line += clearlinenum;
                    snprintf(score,100, "Score: %d", line);
				}
			}
            //start a new brick
            bricktype = rand() % 7;
            positionx = startx;
            positiony = 0;
            rot_case= 0;

            put = 0;
            redraw = 1;

			//check if lost
            if (!rotatedValid(board,piece,bricktype, positionx, positiony + 1, rot_case,bnumberx,bnumbery))
            {
				memset(board, 0, bnumberx*bnumbery*sizeof(int));
				line = 0;
				snprintf(score,100, "Score: %d", line);
			}
		}

		//render the screen
		if (redraw)
        {
            //render background of screen
			SDL_SetRenderDrawColor(grender, 0, 0, 0, 0);
			SDL_RenderClear(grender);

			//render text on screen
            showfont(scoreText,grender,530,100,100,25,score);
			showfont(currentSpeedText,grender,530,200,200,25,currentSpeed);
            showfont( pauseText,grender, 530,500,250,25,"Press: P to stop game");
            showfont(speedupText,grender,610,550,150,25,"+ to speed up");
            showfont(speedownText,grender,615,600,170,25,"- to speed down");
            // grid size and color
			box.w = bsize - 1;
			box.h = bsize - 1;

			SDL_SetRenderDrawColor(grender, 50, 50, 50, 0);


            //fill the screen with grid and brick
			for (int y=0; y<bnumbery; y++)
            {
				for (int x=0; x<bnumberx; x++)
				{
					box.x = x*bsize;
                    box.y = y*bsize;

					if (board[bnumberx*y + x] != 0)
                    {
						SDL_SetRenderDrawColor(grender,
								piece_color[board[bnumberx*y + x] - 1][0],
								piece_color[board[bnumberx*y + x] - 1][1],
								piece_color[board[bnumberx*y + x] - 1][2], 0);
						SDL_RenderFillRect(grender, &box);
						SDL_SetRenderDrawColor(grender, 50, 50, 50, 0);
					}
					else
                    {
						SDL_RenderDrawRect(grender, &box);
					}
				}
			}

			for (int y=0; y<2; y++) {
				for (int x=0; x<4; x++) {
					rotateBrick(&xshift, &yshift, x, y, bricktype, rot_case);
					box.x = (positionx + xshift)*bsize;
					box.y = (positiony + yshift)*bsize;

					if (piece[bricktype][y][x]) {
						SDL_SetRenderDrawColor(grender, piece_color[bricktype][0],
								piece_color[bricktype][1], piece_color[bricktype][2], 0);
						SDL_RenderFillRect(grender, &box);
					}
				}
			}
			SDL_RenderPresent(grender);
			redraw = 0;
		}

		//handle event
        while (SDL_PollEvent(&event))
        {
			switch (event.type)
			{
                case SDL_QUIT:
                    end = 1;
                    break;
                case SDL_WINDOWEVENT:
                    SDL_RenderPresent(grender);
                    break;
                case SDL_KEYDOWN:
                    key = event.key.keysym.sym;

                    // keyboard event
                    switch(key)
                    {
                        case SDLK_ESCAPE:
                            end=1;
                            break;
                        case SDLK_UP:
                            rot_case=changerotphase(board,piece,bricktype, positionx, positiony,rot_case,bnumberx,bnumbery);
                            pause=0;
                            break;
                        case SDLK_RIGHT:
                            positionx=moveright(board,piece,bricktype, positionx, positiony,rot_case,bnumberx,bnumbery);
                            pause=0;
                            break;
                        case SDLK_LEFT:
                            positionx=moveleft(board,piece,bricktype, positionx, positiony,rot_case,bnumberx,bnumbery);
                            pause=0;
                            break;
                        case SDLK_DOWN:
                            positiony=slowdown(board,piece,bricktype, positionx, positiony,rot_case,bnumberx,bnumbery);
                            pause=0;
                            break;
                        case SDLK_SPACE:
                            positiony=fastdown(board,piece,bricktype, positionx, positiony,rot_case,bnumberx,bnumbery);
                            pause=0;
                            put=1;
                            break;
                        case SDLK_p:
                            pause=!pause;
                            break;
                        case SDLK_KP_PLUS:
                        case SDLK_PLUS:
                        case SDLK_EQUALS:
                            if (speed < 100)
                            {
                                speed++;
                                snprintf(currentSpeed,100,"current speed is :%d",speed);
                            }
                            break;
                        case SDLK_KP_MINUS:
                        case SDLK_MINUS:
                            if (speed > 1)
                            {
                                speed--;
                                snprintf(currentSpeed,100,"current speed is :%d",speed);
                            }
                            break;
					}
					break;
				}
                redraw = 1;
                SDL_RenderClear(grender);
				break;

        }
	}
}
