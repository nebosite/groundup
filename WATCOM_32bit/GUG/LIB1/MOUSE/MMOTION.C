#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* Read motion counters */
void GUGMouseReadMotion(unsigned int *hcount, unsigned int *vcount) {
	inregs.w.ax = 11;
	int386( 51, &inregs, &outregs);
	*hcount = outregs.w.cx;
	*vcount = outregs.w.dx;
}
