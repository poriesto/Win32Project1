#include "stdafx.h"
#include "snake.h"
#include "congfx.h"

#include <iostream>
#include <conio.h>

using std::cout;
using std::cin;
using std::endl;

void congfx :: init()
{
	cout << "congfx: Console GFX class initialized." << endl;
}

void congfx :: renderplane(snakeplane* sp, snake* s)
{
	int x,y,p;
	short cell;
//
//	for (p=1;p<7;p++)
//	{
//		getch();
	p = s->last->side;
	cout << endl;
	cout << s->cells->x << ", " << s->cells->y << ", " << s->cells->side << endl;
		//cout << p << endl;
		for (y=0; y<BOARDWIDTH; y++)
		{
			cout << y << "!\t";
			for (x=0; x<BOARDWIDTH; x++)
			{
				cell=sp->getcell(snakecell(x,y,p));
				cout << cell;
			}
			cout << endl;
		}

//	}
}

void congfx :: rotatecube(int dir)
{
	cout << "congfx: No rotations!!!" << endl;
}

congfx :: congfx()
{
	cout << "congfx: Console GFX class created." << endl;
}

congfx :: ~congfx()
{
	cout << "congfx: Console GFX class destroyed." << endl;
}
