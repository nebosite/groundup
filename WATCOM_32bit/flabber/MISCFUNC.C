#include <mem.h>
#include "flabber.h"
#include "math.h"
#include "util.h"
#include "\watcom\gug\lib1\gug.h"



inline int getpixel(int x,int y) { return *(VGA_START+x+y*640);}
inline void setpixel(int x,int y,int c) { *(VGA_START+x+y*640)=c;}

int plasmaspace[65000];
int plasmawidth;
int plasmaheight;
int factor = 32;

																/* function prototpes */
void plasma(int x1, int y1, int w, int h);
char gcTyperArray[256];



/**************************************************************************
	void colorup(void)

	DESCRIPTION: Moves all the colors in the screen up by 1

**************************************************************************/
void colorup(void)
{
	char *vgaspot;
	int x,y;

	for(y = 0; y < maxy; y++) {
		vgaspot = VGA_START + y*640;
		for(x = 0; x < maxx; x++,vgaspot++){
			(*vgaspot)++;
		}
	}
}

/**************************************************************************
	void colordown(void)

	DESCRIPTION: Moves all the colors in the screen up by 1

**************************************************************************/
void colordown(void)
{
	char *vgaspot;
	int x,y;

	for(y = 0; y < maxy; y++) {
		vgaspot = VGA_START + y*640;
		for(x = 0; x < maxx; x++,vgaspot++){
			(*vgaspot)--;
		}
	}
}

/**************************************************************************
	void typer(char c)

	DESCRIPTION:  Handles typing

**************************************************************************/
void typer(char c)
{
	static int x,y;
	static int position = 0;
	static int cursor_on = 0;
	static int cursor_count = 0;
	int pt;

	if(c == 0) {             			// Finished.  Clean up
		if(cursor_on) {             // Turn off cursor
			cursor_on ^= 1;
			GUGDrawFillRectangle(XOR,63,x,y,x+6,y+8);
		}
	}
	else if(c == 1) {        			// Start Fresh
		x = gfprealmousex;
		y = gfprealmousey;
		position = 0;
	}
	else if(c == 2) {							// Flash cursor
		if(cursor_count++ > 2) {
			cursor_count = 0;
			cursor_on ^= 1;
			GUGDrawFillRectangle(XOR,63,x,y,x+6,y+8);
		}
	}
	else {                        // Regular typeing

		if(cursor_on) {             // Turn off cursor
			cursor_on ^= 1;
			GUGDrawFillRectangle(XOR,63,x,y,x+6,y+8);
		}

		pt = giPrintTransparent;    // Make sure we print transparently
		giPrintTransparent = TRUE;

		gcTyperArray[position] = c; // Record the letter in the buffer
		position ++;
		if(position > 255) {
			position = 255;
			memcpy(gcTyperArray,gcTyperArray+1,255);
		}
																// print it!
		print(SET,giWorkingColor,0,x,y,"%c",c);

		x = giPrintX;               // Move the cursor
		if(x > maxx-10) {
			x = 0;
			y += 12;
		}
		else y = giPrintY;
																// Handle newline
		if(c == '\n') position = 0;
																// Restore state
		giPrintTransparent = pt;
	}

	gcTyperArray[position] = 0;   // Make sure array is null terminated
}

/**************************************************************************
	int autobrush3(int signal)


	DESCRIPTION: Moire Pattern Brush

**************************************************************************/
int autobrush3(int signal)
{
	static int coloroff = 0,x,y,c2,stage,cx,cy,linenum;
	int cl,i;
	coloroff++;
	if(coloroff > 15) coloroff = 0;
																		// Handle cycling colors
	cl = giWorkingColor;
	if (giWorkingColor >= 64) cl = (int)(giWorkingColor/16)*16 + coloroff;

	if(signal == signal_start) {
		c2=random(64);
		x = 0;
		y = 0;
		cx = random(maxx);
		cy = random(maxy);
		linenum = stage = 0;
		return 0;
	}

	for(i = 0; i < 5; i++) {
		if(linenum % 2) GUGDrawLine(SET,cl,cx,cy,x,y);
		else GUGDrawLine(SET,c2,cx,cy,x,y);

		switch(stage%4) {
		case 0:
			x++;
			if(x == maxx-1) stage++;
			break;
		case 1:
			y++;
			if(y == maxy-1) stage++;
			break;
		case 2:
			x--;
			if(x == 0) stage++;
			break;
		case 3:
			y--;
			if(y == 0) stage++;
			break;

		}
		linenum++;
	}

	return 0;

}


