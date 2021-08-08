#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* re-enable mouse driver */
int GUGMouseReenableDriver(void) {
	inregs.w.ax = 32;
	int386(51, &inregs, &outregs);
	return (int)outregs.w.ax;
}
