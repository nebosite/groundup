//*************************************************************************
// Put a Mono-Colored sprite in the DreamFX format on the screen flipped
//  on the X axis
//
#include "vga.h"
#include "mode.h"

void GUGFlipXMNSprite(int xb,int yb,int color,char spr[])
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
  write = ((char *)VGA_START + ((yb + ys - 1) * X_WRAP_SIZE)) + xb;

  // compute difference between length of VGA line + clip area and width of
  // sprite.
  write_inc = X_WRAP_SIZE + xs;

  // nice tight loop.
  for (y=0; y<ys; ++y) {
    for (x=0; x<xs; x++) {
	  if (*spr) *write = (char)color;
	  *spr++; *write++;
	}
    write -= write_inc;
  }
}	

