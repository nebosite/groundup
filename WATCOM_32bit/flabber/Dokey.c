//
// DOKEY.C
//
// Keystroke handler for flabbergasted
//
// Author:  Eric Jorgensen

#include "flabber.h"
#include "math.h"
#include "util.h"
#include "malloc.h"
#include "\watcom\gug\lib1\gug.h"
#include "\watcom\gug\lib1\colors.h"
#include "\watcom\gug\lib1\keydefs.h"
#include "\watcom\vat\vat.h"
#include "routine.h"



int note[13] = {60,62,64,65,67,69,71,72,74,76,77,79,81};
int notesound = 1;
signed char errstring[256];
int giTempo = 440;
int giSoundsRandomized = FALSE;
int giMusicWasOn = FALSE;

extern int giMouseReverse;
extern int giMouseTile;


void checkerblack(VARPACKET *vp);



/**************************************************************************
	void checkmemory(void)

	DESCRIPTION:

**************************************************************************/
void checkmemory(void)
{
	int i;

	giPrintTransparent = FALSE;

	if(!memorytest_preallochunk)
		print(SET,15,36,0,145,"Memory: Preallochunk Unallocated");
	if(!memorytest_postallochunk)
		print(SET,15,36,0,135,"Memory: Postallochunk Unallocated");

	for(i = 0; i < MEMTESTSIZE; i++) {
		if(memorytest_prehunk[i]) {
			print(SET,15,4,0,155,"Memory: Prehunk Corrupt!");
			return;
		}
		if(memorytest_posthunk[i]) {
			print(SET,15,4,0,155,"Memory: Posthunk Corrupt!");
			return;
		}

		if(memorytest_preallochunk && *(memorytest_preallochunk + i))
			print(SET,15,4,0,155,"Memory: Preallochunk Corrupt!");
		if(memorytest_postallochunk && *(memorytest_postallochunk + i))
			print(SET,15,4,0,155,"Memory: Postallochunk Corrupt!");
	}

	print(SET,15,36,0,155,"Memory: AOK!");

}
/**************************************************************************
	void setanimfunc(int (*afunc)(int signal))

	DESCRIPTION:  Sets the animation function.  If the funtion is the same,
								it will stop that function and no animation will be active.

**************************************************************************/
void setanimfunc(int (*afunc)(int signal))
{
	if(afunc && animfunc != afunc) {
		animfunc = afunc;
		afunc(signal_start);
	}
	else animfunc = NULL;

}

/**************************************************************************
	void setbrushfunc(int (*afunc)(int signal))

	DESCRIPTION:  Sets the brush function.  If the funtion is the same,
								it will stop that function and no animation will be active.

**************************************************************************/
void setbrushfunc(int (*afunc)(int signal))
{

	if(afunc && brushfunc != afunc) {
		brushfunc = afunc;
		brushfunc(signal_start);
	}
	else brushfunc = NULL;

}

/**************************************************************************
	void AddRoutineToList(CRoutine *newroutine)

	DESCRIPTION:

**************************************************************************/
void AddRoutineToList(CRoutine *newroutine)
{
	if(!newroutine) return;

	if(!gRoutineList) gRoutineList = newroutine;
	else newroutine->addtochain(gRoutineList);
}



