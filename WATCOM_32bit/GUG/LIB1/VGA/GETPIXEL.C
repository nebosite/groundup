//**************************************************************************
// This function gets a pixel
//

#include "vga.h"
#include "mode.h"

int GUGGetPixel(int xpos, int ypos) {
  char *vga_mem;
  
  if (xpos <   0) return(-1);
  if (xpos >=  MAX_X_SIZE) return(-1);
  if (ypos <   0) return(-1);
  if (ypos >=  MAX_Y_SIZE) return(-1);

//  xpos += MAX_X_SIZE;
//  ypos += MAX_Y_SIZE;

  vga_mem  = (char *)VGA_START + xpos + (ypos * X_WRAP_SIZE); // point to the pixel
  return(*vga_mem);
}

