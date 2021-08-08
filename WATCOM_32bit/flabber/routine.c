// ROUTINE.C
//
// Definitions for CRoutine-based classes

#define TRUE 1

#include <time.h>
#include "\watcom\gug\lib1\gug.h"
#include "\watcom\gug\lib1\colors.h"
#include "\watcom\gug\lib1\keydefs.h"
#include "\watcom\vat\vat.h"
#include "routine.h"
#include "flabber.h"
#include "util.h"
#include "math.h"


#define NUMFWCOLORS 7

const int SMOKECOLOR = 0;
const int MAXFIREWORKS = 10;
const float GRAVITY = .002;
const float AIRRESISTANCE = .999;
int CFireWorkDraw::iNumFireworks = 0;
int CBounceDraw::iNumBalls = 0;

int giFWColor[NUMFWCOLORS][100];
int giFWColorsSet = FALSE;



/**************************************************************************
	void CBounceDraw::draw(void)

	DESCRIPTION:  Bouncing Ball

**************************************************************************/
int CBounceDraw::draw(void)
{
	int i,j;
																		// Initilize mortar round
	if(!started) {
		started = TRUE;
		framecount = giDrawFrameCount;
		vp.y1 = 0;
		vp.dx = random(1000)/200.0 -2.5;
		vp.dy = 0;
		vp.r = giBrushSize;
		gravity = (random(30)+5)/ 25.0;
		bounciness = random(400)/1000.0 + 0.5;
		iNumBalls++;
																		// Draw original ball
		if(!giEggMe) GUGDrawFillCircle(XOR,vp.color,vp.x1,vp.y1,vp.r);
		else GUGPutXORFGSprite(vp.x1-flabbersprite[11]->width/2,
													 vp.y1-flabbersprite[11]->height/2,
													 (char *)flabbersprite[11]);
	}
																		// Animate only when there's a new frame
	if(framecount == giDrawFrameCount) return TRUE;
	framecount = giDrawFrameCount;
																		// Erase old ball
	if(!giEggMe) GUGDrawFillCircle(XOR,vp.color,vp.x1,vp.y1,vp.r);
	else GUGPutXORFGSprite(vp.x1-flabbersprite[11]->width/2,
												 vp.y1-flabbersprite[11]->height/2,
												 (char *)flabbersprite[11]);

																		// Move it over
	vp.x1 += vp.dx;
	if(vp.x1 < vp.r) {
		vp.x1 = vp.r;
		vp.dx *= -1;
	}
	if(vp.x1 > maxx-vp.r) {
		vp.x1 = maxx-vp.r;
		vp.dx *= -1;
	}
																		// bounce it
	vp.y1 += vp.dy;
	if(vp.y1 > (int)(maxy - vp.r)) {
		dosound2(60,vp.dy*10,.95 + random(100)/1000.0);
		vp.y1 = (int)(maxy - vp.r);
		vp.dy *= -bounciness;
		if(vp.dy > -gravity) {
			if(!giEggMe) GUGDrawFillCircle(SET,vp.color,vp.x1,vp.y1,vp.r);
			else GUGPutFGSprite(vp.x1-flabbersprite[11]->width/2,
														 vp.y1-flabbersprite[11]->height/2,
														 (char *)flabbersprite[11]);
			iNumBalls--;
			return 0;
		}
	}
	vp.dy += gravity;
																		// Draw new position
	if(!giEggMe) GUGDrawFillCircle(XOR,vp.color,vp.x1,vp.y1,vp.r);
	else GUGPutXORFGSprite(vp.x1-flabbersprite[11]->width/2,
												 vp.y1-flabbersprite[11]->height/2,
												 (char *)flabbersprite[11]);


	return TRUE;
}


