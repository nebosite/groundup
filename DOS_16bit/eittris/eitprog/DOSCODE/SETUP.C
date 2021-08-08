
/**************************************************************************
	SETUP.C

**************************************************************************/
#include "tetris.h"
#include "hiscore.h"

DWORD dateearly=19960203L;
DWORD datelate=19960504L;

WORD tetrissamplerate = 22000;

Font font;
extern WORD         dsp_vers;
extern SHORT					debug_lowdsp;


/*char *soundfilename[]={
	"!PCEFUL1.WAV",              // 0
	"AGONY.WAV",                 // 1
	"ALARMCLK.WAV",              // 2
	"AWWWWW.WAV",                // 3
	"BIGPIPE.WAV",               // 4
	"BIGSMSH.WAV",               // 5
	"CAMEL.WAV",                 // 6
	"CARHORN.WAV",               // 7
	"CRICKET.WAV",               // 8
	"DENTDRIL.WAV",              // 9
	"DOCOE.WAV",                 // 10
	"DRIP.WAV",                  // 11
	"NELSON.WAV",                // 12
	"THIP.WAV",                  // 13
	"THUP.WAV",                  // 14
	"TAP.WAV",                   // 15
	"BING.WAV",                  // 16
	"DOK.WAV",                   // 17
	"PFFEHH.WAV",                // 18
	"DANK.WAV",                  // 19
	"PMP.WAV",                   // 20
	"DROP.WAV"};                 // 21  */

int speedtest();

