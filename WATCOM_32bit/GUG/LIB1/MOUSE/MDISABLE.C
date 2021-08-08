#include <stdio.h>
#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* disable mouse driver */
void far *GUGMouseDisableDriver(void) {
	inregs.w.ax = 31;
	int386x(51, &inregs, &outregs, &segreg);
	if ((int)outregs.w.ax == -1)
		return NULL;
	else
		return MK_FP(segreg.es, outregs.w.bx);
}
