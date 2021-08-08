#include "vga.h"
 
//**************************************************************************
// This function copies the VGA display to a save buffer
//
void GUGSaveDisplay(char *too) {
  int   *vga_mem;      // Char  Pointer to VGA Mode 13 base address
  int   *too_mem;
  int   pos;           // Generic int

  // does too appear to have been malloced?
  if (too == 0L) return;

  vga_mem  = (int *)VGA_POINTER; // point too 0xA0000
  too_mem = (int *)too;          // where too read from

  for (pos=0; pos<16000; ++pos) {
    *too_mem = *vga_mem;
    vga_mem++;
    too_mem++;
  }
}

