#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* set video mode */
unsigned int GUGMouseSetVideoMode(unsigned int mode, unsigned int font) {
	inregs.w.ax = 40;
	inregs.w.cx = mode;
	inregs.w.dx = font;
	int386(51, &inregs, &outregs);
	return outregs.w.cx;
}
