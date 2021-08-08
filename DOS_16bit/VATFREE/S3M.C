/**************************************************************************
												VARMINT'S AUDIO TOOLS 0.71

	S3M.C

		This file contains source code far all S3M related functions in VAT.


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
#include <dos.h>
#include "vat.h"

#define DOSYNC2    if(sync_on && !(syncbytecount++ % bytes_per_synccheck) && inportb(0x3da)&0x08) vsyncclock = 1000
#define DOSYNC1    if(sync_on && inportb(0x3da)&0x08) vsyncclock = 1000

// ------------------------------------ internal functions

void sdodiv(void);
void sdotick(void);
void inits3m(void);


// ------------------------------------ external varaibles

extern SHORT dma_bufferlen;
extern SHORT *mix_buffer;
extern SHORT vsin[];
extern SHORT vtable[256][64];

// ------------------------------------ S3m Variables

                                       // Default periods for calculating
                                       // Notes.
LONG s3m_period[12] = {109568L,103424L,97536L,92160L,86784L,81920L,
											77312L,72960L,68864L, 65024L,61440L,58048L};

                                       // This is for volume settings in effect
                                       // number Q retrig+volslide
LONG s3m_retvol[16] = {0,-1,-2,-4,-8,-16,91,92,0,1,2,4,8,16,93,94};

LONG channels;
LONG s3m_division;
LONG s3m_loopcount=-1;
LONG s3m_vibratocount=0;
LONG s3m_reset=FALSE;
SHORT s3m_bytespertick=220;
LONG s3m_divspot;
SHORT s3m_volume=8;
SHORT s3m_on=FALSE;
LONG s3m_order;
LONG s3m_patterndelay=0;
LONG s3m_divbytes=160;
BYTE VFAR *s3m_pattern,*s3m_pstop,*s3m_loopspot=NULL;
S3M VFAR *s3m_data=NULL;
LONG s3m_currentbyte,s3m_currenttick,s3m_ticksperdivision=6;
                                       // Allows on/off control of s3mchannels
BYTE s3m_channelselect[32] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
														 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
static CHANNEL VFAR chan[32];

/*************************************************************************
void s3mplayer(void)

DESCRIPTION: Routine for playing s3m files.  This is designed to be called
             from a timer interrupt.  To use these values must be set:

             s3m_data must point to a filled s3m structure
             s3m_reset must be TRUE.
             s3m_on must be TRUE.

             The interrupt should pick up from here.
*************************************************************************/
void s3mplayer(void)
{
	static SHORT i,j,vol;
	LONG lastbyte;
	DWORD dummy1=0,position=0,dummy=0,*pos,end,pinc;
	SAMPLE *data;

	DOSYNC1;

	pos = (DWORD *)(((BYTE *)&position)+1);


	if(s3m_reset) {
		channels=s3m_data->channelnum;       // Reset the S3M?
		for(i = 0; i < channels; i++ ) {     // Reset all channels
			DOSYNC1;
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
			chan[i].s3m_fine=FALSE;
			chan[i].fineperiod=0;
		}
																				 // reset the global s3m variables
		s3m_divbytes=s3m_data->channelnum * 5;
		s3m_pattern=s3m_data->pattern_data[s3m_data->order[0]];
		s3m_pstop=s3m_pattern+s3m_divbytes*64;

		s3m_bytespertick=((s3m_data->inittempo-250L)*220L)/-125L;
		s3m_bytespertick=(WORD)(((LONG)sample_rate*s3m_bytespertick)/11000L);

		DOSYNC1;

		s3m_ticksperdivision=s3m_data->initspeed;
		s3m_currentbyte=0;
		s3m_currenttick=0;
		s3m_reset=FALSE;
		s3m_order=0;
		s3m_division=0;
	}
																				 //Mix the buffer if the number of
																				 //left is bigger than bufferlen
	if(s3m_currentbyte > dma_bufferlen) {
		for(i=0;i<channels;i++){             //loop through ALL channels...
			DOSYNC1;
			if(chan[i].volume && *chan[i].pos < chan[i].end) {
				vol = (chan[i].volume * s3m_volume)/100;
				data = chan[i].sdata;
				position = chan[i].position;
				end = chan[i].end*256;
				pinc = chan[i].pinc;

				for(j=0;j<dma_bufferlen;j++){
					DOSYNC2;
					*(mix_buffer+j) += (*(data + (ARRAYTYPE)*pos)*vol)>>6;
					position+= pinc;
					if(position>=end) {
						if(chan[i].sflag&0x1) {      //If this inst loops loop it...

							*pos -= (chan[i].rlength-chan[i].offset);
							*chan[i].pos = *pos;
							chan[i].counter=0;
							end = chan[i].end=chan[i].rlength;
							end <<= 8;
						}
						else break;
					}
				}
				chan[i].position = position;
			}
		}
		s3m_currentbyte -= dma_bufferlen;
	}
																				 //if we have less than bufferlen to
																				 //mix then we mix the rest and call
                                         //our tick routine, if it as a division
                                         //we also call our division routine
  else {
		for(i=0;i<channels;i++){             //mix ALL channels
			DOSYNC1;
			if(chan[i].volume && *chan[i].pos < chan[i].end) {
				vol = (chan[i].volume * s3m_volume)/100;
				data = chan[i].sdata;
				position = chan[i].position;
				end = chan[i].end*256;
				pinc = chan[i].pinc;

				for(j=0;j<s3m_currentbyte;j++){
					DOSYNC2;
					*(mix_buffer+j) += (*(data + (ARRAYTYPE)*pos)*vol)>>6;
					position+=pinc;
					if(position>=end) {
						if(chan[i].sflag&0x1) {

							*pos -= (chan[i].rlength-chan[i].offset);
							*chan[i].pos  = *pos;
							chan[i].counter=0;
							end = chan[i].end=chan[i].rlength;
							end <<= 8;
            }
            else break;
          }
				}
				chan[i].position = position;
      }
		}

		lastbyte=s3m_currentbyte;            //if we are at a division call it
		if(s3m_currenttick >= s3m_ticksperdivision*(s3m_patterndelay+1)) {
			s3m_patterndelay=0;
			sdodiv();
			s3m_division++;
			if(s3m_pattern == s3m_pstop) {
				s3m_order++;
				s3m_division=0;
																			// End of the s3m?
				if(s3m_order == s3m_data->orders) {
					s3m_on=FALSE;
					s3m_reset=TRUE;
					if(s3m_data->repeatmusic) { // repeat?
						if(s3m_data->repeatmusic > 0) s3m_data->repeatmusic--;
						s3m_on = TRUE;
					}
																		 // Check for a chain function
					if(s3m_data->chainfunc) s3m_data->chainfunc(s3m_data);

																		 // Check for a chain
					if(s3m_data->chain) {
						s3m_data = s3m_data->chain;
						s3m_on = TRUE;
					}

				}
				else {
					s3m_pattern=s3m_data->pattern_data[s3m_data->order[s3m_order]];
					s3m_pstop=s3m_pattern+s3m_divbytes*64;
				}
			}
			s3m_currenttick=0;
		}
		s3m_currentbyte=s3m_bytespertick;    //reset current byte
		s3m_currenttick++;
		sdotick();                           //do the tick stuff
		for(i=0;i<channels;i++){             //mix the rest of ALL channels up to
																				 //bufferlen
			DOSYNC1;
			if(chan[i].volume && *chan[i].pos < chan[i].end) {
				vol = (chan[i].volume * s3m_volume)/100;
				data = chan[i].sdata;
				position = chan[i].position;
				end = chan[i].end*256;
				pinc = chan[i].pinc;

				for(j=lastbyte;j<dma_bufferlen;j++){
					DOSYNC2;
					*(mix_buffer+j) += (*(data + (ARRAYTYPE)*pos)*vol)>>6;
					position+=pinc;
					if(position>=end) {
						if(chan[i].sflag&0x1) {

							*pos -= (chan[i].rlength-chan[i].offset);
							*chan[i].pos = *pos;
							chan[i].counter=0;
							end = chan[i].end = chan[i].rlength;
							end <<= 8;
						}
						else break;
					}
				}
				chan[i].position = position;
			}
		}
		s3m_currentbyte-=(dma_bufferlen-lastbyte);
	}
	DOSYNC1;
}

