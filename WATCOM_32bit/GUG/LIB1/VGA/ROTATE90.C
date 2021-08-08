#include <stdio.h>
#include <string.h>
#include <malloc.h>

// Sprite Rotation

void GUGSpriteRotate90(char *sprite) {
  int  sz,sx,sy,x,y,y1;
  char *spr_save;  // [1028];

  sx = GUGSpriteWidth(sprite);
  sy = GUGSpriteHeight(sprite);
  sz = GUGSpriteSize(sprite);
  if ((spr_save = malloc(sz)) == NULL)
    return;

  memcpy((char *)spr_save,(char *)sprite,sz);
  sprite[0] = sy;
  sprite[2] = sx;
  for (x=0; x<sx; ++x) {
    for (y=0,y1=sy-1; y<sy; ++y,--y1) {
  	  sprite[(x*sy)+y1+4] = spr_save[(y*sx)+x+4];
    }
  }
  free(spr_save);
}

