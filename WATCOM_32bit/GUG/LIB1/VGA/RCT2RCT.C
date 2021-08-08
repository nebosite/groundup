//
//  Source is in BUFFER memory
//  Destin is in VGA    memory
//
#include "vga.h"
#include "mode.h"

void GUG_fix_point(int *p1, int *p2, char axis);

void GUGCopyRectToRect(int xs1,int ys1,int xs2,int ys2)
{
  char *from;
  char *too;
  int  x,y;

  GUG_fix_point(&xs1,&xs2,'X');
  GUG_fix_point(&ys1,&ys2,'Y');

  x = xs2 - xs1;
  for (y=ys1; y<=ys2; ++y)
  {
     from = (char *)VGA_START   + xs1 + (y * X_WRAP_SIZE); // point to the pixel
     too  = (char *)VGA_POINTER + xs1 + (y * 320);         // point to the pixel
     memcpy(too,from,x);
  }
}


