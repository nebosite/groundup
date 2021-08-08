#include "vga.h"
#include "mode.h"

void GUG_fix_point(int *x, int *y, char axis);

void GUGVLine(int ystart, int ystop, int x, int color)
{
   char *vga_mem;

   if (x <   0) return;
   if (x > (MAX_X_SIZE-1)) return;
//   x += MAX_X_SIZE;
  
   GUG_fix_point(&ystart,&ystop,'Y');
//   ystart += MAX_Y_SIZE;
//   ystop  += MAX_Y_SIZE;
   
   vga_mem = VGA_START + x + (ystart * X_WRAP_SIZE); 
   
   while (ystart <= ystop) {
     *vga_mem = color;
     vga_mem += X_WRAP_SIZE;
     ystart++;
   }
}
