#include <stdio.h>
#include <i86.h>

extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* list video modes */
void far *GUGMouseListVideoModes(void) {
	void far *temp;
	unsigned int list[1000];
	unsigned int far *test;
	int count = 0;

	inregs.w.ax = 41;
	inregs.w.cx = 0;
	int386(51, &inregs, &outregs);
	temp = MK_FP(outregs.w.bx, outregs.w.dx);
	if (temp != NULL)
		return temp;
	else
	{
		do {
			list[count] = outregs.w.cx;
			inregs.w.cx = 1;
			int386(51, &inregs, &outregs);
			count++;
		} while (list[count-1] != 0);
		test = (unsigned int *)malloc(sizeof(unsigned int) * count);
		for ( ; count > -1; count--)
			test[count] = list[count];
	}
	return (void far *)test;
}
