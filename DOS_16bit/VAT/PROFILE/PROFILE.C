/**************************************************************************

	EXAMPLE3.C

	Written by Eric Jorgensen (1995)

	The is an example program to illustrate how to use Varmint's Audio
	Tools to play MOD files.


**************************************************************************/

#include "vat.h"
#include <conio.h>
#include <alloc.h>
#include <stdio.h>
#include <stdlib.h>

void modplayer(void);
WORD mcalc(WORD);
void dotick(void);
void dodiv(void);
WORD upsemitone(WORD inc, WORD steps);
WORD downsemitone(WORD inc, WORD steps);
void initmod(void);



WORD mue3,mue23;
WORD               dma_bufferlen=64;
SHORT VFAR         *mix_buffer;
BYTE VFAR          *dma_buffer[2];
WORD vsyncclock=0,sample_rate=11000;
BYTE sync_on=0;
void main(void)
{
	int i;
																					// You need a MOD structure to
																					// hold the data from the MOD file.
	MOD far *song;
																					// You will also need a character
																					// string to catch any error
																					// messages from LoadMod().
	char errstring[100];


	dma_buffer[0] = (BYTE far *)farmalloc(1000);
	if(!dma_buffer[0]) {
		exit(1);
	}
	dma_buffer[1] = dma_buffer[0]+dma_bufferlen;

																				// Allocate space for Mixing buffer
	mix_buffer = (SHORT VFAR *)VMALLOC(dma_bufferlen*2+10);
	if(!mix_buffer) {
		return(FALSE);
	}

																					// In general, it is good to perform
																					// all file access before settup
																					// up the sound blaster.
	song = LoadMod("noname.mod",errstring);
	if(!song) {
		printf("ERROR loading MOD:  %s\n",errstring);
		exit(1);
	}

	mod_data = song;                        // Tell VAT which song to play.
	ModCommand(v_play);                     // Start the music!

	for(i = 1; i < 200; i++) modplayer();

	FreeMod(song);                          // Free our sond effect.

}
