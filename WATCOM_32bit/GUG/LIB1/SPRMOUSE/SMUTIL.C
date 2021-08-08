//**************************************************************************
// This function Draws the mouse cursor to VGA only
//

#include "..\vga\vga.h"
#include "..\vga\mode.h"
#include "..\gug.h"

char background[16000];
int giDrawCalled = 0;
int lastx,lasty;


/**************************************************************************
	void GUGSMDraw(int xb,int yb)

	DESCRIPTION: Put a sprite and keep it's background

**************************************************************************/
void GUGSMDraw(int xb,int yb)
{
	int width,height,adjusted_width;
	int xstart,xend;
	int ystart,yend;
	int x,y,i;
	char *data,*writespot,*bgspot;

	giDrawCalled = 0;
																	// Get dimensions on the sprite
	width = *((short int *)GUG_Sprite_Mouse);
	height = *((short int *)(GUG_Sprite_Mouse+2));

	memcpy(background,GUG_Sprite_Mouse,4);       // Give background sprite the same dimensions

	if(width*height > 15900) return;// Too big?

	giDrawCalled = 1;
	lastx = xb;
	lasty = yb;


	xstart = ystart = 0;
	xend = width;
	yend = height;

																	// Clip it to the screen
	if(xb < 0) xstart = -xb;
	if(xb+width >= MAX_X_SIZE) xend =  - (xb - MAX_X_SIZE);
	adjusted_width = xend-xstart;

	if(yb < 0) ystart = -yb;
	if(yb+width >= MAX_Y_SIZE) yend =  - (yb - MAX_Y_SIZE);

																	// draw it
	for(y = ystart; y < yend; y++) {
																				// Set pointers
		data = GUG_Sprite_Mouse+4 + y*width + xstart;
		writespot = VGA_START + (y+yb) * X_WRAP_SIZE + xb + xstart;
		bgspot = background+4 + y*width + xstart;

																				// GO through a line of pixels
		for(i = 0; i < adjusted_width; i++) {
			*bgspot = *writespot;
			if(*data) *writespot = *data;
			data++;
			writespot++;
			bgspot++;
		}
	}




}

/**************************************************************************
	void GUGSMUnDraw(void)

	DESCRIPTION: Put a sprite's background back in place

**************************************************************************/
void GUGSMUnDraw(void)
{
	int width,height,adjusted_width;
	int xstart,xend;
	int ystart,yend;
	int x,y,i;
	char *data,*writespot,*bgspot;
																	// protect ourselves from called this
																	// Function first
	if(!giDrawCalled) return;

																	// Get dimensions on the sprite
	width = *((short int *)background);
	height = *((short int *)(background+2));


	xstart = ystart = 0;
	xend = width;
	yend = height;

	//width=16;
	//height = 16;

																	// Clip it to the screen
	if(lastx < 0) xstart = -lastx;
	if(lastx+width >= MAX_X_SIZE) xend =  - (lastx - MAX_X_SIZE);
	adjusted_width = xend-xstart;

	if(lasty < 0) ystart = -lasty;
	if(lasty+width >= MAX_Y_SIZE) yend =  - (lasty - MAX_Y_SIZE);

																	// draw it
	for(y = ystart; y < yend; y++) {
																				// Set pointers
		data = background+4 + y*width + xstart;
		writespot = VGA_START + (y+lasty) * X_WRAP_SIZE + lastx + xstart;

																				// GO through a line of pixels
		for(i = 0; i < adjusted_width; i++) {
			*writespot = *data;         // Note: not transparent!
			data++;
			writespot++;
		}
	}
}



