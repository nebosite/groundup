// Utilities for Flabbergasted
// Eric Jorgensen (1997)

#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include "util.h"
#include "math.h"
#include "flabber.h"
#include "\watcom\gug\lib1\gug.h"
#include "\watcom\vat\vat.h"

#include ".\fonts\small.h"
#include ".\fonts\8x11snsf.h"
#include ".\fonts\computer.h"
#include ".\fonts\digital.h"
#include ".\fonts\dragon.h"
#include ".\fonts\outline.h"
#include ".\fonts\roman2.h"
#include ".\fonts\simpagar.h"

#define PI 3.141592654

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif



double fpFastSin[360];
double fpFastCos[360];
int arccosarray[16384];

int giPrintTransparent = TRUE;
int giItalicsOn = FALSE;
int giBoldOn = FALSE;
int giUnderlineOn = FALSE;
int giShadowOn = FALSE;
char *gpFont = NULL;
char *gpFontData[20];
int giPrintX = 0;
int giPrintY = 0;
int giTabStop = 40;
int quickroot[70000];


/**************************************************************************
	void *getstaticmemorypointer(int size)

	DESCRIPTION:

**************************************************************************/
void *flabmalloc(int size)
{
#ifdef DEMOVERSION
	extern BYTE memoryhunkachunk[];
	static memoryleft = DEMOMEMORYSIZE;
	static BYTE *mpointer = memoryhunkachunk,*spot;

	if(size > memoryleft) return NULL;
	else {
		memoryleft -= size;
		spot = mpointer;
		mpointer += size;
		return (void *)spot;
	}
#endif

	return malloc(size);
}

/**************************************************************************
	int QuickSqrt(int seed)

	DESCRIPTION:

**************************************************************************/
int QuickSqrt(int seed)
{
	if(seed > 0x1000) seed = 0x1000;
	return quickroot[seed];

}

/**************************************************************************
	void verbosef(CHAR *string,...)

	DESCRIPTION:

**************************************************************************/
void verbosef(char *string,...)
{
	va_list ap;
	char outstr[4096];


	va_start(ap, string);                  // sort out variable argument list
	if(giVerbose) vsprintf(outstr,string,ap);
	va_end(ap);                            // clean up

	if(giVerbose) printf(outstr);
}


/**************************************************************************
	VATMUSICTYPE ZotType(char *filename)

	DESCRIPTION:

**************************************************************************/
VATMUSICTYPE ZotType(char *filename)
{
	FILE *input;
	VATMUSICTYPE mtype;
	char string[256];

	input = fopen(filename,"rb");
	if(!input) return v_musictype_error;


	if(fread(string,1,40,input) < 40) {
		fclose(input);
		return v_musictype_error;
	}
	if(!strstr(string,"Zorg's Omnifarious Tunage")) {
		fclose(input);
		return v_musictype_unknown;
	}

	if(fread(string,1,3,input) < 3) {
		fclose(input);
		return v_musictype_error;
	}
	string[3] = 0;
	if(!strcmp(string,"mod")) mtype = v_musictype_mod;
	else if(!strcmp(string,"s3m")) mtype = v_musictype_s3m;
	else if(!strcmp(string,"mid")) mtype = v_musictype_midi;
	else mtype =  v_musictype_unknown;

	fclose(input);

	return mtype;

}

