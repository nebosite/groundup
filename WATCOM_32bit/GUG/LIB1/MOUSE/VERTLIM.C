#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

// Set the vertical limit
void GUGMouseVerticalLimit(unsigned int min, unsigned int max) {
  inregs.w.ax = 8;
  inregs.w.cx = min;
  inregs.w.dx = max;
  int386( 51, &inregs, &outregs);
}
