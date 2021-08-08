//
// Resize a rectangle
//  Source and Destination are both in BUFFER memory
//
#include "vga.h"
#include "mode.h"

void  gug_stretch(int,int,int,int,int,int);
#define sign(x) ((x)>0 ? 1:-1)

void GUGResizeRectangle(int xs1,int ys1,int xs2,int ys2,int xd1,int yd1,int xd2,int yd2)
{
	int dx,dy,e,d,dx2;
	int sx,sy;
	dx=abs(yd2-yd1);
	dy=abs(ys2-ys1);
	sx=sign(yd2-yd1);
	sy=sign(ys2-ys1);
	e=(dy<<1)-dx;
	dx2=dx<<1;
	dy<<=1;

	for(d=0;d<=dx;d++)
	{
		gug_stretch(xd1,xd2,xs1,xs2,ys1,yd1);
		while(e>=0)
		{
			ys1+=sy;
			e-=dx2;
		}
		yd1+=sx;
		e+=dy;
	}
}

void gug_stretch(int x1,int x2,int y1,int y2,int yr,int yw)
{
	int  dx,dy,e,d,dx2;
    int  sx,sy,color;
    char *vga_mem;

	dx=abs(x2-x1);
	dy=abs(y2-y1);
	sx=sign(x2-x1);
	sy=sign(y2-y1);
	e=(dy<<1)-dx;
	dx2=dx<<1;
	dy<<=1;

	for(d=0;d<=dx;d++)
	{

//		color = GUGGetPixel(y1,yr);
        vga_mem  = (char *)VGA_START + y1 + (yr * X_WRAP_SIZE); // point to the pixel
        color = *vga_mem;

//		GUGSetPixel(x1,yw,color);
        vga_mem  = (char *)VGA_START + x1 + (yw * X_WRAP_SIZE); // point to the pixel
        *vga_mem = color;

		while(e>=0)
		{
			y1+=sy;
			e-=dx2;
		}
		x1+=sx;
		e+=dy;
	}
}

