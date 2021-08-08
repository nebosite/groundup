#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* set language for messages */
void GUGMouseSetLanguage(unsigned int number) {
	inregs.w.ax = 34;
	inregs.w.bx = number;
	int386(51, &inregs, &outregs);
}
