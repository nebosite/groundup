#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* software reset */
int GUGMouseSoftwareReset(void) {
	inregs.w.ax = 33;
	int386(51, &inregs, &outregs);
	if (((int)outregs.w.ax == -1) && (outregs.w.bx == 2))
		return -1;
	else
		return 0;
}
