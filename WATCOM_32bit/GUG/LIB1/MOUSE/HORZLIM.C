#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* Set the Horizontal Limit */
void GUGMouseHorizontalLimit(unsigned int min, unsigned int max) {
  min *= 2;
  max *= 2;
  inregs.w.ax = 7;
  inregs.w.cx = min;
  inregs.w.dx = max;
  int386( 51, &inregs, &outregs);
}
