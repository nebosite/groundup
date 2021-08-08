#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

int *GUGMouseSwitch(unsigned int *size) {
	int *temp;
	temp = (int *)malloc(341);

	inregs.w.ax = 41;
	inregs.w.cx = 341;
	inregs.w.dx = FP_OFF(temp);
	segreg.es = FP_SEG(temp);
	int386x(51, &inregs, &outregs, &segreg);
	*size = outregs.w.cx;
	return temp;
}


