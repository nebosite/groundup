//*************************************************************************
// Return the size of a sprite
//
#include "vga.h"

int GUGSpriteSize(char spr[])
{
  return(((spr[0] + (spr[1]*256)) * (spr[2]) + (spr[3]*256)) + 4);
}       
