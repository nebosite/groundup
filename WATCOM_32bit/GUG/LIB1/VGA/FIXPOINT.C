#include "mode.h"

void GUG_fix_point(int *p1, int *p2, char axis)
{
  int t;

  if (*p1 > *p2) {
    t   = *p1;
    *p1 = *p2;
    *p2 = t;
  }

  if (axis == 'X') {
    if (*p1 <              0) *p1 =   0;
		if (*p1 > (MAX_X_SIZE-1)) *p1 = (MAX_X_SIZE-1);
		if (*p2 <              0) *p2 =   0;
    if (*p2 > (MAX_X_SIZE-1)) *p2 = (MAX_X_SIZE-1);
  }
  else {
    if (*p1 <   0) *p1 =   0;
		if (*p1 > (MAX_Y_SIZE-1)) *p1 = (MAX_Y_SIZE-1);
		if (*p2 <   0) *p2 =   0;
    if (*p2 > (MAX_Y_SIZE-1)) *p2 = (MAX_Y_SIZE-1);
  }
}
