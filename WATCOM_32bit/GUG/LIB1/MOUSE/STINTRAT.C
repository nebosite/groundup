#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* set interupt rate */
void GUGMouseSetInteruptRate(unsigned int rate) {
	inregs.w.ax = 28;
	inregs.w.bx = rate;
	int386(51, &inregs, &outregs);
}
