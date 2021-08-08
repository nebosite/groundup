//*************************************************************************
// Put a BG sprite in the DreamFX format on the screen, it will be clipped
//  to a view rectangle.
//
#include "vga.h"
#include "mode.h"

void GUGClipBGSprite(int xb,int yb,   // Upper left hand corner of the Sprite
                     int cwx1,
                     int cwy1,        // Upper left hand corner of the clip window
                     int cwx2,
                     int cwy2,        // Lower right hand corner of the clip window
                     char spr[])
{
  int   x,xs,y,ys;
  char  *write,*spr_end,*spr_sub_end;
  int   write_inc;

  // Get the X/Y sizes
  xs =  *spr++; 
  xs += (*spr++ * 256);
  ys =  *spr++; 
  ys += (*spr++ * 256);

  if (cwx1 >= cwx2)
    return;
  if (cwy1 >= cwy2)
    return;

  // Clip it to the screen
  if (xb <= (0-xs)         || 
      xb >  (MAX_X_SIZE-1) || 
      yb <= (0-ys)         || 
      yb >  (MAX_Y_SIZE-1)) 
     return;

  // Clip it to the view screen
  if (xb <  (cwx1-xs)      || 
      xb >  cwx2           || 
      yb <  (cwy1-ys)      || 
      yb >  cwy2) 
     return;

//  cwx1++;
//  cwy1++;
//  cwx2--;
//  cwy2--;

//  cwx2 = cwx2 - cwx1;
//  cwy2 = cwy2 - cwy1;
//  cwx1  = 0;
//  cwy1  = 0;

  // compute start address in vga page.
  write = ((char *)VGA_START + (yb * X_WRAP_SIZE)) + xb;

  // compute difference between length of VGA line + clip area and width of
  // sprite.
  write_inc = X_WRAP_SIZE - xs;

  // nice tight loop.
  for (y=0; y<ys; ++y) {
    for (x=0; x<xs; x++) {
      if (((x+xb) > cwx1) && ((x+xb) < cwx2) &&
          ((y+yb) > cwy1) && ((y+yb) < cwy2))
      {
        *write=*spr;
      }
      spr++;
      write++;
    }
    write += write_inc;
  }
}	