/**************************************************************************
	void LoadZotMod(char *filename)

	DESCRIPTION:

**************************************************************************/
void *LoadZot(char *filename, char *errstring)
{
	char string[1000];
	int i,j,ptotal,totalmem,usedmem;
	FILE *input;
	BYTE *mempointer;
	int readmem = 0;
	VATMUSICTYPE mtype= v_musictype_unknown;
	void *mobj,*memoryblock;
	int patternsize;



	input = fopen(filename,"rb");
	if(!input) {
		sprintf(errstring,"Error opening zot file: %s\n",filename);
		return NULL;
	}


	if(fread(string,1,40,input) < 40) {
		fclose(input);
		sprintf(errstring,"File Read error!\n");
		return NULL;
	}
	if(!strstr(string,"Zorg's Omnifarious Tunage")) {
		fclose(input);
		sprintf(errstring,"Not a ZOT file!\n");
		return NULL;
	}

	if(fread(string,1,3,input) < 3) {
		fclose(input);
		sprintf(errstring,"File Read error!\n");
		return NULL;
	}
	string[3] = 0;
	if(!strcmp(string,"mod")) mtype = v_musictype_mod;
	else if(!strcmp(string,"s3m")) mtype = v_musictype_s3m;
	else if(!strcmp(string,"mid")) mtype = v_musictype_midi;
	else {
		fclose(input);
		sprintf(errstring,"Unknown music type!\n");
		return NULL;
	}




	if(fread(&usedmem,1,sizeof(int),input) < sizeof(int)) {
		fclose(input);
		sprintf(errstring,"File Read error!\n");
		return NULL;
	}

	memoryblock = malloc(usedmem);
	if(!memoryblock) {
		fclose(input);
		sprintf(errstring,"Out of memory!\n");
		return NULL;
	}

	mempointer = (BYTE *)memoryblock;
	while(readmem < usedmem) {
		printf(".");
		if(fread(mempointer+readmem,1,50000,input) < 50000) break;
		readmem += 50000;
	}
	fclose(input);


	mobj = memoryblock;
	mempointer = (BYTE *)memoryblock;
	if(mtype == v_musictype_mod) {
		mempointer += sizeof(MOD);
		for(i = 0; i < 32; i++) {
			if(((MOD *)mobj)->slength[i]) {
				((MOD *)mobj)->sdata[i] = (SAMPLE *)mempointer;
				mempointer += ((MOD *)mobj)->slength[i];
			}
		}
		for(i = 0; i < 128; i++) {
			if(((MOD *)mobj)->pattern_data[i]) {
				((MOD *)mobj)->pattern_data[i] = mempointer;
				mempointer += 1024;
			}
		}
	}

	else if(mtype == v_musictype_s3m) {
		mempointer += sizeof(S3M);
		for(i = 0; i < 100; i++) {
			if(((S3M *)mobj)->slength[i]) {
				((S3M *)mobj)->sdata[i] = (SAMPLE *)mempointer;
				mempointer += ((S3M *)mobj)->slength[i];
			}
		}
		patternsize = ((S3M *)mobj)->channelnum * 5 * 64;
		for(i = 0; i < 256; i++) {
			if(((S3M *)mobj)->pattern_data[i]) {
				((S3M *)mobj)->pattern_data[i] = mempointer;
				mempointer += patternsize;
			}
		}
	}

	else if(mtype == v_musictype_midi) {
		mempointer += sizeof(MIDI);
		for(i = 0; i < MAXMIDITRACKS; i++) {
			if(((MIDI *)mobj)->track[i]) {
				((MIDI *)mobj)->track[i]  = mempointer;
				mempointer +=  ((MIDI *)mobj)->tracksize[i];
			}
		}
	}
	return mobj;

}

