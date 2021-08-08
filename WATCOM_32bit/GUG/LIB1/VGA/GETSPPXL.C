//**************************************************************************
// This function gets a pixel from a sprite
//

#include "vga.h"
#include "mode.h"

int GUGGetSpritePixel(int xpos, int ypos, char *spr) {
  char *mem;
  int  xs,ys;

  xs = GUGSpriteWidth(spr);
  ys = GUGSpriteHeight(spr);

  if (xpos <    0) return(-1);
  if (xpos >=  xs) return(-1);
  if (ypos <    0) return(-1);
  if (ypos >=  ys) return(-1);

  mem = spr;                    // Point to sprite
  mem += 4;                     // Point past size data
  mem += (ypos * xs) + xpos;	// Point to the byte in question

  return(*mem);
}

