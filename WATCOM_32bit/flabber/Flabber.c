#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include "flabber.h"
#include "math.h"
#include "util.h"
#include "\watcom\gug\lib1\gug.h"      // Load the GUG definitions etc
#include "\watcom\gug\lib1\colors.h"
#include "\watcom\gug\lib1\keydefs.h"
#include "\watcom\vat\vat.h"

#define SCANCODE_TAB 0x0f

enum {music_nomusic=0, music_on};

int mousedone = FALSE;
int mousebusy = FALSE;

int musicstatus = music_nomusic;
int giStatusMode = FALSE;
int giMouseReverse = FALSE;
int giMouseTile = 0;
DWORD gdwFrame = 0;
int giStressMode = stressmode_off;
int giStressRepeat = 0;
int giStressFrame = 0;
char giStressKey = 0;
int giTextType = 0;
int giUserDidSomething = FALSE;

BYTE gNoteKey[] = {0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD};
int giNumNoteKeys = 12;

BYTE gAnimKey[] = {0x3d,0x3f,0x41,0x43,0x44,0x57,0x58,0x50,0x51};
int giNumAnimKeys = 9;

BYTE gBrushKey[] = {0x18,0x1a,0x28,0x2B,0x35};
int giNumBrushKeys = 5;

BYTE gRegularKey[] = {0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,
											0x19,0x1b,0x1c,0x1E,0x1F,0x20,0x21,0x22,
											0x23,0x24,0x25,0x26,0x2C,0x2D,0x2E,
											0x30,0x31,0x32,0x37,0x39,0x3b,0x3c,0x3e,
											0x40,0x47,0x48,0x49,0x4b,0x4c,0x4f,
											0x62,0x63,0x64,0x65,0x68,0x6a,0x6b,0x6c
											};
int giNumRegularKeys = 46;
int gilastmusiccounter = 0;



// ------------    Other Vairables

#ifdef __cplusplus                     // Wrapper for function prototypes.
extern "C" {                           // Necessary for C++ compilers.
#endif


extern SHORT           mod_currenttick;
extern SHORT           mod_tablepos;
extern BYTE           *mod_pstop, *mod_pattern;

extern SHORT           s3m_currenttick;
extern SHORT           s3m_tablepos;
extern BYTE           *s3m_pstop, *s3m_pattern;

extern SHORT           s3m_order;
extern SHORT           s3m_divbytes;

extern DWORD					internal_sample_rate;

extern volatile WORD   DSP_overhead;

#ifdef __cplusplus
}                                      // End C++ prototype wrapper.
#endif



/**************************************************************************
	int checkquit(void)

	DESCRIPTION:  Asks the user if they really want to quit.  Returns true if
								they do.

**************************************************************************/
int checkquit(void)
{
	int i,t=0;
	int tick_wait,pcount  = 0;
	int flag = 0;
	char r;
															 // Preserve the screen
	GUGBlockGet(0,0,maxx-1,maxy-1,grbWorkSpace);
															 // Prepare a few things
	tick_wait = CLK_TCK/20;
	if(!tick_wait)tick_wait = 1;

															 // Draw a thing for the user
	for(i = 0; i < 80; i++) {
		GUGDrawRectangle(SET,i+48,i,i,319-i,199-i);
		GUGCopyToDisplay();

	}

	GUGDrawFillRectangle(SET,0,i,i,319-i,199-i);
	print(SET,63,0,i+25,i+10,"Do you really want\nto quit? (Y/N)");
																// Main loop
	GUGCopyToDisplay();
	while(!flag) {
		if(clock()>= t) {
			t = clock()+tick_wait;


			// ---------------------------------------------------
			GUGVSync();
			dopalette(pcount++);
			// ---------------------------------------------------

		}
		if(GUGKeyHit()) {
			r = GUGGetKey();
			if(r == 'y' || r == 'Y') flag = 2;
			else flag = 1;
		}
	}

	GUGPutBGSprite(0,0,(char *)grbWorkSpace);

	return flag -1;
}


