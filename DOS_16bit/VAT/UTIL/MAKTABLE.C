#include <stdio.h>
#include <conio.h>
#include "svgacc.h"
																/* function prototpes */

t[2][2] = {{0,1},{2,3}};

main()
{
	int i,j,k;
	int a[256][64];
	int mouse,videocard,vmode;
	RGB palette[256];
	float f;

	videocard = whichvga();           // Initialize graphics
	res800();                         // Select 800x600x256 resolution.


	drwbox(SET,8,0,0,maxx,maxy);
	for(i = maxy; i > 0; i -=60) drwline(SET,8,0,i,maxx,i);

	for(i = 0; i < 64; i++) {
		f = 1.0/((8.0-i/8.0)*0.6+0.3);
		drwpoint(SET,14,(i+1)* 12,maxy-f*60.0);
	}


	getch();


	restext();
	exit(1);
	for(j =0; j < 256; j++) {
		for(i = 0; i < 64; i++) {
			f = 1.0/((8.0-i/8.0)*0.2+0.1) - 0.588;
			a[j][i] = f * (j-127);
		}
	}

	printf("SHORT vtable[256][64]= {\n");
	for(i = 0; i < 256; i++) {
		printf("\t{");
		for(j = 0; j < 63; j++) {
			if(wherex()>74) printf("\n\t ");
			printf("%d,",a[i][j]);
		}
		printf("%d}",a[i][63]);
		if(i < 255) printf(",");
		printf("\n");
	}
	printf("}\n");

}