/**************************************************************************
	void doscreen(int action)

	DESCRIPTION: Saves the screen to one of nine slots

	ARGUMENTS:
		action	0 = Save screen, 1 = load screen


			GUGBlockGet(0,0,maxx-1,maxy-1,grbWorkSpace);
			drawwatermark();
			GUGGetPalette((char *)palette);
			GUGWritePCX("mypic.pcx",0,0,maxx-1,maxy-1,(unsigned char *)palette);

			giPrintTransparent = FALSE;
			print(SET,63,0,10,10,"This screen has been saved as MYPIC.PCX.\nPress any key...");
			GUGCopyToDisplay();
			dosound(17);
			while(!GUGScanKeyHit());
			GUGGetScanCode();
			GUGPutBGSprite(0,0,(char *)grbWorkSpace);
			memset(typed,' ',31);    // Clear special signal array

**************************************************************************/
void doscreen(int action)
{
	char pcxdata[65000];
	char pcxname[256];
	char pal[1000];
	int x,y,lx,ly;
	unsigned int mx,my,mb;
	int i,j,t=0;
	int slotpicked = -1;
	int tick_wait,pcount  = 0;
	int mousedown = FALSE;
															 // Preserve the screen
	GUGBlockGet(0,0,maxx-1,maxy-1,grbWorkSpace);

															 // Prepare random stuff
	giPrintTransparent = FALSE;
	tick_wait = CLK_TCK/20;
	if(!tick_wait)tick_wait = 1;


															 // Load and display all 12 slots
	for(i = 0; i < 12; i++) {
		sprintf(pcxname,"screen%d.pcx",i+1);
		lx = (i%4)*80;
		ly = (i/4)*50+50;

		if(GUGLoadPCX(pcxname,pcxdata,pal)) {
			for(x = 0; x < 80 ; x++) {
				for(y = 0; y < 50; y++) {
					GUGDrawPoint(SET,pcxdata[(x<<2) + (y<<2)*320],x+lx,y+ly);
				}
			}
			GUGDrawRectangle(SET,63,x+lx,y+ly,x+lx+79,y+ly+49);
		}
		else {
			GUGDrawFillRectangle(SET,0,lx,ly,lx+79,ly+49);
			GUGDrawLine(SET,63,lx,ly,lx+79,ly+49);
			GUGDrawLine(SET,63,lx+79,ly,lx,ly+49);
			print(SET,63,0,lx+7,ly+20,">> EMPTY <<");
		}

		GUGDrawRectangle(SET,63,lx,ly,lx+79,ly+49);
		print(SET,63,0,lx+5,ly+5,"#%d",i+1);

	}

	if(action) print(SET,63,0,5,5,"Please pick a picture to load.");
	else print(SET,63,0,5,5,"Please pick a place to store your picture.");
	print(SET,7,0,7,20,"OOPS!");
	GUGDrawRectangle(SET,63,5,19,37,31);


																// Main loop
	while(slotpicked == -1) {
		if(clock()>= t) {
			t = clock()+tick_wait;

			GUGMousePosition(&mb,&mx,&my);   // pick up mouse info

																// Draw crosshairs if button is pushed
			GUG_Sprite_Mouse = (char *)flabbersprite[cursor_x];

			GUGSMDraw(mx-8,my-8);

			// ---------------------------------------------------
			GUGVSync();
			dopalette(pcount++);
			GUGCopyToDisplay();
			// ---------------------------------------------------

			GUGSMUnDraw();
		}

		if(mb) mousedown = TRUE;
		if(!mb && mousedown) {
			if(mx > 5 && mx < 37 && my > 19 && my < 31) slotpicked = 0;
			else if(my > 50) {
				slotpicked = mx/80 + ((my/50)-1)*4 + 1;
			}
		}
	}

	if(!slotpicked) {
		GUGPutBGSprite(0,0,(char *)grbWorkSpace);
		return;
	}
															 // handle the picture
	if(action) print(SET,63,0,5,5,"          Loading the picture...           ");
	else print(SET,63,0,5,5,"          Saving the picture...           ");
	i = slotpicked-1;
	sprintf(pcxname,"screen%d.pcx",i+1);
	lx = (i%4)*80;
	ly = (i/4)*50+50;


	if(action) {                // Load the pcx
		if(GUGLoadPCX(pcxname,pcxdata,pal)) {
			for(y = 0; y < maxy ; y++) {
				GUGDrawLine(XOR,63,0,y+1,maxx,y+1);
				for(x = 0; x < maxx; x++) {
					GUGDrawPoint(SET,pcxdata[x + y*320],x,y);
				}
				GUGCopyToDisplay();
				dosound(34,32,2.5 - y/80.0);
				MilliDelay(10);
			}
		}

	}
	else  {	  
		for(j = 0; j < giSaveScreen * 3 + 1; j++) {
			i = slotpicked-1;
			sprintf(pcxname,"screen%d.pcx",i+1);
			lx = (i%4)*80;
			ly = (i/4)*50+50;

			for(x = 0; x < 80 ; x++) {
				GUGDrawLine(XOR,63,x+lx+1,ly,x+lx+1,ly+49);
				for(y = 0; y < 50; y++) {
					GUGDrawPoint(SET,grbWorkSpace->data[(x<<2) + (y<<2)*320],x+lx,y+ly);
				}
				GUGCopyToDisplay();
				dosound(34,32,.8 + x/160.0);
				MilliDelay(15);
			}
			GUGPutBGSprite(0,0,(char *)grbWorkSpace);
			drawwatermark();
			GUGGetPalette((char *)palette);
			GUGWritePCX(pcxname,0,0,maxx-1,maxy-1,(unsigned char *)palette);
			erasewatermark();

			slotpicked++;
			pcount += 4;
			dopalette(pcount);
			if(slotpicked > 12) slotpicked = 0;
		}
	}


}


