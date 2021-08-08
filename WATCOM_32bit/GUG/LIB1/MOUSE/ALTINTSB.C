#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* Alternate interupt subroutine definition */
int GUGMouseAlternteInterupt(void far *routine, unsigned int mask) {
	inregs.w.ax = 24;
	inregs.w.cx = mask;
	inregs.w.dx = FP_OFF(routine);
	segreg.es = FP_SEG(routine);
	int386x(51, &inregs, &outregs, &segreg);
	return (int)outregs.w.ax;
}
