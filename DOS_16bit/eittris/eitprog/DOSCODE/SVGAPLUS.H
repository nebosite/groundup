/*************************************************************************
	SVGAPLUS.h

	This is the header for extra functions to suppllement the SVGA
		library SVGACC.

	Written By: Eric Jorgensen (1994)
**************************************************************************/

#include "svgacc.h"
#include <stdio.h>
#include <math.h>
#include <dos.h>
#include <string.h>
#include <conio.h>

#define TAB 5
#define TRUE 1
#define FALSE 0

void 	setcol(RGB *p,int r, int g, int b);
void 	print(PixelMode pmode, int color, int x, int y, char *s, ...);
void 	drwchar(PixelMode pmode, int color, int x, int y, char c);
int 	textheight(char *string);
int 	textwidth(char *string);
int   scanconvertpoly(int color, int points, D2Point poly[]);
void getinput(int x,int y,int fc,int bc,char *prompt,char *string,int maxlength);
char inkey(void);

                             // Define these funcs elsewhere
extern Font SVGAfont;
extern byte far *fontpointer;
extern int fontseg, fontoff;
extern int Tab;
extern D2Point *sortpt;
extern int assume_nocross;


/* typedef struct  {
	int i;
	double x,dx;
} Edge;*/
typedef struct  {
	int i;
	long int x,dx;
} Edge;





