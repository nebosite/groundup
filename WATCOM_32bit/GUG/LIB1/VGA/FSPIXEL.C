#include "vga.h"
#include "mode.h"
 
//**************************************************************************
// This function sets a pixel on the VGA
//
void GUGFastSetPixel(int xpos, int ypos,int color) {
  char *vga_mem;

// 640 = 512 + 128
//       <<9   <<7

  vga_mem  = (char *)VGA_START + xpos;
  vga_mem += (ypos << 9) + (ypos << 7); // point to the pixel
  *vga_mem = color;
}

