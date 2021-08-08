#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* position mouse cursor */
void GUGMousePut(unsigned int mx, unsigned int my) {
	inregs.w.ax = 4;
	inregs.w.bx = mx;
        inregs.w.dx = my;
	int386( 51, &inregs, &outregs);
}
