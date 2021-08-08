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
#include "..\lib1\gug.h"      // Load the GUG definitions etc
#include "..\lib1\colors.h"
#include "..\lib1\keydefs.h"

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


  // draw a while bunch of overlapping string containing "G.U.G." in
  // different colors then cycle the palette
  for (x=0; x<200; ++x)
  {
    GUGPutText(x+10       ,      x,x/2,"G.U.G.");
    GUGPutText(319+10-48-x,199-8-x,x/2,"G.U.G.");
	GUGPutText(319+10-48-x,      x,x/2,"G.U.G.");
    GUGPutText(x+10       ,199-8-x,x/2,"G.U.G.");
    GUGPutText(144+10,96,45,"GUG");
    GUGCopyToDisplay();
  }
  sprintf((char *)mes,"GUG %s",GUGVersion());
  GUGPutText(144+10-19,192,215,(char *)mes);
  GUGCopyToDisplay();

  // Rotate the palette
  x = 0;
  while (x < 2) {
    GUGCyclePalette((char *)rotate_palette,1,215);
    delay(50);  // 50ms delay
    // if a key is hit then copy the screen to the save buffer
    if (GUGKeyHit()) {
      if (x == 0) {
        GUGGetKey();
	    GUGSaveDisplay((char *)save_buffer);
	    GUGClearDisplay();
	    GUGCenterText(90,215,"Screen saved in the Save Buffer");
        GUGCopyToDisplay();
        while (!GUGKeyHit()) {
		  GUGCyclePalette((char *)rotate_palette,1,215);
          delay(50);
		}
		GUGGetKey();
        // restore the screen from the save buffer
	    GUGRestoreDisplay((char *)save_buffer);
	  }
	  x++;
	}
  }
  GUGGetKey();

  // restore the 666 palette
  GUGSetPalette((char *)GUG_666_Palette);

  // line demo
  GUGClearDisplay();
  x=0;
  do {
    GUGLine(rand()/MAX_X,rand()/MAX_Y,
	        rand()/MAX_X,rand()/MAX_Y,
			rand()/MAX_C);
    // only copy to the screen after 50 lines have been drawn
    if (++x > 50) {
	  x = 0;
      GUGCenterFrameText(190,WHITE,"GUGLine() Demo",BLACK);
	  GUGCopyToDisplay();
	}
  }
  while (!GUGKeyHit());
  GUGGetKey();

  // Circle demo
  GUGClearDisplay();
  x=0;
  do {
    GUGCircle(rand()/200,
	          30,
			  rand()/MAX_C,
              rand()/MAX_X
              ,rand()/MAX_Y);

    // only copy to the screen after 50 lines have been drawn
    if (++x > 50) {
	  x = 0;
      GUGCenterFrameText(190,WHITE,"GUGCircle() Demo",BLACK);
	  GUGCopyToDisplay();
	}
  }
  while (!GUGKeyHit());
  GUGGetKey();

  // Filled Circle demo
  GUGClearDisplay();
  do 
  {
    x = rand()/MAX_X;
	y = rand()/MAX_Y;
	c = rand()/MAX_C;
    GUGFillCircle(rand()/200,30,c,x,y);
    GUGCenterFrameText(190,WHITE,"GUGFillCircle() Demo",BLACK);
	GUGCopyToDisplay();
  }
  while (!GUGKeyHit());
  GUGGetKey();

  // Filled Shape demo
  // Use the circle routine with a low number of line segments to
  //   draw shapes
  GUGClearDisplay();
  do 
  {
    x = rand()/MAX_X;
	y = rand()/MAX_Y;
	c = rand()/MAX_C;
    GUGCenterFrameText(190,WHITE,"GUG Filled Shapes Demo",BLACK);
	GUGFillCircle(rand()/200,rand()/3200+2,c,x,y);
    GUGCopyToDisplay();
  }
  while (!GUGKeyHit());
  GUGGetKey();

  // rect demo
  GUGClearDisplay();
  x=0;
  do {
    GUGRectangle(rand()/MAX_X,rand()/MAX_Y,
	        rand()/MAX_X,rand()/MAX_Y,
			rand()/MAX_C);
    // only copy to the screen after 50 rectangles are drawn
    if (++x > 50) {
	  x = 0;
      GUGCenterFrameText(190,WHITE,"GUGRectangle() Demo",BLACK);
	  GUGCopyToDisplay();
	}
  }
  while (!GUGKeyHit());
  GUGGetKey();

  // filled rect demo
  GUGClearDisplay();
  do {
    GUGFillRectangle(rand()/MAX_X,rand()/MAX_Y,
	        rand()/MAX_X,rand()/MAX_Y,
			rand()/MAX_C);
    GUGCenterFrameText(190,WHITE,"GUGFillRectangle() Demo",BLACK);
    GUGCopyToDisplay();
  }
  while (!GUGKeyHit());
  GUGGetKey();

  // Polygon demo
  GUGClearDisplay();
  x=0;
  do {
    i = rand() / 1638;
    for (y=0; y<i; ++y)
	{
	  poly[y].x = rand()/MAX_X;
	  poly[y].y = rand()/MAX_Y;
	}
	GUGPoly(rand()/MAX_C,i,poly);
    GUGCenterFrameText(190,WHITE,"GUGPoly() Demo",BLACK);
    GUGCopyToDisplay();
  }
  while (!GUGKeyHit());
  GUGGetKey();

  // Polygon demo
  GUGClearDisplay();
  x=0;
  do {
    i = rand() / 1638;
    for (y=0; y<i; ++y)
	{
	  poly[y].x = rand()/MAX_X;
	  poly[y].y = rand()/MAX_Y;
	}
	GUGFillPoly(rand()/MAX_C,i,poly);
    GUGCenterFrameText(190,WHITE,"GUGFillPoly() Demo",BLACK);
	GUGCopyToDisplay();
  }
  while (!GUGKeyHit());
  GUGGetKey();


  // Clipped Sprite Demo's
  i = 0;
  for (x=110; x<210; ++x)
  {
    GUGClearDisplay();
    GUGRectangle(140,80,180,120,RED);

    GUGClipFGSprite(x,90,
                    140,80,
                    180,120,
                    ship1_sprites[i]);
    if (++i == 60) i = 0;

    GUGCenterText(190,WHITE,"Clipped Sprite Demo");
    GUGCopyToDisplay();
    delay(10);
  }
  for (y=50; y<150; ++y)
  {
    GUGClearDisplay();
    GUGRectangle(140,80,180,120,RED);

    GUGClipFGSprite(150,y,
                    140,80,
                    180,120,
                    ship1_sprites[i]);
    if (++i == 60) i = 0;

    GUGCenterText(190,WHITE,"Clipped Sprite Demo");
    GUGCopyToDisplay();
    delay(10);
  }
  for (x=40; x<200; ++x)
  {
    GUGClearDisplay();
    GUGRectangle(140,80,180,120,RED);

    GUGClipFGSprite(x+60,x,
                    140,80,
                    180,120,
                    ship1_sprites[i]);
    if (++i == 60) i = 0;

    GUGCenterText(190,WHITE,"Clipped Sprite Demo");
    GUGCopyToDisplay();
    delay(10);
  }
  while (!GUGKeyHit());
  GUGGetKey();

  for (x=110; x<210; ++x)
  {
    GUGClearDisplay();
    GUGRectangle(140,80,180,120,RED);

    GUGClipMNSprite(x,90,
                    140,80,
                    180,120,
                    RED,
                    ship1_sprites[i]);
    if (++i == 60) i = 0;

    GUGCenterText(190,WHITE,"Clipped MN Sprite Demo");
    GUGCopyToDisplay();
    delay(10);
  }
  for (y=50; y<150; ++y)
  {
    GUGClearDisplay();
    GUGRectangle(140,80,180,120,RED);

    GUGClipMNSprite(150,y,
                    140,80,
                    180,120,
                    GREEN,
                    ship1_sprites[i]);
    if (++i == 60) i = 0;

    GUGCenterText(190,WHITE,"Clipped MN Sprite Demo");
    GUGCopyToDisplay();
    delay(10);
  }
  for (x=40; x<200; ++x)
  {
    GUGClearDisplay();
    GUGRectangle(140,80,180,120,RED);

    GUGClipMNSprite(x+60,x,
                    140,80,
                    180,120,
                    PURPLE,
                    ship1_sprites[i]);
    if (++i == 60) i = 0;

    GUGCenterText(190,WHITE,"Clipped MN Sprite Demo");
    GUGCopyToDisplay();
    delay(10);
  }
  while (!GUGKeyHit());
  GUGGetKey();

  // Draw Flipped Sprite Demo's
  GUGClearDisplay();

  GUGHLine(0,319,15,12);
  GUGVLine(0,199,15,12);

  GUGPutFGSprite(10,10,ship1_sprites[0]);

  GUGFlipXFGSprite( 50,10,ship1_sprites[0]);
  GUGFlipXBGSprite( 90,10,ship1_sprites[0]);
  GUGFlipXMNSprite(130,10,6,ship1_sprites[0]);

  GUGFlipXFGSprite(10, 50,ship1_sprites[0]);
  GUGFlipXBGSprite(10, 90,ship1_sprites[0]);
  GUGFlipXMNSprite(10,130,6,ship1_sprites[0]);

  GUGCenterText(190,WHITE,"Sprite X Flipped Demo");
  GUGCopyToDisplay();

  do {} while (!GUGKeyHit());
  GUGGetKey();

  GUGClearDisplay();

  GUGHLine(0,319,15,12);
  GUGVLine(0,199,15,12);

  GUGPutFGSprite(10,10,ship1_sprites[0]);

  GUGFlipYFGSprite( 50,10,ship1_sprites[0]);
  GUGFlipYBGSprite( 90,10,ship1_sprites[0]);
  GUGFlipYMNSprite(130,10,6,ship1_sprites[0]);

  GUGFlipYFGSprite(10, 50,ship1_sprites[0]);
  GUGFlipYBGSprite(10, 90,ship1_sprites[0]);
  GUGFlipYMNSprite(10,130,6,ship1_sprites[0]);

  GUGCenterText(190,WHITE,"Sprite Y Flipped Demo");
  GUGCopyToDisplay();

  do {} while (!GUGKeyHit());
  GUGGetKey();

