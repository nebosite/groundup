//
// ANIMFUNC.C
//
// Animation functions for flabbergasted
//
// Author:  Eric Jorgensen

#include <mem.h>
#include <math.h>
#include "flabber.h"
#include "util.h"
#include "\watcom\gug\lib1\gug.h"
#include "\watcom\gug\lib1\colors.h"
#include "\watcom\gug\lib1\keydefs.h"
#include "\watcom\vat\vat.h"

#define NUMFLAKES 150
#define NUMHOLES 30

#define  M_PI  3.14159265358979323846


typedef struct dot {
	int x,y;
	int ym;
	BYTE c;

} DOT;


int flakecolor = 63;
int fallingspeed = 3;
int diffusionrate = 150;
char *morphtemplate[64000];


char localdata[10][10000];

/**************************************************************************
	void movehole(DOT *d)

	DESCRIPTION:

**************************************************************************/
void movehole(DOT *d)
{
	int nx,ny,c;
	int direction = random(8);

	nx = d->x;
	ny = d->y;
	switch(direction) {
	case 0:                          // left
		nx = d->x-1;
		break;
	case 1:                          // up left
		nx = d->x-1;
		ny = d->y-1;
		break;
	case 2:                          // up
		ny = d->y-1;
		break;
	case 3:                          // up right
		nx = d->x+1;
		ny = d->y-1;
		break;
	case 4:                          // right
		nx = d->x+1;
		break;
	case 5:                          // right down
		nx = d->x+1;
		ny = d->y+1;
		break;
	case 6:                          // down
		ny = d->y+1;
		break;
	case 7:                          // down left
		nx = d->x-1;
		ny = d->y+1;
		break;
	}

	if(nx <0) nx = maxx-1;
	if(ny <0) ny = maxy-1;
	if(nx >= maxx) nx = 0;
	if(ny >= maxy) ny = 0;

	c = GUGGetPixel(nx,ny);
	GUGDrawPoint(SET,c,d->x,d->y);
	GUGDrawPoint(SET,c,nx,ny);
	d->x = nx;
	d->y = ny;

}
/**************************************************************************
	void movedot(DOT *d)

	DESCRIPTION:

**************************************************************************/
void movedot(DOT *d)
{
	GUGDrawPoint(SET,0,d->x,d->y);        // Erase old point;

																		 // move down
	d->y = d->y+d->ym;
	if(d->y < 0) return;

	if(d->y == maxy-1) {               // Hit the bottom?
		GUGDrawPoint(SET,d->c,d->x,d->y);
		d->ym = 0;
		return;
	}

	if(!GUGGetPixel(d->x,d->y+1)) {        // nothing below?
		GUGDrawPoint(SET,d->c,d->x,d->y);
		return;
	}
																			// solid surface?
	if(GUGGetPixel(d->x+1,d->y+1) && GUGGetPixel(d->x-1,d->y+1)) {
		GUGDrawPoint(SET,d->c,d->x,d->y);
		d->ym = 0;
		return;
	}
																			// Roll off somewhere
	if(random(2)) {                     // Maybe try to the left
		if(!GUGGetPixel(d->x-1,d->y+1) && !GUGGetPixel(d->x-1,d->y)) {
			d->x--;
			if(d->x < 0) {
				d->x = 0;
				GUGDrawPoint(SET,d->c,d->x,d->y);
				d->ym = 0;
				return;
			}
			GUGDrawPoint(SET,d->c,d->x,d->y);
			return;
		}
	}
																		 // Try to the right
	if(!GUGGetPixel(d->x+1,d->y+1) && !GUGGetPixel(d->x+1,d->y)) {
		d->x++;
		if(d->x > maxx-1) {
			d->x = maxx-1;
			GUGDrawPoint(SET,d->c,d->x,d->y);
			d->ym = 0;
			return;
		}
		GUGDrawPoint(SET,d->c,d->x,d->y);
		return;
	}
																		 // Try to te left
	if(!GUGGetPixel(d->x-1,d->y+1) && !GUGGetPixel(d->x-1,d->y)) {
		d->x--;
		if(d->x < 0) {
			d->x = 0;
			GUGDrawPoint(SET,d->c,d->x,d->y);
			d->ym = 0;
			return;
		}
		GUGDrawPoint(SET,d->c,d->x,d->y);
		return;
	}

																		 // npwhere to go.  Just stick it.
	GUGDrawPoint(SET,d->c,d->x,d->y);
	d->ym = 0;


}

