#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/*get virtual screen coordinates */
void GUGMouseGetVSC(unsigned int *xmin, unsigned int *ymin,unsigned int *xmax, 
                    unsigned int *ymax) {
	inregs.w.ax = 49;
	int386(51, &inregs, &outregs);
	*xmin = outregs.w.ax;
	*ymin = outregs.w.bx;
	*xmax = outregs.w.cx;
	*ymax = outregs.w.dx;
}
