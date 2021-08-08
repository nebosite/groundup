#include <i86.h>

//extern int    gug_mouse_counter;
extern union  REGS inregs, outregs;
extern struct SREGS segreg;

/* Show the mouse cursor */
void GUGMouseShow(void) {
//  ++gug_mouse_counter;
//  if (gug_mouse_counter == 1)
//  {
    inregs.w.ax = 1;
    int386( 51, &inregs, &outregs);
//  }
}