/*
  GUGClearDisplay();
  GUGPutText(20,30,40,"Pixel Test");

  // draw a litte + sign in the upper left corner of the screen
  GUGSetPixel( 0, 0,24);
  GUGSetPixel(-1, 0,25);
  GUGSetPixel( 1, 0,26);
  GUGSetPixel( 0, 1,27);
  GUGSetPixel( 0,-1,28);

  GUGCopyToDisplay();

  // test the put/get pixel functions
  if (GUGGetPixel(0,0) == 24)
    GUGPutText(130,30,20,"GUGGetPixel() working");
  else
    GUGPutText(130,30,20,"GUGGetPixel() failed");
 
  if (GUGTestPixel(0,0,24) == 1)
    GUGPutText(130,40,20,"GUGTestPixel() working");
  else
    GUGPutText(130,40,20,"GUGTestPixel() failed");
 
  // now a + in the upper right corner
  GUGSetPixel(319, 0,24);
  GUGSetPixel(318, 0,25);
  GUGSetPixel(320, 0,26);
  GUGSetPixel(319, 1,27);
  GUGSetPixel(319,-1,28);

  // lower left corner
  GUGSetPixel( 0,199,24);
  GUGSetPixel(-1,199,25);
  GUGSetPixel( 1,199,26);
  GUGSetPixel( 0,200,27);
  GUGSetPixel( 0,198,28);

  // lower right corner
  GUGSetPixel(319,199,24);
  GUGSetPixel(318,199,25);
  GUGSetPixel(320,199,26);
  GUGSetPixel(319,200,27);
  GUGSetPixel(319,198,28);

  // center of the screen
  GUGSetPixel(159, 99,24);
  GUGSetPixel(158, 99,25);
  GUGSetPixel(160, 99,26);
  GUGSetPixel(159,100,27);
  GUGSetPixel(159, 98,28);

  GUGCopyToDisplay();
  while (!GUGKeyHit());
  GUGGetKey();

*/

  // test for FastSetPixel
  GUGClearDisplay();
  GUGPutText(20,30,40,"Fast Pixel Test");

  // draw a litte + sign in the upper left corner of the screen
  GUGFastSetPixel( 0, 0,24);
  GUGFastSetPixel(-1, 0,25);
  GUGFastSetPixel( 1, 0,26);
  GUGFastSetPixel( 0, 1,27);
  GUGFastSetPixel( 0,-1,28);

  GUGCopyToDisplay();

  // test the put/get pixel functions
  if (GUGGetPixel(0,0) == 24)
    GUGPutText(130,30,20,"(F) GUGGetPixel() working");
  else
    GUGPutText(130,30,20,"(F) GUGGetPixel() failed");
 
  if (GUGTestPixel(0,0,24) == 1)
    GUGPutText(130,40,20,"(F) GUGTestPixel() working");
  else
    GUGPutText(130,40,20,"(F) GUGTestPixel() failed");
 
  // now a + in the upper right corner
  GUGFastSetPixel(319, 0,24);
  GUGFastSetPixel(318, 0,25);
  GUGFastSetPixel(320, 0,26);
  GUGFastSetPixel(319, 1,27);
  GUGFastSetPixel(319,-1,28);

  // lower left corner
  GUGFastSetPixel( 0,199,24);
  GUGFastSetPixel(-1,199,25);
  GUGFastSetPixel( 1,199,26);
  GUGFastSetPixel( 0,200,27);
  GUGFastSetPixel( 0,198,28);

  // lower right corner
  GUGFastSetPixel(319,199,24);
  GUGFastSetPixel(318,199,25);
  GUGFastSetPixel(320,199,26);
  GUGFastSetPixel(319,200,27);
  GUGFastSetPixel(319,198,28);

  // center of the screen
  GUGFastSetPixel(159, 99,24);
  GUGFastSetPixel(158, 99,25);
  GUGFastSetPixel(160, 99,26);
  GUGFastSetPixel(159,100,27);
  GUGFastSetPixel(159, 98,28);

  GUGCopyToDisplay();
  while (!GUGKeyHit());
  GUGGetKey();




  // test Vline's
  GUGPutText(20,40,40,"VLine Test");
  GUGVLine(3,196,  0,28);
  GUGVLine(3,196,319,28);
  GUGCopyToDisplay();
  while (!GUGKeyHit());
  GUGGetKey();

  // test HLine's
  GUGPutText(20,50,40,"Hline Test");
  GUGHLine(3,316,  0,28);
  GUGHLine(3,316,199,28);
  GUGCopyToDisplay();
  while (!GUGKeyHit());
  GUGGetKey();

  // test Rectangle
  GUGPutText(20,60,40,"Rectangle Test");
  GUGRectangle(5,5,314,194,17);
  GUGCopyToDisplay();
  while (!GUGKeyHit());
  GUGGetKey();

  // test Filled Rectangle
  GUGFillRectangle(10,10,309,189,22);
  GUGPutText(20,70,40,"Filled Rectangle Test");
  GUGCopyToDisplay();
  while (!GUGKeyHit());
  GUGGetKey();

  // test the BG sprite function
  i = l = 0;
  do {
    // set the screen the color l
    GUGSetDisplay(l);
    for (x=-110; x<500; x+=30) {
	  for (y=-110; y<300; y+= 30) {
        GUGPutBGSprite(x,y,ship1_sprites[i]);
	  }
	}
	if (++i >  59) i = 0;
	if (++l > 215) l = 0;
    GUGCenterFrameText(190,WHITE,"GUG Background Sprites",BLACK);
    GUGCopyToDisplay();
  }
  while (!GUGKeyHit());
  GUGGetKey();

  // test the FG sprite function
  i = l = 0;
  do {
    GUGSetDisplay(l);
    for (x=-110; x<500; x+=30) {
	  for (y=-110; y<300; y+= 30) {
        GUGPutFGSprite(x,y,ship1_sprites[i]);
	  }
	}
	if (++i >  59) i = 0;
	if (++l > 255) l = 0;
    GUGCenterFrameText(190,WHITE,"GUG Foreground Sprites",BLACK);
    GUGCopyToDisplay();
  }
  while (!GUGKeyHit());
  GUGGetKey();

  // test MN sprite functions
  i = 1;
  l = 0;
  do {
    GUGSetDisplay(l);
    for (x=-110; x<500; x+=30) {
	  for (y=-110; y<300; y+= 30) {
        GUGPutMNSprite(x,y,i,ship1_sprites[i]);
	  }
	}
	if (++i >  59) i = 0;
	if (++l > 255) l = 0;
    GUGCenterFrameText(190,WHITE,"GUG Monocolored Sprites",BLACK);
    GUGCopyToDisplay();
  }
  while (!GUGKeyHit());
  GUGGetKey();


  // test the compiled sprite function
  x = test_spr();

  // if we have a mouse demo it!
  if (status == MOUSE_LOADED) {  // then mouse is installed
  GUGClearDisplay();
  GUGCenterText(100,30,"Click the mouse to continue");
  GUGCopyToDisplay();
  ox = 65535;;
  oy = 65535;
  GUGMouseShow();
  do {
    GUGMousePosition((unsigned int *)&button,
                     (unsigned int *)&mx,
                     (unsigned int *)&my);
    if ((ox != mx) || (oy != my)) {
      sprintf((char *)mes,"X:%3d y:%3d",mx,my);
      GUGFillRectangle(100,190,230,199,0);
      GUGCenterText(190,40,(char *)mes);
	  GUGMouseHide();
      GUGCopyToDisplay();
	  GUGMouseShow();
      ox = mx;
	  oy = my;
	}
//    delay(50);
  }
  while (!button);
  GUGMouseHide();

  do {
    GUGMousePosition((unsigned int *)&button,
                     (unsigned int *)&mx,
                     (unsigned int *)&my);
  }
  while (button);

  GUGClearDisplay();
  GUGCenterText(100,30,"Click the mouse to continue");
  GUGRectangle(80,50,240,150,20);
  GUGMouseHorizontalLimit(80,240);
  GUGMouseVerticalLimit(50,150);
  GUGCopyToDisplay();
  GUGMouseShow();
  ox = 65535;
  oy = 65535;
  do {
    GUGMousePosition((unsigned int *)&button,
                     (unsigned int *)&mx,
                     (unsigned int *)&my);
    if ((ox != mx) || (oy != my)) {
      sprintf((char *)mes,"X:%3d y:%3d",mx,my);
      GUGFillRectangle(100,190,230,199,0);
      GUGCenterText(190,40,(char *)mes);
	  GUGMouseHide();
      GUGCopyToDisplay();
      GUGMouseShow();
      ox = mx;
	  oy = my;
	}
//    delay(50);
  }
  while (!button);

  do {
    GUGMousePosition((unsigned int *)&button,
                     (unsigned int *)&mx,
                     (unsigned int *)&my);
  }
  while (button);
  GUGMouseHide();

  GUGClearDisplay();
  GUGSMShow();  // Show the Sprite Mouse
  GUGMouseHorizontalLimit(0,320);
  GUGMouseVerticalLimit(0,200);
  GUGCenterText(100,30,"Click the mouse to continue");
  GUGSMCopyToDisplay(mx,my);
  i = 0;
  do {

    GUG_Sprite_Mouse = ship1_sprites[i];
	if (++i >  59) i = 0;

    GUGMousePosition((unsigned int *)&button,
                     (unsigned int *)&mx,
                     (unsigned int *)&my);
    GUGClearDisplay();
    GUGCenterText(100,30,"Click the mouse to continue");
    sprintf((char *)mes,"X:%3d y:%3d",mx,my);
    GUGCenterText(190,40,(char *)mes);
    GUGSMCopyToDisplay(mx,my);
  }
  while (!button);

  do {
    GUGMousePosition((unsigned int *)&button,
                     (unsigned int *)&mx,
                     (unsigned int *)&my);
  }
  while (button);

  }

  // show off the kbd handling functions
  // shows the indexes into the GUG_key_table[] array,
  // puts a small arrow below the index number when a key is down
  GUGMouseHide();
  while(GUG_key_table[1]==0) {
					 // 1234567890123456789012345678901234567890
    GUGClearDisplay();
    GUGCenterText(  0,15,"Ground Up's MultiKey Handler Demo");
    GUGCenterText(192,20,"Play with the keys - <ESC> exits");

    GUGPutText(20, 24,50,"          1         2         3         ");
    GUGPutText(20, 32,50,"0123456789012345678901234567890123456789");

    GUGPutText(20, 56,50,"4         5         6         7         ");
    GUGPutText(20, 64,50,"0123456789012345678901234567890123456789");

    GUGPutText(20, 88,50,"                    1         1");
    GUGPutText(20, 96,50,"8         9         0         1         ");
    GUGPutText(20,104,50,"0123456789012345678901234567890123456789");

    GUGPutText(20,128,50,"1");
    GUGPutText(20,136,50,"2");
    GUGPutText(20,144,50,"01234567");

    sprintf((char *)mes,        "                                        ");
    for (x=0; x<40; ++x) {
	  if (GUG_key_table[x] > 0) mes[x] = '';
	}
	GUGPutText(20,40,55,(char *)mes);

    sprintf((char *)mes,        "                                        ");
    for (x=40; x<80; ++x) {
	  if (GUG_key_table[x] > 0) mes[x-40] = '';
	}
	GUGPutText(20,72,55,(char *)mes);

    sprintf((char *)mes,        "                                        ");
    for (x=80; x<120; ++x) {
	  if (GUG_key_table[x] > 0) mes[x-80] = '';
	}
	GUGPutText(20,112,55,(char *)mes);

    sprintf((char *)mes,"        ");
    for (x=120; x<128; ++x) {						   
	  if (GUG_key_table[x] > 0) mes[x-120] = '';
	}
	GUGPutText(20,152,55,(char *)mes);

    GUGCopyToDisplay();
  }

  // Remove any buffered up key strokes
  while (GUG_key_table[ESC] == KEY_IS_DOWN)
  {
   x++;
  }

  while (GUGKeyHit())
  {
    GUGGetKey();
  }

  // Demo joystick stuff
  do_joystick();

  GUGStopKeyboard();
  GUGMouseReset((int *)&status,(unsigned int *)&button);
  GUGEnd();
}

