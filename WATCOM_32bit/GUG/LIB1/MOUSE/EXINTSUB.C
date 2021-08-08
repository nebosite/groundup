#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* Exchange Interupt Subroutines */
void far *GUGMouseExchangeInterupt(void far *subroutine, unsigned int mask) {
	inregs.w.ax = 20;
	inregs.w.cx = mask;
	inregs.w.dx = FP_OFF(subroutine);
	segreg.es = FP_SEG(subroutine);
	int386( 51, &inregs, &outregs);
	return MK_FP(segreg.es,outregs.w.dx);
}
