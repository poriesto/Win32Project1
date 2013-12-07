// kbdctl.cpp: implementation of the kbdctl class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "kbdctl.h"
#include <conio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

kbdctl::kbdctl()
{
	/* nothing here either */
}

kbdctl::~kbdctl()
{
	/* nothing to do here */
}

int kbdctl::isai()
{
	return 0;
}

void kbdctl::init()
{
	while (_kbhit())
		_getch();
}

int kbdctl::pollinput()
{
	return (_kbhit());
}

int kbdctl::getinput()
{
	switch (_getch())
	{
		case '2':
			return 1;

		case '4':
			return 2;

		case '8':
			return 3;

		case '6':
			return 4;

		case 'q':
		case 'Q':
			return STOPKEY;

		default:
			return 0;
	}
}
