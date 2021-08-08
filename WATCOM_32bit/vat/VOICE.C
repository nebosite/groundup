/**************************************************************************
												VARMINT'S AUDIO TOOLS 1.1

	WAV.C

		This file contains source code far all VOICE related functions in VAT.


	Authors: Eric Jorgensen, December 1997

	Copyright 1995 - Ground Up

**************************************************************************/

#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <dos.h>
#include <string.h>
#include "vat.h"
#include "internal.h"

#define MAXNOTETOKENS 64
#define CHROMATIC_RATIO 1.059463094
//#define debugf nullf

//---------------------------- Internal Structures
	// PATCHNOTE Structure: The patch note structure is used To play a
										//  	single note from a Gravis-type patch.
typedef struct patchnote {
	PATCH   			*sourcepatch;          // pointer to the source patch
	PATCHSAMPLE   *sourcesample;         // pointer to the source patchsample
	BYTE		available;                   // Tracks available objects

	DWORD   dummy;
	DWORD   position;                    // data position used internally by sbint
	DWORD   dummy2;
	DWORD   *pos;                        // pointer to current byte position
	DWORD   rootpinc;                    // rate counter
	DWORD   pinc;                        // rate counter

	BYTE		mastervolume;		  					 // Main volume control for the note
	BYTE    volume;                      // volume of the sample
	BYTE    pan;                         // panning value of the sample
	BYTE    buffer;

	LONG    envelope;                    // Current envelope #
	LONG		volumetarget;                // Amplitude we are heading to
	LONG		volumeinc;                  // delta change each vat tick
	LONG		longvolume;

	LONG 		tick;                        // Clock counter for vibrato and tremolo

																			 // vibrato parameters
	LONG		vsweep;                      // tick offset of sweep end point
	LONG		vrate;                       // ticks/cycle
	LONG		vdepth;                      // Ratio = x*.00784

	LONG		trate;                       // tremolo parameters
	LONG		tdepth;

	VATSTATUS status;                    // indicates the play status
	LONG    handle;                      // unique id to perform ops with
	struct patchnote *next,*prev;

} PATCHNOTE;

//---------------------------- Internal functions

void freenote(PATCHNOTE *pnote);
PATCHNOTE  *newpatchnote(void);
PATCHNOTE  *find_note(DWORD handle);
void makedefaultpatches(void);

//---------------------------- External variables

extern VATSTATUS internal_status;
extern volatile SHORT *mix_buffer;
extern SHORT wav_vol_table[64][256];
extern SHORT lpan[64][60],rpan[64][60];
extern DWORD vat_stereo;
extern DWORD internal_sample_rate;
extern SHORT vsin[];

//---------------------------- Internal variables

SHORT      notes_in_queue = 0;

PATCHNOTE	*notelist = NULL;
PATCHNOTE	 notetoken[MAXNOTETOKENS];
LONG       patch_id = 1,sample_id=1,note_handle=1;
LONG			 pitchtable[128];
LONG			debugnum = 0;
PATCH			defaultinstrument;
PATCH			defaultdrum;
PATCHSAMPLE defaultinstrumentsample;
PATCHSAMPLE	defaultdrumsample;
SAMPLE		defaultsampledata[5000];

int sqroot[256] = { 0,1,1,1,2,2,2,2,2,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,5,5,
	5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
	7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
	9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,11,
	11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,12,12,
	12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,13,13,
	13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
	13,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,
	14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
	15,15,15,15,15,15,15,15,15,15,15,15,15};

/**************************************************************************
	void debugf(CHAR *string,...)

	DESCRIPTION:  For yuks

**************************************************************************/
/*void nullf(CHAR *string,...)
{
	va_list ap;

//  _disable();

	va_start(ap, string);                  // sort out variable argument list
//	printf(string,ap);
	va_end(ap);                            // clean up
//  _enable();
}
*/

/********************************************************************

	LONG calcmodulation(WORD theta,WORD amplitude)

	Description: Calculates vibrato and tremolo changes

	Returns a new inc value.

********************************************************************/
LONG calcmodulation(LONG theta,LONG amplitude)
{
																					// claculate sin wave parameter
//	theta = (((LONG)period * s3m_vibratocount * 100) / 64) % 100;
																					// grab precalclated sin
	return ((LONG)vsin[theta] * amplitude)/256L;
}

/**************************************************************************
	dovolume()

	DESCRIPTION: I created this to free up clutter in the note player,
							 plus possible address a few weird compiler bugs.

**************************************************************************/
int dovolume(PATCHNOTE *pnote)
{
	LONG vinc,vol,targ,env,tick,vdepth,tdepth;
	PATCHSAMPLE *psamp;

	psamp = pnote->sourcesample;
	vol = pnote->longvolume;
	targ = pnote->volumetarget;
	env = pnote->envelope;
	vinc = pnote->volumeinc;
	tick = pnote->tick++;

																	// Handle envelop ramping
	if(vol > targ) {
		vol -= vinc;
		if(vol < targ) vol = targ;
	}
	else {
		vol += vinc;
		if(vol > targ) vol = targ;
	}

	if(vol == targ) {
		env++;
		if(env == 3 && pnote->sourcesample->mode_sustain)
			env = 2;

		if(env > 5 || (env > 2 && pnote->sourcesample->mode_clamped_release )) {
			return v_false;
		}
		else {
			targ = pnote->sourcesample->envelope_offset[env];
			vinc = psamp->envelope_rate[env] /
				(internal_sample_rate/(dma_bufferlen * (vat_stereo+1)));
		}
	}
																// Do vibrato calculations
	if(pnote->vrate) {
		if(pnote->vsweep && tick < pnote->vsweep) vdepth = (pnote->vdepth * tick)/pnote->vsweep;
		else vdepth = pnote->vdepth;

		vdepth = (vdepth * pnote->rootpinc * 4)/10000;
		pnote->pinc = pnote->rootpinc + calcmodulation(((tick*100)/pnote->vrate)%100,vdepth);
	}

	if(pnote->trate) {
		tdepth = (sqroot[pnote->tdepth] * vol * 2)/1000;
		vol += calcmodulation(((tick*100)/pnote->trate)%100,tdepth);
	}

	if(vol > 65535) vol = 65535;
	if(vol < 0) vol = 0;

	pnote->envelope = env;
	pnote->longvolume = vol;
	pnote->volumetarget = targ;
	pnote->volumeinc = vinc;
	pnote->volume = ((vol * pnote->mastervolume)/128) >> 10;

	return v_true;
}

