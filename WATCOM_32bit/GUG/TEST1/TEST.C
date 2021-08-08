//
// Demo and Test program for GUG
//  Copyright 1995 Ground Up Software
//
// Uses 'makefile' and 'link.cmd' to build
// via wmake
//
// Expects to find the GUG headers and LIB in a directy under the one
//   this code is in named  'lib1'
//

#include <stdio.h>
#include <i86.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <gug.h>      // Load the GUG definitions etc
#include <colors.h>
#include <keydefs.h>

#define MAX  100      // 100 sprites MAX

// Used with the rand() function
#define MAX_X (32768/320)  // Random to 320
#define MAX_Y (32768/200)  // Random to 200
#define MAX_C (32768/215)  // Random to 216 as 0-215 used in 666 palette

// A function to test the sprite functions
int test_spr(void);
void do_joystick(void);

// We are going to load sprites from the file names ship1.spr, it
//  has 60 total sprites in it.
#define MAX_SHIP1_SPRITES 60
char *ship1_sprites[MAX_SHIP1_SPRITES];  // 60 sprites in the sequence

main() {
  int   l,i,x,y,c;
  int   status;
  unsigned int button,mx,my,ox,oy;
  char  *save_buffer = NULL;
  char  txt;
  char  mes[80];
  char  rotate_palette[768];
  GUGVertex poly[20];

  // Used to save the screen in
  if ((save_buffer = (char *)malloc(64000)) == NULL) {
    printf("Error in malloc()\n");
    return;
  }

  // Load the sprites in ship1.spr
  if (GUGLoadSprite("ship.spr",ship1_sprites) < 1) {
    printf("Unable to find player.spr\n");
	return;
  }

  // Start GUG
  if (GUGInitialize() == 0)
  {
    printf("GUG was not able to initialize.\n");
	return;
  }

  // Get a copy of the 666 palette to use in the palette cycling demos
  GUGGetPalette((char *)rotate_palette);
  // start the mouse and keyboard handlers
  GUGMouseReset((int *)&status,(unsigned int *)&button);
  GUGStartKeyboard();
 
  // clears the display
  GUGClearDisplay();
  GUGDebugClear();

  // restore the 666 palette
  GUGSetPalette((char *)GUG_666_Palette);

  // Clipped Sprite Demo's
  for (y=50; y<150; ++y)
  {

    sprintf(mes,"Y Loop at %d",y);
    GUGDebugStringAtXY(mes,5,y-60);

    GUGClearDisplay();
    GUGRectangle(140,80,180,120,RED);

    GUGClipFGSprite(150,y,
                    140,80,
                    180,120,
                    ship1_sprites[0]);

    GUGCenterText(190,WHITE,"Clipped Sprite Demo");
    GUGCopyToDisplay();
  }


  // Clipped Sprite Demo's
  for (x=110; x<210; ++x)
  {

    sprintf(mes,"X Loop at %d",x);
    GUGDebugStringAtXY(mes,50,x-120);

    GUGClearDisplay();
    GUGRectangle(140,80,180,120,RED);

    GUGClipFGSprite(x,90,
                    140,80,
                    180,120,
                    ship1_sprites[0]);

    GUGCenterText(190,WHITE,"Clipped Sprite Demo");
    GUGCopyToDisplay();
  }

  GUGStopKeyboard();
  GUGEnd();

}