/**************************************************************************
	getinput(x,y,fc,bc,prompt,string,maxlength);

	DESCRIPTION: This gets string input from the user. This function
							 fills the variable 'string' with text information.
							 If string already has text information in it, getinput()
							 will use it.

	fc,bc = 		foregroundcolor, backgroundcolor
  *prompt = Text to prompt the user
  *string = Output buffer.  Should already containa default value
  maxlength = maxiumum length of input

**************************************************************************/
/*void getinput(int x,int y,int fc,int bc,
			char *prompt,char *string,int maxlength)
{
	int w,h,wx,wy,c,flag,dd=0,color;
	char buffer[255],r,minibuff[2];
	int printstate;

	printstate = giPrintTransparent;
	giPrintTransparent = FALSE;

	mousehide();                       		// Get rid of mouse cursor
	minibuff[1] = 0;                      // clear small string buffer

	w = textwidth("A");
	h = textheight("A");
	wx = x+textwidth(prompt);          		// get location if leftmost input char
	wy = y;

	sprintf(buffer,"%s%s",prompt,string);
	drwstring(SET,fc,bc,buffer,x,y);        // display prompt and default string

	strcpy(buffer,string);     							// copy string for editing

	c = strlen(buffer);
	flag = 1;

	while(flag) {                          	// ANIMATED STRING EDITOR LOOP
		if(dd > 100) color = fc;       	 		 	// Blink cursor
		else color = bc;                      // draw cursor
		drwfillbox(SET,color,wx+c*w, wy, wx+c*w+w, wy+h);

		delay(10);                        		// control blink rate
		dd += 5;
		if(dd > 199) dd = 0;

		r = inkey();
		if(r) {                      					// look for a key stroke
			if( r >= ' ') {           					// If r is a regular alpha-numeric
																					// character, add it to the name
																					// string.
				buffer[c] = r;
																					// move the cursor
				drwfillbox(SET,bc,wx+c*w,wy,wx+c*w+w,wy+h);   // erase it
				drwfillbox(SET,bc,wx,wy,wx+maxlength*w+w,wy+h); 		 // erase string
				buffer[c+1] = 0;              		// extend string terminator
				drwstring(SET,fc,bc,buffer,wx,wy);  		// draw the new string
				c++;                      				// move cursor index
				if(c>maxlength) c = maxlength;// limit string length
			}
			else if(r == 13) flag = 0;    			// return = finished
			else if( r == 8) {             			// backspace
				drwfillbox(SET,bc,wx+c*w,wy,wx+c*w+w,	wy+h);  // erase cursor
				c--;                      				// move string index
				if(c < 0) c = 0;          				// don't go off te end!
				buffer[c] = 0;            				// move back string terminator
				drwfillbox(SET,bc,wx+w,wy,wx+maxlength*w+w,wy+h);  // erase string
				drwstring(SET,fc,bc,buffer,wx,wy); 		// draw the new string
			}
			else if(r == 27)	{									// escape key
				flag = 0;                         // end loop
				buffer[0] = 0;                    // clear input string
			}
		}
	}
	strcpy(string,buffer);                  // store new string
	*(string+maxlength) = 0;                // make sure string is of this length

	giPrintTransparent = printstate;     // Restore print state

}  */

