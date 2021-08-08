//*************************************************************************
// Put a FG sprite in the DreamFX format on the screen
//
#include "vga.h"
#include "mode.h"

void GUGPutFGSprite(int xb,int yb,char spr[])
{
  int   x,xs,y,ys;
  char  *write,*spr_end,*spr_sub_end;
  int   write_inc;

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

//  xb += MAX_X_SIZE;		// offset for clipping area
//  yb += MAX_Y_SIZE;
  // compute start address in vga page.
  write = ((char *)VGA_START + (yb * X_WRAP_SIZE)) + xb;

  // compute difference between length of VGA line + clip area and width of
  // sprite.
  write_inc = X_WRAP_SIZE - xs;

  spr_end = spr + xs * ys;
  do {
	spr_sub_end = spr + xs;
	switch (xs & 0x7) {
	case 7:
	  if (*spr) *write=*spr;
	  spr++;
	  write++;
	case 6:
	  if (*spr) *write=*spr;
	  spr++;
	  write++;
	case 5:
	  if (*spr) *write=*spr;
	  spr++;
	  write++;
	case 4:
	  if (*spr) *write=*spr;
	  spr++;
	  write++;
	case 3:
	  if (*spr) *write=*spr;
	  spr++;
	  write++;
	case 2:
	  if (*spr) *write=*spr;
	  spr++;
	  write++;
	case 1:
	  if (*spr) *write=*spr;
	  spr++;
	  write++;
	}
	if (spr < spr_sub_end)
      do {
	    if (*spr) *write=*spr;
	    spr++;
	    write++;
	    if (*spr) *write=*spr;
	    spr++;
	    write++;
	    if (*spr) *write=*spr;
	    spr++;
	    write++;
	    if (*spr) *write=*spr;
	    spr++;
	    write++;
	    if (*spr) *write=*spr;
	    spr++;
	    write++;
	    if (*spr) *write=*spr;
	    spr++;
	    write++;
	    if (*spr) *write=*spr;
	    spr++;
	    write++;
	    if (*spr) *write=*spr;
	    spr++;
	    write++;
	  } while (spr < spr_sub_end);
    write += write_inc;
  }	while (spr < spr_end);
/*
  // nice tight loop.
  for (y=0; y<ys; ++y) {
    for (x=0; x<xs; x++) {
	  if (*spr) *write=*spr;
	  spr++;
	  write++;
	}
    write += write_inc;
  }
*/
}	