/**************************************************************************
	void noteplayer(void)

	DESCRIPTION:  Work function called from interrupt to play patches as notes

**************************************************************************/
void noteplayer(void)
{
	PATCHNOTE  *pnote,*phold;
	PATCHSAMPLE *psamp;
	SAMPLE *data;
	static DWORD dumm1=0,position=0,dumm2=0;
	static DWORD pinc,length;
	DWORD *pos;
	LONG volume;
	BYTE rvolume,lvolume;
	LONG pan;
	SHORT *vtr,*vtl,*vt;
	LONG j;
	LONG sval;
	SHORT *mbuf;


																	 // ***********************************
																	 // *                                 *
																	 // *         Mix in notes            *
																	 // *                                 *
																	 // ***********************************
	pos = (DWORD *)(((BYTE *)&position)+2);
	pnote = notelist;

	while(pnote) {
		if(!dovolume(pnote)) {
			freenote(pnote);
			pnote = pnote->next;
			continue;
		}
		psamp = pnote->sourcesample;
		volume = pnote->volume;
		pinc = pnote->pinc;
		pan = pnote->pan;


		data = psamp->data;               // Set up speed varaibles
		position = pnote->position;
		length = psamp->size * 0x10000;
		if(psamp->mode_looping) {
			length = psamp->loop_end * 0x10000 + ((psamp->end_fraction * 0x10000L)>>4);
		}
		rvolume = (BYTE)rpan[volume][pan];
		lvolume = (BYTE)lpan[volume][pan];
		vtr = wav_vol_table[rvolume]+ 128;
		vtl = wav_vol_table[lvolume]+ 128;

		mbuf = mix_buffer;

		for(j = 0; j < dma_bufferlen; j+=(vat_stereo+1)) {
			sval = *(data + (ARRAYTYPE)(*pos));
														// Add this byte to the mixing buffer
			*mbuf += vtl[sval];
			mbuf++;
			*(mix_buffer+j+vat_stereo) += vtr[sval];
			mbuf += vat_stereo;
																// Here is where the frequency magic
																// happens.  I use fixed point arithmatic
																// to increment the sample position pointer
																// at different rates.
			position += pinc;

																// Are we at the end of the sample?
			if(position >= length) {
				if(!psamp->mode_looping) {     // Do we not repeat this sample?
					freenote(pnote);
					break;
				}
				else {                    // Decrememnt the repeat counter
					position -= length;
					position += psamp->loop_start * 0x10000  +
											((psamp->end_fraction * 0x10000L)>>4);
				}
			}


		}

		pnote->position = position;
		pnote = pnote->next;
	}
}


/**************************************************************************
	void freenote(PATCHNOTE *pnote)

	DESCRIPTION:  Takes the note out of the note list and marks it
								available for future use.

	INPUTS:
		pnote    pointer to the note to free

**************************************************************************/
void freenote(PATCHNOTE *pnote)
{
	PATCHNOTE *noteprev,*notenext;

	if(!pnote || pnote->available) return;
																			 // Take it out of the note list
	noteprev = pnote->prev;
	notenext = pnote->next;

	if(!noteprev) {
		notelist = notenext;
		if(notelist) notelist->prev = NULL;
	}
	else {
		noteprev->next = notenext;
		if(notenext) notenext->prev = noteprev;
	}

	pnote->available = v_true;           // Mark as available for future use

}


/**************************************************************************
	PATCHNOTE  *newpatchnote(void)

	DESCRIPTION:  Finds and unused patchnote object an initializes it

								Note: PATCHNOTE Tokens are pre-allocated rather than dynamically
											allocated because many thousands of notes may
											be played in a single execution.  Allocating and
											re-allocating all this tiny pieces of memory may cause
                      problems.

  RETURNS:
		Pointer to the new PATCHNOTE structure


**************************************************************************/
PATCHNOTE  *newpatchnote(void)
{
	PATCHNOTE	*pnote;
	int i;
																	 // Find an available note token
	for(i =0 ; i< MAXNOTETOKENS && !notetoken[i].available; i++);
	if(i == MAXNOTETOKENS) return(NULL);

	pnote = &notetoken[i];
																	 // Initialize varaibles
	pnote->sourcepatch = NULL;
	pnote->sourcesample = NULL;
	pnote->available = v_false;
	pnote->dummy = 0;
	pnote->position = 0;
	pnote->dummy2 = 0;
																			 // Set up for 16 bit fixed decimal
	pnote->pos = (DWORD *)(((BYTE *)&(pnote->position))+ 2);
	pnote->pinc = 0x10000;

	pnote->mastervolume = 43;            // 43 represents standard volume
	pnote->volume = 43;                  // 43 represents standard volume
	pnote->pan = 30;                     // 30 is middle panning value

	pnote->tick = 0;
	pnote->status = v_stopped;
	pnote->handle = note_handle++;
	pnote->next = NULL;
	pnote->prev = NULL;
	return(pnote);
}



