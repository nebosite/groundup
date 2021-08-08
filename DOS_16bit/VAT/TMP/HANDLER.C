#include <dos.h>
#include "vat.h"
																	 // Definitions
#define DOSYNC        if(sync_on && inportb(0x3da)&0x08) vsyncclock = 1000

																	 // External functions
void initwav(void);
void initmod(void);
void inits3m(void);
void initmid(void);

void wavplayer(void);
void modplayer(void);
void s3mplayer(void);
void midiplayer(void);

void venable(void);
void vdisable(void);
void dmaset(BYTE VFAR *sound_address,WORD len,BYTE channel);

																	 // external variables
extern SHORT              vinit;
extern WORD               dma_bufferlen;
extern SHORT VFAR         *mix_buffer;
extern SOUNDEFFECT VFAR   *soundlist;
extern SHORT              dma_currentbuffer;
extern BYTE VFAR          *dma_buffer[2];
extern WORD               dsp_vers;
extern WORD               dma_ch;
extern LONG               midi_count;
extern SHORT              midi_callfreq;
extern WORD               io_addr;

/**************************************************************************
	void VFAR _saveregs interrupt sbint()

	DESCRIPTION:  This is the sound Blaster interrupt that is to be
								called at the end of DMA transfer.  This is how the flow
								of things goes:

									Mix regular samples
									Mix MOD stuff
									Calculate next DMA half of buffer
									acknowledge interrupt
									Run the midi stuff.

								The DOSYNC's are macros define in sound.h designed to
								check the vertical retrace and then set vsyncclock so that
								these sound functions can be used with games that check
								the vertical retrace.

**************************************************************************/
void VFAR _saveregs _loadds interrupt sbint(void)
{
	SHORT i,j;
  LONG mcount,mskip;
	SHORT VFAR *mbuf;
	BYTE VFAR *dbuf;

	vdisable();                      // disable interrupts();

	if(vinit) {                      // Initialize the different players
		initwav();
		initmod();
		inits3m();
		initmid();
		vinit=FALSE;
	}


	if(DSP_overhead) TimerOn();      // start timer to measure DSP overhead

	DOSYNC;                          // Macro for checking the vertical retrace
																	 // clear out the mixing buffer
	for(j = 0; j < dma_bufferlen+1; j++) *(mix_buffer+j) = 128;
	DOSYNC;

	if(soundlist) wavplayer();       // Play wave data

	DOSYNC;


  if(mod_bytespertick < dma_bufferlen) mod_on = FALSE;
  if(s3m_bytespertick < dma_bufferlen) s3m_on = FALSE;

  if(mod_on && mod_data) modplayer();        // MOD stuff activated and ready?
  if(s3m_on && s3m_data) s3mplayer();        // S3M stuff activated and ready?


	if(debug_reverseflipflop) dma_currentbuffer ^= 1;

	DOSYNC;

																	 // Write mixed stuff to the playback buffer
	for(mbuf = mix_buffer, dbuf = dma_buffer[dma_currentbuffer];
			mbuf != mix_buffer+dma_bufferlen;
			mbuf++) {
		if(*mbuf > 254) *mbuf = 254;       // Clip overload values
		else if(*mbuf < 1) *mbuf = 1;
		*(dbuf++) = *mbuf;
	}

	DOSYNC;
	if(!debug_reverseflipflop) dma_currentbuffer ^= 1;

	if(dsp_vers < 0x200) {                 // Not SB 2.0?
																					// Set up DMA for one-shot
		dmaset(dma_buffer[dma_currentbuffer],dma_bufferlen-1,dma_ch);
		DOSYNC;
		DSPWrite(0x14);                       // One shot DMA DAC (8bit)
		DSPWrite((dma_bufferlen-1) & 0xff);  // Write length low byte
		DSPWrite((dma_bufferlen-1) >> 8);    // Write length high byte
	}


	DOSYNC;


																	 // Varmint's system clock
	vclock ++;                       // Vertical retrace sync clock
	vsyncclock ++;

																	 // MIDI stuff first
	midi_count-= 256;
	if(midi_count < 256) {
		midiplayer();                  // Call a midi player
    mcount =  ((LONG)midi_callfreq * midi_usertempo)/100;
                                   // CHeck to see if the frequency of
                                   // sbint is too course to play this
                                   // MIDI at full speed.
    if(mcount < 256) {
      mskip = (256/mcount) +1;
      mcount *= mskip;
      for(i = 1; i < mskip; i++) midiplayer();
    }
		midi_count += mcount;  // reset counter
		DOSYNC;
	}

	if(DSP_overhead) DSP_overhead = TimerOff();//  How long did this take?

	inportb(io_addr+DSP_RSTATUS);    // Acknowledge DSP interrupt

	outportb(0x20,0x20);             // Clear PIC
	outportb(0xa0,0x20);

	venable();                       // Enable interrupts again
}
