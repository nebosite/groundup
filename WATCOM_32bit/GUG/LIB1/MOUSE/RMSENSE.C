#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* read mouse sensitivity */
void GugMouseReadSensitivity(unsigned int *hnum, unsigned int *vnum, 
                             unsigned int *dst) {
	inregs.w.ax = 27;
	int386(51, &inregs, &outregs);
	*hnum = outregs.w.bx;
	*vnum = outregs.w.cx;
	*dst = outregs.w.dx;
}
