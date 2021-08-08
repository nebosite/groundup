#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* load acceleration curves */
unsigned int GUGMouseLoadCurves(unsigned int number, void far *curves) {
	inregs.w.ax = 43;
	inregs.w.bx = number;
	inregs.w.si = FP_OFF(curves);
	segreg.es = FP_SEG(curves);
	int386x(51, &inregs, &outregs, &segreg);
	return outregs.w.ax;
}
