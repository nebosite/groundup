#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "svgacc.h"
#include "math.h"
#include "fourier.h"
#include <time.h>

#define ASIZE 1024
																/* function prototpes */
void dotest(void);
signed int data[10000];
signed int ddata[ASIZE];
double outdata[ASIZE],outidata[ASIZE];

main()
{
	int mouse,videocard,vmode;
	RGB palette[256];

	videocard = whichvga();           // Initialize graphics
	res320();                         // Select 800x600x256 resolution.
	dotest();

	//restext();
}


/**************************************************************************
	void dotest(void)

	DESCRIPTION:  Performs the fast fourier test

**************************************************************************/
void dotest(void)
{
	double period,angle;
	int i,j,skip;
	int num=100;
	long t;
	char str[100];

	skip = 10000/ASIZE;

	angle = 0;
	for(i = 0; i < 10000; i++) {
		data[i] = 100 * cos(angle);
		angle += M_PI/20000.0 * 3520;
		//angle += random(1000)/5000.0;
	}
	for(i = 0; i < 10000; i++) {
		data[i] += 100 * cos(angle);
		angle += M_PI/20000.0 * 1760;
		//angle += random(1000)/5000.0;
	}
	for(i = 0; i < 10000; i++) {
		data[i] += 100 * cos(angle);
		angle += M_PI/20000.0 * 880;
		//angle += random(1000)/5000.0;
	}
	for(i = 0; i < 10000; i++) {
		data[i] += 100 * cos(angle);
		angle += M_PI/20000.0 * 440;
		//angle += random(1000)/5000.0;
	}
	for(i = 0; i < 10000; i++) {
		data[i] += 100 * cos(angle);
		angle += M_PI/20000.0 * 220;
		//angle += random(1000)/5000.0;
	}
	for(i = 0; i < 10000; i++) {
		data[i] += 100 * cos(angle);
		angle += M_PI/20000.0 * 110;
		//angle += random(1000)/5000.0;
	}
	for(i = 0; i < 10000; i++) {
		data[i] += 100 * cos(angle);
		angle += M_PI/20000.0 * 55;
		//angle += random(1000)/5000.0;
	}

	for(i = 0; i < ASIZE; i++) {
		ddata[i] = data[i*skip];
	}
	t = clock();
	for(j = 0; j < num; j++) {

		fft_double ( ASIZE,ddata,NULL,outdata,outidata);
		//drwfillbox(SET,0,0,0,maxx,maxy);
		for(i = 1; i < ASIZE/2; i++) {
			drwline(SET,j%14+1,i/2,199-fabs(outdata[i]/100.0)
												,(i-1)/2,199-fabs(outdata[i-1])/100.0);
		}
	}
	t = clock() - t;
	sprintf(str,"%lf ",(double)num/(t/18.2));
	drwstring(SET,0,15,str,10,10);
	getch();

}