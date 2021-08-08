#include <conio.h>
#include <mem.h>

#define DAC_WRITE_INDEX 0x3c8
#define DAC_DATA        0x3c9

//***************************************************************************
// Get the palette entries and return them      
//
void GUGSetPaletteEntry(int index,int red, int green, int blue) {
  outp(DAC_WRITE_INDEX,index);
  outp(DAC_DATA,(char)red);
  outp(DAC_DATA,(char)green);
  outp(DAC_DATA,(char)blue);
}

