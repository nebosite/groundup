#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

void GUGMouseButtonDown(unsigned int mbutton, unsigned int *mbstate,
	                    unsigned int *numpress, unsigned int *mx, 
	                    unsigned int *my) {
  inregs.w.ax = 5;
  inregs.w.bx = mbutton;
  int386( 51, &inregs, &outregs);
  *mbstate = outregs.w.ax;
  *numpress = outregs.w.bx;
  *mx = outregs.w.cx;
  *my = outregs.w.dx;
}
