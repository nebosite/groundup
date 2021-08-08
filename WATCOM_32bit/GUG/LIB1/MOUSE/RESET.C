#include <i86.h>

union  REGS  inregs, outregs;
struct SREGS segreg;

// Reset the Mouse Driver
void GUGMouseReset(int *status, unsigned int *button) {
  inregs.w.ax = 0;
  int386( 51, &inregs, &outregs);
  *status = (int)outregs.w.ax;
  if (*status != 0) *status = -1;
  *button = outregs.w.bx;
}

