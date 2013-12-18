#include "stdafx.h"
/* Snakegam.cpp : Game class functions */
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <time.h>
#include "snake.h"

using std::cout;
using std::cin;
using std::endl;

extern snakegame *maingame;

void snakegame :: init()
{
	srand((int)time(NULL));
	maingame = this;
}
	
void snakegame :: addrand ()
{
	snakeclist *scl;
	snakecell sc(rand()%BOARDWIDTH, rand()%BOARDWIDTH, (rand()%6) + 1);
recheck:
	for (scl = this->snakes[0]->cells; scl->next != NULL; scl = scl->next)
	{
		if ((sc.x == scl->x) && (sc.y == scl->y) && (sc.side == scl->side))
		{
			sc.x = rand()%BOARDWIDTH;
			sc.y = rand()%BOARDWIDTH;
			sc.side = (rand()%6) + 1;
			goto recheck;
		}
	}
	plane->setcell(sc, CELL_FOOD);
	if (plane->foods == NULL)
		plane->foods = new snakeclist(sc.x, sc.y, sc.side);
	else
		plane->foods->next = new snakeclist(sc.x, sc.y, sc.side);
}

snakecell snakegame :: startloc (int player)
{
	return snakecell(player*2,BOARDWIDTH-(player*2),3);
}

void snakegame :: endgame (int player)
{
	this->stop = 1;
}

void snakegame :: update()
{
	int i;

	for (i=0; i<nsnakes; i++)
	{
		snakeclist *scl;
		snakeclist *scl2;
		char buf[30];
		int movestat;
		movestat=plane->nextcell(snakes[i]);
		playeract(movestat,i);
		
		for (scl = this->snakes[i]->cells; scl->next != NULL; scl = scl->next)
		{
			for (scl2 = this->snakes[i]->cells; scl2->next != NULL; scl2 = scl2->next)
			{
				if (scl2 == scl)
					continue;
				if ((scl2->x == scl->x) && (scl2->y == scl->y) && (scl2->side == scl->side))
				{
					sprintf(&buf[0], "Your score is %d.", maingame->players[0]->score);
					MessageBox(NULL, &buf[0], "SuperSnake3D", 0);
					exit(0);
					cout.flush();
					stop = 1;
				}
			}
		};
	}

	if (!count)
	{
		count = COUNTMIN * (rand() * COUNTRND) / RAND_MAX;
		addrand();
	}
}

void snakegame :: redraw()
{
	gfx->renderplane(plane, snakes[0]);
}

snakegame :: snakegame()
{
	stop = 0;
	pause = 0;
	plane = new snakeplane();
	gfx = NULL;
}

snakegame :: snakegame(int nnsnakes)
{
	int i;

	stop =0;

	nsnakes = nnsnakes;

	plane = new snakeplane();
	gfx = NULL;

	snakes = new snake* [nnsnakes];
	ctls = new snakectl* [nnsnakes];

	for (i=0; i<nnsnakes; i++)
	{
		snakes[i] = new snake(startloc(i),SNAKE_ILEN);
		players[i] = new snakeplayer();
		players[i]->score=0;
		players[i]->lives=I_LIVES;
	}
}

snakegame :: ~snakegame()
{
	int i;
	
	delete plane;

	for (i=0; i<nsnakes; i++)
	{
		delete snakes[i];
		delete players[i];
		delete ctls[i];
	}

	delete gfx;

}

void snakegame :: playeract(int movestat, int player)
{
	switch(movestat)
	{
	case 0:
		return;
	case SNAKE_DIE:
		if(players[player]->lives--)
		{
			endgame(player);
			return;
		}
		snakes[player]->kill(startloc(player));
		break;
	case SNAKE_EAT:
		snakes[player]->eat();
		players[player]->score+=FOOD_SCORE;
		addrand();
		break;
	case SNAKE_POISON:
		snakes[player]->poison();
		players[player]->score+=POISON_SCORE;
		break;
	case SNAKE_EXTRA:
		players[player]->score+=EXTRA_SCORE;
		break;
	case SNAKE_LIFE:
		players[player]->lives++;
		break;
	}
}

void snakegame :: mainloop ()
{
	while (!stop)
	{
		if (!pause)
			update();
		redraw();

		Sleep(500); /* check keys */

		int i;

		for (i=0; i<nsnakes; i++)
		{
			if (ctls[i]->pollinput() && (pause != 1))
			{
				short move;
				move = ctls[i]->getinput();
				if (move)
				{
					if (move==STOPKEY)
					{
						cout << "Ending due to stop key pressed."<<endl;
						stop=1;
						return;
					}
					if (move<=4)
						snakes[i]->steer(move);
				}
			}
		}
	}
	cout << "Ending due to snake crash!" <<endl;
}

extern void drawScene();
extern void drawSceneU();

void snakeup()
{
	if (!maingame->pause)
		maingame->update();
	maingame->redraw();

	int i;
	for (i=0; i<maingame->nsnakes; i++)
	{
		if (maingame->ctls[i]->pollinput() && (maingame->pause != 1))
		{
			short move;
			move = maingame->ctls[i]->getinput();
			if (move)
			{
				if (move==STOPKEY)
				{
					MessageBox(NULL,"Ending due to stop key pressed.","Snake",0);
					maingame->stop=1;
					return;
				}
				if (move<=4)
				{
					maingame->snakes[i]->steer(move);
				}
			}
		}
	}
}