/**************************************************************************
	void playmusic(int direction)

	DESCRIPTION:

**************************************************************************/
void playmusic(int direction)
{

	Log("------ Entering playmusic() ------- \n");
	gilastmusiccounter = 0;

	if(!giSoundOn || !giMusicOn) return;
	if(!giMakeNoise) return;

	Log("  playmusic() Checking pointer...\n");

	if(!gpMusicList) return;
	if(!gpMusicPointer) gpMusicPointer = gpMusicList;

																// Stop and free music first
	if(ModStatus() != v_nonexist) ModCommand(v_stop);
	if(gpMyMod) {
		Log("Freeing Module (%s)\n",gpMyMod->title);
		if(gpMusicPointer->iszot) free(gpMyMod);
		else FreeMod(gpMyMod);
		gpMyMod = NULL;
	}
	if(S3MStatus() != v_nonexist) S3MCommand(v_stop);
	if(gpMyS3M) {
		Log("Freeing S3M (%s)\n",gpMyS3M->title);
		if(gpMusicPointer->iszot) free(gpMyS3M);
		else FreeS3M(gpMyS3M);
		gpMyS3M = NULL;
	}
	if(MidiStatus() != v_nonexist) MidiCommand(v_stop);
	if(gpMyMidi) {
		Log("Freeing Midi (%s)\n",gpMyMidi->title);
		if(gpMusicPointer->iszot) free(gpMyMidi);
		else FreeMidi(gpMyMidi);
		gpMyMidi = NULL;
	}
																// Try to load a music file

	int stilltrying = 5;
	while(stilltrying) {
		stilltrying--;

		if(direction > 0) gpMusicPointer = gpMusicPointer->next;
		else gpMusicPointer = gpMusicPointer->prev;

		Log("Music pointer is %s\n",gpMusicPointer->path);

		switch(gpMusicPointer->type) {
		case v_musictype_mod:
			if(gpMusicPointer->iszot) gpMyMod = (MOD *)LoadZot((char *)(gpMusicPointer->path),(char *)errstring);
			else gpMyMod = LoadMod(gpMusicPointer->path,errstring);
			if(gpMyMod) {
				Log("Playing Module %s\n",gpMyMod->title);
				PlayMod(gpMyMod);
				giTempo = ModSetting(v_rate,GET_SETTING);
				stilltrying = 0;
				continue;
			}
			else {
				Log("playmusic(): %s [%s]\n",errstring,gpMusicPointer->path);
			}
			break;
		case v_musictype_s3m:
			if(gpMusicPointer->iszot) gpMyS3M = (S3M *)LoadZot((char *)(gpMusicPointer->path),(char *)errstring);
			else  gpMyS3M = LoadS3M(gpMusicPointer->path,errstring);
			if(gpMyS3M) {
				Log("Playing S3M %s\n",gpMyS3M->title);
				PlayS3M(gpMyS3M);
				giTempo = S3MSetting(v_rate,GET_SETTING);
				stilltrying = 0;
				continue;
			}
			else {
				Log("playmusic(): %s [%s]\n",errstring,gpMusicPointer->path);
			}
			break;
		case v_musictype_midi:
			if(gpMusicPointer->iszot) gpMyMidi = (MIDI *)LoadZot((char *)(gpMusicPointer->path),(char *)errstring);
			else gpMyMidi = LoadMidi(gpMusicPointer->path,errstring);
			if(gpMyMidi) {
				Log("Playing Midi %s\n",gpMyMidi->title);
				PlayMidi(gpMyMidi);
				giTempo = MidiSetting(v_rate,GET_SETTING);
				stilltrying = 0;
				continue;
			}
			else {
				Log("playmusic(): %s [%s]\n",errstring,gpMusicPointer->path);
			}
			break;
		}
	}


}

