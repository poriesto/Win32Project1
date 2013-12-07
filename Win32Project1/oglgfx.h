#include "snake.h"
#include <stdio.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/glut.h"
#include <windows.h>
#include <math.h>
#include <windows.h>
#include <GL/gl.h>

#define SWAPBUFFERS SwapBuffers(ghDC)
#define WIDTH 300
#define HEIGHT 200

#define WINDOW_STYLE WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN

extern char szAppName[];

void FindSnake(GLdouble &nx, GLdouble &ny, GLdouble &nz);

class oglgfx : public snakegfx, public snakectl
{
	friend void drawScene(void);
	friend void drawSceneU(void);
	friend void processNormalKeys(unsigned char key, int x, int y);
	friend void processSpecialKeys(int key, int x, int y);
	friend void PutMiniCube(int x, int y, int p);
	friend void polarView(GLdouble radius);

private:

	int keypress;
	int speed;

//	HWND ghWnd;
//	HDC ghDC;
//	HGLRC ghRC;

	/* Window procedure ! ! ! */

	GLfloat angle;
	GLdouble radius;

	GLfloat curlng;
	GLfloat curlat;
	GLfloat deslng;
	GLfloat deslat;

	/* Draw a cube */
	GLvoid resize(GLsizei,GLsizei);
	void polarView(GLdouble);
	void createObjects();
	
public:

	int pollinput();
	int getinput();
	int isai();

	//.void __cdecl processSpecialKeys(int key, int x, int y);

	/* initialize gfx */
	virtual void init(int argc, char **argv);

	/* render the whole field. override me */
	virtual void renderplane(snakeplane* sp, snake *s);

	/* rotate the cube to a given side */
	void rotatecube(int side);

	/* constructor */
	oglgfx();
	/* destructor */
	virtual ~oglgfx();
};

