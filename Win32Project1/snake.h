#ifndef _SNAKE_H
#define _SNAKE_H

/* initial length */
#define SNAKE_ILEN 8
/* initial life */
#define I_LIVES 3
/* error codes */
#define SNAKE_DIE 1
#define SNAKE_EAT 2
#define SNAKE_POISON 3
#define SNAKE_EXTRA 4
#define SNAKE_LIFE 5
/* bonuses */
#define FOOD_SCORE 10
#define POISON_SCORE -5
#define EXTRA_SCORE 50

#define COUNTMIN 50
#define COUNTRND 100

#define BOARDWIDTH 16

#define CELL_EMPTY 0
#define CELL_BLOCK 1
#define CELL_SNAKE 2
#define CELL_FOOD 3
#define CELL_POISON 4
#define CELL_EXTRA 5
#define CELL_LIFE 6

#define NIBBLE_EAT 6
#define NIBBLE_POISON 3

#define DIR_UP 1
#define DIR_LEFT 2
#define DIR_DOWN 3
#define DIR_RIGHT 4

#define STOPKEY 5

/* class prototypes */

class snakecell;
class snakeclist;
class snakeplane;
class snake;
class snakegfx;
class snakeplayer;
class snakectl;
class snakegame;

/* class definitions */

/* snakecell: basically only a coord. */
class snakecell
{
public:
	/* position on the X axis */
	int x;
	/* position on the Y axis */
	int y;
	/*       +-----+      * 
	 *       |  1  |      * 
	 *       +-----+      * 
	 *       |  2  |      * 
	 * +-----+-----+-----+* 
	 * |  3  |  4  |  5  +* 
	 * +-----+-----+-----+* 
	 *       |  6  |      * 
	 *       +-----+      * 
	 * which side it's on */
	int side;

	/* constructor */
	snakecell(int x, int y, int side);
	/* constructor */
	snakecell();
};

/* snakeclist: doubly linked list of cells, used for the snake. */
class snakeclist: public snakecell
{
public:
	/* previous element of the list */
	snakeclist *prev;
	/* next element of the list */
	snakeclist *next;

	/* constructor */
	snakeclist();
	/* constructor */
	snakeclist(int x, int y, int side);
	/* constructor */
	snakeclist(snakeclist* prev);
	/* constructor */
	snakeclist(int x, int y, int side, snakeclist* prev);
	/* constructor */
	snakeclist(snakeclist* prev, snakeclist* next);
	/* constructor */
	snakeclist(int x, int y, int side, snakeclist* prev, snakeclist* next);
	/* destructor */
	~snakeclist();
};

/* snakeplane: playing field for snake */
class snakeplane
{
private:
	/* update the side if the snake ran over */
	void chgside (int &nx, int &ny, int &ns, short &ndir);
	/* kill an item */
	void killcell (snakecell sc);
#if 0
	/* get extremities */
	void getbounds(int &xmin, int &xmax, int &ymin, int &ymax, int side);
#endif
	
public:
	/* what is at each spot? */
	short grid[BOARDWIDTH+3][BOARDWIDTH+3][6+3];

	/* locations of all the foods */
	snakeclist * foods;
	/* locations of all extras */
	snakeclist * extras;
	/* locations of all poisons */
	snakeclist * poisons;
	/* locations of all the extra lives */
	snakeclist * lives;

	/* get what's at cell sc */
	short getcell (snakecell sc);
	/* set what's at cell sc */
	void setcell (snakecell,short);

	/* move snake forward, do bounds checking */
	int nextcell(snake *);

	/* constructor */
	snakeplane();
	/* destructor */
	~snakeplane();
};

class snake
{
private:
	/* the length of the snake */
	int length();
public:
	/* the linked list of cells in the snake */
	snakeclist * cells;
	/* first cell in the snake */
	snakeclist * last;
	/* amount left to grow */
	int nibble;
	/* 1: up
	   2: left
	   3: down
	   4: right
	   direction we're going */
	short direction;
	/* steer in direction d */
	short steer(short d);

	/* kill the snake - new one starts on start. */
	void kill(snakecell start);
	/* eat one */
	void eat();
	/* poisoned! */
	void poison();

	/* constructor */
	snake();
	/* constructor takes starting cell, and length to grow to */
	snake(snakecell sc, int length);
	/* destructor */
	~snake();
};

/* snakegfx: displays graphics. extend this! */
class snakegfx
{
public:
	/* initialize gfx */
	virtual void init();
	/* render the whole field. override me */
	virtual void renderplane(snakeplane* sp, snake* s);

	/* rotate the cube to a given side */
	void rotatecube(int dir);

	/* constructor */
	snakegfx();
	/* destructor */
	virtual ~snakegfx();
};

class snakeplayer
{
public:
	int score;
	int lives;
};

/* the controls... one can be an ai? extend me for human input and ai. */
class snakectl
{
public:
	/* initialize ctls */
	virtual void initctl();
	/* poll for input. returns 1 if there is input waiting. */
	virtual int pollinput();
	/* get the move made. returns a direction like shown earlier. */
	virtual int getinput();
	/* are we an ai? (do we need to display this?) */
	virtual int isai();

	/* constructor */
	snakectl();
	/* destructor */
	virtual ~snakectl();
};

/* and finally... the game! */
class snakegame
{
	friend void snakeup();
	friend void main(int argc, char** argv);
private:
	/* take an action based on a collision */
	void playeract(int movestat, int player);
	/* kill off player */
	void endgame(int player);
	/* get a starting location */
	snakecell startloc(int player);
	/* a random delay counter */
	int count;
	/* change items */
	
	/* update (call once per frame) */
	void update();
	/* redraw screen (call to draw a frame) */
	void redraw();

public:
	void addrand();
	/* stop yet? */
	int stop;
	/* paused ! */
	int pause;
	/* the playing field */
	snakeplane* plane;
	/* number of snakes on the field */
	int nsnakes;
	/* snakes */
	snake** snakes;
	/* control object */
	snakectl** ctls;
	/* score+lives */
	snakeplayer* players[30];
	/* graphics object */
	snakegfx *gfx;
	
	/* initialize objects, call before running anything else! */
	void init();

	/* MAIN LOOP */
	void mainloop();

	/* constructor */
	snakegame();
	/* constructor */
	snakegame(int nsnakes);
	/* destructor */
	~snakegame();
};

#endif