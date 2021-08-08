#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* reset mouse hardware */
int GUGMouseHardReset(void) {
	inregs.w.ax = 47;
	int386(51, &inregs, &outregs);
	return (int)outregs.w.ax;
}
