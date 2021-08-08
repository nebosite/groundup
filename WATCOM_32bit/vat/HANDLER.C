/**************************************************************************
                        VARMINT'S AUDIO TOOLS 1.1

  HANDLER.C

    This contains the function used for the sb interrupt.


  Authors: Eric Jorgensen (smeagol@rt66.com)
           Bryan Wilkins  (bwilkins@rt66.com)

  Copyright 1995 - Ground Up


  NO-NONSENSE LISCENCE TERMS

    - This code is for personal use only.  Don't give it to anyone else.

    - You can use this code in your own applications, and you can even
      distribute these applications without royalty fees (please send
      us a copy!), but you can't include any of this source code with
      the distribution.

    - You may NOT use this code in your own libraires or programming tools
      if you are going to distribute them.

    - You are now responsible for this code.  If you put it in a game and
      it crashes the US Department of Defense computer system, it's your
      problem now, and not ours.

      We would like to hear about bug reports, but now that you have the
      code, it is not our responsibility to fix those bugs.

    - Ground Up is not obligated to provide technical support for VAT.
      (if you are willing to shell out a lot of clams, however, I am
      sure that we would be happy to drop what we're doing and help you
      out.)

                           **** WARNING ****

 Use Varmint's Audio Tools at your own risk.  We have tested VAT as much
 as we can, but we will not garantee that it won't turn your hair blue,
 rot your teeth, or send your love life spiraling even further into oblivion.

 VAT has been found to cause cancer in laboratory rats.

**************************************************************************/
#include <dos.h>
#include "vat.h"
#include "internal.h"

#define DSP_RSTATUS       0x0E

                                   // Definitions

                                   // External functions
//void initwav(void);
//void initmod(void);
//void inits3m(void);
//void initmid(void);
//void initnote(void);

void wavplayer(void);
void modplayer(void);
void s3mplayer(void);
void midiplayer(void);
void noteplayer(void);

void venable(void);
void vdisable(void);
void dmaset(BYTE  *sound_address,WORD len,BYTE channel);

                                   // external variables
extern SHORT           vinit;
extern SHORT          *mix_buffer;
extern SOUNDEFFECT    *soundlist;
extern SHORT           dma_currentbuffer;
extern BYTE           *dma_buffer[2];
extern WORD            dsp_vers;
extern WORD            dma_ch;
extern LONG            midi_count;
extern SHORT           midi_callfreq;
extern WORD            io_addr;
extern SHORT           midi_usertempo;
extern volatile WORD   vsyncclock;
extern volatile DWORD  vclock;
extern volatile SHORT  debug_reverseflipflop;
extern volatile WORD   DSP_overhead;

/**************************************************************************
  void  _saveregs interrupt sbint()

  DESCRIPTION:  This is the sound Blaster interrupt that is to be
                called at the end of DMA transfer.  This is how the flow
                of things goes:

                  Mix regular samples
                  Mix MOD stuff
                  Calculate next DMA half of buffer
                  acknowledge interrupt
                  Run the midi stuff.

**************************************************************************/
void  _saveregs _loadds interrupt sbint(void)
{
  SHORT i,j;
  static LONG mcount,mskip;
  SHORT  *mbuf;
  BYTE  *dbuf;

  vdisable();                      // disable interrupts();
  if(DSP_overhead) TimerOn();      // start timer to measure DSP overhead

                                   // To avoid static, update the DMA buffer
                                   // first thing!!
  if(debug_reverseflipflop) dma_currentbuffer ^= 1;

                                   // Write mixed stuff to the playback buffer
	for(mbuf = mix_buffer, dbuf = dma_buffer[dma_currentbuffer];
      mbuf != mix_buffer+dma_bufferlen;
      mbuf++) {
    if(*mbuf > 255) *mbuf = 255;       // Clip overload values
    else if(*mbuf < 0) *mbuf = 0;
    *(dbuf++) = *mbuf;
	}
																	// The long buffer is for when
																	// you need access to long streams
																	// of data without having to
																	// worry about your data collection
																	// getting interrupted.
	if( longbuffer) {
		for(i = 0; i < dma_bufferlen; i++) {
			*(longbuffer+(longbufferpointer%longbuffersize))
				= *(dma_buffer[dma_currentbuffer]+i);
			longbufferpointer++;
		}
	}

  if(!debug_reverseflipflop) dma_currentbuffer ^= 1;

  for(j = 0; j < dma_bufferlen+1; j++) {
    *(mix_buffer+j) = 128;
  }

	if(soundlist) wavplayer();       // Play wave data
	noteplayer();

/*** Moved to respective modules to make variables static
  if(mod_bytespertick < dma_bufferlen) mod_on = v_false;
  if(s3m_bytespertick < dma_bufferlen) s3m_on = v_false;

  if(mod_on && mod_data) modplayer();        // MOD stuff activated and ready?
  if(s3m_on && s3m_data) s3mplayer();        // S3M stuff activated and ready?
***/
	modplayer();
	s3mplayer();

  if(dsp_vers < 0x200) {                 // Not SB 2.0?
                                          // Set up DMA for one-shot
    dmaset(dma_buffer[dma_currentbuffer],dma_bufferlen-1,dma_ch);
    DSPWrite(0x14);                       // One shot DMA DAC (8bit)
    DSPWrite((dma_bufferlen-1) & 0xff);  // Write length low byte
    DSPWrite((dma_bufferlen-1) >> 8);    // Write length high byte
  }





  vclock ++;                       // Varmint's system clock
  vsyncclock ++;                   // Vertical retrace sync clock

                                   // MIDI stuff
  midi_count-= 256;
	if(midi_count < 256) {
		midiplayer();                  // Call a midi player
    mcount =  ((LONG)midi_callfreq * midi_usertempo)/100;
                                   // CHeck to see if the frequency of
                                   // sbint is too course to play this
                                   // MIDI at full speed.  If it is, the
                                   // call midiplayer() extra times to
                                   // keep up.
    if(mcount < 256) {
      mskip = (256/mcount) +1;
      mcount *= mskip;
			for(i = 1; i < mskip; i++) midiplayer();
    }
    midi_count += mcount;           // reset counter
  }

  if(DSP_overhead) DSP_overhead = TimerOff();//  How long did this take?

  VINPORTB(io_addr+DSP_RSTATUS);    // Acknowledge DSP interrupt

  VOUTPORTB(0x20,0x20);             // Clear PIC
  VOUTPORTB(0xa0,0x20);

  venable();                       // Enable interrupts again
}
