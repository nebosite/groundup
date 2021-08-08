//*************************************************************************
// Return the width of a sprite
//
#include "vga.h"

int GUGSpriteWidth(char spr[])
{
  return(spr[0] + (spr[1] * 256));
}       
