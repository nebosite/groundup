//**************************************************************************
// This function copies memory to the VGA.
//

#include "..\vga\vga.h"
#include "..\vga\mode.h"

// Provided for compatability
void GUGSMCopyToDisplay(int x, int y) {
  GUGSMBufferPut(x,y);   
}

void GUGSMBufferPut(int x, int y) {
  int x1;
  char *from;
  char *too;
  extern int  SHOW_SPRITE_MOUSE;
  extern char *GUG_Sprite_Mouse;

  if ((GUG_Sprite_Mouse) && (SHOW_SPRITE_MOUSE))
    GUGPutFGSprite(x,y,GUG_Sprite_Mouse);

  too  = VGA_POINTER;
  from = VGA_START;
  for (x1=0; x1<MAX_Y_SIZE; ++x1) {
    memcpy(too,from,MAX_X_SIZE);
	too  += MAX_X_SIZE;
	from += X_WRAP_SIZE;
  }
}

