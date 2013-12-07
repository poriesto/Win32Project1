/* Snakcel.cpp:
   Cell and list operations */
#include "stdafx.h"
#include "snake.h"
#include <stdlib.h>

snakecell :: snakecell ()
{
}

snakecell :: snakecell (int nx, int ny, int nside)
{
	x=nx;
	y=ny;
	side = nside;
}

snakeclist :: snakeclist ()
{
	prev = next = NULL;
}

snakeclist :: snakeclist (int nx, int ny, int nside)
{
	prev = next = NULL;
	x = nx;
	y = ny;
	side = nside;
}

snakeclist :: snakeclist (int nx, int ny, int nside, snakeclist *nprv)
{
	prev = nprv;
	if (prev)
		prev->next=this;

	next = NULL;
	x = nx;
	y = ny;
	side = nside;
}

snakeclist :: snakeclist (int nx, int ny, int nside, snakeclist *nprv, snakeclist *nnxt)
{
	prev = nprv;
	if (prev)
		prev->next=this;

	next = nnxt;
	if (next)
		next->prev=this;

	x = nx;
	y = ny;
	side = nside;
}

snakeclist :: snakeclist (snakeclist *nprv)
{
	prev = nprv;
	if (prev)
		prev->next=this;

	next = NULL;
}

snakeclist :: snakeclist (snakeclist *nprv, snakeclist *nnxt)
{
	prev = nprv;
	if (prev)
		prev->next=this;

	next = nnxt;
	if (next)
		next->prev=this;
}

snakeclist :: ~snakeclist ()
{
	if (prev)
		prev->next=next;
	if (next)
		next->prev=prev;
}