/**************************************************************************
	LONG PlayNote (LONG midinote, PATCH *p)

	DESCRIPTION:  Sets up a voice in the queue for immediate rendering.

**************************************************************************/
LONG PlayNote (LONG midinote, PATCH *p)
{
	PATCHNOTE *pnote = NULL;
	int i;
	LONG playfreq;
//	double diff,lowdiff;
	int diff,lowdiff;
	DWORD fratio,pf,rf;
//	double fratio;
	PATCHSAMPLE *psamp,*closestpsamp;

//	if (internal_status != v_started)    // check VAT status
//		return 0;

	if (!p)                          		// check Voice validity
		return 0;

																			 // In case this operation takes a
																			 // long time, we wat to disable
																			 // interrupts
	vdisable();

	pnote = newpatchnote();
	if(pnote) {
		//debugf("P");
		pnote->sourcepatch = p;
																			// Figure out the frequency that
																			// we are playing.

																			// Midi note 128 signals percussion.
																			// Percussion samples are played
																			// at their root frequency
		if(midinote == 128) {
			playfreq = p->samplelist->root_frequency;
			pnote->sourcesample = p->samplelist;
		}


																			// For regular midi notes, we need
																			// to find the sample that best
																			// matches the target frequency.
		else {
			playfreq = pitchtable[midinote];
			psamp = p->samplelist;
			lowdiff = 10000000;
			closestpsamp = NULL;

			while(psamp) {                  // Go down the list
				//debugf("S*");

																			// Check for a direct match
				if (playfreq > psamp->low_frequency &&
						playfreq < psamp->high_frequency) {
					closestpsamp = psamp;
					lowdiff=0;
				}
																			// Otherwise, just get the closest one
				else {
//					diff = fabs(log((double)playfreq/psamp->root_frequency));
					diff = abs(playfreq - psamp->root_frequency);
					if(diff < lowdiff) {
						lowdiff = diff;
						closestpsamp = psamp;
					}
				}

				psamp = psamp->next;
			}

			pnote->sourcesample = closestpsamp;
		}
																				// Calculate the playback rate
//		fratio = (double)playfreq/pnote->sourcesample->root_frequency;
//		fratio *= (double)(pnote->sourcesample->sample_rate)/internal_sample_rate;
//		pnote->rootpinc = pnote->pinc = 0x10000 * fratio;


		pf = (playfreq+5)/10;
		rf = (pnote->sourcesample->root_frequency+5)/10;

		fratio = (pf * 0x1000)/rf;
		fratio = fratio *
						((pnote->sourcesample->sample_rate*0x100)/internal_sample_rate);


		pnote->rootpinc = pnote->pinc = fratio/0x10;

																				// Set up envelope calculations
		pnote->longvolume = 0;
		pnote->envelope = 0;
		pnote->volumetarget = pnote->sourcesample->envelope_offset[0];
		pnote->volumeinc =
			pnote->sourcesample->envelope_rate[0] /
			(internal_sample_rate/(dma_bufferlen * (vat_stereo+1)));
																				// Convert end of vibrato sweep
																				// into a tick number.

																				// Ticks il sweep starts
		pnote->vsweep = ( pnote->sourcesample->vibrato_sweep  *
			(internal_sample_rate/(dma_bufferlen * (vat_stereo+1))))/45;
																				// Ticks for one vibrato cycle
		pnote->vrate = ( (pnote->sourcesample->vibrato_rate+1)  *
			(internal_sample_rate/(dma_bufferlen * (vat_stereo+1))))/250;
																				// Vibrato depth. 255 = one octave
		pnote->vdepth = pnote->sourcesample->vibrato_depth;

		pnote->trate = ( (pnote->sourcesample->tremolo_rate+1)  *
			(internal_sample_rate/(dma_bufferlen * (vat_stereo+1))))/250;
		pnote->tdepth = pnote->sourcesample->tremolo_depth;
		pnote->tick = 0;

																				// Add note to play list
		pnote->next = notelist;
		pnote->prev = NULL;
		pnote->status = v_started;
		if(notelist) notelist->prev = pnote;
		notelist = pnote;
	}

	venable();
	if(pnote) return pnote->handle;
	else return 0;
}

 /**************************************************************************\
 |*                                                                        *|
 |* GC - 10/6/96, v1.1                                                     *|
 |*                                                                        *|
 |*  Change the play status or attributes of the Wave in the queue         *|
 |*  which corresponds to the given handle.  When changing an attribute,   *|
 |*  limits value to valid ranges for the attribute in question.  Ignores  *|
 |*  attribute changes which the play type of the Wave does not support.   *|
 |*                                                                        *|
 |*  IN:                                                                   *|
 |*    LONG handle                                                         *|
 |*      a unique id referring to the queued Wave to perform the given     *|
 |*      operations on                                                     *|
 |*    VATCOMMAND cmd                                                      *|
 |*      the operation to perform on the queued Wave                       *|
 |*    int value                                                           *|
 |*      for attribute changing commands, the value to change the          *|
 |*      attribute in question to                                          *|
 |*                                                                        *|
 |*  OUT:                                                                  *|
 |*    VATBOOL success                                                     *|
 |*      v_true if successful (the handle is valid)                        *|
 |*      v_false if unsuccessful (the handle is invalid)                   *|
 |*                                                                        *|
 |*  Replaces:                                                             *|
 |*    AlterSoundEffect (compatible args)                                  *|
 |*   * updates status                                                     *|
 |*   * checks and adjusts values                                          *|
 |*                                                                        *|
 \**************************************************************************/