//**************************************************************************
// Test spritres
//

int test_spr(void)
{
  int   i,xs,ys,l,x,y;
  int   start,sample,frames,rt;
  float fps;
  char  buf[40];

  l = i = 0;
  // gonna use the 18.2ms timer to count FPS
  start  = clock();
  while (start == clock());
  frames = 0;
  do
  {
    // reset the display to color l
    GUGSetDisplay(l);

    if (++l > 255) l = 0;

    // draw the compiled sprites ever 30 pixels starting off the screen
	// and ending off the other corner of the screen
    for (x=0; x<12; x++) {
	  for (y=0; y<8; y++) {
	    xs = (x * 30)-15;
	    ys = (y * 30)-15;
        // draw_alien_ship was created by spr2asm
        draw_ship(i,xs,ys);
	  }	// of for y
	}	// of for x

    // increment the sprite counter, 0-59 are valid
    i++;
    if (i > MAX_SHIP1_SPRITES) i = 0;

    // how much elapsed time
    sample = clock();

    // count the frames and calc the FPS
    frames++;
    rt  = (sample - start); // / CLOCKS_PER_SEC;
    fps	= ((float)frames / (float)rt) * CLOCKS_PER_SEC;
	sprintf((char *)buf,"RT:%5d Frms:%5d FPS:%7.2f",rt,frames,fps);
	GUGCenterFrameText(180,WHITE,(char *)buf,BLACK);
	GUGCenterFrameText(190,WHITE,"Compiled Sprite Demo",BLACK);
    // let em see the sprites we drew
    GUGCopyToDisplay();
  }
  while (!GUGKeyHit());

  GUGGetKey();

  return(fps);
}


void do_joystick(void)
{
  int    x,y,ox,oy;
  int    i,f;
  char   mes[120];

  GUGInitTimer();

  i = GUGJoystickCalibrate();

  if (i == 0) return;

  GUGClearDisplay();

  x = ox = GUGScaleX1Axis();
  delay(10);
  y = oy = GUGScaleY1Axis();
  delay(10);

  while (GUG_key_table[ESC] == KEY_IS_UP)
  {
    if (GUGReadButtons() & J1_B1)
	{
	  GUGClearDisplay();
	}

    if (f == 0)
	{
      delay(5);
      x = GUGScaleX1Axis();	 // On even frames (f = 0)
    }
    else
    {
      delay(5);
      y = GUGScaleY1Axis();	 // On odd frames (f = 1)
 	}

	++f;	  // Increment f
	f &= 1;	  // F will always = 0 or one only

 	GUGLine(ox*3.2,oy*2.0,x*3.2,y*2.0,120);
	ox = x;
	oy = y;

    GUGCenterText(180,RED,"Button 1 to clear - <ESC> to exit");
    GUGCenterText(190,WHITE,"Joystick Handler Demo");
    GUGFastCopy(VGA_START);
  }
}


