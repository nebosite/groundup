#include <stdio.h>
#include <math.h>
#include "..\pi.h"

void GUGCircle(float r, int l, int c, int ox, int oy)
{
  float theta=0;
  float thinc;
  int   i;
  int   x,y;

  thinc=2*M_PI/l;

  GUGPIXSetColor(c);

  if (r == 0) return;
  GUGPIXMove((int)r+ox,0+oy);
  for (i=0; i<l; ++i)
  {
    theta = theta + thinc;
    x = r * cos(theta);
	y = r * sin(theta);
	GUGPIXLine(x+ox,y+oy);
  }
}
