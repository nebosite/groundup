#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* light pen emulation on */
void GUGMouseLightPenOn(void) {
	inregs.w.ax = 13;
	int386(51, &inregs, &outregs);
}
