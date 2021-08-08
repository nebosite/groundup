// Mouse action handler for flabbergasted
//
// Author:  Eric Jorgensen

#include "flabber.h"
#include "util.h"
#include "\watcom\gug\lib1\gug.h"
#include "\watcom\gug\lib1\colors.h"
#include "\watcom\gug\lib1\keydefs.h"
#include "\watcom\vat\vat.h"

#define RIGHTMOUSE 2
#define LEFTMOUSE 1


int ox = 0, oy = 0, ob = 0;

/**************************************************************************
	void domouse(int x, int y, int b)

	DESCRIPTION:  Does something with current mouse position.

**************************************************************************/
void domouse(int x, int y, int b)
{
	static int coloroff = 0;
	int i,xx,yy,r,a;

	coloroff++;
	if(coloroff > 15) coloroff = 0;
																		// Right button = grab color
	if(b & RIGHTMOUSE) {
		giWorkingColor = GUGGetPixel(x,y);
																		// Keep track of picked colors
		if(giWorkingColor <64) {
			for(i = 9; i>0; i--) gColorStack[i] = gColorStack[i-1];
			gColorStack[0] = giWorkingColor;
		}
	}
																		// Handle cycling colors
	if (giWorkingColor >= 64) giWorkingColor = (int)(giWorkingColor/16)*16 + coloroff;

	if(b & LEFTMOUSE) {
		switch(giBrushShape) {
		case brush_square:
			GUGDrawFillRectangle(SET,giWorkingColor,x-giBrushSize,y-giBrushSize,x+giBrushSize,y+giBrushSize);
			break;
		case brush_slash:
			GUGDrawLine(SET,giWorkingColor,x-giBrushSize,y+giBrushSize,x+giBrushSize,y-giBrushSize);
			GUGDrawLine(SET,giWorkingColor,x-giBrushSize-1,y+giBrushSize,x+giBrushSize-1,y-giBrushSize);
			GUGDrawLine(SET,giWorkingColor,x-giBrushSize+1,y+giBrushSize,x+giBrushSize+1,y-giBrushSize);
			break;
		case brush_slant:
			GUGDrawLine(SET,giWorkingColor,x-giBrushSize,y-giBrushSize,x+giBrushSize,y+giBrushSize);
			GUGDrawLine(SET,giWorkingColor,x-giBrushSize-1,y-giBrushSize,x+giBrushSize-1,y+giBrushSize);
			GUGDrawLine(SET,giWorkingColor,x-giBrushSize+1,y-giBrushSize,x+giBrushSize+1,y+giBrushSize);
			break;
		case brush_spray:
			r = random(giBrushSize);
			a = random(360);
			xx = fpFastSin[a] * r;
			yy = fpFastCos[a] * r;
			GUGDrawPoint(SET,giWorkingColor,x+xx,y+yy);
			break;
		case brush_circle:
			GUGDrawFillCircle(SET,giWorkingColor,x,y,giBrushSize);
			break;
		}

	}
															 // Preserve old mouse values
	ox = x;
	oy = y;
	ob = b;

}