/**************************************************************************
	void bnwrect(int x1,int y1, int x2, int y2)

	DESCRIPTION: Converts a rectangel to Black and White

**************************************************************************/
void bnwrect(int x1,int y1, int x2, int y2)
{
	int i,size;
	char *data;
	int pcolor[256];

	GUGGetPalette((char *)palette);
																 // Rectify Palette intensities
	for(i = 0; i < 256; i++) {
		pcolor[i] =
			((palette[i].r*3 + palette[i].g*3 + palette[i].b * 4) * 16)/640+48;
		if(pcolor[i] < 8) pcolor[i] = 0;
	}
																 // Get our workspace
	size = (x2-x1+1) *(y2-y1+1);
	GUGBlockGet(x1,y1,x2,y2,grbWorkSpace);
																 // Process it
	data = grbWorkSpace->data;
	for(i = 0; i < size; i++) {
		*data = pcolor[*data];
		data++;
	}

	GUGPutBGSprite(x1,y1,(char *)grbWorkSpace);
}






/**************************************************************************
	void doplasma(int x1, int y1, int w, int h)

	DESCRIPTION:

**************************************************************************/
void doplasma(int x1, int y1, int w, int h, int colorbase)
{
	char *vidspot;
	int *dataspot;
	int i,j;

	memset(plasmaspace,0,65000 * sizeof(int));

	plasmawidth = w+1;
	plasmaheight = h+1;

	plasmaspace[0] 					= random(8000)+16000;
	plasmaspace[w] 					= random(8000)+16000;
	plasmaspace[h*(w+1)] 		= random(8000)+16000;
	plasmaspace[w+h*(w+1)] 	= random(8000)+16000;

	plasma(0,0,w,h);

	dataspot = plasmaspace;
	for(j = 0; j <= h; j++) {
		vidspot = VGA_START + x1 + (y1+j)*640;
		for(i = 0; i <= w; i++,vidspot++,dataspot++) {
			*vidspot = ((*dataspot)>>7)%16 + colorbase;
		}
	}
}

/**************************************************************************
	void plasma(int x1, int y1, int w, int h)

	DESCRIPTION: Generates a plasma field based on midpoint algorythm

**************************************************************************/
void plasma(int x1, int y1, int w, int h)
{
	int x2,y2,x3,y3,nw,nh;
	int ph[5],h1,h2,h3,h4;
	int *data1,*data2,*data3;


	nw = w/2;
	nh = h/2;
	x2 = x1 + nw;
	y2 = y1 + nh;
	x3 = x1+w;
	y3 = y1+h;

	data1 = plasmaspace + y1 * plasmawidth;
	data2 = plasmaspace + y2 * plasmawidth;
	data3 = plasmaspace + y3 * plasmawidth;

																 // Get data from height field
	h1 = *(data1+x1); //getpixel(x1,y1);
	h2 = *(data1+x3); //getpixel(x3,y1);
	h3 = *(data3+x1); //getpixel(x1,y3);
	h4 = *(data3+x3); //getpixel(x3,y3);

																	 // plot new points if empty
	ph[0] = (h1+h2)/2 + random(w*factor) - w*factor/2;
	ph[1] = (h1+h3)/2 + random(h*factor) - h*factor/2;
	ph[3] = (h2+h4)/2 + random(h*factor) - h*factor/2;
	ph[4] = (h3+h4)/2 + random(w*factor) - w*factor/2;
	ph[2] = (h1+h2+h3+h4)/4;

	if(!*(data1+x2)) *(data1+x2) = ph[0]; //setpixel(x2,y1,ph[0]);
	if(!*(data2+x1)) *(data2+x1) = ph[1]; //setpixel(x1,y2,ph[1]);
	if(!*(data2+x2)) *(data2+x2) = ph[2]; // setpixel(x2,y2,ph[2]);
	if(!*(data2+x3)) *(data2+x3) = ph[3]; //setpixel(x3,y2,ph[3]);
	if(!*(data3+x2)) *(data3+x2) = ph[4]; //setpixel(x2,y3,ph[4]);


																	// recurse to smaller squares
	if(nw     > 1 || nh     > 1) plasma(x1,y1,nw,nh);    		// quad1
	if((w-nw) > 1 || nh     > 1) plasma(x2,y1,w-nw,nh);    	// quad2
	if(nw     > 1 || (h-nh) > 1) plasma(x1,y2,nw,h-nh);    	// quad3
	if((w-nw) > 1 || (h-nh) > 1) plasma(x2,y2,w-nw,h-nh);   // quad4

}