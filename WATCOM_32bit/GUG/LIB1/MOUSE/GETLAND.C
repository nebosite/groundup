#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;
        
/* return language number */
unsigned int GUGMouseGetLanguage(void) {
	inregs.w.ax = 35;
	int386(51, &inregs, &outregs);
	return outregs.w.bx;
}
        