/**************************************************************************
	void newflake(DOT *d)

	DESCRIPTION:

**************************************************************************/
void newflake(DOT *d)
{
	d->x = random(maxx);
	d->y = -random(30);
	d->c = (BYTE)flakecolor;
	d->ym = 1;
}

/**************************************************************************
	void newhole(DOT *d)

	DESCRIPTION:

**************************************************************************/
void newhole(DOT *d)
{
	d->x = random(maxx);
	d->y = random(maxy);
}


/**************************************************************************
	void linesprite(RasterBlock *sprite)

	DESCRIPTION: Specialized sprite put for the slump function

**************************************************************************/
void linesprite(char *data,int x,int length,int depth = 1)
{
	char *puthere = VGA_START + x + 640*depth;

	while(length--) {
		*puthere = *data++;
		puthere += 640;
	}

}

/**************************************************************************
	void quickslideup(int x, int step)

	DESCRIPTION: Specialized sprite put for the slump function

**************************************************************************/
void quickslidedown(int x, int step)
{
	char *puthere = VGA_START + x + maxy * 640;
	char *getthis = VGA_START + x + (maxy-step) * 640;
	int i = maxy;

	while(i > step) {
		*puthere = *getthis;
		puthere -= 640;
		getthis -= 640;
		i--;
	}

}

/**************************************************************************
	void quickslidedown(int x, int step)

	DESCRIPTION: Specialized sprite put for the slump function

**************************************************************************/
void quickslideup(int x, int step)
{
	char *puthere = VGA_START + x;
	char *getthis = VGA_START + x + step * 640;
	int i = step;

	while(i < maxy) {
		*puthere = *getthis;
		puthere += 640;
		getthis += 640;
		i++;
	}

}

/**************************************************************************
	int getangleindex(int x1, int y1, int x2, int y2,int divisions)


  DESCRIPTION: This function returns the indexed angle that represents
  						 the direction from one object to another.

               getangleindex() assumes standard video coodinates, ie:
               0,0 is at the top left of the screen.  It also assumes
               That and angle of zero points directly to the right.

  INPUTS:

  	x1,y1				Coodinates of pointing object
    x2,y2				Coodinates of target object
    divisions   Number of angular divisions in the circle.

  RETURNS:

  	Angle value in the range of 0 to divisions-1.

**************************************************************************/
int getangleindex(int x1, int y1, int x2, int y2,int divisions)
{
	double dx,dy,angle;

	dx = x1-x2;                         // Calculate side of a right triangle
	dy = y1-y2;

  if(!dx && !dy) return(0);

  angle = atan2(dy,dx);               // Calculate the angle.  atan2 is a
                                      // Special trig function that works
                                      // even if the arguments are zero.

																			// Send back result
	return (int)( (angle+M_PI)/(M_PI*2.0) * divisions) % divisions;
}


/**************************************************************************
	char *vgaspot(int x, int y)

	DESCRIPTION:  Returns the pointer to a particular spot in the
								vga prep buffer

**************************************************************************/
char *vgaspot(int x, int y)
{
	return VGA_START + x + y*640;
}


/**************************************************************************
	char *neighborspot(int x, int y, int d)

	DESCRIPTION:  Return the pointer to a neighbor spot in the
								vga prep buffer

**************************************************************************/
char *neighborspot(int x, int y, int d)
{
	switch(d) {
	case 0:                   	// Left
		return vgaspot(x-1,y);
	case 1:                     // up left
		return vgaspot(x-1,y-1);
	case 2:                     // up
		return vgaspot(x,y-1);
	case 3:                     // up right
		return vgaspot(x+1,y-1);
	case 4:                     // right
		return vgaspot(x+1,y);
	case 5:                     // right down
		return vgaspot(x+1,y+1);
	case 6:                     // down
		return vgaspot(x,y+1);
	case 7:                     // down left
		return vgaspot(x-1,y+1);
	default:                    // Stay the same
		return vgaspot(x,y);
	}

}

