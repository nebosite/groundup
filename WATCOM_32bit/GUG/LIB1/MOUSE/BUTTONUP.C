#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

void GUGMouseButtonRelease(unsigned int mbutton, unsigned int *mbstatus,
	                       unsigned int *numrelease, unsigned int *mx, 
	                       unsigned int *my) {
  inregs.w.ax = 6;
  inregs.w.bx = mbutton;
  int386( 51, &inregs, &outregs);
  *mbstatus = outregs.w.ax;
  *numrelease = outregs.w.bx;
  *mx = outregs.w.cx;
  *my = outregs.w.dx;
}
