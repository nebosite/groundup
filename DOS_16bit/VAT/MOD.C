/**************************************************************************
												VARMINT'S AUDIO TOOLS 0.71

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
#include <alloc.h>
#include <DOS.h>
#include <string.h>
#include "vat.h"

#define DOSYNC2    if(sync_on && !(syncbytecount++ % bytes_per_synccheck) && inportb(0x3da)&0x08) vsyncclock = 1000
#define DOSYNC1    if(sync_on && inportb(0x3da)&0x08) vsyncclock = 1000

//-------------------------------- Internal Functions

void dotick(void);
void dodiv(void);
WORD upsemitone(WORD inc, WORD steps);
WORD downsemitone(WORD inc, WORD steps);
void initmod(void);


//-------------------------------- External varaibles

extern SHORT dma_bufferlen,*mix_buffer,vsin[];
extern SHORT vtable[256][64];


//-------------------------------- MOD varaibles

MOD VFAR     *mod_data = NULL;
SHORT       mod_on = FALSE,mod_reset = FALSE,mod_tablepos=0;
BYTE VFAR    *mod_pattern,*mod_pstop,*mod_loopspot=NULL;
SHORT       mod_loopcount = -1;
SHORT       mod_bytespertick = 220,mod_ticksperdivision = 6;
SHORT       mod_currentbyte = 0,mod_currenttick = 0;
SHORT       mod_divoffset =0;
SHORT       mod_glissando = FALSE;
SHORT       mod_finetune = 0;
SHORT       mod_patterndelay = 0;
SHORT       mod_volume = 31;
WORD        mod_vibratocount = 0;
BYTE        mod_channelselect[4] = {1,1,1,1};
static CHANNEL VFAR chan[4];


/*************************************************************************
void modplayer(void)

DESCRIPTION: Routine for playing mod files.  This is designed to be called
             from a timer interrupt.  To use these values must be set:

             mod_data must point to a filled mod structure
             mod_reset must be TRUE.
             mod_on must be TRUE.

             The interrupt should pick up from here.
*************************************************************************/
void modplayer(void)
{
	static SHORT i,j,vol;
	SHORT lastbyte;
	DWORD dumm1=0,position=0,dummy2=0,*pos,end,pinc;
	SAMPLE *data;



	pos = (DWORD *)(((BYTE *)&position)+1);


	if(mod_reset) {                // Reset the MOD?
		for(i = 0; i < 4; i++ ) {    // Reset all four channels
			chan[i].bufferdummy1 = 0;
			chan[i].bufferdummy2 = 0;
			chan[i].sdata = NULL;
			chan[i].offset = 0;
			chan[i].rlength = 0;
			chan[i].end = 0;
			chan[i].volume = 0;
			chan[i].sample_number = 0;
			chan[i].position= 0;
			chan[i].pos = (DWORD *)(((BYTE *)&chan[i].position)+1);
			chan[i].counter = 0;
			chan[i].pinc = 0;
			chan[i].effect = 0;
			chan[i].x = 0;
			chan[i].y = 0;
		}
																		 // Reset global mod variables
		mod_pattern=mod_data->pattern_data[mod_data->ptable[0]];
		mod_pstop = mod_pattern+1024;
		mod_tablepos=0;
		mod_bytespertick = (WORD)(((LONG)sample_rate *220)/11000L);
		mod_ticksperdivision = 6;
		mod_currentbyte = 0;
		mod_currenttick = 0;
		mod_divoffset =0;
		mod_reset = FALSE;           // Reset the reset switch
	}

																		 // **************************************
																		 // This little section mixes all the mod
																		 // channels if the number of bytes left
																		 // to go until the next tick is bigger
																		 // than the dma_buffer length.
																		 // **************************************
	if(mod_currentbyte > dma_bufferlen) {
		for(i = 0; i < 4; i++) {     // Loop through the four channels

																		 // If the volume is zero or if the sample
                                     // has ended, then there is no need to mix
																		 // anything.

			if(chan[i].volume && *chan[i].pos <= chan[i].end) {
				vol = (chan[i].volume * mod_volume)/100;
				data = chan[i].sdata;
				position = chan[i].position;
				end = chan[i].end*256L;
				pinc = chan[i].pinc;
																		// Loop along the length of the mixing buffer
				for(j = 0; j < dma_bufferlen; j++) {
					DOSYNC2;
																 // Add this byte to the mixing buffer
					*(mix_buffer+j) += (*(data + (ARRAYTYPE)*pos)*vol)>>6;
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
							end *=256L;
            }

            else break;          // else Jump out of mixing loop
          }
				}
				chan[i].position = position;
      }
    }
                                     // Keep track of where we are.
    mod_currentbyte -= dma_bufferlen;
	}
                                     // **************************************
                                     // This little section mixes all the mod
                                     // channels if the number of bytes left
                                     // to go until the next tick is *smaller*
                                     // than the dma_buffer length.
																		 //
                                     // It first mixes what is left, then it
                                     // decrements the tick and calls out
                                     // to the module handling routines.
                                     // Once that is done, it mixes the
                                     // rest of the DMA buffer.
                                     //
                                     // The two mixing routines are extacly the
                                     // same as the one above except the first
                                     // one loops over the first part of the
                                     // mixing buffer, and the second mixes
																		 // over the rest.
                                     // **************************************

  else {
                                     // Mix the first part of the buffer
		for(i = 0; i < 4; i++) {
			if(chan[i].volume && *chan[i].pos <= chan[i].end) {
				vol = (chan[i].volume * mod_volume)/100;
				data = chan[i].sdata;
				position = chan[i].position;
				end = chan[i].end*256L;
				pinc = chan[i].pinc;

				for(j = 0; j < mod_currentbyte; j++) {
					DOSYNC2;
					*(mix_buffer+j) += (*(data + (ARRAYTYPE)*pos)*vol)>>6;
					position += pinc;
																 // Are we at the end of the sample?
					if(position >= end) {
                                 // Repeating?  Move the position back.
						if(chan[i].rlength > 1) {
							*pos -= chan[i].rlength;
							*chan[i].pos = *pos;
							chan[i].counter = 0;
							end = chan[i].end = chan[i].offset+chan[i].rlength;
							end *= 256L;
            }
            else break;          // else Jump out of mixing loop
          }
				}
				chan[i].position = position;
      }
		}

		lastbyte = mod_currentbyte;  // Keep track of where we are inthe buffer

                                     // Ready for next division?
    if(mod_currenttick >= mod_ticksperdivision * (mod_patterndelay+1) ) {
      mod_patterndelay = 0;      // Reset pattern delay
			dodiv();                   // Handle the division commands.
																 // Are we at the end of the pattern?
      if(mod_pattern == mod_pstop) {
        mod_tablepos++;          // Next table!

                                     // Done with tables?  Done with MOD.
        if(mod_tablepos == mod_data->num_positions) {
					mod_on = FALSE;
          mod_reset = TRUE;

          if(mod_data->repeatmusic) { // repeat?
            if(mod_data->repeatmusic > 0) mod_data->repeatmusic--;
            mod_on = TRUE;
          }
                                     // Check for a chain function
          if(mod_data->chainfunc) mod_data->chainfunc(mod_data);

                                     // Check for a chain
					if(mod_data->chain) {
            mod_data = mod_data->chain;
            mod_on = TRUE;
          }
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

    mod_currenttick++;           // Do our tick stuff.
		dotick();
  
																		 // Mix the rest of the buffer
    for(i = 0; i < 4; i++) {
			if(chan[i].volume && *chan[i].pos <= chan[i].end) {
				vol = (chan[i].volume * mod_volume)/100;
				data = chan[i].sdata;
				position = chan[i].position;
				end = chan[i].end*256L;
				pinc = chan[i].pinc;

				for(j = lastbyte; j < dma_bufferlen; j++) {
					DOSYNC2;
					*(mix_buffer+j) += (*(data + (ARRAYTYPE)*pos)*vol)>>6;
					position += pinc;
																		 // Are we at the end of the sample?
					if(position >= end) {
                                  // Repeating?  Move the position back.
            if(chan[i].rlength > 1) {
							*pos -= chan[i].rlength;
							*chan[i].pos = *pos;
							chan[i].counter = 0;
							end = chan[i].end = chan[i].offset+chan[i].rlength;
							end *= 256L;
						}
						else break;
          }
				}
				chan[i].position = position;
			}
		}
																		 // Update our position
		mod_currentbyte -= (dma_bufferlen-lastbyte);
	}

	DOSYNC1;
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
WORD calcvibrato(WORD inc,WORD period,WORD amplitude)
{
	LONG newinc,theta;

	newinc = (LONG)inc * 256L;              // convert to fixed point

																					// claculate sin wave parameter
	theta = (((LONG)period * mod_vibratocount * 100) / 64) % 100;
																					// grab precalclated sin
	newinc = newinc + (LONG)((LONG)vsin[(ARRAYTYPE)theta] * amplitude);

	return(WORD)(newinc / 256L);            // Send back as a regular SHORT
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

	mod_vibratocount++;

	for(i = 0; i < 4; i++) {                // Loop through all four channels
		DOSYNC1;
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
				chan[i].pinc = ((LONG)rate * 256)/sample_rate;
				break;
			case 2:                              // slide down
				if(!mod_glissando) chan[i].period += chan[i].porta;
																						 // glissando = chromatic slide
				else chan[i].period = downsemitone(chan[i].period,chan[i].porta);
																						 // Don't go too low
				if(chan[i].period > 2000) chan[i].period = 2000;
																						 // Set frequency counters
				rate =(WORD)( 3546894L/chan[i].period);
				chan[i].pinc = ((LONG)rate * 256)/sample_rate;
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
				rate = (WORD)(3546894L/chan[i].period);
				chan[i].pinc = ((LONG)rate * 256)/sample_rate;
				break;
			case 4:                              // vibrato
				period = calcvibrato(chan[i].period,
														 chan[i].vibperiod,chan[i].vibdepth);

																						 // Set frequency counters
				rate = (WORD)(3546894L/period);
				chan[i].pinc = ((DWORD)rate * 256)/(DWORD)sample_rate;

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
				chan[i].pinc = ((LONG)rate * 256)/sample_rate;

				chan[i].volume += chan[i].vslide;
				if(chan[i].volume < 0) chan[i].volume = 0;
				if(chan[i].volume > 64) chan[i].volume = 64;
				break;
			case 6:                              // Vibrato + volume slide
				period = calcvibrato(chan[i].period,chan[i].vibperiod,chan[i].vibdepth);

				rate = (WORD)(3546894L/period);
				chan[i].pinc = ((LONG)rate * 256)/sample_rate;

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
WORD upsemitone(WORD inc, WORD steps)
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
WORD downsemitone(WORD inc, WORD steps)
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
	SHORT i,j,k;                              // Local variables we'll need
	SHORT samp,pattern_break = FALSE,position_jump = FALSE,loop = FALSE;
	WORD period,rate;
	BYTE e1,e2,e3;

	for(i = 0; i < 4; i++) {                // Loop through all four channels
		DOSYNC1;
		chan[i].retrigger = 0;                // Reset retrigger and cut signals
		chan[i].cut  = -1;
																					// Grab information for this channel
		samp = (*(mod_pattern)&0xF0) + ((*(mod_pattern+2) & 0xf0)>>4);
		period = (*(mod_pattern)&0x0F)*256 + *(mod_pattern+1);
		e1 = (*(mod_pattern+2)) & 0x0F;       // e1-e3 are the command nibbles
		e2 = (*(mod_pattern+3)  & 0xF0) >> 4;
		e3 = (*(mod_pattern+3)) & 0x0F;

		if(samp) {                 						// set a new sample?

			chan[i].sample_number = samp;       // Some MOD commmands need this
			chan[i].volume = mod_data->volume[samp-1];
		}

		if(e1 != 3 && period) {
																					// sample 0 = repeat sample
			if(!samp) {
				if(!chan[i].sample_number) chan[i].sample_number = 1;
				samp = chan[i].sample_number;
			}

			chan[i].sdata = mod_data->sdata[samp-1]; // set a pointer to the data
			chan[i].position = 0;               // Retrigger the sample
			chan[i].counter = 0;
																					// store sample characteristics
			chan[i].offset = mod_data->offset[samp-1];
			chan[i].rlength = mod_data->repeat[samp-1];
																					// Keep track of end so we know
																					// When to stop.
			chan[i].end = mod_data->slength[samp-1];
			if(chan[i].rlength) chan[i].end = chan[i].offset + chan[i].rlength;
																					// Calculate adjusted period
			chan[i].period = period + mod_data->finetune[chan[i].sample_number-1]
															+ mod_finetune;
																					// Set frequency counter
			rate =(WORD)(3546894L/period);
			chan[i].pinc = ((LONG)rate*256)/sample_rate;

		}
																					// Sometimes song start off
																					// without specifying any period,
																					// so I am picking  a default here
		if(!chan[i].period) chan[i].period = 428;

		chan[i].effect = e1;                    // Keep for reference in dotick()
		chan[i].x = e2;
		chan[i].y = e3;

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
				if(e3) chan[i].vibdepth = (WORD)(((LONG)e3 * 595 * chan[i].period)/120000L);
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
				position_jump = TRUE;
				break;
			case 12:                             // Set Volume
				chan[i].volume = e2*16+e3;
				break;
			case 13:                             // Pattern Break
				pattern_break = TRUE;                // We'll do the break later.
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
						chan[i].pinc = ((LONG)rate*256)/sample_rate;
						break;
					case 2:                          // Fineslide down
																						 // Recalculate frequncy counter
						chan[i].period += e3;
						rate = (WORD)(3546894L/chan[i].period);
						chan[i].pinc = ((LONG)rate*256)/sample_rate;
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
								loop = TRUE;
							}
						}
						else if(e3){
							if(!mod_loopcount) mod_loopspot = NULL;
							else loop = TRUE;
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
		if(mod_tablepos == mod_data->num_positions) mod_on = FALSE;
		else {
			mod_pattern = mod_data->pattern_data[mod_data->ptable[mod_tablepos]];
			mod_pstop = mod_pattern+1024;
		}
	}
	else if(position_jump) {                // Position jump?  Go to specified
																					// Table.
		if(mod_tablepos == mod_data->num_positions) mod_on = FALSE;
		else {
			mod_pattern = mod_data->pattern_data[mod_data->ptable[mod_tablepos]];
			mod_pstop = mod_pattern+1024;
		}
	}
}



/**************************************************************************
	void ModCommand(VATCOMMAND c)

	DESCRIPTION:  Simple Interface for working With MOD playback

	INPUTS:
		c           VAT command (See sound.h)

**************************************************************************/
void ModCommand(VATCOMMAND c)
{
	switch(c){
		case v_play:
			mod_reset = TRUE;
			mod_on = TRUE;
			break;
		case v_stop:
			mod_on = FALSE;
			mod_reset = TRUE;
			break;
		case v_pause:
			mod_on = FALSE;
			break;
		case v_resume:
			mod_on = TRUE;
			break;
		case v_rewind:
			mod_reset = TRUE;
			break;
		default:
			break;
	}
}



/**************************************************************************
	MOD VFAR  *LoadMod(CHAR *filename,CHAR *errstring)

	DESCRIPTION:  Loads a Module file (Noise,Sound, or Protracker)

	INPUTS:
		filename    pointer to character string containing the MOD filename
		errstring   pointer to a string for dumping error output

	RETURNS:
		pointer to a new MOD structure filled with MOD data

**************************************************************************/
MOD VFAR *LoadMod(CHAR *filename,CHAR *errstring)
{
	SHORT i,j,ft;
	FILE *input;
	MOD VFAR *m;
	CHAR signature[5];
	SHORT samples = 15;

	m = (MOD VFAR *)VMALLOC(sizeof(MOD));         // Allocate the skeleton MOD struct
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

	input = fopen(filename,"rb");           // access the file
	if(!input) {
		VFREE(m);
		sprintf(errstring,"Cannot open file %s",filename);
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

	rewind(input);                          // Go back to the start.

	fread(m->title,1,20,input);              // read the module title

	m->num_samples = 0;

	for(i = 0; i < samples; i++) {          // read the sample headers
		fread(m->sample_name[i],1,22,input);  // name
																					// length (convert words to bytes)
		m->slength[i] = (fgetc(input) * 256+ fgetc(input))*2;
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

		if(m->slength) m->num_samples++;      // Keep track of the number of real smaples
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
		m->pattern_data[i] = (BYTE VFAR *)VMALLOC(1024);

		if(!m->pattern_data[i]) {             // Did we get the memory?
																					// If not, free what we have
																					// and go home.
			for(j = 0; j < i; j++) VFREE(m->pattern_data[j]);
			sprintf(errstring,"Out of memory");
			VFREE(m);
			return(NULL);
		}
		fread(m->pattern_data[i],1,1024,input);  // Read in the pattern
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
void FreeMod(MOD *freeme)
{
	SHORT i;

	if(!freeme) return;

	for(i = 0; i <32; i++) {           // Free the samples
		if(freeme->sdata[i]) VFREE(freeme->sdata[i]);
	}
	for(i = 0; i <128; i++) {         // Free the pattern data
		if(freeme->pattern_data[i]) VFREE(freeme->pattern_data[i]);
	}
	VFREE(freeme);

}


/**************************************************************************
	CHANNEL VFAR *ModChannels(void)

  DESCRIPTION:  Returns a pointer to the beginning of the MOD channels

**************************************************************************/
CHANNEL VFAR *ModChannels(void)
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
	mod_on = FALSE;
	mod_reset = FALSE;
	mod_glissando = FALSE;
	mod_finetune = 0;
	mod_patterndelay = 0;
	mod_volume = 25;
	mod_vibratocount = 0;
	for(i=0; i < 4; i++) mod_channelselect[i] = 1;
}

