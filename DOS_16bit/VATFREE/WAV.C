/**************************************************************************
												VARMINT'S AUDIO TOOLS 0.71

	WAV.C

		This file contains source code far all WAV related functions in VAT.


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
#include <string.h>
#include "vat.h"

#define DOSYNC1 if(sync_on && inportb(0x3da)&0x08) vsyncclock = 1000
#define DOSYNC2 if(sync_on && !(syncbytecount++ % bytes_per_synccheck) && inportb(0x3da)&0x08) vsyncclock = 1000


//---------------------------- Internal functions

void freesound(DWORD id);
SOUNDEFFECT VFAR *grabsound(DWORD id);
void initwav(void);
LONG waveidseed = -1;

//---------------------------- External variables

extern SHORT dma_bufferlen,*mix_buffer;
extern SHORT vtable[256][64];

//---------------------------- Internal variables

SHORT         sounds_in_queue = 0;

SOUNDEFFECT VFAR *soundlist = NULL;
SOUNDEFFECT VFAR soundtoken[MAXSOUNDTOKENS];
LONG       sampleid = 1;


/**************************************************************************
	void wavplayer(void)

  DESCRIPTION:  Work function called from interrupt to play WAV data

**************************************************************************/
void wavplayer(void)
{
	WORD j;
	SOUNDEFFECT VFAR *s,*hold;
	SAMPLE *data;
	DWORD dummy=0,position,dummy2=0,*pos,length,pinc;
	BYTE volume;

	pos = (DWORD *)(((BYTE *)&position)+1);

	DOSYNC1;
																	 // ***********************************
																	 // *                                 *
																	 // *       Mix in plain sounds       *
																	 // *                                 *
																	 // ***********************************
	s = soundlist;
	while(s){
		DOSYNC1;
		hold = s->next;
		if(s->active && s->type == v_plain) {
			data = s->data;              // set up data pointer
			if(*s->pos >= dma_bufferlen) {// enough left to fill the buffer?
				for(j = 0; j < dma_bufferlen; j++) {
					*(mix_buffer+j) += *(data++);
				}
				s->data = data;
				*s->pos -= (dma_bufferlen);
			}
			else {                         // else play what is left
				position = *s->pos;
				for(j = 0; j <= position; j++) {
					*(mix_buffer+j) += *(data++);
				}
				s->data = data;

				if(s->w->next) {           	// More to play?
					s->w = s->w->next;        // set up next link
					s->data = s->w->data;
					s->length = s->w->chunk_size-1;
					*s->pos = (WORD)s->length;
																		// Mix the rest of the dma_buffer
					if(*s->pos > (dma_bufferlen-j)) {
						*s->pos -= (dma_bufferlen-j);
						data = s->data;
						while(j < dma_bufferlen) {
							*(mix_buffer+j) += *(data++);
							j++;
						}
						s->data = data;
					}
					else {
						data = s->data;
						while(*s->pos) {        // ... or mix rest of sample
							*(mix_buffer+j) += *(data++);
							j++;
							*s->pos--;
						}
						s->data = data;
					}
				}
				else if(!s->repeat) {       // Do we not repeat this sample?

					if(s->chain) {          	// Is there an effect to play after this?
						(s->chain)->next = soundlist;
						soundlist = s->chain;
						s->chain = NULL;      	// Break link to hide from freesound()
						sounds_in_queue++;
					}

					freesound(s->id);      		// Terminate it if not.
					break;
				}
				else {                    	// Decrememnt the repeat counter
					if(s->repeat > 0) s->repeat--; // -1 = infinity
					s->w = s->w->head;
					s->data = s->w->data;
					s->length = s->w->chunk_size-1;
					*s->pos = s->length;
				}
			}
		}
		s = hold;
	}
	DOSYNC1;

																	 // ***********************************
																	 // *                                 *
																	 // *      Mix in fancy sounds        *
																	 // *                                 *
																	 // ***********************************
	s = soundlist;
	while(s){
		DOSYNC1;
		hold = s->next;
		if(s->active && s->type == v_fancy) {
			data = s->data;               // Set up speed varaibles
			position = s->position;
			length = s->length * 256;
			pinc = s->pinc;
			volume = s->volume;

			for(j = 0; j < dma_bufferlen; j++) {
				DOSYNC2;
																		// Add this byte to the mixing buffer
				*(mix_buffer+j) += (*(data + (ARRAYTYPE)*pos)* volume)>>5;
																		// Here is where the frequency magic
																		// happens.  I use fixed point arithmatic
																		// to increment the sample position pointer
																		// at different rates.
				position += pinc;
																		// Are we at the end of the sample?
				if(position >= length) {
					if(s->w->next) {          // More to play?
						s->w = s->w->next;      // set up next link
						data = s->data = s->w->data;
						*pos = *s->pos = 0;
						length = s->length = s->w->chunk_size-1;
						length *= 256;
																		// Mix the rest of the dma_buffer
						while(j < dma_bufferlen && position < length) {
							*(mix_buffer+j) += (*(data + *pos)*volume)>>5;
							position += pinc;
							j++;
						}

						if(position >= length)  break;
					}
					else if(!s->repeat) {     // Do we not repeat this sample?

						if(s->chain) {          // Is there an effect to play after this?
							(s->chain)->next = soundlist;
							soundlist = s->chain;
							s->chain = NULL;      // Break link to hide from freesound()
							sounds_in_queue++;
						}

						freesound(s->id);      	// Terminate it if not.
						break;
					}
					else {                    // Decrememnt the repeat counter
						if(s->repeat > 0) s->repeat--; // -1 = infinity
						position = s->position = 0;
						s->w = s->w->head;
						data = s->data = s->w->data;
						length = s->length = s->w->chunk_size-1;
						length *= 256;
					}
				}
				s->position = position;
			}
		}
		s = hold;
	}
}