/**************************************************************************
	void flabber()

	DESCRIPTION:

**************************************************************************/
void flabber()
{
	int i,t = 0,j;
	int tabup = TRUE;
	int drewlockpreview = FALSE;
//	int x=0,y=0,c=0;
	char r= 0,scan,quitkey;
	int flag = 1;
	int tick_wait;
	int pcount = 0;
	unsigned int mb=0,mx=0,my=0;
	unsigned int oldmb=9999,oldmx=9999,oldmy=9999;
	BYTE wb,wy;
	WORD wx;
	int automouse = FALSE;
	int autokey = FALSE;
	DWORD nextframe = 0xffffffff;
	char autotype = 0;
	int waitingframe = TRUE;
	int scanning = FALSE;
	double dist;
	CRoutine *cr,*crnext;
	int stillgoing;
	int wroteframe;
	int tweenframes=0;
	int repframe;
	int typeframe = 0;
	int tabcount=0;
	int capscount=0;
	double ohead,averageohead;
	char typed[32] = {"---------|---------|---------|-"};
	double ssx= 180,ssy=180,sstx = 180,ssty = 100,ssxm= 0,ssym = 0;
	unsigned int testmovex,testmovey,testbuttons,tb,tx,ty;
	BYTE repeatkey;
	BYTE playnote = 0;
	int repeatcount = 0;
	int targetbrushsize = giBrushSize;
	clock_t ct = clock();

																// Randomize
	for(i = 0; i < (ct % 5000); i++) j = random(10000);

	typed[31]  = 0;

	DSP_overhead = 1;

	GUGStartKeyboard();              // Start special keyboard handler
																// Get start mouse position
	GUGMousePosition(&testbuttons,&testmovex,&testmovey);   

	
	tick_wait = CLK_TCK/20;
	if(!tick_wait)tick_wait = 1;
//	tick_wait = 10;

															// Gather automated information
	if(gpAutoFile && waitingframe) {
		autotype = (char)fgetc(gpAutoFile);
		if(autotype != 'F') {
			fclose(gpAutoFile);
			gpAutoFile= NULL;
		}
		else {
			fread(&nextframe,sizeof(DWORD),1,gpAutoFile);
			waitingframe = FALSE;
		}
	}
																 // Start up with music if requested
	if(giStartWithMusic) playmusic(1);

																// **** MAIN LOOP ****

	while(flag) {


		gdwFrame++;

		wroteframe = FALSE;
		if (!gpAutoFile) automouse = FALSE;
		autokey = FALSE;
																// Gather automated information
		if(gpAutoFile && waitingframe) {
			fread(&nextframe,sizeof(DWORD),1,gpAutoFile);
			waitingframe = FALSE;
		}

		if(gpAutoFile && gdwFrame == nextframe) {
			scanning = TRUE;
			while(scanning) {
				autotype = (char)fgetc(gpAutoFile);
				if(autotype == 'M') {
					fread(&wb,sizeof(BYTE),1,gpAutoFile);
					fread(&wx,sizeof(WORD),1,gpAutoFile);
					fread(&wy,sizeof(BYTE),1,gpAutoFile);
					mb = wb;
					mx = wx;
					my = wy;
					automouse = TRUE;
				}
				else if(autotype == 'K') {
					fread(&scan,sizeof(char),1,gpAutoFile);
					autokey = TRUE;
				}
				else if(autotype == 'F') {
					waitingframe = TRUE;
					scanning = FALSE;
				}
				else {
					fclose(gpAutoFile);
					gpAutoFile= NULL;
					scanning = FALSE;
				}
			}

		}
																// Keep the music Going!
		if(musicstatus == music_nomusic) {
			if(ModStatus() == v_started ||
				 S3MStatus() == v_started ||
				 MidiStatus() == v_started)
				musicstatus = music_on;
		}
		else if(gpMyMod) {
			giTempo = ModSetting(v_rate,GET_SETTING);
			if(ModStatus() == v_stopped) {
				playmusic(1);
				musicstatus = music_nomusic;
			}
		}
		else if(gpMyS3M) {
			giTempo = S3MSetting(v_rate,GET_SETTING);
			if(S3MStatus() == v_stopped) {
				playmusic(1);
				musicstatus = music_nomusic;
			}
		}
		else if(gpMyMidi) {
			giTempo = MidiSetting(v_rate,GET_SETTING);
			if(MidiStatus() == v_stopped) {
				playmusic(1);
				musicstatus = music_nomusic;
			}
		}
		else musicstatus = music_nomusic;


																// Keep on top of continuous waves
		if(!animfunc || animfunc == animation8) {
			if(giBackgroundSound) {
				WaveCommand(giBackgroundSound,v_stop);
			}
			giBackgroundSound = 0;
		}


		if(!automouse && !giScreenSaverMode) {
			GUGMousePosition(&mb,&mx,&my);   // pick up mouse info
			if(giMouseReverse) {
				mx = maxx-mx-1;
				my = maxy-my-1;
			}
		}

																// Record changes in mouse
		if(gpKeyFile) {
			if(mb != oldmb || mx != oldmx || my != oldmy) {
				fputc('F',gpKeyFile);
				fwrite(&gdwFrame,sizeof(DWORD),1,gpKeyFile);
				wroteframe = TRUE;
				fputc('M',gpKeyFile);
				wb = mb;
				wx = mx;
				wy = my;
				fwrite(&wb,sizeof(BYTE),1,gpKeyFile);
				fwrite(&wx,sizeof(WORD),1,gpKeyFile);
				fwrite(&wy,sizeof(BYTE),1,gpKeyFile);
			}

		}
		oldmb = mb;
		oldmx = mx;
		oldmy = my;


																// So that the mouse tracks on slower machines,
																// we must make sure the mouse and drawing
																// routines run at least 10 times between frames
		do {
			tweenframes++;
																	// Move mouse gradually
			dist = abs(gfprealmousex-mx) + abs(gfprealmousey-my);
			if(dist) {
				if (gfprealmousex != mx) gfprealmousex += (mx-gfprealmousex)/dist;
				if (gfprealmousey != my) gfprealmousey += (my-gfprealmousey)/dist;
			}
																	// Handle mouse actions
			if(mb) {
																	// Clear palette if it is there and we are
																	// starting to draw.
				if(mb & 0x01 && giPalPut) {
					GUGPutBGSprite(0,maxy-11,(char *)grbPaletteBlock);
					giPalPut = 0;
				}
				mousebusy = TRUE;

				if(giFloodFill) {
					GUGFloodFillColor(mx,my,giWorkingColor);
					giFloodFill = 0;
					while(mb) GUGMousePosition(&mb,&mx,&my);
				}
				else {
																	// If the tab key is pressed, then use the
																	// mouse to determine coordinates.
					if(GUG_key_table[SCANCODE_TAB]) {
						giMouseW = mx - giMouseX1;
						giMouseH = my - giMouseY1;
						giUseMouseCoords++;
					}
																	// Tile the mouse?
					else if (giMouseTile) {
																					 // grab color?
						if(mb & 2) {
							domouse(gfprealmousex,gfprealmousey,mb);
							giUserDidSomething = TRUE;
						}
						else {
							int xtile = ((int)gfprealmousex) % giMouseTile;
							int ytile = ((int)gfprealmousey) % giMouseTile;
							int xx,yy;

							for(xx = xtile-giMouseTile; xx < maxx+giMouseTile; xx += giMouseTile) {
								for(yy = ytile-giMouseTile; yy < maxy+giMouseTile; yy += giMouseTile) {
									domouse(xx,yy,mb);
								}
							}
						}
					}
					else {
						domouse(gfprealmousex,gfprealmousey,mb);
						giUserDidSomething = TRUE;
					}

				}

			}
			else {
				if(mousebusy) {           // Did we just let up the mouse?
					mousebusy = FALSE;
					mousedone = TRUE;
				}
				else {
					if(GUG_key_table[SCANCODE_TAB] && tabup) {
						giMouseX1 = mx;
						giMouseY1 = my;
						giMouseW = giMouseH = 0;
						giUseMouseCoords++;
					}
				}
				gfprealmousex = mx;
				gfprealmousey = my;
			}
																	// Clear the palette box on any mouse up event
			if(mousedone) {
				if(giPalPut) {
					GUGPutBGSprite(0,maxy-11,(char *)grbPaletteBlock);
					giPalPut = 0;
				}
				mousedone = FALSE;
			}



			// ------------------ Drawing routines ---------------------
			cr = gRoutineList;
			while(cr) {
				stillgoing = cr->draw();
				crnext = cr->Next();
				if(!stillgoing)  {
					if(cr == gRoutineList) gRoutineList = crnext;
					cr->unlinkme();
					delete cr;
				}
				cr = crnext;
			}

		} while(tweenframes < 15 && clock()>=t);

		// ------------------ KEYBOARD CHECKS ----------------------

		if(!GUG_key_table[SCANCODE_TAB]) tabup = TRUE;
		else tabup = FALSE;
																			// Handle click for Tab key
		if(GUG_key_table[SCANCODE_TAB]) {
			tabcount++;
			if(tabcount ==1) dosound(3);
		}
		else tabcount = 0;

																			// Handle click for Caps lock key
		if(GUG_key_table[SCANCODE_CAPS]) {
			capscount++;
			if(capscount ==1) dosound(35);
		}
		else capscount = 0;





		// ------------------ DISPLAY GRAPHICS ----------------------
		if(clock()>= t) {
																// Handle screensaver 
																// This only needs to happen once
																// per frame.
			if(giScreenSaverMode) {
																// mouse movement
				ssxm *= .85;
				ssym *= .85;
				ssx += ssxm; 
				ssy += ssym;

				if(ssx > maxx) ssx = maxx;
				if(ssy > maxy) ssy = maxy;
				if(ssx < 0) ssx = 0;
				if(ssy < 0) ssy = 0;

				if(ssx < sstx) ssxm += 1;
				if(ssx > sstx) ssxm -= 1;
				if(ssy < ssty) ssym += 1;
				if(ssy > ssty) ssym -= 1;

				if(mb && !random(50)) {
					sstx = random(maxx);
					ssty = random(maxy);
				}

				if(!random(300)) {
					mb ^= 1;
					if(mb) dokey(gBrushKey[random(giNumBrushKeys)]);
					sstx = random(maxx);
					ssty = random(maxy);
				}
				if(!random(100)) giWorkingColor = random(256);

				mx = ssx;
				my = ssy;
																// ************* Keystrokes ***********
																// regular keys
				if(repeatcount) {
					repeatcount--;
					if(!random(4)) dokey(repeatkey);
				}
				else {
					if(!random(800)) {
						repeatcount = random(400)+50;
						repeatkey = gRegularKey[random(giNumRegularKeys)];
					}
					if(!random(100)) {
						dokey(gRegularKey[random(giNumRegularKeys)]);
					}
				}	
																// play random notes
				if(playnote) {
					playnote--;
					if(!random(10)) 
						dokey(gNoteKey[random(giNumNoteKeys)]);
				}
				else {
					if(!random(500)) {
						dokey(0x29);
						playnote = random(500)+100;
					}
				}	
																// change effect

				if(!random(1500)) dokey(gAnimKey[random(giNumAnimKeys)]);
			  
																// Cancel everything
//				if(!random(15000)) dokey(0x0E);
																// handle music
				if(gilastmusiccounter > 15000) 	dokey(0x66); // next song
//				if(!random(10000)) dokey(0x66);	 // start music
//				if(!random(10000)) dokey(0x67);	 // Toggle music on/off

																// Brush size change
				if(giBrushSize < targetbrushsize) dokey(0x34);
				if(giBrushSize > targetbrushsize) dokey(0x33);
				if(!random(1000)) targetbrushsize = random(50) ;	 
				
																// special one-time keys
				if(!random(8000)) dokey(0x42);	// snow	
				if(!random(8000)) dokey(0x52);	// moire
				if(!random(8000)) dokey(0x4d);	// backward sounds
				if(!random(8000)) dokey(0x53);	// randomize sounds
				if(!random(4000)) dokey(0x45);	// dark/light color change

			}

			t = clock()+tick_wait;
																// Draw crosshairs if button is pushed
			if(mb) GUG_Sprite_Mouse = (char *)flabbersprite[cursor_x];
			else GUG_Sprite_Mouse = (char *)flabbersprite[giMouseCursor];

			if(giFloodFill) GUG_Sprite_Mouse = (char *)flabbersprite[cursor_fill];

																// Handle Lock 'n drag key stuff
			if(GUG_key_table[SCANCODE_TAB]) {
				GUG_Sprite_Mouse = (char *)flabbersprite[cursor_plus];
				GUGDrawCircle(XOR,63,giMouseX1,giMouseY1,
											sqrt(giMouseW*giMouseW + giMouseH*giMouseH));
				GUGDrawLine(XOR,63,giMouseX1,giMouseY1,
											giMouseX1 + giMouseW,giMouseY1 + giMouseH);
				GUGDrawRectangle(XOR,63,giMouseX1,giMouseY1,
											giMouseX1 + giMouseW,giMouseY1 + giMouseH);
				drewlockpreview = TRUE;
			}
			if(!giFloodFill) GUGSMDraw(mx-8,my-8);
			else GUGSMDraw(mx-4,my-14);

																// SPecial debug status info
			if(giStatusMode) {
				giPrintTransparent = FALSE;
				print(SET,63,0,0,0,"Frame: %d,(%d) ",gdwFrame,giDrawFrameCount);
				print(SET,63,0,190,0,"Version: %s",VERSION);
				print(SET,15,0,0,10,"Ms%d M%d S%d Tm%d ",musicstatus,ModStatus(),S3MStatus(),giTempo);
				if(gpMyMod) {
					print(SET,15,0,0,20,"M1: %s  (POS: %x/%x DIV: %X)          ",
								gpMyMod->title,
								mod_tablepos,
								gpMyMod->num_positions,
								64-(long)(mod_pstop-mod_pattern)/16);
				}
				else if(gpMyS3M){
					print(SET,15,0,0,20,"M2: %s  (ORD: %x/%x DIV: %X)          ",
								gpMyS3M->title,
								s3m_order,
								gpMyS3M->orders,
								64-(long)(s3m_pstop-s3m_pattern)/s3m_divbytes);
				}
				else if(gpMyMidi){
					print(SET,15,0,0,20,"M3: %s            ",gpMyMidi->title);
				}
				else {
					print(SET,15,0,0,20,"                               ");
				}
				print(SET,31,0,0,30,"LastKey: %d  FPRef: %d   ",scan,tweenframes);

				if(giSoundOn) print(SET,31,0,0,40,"SR: %d   ",internal_sample_rate);
				else print(SET,31,0,0,40,"<No sound card detected>");

				if(!giDemoDays) print(SET,47,0,0,50,"Registered to: %s",gcUserName);
				else {
					print(SET,47,0,0,50,"Day %d of 30 day evaluation period",giDemoDays);
					if(giDemoDays > 30) print(SET,96,0,20,60,"Please Register");
				}

				ohead = (double)DSP_overhead/1.193/(1000000.0/(135.0*4))*100.0;
				averageohead *=.98;
				averageohead += ohead/50.0;
				print(SET,47,0,0,80,"VAT overhead: %.2lf%%",averageohead);

				print(SET,31,0,0,90,"Type '%s' to exit.",giHardQuit ? "qQ": "q");
			}

			drawwatermark();

			// ---------------------------------------------------
			GUGVSync();
			dopalette(pcount++);
			GUGCopyToDisplay();
			// ---------------------------------------------------

			erasewatermark();

			GUGSMUnDraw();
																// Handle Lock 'n drag key stuff (Tab key)
			if(drewlockpreview) {
				GUGDrawRectangle(XOR,63,giMouseX1,giMouseY1,
											giMouseX1 + giMouseW,giMouseY1 + giMouseH);
				GUGDrawLine(XOR,63,giMouseX1,giMouseY1,
											giMouseX1 + giMouseW,giMouseY1 + giMouseH);
				GUGDrawCircle(XOR,63,giMouseX1,giMouseY1,
											sqrt(giMouseW*giMouseW + giMouseH*giMouseH));
				drewlockpreview = FALSE;
			}
			// (animfunc && animfunc != animation8) animfunc(signal_continue);
			if (animfunc) animfunc(signal_continue);
			if (brushfunc) brushfunc(signal_continue);

			tweenframes = 0;
			giDrawFrameCount++;
																 // Yawn if user does nothing
			if(!giUserDidSomething && (giDrawFrameCount % 600) == 0) dosound(69);

																 // Handle Screensaver stuff
			if(giScreenSaverMode) {


																// See if we need to quit	 (any
																// mouse movement or keystroke)
				GUGMousePosition(&tb,&tx,&ty);
				if(tb != testbuttons ||
					 tx != testmovex ||
					 ty != testmovey ||
					 r) flag = 0;
			}
		}

																 // Handle stress mode
		if(giStressMode && giStressFrame != giDrawFrameCount) {
			giStressFrame = giDrawFrameCount;
			if(!giStressRepeat) {
				do {
					giStressKey = random(0x6F);
				} while (giStressKey > 0x58 && giStressKey < 0x60);
				if(giStressMode == stressmode_deliberate) giStressRepeat = random(100) + 20;
			}
			else giStressRepeat--;

																 // Save stress keystrokes to key file
			if(gpKeyFile) {
				if(!wroteframe) {
					fputc('F',gpKeyFile);
					fwrite(&gdwFrame,sizeof(DWORD),1,gpKeyFile);
					wroteframe = TRUE;
				}
				fputc('K',gpKeyFile);
				fwrite(&giStressKey,sizeof(char),1,gpKeyFile);

			}

			dokey(giStressKey);
		}
																 // Handle typing
		if(giTextType) {
			char z;

			if(giDrawFrameCount != typeframe) { // Flash the cursor
				typeframe = giDrawFrameCount;
				typer(2);
			}

/*			if(GUGKeyHit()) {
				z = GUGGetKey();
				if(z == 13) z = '\n';
				typer(z);
				if(z == '\n') {
					typer(0);
					giTextType = 0;
				}
			}


			while(GUGScanKeyHit()) scan = GUGGetScanCode();*/
		}


																 // Handle regular keystrokes
		if(GUGScanKeyHit() || autokey) {
			quitkey = FALSE;
			while(GUGKeyHit()) {
				r = GUGGetKey();
				if(r == 'Q' || r == 'q') quitkey = TRUE;
				memcpy(typed,typed+1,31);
				typed[30] = r;
			}
			if(!autokey) while(GUGScanKeyHit()) scan = GUGGetScanCode();

																 // Move palette out of the way
			if(giPalPut && giPalPut != 0x19) {
					GUGPutBGSprite(0,maxy-11,(char *)grbPaletteBlock);
					giPalPut = 0;
					mousedone = FALSE;
			}

																 // Save to keystroke file
			if(gpKeyFile) {
				if(!wroteframe) {
					fputc('F',gpKeyFile);
					fwrite(&gdwFrame,sizeof(DWORD),1,gpKeyFile);
					wroteframe = TRUE;
				}
				fputc('K',gpKeyFile);
				fwrite(&scan,sizeof(char),1,gpKeyFile);

			}
																 // Handle Typeing
			if(giTextType &&  (isprint(r) || r == 13)) {
				if(r == 13) r = '\n';
				dosound(68);
				typer(r);
				if(r == '\n') {
					typer(0);
					giTextType = 0;
				}
				typed[30] = ' ';							// Foil quit mechanism!
			}
			else {
				dokey(scan);               // Execute the keystroke
				if(!giHardQuit && quitkey && checkquit()) flag = 0;
			}
			giUserDidSomething = TRUE;

		}




															 // Quit flabbergasted?
		if(giHardQuit) {
			if(strstr(typed,"qQ")) {
				if(checkquit()) flag = 0;
				else memset(typed,' ',31);
			}
		}

		if(strstr(typed,"Varmint")) {
			giEggMe = 1;
			memset(typed,' ',31);    // Clear special signal array
		}
	}

															 // **** END MAIN LOOP ****
	GUGStopKeyboard();              // Stop special keyboard handler

}