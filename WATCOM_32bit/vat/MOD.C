/**************************************************************************
                        VARMINT'S AUDIO TOOLS 1.1

  MOD.C

    This file contains source code far all MOD related functions in VAT.


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
#include <stdio.h>
#include <malloc.h>
#include <dos.h>
#include <string.h>
#include "compat.h"
#include "vat.h"
#include "internal.h"

//-------------------------------- Internal Functions

void dotick(void);
void dodiv(void);
LONG upsemitone(LONG inc, LONG steps);
LONG downsemitone(LONG inc, LONG steps);
void initmod(void);


//-------------------------------- External varaibles

extern VATSTATUS internal_status;
extern SHORT *mix_buffer,vsin[];
extern DWORD internal_sample_rate;
extern DWORD vat_stereo;
extern SHORT vol_table[64][256];

//-------------------------------- MOD varaibles

static MOD     *mod_data = NULL;
static SHORT mod_on = v_false;
static SHORT mod_reset = v_false;
SHORT				mod_printout = v_false;
SHORT mod_tablepos=0;
BYTE    *mod_pattern,*mod_pstop,*mod_loopspot=NULL;
SHORT       mod_loopcount = -1;
//static
SHORT       mod_bytespertick = 220;
SHORT mod_ticksperdivision = 6;
SHORT       mod_currentbyte = 0,mod_currenttick = 0;
SHORT       mod_divoffset =0;
SHORT       mod_glissando = v_false;
SHORT       mod_finetune = 0;
SHORT       mod_patterndelay = 0;
static SHORT       mod_volume = 50;
WORD        mod_vibratocount = 0;
static VATBOOL mod_hardstop = v_false;
BYTE        mod_channelselect[4] = {1,1,1,1};
VATSTATUS   mod_status=v_nonexist;
static CHANNEL  chan[4];


/*************************************************************************
void modplayer(void)

DESCRIPTION: Routine for playing mod files.  This is designed to be called
						 from a timer interrupt.  To use these values must be set:

						 mod_data must point to a filled mod structure
						 mod_reset must be v_true.
						 mod_on must be v_true.

						 The interrupt should pick up from here.
*************************************************************************/
void modplayer(void)
{
	static int i,j;
	static SHORT vol;
	SHORT *vt;
	SHORT  lastbyte;
	static DWORD dummy1=0,position=0,dummy2=0,end,pinc;
	DWORD *pos;
	SAMPLE *data;
	// +ECODE: New Variables Here
	DWORD bufpos,mixto,bytestomix;
	ARRAYTYPE dval;
	// -ECODE

	// moved here from handler.c to make mod_on static
	if (!mod_on || !mod_data)
		return;

	pos = (DWORD *)(((BYTE *)&position)+1);

	if(mod_reset) {                // Reset the MOD?
		for(i = 0; i < 4; i++ ) {    // Reset all four channels
			chan[i].bufferdummy1 = 0;
			chan[i].bufferdummy2 = 0;
			chan[i].sdata = NULL;
			chan[i].offset = 0;
      chan[i].rlength = 0;
      chan[i].end = -1;
      chan[i].volume = 0;
      chan[i].sample_number = 0;
      chan[i].position= 0;
      chan[i].pos = (DWORD *)(((BYTE *)&chan[i].position)+1);
      chan[i].counter = 0;
      chan[i].pinc = 0;
      chan[i].effect = 0;
      chan[i].x = 0;
      chan[i].y = 0;
      chan[i].period=0;
			chan[i].count = 0;
      chan[i].data1 = 0;
      chan[i].data2 = 0;
      chan[i].data3 = 0;
      chan[i].data4 = 0;
      chan[i].vslide = 0;
      chan[i].cut = 0;
     }
                                     // Reset global mod variables
    mod_pattern=mod_data->pattern_data[mod_data->ptable[0]];
		mod_pstop = mod_pattern+1024;
    mod_tablepos=0;
//    mod_bytespertick = (WORD)(((LONG)internal_sample_rate * 220 * (vat_stereo+1))/11000L);
    mod_bytespertick=(WORD)(((LONG)internal_sample_rate*60)/(24*125))<<vat_stereo;
    if (mod_bytespertick < dma_bufferlen)
      mod_bytespertick = dma_bufferlen;
//    if(mod_bytespertick&1)mod_bytespertick++;
    mod_ticksperdivision = 6;
    mod_currentbyte = 0;
    mod_currenttick = 0;
    mod_divoffset =0;
		mod_reset = v_false;           // Reset the reset switch
		mod_hardstop = v_false;
  }


	bufpos = 0;
	while(bufpos < dma_bufferlen) {
																	 // Tempo correction.  Odd tempos mess
																	 // up stereo mixing.
		mod_bytespertick = (mod_bytespertick/2)*2;
		if(mod_bytespertick < 2) mod_bytespertick = 2;

		if(mod_currentbyte < (dma_bufferlen-bufpos)) {
			mixto = bufpos + mod_currentbyte;
			bytestomix = mod_currentbyte;
    }
    else { 
      mixto = dma_bufferlen;
      bytestomix = dma_bufferlen-bufpos;
    }
																	// Mix buffer from bufpos to mixto

		for(i = 0; i < 4; i++) {     // Loop through the four channels

                                     // If the volume is zero or if the sample
                                     // has ended, then there is no need to mix
                                     // anything.

			if(chan[i].volume && *chan[i].pos <= chan[i].end && chan[i].sdata) {
        vol = (chan[i].volume * mod_volume)/100;
        vt = vol_table[vol]+128;
				data = chan[i].sdata;
        position = chan[i].position;
        end = chan[i].end*256;
        pinc = chan[i].pinc;
                                    // Loop along the length of the mixing buffer
				for(j = (i&vat_stereo)+bufpos; j < mixto; j+=(vat_stereo+1)) {
																 // Add this byte to the mixing buffer
					dval = (*(data + (ARRAYTYPE)*pos));
					*(mix_buffer+j) += vt[dval];
                                     // Here is where the frequency magic
                                     // happens.  I use fixed point arithmatic
                                     // to increment the sample position pointer
                                     // at different rates.
          position += pinc;
                                    // Are we at the end of the sample?
          if(position >= end) {
                                     // Repeating?  Move the position back.
            if(chan[i].rlength > 1) {
              *pos -= chan[i].rlength;
							*chan[i].pos = *pos;

              chan[i].counter = 0;
              end = chan[i].end = chan[i].offset+chan[i].rlength;
              end *=256;
            }

            else break;          // else Jump out of mixing loop
          }
        }
        chan[i].position = position;
      }
    }
                                     // Keep track of where we are.
		//mod_currentbyte -= dma_bufferlen;
		mod_currentbyte -= bytestomix;
  
		if(mod_currentbyte <= 0 ) {
																	 // Ready for next division?
			if(mod_currenttick >= mod_ticksperdivision * (mod_patterndelay+1) ) {
				mod_patterndelay = 0;      // Reset pattern delay
				dodiv();                   // Handle the division commands.
																	 // Are we at the end of the pattern?
				if((mod_pattern == mod_pstop)  || mod_hardstop) {
					mod_tablepos++;          // Next table!

																			 // Done with tables?  Done with MOD.
					if ((mod_tablepos == mod_data->num_positions) || mod_hardstop) {
						mod_on = v_false;
						mod_reset = v_true;
						mod_status = v_stopped;
						if (mod_data->chainfunc) { // Check for a chain function
							mod_data->chainfunc ();
							mod_data->chainfunc = NULL;
						}
						if (mod_data->chain) {      // Check for a chain
							mod_data = mod_data->chain;
							mod_data->chain = NULL;
							mod_on = v_true;
							mod_status = v_started;
						} else if (mod_data->repeatmusic) {  // repeat?
							if (mod_data->repeatmusic > 0)
								mod_data->repeatmusic--;
							mod_on = v_true;
							mod_status = v_started;
						}
						return;                    // We must stop mixing here or we
																			 // won't reset the s3m before we
																			 // do more mixing.
					}
					else {                   // Otherwise, set pointer to next table
						mod_pattern = mod_data->pattern_data[mod_data->ptable[mod_tablepos]];
						mod_pstop = mod_pattern+1024;
					}
				}
				mod_currenttick = 0;       // Reset the tick counter
			}
																			 // Reset the byte counter
			mod_currentbyte = mod_bytespertick;

			dotick();
			mod_currenttick++;           // Do our tick stuff.

		}
		bufpos = mixto;
  }

}