/**************************************************************************
	void freesound(DWORD id)

	DESCRIPTION:  Removes sound effect from active list and clears token for
								later use.

	INPUTS:
		id    Id of sound effect to free

**************************************************************************/
void freesound(DWORD id)
{
	SOUNDEFFECT VFAR *s,*hold,*hold2;


	hold = NULL;                       // Find the sound based on the id
	s = soundlist;
	while(s && s->id != id) {          // move down until we find the id
		DOSYNC1;
		hold = s;
		s = s->next;
	}

	if(!s) return;                     // No such sound? go home!

	sounds_in_queue--;                 // keep track for PlaySound()
	s->type = v_unused;
	s->id = 0;

	if(!hold) {                        // Hold empty? Must be head of list
		soundlist = s->next;             // Close the list
		return;
	}

	hold->next = s->next;              // close the spot in the list

	hold = s->chain;                   // Kill any chains attached to it
	while(hold) {
		DOSYNC1;
		hold2 = hold->chain;
		hold->type = v_unused;
		hold->id = 0;
		hold = hold2;
	}
	return;
}


/**************************************************************************
	SOUNDEFFECT VFAR *newsoundeffect(void)

	DESCRIPTION:  Creates a new sound effect an initializes it variables

								Note: Soundeffect Tokens are pre-allocated rather than dynamically
											allocated because many thousands of sounds may
											be played in a single game.  Allocating and
											re-allocating all this tiny pieces of memory can cause
											problems.

	RETURNS:
		Pointer to the new sound effect structure

	SAMPLE  *data;
	DWORD   length;
	DWORD   position;
	WORD    *pos;
	WORD    pinc;
	SHORT     repeat;
	BYTE    volume;
	BYTE    active;
	DWORD   id;
	struct soundeffect *chain;
	struct soundeffect *next;

**************************************************************************/
SOUNDEFFECT VFAR *newsoundeffect(void)
{
	SOUNDEFFECT VFAR *s;
	SHORT i;
																	 // Find an empty sound token
	for(i =0 ; i< MAXSOUNDTOKENS && soundtoken[i].type != v_unused; i++);
	if(i == MAXSOUNDTOKENS) return(NULL);
	s = &soundtoken[i];
																	 // Initialize varaibles
	s->data = NULL;
	s->length = 1;
	s->position = 0;
	s->pos = (WORD *)(((BYTE *)&(s->position))+ 1);
	s->pinc = 256;
	s->repeat = 0;
	s->volume = 43;                  // 43 represents standard volume
	s->active = TRUE;
	s->id = sampleid++;
	s->chain = NULL;
	s->next = NULL;
	s->chainfunc = NULL;
	return(s);
}

