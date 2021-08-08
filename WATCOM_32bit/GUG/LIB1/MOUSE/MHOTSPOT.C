#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* read cursor hot spot */
void GUGMouseReadHotSpot(unsigned int *fCursor, unsigned int *hhot,  
			 unsigned int *vhot,    unsigned int *type) {
	inregs.w.ax = 42;
	int386(51, &inregs, &outregs);
	*fCursor = outregs.w.ax;
	*hhot = outregs.w.bx;
	*vhot = outregs.w.cx;
	*type = outregs.w.dx;
}
