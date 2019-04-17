#include "rotatebrick.h"

void rotatebrick(int *xshift, int *yshift, int x, int y, int pn, int rot_case)
{
    int rot_method;

	switch (pn) {
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