/**************************************************************************
	void setup(void)

	DESCRIPTION:  Sets up graphics and everything


**************************************************************************/
void setup(void)
{
	void eittimer(void);
	int i,j=0,k,n;
	FILE *fontfile;
	extern SAMPLE *test[];
	int gerr;
	WORD cspeed;
	//struct date today;
	//DWORD date1;


	clrscr();
	DSP_overhead = 0;

																			 // Set up timer for millisecond
																			 // intervals
	InstallTimer0(1181,eittimer);


																		// Check the date
	//getdate(&today);
	//date1 = today.da_year*10000L + today.da_mon * 100L + (DWORD)today.da_day;

	textcolor(WHITE);
	cprintf("\n                        Varmint's EITtris Version %s\r\n\n",VERSION);

/*  if(date1 < dateearly || date1 > datelate) {
  	printf("\nThe current date is (%d/%d/%d).\n",
						(int)today.da_mon,(int)today.da_day,(int)today.da_year );
    printf("This beta version is not valid at this time.  Please check\n");
		printf("     http://www.ericjorgensen.com/eittris\n");
    printf("For the most recent version.\n");
    exit(2);
	}*/

	textcolor(LIGHTRED);
	cprintf(
	"If you are having problems running Varmint's EITtris, please read\r\n"
	"the file named TROUBLE.TXT for some troubleshooting tips.\r\n\r\n");
	printf("EITtris is ");
	textcolor(YELLOW);
	cprintf(">>FREEWARE<<\r\n\n");
	printf(
	"I want everyone to enjoy this game freely, so copy it all you want,\n"
	"put it on shareware CD-Roms, BBS's, FTP sites, etc...  Just don't\n"
	"charge any money for it other than incidental costs necessary for\n"
	"distribution.\n"
	"\n"
	"Author:  Eric Jorgensen\n"
	"Author's email: varmint@ericjorgensen.com\n"
	"Author's WWW Home Page:  http://www.ericjorgensen.com\n"
	"EITtris Home Page:  http://www.ericjorgensen.com/eittris\n"
	"\n");


  randomize();
	readconfig();

	if(!highscoreson) {
		clrscr();
		printf("Notice:  \n\n"
		"High scores have been deactivated because you have altered game play\n"
		"options in EITTRIS.CFG.  If you want to play with high scores enabled,\n"
		"you need to comment out any game play option settings.\n\n"
		"Please press any key to continue...\n");
		getch();
	}


	for(i=0; i < MAXPLAYERS; i++) person[i] = NULL;  		// reset all player pointers
  for(i = 0; i < 50; i++) bgrnd[i] = NULL;    // reset backgroun pointers

  for(i= 0; i < 256; i++) {
		charbuffer[i] = 0;  							// reset input buffer
		fade[i] = i;                      // initialize fade values
    bwfade[i] = i;
  }
																// Make sure we have hi scores loaded
	if(!scores) scores = readscores();

  																		// initialize sound blaster
	if(soundtype == SBSOUND) {
		integritytest=TRUE;
		if(SBSetUp() != 0) {
																			// Set the sample rate
			SetSampleRate(tetrissamplerate);
			/*for(i = 0; i < 22; i++) {        // Load sound effects
      	soundbite[i] = LoadWave(soundfilename[i],&soundlength[i]);
      }
      writesounds();*/
			setsounds();
		}
    else{
			soundtype = PCSOUND;
		}
		integritytest=FALSE;

	}
	else {                              // Need this in case SB not selected
		InitTimerFunctions();
	}

	whichvga();             						// Initialize graphics
	if(hires) gerr = res1024();
	else gerr = res800();
	if(!gerr) {
		restext();
		printf("ERROR: Graphics cannot initialize.  Perhaps you could try \n");
		printf("changing the HIRES option in the config file.\n");
		exit(0);
  }

	fontfile = fopen("eittris.fon","rb");// open font file for binary read
	if(fontfile) {
	  fread(&font,4098,1,fontfile);
	  fclose(fontfile);
	  fontset(&font);
	}

	txtht = textheight("A")+2;


                                      // allocate dummy blocks

	dummy[0] = (RasterBlock far *)farmalloc(2000);
	if(!dummy[0]) {
		restext();
		printf("Out of memory.\n");
	}

																					// Blank the colors to make things

																			// look clean.
	for(i=0; i < 256; i++) setcol(&palette[i],0,0,0);
	palset(palette,0,255);
																			// Create 666 palette and 4bit greyscale
  for(i = 0; i < 6; i++) {
  	for(j = 0; j < 6; j++) {
  		for(k = 0; k < 6; k++) {
      	setcol(&palette[i+j*6+k*36],i*12.6,j*12.6,k*12.6);
        fade[i+j*6+k*36] = (int)(i/2.0 + 0.5) + (int)(j/2.0 + 0.5)*6 +
													 (int)(k/2.0 + 0.5)*36;
				bwfade[i+j*6+k*36] = (i * 0.2 + j * 0.5 + k * 0.3 ) * 1.2 + 216;
      }
    }
  }
  for(i = 0; i < 16; i++) {
		setcol(&palette[i+216],i*4.2,i*4.2,i*4.2);
    fade[i+216] = 216+i/2;
    bwfade[i+216] = 216+i/3;

  }

	pcxput(SET,0,0,"res800.pcx");       // Load block graphics
  for(i = 0; i < 256; i++) shape[i] = NULL;


	for(i = 0; i < 17; i++) {           // Read the normal blocks
  	shape[i] = (RasterBlock far *)farmalloc(
								(block_width+1)*(block_height+1)+20);
    if(!shape[i]) {
    	restext();
      printf("OUT of memory.\n");
      exit(1);
    }
    blkget((i%20)*block_width,(i/20)*block_height,
					 (i%20)*block_width+block_width-1,
					 (i/20)*block_height+block_height-1,shape[i]);

	}
																					// Read the special blocks
	for(i = SPECIALBASE; i < SPECIALBASE + NUMBEROFSPECIALS; i++) {
  	shape[i] = (RasterBlock far *)farmalloc(
								(block_width+1)*(block_height+1)+20);
    if(!shape[i]) {
    	restext();
			printf("OUT of memory. (special sprites)\n");
      exit(1);
    }
		blkget((i%20)*block_width,
					 (i/20)*block_height,
					 (i%20)*block_width+block_width-1,
					 (i/20)*block_height+block_height-1,shape[i]);

	}

	for(i  = 0; i < numbackgrounds; i++) {  // Read backgrounds
																					// Create the structures
		bgrnd[i] = (BGROUND *)farmalloc(sizeof(BGROUND));
		if(!bgrnd[i]) {
			restext();
			printf("OUT of memory. (Backgrounds)\n");
			exit(1);
		}
																					// Fill them up
		for(j = 0; j < 2; j++) {
			for(k = 0; k < 2; k++) {
				bgrnd[i]->b[j][k] = (RasterBlock far *)farmalloc(
								(block_width+1)*(block_height+1)+20);
				if(!bgrnd[i]->b[j][k]) {
					restext();
					printf("OUT of memory. (Backgrounds)\n");
					exit(1);
				}
				n = (i%10)*2 +(i/10)*40 + 80 + j + k*20;
				blkget((n%20)*block_width,(n/20)*block_height,
							 (n%20)*block_width+block_width-1,
							 (n/20)*block_height+block_height-1,bgrnd[i]->b[j][k]);
			}
    }
	}




	for(i = ANIMBASE; i < ANIMBASE+12; i++) {           // Read the animations
  	shape[i] = (RasterBlock far *)farmalloc(
								(block_width+1)*(block_height+1)+20);
    if(!shape[i]) {
    	restext();
      printf("OUT of memory.\n");
      exit(1);
    }
		blkget((i%20)*block_width,(i/20)*block_height,
					 (i%20)*block_width+block_width-1,
					 (i/20)*block_height+block_height-1,shape[i]);

  }

  for(i = 0; i < 256; i++) {          // Assign all the shapes for kicks
  	if(!shape[i]) shape[i] = shape[0];
  }

	fillpage(0);                        // clear the screen
	palset(palette,0,255);              // install palette

																			// Test the speed of this computer.
																			// Slow computers should not be
																			// allowed to enter high scores
																			// on the web page.
	cspeed = 0;
	for(i = 0; i < 5; i++) {
		cspeed += speedtest();
	}

	cspeed /= 5;
	if(cspeed > 4500) {
		slowcomputer = TRUE;
	}

	//mouse = whichmouse();             // initialize mouse
}