/**************************************************************************
	DWORD PlaySound(WAVE VFAR *w,VATPLAYTYPE type)

	DESCRIPTION: Adds an sound to the play list.  If the playlist is full,
							 the oldest one gets chopped;

	INPUTS:
		w					Pointer to wave structure
		type      inidicates which code is used to play the sound

	RETURNS:
		id of created sound effect or NULL on failure.  This id can is used
		as a handle to access the effect by other functions.


**************************************************************************/
DWORD PlaySound(WAVE VFAR *w,VATPLAYTYPE type)
{
	SOUNDEFFECT VFAR *s;

	if(!w) return 0;

	_disable();                               // We don't want any interrupts
																						// While we do this.

	if(sounds_in_queue >= MAXSOUNDS) {        // Too many sounds active?
																						// Chop off sound at end of list
		s = soundlist;
		while(s && s->next && s->next->repeat != -1 ) s = s->next;
		freesound(s->id);                       // Kill the sound
	}

	s = newsoundeffect();                     // Allocate new effect
	if(!s) {
		_enable();                              // restore interrupts
		return(0);
	}

	s->data = w->data;                        // Initialize data portion
	s->length = w->chunk_size-1;
	if(type == v_plain) *s->pos = (WORD)s->length;
	s->type = type;
	s->w = w;

	s->next = soundlist;                      // Add to the list
	soundlist = s;

	sounds_in_queue++;

	_enable();                                // retore interrupts
	return(s->id);
}


/**************************************************************************
	DWORD ChainSoundEffect(WAVE VFAR *w,VATPLAYTYPE type,DWORD id)

	DESCRIPTION:  This chains a new soundeffect to an active one.  The new
								sound effect wiill be played when the first one os finished.

	INPUTS:
		data      pointer to sample data
		length    length of sample in bytes
		type      playtype for the sew sample (v_fancy or v_plain)
		id        id if the sound effect to chain to

	RETURNS:
		id of created sound effect or NULL on failure.  This id can is used
		as a handle to access the effect by other functions.


**************************************************************************/
DWORD ChainSoundEffect(WAVE VFAR *w,VATPLAYTYPE type,DWORD id)
{
	SOUNDEFFECT VFAR *s,*o;

	if(!w) return 0;

	_disable();                               // We don't want any interrupts
																						// While we do this.

	o = grabsound(id);                       // grab the original effect
	if(!o) {
		_enable();                             // Restore interrupts
		return(0);
	}

	s = newsoundeffect();                    // Allocate new effect
	if(!s) {
		_enable();                             // restore interrupts
		return(0);
	}

	s->data = w->data;                        // Initialize data portion
	s->length = w->chunk_size-1;
	if(type == v_plain) *s->pos = (WORD)s->length;
	s->type = type;
	s->w = w;
																					 // Link the new soundeffect
	while(o->chain) o = o->chain;            // Find the end of the chain
	o->chain = s;

	_enable();                               // Restore interrupts
	return(s->id);
}


/**************************************************************************
	SHORT AddChainFunction(DWORD id,void (*func)(SOUNDEFFECT VFAR *))

	DESCRIPTION:  Attaches a function to a sound effect.  The function is
								called when the sound effect is done.

	INPUTS:
		id      Id of sound effect to use
		func    pointer to the function to chain to

	RETURNS:
		TRUE if successful, FALSE if not

**************************************************************************/
SHORT AddChainFunction(DWORD id,void (*func)(SOUNDEFFECT VFAR *))
{
	SOUNDEFFECT VFAR *s;

	s = grabsound(id);              // find the soundeffect
	if(!s) return(FALSE);

	s->chainfunc = func;            // add the function

	return(TRUE);                   // It worked!
}

/**************************************************************************
	SOUNDEFFECT VFAR *grabsound(DWORD id)

	DESCRIPTION:  Finds a sound structure matching the id

	INPUTS:
		id      id of the sound structure to find

**************************************************************************/
SOUNDEFFECT VFAR *grabsound(DWORD id)
{
	SHORT i;
																// Search sound tokens for matching id
	for(i = 0; i < MAXSOUNDTOKENS && soundtoken[i].id != id; i++);
	if(i == MAXSOUNDTOKENS) return NULL;

	return(&soundtoken[i]);       // Return what we got
}

