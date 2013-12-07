// kbdctl.h: interface for the kbdctl class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _KBDCTL_H
#define _KBDCTL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "snake.h"

class kbdctl : public snakectl  
{
public:
	/* initialize ctls */
	void init();
	/* poll for input. returns 1 if there is input waiting. */
	int pollinput();
	/* get the move made. returns a direction like shown earlier. */
	int getinput();
	/* are we an ai? (do we need to display this?) */
	int isai();

	kbdctl();
	virtual ~kbdctl();

};

#endif // ifndef _KBDCTL_H