/**************************************************************************
  WORD calcvibrato(WORD inc,WORD period,WORD amplitude)

  DESCRIPTION:  Caluculates a new inc value based on vibrato parameters

	INPUTS:
    inc       Base value
    period    (period * ticks_per_division)/64 = cycles per division
    amplitude Amplitde of the occillation.

  RETURNS:
    New inc value

**************************************************************************/
LONG calcvibrato(LONG inc,LONG period,LONG amplitude)
{
  LONG newinc,theta;

//gotoxy(1,1);
//fprintf(stderr,"I: %d  P:%d  A:%d   ",(int)inc,(int)period,(int)amplitude);


                                          // claculate sin wave parameter
	theta = (((LONG)period * mod_vibratocount * 100) / 64) % 100;
                                          // grab precalclated sin
	inc += ((LONG)vsin[(ARRAYTYPE)theta] * amplitude)/2048;

	return inc;
}

/**************************************************************************
  void dotick(void)

  DESCRIPTION:  Handles ongoing MOD commands at each tick.

**************************************************************************/
void dotick(void)
{
	SHORT i;                              // Local variable we need
	WORD period,rate;
	BYTE e1,e2;
	LONG tempinc;

	mod_vibratocount++;

	for(i = 0; i < 4; i++) {                // Loop through all four channels
		e1 = chan[i].effect;                  // Get info aboput what is going on
		e2 = chan[i].x;

    if(chan[i].retrigger) {               // Check for a retrigger signal
                                          // Time to retrigger?
      if(!(mod_currenttick % chan[i].retrigger)) {
        chan[i].position = 0;
        chan[i].counter = 0;
        chan[i].end = mod_data->slength[chan[i].sample_number-1];
			}
    }

    if(chan[i].cut > -1) {                // Check for a cut signal
      if(mod_currenttick >= chan[i].cut) chan[i].volume = 0;
    }

    switch(e1) {
      case 0:                              // Arpeggio
				chan[i].count++;
        switch(chan[i].count % 3) {
          case 0:
            chan[i].pinc = chan[i].data1;
            break;
          case 1:
            chan[i].pinc = chan[i].data2;
            break;
          case 2:
            chan[i].pinc = chan[i].data3;
            break;
        }
        break;
      case 1:                              // Slide up
                                             // glissando = chromatic slide
        if(!mod_glissando) chan[i].period -= chan[i].porta;
				else chan[i].period = upsemitone(chan[i].period,chan[i].porta);
                                             // Don't go too high
        if(chan[i].period < 1) chan[i].period = 1;
                                             // Set frequency counters
        rate = (WORD)(3546894L/chan[i].period);
        chan[i].pinc = ((LONG)rate * 256)/internal_sample_rate;
        break;
      case 2:                              // slide down
				if(!mod_glissando) chan[i].period += chan[i].porta;
																						 // glissando = chromatic slide
				else chan[i].period = downsemitone(chan[i].period,chan[i].porta);
																						 // Don't go too low
				if(chan[i].period > 2000) chan[i].period = 2000;
																						 // Set frequency counters
				rate =(WORD)( 3546894L/chan[i].period);
				chan[i].pinc = ((LONG)rate * 256)/internal_sample_rate;
        break;
			case 3:                              // slide to note
                                             // Slide up or down? Each case is
                                             // just like regular up and down
                                             // slides.
        if(chan[i].period < chan[i].period2) {
          if(!mod_glissando) chan[i].period += chan[i].porta;
          else chan[i].period = downsemitone(chan[i].period,chan[i].porta);
          if(chan[i].period > chan[i].period2) chan[i].period = chan[i].period2;
        }
        else if(chan[i].period > chan[i].period2) {
          if(!mod_glissando) chan[i].period -= chan[i].porta;
					else chan[i].period = upsemitone(chan[i].period,chan[i].porta);
          if(chan[i].period < chan[i].period2) chan[i].period = chan[i].period2;
        }
                                             // Set frequency counters
        if(chan[i].period<1) chan[i].period=1;
        rate = (WORD)(3546894L/chan[i].period);
        chan[i].pinc = ((LONG)rate * 256)/internal_sample_rate;
        break;
      case 4:                              // vibrato
				period =chan[i].period;
                                             // Set frequency counters
				rate = (WORD)(3546894L/period);
				tempinc = rate * 256L;
				tempinc = calcvibrato(tempinc,chan[i].vibperiod,chan[i].vibdepth);
				chan[i].pinc = tempinc/(DWORD)internal_sample_rate;
				break;
      case 5:                             // Cont. Slide to note + vol. Slide
        if(chan[i].period < chan[i].period2) {
          chan[i].period += chan[i].porta;
          if(chan[i].period > chan[i].period2) chan[i].period = chan[i].period2;
        }
        else if(chan[i].period > chan[i].period2) {
          chan[i].period -= chan[i].porta;
          if(chan[i].period < chan[i].period2) chan[i].period = chan[i].period2;
        }
				rate = (WORD)(3546894L/chan[i].period);
        chan[i].pinc = ((LONG)rate * 256)/internal_sample_rate;

        chan[i].volume += chan[i].vslide;
        if(chan[i].volume < 0) chan[i].volume = 0;
        if(chan[i].volume > 64) chan[i].volume = 64;
        break;
			case 6:                              // Vibrato + volume slide
				period =chan[i].period;
                                             // Set frequency counters
				rate = (WORD)(3546894L/period);
				tempinc = rate * 256L;
				tempinc = calcvibrato(tempinc,chan[i].vibperiod,chan[i].vibdepth);
				chan[i].pinc = tempinc/(DWORD)internal_sample_rate;

        chan[i].volume += chan[i].vslide;
        if(chan[i].volume < 0) chan[i].volume = 0;
        if(chan[i].volume > 64) chan[i].volume = 64;
        break;
      case 7:                              // Tremolo
																						 // Just like Vibrato except with
                                             // this modulates sample volume
        period = calcvibrato(chan[i].volume,chan[i].vibperiod,chan[i].vibdepth);


        if(chan[i].volume < 0) chan[i].volume = 0;
        if(chan[i].volume > 64) chan[i].volume = 64;
        break;
      case 10:                            // Volume slide
        chan[i].volume += chan[i].vslide; // change the volume.
                                          // Clip.
        if(chan[i].volume < 0) chan[i].volume = 0;
        if(chan[i].volume > 64) chan[i].volume = 64;
				break;
      case 14:
        switch(e2) {
          case 13:                        //  Delay sample
                                          // data4 is decremented on each
                                          // Pass.  When it gets to zero,
                                          // the sample volume is turned
                                          // on.
            if(!chan[i].data4) chan[i].volume = chan[i].data3;
            chan[i].data4--;
						break;
          default:
            break;
        }
        break;
      case 15:
        break;
			default:
        break;
    }

    chan[i].volume *= mod_channelselect[i];  // Activate channel mask
  }
}


