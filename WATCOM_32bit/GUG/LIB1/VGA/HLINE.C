#include "vga.h"
#include "mode.h"

void GUG_fix_point(int *x, int *y, char axis);

void GUGHLine(int xstart, int xstop, int y, int color)
{
   char *vga_mem;

   if (y <   0) return; 
   if (y >=  MAX_Y_SIZE) return;
//   y += MAX_Y_SIZE;

   GUG_fix_point(&xstart,&xstop,'X'); 
//   xstart += MAX_X_SIZE;
//   xstop  += MAX_X_SIZE;

   vga_mem = VGA_START + xstart + (y * X_WRAP_SIZE); 
   
   while (xstart <= xstop) {
     *vga_mem = color;
     ++vga_mem;
     ++xstart;
   }
}
