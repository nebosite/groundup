#include <stdio.h>
#include <math.h>
#include "..\pi.h"

typedef struct  {
  int x;
  int y;
}GUGVertex;
int GUGFillPoly(int color, int points, GUGVertex poly[]);
extern int GUG_Poly_No_Cross;

void GUGFillCircle(float r, int l, int c, int ox, int oy)
{
  float theta=0;
  float thinc;
  int   i,p;
  int   x,y;
  GUGVertex poly[60];
  int   flag;

  if (l > 60) l = 60;
  p = 0;

  flag = GUG_Poly_No_Cross;
  GUG_Poly_No_Cross = 1;  // True

  thinc=2*M_PI/l;

  if (r == 0) return;
  poly[p].x = (int)r+ox;
  poly[p].y = 0+oy;

  for (i=0; i<l; ++i)
  {
    theta = theta + thinc;
    x = r * cos(theta);
	y = r * sin(theta);
	p++;
    poly[p].x = x+ox;
    poly[p].y = y+oy;
  }
  GUGFillPoly(c,l,poly);

  GUG_Poly_No_Cross = flag;
 
}
