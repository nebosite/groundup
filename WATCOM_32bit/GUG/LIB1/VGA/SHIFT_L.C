#include <stdio.h>
#include <string.h>

//*********************************************************************
// Sprite shifting functions

void GUGShiftSpriteLeft(char *spr) {
  int   x,y,p,xs,ys,sz;
  char 	s1[1024];
  char	*s2;

  s2 = spr + 4;

  xs = GUGSpriteWidth(spr);
  ys = GUGSpriteHeight(spr);
  sz = xs*ys;

  memcpy((char *)s1,(char *)s2,sz);

  for (y=0; y<ys; ++y) {
    for (x=0; x<xs-1; ++x) {
      s2[(y*xs)+x] = s1[(y*xs)+x+1];
    }
    s2[(y*xs)+xs-1] = s1[(y*xs)];
  }
}
