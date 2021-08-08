#include <stdio.h>
#include <mem.h>
#include "flabber.h"
#include "\watcom\gug\lib1\gug.h"      // Load the GUG definitions etc
#include "\watcom\gug\lib1\colors.h"
#include "\watcom\gug\lib1\keydefs.h"
#include "\watcom\vat\vat.h"
#include <math.h>
#include "util.h"

#define fsin(X) sin((X/180.0)*3.141592)

Palette animpal[16][256];
Palette randompal[16];

/**************************************************************************
	void palbox(int x,int y)

	DESCRIPTION:  Draws the palette box with all 256 colors

**************************************************************************/
void palbox(int x,int y)
{
	int i;
																	// draw the colors
	for(i=0; i < 256; i++)
		GUGFillRectangle((i%32)*3+x,(i/32)*3+y,(i%32)*3+3+x,(i/32)*3+3+y,i);
																	// Draw a frame
	GUGRectangle(x-1,y-1,32*3+1+x,8*3+1+y,63);

}

/*************************************************************************
	setcol(p,r,g,b);

	DESCRIPTION: mmacro for setting rgb values

****************************************************************************/
void setcol(Palette *p,int r, int g, int b)
{
	p->r = r;
	p->b = b;
	p->g = g;
}


/**************************************************************************
	void dopalette(int t)

	DESCRIPTION:

**************************************************************************/
void dopalette(int t)
{
	int i;


	t = t%16;
														 // Do the random palette
	for(i = 0; i < 16; i++) {
		randompal[i].r = randompal[i+1].r;
		randompal[i].g = randompal[i+1].g;
		randompal[i].b = randompal[i+1].b;

	}

	randompal[15].r = random(64);
	randompal[15].g = random(64);
	randompal[15].b = random(64);

	memcpy(&(animpal[t][144]),randompal,sizeof(Palette)*16);
															// Actually set the palette
	GUGSetPalette((char *)animpal[t]);

}
/*************************************************************************
	setuppalette();

	DESCRIPTION: animates the palette

****************************************************************************/
void setuppalette()
{
	int i,j,k,l=1,t;
	double a,a2,a3,b,c,c2;
	Palette *p;
	double PR = 9;

	for(t = 0; t< 16; t++) {
		p = animpal[t];
																				// Set up different palette regions

		if(giWhitePalette) {
			for(i = 0; i < 8; i++) {
				setcol(&p[7-i],i*PR,63,63);
				setcol(&p[7-i+8],i*PR,i*PR,63);
				setcol(&p[7-i+16],63,i*PR,63);
				setcol(&p[7-i+24],63,i*PR,i*PR);
				setcol(&p[7-i+32],63,63,i*PR);
				setcol(&p[7-i+40],i*PR,63,i*PR);
			}
		}
		else {
			for(i = 0; i < 8; i++) {
				setcol(&p[i],i*PR,0,0);
				setcol(&p[i+8],i*PR,i*PR,0);
				setcol(&p[i+16],0,i*PR,0);
				setcol(&p[i+24],0,i*PR,i*PR);
				setcol(&p[i+32],0,0,i*PR);
				setcol(&p[i+40],i*PR,0,i*PR);
			}
		}
																				// Grayscale palette
		for(i=0; i < 16; i++) {
			if(giWhitePalette) {
				p[15-i+48].r = i*4.2;
				p[15-i+48].g = i*4.2;
				p[15-i+48].b = i*4.2;
			}
			else {
				p[i+48].r = i*4.2;
				p[i+48].g = i*4.2;
				p[i+48].b = i*4.2;
			}
		}
																				// Animated Palettes
		if((t/16)%2) l = -1;
		for(i = 0; i < 16; i++){
			a = ((t+i)%16)/16.0 * 360;
			b = ((t*l+i)%16)/16.0 * 360;
			c = ((-t+i)%16)/16.0 * 360;
			k = (t+i)%16;
			j = (t+i+8)%16;
			setcol(&(p[64+i]),k*3,0,k*2);
			setcol(&(p[80+i]),0,j*3.8,k*3.8);
			setcol(&(p[96+i]),32+31*fsin(a),32+31*fsin(a),0);
			setcol(&(p[112+i]),0,0,32+31*fsin(b));

			a2 = a*2+50;
			a3 = a*4+100;
			setcol(&(p[128+i]),32+31*fsin(a),32+31*fsin(a2),32+31*fsin(a3));
			p[144+i].r = p[144+i+1].r;
			p[144+i].g = p[144+i+1].g;
			p[144+i].b = p[144+i+1].b;

			if(i == t % 16) setcol(&(p[160+i]),255,0,0);
			else setcol(&(p[160+i]),0,0,0);

			setcol(&(p[176+i]),0,32+31*fsin(a),0);
			setcol(&(p[192+i]),32+31*fsin(a+50),32+31*fsin(a),32+31*fsin(a+100));
			setcol(&(p[208+i]),32+31*fsin(100-c*2),16+15*fsin(100-a),32+31*fsin(100-a));

			c2 = c+300;
			setcol(&(p[224+i]),32+31*fsin(c2),16+15*fsin(c2),0);

																			// "Invisible" palette
			if(giWhitePalette) setcol(&p[i+240],63,63,63);
			else setcol(&p[i+240],0,0,0);
		}
		p[144+15].r = random(64);
		p[144+15].g = random(64);
		p[144+15].b = random(64);
	}


	GUGSetPalette((char *)animpal[0]);
}
