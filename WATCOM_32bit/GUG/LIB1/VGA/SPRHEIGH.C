//*************************************************************************
// Return the height of a sprite
//
#include "vga.h"

int GUGSpriteHeight(char spr[])
{
  return(spr[2] + (spr[3] * 256));
}       