/**************************************************************************
	WORD upsemitone(WORD inc, WORD steps)

  DESCRIPTION:  Moves a MOD frequency up the specified number of
                half-steps.

  INPUTS:
    inc     fixed point inc value
    steps   nmber of half-steps to go up

  RETURNS:
    New pinc value

**************************************************************************/
LONG upsemitone(LONG inc, LONG steps)
{
  LONG newinc;


  newinc = (LONG)inc * 256;                // Convert inc to fixed point

  while(steps) {                          // loop through the steps
    newinc = (newinc * 944)/1000L;        // Move up a semitone
    steps--;
  }

	return(WORD)(newinc / 256);              // Convert back to SHORT and return
}

/**************************************************************************
  WORD downsemitone(WORD inc, WORD steps)

  DESCRIPTION:  Moves a MOD frequency down the specified number of
								half-steps.

  INPUTS:
    inc     fixed point inc value
    steps   nmber of half-steps to go up

  RETURNS:
    New pinc value

**************************************************************************/
LONG downsemitone(LONG inc, LONG steps)
{
  LONG newinc;


  newinc = (LONG)inc * 256;                      // Convert inc to fixed point

  while(steps) {                          // loop through the steps
    newinc = (newinc * 1059)/1000L;       // Move down a semitone
    steps--;
  }

  return(WORD)(newinc / 256);              // Convert back to SHORT and return
}