/**************************************************************************
	void AlterSoundEffect(DWORD id,VATCOMMAND c,LONG parameter)

	DESCRIPTION:  Alters items in the sound effect structure

	INPUTS:
		id          soundeffect id
		c           The command id to signal the appropriate action
		parameter   The argument of the command

**************************************************************************/
void AlterSoundEffect(DWORD id,VATCOMMAND c,LONG parameter)
{
	SOUNDEFFECT VFAR *s;

	s = grabsound(id);

	if(!s) return;

	switch(c) {                            // Act on all the varmint commands
		case v_play:
			s->position = 0;
			s->active = TRUE;
			s->w = s->w->head;
			s->data = s->w->data;
			break;
		case v_stop:
			freesound(id);
			break;
		case v_pause:
			s->active = FALSE;
			break;
		case v_resume:
			s->active = TRUE;
			break;
		case v_rewind:
			s->position = 0;
			s->w = s->w->head;
			s->data = s->w->data;
			break;
		case v_setrepeat:
			s->repeat = parameter;              // positive value = loop x times
																					// negative value = loop forever
																					// 0 = loop once
			break;
		case v_setpos:
			if(s->type == v_fancy) *s->pos = parameter;
			else if(s->type == v_plain) s->data = s->w->data + (ARRAYTYPE)parameter;
			break;
		case v_setrate:                       // Rate is sent in as a fixed point
			s->pinc = parameter;
			break;
		case v_setvolume:
			if(parameter > 63) parameter = 63;
			if(parameter < 0) parameter = 0;
			s->volume = parameter;              // 63 = LOUD, 0 = silent
			break;
		default:
			break;
	}

}




/*********************************************************************
	WAVE VFAR *LoadWave(CHAR *wavefile, CHAR *errstring)

	DESCRIPTION:  Loads a wave files  (mono, 8bit)

	INTPUTS:

		wavefile  	filename of wave file
		errstring   preallocated string for storing errors (256 bytes min)

	RETURNS:
		pointer to data

**********************************************************************/
WAVE VFAR *LoadWave(CHAR *wavefile, CHAR *errstring)
{
	WORD ii;
	WAVE VFAR *newwave,*hold;
	BYTE dummydata[255];
	FILE *input;
	DWORD rlen,flen,blen,length,l;
	WORD s_per_sec,b_per_sec,num_channels,tag;
	CHAR riffid[5],waveid[5],fmtid[5],dataid[5];

	input = fopen(wavefile,"rb");
	if(!input) {                              // If unsuccesful...
		sprintf(errstring,"Cannot open file %s",wavefile);
		return(NULL);                           // REturn a null pointer
	}
																						// Get WAVE header data

	fread(riffid,1,4,input);                  // wave files staqrt with "Riff"
	riffid[4] = 0;
	fread(&rlen,1,4,input);                   // File size
	fread(waveid,1,4,input);                  // Wave id string  ("Wave")
	waveid[4] = 0;
	if(strcmp(waveid,"WAVE")) {               // is it a wave file?
		fclose(input);
		sprintf(errstring,"%s is not a WAVE file",wavefile);
		return(NULL);
	}

	fread(fmtid,1,4,input);                   // Format id string ("fmt ")
	fmtid[4] = 0;
	fread(&flen,1,4,input);                   // offset to data
	if(flen > 240) flen = 240;                // Just a precaution so that
																						// We do not overload dummydata

	fread(&tag,1,2,input);                    // tag
	fread(&num_channels,1,2,input);           // number of channels
	fread(&s_per_sec,1,2,input);              // sample rate (hz)
	fread(&b_per_sec,1,2,input);              // bytes per seconf rate
	fread(dummydata,1,(size_t)flen-8,input);          // Skip ahead
	fread(dataid,1,4,input);                  // Dataid string
	dataid[4] = 0;
	fread(&length,1,4,input);                  // length of data

																						// create top mem structure
	newwave = (WAVE VFAR *)VMALLOC(sizeof(WAVE));
	if(!newwave) {                            // out of mem?
		fclose(input);
		sprintf(errstring,"Out of memory");
		return(NULL);
	}
	hold = newwave;                           // Set working pointer
	hold->next = NULL;

	l = length;                               // dummy holder for length

	while(l > 0) {
		blen = MAXCHUNKSIZE;                    // Number of bytes to read
		if(l < MAXCHUNKSIZE) blen = l;

		hold->data = (SAMPLE *)VMALLOC(blen+1); // allocate memory for data
		if(!hold->data) {                       // oops.  Not enough mem!
			fclose(input);
			sprintf(errstring,"Out of memory");
			while(newwave){                       // deallocate what we have done
				if(newwave->data) VFREE(newwave->data);
				hold = newwave;
				newwave = newwave->next;
				VFREE(hold);
			}
			return(NULL);
		}


		fread(hold->data,1,(size_t)blen,input);    // read the data

		for(ii = 0; ii < blen; ii++) {       // convert to signed format
			*(hold->data + ii) = ((BYTE)*(hold->data + ii))-128;
		}
																				 // Fill in structure
		hold->id = waveidseed;
		hold->sample_rate = s_per_sec;
		hold->byte_rate = b_per_sec;
		hold->chunk_size = blen;             // size of this chunk in bytes
		hold->sample_size = length;          // size of entire linked sample
		hold->head = newwave;                // points to top link.

																				 // Allocate next link
		if(l-blen > 0) {
			hold->next = (WAVE VFAR *)VMALLOC(sizeof(WAVE));
			if(!hold->next) {                    // out of mem?
				fclose(input);
				sprintf(errstring,"Out of memory");
				while(newwave){                    // deallocate what we have done
					if(newwave->data) VFREE(newwave->data);
					hold = newwave;
					newwave = newwave->next;
					VFREE(hold);
				}
				return(NULL);
			}
			hold = hold->next;
			hold->next = NULL;
		}
		l -= blen;
	}

	fclose(input);                            // Wrap it up
	waveidseed --;
	return(newwave);
}


