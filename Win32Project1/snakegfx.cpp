// snakegfx.cpp
// graphics stuff
#include "stdafx.h"
#include "snake.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
// #define NULL ((void*)0)

snakegfx::snakegfx ()
{
	/*cout << "***WARNING***" << endl;
	cout << "You're not using a real GFX library!" << endl;
	cout << "Perhaps you mean to use one of my child classes?" << endl;
	*/
}

snakegfx::~snakegfx ()
{
}

void snakegfx::init()
{
	/*
	cout << "***WARNING***" << endl;
	cout << "You're not using a real GFX library!" << endl;
	cout << "Perhaps you mean to use one of my child classes?" << endl;
	*/
}

void snakegfx::renderplane(snakeplane *sp, snake* s)
{
	/*
	cout << "***WARNING***" << endl;
	cout << "You're not using a real GFX library!" << endl;
	cout << "Perhaps you mean to use one of my child classes?" << endl;
	*/
	if (sp == NULL)
	{
		cout << "***WARNING***" << endl;
		cout << "Snakeplane is NULL." << endl;
		cout << "Perhaps you aren't playing the game yet?" << endl;
	}
}