/********************************************************************

	void sdodiv(void)

	Description: Handles all of the division commands at each div of
	of the s3m.

********************************************************************/
void sdodiv(void)
{                                      //local variables
	SHORT k;
	LONG row,pattern_break=FALSE,position_jump=FALSE,loop=FALSE;
	static BYTE instrument,note,octave,volume,command,info;
  BYTE infox,infoy;
	DWORD rate;

	for(k=0;k<channels;k++){               //check all of the channels
		DOSYNC1;
		chan[k].cut=-1;
    note=*(s3m_pattern)&0x0f;            //pull note out of pattern
    octave=(*(s3m_pattern)&0xf0)>>4;     //pull octave out of pattern
    instrument=*(s3m_pattern+1);         //get the instrument too
		volume=*(s3m_pattern+2);             //and the volume
		command=*(s3m_pattern+3);            //plus the effect
		chan[k].effect=command;
    info=*(s3m_pattern+4);               //effects info...
		infox=(info&0xf0)>>4;
    infoy=info&0x0f;
		chan[k].x=info;
		if(volume!=255) {
			if(volume > 63) volume = 63;         // clip values of 64.
			chan[k].volume=volume;
		}

    if(*(s3m_pattern)==254){             //254 means that this channel is turned
                                         //off.
			chan[k].sdata=NULL;
			chan[k].position=0;
			chan[k].counter=0;
			chan[k].end=0;
      note=255;
    }
    if(*s3m_pattern==255) note=255;
    if(instrument) {                     //if there is an instrument assign
                                         //variables specific to the instrument
				chan[k].sample_number=instrument-1;
				chan[k].sdata=s3m_data->sdata[instrument-1];
        chan[k].sflag=s3m_data->sflag[instrument-1];
        chan[k].position=0;
				chan[k].counter=0;
        chan[k].offset=s3m_data->loopbegin[instrument-1];
				chan[k].rlength=s3m_data->loopend[instrument-1];
				chan[k].end=s3m_data->slength[instrument-1];
				if(chan[k].sflag & 0x01) chan[k].end = chan[k].rlength;
        if(volume==255)
          chan[k].volume=s3m_data->volume[instrument-1];
    }
    if((note!=255)&&(command!=7)){       //if a note is involved compute the
                                         //new period of the note.
			chan[k].period=
				(LONG)(10L*((13381L*s3m_period[note])/(1<<octave))/
				s3m_data->c2spd[chan[k].sample_number]);
			rate=(DWORD)(14317056L/chan[k].period);
			chan[k].pinc=((DWORD)rate*256L)/sample_rate;
			chan[k].position=0;
			chan[k].counter=0;
		}
    switch(command) {
			case 1:                              //Set Speed
				s3m_ticksperdivision=info;
				break;
			case 2:                              //Jump to order
				s3m_order=info;
				position_jump=TRUE;
				break;
			case 3:                              //Break pattern to row
				row=info;
				pattern_break=TRUE;
				break;
			case 4:                               // Volume slide up down
																						// and fine and extra
																						// fine all in one!!!
				chan[k].finevol = FALSE;
				if(infox==15){
					if((infoy>0)&&(infoy<15)) {
						chan[k].fineadjust=-infoy;
						chan[k].vslide=0;
						chan[k].finevol=TRUE;
						break;
					}
				}
				else if(infoy==15) {
					if((infox>0)&&(infox<15)) {
						chan[k].fineadjust=infox;
						chan[k].vslide=0;
						chan[k].finevol=TRUE;
						break;
					}
				}
				else if(info){
					if(infox==0)  chan[k].vslide =  -infoy;
					else          chan[k].vslide =   infox;
					chan[k].finevol=FALSE;
				}

				if(chan[k].finevol) {
					chan[k].volume+=chan[k].fineadjust;
					if(chan[k].volume<0)chan[k].volume=0;
					else if(chan[k].volume>63)chan[k].volume=63;
					chan[k].finevol = FALSE;
				}
				break;
			case 5:                              //slide note down fine and extra fine too.
				if(infox==15) {
					chan[k].period+=infoy*3;
					chan[k].fineperiod=infoy*3;
					rate=(DWORD)(14317056L/chan[k].period);
					chan[k].pinc=((DWORD)rate*256L)/sample_rate;
					chan[k].porta=0;
					chan[k].s3m_fine=TRUE;
					break;
				}
				if(infox==14) {
					chan[k].period+=infoy;
					chan[k].fineperiod=infoy;
					rate=(DWORD)(14317056L/chan[k].period);
					chan[k].pinc=((DWORD)rate*256L)/sample_rate;
					chan[k].porta=0;
					chan[k].s3m_fine=TRUE;
					break;
				}
				if(info) {
					chan[k].porta=info*3;
					chan[k].s3m_fine=FALSE;
				}
				else if(chan[k].s3m_fine){
					chan[k].period+=chan[k].fineperiod;
					rate=(DWORD)(14317056L/chan[k].period);
					chan[k].pinc=((DWORD)rate*256L)/sample_rate;
					chan[k].porta=0;
				}
				break;
			case 6:                              //slide note up fine and extra fine too.
				if(infox==15) {
					chan[k].period-=infoy*3;
					chan[k].fineperiod=infoy*3;
					rate=(DWORD)(14317056L/chan[k].period);
					chan[k].pinc=((DWORD)rate*256L)/sample_rate;
					chan[k].porta=0;
					chan[k].s3m_fine=TRUE;
					break;
				}
				if(infox==14) {
					chan[k].period-=infoy;
					chan[k].fineperiod=infoy;
					rate=(DWORD)(14317056L/chan[k].period);
					chan[k].pinc=((DWORD)rate*256L)/sample_rate;
					chan[k].porta=0;
					chan[k].s3m_fine=TRUE;
					break;
				}
				if(info) {
					chan[k].porta=info*3;
					chan[k].s3m_fine=FALSE;
				}
				else if(chan[k].s3m_fine){
					chan[k].period-=chan[k].fineperiod;
					rate=(DWORD)(14317056L/chan[k].period);
					chan[k].pinc=((DWORD)rate*256L)/sample_rate;
					chan[k].porta=0;
				}
				break;
			case 7:                              //Tone port. still uses floating point
																					 //I still WILL change it... :-)

				if(info)chan[k].porta=info*3;
				if(note!=255) chan[k].period2=
					(LONG)(10L*((13381L*s3m_period[note])/(1<<octave))/
					 s3m_data->c2spd[chan[k].sample_number]);
				break;
			case 8:                              //Vibrato
				if(infox || infoy)s3m_vibratocount=0;
				if(infox)chan[k].vibperiod=infox;
				if(infoy)chan[k].vibdepth=(DWORD)(((LONG)infoy*595L*chan[k].period)/120000L);
				break;
			case 11:                             //Vibrato+volumeslide
			case 12:                             //Toneport+volumeslide
				if(infox==0)chan[k].vslide=-infoy;
				else chan[k].vslide=infox;
				break;
			case 15:                             //Set sample offset
				chan[k].position=65536L*info;
																					 // Handle looping
				if(chan[k].sflag & 0x01 && chan[k].rlength) {
					while(*chan[k].pos > chan[k].rlength)
						*chan[k].pos -= (chan[k].rlength-chan[k].offset);
				}
				break;
			case 17:                             //Retrig+volumeslide
				if(infoy) chan[k].retrigger=infoy;
				chan[k].vslide=s3m_retvol[infox];
				break;
			case 19:                             //Special
				switch(infox){
					case 8:                            //channel pan not used by us..
						break;
					case 11:                           //pattern loop
						if(s3m_loopcount==-1) {
							if(!infoy) {
								s3m_loopspot=s3m_pattern-(k*5);
								s3m_divspot=s3m_division-1;
							}
							else {
								if(!s3m_loopspot) {
									s3m_loopspot =
										s3m_data->pattern_data[s3m_data->order[s3m_order]];
									s3m_divspot = -1;
								}
								s3m_loopcount = infoy-1;
								loop=TRUE;
							}
						}
						else if(infoy) {
							if(!s3m_loopcount)s3m_loopspot=NULL;

							else loop=TRUE;
							s3m_loopcount--;
						}
						break;
					case 12:                           //notecut in x frames
						chan[k].cut=infoy;
						break;
					case 13:                           //notedelay for x frames
						chan[k].data4=infoy;
						chan[k].data3=chan[k].volume;
						chan[k].volume=0;
						break;
					case 14:                           //patterndelay
						s3m_patterndelay=infoy;
						break;
					default:
						break;
				}
				break;
			case 20:                             //Set Tempo

				s3m_bytespertick = ((LONG)sample_rate * 60L)/(24L * info);
				if(s3m_bytespertick < dma_bufferlen) s3m_bytespertick = dma_bufferlen;

				// OLD CODE: This stuff was set up by Bryan
				//s3m_bytespertick=((info-250L)*220L)/-125L;
				//s3m_bytespertick=(WORD)(((LONG)sample_rate*s3m_bytespertick)/11000L);
				break;
			case 21:                             //Fine vibrato
				if(infox || infoy)s3m_vibratocount=0;
				if(infox)chan[k].vibperiod=infox;
				if(infoy)chan[k].vibdepth=(DWORD)(((LONG)infoy*595*(chan[k].period/4))/120000L);
				break;
			default:
				break;
		}
		s3m_pattern+=5;
	}

	while(k < channels) {                  // Make sure we get to next div
		s3m_pattern+=5;
		k++;
	}
	if(loop){                              //loop if active
		s3m_pattern=s3m_loopspot;
		s3m_division=s3m_divspot;
	}
	if(pattern_break){                     //break the pattern if instructed
		s3m_order++;
		if(s3m_order==s3m_data->orders){
			s3m_on=FALSE;
			s3m_reset=TRUE;
		}
		else {
			s3m_pattern=s3m_data->pattern_data[s3m_data->order[s3m_order]];
			s3m_pattern+=s3m_divbytes*row;
			s3m_division=row-1;
			s3m_pstop=s3m_pattern+s3m_divbytes*64;
		}
	}
	if(position_jump){                     //jump position if needed
		if(s3m_order>=s3m_data->orders){
			s3m_on=FALSE;
			s3m_reset=TRUE;
		}
		else {
			s3m_pattern=s3m_data->pattern_data[s3m_data->order[s3m_order]];
			s3m_pstop=s3m_pattern+s3m_divbytes*64;
			s3m_division=-1;
		}
	}
}

