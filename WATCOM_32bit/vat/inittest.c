#include "vat.h"
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <malloc.h>

struct chunk {
	char data[8211];
};


extern VAT_STATE internal_state;

void Show_State (void);
void startstoptest (void);

void main(void)
{
	memtest();
}

void memtest(void)
{
	int i,j;
	struct chunk *mylist[100];

	printf(	"VAT memory allocation/deallocation stress test (C++).\n\n"
					"Press any key to continue, then any key to halt.\n");

	getch();

	SBSetUp (44000, 70);
	GoVarmint ();
	while(!kbhit()) {
		fprintf(stderr,"Allocating");
		for(i = 0; i < 100; i++) {
			if(i%2) fprintf(stderr,".");
			mylist[i] = (struct chunk *)malloc(sizeof(struct chunk));
		}
		fprintf(stderr,"\nDeallocating");
		for(i = 0; i < 100; i++) {
			if(mylist[i]) {
				if(i%2) fprintf(stderr,".");
				free(mylist[i]);
			}
		}
		fprintf(stderr,"\n");
	}
	getch();
	DropDeadVarmint ();
	SBCleanUp ();
}

void startstoptest (void)
{
	WAVE *testwave;
	int i=1,j,retval;
	char errstring[256];

	testwave = LoadWave("varmint.wav",errstring);
	if(!testwave) {
		fprintf(stderr,"Loadwave ERROR: %s\n",errstring);
		return;
	}


	printf(	"VAT initialization stress test.\n\n"
					"Press any key to continue, then any key to halt.\n");
	getch();
	while(!kbhit()) {
		fprintf(stderr,"[Test %d] ",i++);
		retval = SBSetUp (44000, 70);
		fprintf(stderr,"Setup(%d),",retval);
		if(retval) {
			GoVarmint ();
			fprintf(stderr,"go,");
			for(j = 0; j < 20; j++) {
				PlayWave(testwave,v_false,v_fancy);
				MilliDelay(1);
			}

			DropDeadVarmint ();
			fprintf(stderr,"drop,");
//			MilliDelay(500);

			SBCleanUp ();
			fprintf(stderr,"Cleanup");
//			MilliDelay(100);
		}
		fprintf(stderr,"\n");
	}
	getch();

	fprintf(stderr,"All Done!\n\n");
}

void Show_State ()
{
  printf ("VAT's major version number: %d\n", internal_state.vat_vers_maj);
  printf ("VAT's minor version number: %d\n", internal_state.vat_vers_min);
  printf ("commercial copy? %d\n", internal_state.commercial);
  printf ("registration info: %s\n", internal_state.register_string);
  printf ("sample rate: %d\n", internal_state.sample_rate);
  printf ("refresh rate: %d\n", internal_state.refresh_rate);
  printf ("stereo allowed? %d\n", internal_state.allow_stereo);
  printf ("8-bit / 16-bit: %d\n", internal_state.bit_depth);
  printf ("DSP major version number: %d\n", internal_state.dsp_vers_maj);
  printf ("DSP minor version number: %d\n", internal_state.dsp_vers_min);
  printf ("BLASTER environment variable: %s\n", internal_state.blaster_string);
  printf ("BLASTER string 'A' element: 0x%X\n", internal_state.blaster_ioport);
  printf ("BLASTER string 'I' element: %d\n", internal_state.blaster_irq);
  printf ("BLASTER string 'D' element: %d\n", internal_state.blaster_lowdma);
  printf ("BLASTER string 'H' element: %d\n", internal_state.blaster_highdma);
  printf ("BLASTER string 'P' element: 0x%X\n", internal_state.blaster_mpuport);
  printf ("BLASTER string 'E' element: %d\n", internal_state.blaster_effects);
  printf ("BLASTER string 'T' element: %d\n", internal_state.blaster_cardtype);
  printf ("address being used for FM: 0x%X\n", internal_state.fm_addr);
  printf ("MIDI environment variable: %s\n", internal_state.midi_string);
  printf ("MIDI string 'SYNTH' element: %d\n", internal_state.midi_synth);
  printf ("MIDI string 'MAP' element: %d\n", internal_state.midi_map);
  printf ("MIDI string 'MODE' element: %d\n", internal_state.midi_mode);
  printf ("availability of audio output: %d\n", internal_state.status);
  getchar ();
}

