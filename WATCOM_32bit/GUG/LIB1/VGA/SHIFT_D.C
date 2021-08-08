#include <stdio.h>
#include <string.h>

//*********************************************************************
// Sprite shifting functions

void GUGShiftSpriteDown(char *spr) {
  int   x,y,p,xs,ys,sz;
  char 	s1[1024];
  char	*s2;

  s2 = spr + 4;

  xs = GUGSpriteWidth(spr);
  ys = GUGSpriteHeight(spr);
  sz = xs*ys;

  memcpy((char *)s1,(char *)s2,sz);

  for (y=1; y<ys; ++y) {
    memcpy((char *)&s2[y*xs],(char *)&s1[(y-1)*xs],xs);
  }
  memcpy((char *)s2,(char *)&s1[(ys-1)*xs],xs);
}