/********************************************************************

	WORD scalcvibrato(WORD inc,WORD period,WORD amplitude)

	Description: Calculates a new inc value based on s3m vibrato
	parameters.. See calcvibrato function for input definitions

  Returns a new inc value for period.

********************************************************************/
WORD scalcvibrato(WORD inc,WORD period,WORD amplitude)
{
  LONG newinc,theta;

  newinc = (LONG)inc * 256L;          // convert to fixed point

                                          // claculate sin wave parameter
  theta = (((LONG)period * s3m_vibratocount * 100) / 64) % 100;
                                          // grab precalclated sin
  newinc = newinc + (LONG)((LONG)vsin[(WORD)theta] * amplitude);

	return(WORD)(newinc / 256L);            // Send back as a regular SHORT
}

/********************************************************************

 void sdotick(void)

 Description:  Handles ongoing s3m commands at each "tick"

********************************************************************/
void sdotick(void)
{
	SHORT i;
	DWORD rate,period;
	s3m_vibratocount++;

	DOSYNC1;

  for(i=0;i<channels;i++){               //look at all channels
    switch(chan[i].effect) {
			case 4:                            //volume slide
				chan[i].volume+=chan[i].vslide;
				if(chan[i].volume<0)chan[i].volume=0;
				else if(chan[i].volume>63)chan[i].volume=63;
        break;
      case 5:                            //Slide note down
        chan[i].period+=chan[i].porta;
        rate=(DWORD)14317056L/(chan[i].period);
        chan[i].pinc=((DWORD)rate*256L)/sample_rate;
        break;
      case 6:                            //Slide note up
        chan[i].period-=chan[i].porta;
        rate=(DWORD)14317056L/chan[i].period;
        chan[i].pinc=((DWORD)rate*256L)/sample_rate;
        break;
      case 7:                            //tone portamento
        if(chan[i].period<chan[i].period2){
          chan[i].period+=chan[i].porta;
          if(chan[i].period>chan[i].period2)chan[i].period=chan[i].period2;
        }
        else if(chan[i].period>chan[i].period2){
          chan[i].period-=chan[i].porta;
          if(chan[i].period<chan[i].period2)chan[i].period=chan[i].period2;
        }
        if(chan[i].period<1)chan[i].period=1;
        rate=(DWORD)14317056L/chan[i].period;
				chan[i].pinc=((LONG)rate*256L)/sample_rate;
        break;
      case 8:                            //Vibrato
        if(!chan[i].period)chan[i].period=1;
        period=scalcvibrato(chan[i].period,chan[i].vibperiod,chan[i].vibdepth);
        rate=(DWORD)(14317056L/period);
				chan[i].pinc=((LONG)rate*256L)/sample_rate;
        break;
      case 11:                           //vibrato+volumeslide
				chan[i].volume+=chan[i].vslide;
        if(chan[i].volume<0)chan[i].volume=0;
				else if(chan[i].volume>63)chan[i].volume=63;
        if(!chan[i].period)chan[i].period=1;
				period=scalcvibrato(chan[i].period,chan[i].vibperiod,chan[i].vibdepth);
        rate=(DWORD)(14317056L/period);
				chan[i].pinc=((LONG)rate*256L)/sample_rate;
        break;
      case 12:                           //port+volumeslide
				chan[i].volume+=chan[i].vslide;
        if(chan[i].volume<0)chan[i].volume=0;
				else if(chan[i].volume>63)chan[i].volume=63;
        if(chan[i].period<chan[i].period2){
          chan[i].period+=chan[i].porta;
          if(chan[i].period>chan[i].period2)chan[i].period=chan[i].period2;
        }
        else if(chan[i].period>chan[i].period2){
          chan[i].period-=chan[i].porta;
          if(chan[i].period<chan[i].period2)chan[i].period=chan[i].period2;
        }
        if(chan[i].period<1)chan[i].period=1;
				rate=(DWORD)(14317056L/chan[i].period);
				chan[i].pinc=((LONG)rate*256L)/sample_rate;
        break;
			case 17:                           //retrig + volumeslide

				if(chan[i].retrigger && !(s3m_currenttick % chan[i].retrigger)) {
          chan[i].position=0;
          chan[i].counter=0;
				}

				if(chan[i].vslide > 90){         // special vol slide?
					switch(chan[i].vslide){
						case 91:
							chan[i].volume=(chan[i].volume*2)/3;
							break;
						case 92:
							chan[i].volume=chan[i].volume/2;
							break;
						case 93:
							chan[i].volume=(chan[i].volume*3)/2;
							break;
						case 94:
							chan[i].volume=chan[i].volume*2;
							break;
						default:
							break;
					}
				}
				else chan[i].volume+=chan[i].vslide;

				if(chan[i].volume<0)chan[i].volume=0;
				else if(chan[i].volume>63)chan[i].volume=63;

        break;
      case 19:                           //special
        switch((chan[i].x&0xf0)>>4) {
          case 12:                       //notecut
						if(s3m_currenttick>=chan[i].cut)chan[i].volume=0;
            break;
          case 13:                       //notedelay
            if(!chan[i].data4) {
              chan[i].position=0;
              chan[i].counter=0;
							chan[i].volume=chan[i].data3;
            }
            chan[i].data4--;
            break;
          default:
            break;
        }
			case 21:                           //fine vibrato
        if(!chan[i].period)chan[i].period=1;
        period=scalcvibrato(chan[i].period,chan[i].vibperiod,chan[i].vibdepth);
        rate=(DWORD)(14317056L/period);
				chan[i].pinc=((LONG)rate*256L)/sample_rate;
        break;
      default:
        break;
		}
		chan[i].volume *= s3m_channelselect[i];  // THis allows the user to mask
																						 // channels
  }
}


