/* Snakepln.cpp: snakeplane class functions */
#include "stdafx.h"
#include "snake.h"
#include <stdlib.h>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

snakeplane :: snakeplane()
{
	foods=extras=poisons=lives=NULL;
	int x,y,p;

	for (p=1;p<7;p++)
		for (y=0;y<=BOARDWIDTH;y++)
			for (x=0;x<=BOARDWIDTH;x++)
				grid[x][y][p-1]=0;
}

snakeplane :: ~snakeplane ()
{
}

short snakeplane :: getcell(snakecell sc)
{
	if (sc.side < 0)
		exit(0);
	return grid[sc.x][sc.y][sc.side-1];
}

void snakeplane :: setcell(snakecell sc, short val)
{
	grid[sc.x][sc.y][sc.side-1]=val;
}

#if 0
void snakeplane :: getbounds(int &xmin, int &xmax, int &ymin, int &ymax, int side)
{
	switch (side)
	{
	case 1:
		xmin=BOARDWIDTH;
		ymin=BOARDWIDTH*3;
		xmax=BOARDWIDTH*2-1;
		ymin=BOARDWIDTH*4-1;
		return;
	case 2:
		xmin=BOARDWIDTH;
		ymin=BOARDWIDTH*2;
		xmax=BOARDWIDTH*2-1;
		ymin=BOARDWIDTH*3-1;
		return;
	case 3:
		xmin=0;
		ymin=BOARDWIDTH;
		xmax=BOARDWIDTH-1;
		ymin=BOARDWIDTH*2-1;
		return;
	case 4:
		xmin=BOARDWIDTH;
		ymin=BOARDWIDTH;
		xmax=BOARDWIDTH*2-1;
		ymin=BOARDWIDTH*2-1;
		return;
	case 5:
		xmin=BOARDWIDTH*2;
		ymin=BOARDWIDTH;
		xmax=BOARDWIDTH*3-1;
		ymin=BOARDWIDTH*2-1;
		return;
	case 6:
		xmin=BOARDWIDTH;
		ymin=0;
		xmax=BOARDWIDTH*2-1;
		ymin=BOARDWIDTH-1;
		return;
	}
}
#endif

int snakeplane :: nextcell(snake *snake)
{
	int nx, ny, ns;
	int xminp,xmaxp,yminp,ymaxp;
	snakeclist *clistx;
	short incell;

	nx=snake->last->x;
	ny=snake->last->y;
	ns=snake->last->side;

	switch (snake->direction)
	{
	case 1:
		ny++;
		break;
	case 2:
		nx--;
		break;
	case 3:
		ny--;
		break;
	case 4:
		nx++;
	}

//    getbounds(xminp,xmaxp,yminp,ymaxp,ns);
	xminp = yminp = 0;
	xmaxp = ymaxp = 15;

	if (nx<xminp || nx>xmaxp || ny<yminp || ny>ymaxp)
		chgside(nx,ny,ns,snake->direction);

	clistx = new snakeclist(nx,ny,ns,snake->last);
	snake->last=clistx;

	if (snake->nibble==0)	/* delete one link */
	{
		snake->cells=snake->cells->next;
		setcell(*(snake->cells->prev),0);
		delete snake->cells->prev;
	}
	else if (snake->nibble>0) /* don't delete link, dec nibble */
	{
		snake->nibble--;
	}
	else if (snake->nibble<0) /* delete 2 links, inc nibble */
	{
		snake->cells=snake->cells->next;
		setcell(*(snake->cells->prev),0);
		delete snake->cells->prev;
		snake->cells=snake->cells->next;
		setcell(*(snake->cells->prev),0);
		delete snake->cells->prev;

		snake->nibble++;
	}

	if (incell=getcell(*(snake->last)))
		if (incell==CELL_BLOCK || incell==CELL_SNAKE)
			return SNAKE_DIE;

	snakecell temp;

	temp.side = snake->last->side;
	temp.x = snake->last->x;
	temp.y = snake->last->y;

	setcell(temp,CELL_SNAKE);

	if (incell)
		killcell(*(snake->last));

	switch (incell)
	{
	case CELL_FOOD:
		return SNAKE_EAT;
	case CELL_POISON:
		return SNAKE_POISON;
	case CELL_EXTRA:
		return SNAKE_EXTRA;
	case CELL_LIFE:
		return SNAKE_LIFE;
	default:
		return 0;
	}
}

