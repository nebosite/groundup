#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

void GUGMousePosition(unsigned int *mpressed, unsigned int *mx, 
                      unsigned int *my) {
  inregs.w.ax = 3;
  int386( 51, &inregs, &outregs);
  *mpressed = outregs.w.bx;
  *mx = outregs.w.cx;
  *mx = *mx / 2;
  *my = outregs.w.dx;
}