/**************************************************************************
	void animation11(void)

	DESCRIPTION:  Vortex

**************************************************************************/
int animation11(int signal)
{
	int x,y,x2,y2,index,ierror,d,rotation,angle,angle2,n;
	int cx,cy,r;
	static char *data,**vspot;
	double warp,threshhold;

															// Create the morph template
	if(signal == signal_start) {
		cx = random(320);
		cy = random(200);
		rotation = random(2);
		if(!rotation) rotation = -1;
		warp = 1.0;
		threshhold = 500.0;

		for(x = 0; x < maxx; x++) {
			for(y = 0; y < maxy; y++) {
				r = sqrt((x-cx)*(x-cx) + (y-cy)*(y-cy));
				angle = getangleindex(cx,cy,x,y,360);
				angle2 = angle+warp/(r/threshhold);
				r+=2;

				x2 = cx + r * getcos(angle2);
				x2 = (x2+3200) % maxx;
				y2 = cy + r * getsin(angle2);
				y2 = (y2+2000) % maxy;

				morphtemplate[x+y*maxx] = vgaspot(x2,y2);
			}
		}
															// set up workspace
		grbWorkSpace->width = (short int)maxx;
		grbWorkSpace->height =  (short int)maxy;
		return 0;
	}
	data = grbWorkSpace->data;
	vspot = morphtemplate;
															// process the array into the workspace
	for(y = 0; y < maxy; y++) {
		for(x = 0; x < maxx; x++,data++,vspot++) {
			*data = *(*vspot);
			//(*data)--;
			//if((*data) == 0xff) *data = 0;
		}
	}


	GUGPutBGSprite(0,0,(char *)grbWorkSpace);       // draw the sucker;
	return 1;
}
/**************************************************************************
	void animation10(void)

	DESCRIPTION:  Hyper-Vortex

**************************************************************************/
int animation10(int signal)
{
	int x,y,index,ierror,d,rotation;
	static char *data,**vspot;

															// Create the morph template
	if(signal == signal_start) {
		rotation = random(360);
		for(x = 0; x < maxx; x++) {
			for(y = 0; y < maxy; y++) {
				index = getangleindex(160,100,x,y,360) +rotation + ierror;
				while(index < 0) index += 360;
				while(index >= 360) index -= 360;
				d = ((index)%360)/45;
				ierror = index - d*45;
//				if(x ==0 || y == 0 || x == maxx-1 || y == maxy-1) d = 8;
				morphtemplate[x+y*maxx] = neighborspot(x,y,d);
			}
		}
															// set up workspace
		grbWorkSpace->width = (short int)maxx;
		grbWorkSpace->height =  (short int)maxy;
		return 0;
	}
	data = grbWorkSpace->data;
	vspot = morphtemplate;
															// process the array into the workspace
	for(y = 0; y < maxy; y++) {
		for(x = 0; x < maxx; x++,data++,vspot++) {
			*data = *(*vspot);
			//(*data)--;
			//if((*data) == 0xff) *data = 0;
		}
	}


	GUGPutBGSprite(0,0,(char *)grbWorkSpace);       // draw the sucker;
	return 1;
}