/**************************************************************************
	void CSpiralDraw::draw(void)

	DESCRIPTION:  Draw a random spiral

**************************************************************************/
int CSpiralDraw::draw(void)
{
	int x,y,t;

	if(!started) {
		dr = random(100)/1000.0 + 0.005;
		dt = random(1000)/100.0 - 5;
		radius = 0;
		theta = random(360);
		vp.x2 = vp.x1;
		vp.y2 = vp.y1;
		counter = 0;
		started = TRUE;
	}


	counter++;
	radius += dr;
	theta += dt;
	if(theta < 0) theta += 3600;
	t = theta;
	x = vp.x1 + radius * getcos(t);
	y = vp.y1 + radius * getsin(t);
	GUGDrawLine(SET,vp.colorbase+counter%16,vp.x2,vp.y2,x,y);
	vp.x2 = x;
	vp.y2 = y;

	if(radius > maxx) return FALSE;
	else return TRUE;
}

/**************************************************************************
	void rdraw1(int width, int x1, int y1, int angle)

	DESCRIPTION: Recursive draw for Treedraw

**************************************************************************/
void rdraw1(int width, int x1, int y1, int angle)
{
	int length,x,y,i,colorbase;

	length = (width*10*(random(80)+40))/100;
																			// Calculate where the branch goes
																			// Draw the branch
	for(i = 0; i < length; i++) {
		x = x1 + (i+1) * getcos(angle);
		y = y1 + (i+1) * getsin(angle);
		GUGDrawCircle(SET,3,x,y,width);
		x = x1 + (i) * getcos(angle);
		y = y1 + (i) * getsin(angle);
		GUGDrawCircle(SET,5,x,y,width-1);
	}
	width--;
																			// Draw a leaf if we are done,
																			// otherwise make more branches,
	if(!width) {
		colorbase = (giWorkingColor/16)*16;

//		for(i = 0; i < 3; i++) GUGDrawFillCircle(SET,random(16)+colorbase,x+random(10)-5,y+random(10)-5,2);
		GUGDrawFillCircle(SET,random(16)+colorbase,x,y,2);
	}
	else {
		for(i = 0; i < 6; i++) rdraw1(random(width)+1,x,y,angle + random(140)-70);
	}


}

/**************************************************************************
	void CBallDraw::draw(void)

	DESCRIPTION:  Ball bouncer (more like an argyle pattern)

**************************************************************************/
int CBallDraw::draw(void)
{

	int i;

	if(!started) {
		t = 0;
		started = TRUE;
		vp.x1 = random(maxx);
		vp.y1 = random(maxy);
		vp.dx = random(2);
		vp.dy = random(2);
		if(vp.dx < 0.5) vp.dx = -1;
		if(vp.dy < 0.5) vp.dy = -1;
		vp.w = 4;
		counter = 10;
	}

																		// Animate only when there's a new frame
	if(t == giDrawFrameCount) return TRUE;
	t = giDrawFrameCount;

	for(i = 0; i < 200; i++) {

		GUGDrawFillCircle(SET,vp.color,vp.x1,vp.y1,vp.w);

		vp.x1 += vp.dx;
		if(vp.x1 <vp.w || vp.x1 > (maxx-vp.w)) {
			counter --;
			vp.dx = -vp.dx;
		}
		vp.y1 += vp.dy;
		if(vp.y1 < vp.w || vp.y1 > (maxy-vp.w)) {
			counter--;
			vp.dy = -vp.dy;
		}
		if(counter <0) counter = 0;
	}

	return counter;
}

/**************************************************************************
	void CFireWorkDraw::stage1(void)

	DESCRIPTION:  Launch Routine

**************************************************************************/
void CFireWorkDraw::stage1(void)
{
	int i;

	for(i = 0; i < numactive; i++) {
		GUGDrawPoint(SET,SMOKECOLOR,x[i],y[i]);
		x[i] += xm[i];
		y[i] += ym[i];
		xm[i] *= AIRRESISTANCE;
		ym[i] *= AIRRESISTANCE;
		ym[i] += GRAVITY;


		switch(type) {
		default:
			GUGDrawPoint(SET,scolor[i],x[i],y[i]);
			break;
		}
	}

	if(ym[0] > -.1) {
		if(!random(80) || ym[0] > 3.0) {
			stage++;
			dosound2(33,80,0.8 + (double)random(400)/1000.0,30 + (((double)x[0]-160.0)*20)/160.0 );
		}
	}
}

