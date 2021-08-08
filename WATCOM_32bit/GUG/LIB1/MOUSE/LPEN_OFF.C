#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* light pen emulation off */
void GUGMouseLightPenOffff(void) {
	inregs.w.ax = 14;
	int386(51, &inregs, &outregs);
}