/**************************************************************************
	void animation9(void)

	DESCRIPTION:  Crazy effect

**************************************************************************/
int animation9(int signal)
{
	int i,x,y,d;
	static char *data,**vspot;
														 // Create the morph template
	if(signal == signal_start) {
		for(x = 0; x < maxx; x++) {
			for(y = 0; y < maxy; y++) {
				d = random(8);
				morphtemplate[x+y*maxx] = neighborspot(x,y,d);
			}
		}
														 // set up workspace
		grbWorkSpace->width = (short int)maxx;
		grbWorkSpace->height =  (short int)maxy;
		return 0;
	}
	data = grbWorkSpace->data;
	vspot = morphtemplate;
														 // process the array into the workspace
	for(y = 0; y < maxy; y++) {
		for(x = 0; x < maxx; x++,data++,vspot++) {
			*data = *(*vspot);
			(*data)--;
			if((*data) == 0xff) *data = 0;
		}
	}
														 // Continue to rnadomize template
	for(i = 0; i < 100; i++) {
		x = random(320);
		y = random(200);
		d = random(8);
		morphtemplate[x+y*maxx] = neighborspot(x,y,d);
	}

	GUGPutBGSprite(0,0,(char *)grbWorkSpace);       // draw the sucker;
	return 1;
}


/**************************************************************************
	void animation7(void)

	DESCRIPTION:  Standard blur of the whole screen. (non-center weighted)

**************************************************************************/
int animation7(int signal)
{
	int i,y;
//  int x,bgcolor;
	char *setme;
	char *dt[3],*dtemp,*dataup,*datadown,*data;
//	char *wtemp;
	char *d1,*d2,*d3;
	RasterBlock *rb[3],*rtemp;
	int iTotal;


	if(signal == signal_start) return 0;

																	// set up workspace
	grbWorkSpace->width = (short int)maxx;
	grbWorkSpace->height =  (short int)maxy;

	for(i = 0; i < 3; i++) {
		rb[i] = grbTemp[i];
		dt[i] = rb[i]->data;
	}

																	// loop over rows
	for(y = 0; y < maxy; y++) {

		if(y == 0) {                  // initialize first row
			memset(dt[1],0,maxx);
			GUGBlockGet(0,0,maxx-1,0,rb[2]);
		}
																	// Shift, then get next row down
		dtemp = dt[0];
		rtemp = rb[0];

		dt[0] = dt[1];
		rb[0] = rb[1];

		dt[1] = dt[2];
		rb[1] = rb[2];

		dt[2] = dtemp;
		rb[2] = rtemp;

		if(y != maxy-1) GUGBlockGet(0,y+1,maxx-1,y+1,rb[2]);
		else memset(dt[2],0,maxx);

		dataup = dt[0];
		data = dt[1];
		datadown = dt[2];
																	// Blur Each point
		d1 = dataup;
		d2 = data;
		d3 = datadown;
		for(i = 0,setme = grbWorkSpace->data + y*(maxx);
				i < maxx;
				i++,setme++,d1++,d2++,d3++) {

			iTotal = 0;
//			iTotal += *(d1-1) + *(d1) + *(d1+1);
//			iTotal += *(d2-1) +  *(d2+1);
//			iTotal += *(d3-1) + *(d3) + *(d3+1);
			iTotal +=  *(d1);
			iTotal += *(d2-1) +  (*d2)*28 +  *(d2+1);
			iTotal +=  *(d3) ;

			*(setme) = (char)(iTotal>>5);
		}


	}

	GUGPutBGSprite(0,0,(char *)grbWorkSpace);       // draw the sucker;
	return 1;
}

/**************************************************************************
	int animation6(int signal)

	DESCRIPTION: Diffusion

**************************************************************************/
int animation6(int signal)
{
	static DOT d[NUMHOLES];
//	static int test=0;
	int i,j;

	if(signal == signal_start) {
		for(i = 0; i < NUMHOLES; i++) {
			newhole(&(d[i]));
		}
		return 0;
	}

																 // animate
	for(j = 0 ; j < diffusionrate; j++) {
		for(i = 0; i < NUMHOLES; i++) {
			movehole(&d[i]);
		}
	}
	return 0;
}

/**************************************************************************
	void animation5(void)

	DESCRIPTION: Slides alternate lines

**************************************************************************/
int animation5(int signal)
{
	RasterBlock *slice= (RasterBlock *)localdata[0];
	int x,y;
	static int direction = 0;

	if(signal == signal_start) {
		direction = random(2);
		return 0;
	}

	switch(direction) {
		case 0:							// Slide up/down
			for(x = 0; x< maxx; x+=2) {
				quickslideup(x,1);
				quickslidedown(x+1,1);
			}
		break;
		case 1:							// Slide right/left
			for(y = 0; y< maxy; y+=2) {
				GUGBlockGet(0,y,maxx-1,y,grbWorkSpace);
				GUGPutBGSprite(-1,y,(char *)grbWorkSpace);

				GUGBlockGet(0,y+1,maxx-1,y+1,grbWorkSpace);
				GUGPutBGSprite(1,y+1,(char *)grbWorkSpace);
			}
		break;
	}

	return 0;
}

