#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* Driver storage space */
unsigned int GUGMouseDriverSpace(void) {
	inregs.w.ax = 21;
	int386( 51, &inregs, &outregs);
	return outregs.w.bx;
}
