#include "vga.h"
 
//**************************************************************************
// This function copies a save buffer to the VGA's memory
//
void GUGRestoreDisplay(char *from) {
  int   *vga_mem;      // Char  Pointer to VGA Mode 13 base address
  int   *from_mem;
  int   pos;           // Generic int

  // does too appear to have been malloced?
  if (from == 0L) return;

  vga_mem  = (int *)VGA_POINTER; // point too 0xA0000
  from_mem = (int *)from;        // where too read from

  for (pos=0; pos<16000; ++pos) {
    *vga_mem = *from_mem;
    vga_mem++;
    from_mem++;
  }
}

