#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* define screen update region */
void GUGMouseDefineUpdate(unsigned int tlx, unsigned int tly, unsigned int brx,
	                  unsigned int bry) {
	inregs.w.ax = 16;
	inregs.w.cx = tlx;
	inregs.w.dx = tly;
	inregs.w.si = brx;
	inregs.w.di = bry;
	int386( 51, &inregs, &outregs);
}
