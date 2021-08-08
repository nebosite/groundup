#include <stdio.h>
#include <string.h>
#include <malloc.h>

// V-Flip Rotation

void GUGSpriteVFlip(char *sprite) {
  int  sz,sx,sy,x,y,y1;
  char *spr_save;  //[1028];

  sx = GUGSpriteWidth(sprite);
  sy = GUGSpriteHeight(sprite);
  sz = GUGSpriteSize(sprite);

  if ((spr_save = malloc(sz)) == NULL)
    return;

  memcpy((char *)spr_save,(char *)sprite,sz);
  for (y=0; y<sy;++y) {
    for (x=0; x<sx; ++x) {
      sprite[(y*sx)+x+4] = spr_save[(y*sx)+(sx-x-1)+4];
    }
  }
  free(spr_save);
}