/**************************************************************************
	int animation4(int signal)

	DESCRIPTION:  Snow!

**************************************************************************/
int animation4(int signal)
{
	static DOT d[NUMFLAKES];
	int i,j;

	if(signal == signal_start) {
		for(i = 0; i < NUMFLAKES; i++) {
			newflake(&(d[i]));
			d[i].y = -random(200);
		}
		flakecolor = random(64);
		while((flakecolor%8)<3) flakecolor = random(64);
		return 0;
	}

																 // voidcolor is what comes off the top.
	if(!random(2000)) {
		flakecolor = random(64);
		while((flakecolor%8)<3) flakecolor = random(64);
	}

																 // fill an empty flake
	for(i = 0; i < NUMFLAKES; i++) {
		if(!d[i].ym) newflake(&d[i]);
	}
																 // animate
	for(j = 0 ; j < fallingspeed; j++) {
		for(i = 0; i < NUMFLAKES; i++) {
			if(d[i].ym) movedot(&d[i]);
		}
	}
	return 0;
}
/**************************************************************************
	void animation3(void)

	DESCRIPTION: Slides screen over some random direction

**************************************************************************/
int animation3(int signal)
{
	RasterBlock *slice= (RasterBlock *)localdata[0];
//	char *data;
//	int pcolor[256];
	static int direction = 0;

	if(signal == signal_start) {
		direction = random(8);
		return 0;
	}

	switch(direction) {
		case 0:							// Slide left
			GUGBlockGet(0,0,maxx-1,maxy-1,grbWorkSpace);
			GUGPutBGSprite(-1,0,(char *)grbWorkSpace);
		break;
		case 1:							// Slide left up
			GUGBlockGet(0,0,maxx-1,maxy-1,grbWorkSpace);
			GUGPutBGSprite(-1,-1,(char *)grbWorkSpace);
		break;
		case 2:							// Slide up
			GUGBlockGet(0,0,maxx-1,maxy-1,grbWorkSpace);
			GUGPutBGSprite(0,-1,(char *)grbWorkSpace);
		break;
		case 3:							// Slide up right
			GUGBlockGet(0,0,maxx-1,maxy-1,grbWorkSpace);
			GUGPutBGSprite(1,-1,(char *)grbWorkSpace);
		break;
		case 4:							// Slide right
			GUGBlockGet(0,0,maxx-1,maxy-1,grbWorkSpace);
			GUGPutBGSprite(1,0,(char *)grbWorkSpace);
		break;
		case 5:							// Slide right down
			GUGBlockGet(0,0,maxx-1,maxy-1,grbWorkSpace);
			GUGPutBGSprite(1,1,(char *)grbWorkSpace);
		break;
		case 6:							// Slide down
			GUGBlockGet(0,0,maxx-1,maxy-1,grbWorkSpace);
			GUGPutBGSprite(0,1,(char *)grbWorkSpace);
		break;
		case 7:							// Slide left down
			GUGBlockGet(0,0,maxx-1,maxy-1,grbWorkSpace);
			GUGPutBGSprite(-1,1,(char *)grbWorkSpace);
		break;

	}

	return 0;
}

