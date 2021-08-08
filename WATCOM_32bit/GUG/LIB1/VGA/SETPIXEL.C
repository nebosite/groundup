#include "vga.h"
#include "mode.h"
 
//**************************************************************************
// This function sets a pixel on the VGA
//
void GUGSetPixel(int xpos, int ypos,int color) {
  char *vga_mem;

  if (xpos <              0) return;
  if (xpos > (MAX_X_SIZE-1)) return;
  if (ypos <              0) return;
  if (ypos > (MAX_Y_SIZE-1)) return;

  // Correct for Buffer
//  xpos += MAX_X_SIZE;
//  ypos += MAX_Y_SIZE;

  vga_mem  = (char *)VGA_START + xpos + (ypos * X_WRAP_SIZE); // point to the pixel
  *vga_mem = color;
}