VATBOOL NoteCommand (LONG handle, VATCOMMAND cmd)
{
	PATCHNOTE *pnote;
																	// Grab the note
	pnote = find_note(handle);
	if(!pnote) return v_false;

																	// process command
	switch (cmd) {
																	// On stop, force the note into release mode
	case v_stop:
		if(pnote->envelope < 3) {
			pnote->envelope = 3;
			pnote->volumetarget =
				pnote->sourcesample->envelope_offset[pnote->envelope];
			pnote->volumeinc =
				pnote->sourcesample->envelope_rate[pnote->envelope] /
				(internal_sample_rate/(dma_bufferlen * (vat_stereo+1)));
		}
		break;
	case v_remove:
		freenote (pnote);        		// remove from play queue
		break;
	default:
		return v_false;              	// invalid command
	}

																	// return confirmation
  return v_true;
}


/**************************************************************************
	int VoiceSetting (LONG handle, VATSETTING set, int value)

	DESCRIPTION:

**************************************************************************/
int NoteSetting (LONG handle, VATSETTING set, int value)
{
	PATCHNOTE *pnote;

	// find note based on handle
	pnote = find_note(handle);
	if (!pnote) return -1;

  // process setting
  switch (set) {
	case v_volume:
    if (value == GET_SETTING)
			value = pnote->mastervolume;
    else {
			if (value > 127)            // limit volume to 0 - 127 (midi compatable)
				value = 127;
      else if (value < 0)
        value = 0;
			pnote->mastervolume = value;
		}
    break;
	case v_panpos:
    if (value == GET_SETTING)
			value = pnote->pan;
		else {
			if (value > 59)
				value = 59;
			else if (value < 1)
				value = 1;
			pnote->pan = value;
		}
		break;
	default:
    return -1;
  }

	// return value as confirmation or notification of adjustment

	return value;
}


 /**************************************************************************\
 |*                                                                        *|
 |* GC - 10/6/96, v1.1                                                     *|
 |* EJ - 12/25/97, v1.2                                                    *|

			VATSTATUS NoteStatus (LONG handle)
 |*                                                                        *|
 |*  Retrieve the play status of the Wave in the queue which corresponds   *|
 |*  to the given handle or Wave id.                                       *|
 |*                                                                        *|
 |*  IN:                                                                   *|
 |*    LONG handle                                                         *|
 |*      a unique id referring to the queued Wave to retrieve status of    *|
 |*                                                                        *|
 |*  OUT:                                                                  *|
 |*    VATSTATUS status                                                    *|
 |*      the current play status of the Wave                               *|
 |*     * v_nonexist - nonexistent                                         *|
 |*     * v_stopped - not yet played (chained or caught before interrupt)  *|
 |*              Waves are removed when finished, not simply stopped.      *|
 |*     * v_started - playing                                              *|
 |*     * v_paused - paused                                                *|
 |*                                                                        *|
 |*  Replaces:                                                             *|
 |*    SoundActive (compatible args)                                       *|
 |*   * searches voicelist rather than voicetoken                          *|
 |*   * returns status rather than boolean                                 *|
 |*                                                                        *|
 \**************************************************************************/

VATSTATUS NoteStatus (LONG handle)
{
	PATCHNOTE *pnote;

	if (!(pnote = find_note (handle))) return v_nonexist;
	else return pnote->status;
}


/**************************************************************************
	PATCHNOTE  *find_note(DWORD handle)

	DESCRIPTION:  Finds a patchnote structure matching the handle.

	INPUTS:
		handle      handle or wave id of the sound structure to find.

**************************************************************************/
PATCHNOTE  *find_note(DWORD handle)
{
	int i;
	PATCHNOTE *pnote;

	if (!handle) return NULL;

																	// search for the note based on handle
	for (pnote=notelist; pnote && pnote->handle != handle; pnote=pnote->next);
			//debugf("F");

	if (pnote && !pnote->available) return pnote;        // Found it!
	else return NULL;               // Didn't find it!
}



