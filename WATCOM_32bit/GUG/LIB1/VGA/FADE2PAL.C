//
// Updated 8/20/95 NBBII Changed new to nwp for c++ compatability
//
#include <i86.h>

void GUG_put_pal_raw(char *pal, int num_colors, int start_index);
void GUG_get_pal_raw(char *pal, int num_colors, int start_index);

void GUGFadeToPalette(char *nwp, int speed) {
  char   pal[768];
  int  pos,changes;

  GUG_get_pal_raw((char *)pal,256,0);

  do {
    for (changes=0,pos=0; pos<256; ++pos) {
      if (pal[(pos*3)]   < nwp[(pos*3)])   ++pal[(pos*3)]  ,changes++;
      if (pal[(pos*3)+1] < nwp[(pos*3)+1]) ++pal[(pos*3)+1],changes++;
      if (pal[(pos*3)+2] < nwp[(pos*3)+2]) ++pal[(pos*3)+2],changes++;
      if (pal[(pos*3)]   > nwp[(pos*3)])   --pal[(pos*3)]  ,changes++;
      if (pal[(pos*3)+1] > nwp[(pos*3)+1]) --pal[(pos*3)+1],changes++;
		if (pal[(pos*3)+2] > nwp[(pos*3)+2]) --pal[(pos*3)+2],changes++;
    }
    GUG_put_pal_raw((char *)pal,256,0);
    delay(speed);
  }
  while (changes);
}
