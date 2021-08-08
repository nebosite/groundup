#include "tetris.h"

#define NUMDOTS 50

typedef struct dot {
	int x,y;
	int ym;
	BYTE c;

} DOT;


int voidcolor = 1;

/**************************************************************************
	void newdot(DOT *d)

	DESCRIPTION:

**************************************************************************/
void newdot(DOT *d)
{
	d->x = random(800) + (maxx-800)/2;
	d->y = 135;
	d->ym = -1;
}


/**************************************************************************
	void movedot(DOT *d)

	DESCRIPTION:

**************************************************************************/
void movedot(DOT *d)
{
	drwpoint(SET,0,d->x,d->y);        // Erase old point;

																		 // move up or down
	d->y = d->y+d->ym;

	if(d->ym < 0) {                    // moving up?
																		 // reach the top?
		if(d->y < 0) {
			d->ym = 1;
			d->c = voidcolor;
			return;
		}
																		 // Find a point? Let's go down!
		d->c = getpoint(d->x,d->y);
		if(d->c) {
			d->ym = 1;
			return;
		}

		return;
	}


	if(d->y == maxy-1) {               // Hit the bottom?
		drwpoint(SET,d->c,d->x,d->y);
		d->ym = 0;
		return;
	}

	if(!getpoint(d->x,d->y+1)) {        // nothing below?
		drwpoint(SET,d->c,d->x,d->y);
		return;
	}
																			// solid surface?
	if(getpoint(d->x+1,d->y+1) && getpoint(d->x-1,d->y+1)) {
		drwpoint(SET,d->c,d->x,d->y);
		d->ym = 0;
		return;
	}
																			// Roll off somewhere
	if(random(2)) {                     // Maybe try to yhe left
		if(!getpoint(d->x-1,d->y+1) && !getpoint(d->x-1,d->y)) {
			d->x--;
			if(d->x < 0) {
				d->x = 0;
				drwpoint(SET,d->c,d->x,d->y);
				d->ym = 0;
				return;
			}
			drwpoint(SET,d->c,d->x,d->y);
			return;
		}
	}
																		 // Try to the right
	if(!getpoint(d->x+1,d->y+1) && !getpoint(d->x+1,d->y)) {
		d->x++;
		if(d->x > maxx-1) {
			d->x = maxx-1;
			drwpoint(SET,d->c,d->x,d->y);
			d->ym = 0;
			return;
		}
		drwpoint(SET,d->c,d->x,d->y);
		return;
	}
																		 // Try to te left
	if(!getpoint(d->x-1,d->y+1) && !getpoint(d->x-1,d->y)) {
		d->x--;
		if(d->x < 0) {
			d->x = 0;
			drwpoint(SET,d->c,d->x,d->y);
			d->ym = 0;
			return;
		}
		drwpoint(SET,d->c,d->x,d->y);
		return;
	}

																		 // npwhere to go.  Just stick it.
	drwpoint(SET,d->c,d->x,d->y);
	d->ym = 0;


}

/**************************************************************************
	void egg2(void)

	DESCRIPTION:

**************************************************************************/
void egg2(void)
{
	static DOT d[NUMDOTS];
	static int test=0;
	int i;

																 // voidcolor is what comes off the top.
	if(random(20000) == 22) voidcolor = random(215);

	if(!test) {                    // initial condition
		test = 1;
		for(i = 0; i < NUMDOTS; i++ ) d[i].ym = 0;;
	}
																 // fill an empty dot
	for(i = 0; i < NUMDOTS; i++) {
		if(!d[i].ym) {
			newdot(&d[i]);
			break;
		}
	}
																 // animate
	for(i = 0; i < NUMDOTS; i++) {
		if(d[i].ym) movedot(&d[i]);
	}


}