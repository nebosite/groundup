/*
** show pcx image file
*/

#include "vga.h"
#include "mode.h"

typedef struct {
  int  x_size;         // Width of the PCX
  int  y_size;	      // Height of the PCX
  char *image;	      // Points to the PCX's image data
  char palette[768];  // Points to the PCX's palette data
} GUG_PCX;

void GUGShowPCX(int x,int y,GUG_PCX *gug_pcx)
{
  int  yl;
  int  bx,by;
  char *from;
  char *too;

  // general clipping
  if (x > 319) return;
  if (y > 199) return;
  if (x < (0 - gug_pcx->x_size)) return;
  if (y < (0 - gug_pcx->y_size)) return;

  // Clip it to the buffer
  bx = gug_pcx->x_size;
  if ((bx+x) > 320) bx = 320 - x;
  by = gug_pcx->y_size;
  if ((by+y) > 200) by = 200 - y;
	   
  too  = VGA_START + (y * X_WRAP_SIZE) + x;
  from = gug_pcx->image;
//  for (yl=0; yl<gug_pcx->y_size; ++yl) {
//    memcpy(too,from,gug_pcx->x_size);
  for (yl=0; yl<by; ++yl) {
    memcpy(too,from,bx);
	too  += X_WRAP_SIZE;
	from += gug_pcx->x_size;
  }
}
