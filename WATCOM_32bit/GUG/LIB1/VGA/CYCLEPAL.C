void GUG_put_pal_raw(char *pal, int num_colors, int start_index);

void GUGCyclePalette(char *pal, int start, int stop) {
  int pos,changes;
  int dummy;

  if (start < stop) {
    pal[(stop*3)]   = pal[(start*3)];
    pal[(stop*3)+1] = pal[(start*3)+1];
    pal[(stop*3)+2] = pal[(start*3)+2];

    for (pos=start; pos<stop; ++pos) {
      pal[(pos*3)]   = pal[((pos+1)*3)];
      pal[(pos*3)+1] = pal[((pos+1)*3)+1];
      pal[(pos*3)+2] = pal[((pos+1)*3)+2];
    }
    GUG_put_pal_raw(pal,256,0);
  }
  else if (start > stop) {
    pal[(stop*3)]   = pal[(start*3)];
    pal[(stop*3)+1] = pal[(start*3)+1];
    pal[(stop*3)+2] = pal[(start*3)+2];

    for (pos=start; pos>stop; --pos) {
      pal[(pos*3)]   = pal[((pos-1)*3)];
	  pal[(pos*3)+1] = pal[((pos-1)*3)+1];
      pal[(pos*3)+2] = pal[((pos-1)*3)+2];
    }
    GUG_put_pal_raw(pal,256,0);
  }
}
