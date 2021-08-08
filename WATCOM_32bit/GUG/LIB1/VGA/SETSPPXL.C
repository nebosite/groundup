//**************************************************************************
// This function sets a pixel in a sprite
//

#include "vga.h"
#include "mode.h"

void GUGSetSpritePixel(int xpos, int ypos, int color, char *spr) {
  char *mem;
  int  xs,ys;

  xs = GUGSpriteWidth(spr);
  ys = GUGSpriteHeight(spr);

  if (xpos <    0) return;
  if (xpos >=  xs) return;
  if (ypos <    0) return;
  if (ypos >=  ys) return;

  mem = spr;                    // Point to sprite
  mem += 4;                     // Point past size data
  mem += (ypos * xs) + xpos;	// Point to the byte in question
  *mem = color;
}

