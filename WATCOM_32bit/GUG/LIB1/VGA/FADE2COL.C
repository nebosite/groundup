#include <i86.h>

void GUG_put_pal_raw(char *pal, int num_colors, int start_index);
void GUG_get_pal_raw(char *pal, int num_colors, int start_index);

void GUGFadeToColor(int color, int speed) {
  char   pal[768];
  int  red,green,blue;
  int  pos,changes;

  GUG_get_pal_raw(pal,256,0);

  red   = pal[(color*3)];
  green = pal[(color*3)+1];
  blue  = pal[(color*3)+2];

  do {
    for (changes=0,pos=0; pos<256; ++pos) {
      if (pal[(pos*3)]   < red)   ++pal[(pos*3)]  ,changes++;
      if (pal[(pos*3)+1] < green) ++pal[(pos*3)+1],changes++;
      if (pal[(pos*3)+2] < blue)  ++pal[(pos*3)+2],changes++;
      if (pal[(pos*3)]   > red)   --pal[(pos*3)]  ,changes++;
      if (pal[(pos*3)+1] > green) --pal[(pos*3)+1],changes++;
      if (pal[(pos*3)+2] > blue)  --pal[(pos*3)+2],changes++;
    }
    GUG_put_pal_raw(pal,256,0);
    delay(speed);
  }
  while (changes);
}
