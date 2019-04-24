#include <SDL2/SDL.h>
#include "eventhandle.h"
#include "OperateBrick.h"

// change rotate case so the brick will rotate
int changerotphase(int *board,int brick[][2][4],int bricktype, int positionx, int positiony, int rot_case,int bnumberx,int bnumbery)
{
    if (rotatedValid(board, brick,bricktype, positionx+1, positiony,(rot_case + 1) % 4,bnumberx,bnumbery))
    {
          return (rot_case + 1) % 4;
    }
    return rot_case;
}

// move right a space
int moveright(int *board,int brick[][2][4],int bricktype, int positionx, int positiony, int rot_case,int bnumberx,int bnumbery)
{
    	if (rotatedValid(board, brick,bricktype, positionx+1, positiony,rot_case,bnumberx,bnumbery))
    	{
    	    return ++positionx;
    	}
        return positionx;
}

//move left a space
int moveleft(int *board,int brick[][2][4],int bricktype, int positionx, int positiony, int rot_case,int bnumberx,int bnumbery)
{
    	if (rotatedValid(board, brick,bricktype, positionx-1, positiony,rot_case,bnumberx,bnumbery))
    	{
    	    return --positionx;
    	}
        return positionx;
}


//move down a space
int slowdown(int *board,int brick[][2][4],int bricktype, int positionx, int positiony, int rot_case,int bnumberx,int bnumbery)
{
    	if (rotatedValid(board,brick ,bricktype, positionx, positiony+1,rot_case,bnumberx,bnumbery))
    	{
    	    return ++positiony;
    	}
        return positiony;
}

//place the brick at the bottom
int fastdown(int *board,int brick[][2][4],int bricktype, int positionx, int positiony, int rot_case,int bnumberx,int bnumbery)
{
    int i;
    for(i=positiony;i<bnumbery;i++)
    {
        if(!rotatedValid(board,brick ,bricktype, positionx, i, rot_case,bnumberx,bnumbery))
           {
                break;
           }
    }
    return i-1;
}