/**************************************************************************
  void dodiv(void)

  DESCRIPTION:  Handles the commands found at a module division.

**************************************************************************/
void dodiv(void)
{
	int i,j,k,stone;                        // Local variables we'll need
  SHORT samp,pattern_break = v_false,position_jump = v_false,loop = v_false;
	SHORT period,rate;
	BYTE e1,e2,e3;
	LONG tempinc;


	if(mod_printout) {                      // Some diagnostics
		i = (long)(mod_pstop-mod_pattern)/16;
		if(i == 64) printf("DIVISION: %x/%x\n",mod_tablepos,mod_data->num_positions);
		printf("  D%d]\t",i);
	}

  for(i = 0; i < 4; i++) {                // Loop through all four channels
    chan[i].retrigger = 0;                // Reset retrigger and cut signals
    chan[i].cut  = -1;
                                          // Grab information for this channel
    samp = (*(mod_pattern)&0xF0) + ((*(mod_pattern+2) & 0xf0)>>4);
    period = (*(mod_pattern)&0x0F)*256 + *(mod_pattern+1);
    e1 = (*(mod_pattern+2)) & 0x0F;       // e1-e3 are the command nibbles
    e2 = (*(mod_pattern+3)  & 0xF0) >> 4;
    e3 = (*(mod_pattern+3)) & 0x0F;

		if(samp && samp <= 32 && mod_data->sdata[samp-1]) {  // set a new sample?
      chan[i].sample_number = samp;       // Some MOD commmands need this
      chan[i].volume = mod_data->volume[chan[i].sample_number-1];
                                          // Set the volume to the default
		}


    if(e1 != 3 && period ) {                 // set a new period?
			chan[i].sdata = mod_data->sdata[chan[i].sample_number-1]; // set a pointer to the data
      chan[i].end = mod_data->slength[chan[i].sample_number-1];
                                          // store sample characteristics
      chan[i].offset = mod_data->offset[chan[i].sample_number-1];
      chan[i].rlength = mod_data->repeat[chan[i].sample_number-1];
                                          // Keep track of end so we know
                                          // When to stop.
      if(chan[i].rlength) chan[i].end = chan[i].offset+chan[i].rlength;

      chan[i].position = 0;               // Retrigger the sample
      chan[i].counter = 0;
                                          // Calculate adjusted period
			chan[i].period = period + mod_data->finetune[chan[i].sample_number-1]
                              + mod_finetune;
																					// Set frequency counter
      rate =(WORD)(3546894L/period);
      chan[i].pinc = ((LONG)rate*256)/internal_sample_rate;
    }
                                          // Sometimes song start off
                                          // without specifying any period,
                                          // so I am picking  a default here
		if(!chan[i].period) chan[i].period = 428;

    chan[i].effect = e1;                    // Keep for reference in dotick()
    chan[i].x = e2;
    chan[i].y = e3;

		if(mod_printout) {                      // Some diagnostics
			printf("C%d E%d,%d,%d \tP%d S%d\t | ",i,e1,e2,e3,period,samp );
		}

    switch(e1) {                            // Process the commands
      case 0:                               // Arpeggio
        chan[i].data1 = chan[i].pinc;       // First frequncy
        chan[i].data2 = upsemitone(chan[i].pinc,e2); // Second frequency
        chan[i].data3 = upsemitone(chan[i].pinc,e3); // Third Frequency

        chan[i].count = 0;
        break;
      case 1:                              // Slide up.
        chan[i].porta = e2*16 + e3;          // Calculate slide rate
        break;
      case 2:                              // slide down
        chan[i].porta = e2*16 + e3;          // calculate slide rate
        break;
      case 3:                              // Slide to note
        if(e2 || e3) chan[i].porta = e2*16 + e3;
        if(period) chan[i].period2 = period;
        break;
      case 4:                              // Vibrato (My implementation
                                           // Of this command assumes that
                                           // The wave form is a triggered
                                           // Sin wave.   There are other
                                           // forms defined , but they are
																					 // used very rarely and I don't
                                           // feel like coding them in.

                                             // These numbers will be used
                                             // to calculate the waveform.
				if(e2 || e3) mod_vibratocount = 0; // retrigger waveform?
				if(e2) chan[i].vibperiod = e2;
				if(e3) {
					period =chan[i].period;
																							 // Set frequency counters
					rate = (WORD)(3546894L/chan[i].period);
					tempinc = rate * 256L;
					stone = tempinc - upsemitone(tempinc,1);
					chan[i].vibdepth = ((LONG)e3 * stone )/16L;
				}
				break;
      case 5:                              // Continue Slide to Note + Volume Slide
      case 6:                              // Continue Vibrato + volume slide
                                             // For both of these commands,
                                             // We just need to keep track
                                             // of the volume slide rate
        if((e2 > 0 && e3 > 0) || e3 == 0) chan[i].vslide = e2;
        else chan[i].vslide = -e3;
                                             // If the period is specified,
                                             // Then the volume needs to be
                                             // reset.
        if(period)chan[i].volume = mod_data->volume[chan[i].sample_number-1];
        break;
      case 7:                              // Tremolo (My implementation
                                           // Of this command assumes that
                                           // The wave form is a triggered
                                           // Sin wave.   There are other
                                           // forms defined , but they are
                                           // use very rarely and I dont't
                                           // feel like coding them in.

                                             // These values will be used to
                                             // claculate the wave form
        if(e2) chan[i].vibperiod = e2* mod_ticksperdivision;
        if(e3) chan[i].vibdepth = e3;
        chan[i].volume2 = chan[i].volume;
        break;
      case 8:                              // UNUSED
        break;
			case 9:                              // Set new sample offset
				*chan[i].pos = (e2*4096L+e3*256L)*2L;
        break;
      case 10:                             // Volume slide
                                             // Calculate slide rate
				if((e2 > 0 && e3 > 0) || e3 == 0) chan[i].vslide = e2;
        else chan[i].vslide = -e3;
        if(period)chan[i].volume = mod_data->volume[chan[i].sample_number-1];
        break;
      case 11:                             // Table position jump
        mod_tablepos = e2*16+e3;
        position_jump = v_true;
        break;
      case 12:                             // Set Volume
        chan[i].volume = e2*16+e3;
        if(chan[i].volume>64) chan[i].volume=64;
        break;
      case 13:                             // Pattern Break
        pattern_break = v_true;                // We'll do the break later.
        break;
      case 14:
        switch(e2) {
          case 0:                          // Set filter.  I just ignore this
                                          // since it is a hardware option
            break;
          case 1:                          // Fineslide up
                                             // Recalculate frequency counter
            chan[i].period -= e3;
            rate = (WORD)(3546894L/chan[i].period);
            chan[i].pinc = ((LONG)rate*256)/internal_sample_rate;
            break;
          case 2:                          // Fineslide down
                                             // Recalculate frequncy counter
						chan[i].period += e3;
            rate = (WORD)(3546894L/chan[i].period);
            chan[i].pinc = ((LONG)rate*256)/internal_sample_rate;
            break;
          case 3:                          // Glissando on/off
                                           // If this is on, slide-to-note
                                           // functions should slide by
                                           // semitones rather than smooth
                                           // slides.  This is rarely used.
						mod_glissando = e3;
            break;
          case 4:                          // Vibrato waveform. This is rarely
                                           // used, so for now, the code is
                                           // locked in to use the default
																					 // waveform: 0  (a triggered sin
                                           // wave)
            break;
          case 5:                          // Set sample finetune value
            k = e3;
            if (k > 7) k -= 16;
            mod_data->finetune[chan[i].sample_number-1] =  k;
            break;
          case 6:                         // Loop Pattern
                                             // mod_loopcount is a global
                                             // used to keep track of the loop.
            if(mod_loopcount == -1) {
              if(!e3) mod_loopspot = mod_pattern - ((i)*4);
              else {
                if(!mod_loopspot) mod_loopspot =
                  mod_data->pattern_data[mod_data->ptable[mod_tablepos]];
                mod_loopcount = e3-1;
                loop = v_true;
              }
            }
            else if(e3){
              if(!mod_loopcount) mod_loopspot = NULL;
              else loop = v_true;
              mod_loopcount--;
            }
            break;
          case 7:                          // Termolo waveform.  (see case #4)
            break;
          case 8:                          // UNUSED
            break;
          case 9:                         // Retrigger sample
            chan[i].retrigger = e3;          // Set the retrigger signal used
                                             // in dotick().
            break;
          case 10:                        // Fineslide volume up
            chan[i].volume += e3;
            if(chan[i].volume > 64) chan[i].volume = 64;
						break;
          case 11:                        // Fineslide volume down
            chan[i].volume -= e3;
            if(chan[i].volume < 0) chan[i].volume = 0;
            break;
					case 12:                        // Cut Sample
            chan[i].cut = e3;                // Set cut signal for dotick()
            break;
          case 13:                        // Delay sample
            chan[i].data4 = e3;              // Set counter for dotick()
            chan[i].data3 = chan[i].volume;
            chan[i].volume = 0;              // Turn off volume
            break;
          case 14:                        // Pattern Delay
            mod_patterndelay = e3;
            break;
          case 15:                        // Invert Loop.  THis is too much
                                          // of a headache to worry about
                                          // right now. Sorry.
            break;
          default:                        // Shouldn't ever get here
            break;
        }
        break;
      case 15:                            // Set Speed.
                                             // There are two possible actions
                                             // with this command:  change
                                             // ticks per beat, or change
                                             // beats per minute.  Right
                                             // now, only the ticks per beat
                                             // have been implemented.
        j = e2*16+e3;
        if(j <= 32) {
          if(!j) j = 1;
          mod_ticksperdivision = j;
        } else {
          mod_bytespertick=(WORD)(((LONG)internal_sample_rate*60)/(24*j))<<vat_stereo;
          if (mod_bytespertick < dma_bufferlen)
            mod_bytespertick = dma_bufferlen;
        }
        break;
      default:                            // shouldn't happen.
				break;
    }
    mod_pattern += 4;                     // Advance to next channel
  }

	if(loop) {                              // Loop?  Jump back to placeholder!
    mod_pattern = mod_loopspot;
  }
  else if(pattern_break) {                // Pat. break?  Jump to next pattern!
    mod_tablepos++;
		if(mod_tablepos == mod_data->num_positions) mod_hardstop = v_true;
    else {
      mod_pattern = mod_data->pattern_data[mod_data->ptable[mod_tablepos]];
      mod_pstop = mod_pattern+1024;
    }
  }
  else if(position_jump) {                // Position jump?  Go to specified
                                          // Table.
    if(mod_tablepos == mod_data->num_positions) mod_on = v_false;
    else {
      mod_pattern = mod_data->pattern_data[mod_data->ptable[mod_tablepos]];
      mod_pstop = mod_pattern+1024;
    }
	}

	if(mod_printout) {                      // Some diagnostics
		printf("\n");
	}

}


