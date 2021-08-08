//*************************************************************************
// Put a BG sprite in the DreamFX format on the screen flipped around
//  the Y axis
//
#include "vga.h"
#include "mode.h"

void GUGFlipYBGSprite(int xb,int yb,char spr[])
{
  int   x,xs,y,ys;
  char  *write;
  int write_inc;

  // Get the X/Y sizes
  xs =  *spr++; 
  xs += (*spr++ * 256);
  ys =  *spr++; 
  ys += (*spr++ * 256);

  // Clip it to the screen
  if (xb <= (0-xs)         || 
      xb >  (MAX_X_SIZE-1) || 
      yb <= (0-ys)         || 
      yb >  (MAX_Y_SIZE-1)) 
     return;

  // compute start address in vga page.
  write = ((char *)VGA_START + (yb * X_WRAP_SIZE)) + xb + xs - 1;

  // compute difference between length of VGA line + clip area and width of
  // sprite.
  write_inc = X_WRAP_SIZE + xs;

  // nice tight loop.
  for (y=0; y<ys; ++y) {
    for (x=0; x<xs; x++) {
	  *write-- = *spr++;
	}
    write += write_inc;
  }
}	