/**************************************************************************
	WAVE VFAR *LoadWaveFromMemory(WAVE VFAR *w,SAMPLE *data, LONG l)

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
WAVE VFAR *LoadWaveFromMemory(WAVE VFAR *w,SAMPLE *data, LONG l)
{
	WAVE VFAR *nw,*hold;
																				// Allocate new wave struct
	nw = (WAVE VFAR *)VMALLOC(sizeof(WAVE));
	if(!nw) return NULL;

																				// Put in intial values
	nw->chunk_size = l;             			// size of this chunk in bytes
	nw->data = data;                      // pointer to raw data
	nw->next = NULL;                      // terminate tail.

																				// If w is NULL, that means we
																				// start fresh.
	if(!w) {
		nw->id = waveidseed;                // Give it a handle
		waveidseed--;
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
}

/**************************************************************************
	void FreeWave(WAVE VFAR *w)

	DESCRIPTION:  Frees all the memory associated with a sound effect.

	INPUTS:
		w		pointer to wave structure

**************************************************************************/
void FreeWave(WAVE VFAR *w)
{
	WAVE VFAR *hold;

	if(!w) return;

	while(w){                    			// We are going to free the whole list
		if(w->data) VFREE(w->data);     // Free sound data
		hold = w;
		w = w->next;                    // move down
		VFREE(hold);                    // Free the struct
	}
}


/**************************************************************************
	LONG SoundActive(LONG id)

	DESCRIPTION:  Tells you wether a wave or sound effect is active

					Note:  Wave id's are negative.

	INPUTS:
		id		The id of either a wave or sound effect.

	RETURNS:
		0 for not active, sound effect id if it is

**************************************************************************/
LONG SoundActive(LONG id)
{
	SHORT i;

	if(id < 0) {                      	// Searching for a particular wave?
		for(i = 0; i < MAXSOUNDTOKENS; i++){
			if(soundtoken[i].w->id == id &&
				soundtoken[i].type != v_unused) return(soundtoken[i].id); // found one!
		}
		return(0);
	}
																			// Searching for a particular active
																			// Sound effect?
	else {
		for(i = 0; i < MAXSOUNDTOKENS; i++){
			if(soundtoken[i].id == id &&
				soundtoken[i].type != v_unused) return(id);   // found it!
		}
		return(0);
	}

}

/**************************************************************************
	void initwav(void)

	DESCRIPTION:  Initializes all of the wav stuff to prepare for fresh
								Wave playing.

**************************************************************************/
void initwav(void)
{
	SHORT i;
																				// Set up sound tokens
	for(i = 0; i < MAXSOUNDTOKENS; i++) soundtoken[i].type = v_unused;
	soundlist = NULL;                     // Make sure list is empty
	sounds_in_queue=0;
	sampleid=1;

}