/**************************************************************************
	void animation2(void)

	DESCRIPTION: Slumps the whole screen like in scorched Earth

**************************************************************************/
int animation2(int signal)
{
	RasterBlock *slice= (RasterBlock *)localdata[0];
	char *data;
	int pcolor[256];
	int i,x,y;

	if(signal == signal_start) return 0;

	GUGGetPalette((char *)palette);
																 // Rectify Palette intensities
	for(i = 0; i < 256; i++) {
		pcolor[i] = palette[i].r + palette[i].g + palette[i].b;
		if(pcolor[i] < 8) pcolor[i] = 0;
	}
																 // Loop by collums of the screen
	for(x = 0; x < maxx; x++) {
		GUGBlockGet(x,0,x,maxy,slice);
		data = slice->data + 199;
																 // Look for a blank spot
		for(y = 199; y> 0 && pcolor[*data--]; y--);
		if(y<2) continue;
		for(i = 1; y>0 && !pcolor[*data--] && i< 4; i++,y--);
		if(y< 2) continue;
																 // move stuff down
		slice->height = (short int)y;
//		GUGPutBGSprite(x,1,(char *)slice);
		linesprite(slice->data,x,y,i);
		GUGDrawLine(SET,0,x,0,x,i);
	}

	return 0;
}

/**************************************************************************
	void animation1(void)

	DESCRIPTION:  Performs game of life on whole screen

**************************************************************************/
int animation1(int signal)
{
	int i,y,nb[400],*neighbors;
//  int x,bgcolor;
	char st[400],*setme;
	char *dt[3],*dtemp,*wtemp,*dataup,*datadown,*data;
	RasterBlock *rb[3],*rtemp;


	if(signal == signal_start) return 0;

																	// set up workspace
	grbWorkSpace->width = (short int)maxx;
	grbWorkSpace->height =  (short int)maxy;

	for(i = 0; i < 3; i++) {
		rb[i] = grbTemp[i];
		dt[i] = rb[i]->data;
	}

																	// loop over rows
	for(y = 0; y < maxy; y++) {

		if(y == 0) {                  // initialize first row
			memset(dt[1],0,maxx);
			GUGBlockGet(0,0,maxx-1,0,rb[2]);
		}
																	// Shift, then get next row down
		dtemp = dt[0];
		rtemp = rb[0];

		dt[0] = dt[1];
		rb[0] = rb[1];

		dt[1] = dt[2];
		rb[1] = rb[2];

		dt[2] = dtemp;
		rb[2] = rtemp;

		if(y != maxy-1) GUGBlockGet(0,y+1,maxx-1,y+1,rb[2]);
		else memset(dt[2],0,maxx);

		dataup = dt[0];
		data = dt[1];
		datadown = dt[2];
																	// Count neighbors
		memset(nb,0,330 * sizeof(int));
		for(i = 0, neighbors  = nb+1,setme = st+1;
				i < maxx;
				i++, neighbors++,setme++) {

			if(*(dataup+i)){
				(*(neighbors-1))++;
				(*(neighbors))++;
				(*(neighbors+1))++;
				*(setme-1) = *(setme)= *(setme+1) = *(dataup+i);
			}
			if(*(data+i)){
				(*(neighbors-1))++;
				(*(neighbors+1))++;
				*(setme-1) = *(setme+1) = *(data+i);
			}
			if(*(datadown+i)){
				(*(neighbors-1))++;
				(*(neighbors))++;
				(*(neighbors+1))++;
				*(setme-1) = *(setme)= *(setme+1) = *(datadown+i);
			}
		}

																	 // set the row
		dtemp = grbWorkSpace->data + y*(maxx);
		wtemp = data;
		setme = st+1;
		for(i = 0, neighbors  = nb+1; i <= maxx; i++, neighbors++) {

			switch(*neighbors) {
			case 2:                      // stay alive
				*(dtemp + i) = *(wtemp+i);
				break;
			case 3:                      // stay alive or new birth
				if(!*(wtemp+i)) *(dtemp + i) = *(setme+i);
				else *(dtemp + i) = *(wtemp+i);
				break;
			case 0:                      // Die die die!!!
			case 1:
			default:
				*(dtemp+i) = 0;
				break;
			}

			// ECODE this one makes a neat edge effect!!!
			//*(dtemp+i) =nb[i+1];
			//*(dtemp+i) =*(wtemp+i);
		}
	}

	GUGPutBGSprite(0,0,(char *)grbWorkSpace);       // draw the sucker;
	return 1;
}