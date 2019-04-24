#include "OperateBrick.h"

// rotate the brick update the xshift and yshift by using the rotate case of the brick
void rotateBrick(int *xshift, int *yshift, int x, int y, int bricktype, int rot_case)
{
    int rot_method;

	switch (bricktype) {
	case 0:
		rot_method = 0;
		break;
	case 1: case 2: case 3:
		rot_method = rot_case % 2;
		break;
	case 4: case 5: case 6:
		rot_method = rot_case;
		break;
	}

	switch (rot_method) {
	case 0:
		*xshift = x;
		*yshift = y;
		break;
	case 1:
		*xshift = y + 2;
		*yshift = 2 - x;
		break;
	case 2:
		*xshift = 4 - x;
		*yshift = 1 - y;
		break;
	case 3:
		*xshift = 2 - y;
		*yshift = x - 1;
		break;
	}
}

// judge the rotate operation successful or not
int rotatedValid(int *board,int brick[][2][4],int bricktype, int positionx, int positiony, int rot_case,int bnumberx,int bnumbery)
{
    int xshift, yshift;

	for (int y=0; y<2; y++)
    {
		for (int x=0; x<4; x++)
		{
			rotateBrick(&xshift, &yshift, x, y, bricktype, rot_case);

			if (positiony + yshift >= 0 && brick[bricktype][y][x])
			{
				if (positionx + xshift >= bnumberx || positionx + xshift < 0)
                    return 0;
				else if (positiony + yshift >= bnumbery)
                    return 0;
				else if (positiony >= 0 && board[bnumberx*(positiony + yshift) + positionx + xshift])
                    return 0;
			}
		}
	}

	return 1;
}

// place the brick
int placeBrick(int *board,int brick[][2][4],int bricktype, int positionx, int positiony, int rot_case,int bnumberx,int bnumbery)
{
    int xshift, yshift, isclear, clearline = 0;

	for (int y=0; y<2; y++) {
		for (int x=0; x<4; x++) {
			rotateBrick(&xshift, &yshift, x, y, bricktype, rot_case);

			if (positiony + yshift >= 0 && brick[bricktype][y][x]) board[bnumberx*(positiony + yshift) + positionx + xshift] = bricktype+1;
            //decide color of brick
		}
	}

	//clear lines
	for (int y=positiony-1; y<positiony+3; y++) {
		if (y >= 0 && y < bnumbery) {
			isclear = 1;

			for (int x=0; x<bnumberx; x++) {
				if (board[bnumberx*y + x] == 0) {
					isclear = 0;
					break;
				}
			}

			if (isclear) {
				clearline++;
				for (yshift=y; yshift>0; yshift--)
					for (int x=0; x<bnumberx; x++) board[bnumberx*yshift + x] = board[bnumberx*(yshift-1) + x];
			}
		}
	}

	return clearline;

}
