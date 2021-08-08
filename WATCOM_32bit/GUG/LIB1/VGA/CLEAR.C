//**************************************************************************
// This function copies memory to the VGA.
//
// GUG2.0
//
#include "vga.h"
#include "mode.h"
#include "string.h"

void GUGClearDisplay() {
  int x1;
  char *from;
  char *too;
             // 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 
  int clr[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			  };

  too  = VGA_START;
  from = (char *)&clr[0];
  for (x1=0; x1<MAX_Y_SIZE; ++x1) {
    memcpy(too,from,MAX_X_SIZE);
	too  += X_WRAP_SIZE;
  }
}