/**************************************************************************
	PATCHSAMPLE *loadsample(FILE *input, char *errstring)

	DESCRIPTION: 	Loads each sample part of a patch.  (Called
								from loadlayer)  This is the workhorse of the load patch
								functions.

**************************************************************************/
PATCHSAMPLE *loadsample(FILE *input, char *errstring)
{
	char string[256];
	BYTE v_byte,byte_Samples;
	WORD v_word;
	DWORD v_dword,dword_SampleSize;
	SHORT v_short;
	LONG i,j;
	BYTE envelope_data[12];
	PATCHSAMPLE *newsample = NULL;
	LONG depth16bit,signeddata;
	LONG vroot,vpower,baserate;
	void *data;
	DWORD spot;
	BYTE bvalue;

	newsample = (PATCHSAMPLE *)malloc(sizeof(PATCHSAMPLE));
	if(!newsample) {
		sprintf(errstring,"Out of memory.");
		return(NULL);                           // REturn a null pointer
	}

	newsample->data = NULL;
	newsample->id = sample_id++;																					// Initialize the sample


	fread(string,1,7,input); string[7] = 0;       	// Wave Name
//	debugf("Name=[%s]\n",string);
	strcpy(newsample->name,string);

	fread(&v_byte,1,1,input);                  			// Fractions
//	debugf("Fractions=%d/%d\n",(int)(v_byte/16),(int)(v_byte & 0x0f));
	newsample->start_fraction = (int)(v_byte/16);
	newsample->end_fraction = (int)(v_byte & 0x0f);


	fread(&dword_SampleSize,sizeof(DWORD),1,input); // Size of sample
//	debugf("Size=%d\n",(int)dword_SampleSize);
	newsample->size = dword_SampleSize;


	fread(&v_dword,sizeof(DWORD),1,input);          // Start Loop
	//debugf("Start Loop=%d\n",(int)v_dword);
	newsample->loop_start = v_dword;

	fread(&v_dword,sizeof(DWORD),1,input);          // End Loop
	//debugf("End Loop=%d\n",(int)v_dword);
	newsample->loop_end = v_dword;

	fread(&v_word,sizeof(WORD),1,input);          	// Sample Rate
	//debugf("Sample Rate=%d\n",(int)v_word);
	newsample->sample_rate = v_word;

	fread(&v_dword,sizeof(DWORD),1,input);          // Low Frequency
	//debugf("Low Frequency=%d\n",(int)v_dword);
	newsample->low_frequency = v_dword;

	fread(&v_dword,sizeof(DWORD),1,input);          // High Frequency
	//debugf("High Frequency=%d\n",(int)v_dword);
	newsample->high_frequency = v_dword;

	fread(&v_dword,sizeof(DWORD),1,input);          // Root Frequency
	//debugf("Root Frequency=%d\n",(int)v_dword);
	newsample->root_frequency = v_dword;

	fread(&v_short,sizeof(SHORT),1,input);         	// Tune (1, not used)
	//debugf("Tune=%d\n",(int)v_short);
	newsample->tune = v_short;

	fread(&v_byte,1,1,input);                  			// Balance
	//debugf("Balance=%d\n",(int)v_byte);
	newsample->balance = v_byte;

	fread(&envelope_data,1,12,input);                  			// Balance
//	debugf("Envelope data: ");
																					// Pre-process envelope data.
																					// The rate will be converted
																					// into 16bit volume ticks/sec.
																					// The offset will be converted
																					// to a 16bit value;
	for(i = 0; i < 6; i++) {
//		debugf("%2X ",envelope_data[i]);
		vroot = envelope_data[i]&0x3f;
		vpower = envelope_data[i]>>6;
		newsample->envelope_rate[i] = vroot * 720000 ;
		for(j = 0; j < vpower; j++) {
			newsample->envelope_rate[i] >>=3;
		}
		newsample->envelope_offset[i] = envelope_data[i+6]*0x100;
	}
//	debugf("\n");

	fread(&v_byte,1,1,input);                  			// Temolo Sweep
//	debugf("Tremolo Sweep=%d\n",(int)v_byte);
	newsample->tremolo_sweep = v_byte;

	fread(&v_byte,1,1,input);                  			// Temolo Rate
//	debugf("Tremolo Rate=%d\n",(int)v_byte);
	newsample->tremolo_rate = v_byte;

	fread(&v_byte,1,1,input);                  			// Temolo Depth
//	debugf("Tremolo Depth=%d\n",(int)v_byte);
	newsample->tremolo_depth = v_byte;

	fread(&v_byte,1,1,input);                  			// Vibrato Sweep
//	debugf("Vibrato Sweep=%d\n",(int)v_byte);
	newsample->vibrato_sweep = v_byte;

	fread(&v_byte,1,1,input);                  			// Vibrato Rate
//	debugf("Vibrato Rate=%d\n",(int)v_byte);
	newsample->vibrato_rate = v_byte;

	fread(&v_byte,1,1,input);                  			// Vibrato Depth
//	debugf("Vibrato Depth=%d\n",(int)v_byte);
	newsample->vibrato_depth = v_byte;

	fread(&v_byte,1,1,input);                  			// Modes
//	debugf("Modes:\n");
//	debugf("  Sample depth:%s\n",v_byte&0x01 ? "16bit" : "8bit");
//	debugf("  high bit:%s\n",v_byte&0x02 ? "unsigned" : "signed");
//	debugf("  Looping:%s\n",v_byte&0x04 ? "On" : "Off");
//	debugf("  Bi-D Looping:%s\n",v_byte&0x08 ? "On" : "Off");
//	debugf("  -Looping:%s\n",v_byte&0x10 ? "On" : "Off");
//	debugf("  Sustain:%s\n",v_byte&0x20 ? "On" : "Off");
//	debugf("  Envelopes:%s\n",v_byte&0x40 ? "On" : "Off");
//	debugf("  Clamped Release:%s\n",v_byte&0x80 ? "On" : "Off");
	depth16bit = v_byte&0x01;
	signeddata = v_byte&0x02;
	newsample->mode_looping = v_byte&0x04;
	newsample->mode_bi_dir_looping = v_byte&0x08;
	newsample->mode_backward_looping = v_byte&0x10;
	newsample->mode_sustain = v_byte&0x20;
	newsample->mode_envelopes = v_byte&0x40;
	newsample->mode_clamped_release = v_byte&0x80;

	fread(&v_short,sizeof(SHORT),1,input);          // Scale Frequency
	newsample->scale_frequency = v_short;

	fread(&v_word,sizeof(WORD),1,input);          	// Scale Factor
	//debugf("Scale Fr,Fa=%d,%d\n",(int)v_short,(int)v_word);
	newsample->scale_factor = v_word;

//	debugf("     Reading extensions...\n");

																									// Future extensions
	if(fread(string,1,36,input) < 36) {
		sprintf(errstring,"End of data in the sample!");
		VFREE(newsample);
		return NULL;
	}

//	debugf("     Allocating buffer\n");
	data = VMALLOC(dword_SampleSize);
	if(!data) {
		sprintf(errstring,"Out of memory.");
		VFREE(newsample);
		return NULL;
	}

//	debugf("     Filling Buffer\n");

//	fseek(input,dword_SampleSize,SEEK_CUR);         // Skip the sample (for now)
	if(fread(data,1,dword_SampleSize,input) < dword_SampleSize) {
		sprintf(errstring,"Out of memory.");
		VFREE(newsample);
		VFREE(data);
		return NULL;
	}

//	debugf("     Allocating VAT buffer\n");
	newsample->data = (SAMPLE *)VMALLOC(dword_SampleSize/(depth16bit+1));
	if(!newsample->data) {
		sprintf(errstring,"Out of memory.");
		VFREE(newsample);
		VFREE(data);
		return NULL;
	}
//	debugf("     Filling VAT BUFFER...\n");
//	debugf("       Data type: %s, %s\n",depth16bit ? "16bit" : "8bit", signeddata ? "signed" : "unsigned");
																						// REad data into VAT format
	for(i = 0; i <dword_SampleSize ; i+= (depth16bit+1)) {

		bvalue = *((BYTE *)data + i + depth16bit);
		spot = i/(depth16bit+1);
		if(signeddata) *(newsample->data + spot) = bvalue ^ 0x80;
		else *(newsample->data + spot) = bvalue ;
	}

	if(depth16bit) {
		newsample->loop_start /= 2;
		newsample->loop_end /= 2;
		newsample->size /= 2;
	}

//	debugf("     Wrapping up...\n");
	VFREE(data);
	//debugf("     returning...\n");
	return newsample;
}



