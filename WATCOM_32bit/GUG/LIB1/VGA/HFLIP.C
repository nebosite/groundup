#include <stdio.h>
#include <string.h>
#include <malloc.h>

// H-Flip Rotation

void GUGSpriteHFlip(char *sprite) {
  int  sz,sx,sy,x,y,y1;
  char *spr_save; // [1028];

  sx = GUGSpriteWidth(sprite);
  sy = GUGSpriteHeight(sprite);
  sz = GUGSpriteSize(sprite);
  if ((spr_save = malloc(sz)) == NULL)
    return;

  memcpy((char *)spr_save,(char *)sprite,sz);
  x = sy - 1;
  for (y=0; y<sy;++y,--x) {
    memcpy((char *)&sprite[(y*sx)+4],(char *)&spr_save[(x*sx)+4],sx);
  }
  free(spr_save);
}
