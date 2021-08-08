#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;


/* get/set active acceleation curve */
char far *GUGMouseActiveCurves(int number, unsigned int *success,
	unsigned int *curve) {
	inregs.w.ax = 45;
	inregs.w.bx = (unsigned int)number;
	int386x(51, &inregs, &outregs, &segreg);
	*success = outregs.w.ax;
	*curve = outregs.w.bx;
	return (char far *)MK_FP(segreg.es, outregs.w.si);
}