/**************************************************************************
	int loadlayer(FILE *input, PATCH *newpatch, char *errstring);

	DESCRIPTION: 	Loads each layer part of a patch.  (Called
								from loadinstrument)

**************************************************************************/
int loadlayer(FILE *input, PATCH *newpatch, char *errstring)
{
	char string[500];
	BYTE v_byte,byte_Samples;
	WORD v_word;
	DWORD v_dword;
	int i;
	PATCHSAMPLE *newsamp = NULL;


	fread(&v_byte,1,1,input);                  			// Layer Dup
	//debugf("Duplicate=%d\n",(int)v_byte);
	fread(&v_byte,1,1,input);                  			// Layer ID
	//debugf("ID=%d\n",(int)v_byte);
	fread(&v_dword,sizeof(DWORD),1,input);          // Size of layer
	//debugf("Size=%d\n",(int)v_dword);
	fread(&byte_Samples,1,1,input);                 // #layers (1)
	//debugf("Samples=%d\n",(int)byte_Samples);

																									// Future extensions
	if(fread(string,1,40,input) < 40) {
		sprintf(errstring,"End of data in the layer!");
		return v_false;
	}




																		// Read all the samples and make a list							// Load all of the Samples
	for(i = 0; i < byte_Samples; i++) {
		//debugf("^^^ SAMPLE: %d ^^^\n",i);
		newsamp = loadsample(input,errstring);
		if(!newsamp) {
			FreePatch(newpatch);
			return NULL;
		}
		newsamp->next = newpatch->samplelist;
		newpatch->samplelist = newsamp;
		//debugf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	}


	return v_true;
}

/**************************************************************************
	int loadinstrument(FILE *input, PATCH *newpatch, char *errstring);

	DESCRIPTION: 	Loads each instrument part of a patch.  (Called
								from loadpatch)

**************************************************************************/
int loadinstrument(FILE *input, PATCH *newpatch, char *errstring)
{
	char string[500];
	BYTE v_byte,byte_Layers;
	WORD v_word;
	DWORD v_dword;
	int i;



	fread(&v_word,sizeof(WORD),1,input);            // Instrument ID
	//debugf("Instrument ID=%X\n",(int)v_word);
	fread(string,1,16,input); string[15] = 0;       // Instrument Name
	//debugf("Name=[%s]\n",string);
	strcpy(newpatch->instrument_name,string);
	fread(&v_dword,sizeof(DWORD),1,input);          // Size of instrument
	//debugf("Size=%d\n",(int)v_dword);
	fread(&byte_Layers,1,1,input);                  // #layers (1)
	//debugf("Layers=%d\n",(int)byte_Layers);


																									// Future extensions
	if(fread(string,1,40,input) < 40) {
		sprintf(errstring,"End of data in the instrument!");
		return v_false;
	}


																									// Load just one layer
	for(i = 0; i < 1; i++) {
		//debugf("*** LAYER: %d ***\n",i);
		if(!loadlayer(input,newpatch,errstring)) {
			FreePatch(newpatch);
			return NULL;
		}
		//debugf("***************************************\n");
	}


	return v_true;
}


/*********************************************************************
	PATCH	*LoadPatch(CHAR *patchfile, CHAR *errstring)

	DESCRIPTION:  Loads a Gravis Patch file

	INTPUTS:

		wavefile    filename of wave file
		errstring   preallocated string for storing errors (256 bytes min)

	RETURNS:
		pointer to data

**********************************************************************/
PATCH  *LoadPatch(CHAR *patchfile, CHAR *errstring)
{
	FILE *input;
	char string[500] = {"zorba"};
	BYTE v_byte,byte_Instruments;
	WORD v_word;
	DWORD v_dword;
	int i;
	PATCH *newpatch = NULL;
	char *namestart,*nameend;


	if (!patchfile || !*patchfile || !errstring) {
		if (errstring)
			sprintf (errstring, "Empty filename");
		return(NULL);
	}

	input = fopen(patchfile,"rb");
	if(!input) {                              // If unsuccesful...
		sprintf(errstring,"Cannot open file %s",patchfile);
		return(NULL);                           // REturn a null pointer
	}

	newpatch = (PATCH *)malloc(sizeof(PATCH));
	if(!newpatch) {
		sprintf(errstring,"Out of memory.");
		fclose(input);
		return(NULL);                           // REturn a null pointer

	}
																		 // Initialize the new patch
	newpatch->id = patch_id++;
	newpatch->samplelist = NULL;
																		 // Create a default name
	namestart = strrchr(patchfile,'\\');
	if(!namestart) namestart = patchfile;
	else namestart++;
	strcpy(string,namestart);
	nameend = strrchr(string,'.');
	if(nameend) *nameend = 0;
	strcpy(newpatch->name,string);

																		 // Read Patch header
	fread(string,1,12,input); string[12] = 0;       // PatchID (GFPATCH110)
	//debugf("PatchID=[%s]\n",string);
	if(strcmp(string,"GF1PATCH110")) {
		sprintf(errstring,"Not a valid patch file.");
		FreePatch(newpatch);
		fclose(input);
		return(NULL);                           // REturn a null pointer
	}


	fread(string,1,10,input); string[10] = 0;       // Gravis ID (ID#000002)
	//debugf("GravisID=[%s]\n",string);
	fread(string,1,60,input); string[60] = 0;       // Description
	//debugf("Description=[%s]\n",string);

	fread(&byte_Instruments,1,1,input);             // # instruments (should be 1)
	//debugf("Instruments=%d\n",(int)byte_Instruments);
	fread(&v_byte,1,1,input);                       // # Voices
	//debugf("Voices=%d\n",(int)v_byte);
	fread(&v_byte,1,1,input);                       // #channels  (ignored)
	//debugf("Channels=%d\n",(int)v_byte);
	fread(&v_word,sizeof(WORD),1,input);            // # Waveforms
	//debugf("Waveforms=%d\n",(int)v_word);
	fread(&v_word,sizeof(WORD),1,input);            // Master Volume
	//debugf("Master Volume=%d\n",(int)v_word);
	newpatch->master_volume = v_word;


	fread(&v_dword,sizeof(DWORD),1,input);          // Size patch takes in GUS ram
	//debugf("Data Size=%d\n",(int)v_dword);

																									// Future extensions
	if(fread(string,1,36,input) < 36) {
		sprintf(errstring,"End of data in the patch header!");
		fclose(input);
		return v_false;
	}

																									// Load all of the instruments
	for(i = 0; i < byte_Instruments; i++) {
		//debugf("--- INSTRUMENT: %d ---\n",i);
		if(!loadinstrument(input,newpatch,errstring)) {
			FreePatch(newpatch);
			fclose(input);
			return NULL;
		}
		//debugf("---------------------------------------\n");
	}

	fclose(input);
	return newpatch;
}

/*********************************************************************
	int SavePatch(CHAR *patchfile, PATCH *saveme, CHAR *errstring)

	DESCRIPTION:  saves a Gravis Patch file  (mono, 8bit)

	INTPUTS:

		patchfile		filename of wave file
		saveme			The wave to save!
		errstring   preallocated string for storing errors (256 bytes min)

	RETURNS:
		TRUE on success

**********************************************************************/
int SavePatch(CHAR *patchfile, PATCH *saveme, CHAR *errstring)
{

}


/**************************************************************************
	WAVE *LoadPatchFromMemory(WAVE VFAR *w,SAMPLE *data, LONG l)

	DESCRIPTION:  Creates a Wave structure from raw sample data in
								memory.  Use this function to collect pre-loaded sounds.

	INPUTS:
			w 		Pointer to a wave structure.  If this is NULL, this function
						will create a new structure and return it.  If it points to
						a structure, this function will append the new data to the
						end of the linked list.
			data  POinter to raw sound data.
			l			Length of the data.  This must be less than MAXCHUNKSIZE

	RETURNS
		pointer to new wave struct.   NULL on fail

**************************************************************************/
WAVE *LoadPatchFromMemory(PATCH *w,SAMPLE *data, LONG l)
{
/*	WAVE *nw,*hold;
																				// Allocate new wave struct
	nw = (WAVE *)VMALLOC(sizeof(WAVE));
	if(!nw) return NULL;

																				// Put in intial values.
	nw->chunk_size = l;             			// size of this chunk in bytes
	nw->data = data;                      // pointer to raw data
	nw->next = NULL;                      // terminate tail.

																				// If w is NULL, that means we
																				// start fresh.
	if(!w) {
		nw->stereo = v_false;
		nw->loaded = 0;
		nw->id = voice_id;                // Give it a handle
		wave_id--;
		nw->head = nw;                			// points to top link.
		nw->sample_size = l;          			// size of entire linked sample
	}
	else {
		hold = w;
		while(hold) {                       					// Update list
			hold->sample_size = w->sample_size + l;
			hold = hold->next;
		}
		hold = w;                           // Find last link
		while(hold->next) hold = hold->next;

		hold->next = nw;                    // Add new link and copy values

		nw->sample_rate = w->sample_rate;
		nw->byte_rate = w->byte_rate;
		nw->id = w->id;
		nw->head = w;
		nw->sample_size = w->sample_size;   // size of entire linked sample
	}

	return nw;                            // BYEBYE!
	*/
}


/**************************************************************************
	void FreePatch(PATCH *pat)

	DESCRIPTION:  Frees all the memory associated with a patch.

	INPUTS:
		pat   pointer to patch structure

**************************************************************************/
void FreePatch(PATCH *pat)
{
	PATCHSAMPLE *psamp,*phold;

	if(!pat) return;
																		// Free the samples first
	psamp = pat->samplelist;
	while(psamp) {
		phold = psamp->next;
		VFREE(psamp);
		psamp = phold;
	}
	pat->samplelist = NULL;

	VFREE(pat);                       // Free the patch now
}

/**************************************************************************
	void initnote(void)

	DESCRIPTION:  Initializes all of the note stuff to prepare for fresh
								Midi playing.

**************************************************************************/
void initnote(void)
{
	int i;
	double freq;

																				// Set up sound tokens
	for(i = 0; i < MAXNOTETOKENS; i++) notetoken[i].available = v_true;
	notelist = NULL;                     // Make sure list is empty
	notes_in_queue=0;
	note_handle=1;

																				// Calculate gravis frequency numbers
																				// 60 is the MIDI note for middle C
	for(i = 69, freq = 440000.0 ; i < 128; i++) {
		pitchtable[i] = freq;
		freq *= CHROMATIC_RATIO;
	}

	for(i = 69, freq = 440000.0 ; i >= 0; i--) {
		pitchtable[i] = freq;
		freq /= CHROMATIC_RATIO;
	}

	makedefaultpatches();

}


/**************************************************************************
	void makedefaultpatches(void)

	DESCRIPTION: Sets up the default patches.

**************************************************************************/
void makedefaultpatches(void)
{

	int i;
	PATCHSAMPLE *psamp;
	SAMPLE *s;
	double theta=0,amp=120;
																				// Set up default instruments
																				// The default instrument is a
																				// Generic tone.
																				// The default drum is a low to
																				// high white noise.

	s = defaultsampledata;
	for(i = 0; i < 100; i++) {
		theta = i/50.0 * 3.141593;
		*(s+i) = (int)(100 * sin(theta));
	}

	for(i = 0; i < 4000; i++) {
		amp *=.99885;
		*(s+i+100) = ((double)rand()/RAND_MAX) * amp;
	}


	psamp = &defaultinstrumentsample;

	psamp->id = sample_id++;
	strcpy(psamp->name,"440Hztone");
	psamp->data = defaultsampledata;
	psamp->start_fraction = 0;
	psamp->end_fraction = 0;
	psamp->size = 100;
	psamp->loop_start = 0;
	psamp->loop_end = 99;
	psamp->sample_rate = 44000;
	psamp->low_frequency = 1;
	psamp->high_frequency = 5000000;
	psamp->root_frequency = 440000;
	psamp->tune=512;
	psamp->balance=7;
	psamp->envelope_rate[0]=45360000;
	psamp->envelope_rate[1]=79360;
	psamp->envelope_rate[2]=5700;
	psamp->envelope_rate[3]=80000;
	psamp->envelope_rate[4]=40000000;
	psamp->envelope_rate[5]=40000000;
	psamp->envelope_offset[0]=0x8000;
	psamp->envelope_offset[1]=0x7000;
	psamp->envelope_offset[2]=0x0001;
	psamp->envelope_offset[3]=0x0001;
	psamp->envelope_offset[4]=0x0001;
	psamp->envelope_offset[5]=0x0001;
	psamp->tremolo_sweep = 0;
	psamp->tremolo_rate = 0;
	psamp->tremolo_depth = 0;
	psamp->vibrato_sweep =0;
	psamp->vibrato_rate = 0;
	psamp->vibrato_depth = 0;
	psamp->mode_looping = v_true;
	psamp->mode_bi_dir_looping = v_false;
	psamp->mode_backward_looping = v_false;
	psamp->mode_sustain = v_true;
	psamp->mode_envelopes = v_true;
	psamp->mode_clamped_release = v_false;
	psamp->scale_frequency=60;
	psamp->scale_factor=1024;
	psamp->next = NULL;

	psamp = &defaultdrumsample;

	psamp->id = sample_id++;
	strcpy(psamp->name,"whitedrum");
	psamp->data = defaultsampledata+100;
	psamp->start_fraction = 0;
	psamp->end_fraction = 0;
	psamp->size = 3900;
	psamp->loop_start = 0;
	psamp->loop_end = 3900;
	psamp->sample_rate = 44000;
	psamp->low_frequency = 0;
	psamp->high_frequency = 5000000;
	psamp->root_frequency = 440000;
	psamp->tune=512;
	psamp->balance=7;
	psamp->envelope_rate[0]=45360000;
	psamp->envelope_rate[1]=40000001;
	psamp->envelope_rate[2]=1;
	psamp->envelope_rate[3]=1;
	psamp->envelope_rate[4]=1;
	psamp->envelope_rate[5]=1;
	psamp->envelope_offset[0]=0xff00;
	psamp->envelope_offset[1]=0xff00;
	psamp->envelope_offset[2]=0x0001;
	psamp->envelope_offset[3]=0xff00;
	psamp->envelope_offset[4]=0xff00;
	psamp->envelope_offset[5]=0xff00;
	psamp->tremolo_sweep = 0;
	psamp->tremolo_rate = 0;
	psamp->tremolo_depth = 0;
	psamp->vibrato_sweep =0;
	psamp->vibrato_rate = 0;
	psamp->vibrato_depth = 0;
	psamp->mode_looping = v_false;
	psamp->mode_bi_dir_looping = v_false;
	psamp->mode_backward_looping = v_false;
	psamp->mode_sustain = v_false;
	psamp->mode_envelopes = v_true;
	psamp->mode_clamped_release = v_false;
	psamp->scale_frequency=60;
	psamp->scale_factor=1024;
	psamp->next = NULL;

	defaultinstrument.id = patch_id++;
	defaultinstrument.master_volume = 127;
	strcpy(defaultinstrument.name,"Default Instrument");
	strcpy(defaultinstrument.instrument_name,"440Hz Tone");
	defaultinstrument.samplelist = &defaultinstrumentsample;

	defaultdrum.id = patch_id++;
	defaultdrum.master_volume = 127;
	strcpy(defaultdrum.name,"Default Drum");
	strcpy(defaultdrum.instrument_name,"White drum");
	defaultdrum.samplelist = &defaultdrumsample;



}

