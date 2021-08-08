#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "..\lib1\gug.h"
#include "..\lib1\flic.h"

GUG_fli_ptr Pfli;
int dx = 1, dy = 1;

//**************** FUNCTIONS ****************//
void main (int argc, char *argv[])
{
  int i,v;
  char ch = 0, *virt_scr;
  union REGS regs;
  char mes[80];

  if (argc < 2)
  {
    printf("usage: playflic flicname.fl* [d,r]\n\n\n");
	return;
  }

  switch (argv[2][0]) {
  case 'd':
    Pfli = GUGLoadFLI(argv[1], FLI_DISK);
    break;
  case 'r':
    Pfli = GUGLoadFLI(argv[1], FLI_RAM);
    break;
  default:
    Pfli = GUGLoadFLI(argv[1], FLI_AUTO);
    break;
  }

  if (Pfli  == NULL) {
    printf ("error loading file");
    return;
  }

  if (Pfli->width > 320 || Pfli->height > 200) {
    printf ("File exceeds 320x200");
    return;
  }

  if (!GUGInitialize())
    return;

  virt_scr = (char *)malloc (64000);
  if (virt_scr == NULL) {
    printf ("out of memory, can not allocate virtual screen buffer\n");
    return;
  }

  GUGClearDisplay ();
  while (ch != 27) {
    for (i = 0; i < Pfli->speed; i++)
      GUGVSync ();
    // Play directly yo VGA memory
//    GUGPlayFLIToDisplay(Pfli);

    // Play into the double buffer
    v = GUGPlayFLIToBuffer(Pfli);
    sprintf(mes,"%d",v);
    GUGPutText(0,190,215,mes);
    GUGCopyToDisplay();      


//    GUGPlayFLI(Pfli, virt_scr, 320);
//    GUGCopyToBuffer (virt_scr);
//    GUGCopyRectToRect (0, 0, Pfli->width, (Pfli->height - 1));

    if (kbhit ())
      ch = getch ();
  }

  GUGCloseFLI(Pfli);
  free (virt_scr);
  GUGEnd ();
}

