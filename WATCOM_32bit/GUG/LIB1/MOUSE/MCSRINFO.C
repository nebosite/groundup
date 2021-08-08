#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* read cursor information */
void GUGMouseReadCursor(unsigned int *screen, unsigned int *cursor,
                        unsigned int *hcount, unsigned int *vcount) {
	inregs.w.ax = 39;
	int386(51, &inregs, &outregs);
	*screen = outregs.w.ax;
	*cursor = outregs.w.bx;
	*hcount = outregs.w.cx;
	*vcount = outregs.w.dx;
}
