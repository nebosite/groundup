#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* define display page number */
void GUGMouseDefinePage(unsigned int page) {
	inregs.w.ax = 29;
	inregs.w.bx = page;
	int386( 51, &inregs, &outregs);
}