/**************************************************************************
	void CFireWorkDraw::stage2(void)

	DESCRIPTION:  Explode Routine

**************************************************************************/
void CFireWorkDraw::stage2(void)
{
	int i,j,c,ang;
	float mag;

	switch(type) {
	case 0:
	default:
		numactive = 100;
		c = random(NUMFWCOLORS);
		scount[0] = 0;
		for(i = 1 ; i < numactive; i++) {
			scolor[i] = c;
			sswitch[i] = 0;
			scount[i] = random(100) + 1000;
			x[i] = x[0];
			y[i] = y[0];
			ang = random(360);
			mag = 0.5- fabs(random(5000)/10000.0 + random(5000)/10000.0 - 0.5);
			xm[i] = xm[0] + mag * getcos(ang);
			ym[i] = ym[0] + mag * getsin(ang);
		}
		for(j = 0; j < 10; j++) nextcolor[j] = random(NUMFWCOLORS);

		break;

	}
	stage++;
}

/**************************************************************************
	void CFireWorkDraw::stage3(void)

	DESCRIPTION:  Fade routine

**************************************************************************/
void CFireWorkDraw::stage3(void)
{
	int i,j,numdrawn= 0,c;

	for(i = 0; i < numactive; i++) {
		if(!scount[i]) continue;
		numdrawn++;

		GUGDrawPoint(SET,SMOKECOLOR,x[i],y[i]);
		x[i] += xm[i];
		y[i] += ym[i];
		xm[i] *= AIRRESISTANCE;
		ym[i] *= AIRRESISTANCE;
		ym[i] += GRAVITY;


		switch(type) {
		case 0:                          // Standard
			j = (1000-scount[i])/10;
			if(j < 0) j = 0;
			if(j > 99) j = 99;

			c = giFWColor[scolor[i]][j];
			GUGDrawPoint(SET,c,x[i],y[i]);
			scount[i]-= 6;
			if(scount[i] < 0) scount[i] = 0;
			break;
		case 1:                          // Oooo-Ahhh.
			j = (1000-scount[i])/10;
			if(j < 0) j = 0;
			if(j > 99) j = 99;

			c = giFWColor[scolor[i]][j];
			GUGDrawPoint(SET,c,x[i],y[i]);
			scount[i]-= 12;
			if(scount[i] < 0) {
				sswitch[i]++;
				if(sswitch[i] == 2) scount[i] = 0;
				else {
					scolor[i] = nextcolor[0];
					scount[i] = 940;
				}
			}
			break;
		case 2:                          // Twinkler.
			j = (1000-scount[i])/10;
			if(j < 0) j = 0;
			if(j > 99) j = 99;

			c = giFWColor[scolor[i]][j];
			GUGDrawPoint(SET,c,x[i],y[i]);

			if(sswitch[i]== 0) scount[i]-= 15;
			else {
				scount[i] -= 80;
				if(!random(10)) scount[i] = 1;
			}

			if(scount[i] < 0) {
				sswitch[i]++;
				if(sswitch[i] == 10) scount[i] = 0;
				else {
					if(scolor[i] == 6) scolor[i] = nextcolor[0];
					else scolor[i] = 6;
					scount[i] = 940;
				}
			}
			break;
		}
	}

	if(!numdrawn) stage++;
}



/**************************************************************************
	void setfwcolors(void)

	DESCRIPTION: Sets up the colors for the fireworks


**************************************************************************/
void setfwcolors(void)
{
	int i,j;
															 // Give all colors a bright start
	for(i = 0; i < 4; i++) {
		for(j = 0 ; j < NUMFWCOLORS; j++) {
			giFWColor[j][i] = 63-i*4;
		}
	}
															 // Standard "Straight" Colors  0-6
	for(i = 4; i < 100; i++) {
		for(j = 0 ; j < 6; j++) {
			giFWColor[j][i] = j*8+7 - (i/100.0) * 7;
		}
		giFWColor[6][i] = 63 - (i/100.0) * 15;
	}

	giFWColorsSet = TRUE;

}