/**************************************************************************
  VATBOOL ModCommand(VATCOMMAND c)

  DESCRIPTION:  Simple Interface for working With MOD playback

  INPUTS:
    c           VAT command (See sound.h)

**************************************************************************/
VATBOOL ModCommand (VATCOMMAND cmd)
{
  // check for a current mod
  if (mod_status == v_nonexist)
    return v_false;

	// process command
  switch (cmd) {
  case v_remove:
    if (mod_status != v_nonexist) {
      mod_on = v_false;          /* turn off */
      mod_data = NULL;
      mod_status = v_nonexist;
    }
    break;
  case v_play:
    if (mod_status == v_stopped ||
        mod_status == v_paused) {
      mod_on = v_true;           /* start or resume playing */
      mod_status = v_started;
    }
    break;
  case v_stop:
    if (mod_status == v_started ||
        mod_status == v_paused) {
      mod_on = v_false;          /* stop and reset */
      mod_reset = v_true;
      mod_status = v_stopped;
    }
    break;
  case v_pause:
    if (mod_status == v_started) {
      mod_on = v_false;          /* set inactive */
      mod_status = v_paused;
    }
    break;
  case v_rewind:
    if (mod_status == v_started ||
        mod_status == v_paused) {
      mod_reset = v_true;        /* reset without altering state */
    }
    break;
  default:
    return v_false;              /* invalid command */
  }

  // return confirmation
  return v_true;
}



