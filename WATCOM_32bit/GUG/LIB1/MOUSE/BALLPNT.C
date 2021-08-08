#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;


/* set/read ballpoint mouse information */
void GUGMouseBallPoint(unsigned int command, int rotation, int *status,
                       unsigned int *angle, unsigned int *masks) {
	inregs.w.ax = 48;
	inregs.w.bx = rotation;
	inregs.w.cx = command;
	int386(51, &inregs, &outregs);
	*status = outregs.w.ax;
	*angle = outregs.w.bx;
	*masks = outregs.w.cx;
}