/**************************************************************************
	S3M VFAR *LoadS3M(CHAR *filename,CHAR *errstring)

	DESCRIPTION:  Loads a S3M Module file

	INPUTS:
		filename    pointer to character string containing the MOD filename
		errstring   pointer to a string for dumping error output

	RETURNS:
		pointer to a new S3M structure filled with S3M data

**************************************************************************/
S3M VFAR *LoadS3M(CHAR *filename,CHAR *errstring)
{
	SHORT i=0,j=0,temp=0,temp2=0,vbyte;
	LONG k=0,ordnum=0,paras[256];

																			 // The Paras are used to figure out
                                       // the addresses of the data.
                                       // read in a para and divide by 16 to
																			 // get offset into file.

	LONG instpoint[256];                  // the pointers are pointers to the
	LONG pattpoint[256];                  // data
	FILE *input;
	S3M *s;
	BYTE ftype,control;

	for(i = 0; i < 256; i++) {
		paras[i] = 0;
		instpoint[i] = 0;
		pattpoint[i] = 0;
	}


	s = (S3M *)VMALLOC(sizeof(S3M));      //make room for the music
	if (!s) {
		sprintf(errstring,"Out Of Memory");
		return(NULL);
	}
	s->chain = NULL;
	s->chainfunc = NULL;
	s->repeatmusic = 0;
																			 // initialize the s3m struct
	for(i = 0; i < 100; i++) {
		s->sample_name[i][0] = 0;
		s->slength[i] = 0;
		s->sflag[i] = 0;
		s->loopbegin[i] = 0;
		s->loopend[i] = 0;
		s->c2spd[i] = 0;
		s->volume[i] = 0;
		s->sdata[i] = NULL;
	}
	for(i = 0; i < 256; i++) s->pattern_data[i] = NULL;



	input = fopen(filename,"rb");        //open file
	if (!input) {
		VFREE(s);
		sprintf(errstring,"Cannot open file %s",filename);
		return(NULL);
	}

	fseek(input,29,SEEK_SET);            //Check the type of file by lookin in
																			 //the right spot.
	ftype=fgetc(input);
	if (ftype!=16) {
		VFREE(s);
		sprintf(errstring,"Not a S3M file");
		printf("%d",ftype);
		fclose(input);
		return(NULL);
	}

  rewind(input);

  fread(s->title,1,28,input);          //Get the title of the song.
  fseek(input,4,SEEK_CUR);
  ordnum=fgetc(input);                 //Get number of orders in the song
  fgetc(input);
  s->insnum=fgetc(input);              //get number of instruments
  fgetc(input);
  s->patnum=fgetc(input);              //get number of patterns
  fgetc(input);
  s->flags=fgetc(input);               //Special flags for file that I do not
                                       //use.
  fseek(input,9,SEEK_CUR);
  s->globalvol=fgetc(input);           // get global volume for song, I am not
                                       // using this I replaced this with the
                                       // vat volume control.
  s->initspeed=fgetc(input);           // get initial number of ticks
  s->inittempo=fgetc(input);           // get initial tempo fo song.
  s->mastervol=fgetc(input);           // get master volume, not used either
  fseek(input,12,SEEK_CUR);
	s->channelnum=0;                     // get number of channels in the song
  for(i=0;i<32;i++){
    temp=fgetc(input);
		if (temp!=255) s->channelnum++;
  }
  for(i=0;i<ordnum;i++){               // only use orders that are used by the
                                       // song and not turned off (255)
    temp=fgetc(input);
    if (temp!=255) s->order[i]=temp;
    else break;
  }
  s->orders=i;                         // reset order number for real number
                                       // of orders.
  fseek(input,0x60+ordnum,SEEK_SET);
	for(i=0;i<s->insnum;i++){            // read the instrument info offsets
    fread(&instpoint[i],2,1,input);
  }
  for(i=0;i<s->patnum;i++){            // read the pattern info offsets
    fread(&pattpoint[i],2,1,input);
  }
	temp=0;
	for(i=0;i<s->insnum;i++){            // start reading instrument info
		fseek(input,instpoint[i]*16,SEEK_SET); // move to offset.
		temp2=fgetc(input);
		if(temp2==1) {                     // if there is an instrument there
      temp++;                          // read its info in.
      fseek(input,12,SEEK_CUR);
      fread(&paras[i],3,1,input);      //read in para pointer to offset of
                                       // raw data for instrument
      fread(&s->slength[i],4,1,input);   // length?
      fread(&s->loopbegin[i],4,1,input); // loop?
      fread(&s->loopend[i],4,1,input);
      s->volume[i]=fgetc(input);         // volume of instrument (default)
      fseek(input,2,SEEK_CUR);
      fread(&s->sflag[i],1,1,input);     // flags mainly used for looping
			fread(&s->c2spd[i],4,1,input);     // tuning?
      s->c2spd[i]*=64;                   // multiply by 64 for fixed poin math
      fseek(input,12,SEEK_CUR);
      fread(s->sample_name[i],1,28,input); // what is the name of the inst.
    }
  }
  for(i=0;i<s->insnum;i++){            // read in the raw data for each inst.
    if(paras[i]){
			fseek(input,paras[i]/16,SEEK_SET); // div para by 16 in order to get
																				 // real offset into file. :-)

																				 // It seems that some samples can
																				 // have an incorrect slength.  This
																				 // bit of code is a sanity check
																				 // to make sure the smaple does not
																				 // cross over to other data.

																				 // First check against sample data
			for(j = 0; j < s->insnum; j++ ) {
				if(paras[j] > paras[i]  &&
					 paras[j]/16 < paras[i]/16 + s->slength[i]) {
					s->slength[i] = paras[j]/16 - paras[i]/16;
				}
			}
																				 // next check against pattern data
			for(j = 0; j < s->patnum; j++ ) {
				if(pattpoint[j]*16 > paras[i]/16 &&
					 pattpoint[j]*16 < paras[i]/16 + s->slength[i]) {
					s->slength[i] = pattpoint[j]*16 - paras[i]/16;
				}
			}

			s->sdata[i]=NULL;                  // make sure theres room.
			s->sdata[i]=(SAMPLE *)VMALLOC(s->slength[i]+1);
			if(!s->sdata[i]){
				FreeS3M(s);
				sprintf(errstring,"Out of Memory");
				fclose(input);
				return(NULL);
			}
			fread(s->sdata[i],1,s->slength[i],input);
			for(k=0;k<s->slength[i];k++){     // read it in and make it signed.
				*(s->sdata[i]+(ARRAYTYPE)k)-=128;
			}
		}
	}
	s->insnum=temp;                      // update to real number of insts.
	temp=0;
	vbyte = s->channelnum * 5;           // Calculate number of bytes
																			 // per division.  This is necessary
																			 // to keep the memory usage efficient.
	for(i=0;i<s->patnum;i++){            // start reading pattern info
		fseek(input,pattpoint[i]*16,SEEK_SET);
    fread(&temp2,2,1,input);
    if(temp2>66) {                     // if pattern not all 0's read it in
      temp++;
			s->pattern_data[i]=(BYTE VFAR *)VMALLOC(vbyte*64); // see if theres room
			if(!s->pattern_data[i]){
      	FreeS3M(s);
				sprintf(errstring,"Out of Memory");
				fclose(input);
				return(NULL);
      }
			for(j=0;j<vbyte*64;j+=5) {       // initialize the default values for
                                       // patterns
        s->pattern_data[i][j]=255;
        s->pattern_data[i][j+1]=0;
        s->pattern_data[i][j+2]=255;
        s->pattern_data[i][j+3]=0;
        s->pattern_data[i][j+4]=0;
      }
      for(j=0;j<64;j++){               // read in all division data
        control=fgetc(input);
         while(control) {              // while there is data go for it.
                                       // explanation here. control&31 is the
                                       // channel number things are going in.

          if(control&32) {             // this reads what note and instrument
                                       // respectively for this division/
						s->pattern_data[i][(j*vbyte)+((control&31)*5)]=fgetc(input);
						s->pattern_data[i][(j*vbyte)+((control&31)*5)+1]=fgetc(input);
          }
          if(control&64) {             // This reads the volume for this
                                       // channel in this division
						s->pattern_data[i][(j*vbyte)+((control&31)*5)+2]=fgetc(input);
          }
          else {                       // else set the volume to something
                                       // to let the loop know to use the
                                       // default instrument value
						s->pattern_data[i][(j*vbyte)+((control&31)*5)+2]=255;
          }
          if(control&128) {            // This reads the effect and its info
                                       // for this channel on this div.
						s->pattern_data[i][(j*vbyte)+((control&31)*5)+3]=fgetc(input);
						s->pattern_data[i][(j*vbyte)+((control&31)*5)+4]=fgetc(input);
          }
          control=fgetc(input);
        }
      }
    }
    else {
      s->pattern_data[i]=NULL;         // if there is no data assign a null
                                       // pointer
    }
  }
  s->patnum=temp;                      //This assigns the real number of patts
	fclose(input);
	return(s);
}                                      // that's all folks!!

