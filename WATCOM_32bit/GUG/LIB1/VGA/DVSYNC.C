#include <conio.h>

extern char *VGA_POINTER;             // Always points to the VGA memory


int GUGDebugVSync(void)
{
  int loop = 0;
  char *c = VGA_POINTER;
  static int cc = 5;

  if (cc == 5)
    cc = 35;
  else
    cc = 5;

  while(!(inp(0x3da)&0x08))
  {
    loop++;
	if (!*c) *c=cc;
    if (c < VGA_POINTER + 64000) c++;
  };                                // Wait for retrace to start

  c = VGA_POINTER;
  while((inp(0x3da)&0x08))         // Wait for retrace to finish
  {
	if (!*c) *c=cc;
    if (c < VGA_POINTER + 64000) c++;
  }

  return(loop);
}
