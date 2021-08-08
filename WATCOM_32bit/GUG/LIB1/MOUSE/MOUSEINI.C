#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* get location of mouse.ini file */

char far *GUGMouseLocateINI(void) {
	inregs.w.ax = 52;
	int386x(51, &inregs, &outregs, &segreg);
	return (char far *)MK_FP(segreg.es, outregs.w.dx);
}
