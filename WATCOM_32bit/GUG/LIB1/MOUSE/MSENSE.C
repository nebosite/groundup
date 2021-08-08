#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* mouse sensitivity definition */
void GUGMouseSensitivity(unsigned int hnum, unsigned int vnum, 
                         unsigned int dst) {
	inregs.w.ax = 26;
	inregs.w.bx = hnum;
	inregs.w.cx = vnum;
	inregs.w.dx = dst;
	int386(51, &inregs, &outregs);
}
