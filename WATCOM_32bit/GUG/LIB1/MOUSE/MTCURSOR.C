#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* set text cursor */
void GUGMouseTextCursor(unsigned int type, unsigned int screen, 
                        unsigned int cursor) {
	inregs.w.ax = 10;
	inregs.w.bx = type;
	inregs.w.cx = screen;
	inregs.w.dx = cursor;
	int386( 51, &inregs, &outregs);
}
