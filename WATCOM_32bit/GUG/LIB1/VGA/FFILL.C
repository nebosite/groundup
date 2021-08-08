#include "vga.h"
#include "mode.h"

int fillcolor= 0;
int newcolor = 0;


/**************************************************************************
	void GUGFloodFillColor(int point_x, int point_y, int color)

	DESCRIPTION: Fill a color with a new color

**************************************************************************/
void GUGFloodFillColor(int point_x, int point_y, int color)
{
	int GUGGetPixel(int xpos, int ypos);
	void recur_fill2(int px,int py,int c);

	fillcolor = GUGGetPixel(point_x,point_y);
	if(fillcolor == color) return;
	recur_fill2(point_x,point_y,color);
}



/**************************************************************************
	void recur_fill2(int px,int py,int c)

	DESCRIPTION:

**************************************************************************/
void recur_fill2(int px,int py,int c)
{
	char *vga_mem;
	int x,leftx,rightx;

	if (py <   0) return;
	if (py > 199) return;

	vga_mem  = (char *)VGA_START + px + (py * X_WRAP_SIZE); // point to the pixel
	for(x = px; x <= 319 && *vga_mem == fillcolor; x++,vga_mem++) *vga_mem = c;
	rightx = x-1;

	vga_mem  = (char *)VGA_START + px + (py * X_WRAP_SIZE) - 1; // point to the pixel
	for(x = px-1; x >=0 && *vga_mem == fillcolor; x--,vga_mem--) *vga_mem = c;
	leftx = x+1;

	if(py < 199) {
		vga_mem  = (char *)VGA_START + leftx + ((py+1) * X_WRAP_SIZE); // point to the pixel
		for(x = leftx; x <= rightx; x++,vga_mem++) {
			if(*vga_mem == fillcolor) recur_fill2(x,py+1,c);
		}
	}

	if(py >0) {
		vga_mem  = (char *)VGA_START + leftx + ((py-1) * X_WRAP_SIZE); // point to the pixel
		for(x = leftx; x <= rightx; x++,vga_mem++) {
			if(*vga_mem == fillcolor) recur_fill2(x,py-1,c);
		}
	}
}



/**************************************************************************
	void recur_fill2(int px,int py,int c)

	DESCRIPTION:

**************************************************************************/
/*void recur_fill2(int px,int py,int c)
{
	char *vga_mem;

	if (px <   0) return;
	if (py <   0) return;
	if (px > 319) return;
	if (py > 199) return;

	vga_mem  = (char *)VGA_START + px + (py * X_WRAP_SIZE); // point to the pixel

	if (*vga_mem != fillcolor) return;

	*vga_mem = c;

	recur_fill2(px-1,py,c);
	recur_fill2(px+1,py,c);
	recur_fill2(px,py-1,c);
	recur_fill2(px,py+1,c);
} */


/**************************************************************************
	void GUGFloodFill(int point_x, int point_y, int border, int color)

	DESCRIPTION:

**************************************************************************/
void GUGFloodFill(int point_x, int point_y, int border, int color)
{
  void recur_fill(int px,int py,int b,int c);
//  recur_fill(point_x,point_y,border,color);
}



/**************************************************************************
	void recur_fill(int px,int py,int b,int c)

	DESCRIPTION:

**************************************************************************/
void recur_fill(int px,int py,int b,int c)
{
  char *vga_mem;
 
  if (px <   0) return;
  if (py <   0) return;
  if (px > 319) return;
  if (py > 199) return;

  vga_mem  = (char *)VGA_START + px + (py * X_WRAP_SIZE); // point to the pixel

  if (*vga_mem == b) return;

  *vga_mem = c;

  recur_fill(px-1,py,b,c);
  recur_fill(px+1,py,b,c);
  recur_fill(px,py-1,b,c);
  recur_fill(px,py+1,b,c);
}
