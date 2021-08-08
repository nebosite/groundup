#include <conio.h>
#include <mem.h>

#define DAC_WRITE_INDEX 0x3c8
#define DAC_DATA        0x3c9

//***************************************************************************
// Get the palette entries and return them      
//
void GUG_put_pal_raw(char *pal, int num_colors, int start_index) {
  char *pb = pal;
  outp(DAC_WRITE_INDEX, start_index);
  num_colors *= 3;   // 3 colors per entry
  while (num_colors--) {
    outp(DAC_DATA,*pb++);
  }
}

void GUGSetPalette(char *pal) {
  GUG_put_pal_raw(pal,256,0);
}