/**************************************************************************
	void S3MCommand(VATCOMMAND c)

	DESCRIPTION:  Simple Interface for working With S3M playback

	INPUTS:
		c           VAT command (See vat.h)

**************************************************************************/
void S3MCommand(VATCOMMAND c)
{
  switch(c){
    case v_play:
      s3m_reset = TRUE;
      s3m_on = TRUE;
      break;
    case v_stop:
      s3m_on = FALSE;
      s3m_reset = TRUE;
      break;
    case v_pause:
      s3m_on = FALSE;
      break;
    case v_resume:
      s3m_on = TRUE;
      break;
    case v_rewind:
      s3m_reset = TRUE;
      break;
    default:
      break;
  }
}

/**************************************************************************
	CHANNEL VFAR *S3MChannels(void)

	DESCRIPTION:  Returns a pointer to the beginning of the S3M channels

**************************************************************************/
CHANNEL VFAR *S3MChannels(void)
{
	return chan;
}


/**************************************************************************
	void inits3m(void)

	DESCRIPTION:  Sets up variables so we can start playing s3m's

**************************************************************************/
void inits3m(void)
{
	SHORT i;

	s3m_loopcount=-1;
	s3m_vibratocount=0;
	s3m_reset=TRUE;
	s3m_volume=25;
	s3m_on=FALSE;
	s3m_patterndelay=0;
	s3m_data=NULL;
	for(i = 0; i < 32; i++)  s3m_channelselect[i] = 1;
}

/**************************************************************************
	void FreeS3M(S3M *freeme)

	DESCRIPTION: Frees all the memory associated with a MOD file.

	INPUTS:
		freeme    pointer to S3M structure to free up

**************************************************************************/
void FreeS3M(S3M *freeme)
{
	SHORT i;

	if(!freeme) return;

	for(i = 0; i <100; i++) {           // Free the samples
		if(freeme->sdata[i]) VFREE(freeme->sdata[i]);
	}
	for(i = 0; i <256; i++) {         // Free the pattern data
		if(freeme->pattern_data[i]) VFREE(freeme->pattern_data[i]);
	}
	VFREE(freeme);

}
