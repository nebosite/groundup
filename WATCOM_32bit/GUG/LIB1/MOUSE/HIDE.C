#include <i86.h>

//extern int    gug_mouse_counter;
extern union  REGS  inregs, outregs;
extern struct SREGS segreg;

/* Hide the mouse cursor */
void GUGMouseHide(void) {
//  --gug_mouse_counter;
//  if (gug_mouse_counter == 0)
//  {
    inregs.w.ax = 2;
    int386( 51, &inregs, &outregs);
//  }
}

