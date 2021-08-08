#include <stdio.h>
#include <i86.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <gug.h>
#include <keydefs.h>

#define MAX 256

void main(int argc,char *argv[]) {
  char *spr[MAX];
  int  sprites = 0;
  int  i,c;
  int status;
  unsigned int buttons;
  unsigned int mx,my,mb,sx,sy;
  unsigned int ox,oy,cx,cy,dx,dy;
  GUG_PCX *gug_pcx;
  char mes[80];

  if (argc < 3) {
    printf("\n\nSprite Ripper - Version 0.5 - GUG Version %s\n",GUGVersion());
	printf("  Copyright 1995-1996 Ground Up Software\n");
    printf("  usage: ripper pcx_file spr_file [pal_file]\n\n\n");
	return;
  }

  // Clear the sprite pointers
  for (i=0; i<MAX; ++i) {
    spr[i] = NULL;
  }

// [fold]  [
  // Initialize GUG
  GUGInitialize();

// [fold]  ]
  // Load the requested PCX
  if ((gug_pcx = GUGReadPCX(argv[1])) == NULL) {
    GUGEnd();
    printf("Error - Unable to load %s\n",argv[1]);
    return;
  }

  // Start GUG's keyboard handler
  GUGStartKeyboard();

  // Initialize and show the mouse
  GUGMouseReset((int *)&status,(unsigned int *)&buttons);
  if (status == MOUSE_FAILED) {
    GUGEnd();
	printf("ripper requires a mouse to work properly\n");
	return;
  }
  GUGMouseShow();

  // Copy the PCX in buffer too the VGA cards memory
  GUGMouseHide();
  GUGClearDisplay();
  GUGShowPCX(0,0,gug_pcx);
  GUGCopyToDisplay();
  GUGMouseShow();

  c = 1; // c is the color of the flashing rectangle

  // Don't exit until ESC is pressed
  while (GUG_key_table[ESC] == KEY_IS_UP) {
    // Get the mouse X/Y and BUTTON status
    GUGMousePosition((unsigned int *)&mb,
	                 (unsigned int *)&mx,
					 (unsigned int *)&my);

    if (mb == MOUSE_BUTTON_LEFT) {
      // sx/sy track the upper left corner for the rectangle
	  sx = mx;
	  sy = my;
	  ox = oy = 64000;

      GUGMouseHide();
      // while the button is down size the rectangle
      while (mb == MOUSE_BUTTON_LEFT) {
        GUGMousePosition((unsigned int *)&mb,
	                     (unsigned int *)&mx,
					     (unsigned int *)&my);

         // Only track movement down or right
         if (mx < sx) mx = sx;
		 if (my < sy) my = sy;
		 // Rectangle is clipped to 32x32 pixels max
//         if ((mx-sx) > 31) mx = sx + 31;
//		   if ((my-sy) > 31) my = sy + 31;
		 // if the rect has a new size recopy the PCX to the VGA
         if ((ox != mx) || (oy != my)) {
           GUGClearDisplay();
           GUGShowPCX(0,0,gug_pcx);
           ox = mx;
		   oy = my;
		 }
         // draw the rectangle
         GUGRectangle(sx,sy,mx,my,c);
         sprintf(mes,"%1dx%1d",abs(sx-mx)+1,abs(sy-my)+1);
		 if (sy > 100)
		   GUGCenterFrameText(0,c,mes,0);
		 else
		   GUGCenterFrameText(190,c,mes,0);
         GUGCopyToDisplay();
		 // cycle the color of the rectangle
		 if (++c > 214) c = 1;
	  }  // of while()
      GUGMouseShow();

      // Flash the Rectangle
      while ((mb == MOUSE_NO_BUTTON) &&
             (GUG_key_table[ESC] == KEY_IS_UP)) {
        GUGMousePosition((unsigned int *)&mb,
	                   (unsigned int *)&mx,
			           (unsigned int *)&my);
        // continue to draw the rectangle makeing the color flash
        GUGRectangle(sx,sy,ox,oy,c);
		GUGCopyToDisplay();
	    if (++c > 214) c = 1;

        // Advance the rectangle
		if (GUG_key_table[NUM_PLUS] == KEY_IS_DOWN) {
		  dx = ox - sx;
		  dx++;
		  dy = oy - sy;
		  dy++;
		  sx += dx;
		  ox += dx;
          if (ox > 319) {
		    sx = 0;
			ox = dx-1;
			if (oy < 199) {
			  sy += dy;
			  oy += dy;
			}
		  }
		  GUG_key_table[NUM_PLUS] = KEY_IS_UP;
		}

        // Shrink the Rectangle???
        if ((GUG_key_table[LEFT_CTRL]  == KEY_IS_DOWN) ||
            (GUG_key_table[RIGHT_CTRL] == KEY_IS_DOWN)) {

          // Move Left Side in???
          if ((GUG_key_table[LEFT_ARROW] == KEY_IS_DOWN) ||
              (GUG_key_table[LEFT_NUM]   == KEY_IS_DOWN)) {
		    if (sx < (ox-2)) sx++;
           GUGClearDisplay();
			GUGShowPCX(0,0,gug_pcx);
 			GUGCopyToDisplay();
			GUG_key_table[LEFT_ARROW] = KEY_IS_UP;
			GUG_key_table[LEFT_NUM]   = KEY_IS_UP;
 		  }

          // Move Right Side in???
          if ((GUG_key_table[RIGHT_ARROW] == KEY_IS_DOWN) ||
              (GUG_key_table[RIGHT_NUM]   == KEY_IS_DOWN)) {
		    if (sx < (ox-2)) ox--;
           GUGClearDisplay();
            GUGShowPCX(0,0,gug_pcx);
 			GUGCopyToDisplay();
			GUG_key_table[RIGHT_ARROW] = KEY_IS_UP;
			GUG_key_table[RIGHT_NUM]   = KEY_IS_UP;
 		  }

          // Move Top Side down???
          if ((GUG_key_table[UP_ARROW] == KEY_IS_DOWN) ||
              (GUG_key_table[UP_NUM]   == KEY_IS_DOWN)) {
		    if (sy < (oy-2)) sy++;
           GUGClearDisplay();
            GUGShowPCX(0,0,gug_pcx);
 			GUGCopyToDisplay();
			GUG_key_table[UP_ARROW] = KEY_IS_UP;
			GUG_key_table[UP_NUM]   = KEY_IS_UP;
 		  }

          // Move Bottom Side Up???
          if ((GUG_key_table[DOWN_ARROW] == KEY_IS_DOWN) ||
              (GUG_key_table[DOWN_NUM]   == KEY_IS_DOWN)) {
		    if (sy < (oy-2)) oy--;
           GUGClearDisplay();
            GUGShowPCX(0,0,gug_pcx);
 			GUGCopyToDisplay();
			GUG_key_table[DOWN_ARROW] = KEY_IS_UP;
			GUG_key_table[DOWN_NUM]   = KEY_IS_UP;
 		  }

        }  // end of shrink the rectangle

        // Grow the Rectangle???
        else if ((GUG_key_table[LEFT_ALT]  == KEY_IS_DOWN) ||
                 (GUG_key_table[RIGHT_ALT] == KEY_IS_DOWN)) {

          // Move Left Side out???
          if ((GUG_key_table[LEFT_ARROW] == KEY_IS_DOWN) ||
              (GUG_key_table[LEFT_NUM]   == KEY_IS_DOWN)) {
		    if (sx > (ox-32)) sx--;
           GUGClearDisplay();
            GUGShowPCX(0,0,gug_pcx);
 			GUGCopyToDisplay();
			GUG_key_table[LEFT_ARROW] = KEY_IS_UP;
			GUG_key_table[LEFT_NUM]   = KEY_IS_UP;
 		  }

          // Move Right Side out???
          if ((GUG_key_table[RIGHT_ARROW] == KEY_IS_DOWN) ||
              (GUG_key_table[RIGHT_NUM]   == KEY_IS_DOWN)) {
		    if (sx > (ox-32)) ox++;
           GUGClearDisplay();
            GUGShowPCX(0,0,gug_pcx);
 			GUGCopyToDisplay();
			GUG_key_table[RIGHT_ARROW] = KEY_IS_UP;
			GUG_key_table[RIGHT_NUM]   = KEY_IS_UP;
 		  }

          // Move Top Side up???
          if ((GUG_key_table[UP_ARROW] == KEY_IS_DOWN) ||
              (GUG_key_table[UP_NUM]   == KEY_IS_DOWN)) {
		    if (sy > (oy-32)) sy--;
           GUGClearDisplay();
            GUGShowPCX(0,0,gug_pcx);
 			GUGCopyToDisplay();
			GUG_key_table[UP_ARROW] = KEY_IS_UP;
			GUG_key_table[UP_NUM]   = KEY_IS_UP;
 		  }

          // Move Bottom Side Down???
          if ((GUG_key_table[DOWN_ARROW] == KEY_IS_DOWN) ||
              (GUG_key_table[DOWN_NUM]   == KEY_IS_DOWN)) {
		    if (sy > (oy-32)) oy++;
           GUGClearDisplay();
            GUGShowPCX(0,0,gug_pcx);
 			GUGCopyToDisplay();
			GUG_key_table[DOWN_ARROW] = KEY_IS_UP;
			GUG_key_table[DOWN_NUM]   = KEY_IS_UP;
 		  }

        }  // end of grow the rectangle

        else if ((GUG_key_table[LEFT_ARROW] == KEY_IS_DOWN) ||
            (GUG_key_table[LEFT_NUM]   == KEY_IS_DOWN)) {
		  if (sx > 0) {
		    sx -= 1;
			ox -= 1;
           GUGClearDisplay();
            GUGShowPCX(0,0,gug_pcx);
 			GUGCopyToDisplay();
			GUG_key_table[LEFT_ARROW] = KEY_IS_UP;
			GUG_key_table[LEFT_NUM]   = KEY_IS_UP;
 		  }
		}

        // Move Rectangle Right???
        else if ((GUG_key_table[RIGHT_ARROW] == KEY_IS_DOWN) ||
            (GUG_key_table[RIGHT_NUM]   == KEY_IS_DOWN)) {
		  if (ox <319) {
		    sx += 1;
			ox += 1;
           GUGClearDisplay();
            GUGShowPCX(0,0,gug_pcx);
 			GUGCopyToDisplay();
			GUG_key_table[RIGHT_ARROW] = KEY_IS_UP;
			GUG_key_table[RIGHT_NUM]   = KEY_IS_UP;
 		  }
		}

        // Move Rectangle Uo???
        else if ((GUG_key_table[UP_ARROW] == KEY_IS_DOWN) ||
            (GUG_key_table[UP_NUM]   == KEY_IS_DOWN)) {
		  if (sy > 0) {
		    sy -= 1;
			oy -= 1;
           GUGClearDisplay();
            GUGShowPCX(0,0,gug_pcx);
 			GUGCopyToDisplay();
			GUG_key_table[UP_ARROW] = KEY_IS_UP;
			GUG_key_table[UP_NUM]   = KEY_IS_UP;
 		  }
		}

        // Move Rectangle Down???
        else if ((GUG_key_table[DOWN_ARROW] == KEY_IS_DOWN) ||
            (GUG_key_table[DOWN_NUM]   == KEY_IS_DOWN)) {
		  if (oy < 199) {
		    sy += 1;
			oy += 1;
           GUGClearDisplay();
            GUGShowPCX(0,0,gug_pcx);
 			GUGCopyToDisplay();
			GUG_key_table[DOWN_ARROW] = KEY_IS_UP;
			GUG_key_table[DOWN_NUM]   = KEY_IS_UP;
 		  }
		}

        // Rip and Save the Sprite
        else if (GUG_key_table[SPACE] == KEY_IS_DOWN) {
          // Restore so the rectangle is replaced
          GUGClearDisplay();
          GUGShowPCX(0,0,gug_pcx);
 	      GUGCopyToDisplay();
		  // clip out the sprite
 	      spr[sprites] = GUGClipSprite(sx,sy,ox,oy);
          // Make the sprite flash
          for (mx=0; mx<20; ++mx) {
            GUGPutMNSprite(sx,sy,c,spr[sprites]);
            GUGCopyToDisplay();
			if (c++ > 215) c=1;
		  }
           GUGClearDisplay();
          GUGShowPCX(0,0,gug_pcx);
 		  GUGCopyToDisplay();
          // point to the next sprite
		  if (sprites < MAX-1) ++sprites;
	      GUG_key_table[SPACE] = KEY_IS_UP;
		}
      }

      // should we save the sprite
      if (mb == MOUSE_BUTTON_RIGHT) {
        GUGMouseHide();
        // Restore so the rectangle is replaced
           GUGClearDisplay();
        GUGShowPCX(0,0,gug_pcx);
 	    GUGCopyToDisplay();
		// clip out the sprite
 	    spr[sprites] = GUGClipSprite(sx,sy,ox,oy);
        // Make the sprite flash
        for (mx=0; mx<20; ++mx) {
          GUGPutMNSprite(sx,sy,c,spr[sprites]);
          GUGCopyToDisplay();
		  if (c++ > 215) c=1;
		}
           GUGClearDisplay();
        GUGShowPCX(0,0,gug_pcx);
 		GUGCopyToDisplay();
        GUGMouseShow();
        // point to the next sprite
		if (sprites < MAX-1) ++sprites;
        // wait for the mouse buttons the be released
	    while(mb != MOUSE_NO_BUTTON) {
          GUGMousePosition((unsigned int *)&mb,
	                       (unsigned int *)&mx,
			               (unsigned int *)&my);
		}
	  }
    } // of mb == 1
  }   // of esc not hit

  GUGMouseHide();
  GUGMouseReset((int *)&status,(unsigned int *)&buttons);

  // Remove the keyboard handler
  GUGStopKeyboard();

  // Stop GUG
  GUGEnd();

  // Did the user want a palette file
  if (argc > 3) {
    if (GUGSavePalette(argv[3],gug_pcx->palette) == 1) {
	  printf("Palette saved in %s\n",argv[3]);
	}
	else {
	  printf("Error - Not able to create %s\n",argv[3]);
	}
  }

  // Were there sprites clipped
  if (sprites > 0) {
    if (GUGSaveSprite(argv[2],spr,sprites-1) != 1) {
      printf("Error - Unable to create %s\n",argv[2]);
    }
    else {
      printf("Ripped/Saved %d sprites in %s\n",sprites,argv[2]);
      printf("Normal program termination\n");
    }
  }
  else
  {
    printf("No sprites were ripped\n");
  }
}
// [fold]  1
