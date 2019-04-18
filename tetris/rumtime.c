#include "runtime.h"
#include "time.h"
#include <stdlib.h>
#include "OperateBrick.h"

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

void rungame(SDL_Window* gwindow,SDL_Renderer* grender,int bsize,int bnumberx,int bnumbery)
{

   	int end = 0, redraw = 1;
	int key, shift;

	int speed = 50, line = 0;
	int pause = 0, put = 0;
	int game = 0;
	int startx =(bnumberx-4)/2;
	int bricktype, positiox, positioy, rot_case;

	int xshift, yshift, clearlinenum;

	char title[255];
	snprintf(title, 255, "lines=%d,speed=%d", line, speed);



	int *board = malloc(bnumberx*bnumbery*sizeof(int));
	memset(board, 0, bnumberx*bnumbery*sizeof(int));

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Rect box;

	srand(time(NULL));

	bricktype = rand() % 7;
	positiox = startx;
	positioy = 0;
	rot_case= 0;

	int t = SDL_GetTicks();

	while (!end) {
		if (SDL_GetTicks() - t > 3*(101-speed) && !pause) {
			if (rotatedValid(board,piece,bricktype, positiox, positioy + 1, rot_case,bnumberx,bnumbery))
				positioy++;
			else put = 1;

			t = SDL_GetTicks();
			redraw = 1;
		}

		if (put) {
			if (rotatedValid(board,piece,bricktype, positiox, positioy + 1, rot_case,bnumberx,bnumbery)) {
				clearlinenum = placeBrick(board,piece,bricktype, positiox, positioy, rot_case,bnumberx,bnumbery);
				if (clearlinenum) {
					line += clearlinenum;
					snprintf(title, 255, "lines=%d,speed=%d", line, speed);
					SDL_SetWindowTitle(gwindow, title);
				}
			}

        bricktype = rand() % 7;
        positiox = startx;
        positioy = 0;
        rot_case= 0;

        put = 0;
        redraw = 1;

			//check if lost
			if (rotatedValid(board,piece,bricktype, positiox, positioy + 1, rot_case,bnumberx,bnumbery)) {
				printf("game %d: %d lines\n", ++game, line);
				memset(board, 0, bnumberx*bnumbery*sizeof(int));
				line = 0;
				snprintf(title, 255, "lines=%d,speed=%d", line, speed);
				SDL_SetWindowTitle(gwindow, title);
			}
		}

		if (redraw) {
			SDL_SetRenderDrawColor(grender, 0, 0, 0, 0);
			SDL_RenderClear(grender);

			box.w = bsize - 1;
			box.h = bsize - 1;

			SDL_SetRenderDrawColor(grender, 50, 50, 50, 0);
			SDL_RenderDrawRect(grender, &box);

			for (int y=0; y<bnumbery; y++) {
				for (int x=0; x<bnumberx; x++) {
					box.x = x*bsize;
					box.y = y*bsize;

					if (board[bnumberx*y + x] != 0) {
						SDL_SetRenderDrawColor(grender,
								piece_color[board[bnumberx*y + x] - 1][0],
								piece_color[board[bnumberx*y + x] - 1][1],
								piece_color[board[bnumberx*y + x] - 1][2], 0);
						SDL_RenderFillRect(grender, &box);
						SDL_SetRenderDrawColor(grender, 50, 50, 50, 0);
					} else {
						SDL_RenderDrawRect(grender, &box);
					}
				}
			}

			for (int y=0; y<2; y++) {
				for (int x=0; x<4; x++) {
					rotateBrick(&xshift, &yshift, x, y, bricktype, rot_case);
					box.x = (positiox + xshift)*bsize;
					box.y = (positioy + yshift)*bsize;

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
    }
}


void eventHandle(SDL_Renderer* grender,SDL_Event event,int* end)
{
   while (SDL_PollEvent(&event))
    {


            switch (key)
            {
				case SDLK_ESCAPE:
					end = 1;
					break;
				case SDLK_UP:
					if (valid(board, pn, px, py, (rot + 1) % 4))
                    {
                        rot = (rot + 1) % 4;
                    }
					pause = 0;
					break;
				case SDLK_LEFT:
                    if (valid(board, pn, px - 1, py, rot))
                    {
                        px--;
                    }
					pause = 0;
					break;
				case SDLK_RIGHT:
                    if (valid(board, pn, px + 1, py, rot))
                    {
                        px++;
                    }
					pause = 0;
					break;
				case SDLK_DOWN:
                case SDLK_SPACE:
                    for (yy=py; yy<sh; yy++)
                    {
                        if (!valid(board, pn, px, yy, rot)) break;
                    }
                    py = yy - 1;
                    put = 1;
					pause = 0;
					break;
				case SDLK_p:
					pause = !pause;
					break;
				case SDLK_RETURN:
					printf("game %d: %d lines\n", ++game, line);
					pn = rand() % 7;
					px = startx;
					py = 0;
					rot = 0;
					put = 0;
					redraw = 1;
					memset(board, 0, sw*sh*sizeof(int));
					line = 0;
					snprintf(title, 255, "lines=%d,speed=%d", line, speed);
					SDL_SetWindowTitle(window, title);
					break;
				case SDLK_KP_PLUS: case SDLK_PLUS: case SDLK_EQUALS:
					if (speed < 100) {
						speed++;
						snprintf(title, 255, "lines=%d,speed=%d", line, speed);
						SDL_SetWindowTitle(window, title);
					}
					break;
				case SDLK_KP_MINUS: case SDLK_MINUS:
					if (speed > 1) {
						speed--;
						snprintf(title, 255, "lines=%d,speed=%d", line, speed);
						SDL_SetWindowTitle(window, title);
					}
					break;
				}

				redraw = 1;
				break;
			}
			//SDL_FlushEvent(event.type);
		}
	}
}
