#include <conio.h>
#include <mem.h>

#define DAC_READ_INDEX 0x3c7
#define DAC_DATA       0x3c9

//***************************************************************************
// Get the palette entries and return them      
//
void GUG_get_pal_raw(char *pal, int num_colors, int start_index) {
  char *pb = pal;
  outp(DAC_READ_INDEX, start_index);
  num_colors *= 3;   // 3 colors per entry
  while (num_colors--) {
    *pb++ = (char)inp(DAC_DATA);
  }
}

void GUGGetPalette(char *pal) {
  GUG_get_pal_raw(pal,256,0);
}