void snakeplane :: killcell(snakecell sc)
{
	snakeclist *itemlist;

	switch(getcell(sc))
	{
	case CELL_FOOD:
		itemlist=foods;
	case CELL_POISON:
		itemlist=poisons;
	case CELL_EXTRA:
		itemlist=extras;
	case CELL_LIFE:
		itemlist=lives;
	default:
		itemlist=NULL;
	}
	
	while(itemlist)
	{
		if (itemlist->x==sc.x && itemlist->y==sc.y)
			break;
		itemlist=itemlist->next;
	}
	if (itemlist)
	{
		if (itemlist->prev)
			itemlist->prev->next=itemlist->next;
		if (itemlist->next)
			itemlist->next->prev=itemlist->prev;
		delete itemlist;
	}
}

void snakeplane :: chgside (int &nx,int &ny, int &ns, short &ndir)
{
	if (nx<0)
	{
		switch (ns)
		{
		case 1:
			ns=3;
			ny=BOARDWIDTH-ny-1;
			nx=0;
			ndir = DIR_RIGHT;
			return;
		case 2:
			ns = 3;
			nx=BOARDWIDTH-ny-1;
			ny=BOARDWIDTH-1;
			ndir = DIR_DOWN;
			return;
		case 3:
			ns=1;
			ny=BOARDWIDTH-ny-1;
			nx=0;
			ndir = DIR_RIGHT;
			return;
		case 4:
			ns=3;
			nx=BOARDWIDTH-1;
			ndir = DIR_LEFT;
			return;
		case 5:
			ns=4;
			nx=BOARDWIDTH-1;
			ndir = DIR_LEFT;
			return;
		case 6:
			ns=3;
			nx=ny;
			ny = 0;
			ndir = DIR_UP;
//			cout << "Bug6xxxx";
//			cout.flush();
		default:
			return;
		}
	}
	if(nx>BOARDWIDTH-1)
	{
		switch(ns)
		{
		case 1:
			ns=5;
			ny=BOARDWIDTH-ny-1;
			nx=BOARDWIDTH-1;
			ndir = DIR_LEFT;
			return;
		case 2:
			ns=5;
			nx=ny;
			ny=BOARDWIDTH-1;
			ndir = DIR_DOWN;
			return;
		case 3:
			ns=4;
			nx=0;
			ndir = DIR_RIGHT;
			return;
		case 4:
			ns=5;
			nx=0;
			ndir = DIR_RIGHT;
			return;
		case 5:
			ns=1;
			ny=BOARDWIDTH-ny-1;
			nx=BOARDWIDTH-1;
			ndir = DIR_LEFT;
			return;
		case 6:
			ns=5;
			nx=BOARDWIDTH-ny-1;
			ny=0;
			ndir=DIR_UP;
//			cout << "Bug6xxx " << ns;
//			cout.flush();
		default:
			return;
		}
	}
	if(ny<0)
	{
		switch(ns)
		{
		case 1:
			ns=2;
			ny=BOARDWIDTH-1;
			ndir=DIR_DOWN;
			return;
		case 2:
			ns=4;
			ny=BOARDWIDTH-1;
			ndir=DIR_DOWN;
			return;
		case 3:
			ns=6;
			ny=nx;
			nx=0;
			ndir=DIR_RIGHT;
			return;
		case 4:
			ns=6;
			ny=BOARDWIDTH-1;
			ndir=DIR_DOWN;
			return;
		case 5:
			ns=6;
			ny=BOARDWIDTH-nx-1;
			nx=BOARDWIDTH-1;
			ndir=DIR_LEFT;
			return;
		case 6:
			ns=1;
			ny=BOARDWIDTH-1;
			ndir=DIR_DOWN;
//			cout << "Bug6xx";
//			cout.flush();
		default:
			return;
		}
	}
	switch(ns)
	{
	case 1:
		ns=6;
		ny=0;
		ndir=DIR_UP;
		return;
	case 2:
		ns=1;
		ny=0;
		ndir=DIR_UP;
		return;
	case 3:
		ns=2;
		ny=BOARDWIDTH-nx-1;
		nx=0;
		ndir=DIR_RIGHT;
		return;
	case 4:
		ns=2;
		ny=0;
		ndir=DIR_UP;
		return;
	case 5:
		ns=2;
		ny=nx;
		nx=BOARDWIDTH-1;
		ndir=DIR_LEFT;
		return;
	case 6:
		ns=4;
		ny=0;
		ndir=DIR_UP;
	default:
		return;
	}
}
/*
void snakeplane :: chgside (int &nx, int &ny, int &ns)
{
	switch (ns)
	{
	case 1:
		if (nx<BOARDWIDTH)
		{
			ns=3;
			nx=0;
			ny=BOARDWIDTH*5-ny-1;
			return;
		}
		if (nx>BOARDWIDTH*2-1)
		{
			ns=5;
			nx=BOARDWIDTH*3-1;
			ny=BOARDWIDTH*5-ny-1;
			return;
		}
		if (ny>BOARDWIDTH*4-1)
		{
			ns=6;
			ny=0;
			return;
		}
		ns=2;
		return;
	case 2:
		if (nx<BOARDWIDTH)
		{
			ns=3;
			nx=BOARDWIDTH*3-ny-1;
			ny=BOARDWIDTH*2-1;
			return;
		}
		if (nx>BOARDWIDTH*2-1)
		{
			ns=5;
			nx=ny;
			ny=BOARDWIDTH*2-1;
			return;
		}
		if (ny<BOARDWIDTH*2)
			ns=4;
		else
			ns=1;
		return;
	case 3:
		if (nx<0)
		{
			ns=1;
			ny=BOARDWIDTH*5-ny-1;
			nx=BOARDWIDTH;
			return;
		}
		if (ny<BOARDWIDTH)
		{
			ns=6;
			ny=nx;
			nx=BOARDWIDTH;
			return;
		}
		if (ny>BOARDWIDTH*2-1)
		{
			ns=2;
			ny=BOARDWIDTH*3-nx-1;
			nx=BOARDWIDTH;
			return;
		}
		ns=4;
		return;
	case 4:
		if (nx<BOARDWIDTH)
			ns=3;
		else if (nx>BOARDWIDTH*2-1)
			ns=5;
		else if (ny<BOARDWIDTH)
			ns=6;
		else
			ns=2;
		return;
	case 5:
		if (nx>BOARDWIDTH*3-1)
		{
			ns=1;
			ny=BOARDWIDTH*5-ny-1;
			nx=BOARDWIDTH*2-1;
			return;
		}
		if (ny<BOARDWIDTH)
		{
			ns=6;
			ny=BOARDWIDTH*3-nx-1;
			nx=BOARDWIDTH*2-1;
			return;
		}
		if (ny>BOARDWIDTH*2-1)
		{
			ns=2;
			ny=nx;
			nx=BOARDWIDTH*2-1;
			return;
		}
		ns=4;
		return;
	case 6:
		if (nx<BOARDWIDTH)
		{
			ns=3;
			nx=ny;
			ny=BOARDWIDTH;
			return;
		}
		if (nx>BOARDWIDTH*2-1)
		{
			ns=5;
			nx=BOARDWIDTH*3-ny-1;
			ny=BOARDWIDTH;
			return;
		}
		if (ny<0)
		{
			ns=1;
			ny=BOARDWIDTH*4-1;
			return;
		}
		ns=4;
		return;
	}
}

  */

