#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* define interupt subroutine parameters */
void GUGMouseDefineInterupt(void far *routine, unsigned int mask) {
	inregs.w.ax = 12;
	inregs.w.cx = mask;
	inregs.w.dx = FP_OFF(routine);
	segreg.es = FP_SEG(routine);
	int386x(51, &inregs, &outregs, &segreg);
}