/***************************************************************************
	print(pmode,color,x,y,*s,...)

	DESCRIPTION: This draws a string without changing the background color.

  INPUTS:
  	pmode			Drawing mode
    color			Drawing color
    x,y				Upper left of text
    *s				Format string
		...				Optional arguments (Just like printf)

								NOTE:  normally, I make sure that any function that I
								write that changes graphics includes a mousehide()
								and mouseshow(), but I am making a special exception
								for this since I want print() to go faster.  Plus
								printf() is much more like a primitive anyway.

****************************************************************************/
void print(PIXELMODE pmode, int fgcolor,int bgcolor, int x, int y, char *s, ...)
{
	int i,w,h,xx = x, yy = y;
	va_list ap;
	static char string[5000];

  va_start(ap, s);                  		// sort out variable argument list
	vsprintf(string,s,ap);      					// dump output to a string

																				// We need a font and a string.
	if(!gpFont || !string) {
		va_end(ap);                         // clean up
		return;
	}

	w= fontwidth();
	h=fontheight();

	giPrintX = x;
	giPrintY = y;

	for(i=0; i < strlen(string); i++) {   // loop through the string
																				// Handle Tabs
		if(string[i] == '\t')
			giPrintX = ((giPrintX + giTabStop)/giTabStop)*giTabStop;
		else if (string[i] == '\n') {       // return?  newline
			giPrintX = x;
			giPrintY += h;
		}
		else drwchar(pmode,fgcolor,bgcolor,giPrintX,giPrintY,string[i]);  // default- draw the char
	}
	va_end(ap);                            // clean up

}

/***************************************************************************
	drwchar(pmode,color,x,y,c)

	DESCRIPTION: Draws a character.

****************************************************************************/
void drwchar(PIXELMODE pmode, int fgcolor, int bgcolor, int x, int y, char c)
{
	int w,h,bx,by;
	char *b,bb;
	char *outspot;

																				// get font size
	w = fontwidth();
	h = fontheight();

	b = gpFont + c*16 + 2;      // get character data location

	outspot = VGA_START + x + y*640;

	for(by = 0; by <= h; by++) {                // loop through scan lines
		bb = *b;                            // grab the byte for this line
		for(bx = 0; bx < w; bx++) {         // loop through pixels
																				// put the pixel
			if(bb & 0x80)
				switch(pmode) {
				case SET: *outspot =  fgcolor; break;
				case XOR: *outspot ^= fgcolor; break;
				case AND: *outspot &= fgcolor; break;
				case OR:  *outspot |= fgcolor; break;
				}
			else if(!giPrintTransparent)
				switch(pmode) {
				case SET: *outspot =  bgcolor; break;
				case XOR: *outspot ^= bgcolor; break;
				case AND: *outspot &= bgcolor; break;
				case OR:  *outspot |= bgcolor; break;
				}
			outspot++;
			bb = bb << 1;                     // move to next pixel
		}
		outspot += 640 - fontwidth();
		b++;                                // move to next line
	}
	giPrintX = x+w;
	giPrintY = y;
}

