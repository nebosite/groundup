//
// Resize a sprite into a new sprite and return the new sprite handle
//
#include "stdio.h"
#include "malloc.h"
#include "mode.h"

void  gug_stretch_2(int,int,int,int,int,int);
#define sign(x) ((x)>0 ? 1:-1)

// Globals for this module
char *RSTSfmem;     // From Sprite
int  RSTSfxs,RSTSfys;
char *RSTStmem;		// Too Sprite
int  RSTStxs,RSTStys;
//FILE *DDout;

char *GUGResizeSpriteToSprite(char *fspr,int xd2,int yd2)
{
	int  dx,dy,e,d,dx2;
	int  sx,sy;
    int  xs1,ys1,xs2,ys2;
    int  xd1,yd1;
    char *tspr;

    if (xd2 <   2) return(NULL);
	if (yd2 <   2) return(NULL);
	if (xd2 > 320) return(NULL);
	if (yd2 > 200) return(NULL);

//    DDout = fopen("d.txt","w");

    d = GUGCalcSize(xd2,yd2);

    if ((tspr = malloc(d)) == NULL)
	{
	  return(NULL);
	}

    xd1 = yd1 = xs1 = ys1 = 1;

    RSTSfmem = fspr;                    // Point to source sprite
    RSTSfmem +=   4;                    // Point past size data
    RSTStmem = tspr;					// Point to	destination sprite
	RSTStmem +=   4;                    // Point past size data

 	RSTSfxs = xs2 = GUGSpriteWidth(fspr);
	RSTSfys = ys2 = GUGSpriteHeight(fspr);
    RSTStxs = xd2;
	RSTStys = yd2;

//    fprintf(DDout,"From X:%3d Y:%3d\n",xs2,ys2);
//    fprintf(DDout,"Too  X:%3d Y:%3d Size:%d\n",xd2,yd2,d);

	dx=abs(yd2-yd1);
	dy=abs(ys2-ys1);
	sx=sign(yd2-yd1);
	sy=sign(ys2-ys1);
	e=(dy<<1)-dx;
	dx2=dx<<1;
	dy<<=1;

    if (dx <= 0)
	{
	  free(tspr);
	  return(NULL);
	}

	for(d=0;d<=dx;d++)
	{
		gug_stretch_2(xd1,xd2,xs1,xs2,ys1,yd1);
		while(e>=0)
		{
			ys1+=sy;
			e-=dx2;
		}
		yd1+=sx;
		e+=dy;
	}
    tspr[0] = (char)(xd2 & 0xFF);
	tspr[1] = (char)((xd2 >> 8) & 0xFF);
    tspr[2] = (char)(yd2 & 0xFF);
	tspr[3] = (char)((yd2 >> 8) & 0xFF);

//    fclose(DDout);

    return(tspr);
}

void gug_stretch_2(int x1,int x2,int y1,int y2,int yr,int yw)
{
	int dx,dy,e,d,dx2;
	int sx,sy,color;
	dx=abs(x2-x1);
	dy=abs(y2-y1);
	sx=sign(x2-x1);
	sy=sign(y2-y1);
	e=(dy<<1)-dx;
	dx2=dx<<1;
	dy<<=1;
	for(d=0;d<=dx;d++)
	{
        color = *(RSTSfmem + (((yr-1) * RSTSfxs) + (y1-1)));	// Point to the byte in question
        *(RSTStmem + (((yw-1) * RSTStxs) + (x1-1))) = color;

//    fprintf(DDout,"X1:%3d  Y1:%3d  X2:%3d  Y2:%3d\n",
//            y1-1,yr-1,x1-1,yw-1);

//		  GUGSetPixel(x1,yw,color);
		while(e>=0)
		{
			y1+=sy;
			e-=dx2;
		}
		x1+=sx;
		e+=dy;
	}
}