/**************************************************************************
	int ModSetting (VATSETTING set, int value)

	DESCRIPTION:

**************************************************************************/
int ModSetting (VATSETTING set, int value)
{
  // no checks for current mod before processing, too many loopholes

  // process setting
  switch (set) {
  case v_volume:
    if (value == GET_SETTING)
      value = mod_volume;
    else {
      if (value < 0)             /* limit volume to 0 - 99 */
        value = 0;
      else if (value > 99)
        value = 99;
      mod_volume = value;
    }
    break;
  case v_repeat:
    if (mod_status == v_nonexist)  /* check for current mod */
      return -1;
    if (value == GET_SETTING)
      value = mod_data->repeatmusic;
    else
      mod_data->repeatmusic = value;  /* negative is unterminating */
    break;
  case v_rate:
    // no checks here, let them set it to what they like even though
    // if there's no current mod it'll be reset as soon as there is one
		if (value == GET_SETTING)
      value = mod_bytespertick;
    else {
// ECODE      if (value < dma_bufferlen) /* limit rate to dma_bufferlen - 9999 */
// ECODE				value = dma_bufferlen;
// ECODE			else if (value > 9999)
			if (value > 9999) value = 9999;
			mod_bytespertick = value;
    }
    break;
  case v_panpos:
    return -1;                   /* can't set pan position yet */
  case v_position:
    return -1;                   /* can't set position yet */
  default:
    return -1;                   /* invalid setting */
  }

  // return value as confirmation or notification of adjustment
  return value;
}


