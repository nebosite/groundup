#include <stdio.h>
#include <conio.h>
#include "svgacc.h"
#include "vatfree.h"

int player(char*);

																/* function prototpes */


void main(int argc, char* argv[])
{
	int videocard,vmode;
	RGB palette[256];
	int i;

	videocard = whichvga();           // Initialize graphics
	res320();                         // Select 800x600x256 resolution.

	for(i = 0; i < 16; i++){
		palette[16+i].r = 0;
		palette[16+i].g = 0;
		palette[16+i].b = i*4;

		palette[32+i].r = i*4;
		palette[32+i].g = 0;
		palette[32+i].b = 63;

		palette[48+i].r = 63;
		palette[48+i].g = 0;
		palette[48+i].b = (15-i)*4;

		palette[64+i].r = 63;
		palette[64+i].g = i*4;
		palette[64+i].b = 0;
	}
	palset(palette,16,16+128);

/*	for(i = 0 ; i < 256; i++) {
		drwline(SET,i,i,0,i,10);
	}
	getch(); */

	if(SBSetUp()) {
		SetSampleRate(44000);
		GoVarmint();

		player(argv[1]);

		DropDeadVarmint();
		SBCleanUp();
	}

	restext();
}
