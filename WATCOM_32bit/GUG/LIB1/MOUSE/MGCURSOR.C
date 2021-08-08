#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* set graphics cursor */
void GUGMouseGraphicsCursor(int *cursor, unsigned int hotx, unsigned int hoty) {
	inregs.w.ax = 9;
	inregs.w.bx = hotx;
	inregs.w.cx = hoty;
	inregs.w.dx = FP_OFF(cursor);
	segreg.es = FP_SEG(cursor);
	int386x(51, &inregs, &outregs, &segreg);
}