/**************************************************************************
	int speedtest()

	DESCRIPTION: 	Evaluates the speed of the computer.  We want to invalidate
								high scores if the computer is slow.

**************************************************************************/
int speedtest()
{
	int i,j;
	WORD t = 0;

	TimerOn();
	blkget(0,0,8,5,dummy[0]);
	for(j = 0; j < 600; j+=5) {
		blkput(SET,0,j,dummy[0]);
	}
	t = TimerOff();
	return t;
}


/**************************************************************************
	void writesounds(void)

	DESCRIPTION:   Writes the sound data to a linkable file

**************************************************************************/
/*void writesounds(void)
{
	//FILE *output;
	//int i,k,j;

	output = fopen("sdata.c","w");
  if(!output) return;


	fprintf(output,"#include \"tetris.h\"\n\n\n");

	for(i  = 0; i < 22; i++) {
  	fprintf(output,"SAMPLE sound%d[]={",i);
    for(j = 1; j <= soundlength[i]; j++) {
    	if(!(j%20)) fprintf(output,"\n");
      k = *(soundbite[i]+j);
      fprintf(output,"%d",k);
      if(j != soundlength[i]) fprintf(output,",");
    }
  	fprintf(output,"};\n\n");
	}

	fprintf(output,"void setsounds(void)\n{");
  for(i  = 0; i < 22; i++) {
  	fprintf(output,"  soundbite[%d]=sound%d;\n",i,i);
  	fprintf(output,"  soundlength[%d]=%lu;\n",i,soundlength[i]);
  }
  fprintf(output,"}\n");

  fclose(output);

}  */
