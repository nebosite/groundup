#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;
       
/* save acceleration curves */
void far *GUGMouseSaveCurves(unsigned int *curve, unsigned int *success) {
	inregs.w.ax = 44;
	int386x(51, &inregs, &outregs, &segreg);
	*curve = outregs.w.bx;
	*success = outregs.w.ax;
	return MK_FP(segreg.es, outregs.w.si);
}
       
