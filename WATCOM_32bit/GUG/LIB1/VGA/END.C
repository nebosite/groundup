#include <i86.h>
#include <stdlib.h>
#include "vga.h"
#include "mode.h"

void  GUGSetPalette(char *palette);

extern int curmode;  // mode GUG was started from

//***************************************************************************
// Set the VGA card to mode 3 (80x25 text mode)
//
void GUGEnd(void) {
  union REGS regs;           // Used in the int386 function call

  GUGSetPalette(GUG_Old_Palette);  // restore the original palette

  regs.h.ah = 0x00;          // Int 0x10 option 0x00 set VGA mode
  regs.h.al = curmode;  // 0x03;  // Use mode 0x03 - 80x25 character
  int386(0x10,(union REGS *)&regs,
              (union REGS *)&regs);  // And set the mode

//  printf("Restored to %d\n",curmode);
//  while (!kbhit()) {};
//  getch();

  if (VGA_MEMORY > NULL) free(VGA_MEMORY);
}

