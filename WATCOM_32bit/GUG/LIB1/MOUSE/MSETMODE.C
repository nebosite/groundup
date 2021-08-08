#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* read max virtual display coordinates */
void GUGMouseReadMAXVDC(unsigned int *enable, unsigned int *xmax, 
                        unsigned int *ymax) {
	inregs.w.ax = 38;
	int386(51, &inregs, &outregs);
	*enable = outregs.w.bx;
	*xmax = outregs.w.cx;
	*ymax = outregs.w.dx;
}