/*************************************************************************
	dokey(r);

	DESCRIPTION: Main keystroke handling function

	INPUTS:

		r = scancode


****************************************************************************/
void dokey(char r)
{
//	int x2,y2,x3,y3;
//	int i = 10000,k,j;
//	static int voice = 0;
//	char string[80];
//	double lx,ly,c;
	double fr;
	VARPACKET localvp;
	int i,j,k,x,y,itemp;
	signed char *sdata1,*sdata2;
	int usercolor = FALSE;


	localvp.d1 = localvp.d2 = localvp.d3 = 1;
	if(random(1000)>500) localvp.d1 = -1;
	if(random(1000)>500) localvp.d2 = -1;
	if(random(1000)>500) localvp.d3 = -1;
	localvp.dx = (random(100)-50.0)/20.0;
	localvp.dy = (random(100)-50.0)/20.0;
	localvp.x1 = random(maxx);
	localvp.y1 = random(maxy);
	localvp.x2 = random(maxx);
	localvp.y2 = random(maxy);
	localvp.w = (random(maxx/2)+20) * localvp.d2;
	localvp.h = (random(maxy/2)+20) * localvp.d3;
	localvp.r = random(maxx/6)+20;
	localvp.color = random(256);
	localvp.colorbase = (localvp.color/16)*16;

																// Lock 'n drag!
																// Lock the mouse coordinates in if the
																// key is not TAB or CAPS LOCK
	if(giUseMouseCoords && r != 0x0f && r != 0x3a) {
		giUseMouseCoords = FALSE;
		localvp.x1 = giMouseX1;
		localvp.y1 = giMouseY1;
		if(giMouseW || giMouseH) {
			localvp.x2 = giMouseX1 + giMouseW;
			localvp.y2 = giMouseY1 + giMouseH;
			localvp.w = giMouseW;
			localvp.h = giMouseH;
			localvp.r = sqrt(giMouseW*giMouseW + giMouseH*giMouseH);
		}
	}
															// Lock color   (Caps lock)
	if(GUG_key_table[SCANCODE_CAPS]) {
		localvp.color = giWorkingColor;
		localvp.colorbase = (localvp.color/16)*16;
		usercolor = TRUE;
	}

	switch(r) {
		case 0x1:                  							// KEY: Esc
			giStatusMode ^= TRUE;
			if(giStatusMode) dosound(0,50,1.0);
			break;
		case 0x2:                  // KEY: 1   Note
		case 0x3:                  // KEY: 2   Note
		case 0x4:                  // KEY: 3   Note
		case 0x5:                  // KEY: 4   Note
		case 0x6:                  // KEY: 5   Note
		case 0x7:                  // KEY: 6   Note
		case 0x8:                  // KEY: 7   Note
		case 0x9:                  // KEY: 8   Note
		case 0xA:                  // KEY: 9   Note
		case 0xB:                  // KEY: 0   Note
		case 0xC:                  // KEY: -   Note
		case 0xD:                  // KEY: =   Note
			fr = giScale[note[r-2]-32];
			if(GUG_key_table[SCANCODE_LSHIFT]) fr /= 2;
			if(GUG_key_table[SCANCODE_RSHIFT]) fr *= 2;
			if(GUG_key_table[SCANCODE_LCTRL])  fr /= CHROMATIC_RATIO;
			if(GUG_key_table[SCANCODE_RCTRL])  fr *= CHROMATIC_RATIO;
			dosound(notesound,50,fr);
			break;
		case 0xE:                  // KEY: Backspace  Stop everything
			dosound(2);
			setanimfunc(NULL);
			setbrushfunc(NULL);
			if(ModStatus() == v_started) ModCommand(v_pause);
			if(S3MStatus() == v_started) S3MCommand(v_pause);
			{
				CRoutine *cr;
				while(gRoutineList) {
					cr = gRoutineList->Next();
					delete gRoutineList;
					gRoutineList = cr;
				}
				CFireWorkDraw::iNumFireworks = 0;
				CBounceDraw::iNumBalls = 0;
			}
			giMouseReverse = FALSE;
			giMouseTile = 0;

			break;
		case 0xF:                  // KEY: TAB  lock 'n drag
			// Do nothing here because this is the lock 'n drag key
			break;
		case 0x10:                 // KEY: q  Do nothing
			dosound(4);
			break;
		case 0x11:                 // KEY: w  Checker ball
			dosound(5);
			{
				if(!usercolor) localvp.colorbase = 0;
				CCheckerBall *newball = new CCheckerBall(localvp);
				AddRoutineToList(newball);
				break;
			}
		case 0x12:                 // KEY: e  Cone
			dosound(6);
			{
				if(!usercolor) localvp.colorbase = 224;
				CConeDraw *newcone = new CConeDraw(localvp);
				AddRoutineToList(newcone);
				break;
			}
		case 0x13:                 // KEY: r  Starburst
			dosound(7);
			{
				if(!usercolor) localvp.colorbase = ANIMCOLOR9;
				CStarBurstDraw *newburst = new CStarBurstDraw(localvp);
				AddRoutineToList(newburst);
				break;
			}
		case 0x14:                 // KEY: t  Tree
			dosound(8);
			{
				if(!usercolor) localvp.colorbase = ANIMCOLOR9;
				CTreeDraw *newtree = new CTreeDraw(localvp);
				AddRoutineToList(newtree);
				break;
			}

		case 0x15:                 // KEY: y  Argyle
			dosound(9);
			{
				CBallDraw *newball = new CBallDraw(localvp);
				AddRoutineToList(newball);
				break;
			}

		case 0x16:                 // KEY: u  Checkerboard Pattern
			dosound(10);
			checkerblack(&localvp);
			break;
		case 0x17:                 // KEY: i  Spiral Bar
			dosound(11);
			{
				if(!usercolor) localvp.colorbase = ANIMCOLOR4;
				CSpiralBarDraw *newbar = new CSpiralBarDraw(localvp);
				AddRoutineToList(newbar);
				break;
			}
		case 0x18:                  // KEY: o  Circle brush shape
			dosound(12);
			giMouseCursor = cursor_circle;
			giBrushShape = brush_circle;
			GUG_Sprite_Mouse = (char *)flabbersprite[giMouseCursor];
			break;
		case 0x19:                  // KEY: p  Draw/erase pallette
			if(!giPalPut) {
				dosound(13);
				GUGBlockGet(0,maxy-11,319,maxy,grbPaletteBlock);

				for(j = 0; j < 64; j++) {
					GUGDrawFillRectangle(SET,j,j*5+1,maxy-1,j*5+5,maxy-10);
				}
				for(j = 0; j < 12; j++) {
					for(i = 0; i < 27; i++) {
						GUGDrawLine(SET,j*16+64 + i%16,j*27+i,maxy-1,j*27+i,maxy-6);
					}
				}
				GUGDrawRectangle(SET,63,0,maxy-1,maxx-1,maxy-11);
				giPalPut =1;
			}
			else {
				GUGPutBGSprite(0,maxy-11,(char *)grbPaletteBlock);
				giPalPut = 0;
			}
			break;
		case 0x1A:                  // KEY: [  Square brush shape
			dosound(12);
			giMouseCursor = cursor_square;
			giBrushShape = brush_square;
			GUG_Sprite_Mouse = (char *)flabbersprite[giMouseCursor];
			break;
		case 0x1B:                  // KEY: ]        Horizontal line
			dosound(14);
			for(y = localvp.y1 - giBrushSize/2; y < localvp.y1 + giBrushSize/2; y++) {
				GUGDrawLine(SET,localvp.color,0,y,maxx,y);
			}
			break;
		case 0x1C:                  // KEY: Enter    Vertical line
			dosound(15);
			for(x = localvp.x1 - giBrushSize/2; x < localvp.x1 + giBrushSize/2; x++) {
				GUGDrawLine(SET,localvp.color,x,0,x,maxy);
			}
			break;
		case 0x1D:									// KEY: Left Ctrl  Do nothing
			break;
		case 0x1E:                  // KEY: a  Random regular circle
			dosound(16);
			GUGDrawFillCircle(SET,localvp.color/4,localvp.x1,localvp.y1,localvp.r);
			break;
		case 0x1F:                  // KEY: s  Do nothing (save screen)
			if(GUG_key_table[SCANCODE_LCTRL] || GUG_key_table[SCANCODE_RCTRL]) {
				doscreen(0);
			}
			dosound(17);
			break;
		case 0x20:                  // KEY: d  Nested circles
			dosound(18);
			{
				if(!usercolor) localvp.colorbase = ANIMCOLOR1;
				CTargetDraw *newtarget = new CTargetDraw(localvp);
				AddRoutineToList(newtarget);
			}
			break;
		case 0x21:                  // KEY: f  XOR whole screen with random color
			dosound(19);
			GUGDrawFillRectangle(XOR,localvp.color,0,0,maxx,maxy);
			break;
		case 0x22:                  // KEY: g  Coins
			dosound(20);
			{
				if(!usercolor) localvp.colorbase = ANIMCOLOR2;
				CCoinDraw *newcoin = new CCoinDraw(localvp);
				AddRoutineToList(newcoin);
			}
			break;
		case 0x23:                  // KEY: h  Random XOR'ed rectangle
			dosound(21);
			GUGDrawFillRectangle(XOR,localvp.color,localvp.x1,localvp.y1,localvp.x1+localvp.w,localvp.y1+localvp.w);
			break;
		case 0x24:                  // KEY: j  Flabbergasted!
			dosound(22);
			GUGPutFGSprite(localvp.x1 - flabbersprite[0]->width/2,
										 localvp.y1 - flabbersprite[0]->height/2,
										 (char *)flabbersprite[0]);
			break;
		case 0x25:                  // KEY: k  Palette box
			dosound(23);
																// Make sure palette box ends up on screen
			localvp.x1 = localvp.x1 * (float)(maxx-32*3)/maxx;
			localvp.y1 = localvp.y1 * (float)(maxy-8*3)/maxy;

			palbox(localvp.x1,localvp.y1);
			break;

		case 0x26:                  // KEY: l  Do nothing (load screen)
			if(GUG_key_table[SCANCODE_LCTRL] || GUG_key_table[SCANCODE_RCTRL]) {
				doscreen(1);
			}
			dosound(44,80,.3);
			break;
		case 0x27:                  // KEY: ;  Turn on/off mouse tiling
			dosound(25);
			if(giMouseTile) giMouseTile = 0;
			else giMouseTile = giBrushSize + 32;
			break;
		case 0x28:                  // KEY: '  Spray brush shape
			dosound(12);
			giMouseCursor = cursor_spray;
			giBrushShape = brush_spray;
			GUG_Sprite_Mouse = (char *)flabbersprite[giMouseCursor];
			break;
		case 0x29:                  // KEY: `  Change note sound to last sound
			notesound = giLastSound;
			dosound(notesound);
			break;
		case 0x2A:                  // KEY: Left Shift  Do nothing
			break;
		case 0x2B:                  // KEY: \  Slant brush shape
			dosound(12);
			giMouseCursor = cursor_slant;
			giBrushShape = brush_slant;
			GUG_Sprite_Mouse = (char *)flabbersprite[giMouseCursor];
			break;
		case 0x2C:                  // KEY: z  Circle
			dosound(26);
			GUGDrawCircle(SET,localvp.color,localvp.x1,localvp.y1,localvp.r);
			break;
		case 0x2D:                  // KEY: x  Square
			dosound(27);
			GUGDrawRectangle(SET,localvp.color,localvp.x1,localvp.y1,localvp.x1+localvp.w,localvp.y1+localvp.w);
			break;
		case 0x2E:                  // KEY: c  Nested boxes
			dosound(28);
			{
				if(!usercolor) localvp.colorbase = ANIMCOLOR0;
				CBoxesDraw *newboxes = new CBoxesDraw(localvp);
				AddRoutineToList(newboxes);
			}
			break;
		case 0x2F:                	// KEY: v   Flood Fill
			dosound(29);
			giFloodFill ^= TRUE;
			break;
		case 0x30:                  // KEY: b  Random XOR'd circle
			dosound(30);
			GUGDrawFillCircle(XOR,localvp.color,localvp.x1,localvp.y1,localvp.r);
			break;
		case 0x31:                  // KEY: n Play test Wave
			dosound(1);
			break;
		case 0x32:                  // KEY: m Reverse mouse coordinates
			dosound(24);
			if(!giNiceMouse) giMouseReverse ^= TRUE;
			break;
		case 0x33:                  // KEY: ,  Smaller brush
			dosound(31,50,0.5 + giBrushSize/50.0);
			giBrushSize --;
			if(giBrushSize <1) giBrushSize = 1;
			GUGDrawCircle(XOR,63,gfprealmousex,gfprealmousey,giBrushSize);
			GUGCopyRectToRect(gfprealmousex-giBrushSize,
												gfprealmousey-giBrushSize,
												gfprealmousex+giBrushSize+1,
												gfprealmousey+giBrushSize);
			GUGDrawCircle(XOR,63,gfprealmousex,gfprealmousey,giBrushSize);
			break;
		case 0x34:                  // KEY: .  Larger brush
			dosound(31,50,0.5 + giBrushSize/50.0);
			giBrushSize++;
			if(giBrushSize > 50) giBrushSize = 50;
			GUGDrawCircle(XOR,63,gfprealmousex,gfprealmousey,giBrushSize);
			GUGCopyRectToRect(gfprealmousex-giBrushSize,
												gfprealmousey-giBrushSize,
												gfprealmousex+giBrushSize+1,
												gfprealmousey+giBrushSize);
			GUGDrawCircle(XOR,63,gfprealmousex,gfprealmousey,giBrushSize);
			break;
		case 0x35:                  // KEY: /  slash brush shape
			dosound(12);
			giMouseCursor = cursor_slash;
			giBrushShape = brush_slash;
			GUG_Sprite_Mouse = (char *)flabbersprite[giMouseCursor];
			break;
		case 0x36:                  // KEY: Right Shift Do nothing
			break;
		case 0x37:                  // KEY: Keypad *  Fireworks
			{
				if(CFireWorkDraw::iNumFireworks < 11) {
					dosound(32,50,0.65 + (double)random(50)/1000.0);
					CFireWorkDraw *newfirework = new CFireWorkDraw(localvp);
					AddRoutineToList(newfirework);
				}
			}
			break;

		case 0x38:                  // KEY: Left Alt  Do Nothing
			break;
		case 0x39:                  // KEY: Spacebar
			dosound(34);
			GUGDrawPoint(SET,random(256),localvp.x1,localvp.y1);
			break;
		case 0x3A:                  // KEY: Caps lock Do nothing (lock color)
			break;
		case 0x3B:                  // KEY: F1  Clear to black
			dosound(36);
			GUGDrawFillRectangle(SET,0,0,0,maxx,maxy);
			break;
		case 0x3C:                  // KEY: F2  Clear to random
			dosound(37);
			GUGDrawFillRectangle(SET,random(64),0,0,maxx,maxy);
			break;
		case 0x3D:                  // KEY: F3  scorched Earth Slump
			dobackgroundsound(38);
			setanimfunc(animation2);
			break;
		case 0x3E:                  // KEY: F4  Convert screen to B&W
			dosound(39);
			bnwrect(0,0,maxx-1,maxy-1);
			break;
		case 0x3F:                  // KEY: F5  Game of life scren animation
			dobackgroundsound(25,20,1.8);
			setanimfunc(animation1);
			break;
		case 0x40:                  // KEY: F6  Plasma!
			doplasma(0,0,319,199,random(16)*16);
			dosound(40);
			break;
		case 0x41:                  // KEY: F7  Slide screen
			dobackgroundsound(41,15);
			setanimfunc(animation3);
			break;

		case 0x42:                  // KEY: F8 Snow!
			dosound(42);
			setbrushfunc(animation4);
			break;
		case 0x43:                  // KEY: F9 Alternate Lines
			dobackgroundsound(43,20);
			setanimfunc(animation5);
			break;
		case 0x44:                  // KEY: F10 Diffusion
			dobackgroundsound(44,20);
			setanimfunc(animation6);
			break;
		case 0x45:                  // KEY: Num Lock  Toggle White/black palette
			dosound(45);
			giWhitePalette ^= 1;
			setuppalette();
			break;
		case 0x46:                  // KEY: Scroll lock  Memory Check
			dosound(46);
			checkmemory();
			break;

		case 0x47:                              // KEY: KeyPad 7
			dosound(47);
			break;
		case 0x48:                              // KEY: KeyPad 8
			dosound(48);
			break;
		case 0x49:                              // KEY: KeyPad 9
			dosound(49);
			break;
		case 0x4A:                  // KEY: KeyPad -  giTempo slower
			dosound(50);
			if(GUG_key_table[SCANCODE_LCTRL] ||
				 GUG_key_table[SCANCODE_RCTRL]) giTempo = 2000;
			if(gpMyMod) {
				giTempo *= 1.2;
				ModSetting(v_rate,giTempo);
			}
			else if(gpMyS3M) {
				giTempo *= 1.2;
				S3MSetting(v_rate,giTempo);
			}
			else if(gpMyMidi) {
				giTempo *= 1.2;
				MidiSetting(v_rate,giTempo);
			}
			break;

		case 0x4B:                  // KEY: KeyPad 4 FFT Brush
			dosound(51);
			setbrushfunc(autobrush1);
			break;
		case 0x4C:                  // KEY: KeyPad 5 Polar Waveform Brush
			dosound(52);
			setbrushfunc(autobrush2);
			break;
		case 0x4D:                 // KEY: KeyPad 6  Reverse sounds
			for(i = 0; i < MAXSOUNDS; i++) {
				k = flabbersound[i]->sample_size/2;
				sdata1 = flabbersound[i]->data;
				sdata2 = flabbersound[i]->data + flabbersound[i]->sample_size;
				for(j = 0; j < k; j++) {
					itemp = *sdata1;
					*sdata1 = *sdata2;
					*sdata2 = itemp;
					sdata1++;
					sdata2--;
				}
			}
			dosound(22);
			break;
		case 0x4E:                  // KEY: KeyPad +  giTempo faster
			dosound(50);
			if(GUG_key_table[SCANCODE_LCTRL] ||
				 GUG_key_table[SCANCODE_RCTRL]) giTempo = 4;
			if(gpMyMod) {
				giTempo *= .833333;
				ModSetting(v_rate,giTempo);
			}
			else if(gpMyS3M) {
				giTempo *= .833333;
				S3MSetting(v_rate,giTempo);
			}
			else if(gpMyMidi) {
				giTempo *= .833333;
				MidiSetting(v_rate,giTempo);
			}
			break;

		case 0x4F:                  // KEY: KeyPad 1  Crazy screen effect
			dobackgroundsound(53,20);
			setanimfunc(animation9);
			break;
		case 0x50:                  // KEY: KeyPad 2  Hyper-Vortex Screen Effect
			dobackgroundsound(54,20);
			setanimfunc(animation10);
			break;
		case 0x51:                  // KEY: KeyPad 3  Vortex Screen Effect
			dobackgroundsound(55,20);
			setanimfunc(animation11);
			break;
		case 0x52:                  // KEY: KeyPad Insert  Moire brush
			dosound(56);
			setbrushfunc(autobrush3);
			break;

		case 0x53:                  // KEY: KeyPad Delete  Randomize Sounds
			if(!giSoundsRandomized) {
				WAVE *wtemp;
				int tw;

				dosound(63);
				for(i = 0; i < MAXSOUNDS; i++) {
					tw = random(MAXSOUNDS);
					wtemp = flabbersound[i];
					flabbersound[i] = flabbersound[tw];
					flabbersound[tw] = wtemp;
				}
				giSoundsRandomized = TRUE;
			}
			else {
				loadsounds();
				giSoundsRandomized = FALSE;
			}
			break;

		case 0x57:                  // KEY: F11 Blur
			if(!gpMyMod && !gpMyS3M && !gpMyMidi) dobackgroundsound(57,20);
			setanimfunc(animation7);
			break;

		case 0x58:                  // KEY: F12 FFT animation
			setanimfunc(animation8);
			if(animfunc) dosound(58);
			break;
		case 0x60:                  // KEY: Right alt  Do nothing
			break;
		case 0x61:                  // KEY: Right Ctrl Do nothing
			break;
		case 0x62:                  // KEY: Arrow Up  Draw a spiral
			dosound(59);
			{
				CSpiralDraw *newspiral = new CSpiralDraw(localvp);
				AddRoutineToList(newspiral);
			}
			break;
		case 0x63:                  // KEY: Arrow left  Bouncing Ball
			dosound(60);
			{
				if(CBounceDraw::iNumBalls < 11) {
					CBounceDraw *newbouncer = new CBounceDraw(localvp);
					AddRoutineToList(newbouncer);
				}
			}
			break;

		case 0x64:                  // KEY: Arrow Right  Colors up 1
			dosound(61);
			colorup();
			break;
		case 0x65:                  // KEY: Arrow Down   Colors down 1
			dosound(62);
			colordown();
			break;
		case 0x66:                  // KEY: Insert Start music/next music file
			playmusic(1);
			break;
		case 0x67:                  // KEY: Home  Toggle Music
			if(gpMyMod) {
				if(ModStatus() == v_started) ModCommand(v_pause);
				else if(ModStatus() == v_paused) ModCommand(v_play);
			}
			else if(gpMyS3M) {
				if(S3MStatus() == v_started) S3MCommand(v_pause);
				else if(S3MStatus() == v_paused) S3MCommand(v_play);
			}
			else if(gpMyMidi) {
				if(MidiStatus() == v_started) MidiCommand(v_pause);
				else if(MidiStatus() == v_paused) MidiCommand(v_play);
			}
			break;
		case 0x68:                  // KEY: Page Up  Draw Line  (+ Stress Mode)
			if((GUG_key_table[SCANCODE_LCTRL] || GUG_key_table[SCANCODE_RCTRL]) &&
				 (GUG_key_table[SCANCODE_LALT]  || GUG_key_table[SCANCODE_RALT])) {
				 if(giStressMode) giStressMode = stressmode_off;
				 else {
					giStressMode = stressmode_sporatic;
					dosound(70);
				 }

				 giStressRepeat = 0;
			}
			else {
				GUGDrawLine(SET,localvp.color,localvp.x1,localvp.y1,localvp.x2,localvp.y2);
				dosound(64);
			}
			break;
		case 0x69:                  // KEY: Delete  Prev song
			playmusic(-1);
			break;
		case 0x6A:                							// KEY: End
			dosound(66);
			break;
		case 0x6B:                  // KEY: Page Down Starburst (Stressmode)
			if((GUG_key_table[SCANCODE_LCTRL] || GUG_key_table[SCANCODE_RCTRL]) &&
				 (GUG_key_table[SCANCODE_LALT]  || GUG_key_table[SCANCODE_RALT])) {
				 if(giStressMode) giStressMode = stressmode_off;
				 else {
					giStressMode = stressmode_deliberate;
					dosound(70);
				 }
				 giStressRepeat = 0;
			}
			else {
				for(i = 0; i < 10; i++)
					GUGDrawLine(SET,localvp.color,localvp.x1,localvp.y1,random(320),random(200));
				dosound(65);
			}
			break;
		case 0x6C:                              // KEY: Print Screen
			dosound(67);
			break;
		case 0x6D:                  // KEY: Keypad /  Toggle sound
			giMakeNoise ^=1;

			if(!giMakeNoise) {
				if(gpMyMod && ModStatus() == v_started) {
					ModCommand(v_pause);
					giMusicWasOn = TRUE;
				}
				else if(gpMyS3M && S3MStatus() == v_started) {
					S3MCommand(v_pause);
					giMusicWasOn = TRUE;
				}
				else if(gpMyMidi && MidiStatus() == v_started) {
					MidiCommand(v_pause);
					giMusicWasOn = TRUE;
				}
				else giMusicWasOn = FALSE;

				if(giBackgroundSound) WaveCommand(giBackgroundSound,v_pause);
			}
			else {
				if(gpMyMod && giMusicWasOn) ModCommand(v_play);
				else if(gpMyS3M && giMusicWasOn) S3MCommand(v_play);
				else if(gpMyMidi && giMusicWasOn) MidiCommand(v_play);

				dosound(random(MAXSOUNDS));
				if(giBackgroundSound) WaveCommand(giBackgroundSound,v_resume);
			}
			break;

		case 0x6E:                  // KEY: Keypad enter    Text Typing
			giTextType = TRUE;
			typer(1);
			break;
		default:
			GUGDrawFillCircle(SET,random(64),localvp.x1,localvp.y1,localvp.r);
			break;


	}

}



/**************************************************************************
	void checkerblack(void)

	DESCRIPTION:  Draw a Checkerboard Pattern wherever the screen is black

**************************************************************************/
void checkerblack(VARPACKET *vp)
{
	int x,y;
	char c1,c2;
	char *vgaspot;

	c1 = random(64);
	c2 = vp->color;
	for(y = 0; y < maxy; y++) {
		vgaspot = VGA_START + y * 640;
		for(x = 0; x < maxx; x++,vgaspot++) {
															// only modify black pixels
			if(!(*vgaspot)) {
				if((y/giBrushSize)%2){
					if((x/giBrushSize)%2) *vgaspot=c1;
					else *vgaspot = c2;
				}
				else {
					if((x/giBrushSize)%2) *vgaspot=c2;
					else *vgaspot = c1;
				}
			}
		}
	}

}
