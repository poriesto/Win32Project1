/* Snakecls.cpp: Snake class functions */
#include "stdafx.h"
#include "snake.h"
#include <stdlib.h>

snake :: snake ()
{
	last = cells = NULL;

	nibble=SNAKE_ILEN-1;

	direction = 3;
}

snake :: snake (snakecell cell, int length)
{
	last = cells = new snakeclist(cell.x,cell.y,cell.side);

	nibble = length-1;
	direction = 3;
}

short snake :: steer (short newdir)
{
	if (newdir+2 != direction && newdir-2 != direction)
		direction = newdir;

	return direction;
}

snake :: ~snake ()
{
	snakeclist* l = cells;

	while (l)
	{
		if (l->next)
		{
			l = l->next;
			delete l->prev;
		}
		else
		{
			delete l;
			break;
		}
	}
}

void snake :: kill (snakecell start)
{
	snakeclist *clist;

	clist = cells;
	while (clist)
	{
		if (clist->next)
		{
			clist = clist->next;
			delete clist->prev;
		}
		else
		{
			delete clist;
			break;
		}
	}

	cells = new snakeclist(start.x,start.y,start.side);

	nibble = SNAKE_ILEN;
}

void snake :: eat ()
{
	nibble += NIBBLE_EAT;
}

void snake :: poison ()
{
	if (length()+nibble-NIBBLE_POISON>0)
		nibble -= NIBBLE_POISON;
}

int snake :: length ()
{
	int res=0;
	snakeclist *clist;

	clist=cells;

	while(clist)
	{
		res++;
		clist=clist->next;
	}

	return res;
}
