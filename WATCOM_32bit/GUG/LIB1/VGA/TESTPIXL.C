#include "vga.h"
#include "mode.h"

//**************************************************************************
// This function tests a pixel on the VGA got a given color
//
int GUGTestPixel(int xpos, int ypos,int color) {
  char *vga_mem;
  
  if (xpos <              0) return(-1);
  if (xpos > (MAX_X_SIZE-1)) return(-1);
  if (ypos <              0) return(-1);
  if (ypos > (MAX_Y_SIZE-1)) return(-1);

//  xpos += MAX_X_SIZE;
//  ypos += MAX_Y_SIZE;

  vga_mem  = (char *)VGA_START + xpos + (ypos * X_WRAP_SIZE); // point to the pixel
  if (*vga_mem == color)
    return(1);
  else
    return(0);
}

