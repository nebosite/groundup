#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* define double speed threshhold */
void GUGMouseDefineThreshold(unsigned int speed) {
	inregs.w.ax = 19;
	inregs.w.dx = speed;
	int386( 51, &inregs, &outregs);
}