/*************************************************************************
	inkey();

	DESCRIPTION: Works like the BASIC function inkey$. It returns the top
							 character in the keyboard buffer, and NULL if the buffer
							 is empty.

**************************************************************************/
/*char inkey(void)
{
	if(kbhit()) {
		return(getch());
	}
	else return 0;
}*/
/***************************************************************************
	textheight(string);

	DESCRIPTION: returns the height of a string in pixels.  Right now it
								returns a constant because SVGACC has limited font
								capabilities.

****************************************************************************/
/*int textheight(char *string)
{
	int width,height,i,t;

	fontgetinfo(&width,&height);
	t = 1;
	for(i = 0 ; i < strlen(string); i++) {     // count number of linefeeds
		if(*(string+i) == '\n') {
			t++;
		}
	}
	return(height*t);                          // return total eight
} */
/***************************************************************************
	textwidth(string);

	DESCRIPTION: returns the width of a string in pixels.  Right now it
								returns a quasi-constant because SVGACC has limited font
								capabilities.

****************************************************************************/
/*int textwidth(char *string)
{
	int width,height;

	fontgetinfo(&width,&height);
	return(width*strlen(string));
}*/

/**************************************************************************
	void initutils(void)

	DESCRIPTION:

**************************************************************************/
void initutils(void)
{
	int i,lowr,highr,j;
	double f;
														 // set up trig funcs
	for(i = 0; i < 360; i++) {
		fpFastCos[i] = cos((i/180.0) * PI);
		fpFastSin[i] = sin((i/180.0) * PI);
	}

	for(i = 0; i < 16384; i++) {
		f = (i-8192.0)/8192.0;
		arccosarray[i] = acos(f)/PI * 180.0;
	}
														 // Assign fonts
	for(i = 0; i < 20; i++) gpFontData[i] = NULL;

	gpFont = gpFontData[0] = font_small;
	gpFontData[1] = font_8x11snsf;
	gpFontData[2] = font_computer;
	gpFontData[3] = font_digital;
	gpFontData[4] = font_dragon;
	gpFontData[5] = font_outline;
	gpFontData[6] = font_roman2;
	gpFontData[7] = font_simpagar;


	for(i = 0; i < 256; i++) {
		lowr = i*i;
		highr = (i+1)*(i+1);
		for(j = lowr; j < highr; j++) quickroot[j] = i;
	}

}


/**************************************************************************
	int getarccos(int value)

	DESCRIPTION:  Fast arc cosine function

**************************************************************************/
int getarccos(int value)
{
	value += 8192;
	if(value < 0 || value > 16383) return 0;
	return arccosarray[value];
}

/**************************************************************************
	long memleft(void)

	DESCRIPTION: Function to check how much core is left.

	RETURNS:
		# bytes available on the heap

**************************************************************************/
long memleft(void)
{
	long numfilled = 0;
	long fillsize = 1048567L;
	long filltotal = 0;
	char *chunk[1024];

															// Start allocating memory on the heap
															// until there is no more.
	while(fillsize) {

		chunk[numfilled] = (char *)malloc(fillsize);
															// Can't allocate? chop the fill size
		if(!chunk[numfilled]) fillsize /= 2;
		else {                    // otherwise, total what we have
			filltotal += fillsize;
			numfilled++;
		}

	}

	while(numfilled) {          // Free up the heap again
		numfilled--;
		free(chunk[numfilled]);
	}


	return filltotal;
}



/**************************************************************************
	int random(int rmax)

	DESCRIPTION: Generic random function.  Generates number between 0 and
							 rmax.

**************************************************************************/
int random(int rmax)
{
	if(rmax < 1) rmax = 1;
	return rand() % rmax;

}


/**************************************************************************
	void Log(char *s, ...)

	DESCRIPTION: Convenience logging function

**************************************************************************/
void Log(char *s, ...)
{
	va_list ap;

	va_start(ap, s);                  			// sort out variable argument list
	if(gpLogFile) {
		vfprintf(gpLogFile,s,ap); 						// dump output to a string
		fflush(gpLogFile);                    // Protect Data from GPF's
	}
	va_end(ap);                            	// clean up

}
