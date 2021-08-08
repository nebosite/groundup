#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* set mickey to pixel ratio */
void GUGMouseMickeyToPixel(unsigned int mickeyx, unsigned int mickeyy) {
	inregs.w.ax = 15;
	inregs.w.cx = mickeyx;
	inregs.w.dx = mickeyy;
	int386( 51, &inregs, &outregs);
}
