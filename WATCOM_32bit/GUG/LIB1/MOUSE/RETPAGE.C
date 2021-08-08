#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;
       
/* return display page number */
unsigned int GUGMouseReturnPage(void) {
	inregs.w.ax = 30;
	int386( 51, &inregs, &outregs);
	return outregs.w.bx;
}
       
