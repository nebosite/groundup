//**************************************************************************
// This function fades memory to the VGA.
//

#include "vga.h"
#include "mode.h"
#include "string.h"
#include <i86.h>
						  
#define GUG_NO_FADE       0
#define GUG_RECT_FADE     1
#define GUG_PIXEL_FADE    2
#define GUG_SWIRL_FADE    3
#define GUG_SLIDEX_FADE   4
#define GUG_SLIDEY_FADE   5
#define GUG_PALETTE_FADE  6
#define MAX_FADE          6
#define GUG_RANDOM_FADE  -1
 
void   GUGCopyRectToRect(int xs1,int ys1,int xs2,int ys2);
void   GUGFadeToPalette(char *nwp, int speed);
void   GUGFadeToColor(int color, int speed);
extern char GUG_666_Palette[];

void GUGFadeToDisplay(int type) {
  int    l,x,y;
  int    xst,xsp,yst,ysp;
  char   *from;
  char   *too;
  static int last_fade = -1;

  if (type == GUG_NO_FADE)
  {
    GUGCopyToDisplay();
    return;
  }

  if (type == GUG_RANDOM_FADE)
  {
    do
	{
	  type = rand() / 1000;
	}
	while ((type < GUG_RECT_FADE) || (type > MAX_FADE) ||
	       (type == last_fade));
  }

  last_fade = type;

  if (type == GUG_RECT_FADE)
  {
    for (l=0; l<2048; ++l)
    {
	  x = rand() / 1023;
	  y = rand() / 1638;
      if (x > 31) x = 31;
	  if (y > 19) y = 19;
      GUGCopyRectToRect(x*10,y*10,(x+1)*10,(y+1)*10);
      if (!(l % 3)) delay(1);
	}
	GUGCopyToDisplay();
	return;
  }

  if (type == GUG_PIXEL_FADE)
  {
    for (l=0; l<128000; ++l)
    {
	  x    = rand() / 102;
	  y    = rand() / 163;
      if (x > 319) x = 319;
	  if (y > 199) y = 199;
      too  = VGA_POINTER + (y * MAX_X_SIZE) + x;
	  from = VGA_START   + (y * X_WRAP_SIZE) + x;
      *too = *from;
	}
	GUGCopyToDisplay();
	return;
  }

  if (type == GUG_SWIRL_FADE)
  {
    xst =  0;
	xsp = 32;
    yst =  0;
	ysp = 20;
   
    l = 0;
    do
	{
      for (x=xst; x<xsp; ++x)
	  {
        GUGCopyRectToRect(x*10,yst*10,(x+1)*10,(yst+1)*10);
        if (!(++l % 3)) delay(1);
	  }
      yst++;
      for (y=yst; y<ysp; ++y)
	  {
        GUGCopyRectToRect(xsp*10,y*10,(xsp+1)*10,(y+1)*10);
        if (!(++l % 3)) delay(1);
	  }
      xsp--;
      for (x=xsp-1; x>=xst; --x)
	  {
        GUGCopyRectToRect(x*10,ysp*10,(x+1)*10,(ysp+1)*10);
        if (!(++l % 3)) delay(1);
	  }
	  ysp--;
      for (y=ysp-1; x>=xst; --y)
	  {
        GUGCopyRectToRect(xst*10,y*10,(xst+1)*10,(y+1)*10);
        if (!(++l % 3)) delay(1);
	  }
      xst++;
	}
	while ((xst <= xsp) && (yst <= ysp));

	GUGCopyToDisplay();
	return;
  }

  if (type == GUG_SLIDEX_FADE)
  {
    xst =  0;
	xsp = 31;

    l = 0;
    do
	{
      for (y=0; y<11; ++y)
	  {
        GUGCopyRectToRect(xst*10,y*10,(xst+1)*10,(y+1)*10);
		GUGCopyRectToRect(xsp*10,y*10,(xsp+1)*10,(y+1)*10);

        GUGCopyRectToRect(xst*10,(20-y)*10,(xst+1)*10,((20-y)+1)*10);
		GUGCopyRectToRect(xsp*10,(20-y)*10,(xsp+1)*10,((20-y)+1)*10);

        delay(1);
	  }
      xst++;
	  xsp--;
    }
	while (xst <= xsp);

	GUGCopyToDisplay();
	return;
  }

  if (type == GUG_SLIDEY_FADE)
  {
    yst =  0;
	ysp = 20;

    l = 0;
    do
	{
      for (x=0; x<17; ++x)
	  {
        GUGCopyRectToRect(x*10,yst*10,(x+1)*10,(yst+1)*10);
		GUGCopyRectToRect(x*10,ysp*10,(x+1)*10,(ysp+1)*10);

        GUGCopyRectToRect((32-x)*10,yst*10,((32-x)+1)*10,(yst+1)*10);
		GUGCopyRectToRect((32-x)*10,ysp*10,((32-x)+1)*10,(ysp+1)*10);

        delay(1);
	  }
      yst++;
	  ysp--;
    }
	while (yst <= ysp);

	GUGCopyToDisplay();
	return;
  }

  if (type == GUG_PALETTE_FADE)
  {
    y = rand() / 152;
    GUGFadeToColor(y,1);
    GUGCopyToDisplay();
    GUGFadeToPalette(GUG_666_Palette,1);
	return;
  }



}

