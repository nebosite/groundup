#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* read general driver information */
void GUGMouseReadDriverInfo(unsigned int *info, unsigned int *fCursorLock,
	                    unsigned int *fInMouseCode, 
                            unsigned int *fMouseBusy) {
	inregs.w.ax = 37;
	int386(51, &inregs, &outregs);
	*info = outregs.w.ax;
	*fCursorLock = outregs.w.bx;
	*fInMouseCode = outregs.w.cx;
	*fMouseBusy = outregs.w.dx;
}
