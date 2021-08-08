//**************************************************************************
// This function copies memory to the VGA.
//

#include "vga.h"
#include "mode.h"
#include "string.h"

void GUGCopyToDisplay() {
  int x1;
  char *from;
  char *too;

  too  = VGA_POINTER;
  from = VGA_START;
  for (x1=0; x1<MAX_Y_SIZE; ++x1) {
    memcpy(too,from,MAX_X_SIZE);
	too  += MAX_X_SIZE;
	from += X_WRAP_SIZE;
  }
}

