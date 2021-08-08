#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* read mouse info */
void GUGMouseReadInfo(unsigned int *major, unsigned int *minor, 
                      unsigned int *type,  unsigned int *irq) {
	inregs.w.ax = 36;
	int386(51, &inregs, &outregs);
	*major = outregs.h.bh;
	*minor = outregs.h.bl;
	*type = outregs.h.ch;
	*irq = outregs.h.cl;
}
