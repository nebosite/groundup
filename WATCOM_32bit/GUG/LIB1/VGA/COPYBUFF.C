#include "vga.h"
#include "mode.h"
#include "string.h"

//**************************************************************************
// This function copies a page to the buffer
//
void GUGCopyToBuffer(char *from) {
  int x1;
  char *too;

  too  = VGA_START;
  for (x1=0; x1<MAX_Y_SIZE; ++x1) {
    memcpy(too,from,MAX_X_SIZE);
	too  += X_WRAP_SIZE;
	from += 320;
  }
}