/**************************************************************************
	MOD   *LoadMod(CHAR *filename,CHAR *errstring)

  DESCRIPTION:  Loads a Module file (Noise,Sound, or Protracker)

  INPUTS:
    filename    pointer to character string containing the MOD filename
    errstring   pointer to a string for dumping error output

  RETURNS:
    pointer to a new MOD structure filled with MOD data

**************************************************************************/
MOD  *LoadMod(CHAR *modfile,CHAR *errstring)
{
  int i,j;
  DWORD ft;
  DWORD t1,t2;
  FILE *input;
  MOD  *m;
  CHAR signature[5];
  SHORT samples = 15;

  if (!modfile || !*modfile || !errstring) {
    if (errstring)
      sprintf (errstring, "Empty filename");
    return(NULL);
  }

  m = (MOD  *)VMALLOC(sizeof(MOD));         // Allocate the skeleton MOD struct
  if(!m) {
    sprintf(errstring,"Out of memory");
    return(NULL);
  }
                                          // clean up mod structure first
  for(i = 0; i < 32; i++) {
    m->sdata[i] = NULL;
    m->slength[i] =0;
  }
  m->chain = NULL;
  m->chainfunc = NULL;
  m->repeatmusic = 0;

  input = fopen(modfile,"rb");           // access the file
  if(!input) {
		VFREE(m);
		sprintf(errstring,"Cannot open file %s",modfile);
		return(NULL);
	}

	fseek(input,1080, SEEK_SET);            // Look for signatures so we
																					// can tell of this MOD has 15
																					// Or 31 samples.
	fread(signature,1,4,input);
	signature[4] = 0;
	if(!strcmp(signature,"M.K.")) samples = 31;
	else if(!strcmp(signature,"M!K!")) samples = 31;
	else if(!strcmp(signature,"FLT4")) samples = 31;
//  A blank string could be an S3M
//	else if(!strcmp(signature,"")) samples = 15;
	else {
		VFREE(m);
		fclose(input);
		sprintf(errstring,"Unknown Module type (%s)",signature);
		return(NULL);
	}

	rewind(input);                          // Go back to the start.

	fread(m->title,1,20,input);              // read the module title

	m->num_samples = 0;

	for(i = 0; i < samples; i++) {          // read the sample headers
		fread(m->sample_name[i],1,22,input);  // name
																					// length (convert words to bytes)
		t1=fgetc(input);
		t2=fgetc(input);
		m->slength[i] = (t1 * 256+ t2)*2;
		ft = fgetc(input)&0x0f;                // finetune
		if(ft>7) ft -=16;                     // Convert to a signed value
		m->finetune[i] = ft;

    m->volume[i] = fgetc(input);          // Sample volume
                                          // repeat offset (words -> bytes)
    m->offset[i] = (fgetc(input) * 256 + fgetc(input))*2;
                                          // repeat length (words -> bytes)
    m->repeat[i] = (fgetc(input) * 256 + fgetc(input))*2;
    if(m->repeat[i] == 2) m->repeat[i] = 0;

                                          // Sometimes the repeat length
                                          // and offset are not set properly,
                                          // so we have to do a little
                                          // patching here.
    if(m->offset[i] + m->repeat[i] > m->slength[i] ) {
      if(m->repeat[i] > m->slength[i]) {
        m->repeat[i] = m->slength[i];
        m->offset[i] = 0;
      }
      else {
        m->offset[i] -= (m->repeat[i] + m->offset[i] - m->slength[i]);
      }
    }

    if(m->slength[i]) m->num_samples++;      // Keep track of the number of real smaples
  }
  m->num_positions = fgetc(input);        // number of patterns to play
  fgetc(input);                           // unused byte
  fread(m->ptable,1,128,input);           // read pattern table

  if(samples == 31) {
    fread(m->sig,1,4,input);              // read module signature
    m->sig[4] = 0;
  }
  else strcpy(m->sig,"NONE");

  m->maxpattern = 0;

  for(i = 0; i < 127; i++) { // Find number of unique patterns
    if(m->ptable[i] > m->maxpattern) m->maxpattern = m->ptable[i];
  }

  for(i=0;i<128;i++) m->pattern_data[i]=NULL;  // Reset pattern buffer pointers

  for(i = 0; i <= m->maxpattern; i++) {   // read in 1024-byte patterns
    m->pattern_data[i] = (BYTE  *)VMALLOC(1024);

    if(!m->pattern_data[i]) {             // Did we get the memory?
                                          // If not, free what we have
                                          // and go home.
      for(j = 0; j < i; j++) VFREE(m->pattern_data[j]);
      sprintf(errstring,"Out of memory");
      VFREE(m);
      return(NULL);
    }
    for(j=0;j<64;j++){
      fread(m->pattern_data[i]+0+(j*16),1,sizeof(int),input);
      fread(m->pattern_data[i]+4+(j*16),1,sizeof(int),input);
      fread(m->pattern_data[i]+12+(j*16),1,sizeof(int),input);
      fread(m->pattern_data[i]+8+(j*16),1,sizeof(int),input);
    }
                                          // Read in the pattern
  }
                                          // Reset sample data pointers
  for(i = 0; i < 32; i++) m->sdata[i] = NULL;

  for(i = 0; i <samples; i++) {           // Read in the sample data
    m->sdata[i] = NULL;                   // Reset sample
    if(!m->slength[i]) continue;          // Continue if nothing to read

    m->sdata[i] = (SAMPLE *)VMALLOC(m->slength[i]+1);

    if(!m->sdata[i]) {                    // Did we get the memory?
                                          // If not, free what we have
                                          // and go home.
      for(j = 0; j <= m->maxpattern; j++) VFREE(m->pattern_data[j]);
      for(j = 0; j < i; j++) VFREE(m->sdata[j]);
      sprintf(errstring,"Out of memory");
      VFREE(m);
      return(NULL);
    }
                                          // Read in the sample
    fread(m->sdata[i],1,m->slength[i],input);

  }
  fclose(input);                          // All done!


  return(m);                              // Give the new Module back to
                                          // the caller.

}