/**************************************************************************
	void CFireWorkDraw::draw(void)

	DESCRIPTION:  Firework drawing routine

**************************************************************************/
int CFireWorkDraw::draw(void)
{
	int i,j;
																		// Initilize mortar round
	if(!started) {
		if(!giFWColorsSet) setfwcolors();
		type = random(3);
		started = TRUE;
		framecount = giDrawFrameCount;
		numactive = 1;
		xm[0] = (random(100)-50)/200.0;
		ym[0] = -0.8 - random(100)/500.0;
		x[0] = vp.x1;
		y[0] = maxy;
		scolor[0] = 7;
		stage = 1;
		iNumFireworks++;
	}
																		// Animate only when there's a new frame
	if(framecount == giDrawFrameCount) return TRUE;
	framecount = giDrawFrameCount;
																		// Draw miniframes
	for(i = 0; i < 6; i++) {
		if		 (stage == 1) stage1();
		else if(stage == 2) stage2();
		else if(stage == 3) stage3();
		else if(stage == 4) {
			iNumFireworks--;
			return 0;
		}
	}


	return TRUE;
}
/**************************************************************************
	void CTreeDraw::draw(void)

	DESCRIPTION:  Fractal Tree generator

**************************************************************************/
int CTreeDraw::draw(void)
{

	if(!started) {
		width = 5;
		angle = random(360);
		started = TRUE;
	}

	for(int i = 0; i < 6; i++) rdraw1(random(3)+2,vp.x1,vp.y1,i*60 + random(15)+angle);

	return 0;
}
/**************************************************************************
	void CBoxesDraw::draw(void)

	DESCRIPTION:

**************************************************************************/
int CBoxesDraw::draw(void)
{
	int c;

	if(!started) {
		counter = random(140)+10;
		started = TRUE;
	}

	c = colorcounter%16+vp.colorbase;
	GUGDrawRectangle(SET,c,vp.x1-vp.w/2,
												 vp.y1-vp.h/2,
												 vp.x1+vp.w/2,
												 vp.y1+vp.h/2);
	colorcounter += vp.d1;
	vp.w-= 2*vp.d2;
	vp.h-= 2*vp.d3;

	return counter--;
}

/**************************************************************************
	void CCoinDraw::draw(void)

	DESCRIPTION:

**************************************************************************/
int CCoinDraw::draw(void)
{

	if(!started) {
		counter = 50;
		started = TRUE;
	}

	GUGDrawFillCircle(SET,colorcounter%16+vp.colorbase,
										vp.x1+vp.w*(counter/50.0),
										vp.y1+vp.h*(counter/50.0),
										vp.r/10+5);
	colorcounter += vp.d1;

	return counter--;
}

/**************************************************************************
	void CTargetDraw::draw(void)

	DESCRIPTION:

**************************************************************************/
int CTargetDraw::draw(void)
{

	if(!started) {
		counter = vp.r;
		started = TRUE;
	}

	GUGDrawFillCircle(SET,colorcounter%16+vp.colorbase,vp.x1,vp.y1,counter);
	colorcounter += vp.d1;
	counter -=2;
	if(counter < 0) counter = 0;

	return counter;
}
/**************************************************************************
	void CSpiralBarDraw::draw(void)

	DESCRIPTION:

**************************************************************************/
int CSpiralBarDraw::draw(void)
{

	if(!started) {
		counter = 150 + random(100);
		angle = random(360);
		started = TRUE;
	}

	colorcounter += vp.d1;
	vp.x2 = vp.x1 + (vp.w/2) * getcos(counter+angle);
	vp.y2 = vp.y1 + (vp.w/2) * getsin(counter+angle);
	vp.x3 = vp.x1 + (vp.h/2) * getcos(counter+angle);
	vp.y3 = vp.y1 + (vp.h/2) * getsin(counter+angle);
	GUGDrawLine(SET,colorcounter%16+vp.colorbase,vp.x2  ,vp.y2  ,vp.x3  ,vp.y3);
	GUGDrawLine(SET,colorcounter%16+vp.colorbase,vp.x2+1,vp.y2  ,vp.x3+1,vp.y3);
	GUGDrawLine(SET,colorcounter%16+vp.colorbase,vp.x2-1,vp.y2  ,vp.x3-1,vp.y3);
	GUGDrawLine(SET,colorcounter%16+vp.colorbase,vp.x2  ,vp.y2+1,vp.x3  ,vp.y3+1);
	GUGDrawLine(SET,colorcounter%16+vp.colorbase,vp.x2  ,vp.y2-1,vp.x3  ,vp.y3-1);
	vp.x1 +=vp.dx/10;
	vp.y1 +=vp.dy/10;

	return counter--;
}

