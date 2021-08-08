#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* get active advanced functions */
unsigned int GUGMouseGetAdvanced(void) {
	inregs.w.ax = 50;
	int386(51, &inregs, &outregs);
	return outregs.w.ax;
}