/**************************************************************************
  void FreeMod(MOD *freeme)

  DESCRIPTION: Frees all the memory associated with a MOD file.

  INPUTS:
    freeme    pointer to MOD structure to free up

**************************************************************************/
void FreeMod(MOD *mod)
{
  SHORT i;

  if(!mod) return;

  if (mod == mod_data)
    ModCommand (v_remove);

  for(i = 0; i <32; i++) {           // Free the samples
    if(mod->sdata[i]) VFREE(mod->sdata[i]);
  }
  for(i = 0; i <128; i++) {         // Free the pattern data
    if(mod->pattern_data[i]) VFREE(mod->pattern_data[i]);
  }
  VFREE(mod);

}


/**************************************************************************
  CHANNEL  *ModChannels(void)

  DESCRIPTION:  Returns a pointer to the beginning of the MOD channels

**************************************************************************/
CHANNEL  *ModChannels(void)
{
  return chan;
}


/**************************************************************************
  void initmod(void)

  DESCRIPTION:  Gets all the variable ready for playing mods

**************************************************************************/
void initmod(void)
{
  SHORT i;

  mod_data = NULL;
  mod_on = v_false;
  mod_reset = v_false;
  mod_glissando = v_false;
  mod_finetune = 0;
  mod_patterndelay = 0;
  mod_volume = 50;
	mod_vibratocount = 0;
  mod_bytespertick = 220;
  mod_tablepos = 0;
  mod_pattern = NULL;
  mod_pstop = NULL;
  mod_loopspot = NULL;
  mod_loopcount = -1;
  mod_ticksperdivision = 6;
  mod_currentbyte = 0;
  mod_currenttick = 0;
  mod_divoffset = 0;
  for(i=0; i < 4; i++) mod_channelselect[i] = 1;
  mod_status = v_nonexist;
}

/*************************************************************************
  VATCOMMAND ModStatus(void)

  DESCRIPTION:  Checks the status of the currently playing loaded Mod.

*************************************************************************/
VATCOMMAND ModStatus(void)
{
  return mod_status;
}


/**************************************************************************
	void PlayMod (MOD *mod)

	DESCRIPTION:

**************************************************************************/
void PlayMod (MOD *mod)
{
  /* check VAT status */
  if (internal_status != v_started)
    return;

  if (mod_status != v_nonexist)
    ModCommand (v_remove);
  mod_data = mod;
  if (mod) {
    mod_reset = v_true;
    mod_status = v_stopped;
    ModCommand (v_play);
  } else
    mod_status = v_nonexist;
}


/**************************************************************************
	VATBOOL ModChain (MOD *mod)

	DESCRIPTION:

**************************************************************************/
VATBOOL ModChain (MOD *mod)
{
  if (mod_status == v_nonexist)
    return v_false;

  mod_data->chain = mod;
  return v_true;
}


/**************************************************************************
	VATBOOL ModChainFunc (void (*func)(void))

	DESCRIPTION:

**************************************************************************/
VATBOOL ModChainFunc (void (*func)(void))
{
  if (mod_status == v_nonexist)
    return v_false;

  mod_data->chainfunc = func;
  return v_true;
}


/**************************************************************************
	LONG ModChannelMask (LONG mask)

	DESCRIPTION:

**************************************************************************/
LONG ModChannelMask (LONG mask)
{
  int i;

  if (mask == GET_SETTING) {
    mask = 0;
    for (i=0; i<4; i++)
      if (!mod_channelselect[i])
        mask |= (1<<i);
  } else if (mask < 0 || mask >= (1<<4))
    return -1;
  else
    for (i=0; i<4; i++)
      mod_channelselect[i] = ((mask & (1<<i)) == 0);
  return mask;
}