/**************************************************************************
	void CStarBurstDraw::draw(void)

	DESCRIPTION:  Draw a radiating starburst

**************************************************************************/
int CStarBurstDraw::draw(void)
{
	int k;
	double lx,ly,dx,dy;

	if(!started) {
		counter = 50;
		started = TRUE;
	}

	lx = vp.x1;
	ly = vp.y1;
	k = random(360);
	dx = fpFastCos[k];
	dy = fpFastSin[k];
	while(lx < maxx+1 && lx > 0 && ly < maxy+1 && ly > 0) {
		colorcounter += vp.d1;
		GUGDrawPoint(SET,vp.colorbase+colorcounter%16,lx,ly);
		lx += dx;
		ly += dy;
	}

	return counter--;
}

/**************************************************************************
	void CConeDraw::draw(void)

	DESCRIPTION:

**************************************************************************/
int CConeDraw::draw(void)
{
	if(!started) {
		counter = vp.r/2;
		started = TRUE;
	}

	for(int i = 0; i < frames_per_draw  && counter > 0; i++,counter--) {
		colorcounter += vp.d1;
		GUGDrawFillCircle(SET,colorcounter%16+vp.colorbase,vp.x1,vp.y1,counter);
		vp.x1 += vp.dx/2.0;
		vp.y1 += vp.dy/2.0;
	}

	return counter;
}

/********************************************************************
	sint CCheckerBall::draw()


	DESCRIPTION: Draws a 3-D checkered Ball

*********************************************************************/
int CCheckerBall::draw()
{
	int i,j,x,y,yy,q,cs,h,color,ymod;
	double cx,cy,r = vp.r;
	int 		x1 = vp.x1,
					y1 = vp.y1;


	if(!started) {
		started = TRUE;
		color1 = random(8)*8;             // Pick colors and rotation
		color2 = random(8)*8;
		k = random(6);
	}


																		// Draw the ball.  This routine acts like
																		//	 a hacked ray tracer.  It basically
																		//	 fills in a circle and calculates where
																		//	 each pixel would actually fall on
																		//	 a sphere, then extracts spherical
																		//	 coordinates to determine the color.
	i = counter;

	yy = r/2-i;
	cs = yy/(r/2.0) * 8192;
	q = getarccos(cs);
//	q = acos(yy/(r/2.0));
	cy= (double)q/180.0;      			// canonical spherical coordinate
	y = cy*1000;              			// spherical coordinate
	ymod = (y/120)%2;
																	// h = # of pixels on scan line
	h = sqrt((double)(r/2*r/2) - ((r/2)-i)*((r/2)-i));
	for(j = 0; j< 2*h; j++) {  			// pixel loop
		cx = (double)(h-j)/h;
		q = getarccos((int)(cx*8192));
//		q = acos(cx);
		cx = (double)q/180.0; 				// canonical spherical coordinate
		x = cx*1000 + k* 40;  				// spherical coordiante
																	// generate checker pattern
		q = (ymod ^ ((x/120)%2));
		//if(ymod ^ ((x/120)%2)) q = 1;
		//else q = 0;
																	// the highlight is located at cononical
																	// coordinates (0.4 , 0.4). The color
																	// selected is based on the distance from
																	// this spot.  It is an artificial means
																	// of generating highlights and shading,
																	// but it is quick and looks super!
//			color = 63-80*sqrt((cx-0.4)*(cx-0.4)+(cy-0.4)*(cy-0.4)) + q*64;
		color = 8-11*sqrt((cx-0.4)*(cx-0.4)+(cy-0.4)*(cy-0.4));
		if(color >7) color = 7;
		if(q) color += color1;
		else color += color2;
		GUGDrawPoint(SET,color,x1-h+j,i+y1-r/2);  /* draw it! */
	}

	counter++;
	if(counter > r) return 0;
	else return 1;
}
