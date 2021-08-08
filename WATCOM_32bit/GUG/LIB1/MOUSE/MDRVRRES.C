#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;
      
/* restore mouse driver state */
void GUGMouseRestoreDriver(void far *buffer) {
	inregs.w.ax = 23;
	inregs.w.dx = FP_OFF(buffer);
	segreg.es = FP_SEG(buffer);
	int386x( 51, &inregs, &outregs, &segreg);
}
      
