//**************************************************************************
// This function sets the VGA memory to a color 4 bytes at a time.
//

#include "vga.h"
#include "mode.h"

void GUGSetDisplay(int color) {
  int  x;
  char *c;
  static char buf[MAX_X_SIZE];

  for (x=0; x<MAX_X_SIZE; ++x) {
    buf[x] = (char)color;
  }

  c = VGA_START;
  for (x=0; x<MAX_Y_SIZE; ++x) {
    memcpy(c,buf,MAX_X_SIZE);
	c += X_WRAP_SIZE;
  }
}

