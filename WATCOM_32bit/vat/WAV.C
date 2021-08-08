/**************************************************************************
                        VARMINT'S AUDIO TOOLS 1.1

  WAV.C

    This file contains source code far all WAV related functions in VAT.


  Authors: Bryan Wilkins  (bwilkins@rt66.com)

  Copyright 1995 - Ground Up

**************************************************************************/

#include <stdio.h>
#include <malloc.h>
#include <dos.h>
#include <string.h>
#include "vat.h"
#include "internal.h"

#define DUMMYFORNOW 0
#define DEBUGME printf

//---------------------------- Internal functions

void freesound(DWORD handle);
SOUNDEFFECT  *find_sound(DWORD handle);
void initwav(void);

//---------------------------- External variables

extern VATSTATUS internal_status;
extern volatile SHORT *mix_buffer;
extern SHORT wav_vol_table[64][256];
extern SHORT lpan[64][60],rpan[64][60];
extern DWORD vat_stereo;
extern DWORD internal_sample_rate;

//---------------------------- Internal variables

SHORT         sounds_in_queue = 0;

SOUNDEFFECT  *soundlist = NULL;
SOUNDEFFECT   soundtoken[MAXSOUNDTOKENS];
LONG          wave_id=-1, sound_handle=1;


/**************************************************************************
  void wavplayer(void)

  DESCRIPTION:  Work function called from interrupt to play WAV data

**************************************************************************/
void wavplayer(void)
{
  SOUNDEFFECT  *s,*hold;
  SAMPLE *data;
  static DWORD dumm1=0,position=0,dumm2=0;
  static DWORD pinc,length;
  DWORD *pos;
  BYTE volume;
  BYTE rvolume,lvolume;
  BYTE pan;
  SHORT *vtr,*vtl,*vt;
	int j;
	ARRAYTYPE dval;
                                   // ***********************************
                                   // *                                 *
                                   // *       Mix in plain sounds       *
                                   // *                                 *
                                   // ***********************************
  s = soundlist;
  while(s){
    if(s->active && s->type==v_plain){
      data = s->data;                  // set up data pointer
      if(*s->pos >= dma_bufferlen) {   // enough left to fill the buffer?
        for(j = 0; j < dma_bufferlen; j+=(vat_stereo+1)) {
          *(mix_buffer+j) += *(data++);
          *(mix_buffer+j+vat_stereo) += *(data);
        }
        s->data = data;
        *s->pos -= (dma_bufferlen)/(vat_stereo+1);
      }
      else {                           // else play what is left
        position = *s->pos;
        for(j = 0; j <= position; j+=(vat_stereo+1)) {
          *(mix_buffer+j) += *(data++);
          *(mix_buffer+j+vat_stereo) += *(data);
        }
        s->data = data;
        if(s->wav->next) {               // More to play?
          s->wav = s->wav->next;           // set up next link
          s->data = s->wav->data;
          s->length = s->wav->chunk_size-1;
          *s->pos = (DWORD)s->length;
                                       // Mix the rest of the dma_buffer
          if(*s->pos > (dma_bufferlen-j)) {
            *s->pos -= (dma_bufferlen-j);
            data = s->data;
            while(j < dma_bufferlen) {
              *(mix_buffer+j) += *(data++);
              *(mix_buffer+j+vat_stereo) += *(data);
              j+=(vat_stereo+1);
            }
            s->data = data;
          }
          else {
            data = s->data;
            while(*s->pos) {        // ... or mix rest of sample
              *(mix_buffer+j) += *(data++);
              *(mix_buffer+j+vat_stereo) += *(data);
              j+=(vat_stereo+1);
              *s->pos--;
            }
            s->data = data;
          }
        }
        else if(!s->repeat) {       // Do we not repeat this sample?
          if(s->chain) {            // Is there an effect to play after this?
            (s->chain)->next = soundlist;
            soundlist = s->chain;
            s->chain = NULL;        // Break link to hide from freesound()
            sounds_in_queue++;
          }
          if(s->chainfunc)
            s->chainfunc (s->handle);
          freesound(s->handle);          // Terminate it if not.
          break;
        }
        else {                      // Decrement the repeat counter
          if(s->repeat > 0) s->repeat--; // -1 = infinity
          s->wav = s->wav->head;
          s->data = s->wav->data;
          s->length = s->wav->chunk_size-1;
          *s->pos = (DWORD)s->length;
        }
      }
    }
    s=s->next;
  }
                                   // ***********************************
                                   // *                                 *
                                   // *      Mix in fancy sounds        *
                                   // *                                 *
                                   // ***********************************
  pos = (DWORD *)(((BYTE *)&position)+1);
  s = soundlist;
  while(s){
    if (s->active && s->type==v_fancy) {
      data = s->data;               // Set up speed varaibles
      position = s->position;
      length = s->length * 256;
      pinc = s->pinc;
      volume = s->volume;
      vt = wav_vol_table[volume]+128;
      for(j = 0; j < dma_bufferlen; j+=(vat_stereo+1)) {
                                // Add this byte to the mixing buffer
          *(mix_buffer+j) += vt[(*(data + (ARRAYTYPE)(*pos)))];
          *(mix_buffer+j+vat_stereo) = *(mix_buffer+j);
                                  // Here is where the frequency magic
                                  // happens.  I use fixed point arithmatic
                                  // to increment the sample position pointer
                                  // at different rates.
        position += pinc;
                                  // Are we at the end of the sample?
        if(position >= length) {
          if(s->wav->next) {          // More to play?
            s->wav = s->wav->next;      // set up next link
            data = s->data = s->wav->data;
            *pos = *s->pos = 0;
            length = s->length = s->wav->chunk_size-1;
            length *= 256;
                                // Mix the rest of the dma_buffer
            while(j < dma_bufferlen && position < length) {
              *(mix_buffer+j) += vt[(*(data + (ARRAYTYPE)(*pos)))];
              *(mix_buffer+j+vat_stereo) = *(mix_buffer+j);
              position += pinc;
              j+=(vat_stereo+1);
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
            if(s->chainfunc)
              s->chainfunc (s->handle);
            freesound(s->handle);        // Terminate it if not.
            break;
          }
          else {                    // Decrememnt the repeat counter
            if(s->repeat > 0) s->repeat--; // -1 = infinity
            position = s->position = 0;
            s->wav = s->wav->head;
            data = s->data = s->wav->data;
            length = s->length = s->wav->chunk_size-1;
            length *= 256;
          }
        }
        s->position = position;
      }
    }
    s = s->next;
  }
                                   // ***********************************
                                   // *                                 *
                                   // *      Mix in panning sounds      *
                                   // *                                 *
                                   // ***********************************
	pos = (DWORD *)(((BYTE *)&position)+1);
  s = soundlist;
  while(s){
    if (s->active && s->type==v_pan) {
      data = s->data;               // Set up speed varaibles
      position = s->position;
      length = s->length * 256;
      pinc = s->pinc;
      pan = s->pan;
      rvolume = rpan[s->volume][s->pan];
      lvolume = lpan[s->volume][s->pan];
			vtr = &wav_vol_table[rvolume][128];
			vtl = &wav_vol_table[lvolume][128];
			for(j = 0; j < dma_bufferlen; j+=(vat_stereo+1)) {
																// Add this byte to the mixing buffer
				dval = (*(data + (ARRAYTYPE)(*pos)));
// Forsome reason, these expression cause a crash, so o replaced them
// with pointer notation.  -ej
//				*(mix_buffer+j) += vtl[dval];
//				*(mix_buffer+j+vat_stereo)  += vtr[dval];
				*(mix_buffer+j) += *(vtl + dval);
				*(mix_buffer+j+vat_stereo)  += *(vtr + dval);
																	// Here is where the frequency magic
                                  // happens.  I use fixed point arithmatic
                                  // to increment the sample position pointer
                                  // at different rates.
				position += pinc;

                                  // Are we at the end of the sample?
				if(position >= length) {
          if(s->wav->next) {          // More to play?
            s->wav = s->wav->next;      // set up next link
            data = s->data = s->wav->data;
            *pos = *s->pos = 0;
            length = s->length = s->wav->chunk_size-1;
            length *= 256;
                                // Mix the rest of the dma_buffer
            while(j < dma_bufferlen && position < length) {
              *(mix_buffer+j) += vtl[(*(data + (ARRAYTYPE)(*pos)))];
              *(mix_buffer+j+vat_stereo) += vtr[(*(data + (ARRAYTYPE)(*pos)))];
              position += pinc;
              j+=(vat_stereo+1);
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
            if(s->chainfunc)
              s->chainfunc (s->handle);
            freesound(s->handle);        // Terminate it if not.
            break;
          }
          else {                    // Decrememnt the repeat counter
            if(s->repeat > 0) s->repeat--; // -1 = infinity
            position = s->position = 0;
            s->wav = s->wav->head;
            data = s->data = s->wav->data;
            length = s->length = s->wav->chunk_size-1;
            length *= 256;
          }
				}
				s->position = position;
			}
    }
    s = s->next;
	}
                                   // ***********************************
                                   // *                                 *
                                   // *      Mix in stereo sounds       *
                                   // *                                 *
                                   // ***********************************
  pos = (DWORD *)(((BYTE *)&position)+1);
  s = soundlist;
  while(s){
    if (s->active && s->type==v_stereo) {
      data = s->data;               // Set up speed varaibles
      position = s->position;
      length = s->length * 256;
      pinc = s->pinc;
      volume = s->volume;
      vt = wav_vol_table[volume]+128;
      for(j = 0; j < dma_bufferlen; j+=(vat_stereo+1)) {
                                // Add this byte to the mixing buffer
          *(mix_buffer+j) += vt[(*(data + (ARRAYTYPE)(*pos*2)))];
          *(mix_buffer+j+vat_stereo) += vt[(*(data + (ARRAYTYPE)(*pos*2+1)))];
                                  // Here is where the frequency magic
                                  // happens.  I use fixed point arithmatic
                                  // to increment the sample position pointer
                                  // at different rates.
        position += pinc;
                                  // Are we at the end of the sample?
        if(position >= length) {
          if(s->wav->next) {          // More to play?
            s->wav = s->wav->next;      // set up next link
            data = s->data = s->wav->data;
            *pos = *s->pos = 0;
            length = s->length = s->wav->chunk_size-1;
            length *= 256;
                                // Mix the rest of the dma_buffer
            while(j < dma_bufferlen && position < length) {
              *(mix_buffer+j) += vt[(*(data + (ARRAYTYPE)(*pos*2)))];
              *(mix_buffer+j+vat_stereo) += vt[(*(data + (ARRAYTYPE)(*pos*2+1)))];
              position += pinc;
              j+=(vat_stereo+1);
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
            if(s->chainfunc)
              s->chainfunc (s->handle);
            freesound(s->handle);        // Terminate it if not.
            break;
          }
          else {                    // Decrememnt the repeat counter
            if(s->repeat > 0) s->repeat--; // -1 = infinity
            position = s->position = 0;
            s->wav = s->wav->head;
            data = s->data = s->wav->data;
            length = s->length = s->wav->chunk_size-1;
            length *= 256;
          }
        }
        s->position = position;
      }
    }
    s = s->next;
  }
}


/**************************************************************************
  void freesound(DWORD handle)

  DESCRIPTION:  Removes sound effect from active list and clears token for
                later use.

  INPUTS:
    handle    handle of sound effect to free

**************************************************************************/
void freesound(DWORD handle)
{
  SOUNDEFFECT  *s,*hold,*hold2;


  hold = NULL;                       // Find the sound based on the handle
  s = soundlist;
  while(s && s->handle != handle) {  // move down until we find the handle
    hold = s;
    s = s->next;
  }

  if(!s) return;                     // No such sound? go home!

  sounds_in_queue--;                 // keep track for PlayWave()
  s->type = v_unused;
  s->handle = 0;

  if(!hold) {                        // Hold empty? Must be head of list
    soundlist = s->next;             // Close the list
    return;
  }

  hold->next = s->next;              // close the spot in the list

  hold = s->chain;                   // Kill any chains attached to it
  while(hold) {
    hold2 = hold->chain;
    hold->type = v_unused;
    hold->handle = 0;
    hold = hold2;
  }
  return;
}


/**************************************************************************
  SOUNDEFFECT  *newsoundeffect(void)

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
  SHORT   repeat;
  BYTE    volume;
  BYTE    active;
  VATSTATUS status;
  DWORD   handle;
  struct soundeffect *chain;
  struct soundeffect *next;

**************************************************************************/
SOUNDEFFECT  *newsoundeffect(void)
{
  SOUNDEFFECT  *s;
  int i;
                                   // Find an empty sound token
  for(i =0 ; i< MAXSOUNDTOKENS && soundtoken[i].type != v_unused; i++);
  if(i == MAXSOUNDTOKENS) return(NULL);
  s = &soundtoken[i];
                                   // Initialize varaibles
  s->data = NULL;
  s->length = 1;
  s->position = 0;
  s->pos = (DWORD *)(((BYTE *)&(s->position))+ 1);
  s->pinc = 256;
  s->repeat = 0;
  s->volume = 43;                  // 43 represents standard volume
  s->pan = 30;                     // 30 is middle panning value
  s->active = v_true;
  s->status = v_stopped;
  s->handle = sound_handle++;
  s->chain = NULL;
  s->next = NULL;
  s->chainfunc = NULL;
  return(s);
}

 /**************************************************************************\
 |*                                                                        *|
 |* GC - 10/6/96, v1.1                                                     *|
 |*                                                                        *|
 |*  Add a Wave to the soundlist (removing another if necessary) and       *|
 |*  start it playing at its recorded frequency and with median values     *|
 |*  for volume and panning (if appropriate).                              *|
 |*                                                                        *|
 |*  IN:                                                                   *|
 |*    WAVE *wav                                                           *|
 |*      the WAVE structure to play                                        *|
 |*    int stop_dups                                                       *|
 |*      if 1, stop multiple copies of the Wave from being played          *|
 |*    VATPLAYTYPE type                                                    *|
 |*      the mixing type (v_plain, v_fancy, v_pan, v_stereo)               *|
 |*     * adjusts type to fit the stereo/mono attribute of the Wave        *|
 |*                                                                        *|
 |*  OUT:                                                                  *|
 |*    LONG handle                                                         *|
 |*      the handle of the queued Wave                                     *|
 |*                                                                        *|
 |*  Replaces:                                                             *|
 |*    PlaySound (incompatible args)                                       *|
 |*   * checks play type                                                   *|
 |*   * frees slot more intelligently                                      *|
 |*                                                                        *|
 \**************************************************************************/

LONG PlayWave (WAVE *wav, int stop_dups, VATPLAYTYPE type)
{
  SOUNDEFFECT *s=NULL, *last_s;

  /* check VAT status */
  if (internal_status != v_started)
    return 0;

  /* check Wave validity */
  if (!wav)
    return 0;

  /* check stop_dups */
  if (stop_dups && WaveStatus (wav->id) != v_nonexist)
    return 0;

  /* disable interrupts */
  _disable ();

  /* check for full sound queue */
  if (sounds_in_queue >= MAXSOUNDS) {
    if (!soundlist) {
      _enable ();  // MAXSOUNDS must've been set <= 0; at least don't crash
      return 0;
    }
    /* scan for last nonrepeating wave */
    for (last_s=NULL, s=soundlist; s; s=s->next) {
      if (!s->repeat)
        last_s = s;
    }
    if (last_s)
      freesound (last_s->handle);
    else {
      /* scan for last repeating but terminating wave */
      for (last_s=NULL, s=soundlist; s; s=s->next) {
        if (s->repeat > 0)
          last_s = s;
      }
      if (last_s)
        freesound (last_s->handle);
      else {
        /* scan for last unchained wave */
        for (last_s=NULL, s=soundlist; s; s=s->next) {
          if (!s->chainfunc && !s->chain)
            last_s = s;
        }
        if (last_s)
          freesound (last_s->handle);
        else {
          /* scan for last wave */
          for (s=soundlist; s->next; s=s->next);
          freesound (s->handle);
        }
      }
    }
  }

  /* allocate a new slot */
  if (!(s = newsoundeffect ())) {
    _enable ();  // error allocating new slot;
    return 0;    // re-enable interrupts and return
  }

  /* check mono vs. stereo types */
  if (wav->stereo)    // Wave is stereo;
    type = v_stereo;  // force play type to be stereo
  else if (type == v_stereo)  // not stereo but passed stereo;
    type = v_pan;             // opt for most complex mono play type

  /* set up SOUNDEFFECT struct */
  s->length = wav->chunk_size - 1;
  if (type == v_plain)
    *s->pos = (DWORD)s->length;
  else
    s->position = 0;
  s->type = type;
  s->wav = wav;
  s->data = wav->data;

  /* link it into the soundlist linked list */
  s->next = soundlist;
  soundlist = s;
  sounds_in_queue++;

  /* re-enable interrupts */
  _enable ();

  /* set the relative rate at the frequency the Wave was recorded at */
  if (type != v_plain)
    s->pinc = (256L * wav->sample_rate) / internal_sample_rate;

  /* set the volume at two-thirds level */
  s->volume = 43;

  /* set the panning position in the middle */
  if (type == v_pan)
    s->pan = 30;

  /* start the Wave playing */
  s->active = v_true;
  s->status = v_started;

  /* return the new handle */
  return (s->handle);
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

VATBOOL WaveCommand (LONG handle, VATCOMMAND cmd)
{
  SOUNDEFFECT *s;

  // find sound based on handle
  if (!(s = find_sound (handle)))
    return v_false;

  // process command
  switch (cmd) {
  case v_remove:
  case v_stop:
    if (s->status == v_started ||
        s->status == v_paused) {
      freesound (handle);        /* remove from play queue */
    }
    break;
  case v_play:
    if (s->status == v_paused) {
      s->active = v_true;        /* resume playing */
      s->status = v_started;
    }
    break;
  case v_pause:
    if (s->status == v_started) {
      s->active = v_false;       /* set inactive */
      s->status = v_paused;
    }
    break;
  case v_rewind:
    if (s->status == v_started ||
        s->status == v_paused) {
      if (s->type == v_plain)    /* reset without altering state */
        *s->pos = (DWORD)s->length;
      else
        s->position = 0;
      s->wav = s->wav->head;
      s->data = s->wav->data;
    }
    break;
  default:
    return v_false;              /* invalid command */
  }

  // return confirmation
  return v_true;
}


/**************************************************************************
	int WaveSetting (LONG handle, VATSETTING set, int value)

	DESCRIPTION:

**************************************************************************/
int WaveSetting (LONG handle, VATSETTING set, int value)
{
  SOUNDEFFECT *s;

  // find sound based on handle
  if (!(s = find_sound (handle)))
    return -1;

  // process setting
  switch (set) {
  case v_volume:
    if (value == GET_SETTING)
      value = s->volume;
    else {
      if (value > 63)            /* limit volume to 0 - 63 */
        value = 63;
      else if (value < 0)
        value = 0;
      s->volume = value;
    }
    break;
  case v_repeat:
    if (value == GET_SETTING)
      value = s->repeat;
    else
      s->repeat = value;         /* negative is unterminating */
    break;
  case v_rate:
    if (value == GET_SETTING)
      value = (s->pinc * internal_sample_rate) / 256L;
    else {
			if (s->type != v_plain)
				s->pinc = (256L * value) / internal_sample_rate;
		}
    break;
  case v_panpos:
    if (value == GET_SETTING)
      value = s->pan;
    else {
      if (s->type == v_pan) {    /* limit pan position to 1 - 59 */
        if (value > 59)
          value = 59;
        else if (value < 1)
          value = 1;
        s->pan = value;
      }
    }
    break;
  case v_position:
    if (value == GET_SETTING) {
      if (s->type == v_plain)
        value = s->data - s->wav->data;
      else
        value = *s->pos;
    } else {
      if (value < 0)             /* limit position to 0 - sample_size */
        value = 0;
      else if (value >= s->wav->sample_size)
        value = s->wav->sample_size - 1;
      if (s->type == v_plain)
        s->data = s->wav->data + (ARRAYTYPE)value;
      else
        *s->pos = value;
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
 |*   * searches soundlist rather than soundtoken                          *|
 |*   * returns status rather than boolean                                 *|
 |*                                                                        *|
 \**************************************************************************/

VATSTATUS WaveStatus (LONG handle)
{
  SOUNDEFFECT *s;

  if (!(s = find_sound (handle)))
    return v_nonexist;

  return s->status;
}


/**************************************************************************
  LONG WaveChain(LONG handle,WAVE *wav,VATPLAYTYPE type)

  DESCRIPTION:  This chains a new soundeffect to an active one.  The new
                sound effect wiill be played when the first one os finished.

  INPUTS:
    handle    handle of the sound effect to chain to
    wav       pointer to new wave to play
    type      playtype for the new wave

  RETURNS:
    handle of created sound effect or NULL on failure.  Used
    to access the effect by other functions.


**************************************************************************/
LONG WaveChain(LONG handle,WAVE *wav,VATPLAYTYPE type)
{
  SOUNDEFFECT  *s,*o;

  if (!wav)
    return(0);

  _disable();                               // We don't want any interrupts
                                            // While we do this.

  o = find_sound(handle);                       // grab the original effect
  if(!o) {
    _enable();                             // Restore interrupts
    return(0);
  }

/* enable this with complete disposal of all chained waves
  if (!wav) {
    o->chain = NULL;
    return(0);
  }
*/

  s = newsoundeffect();                    // Allocate new effect
  if(!s) {
    _enable();                             // restore interrupts
    return(0);
  }

  s->data = wav->data;                        // Initialize data portion
  s->length = wav->chunk_size-1;
  if (type == v_plain)
    *s->pos = (WORD)s->length;
  if (wav->stereo)
    type = v_stereo;
  else if (type == v_stereo)
    type = v_pan;
  s->type = type;
  s->wav = wav;
  if (type != v_plain)
    s->pinc = (256L * wav->sample_rate) / internal_sample_rate;
  s->volume = 43;
  if (type == v_pan)
    s->pan = 30;

                                           // Link the new soundeffect
  while(o->chain) o = o->chain;            // Find the end of the chain
  o->chain = s;

  _enable();                               // Restore interrupts
  return(s->handle);
}


/**************************************************************************
  VATBOOL WaveChainFunc(LONG handle,void (*func)(LONG))

  DESCRIPTION:  Attaches a function to a sound effect.  The function is
                called when the sound effect is done.

  INPUTS:
    handle  handle of sound effect to use
    func    pointer to the function to chain to

  RETURNS:
    v_true if successful, v_false if not

**************************************************************************/
VATBOOL WaveChainFunc(LONG handle,void (*func)(LONG))
{
  SOUNDEFFECT  *s;

  s = find_sound(handle);              // find the soundeffect
  if(!s) return(v_false);

  s->chainfunc = func;            // add the function

  return(v_true);                   // It worked!
}

/**************************************************************************
  SOUNDEFFECT  *find_sound(DWORD handle)

  DESCRIPTION:  Finds a sound structure matching either the handle
                or the wave id (handles are > 0, wave id's are < 0)

  INPUTS:
    handle      handle or wave id of the sound structure to find

**************************************************************************/
SOUNDEFFECT  *find_sound(DWORD handle)
{
  int i;
  SOUNDEFFECT *s;

  if (!handle)
    return NULL;

  /* search for the sound based on positive handle */
  for (s=soundlist; s && s->handle != handle; s=s->next);
  if (s)
    return s;

  /* search for the sound based on negative wave id */
  for (s=soundlist; s && s->wav->id != handle; s=s->next);
  if (s)
    return s; // note: multiple copies of a wave makes this match non-unique

  /* search for the sound based on positive handle in all sound tokens */
  for (i=0; i<MAXSOUNDTOKENS && soundtoken[i].handle != handle; i++);
  if (i < MAXSOUNDTOKENS)
    return &soundtoken[i]; // note: this matches chained sounds unlike above

  /* no match - couldn't find it */
  return NULL;
}

/*********************************************************************
	WAVE  *LoadWave(CHAR *wavefile, CHAR *errstring)

	DESCRIPTION:  Loads a wave files  (mono, 8bit)

	INTPUTS:

		wavefile    filename of wave file
    errstring   preallocated string for storing errors (256 bytes min)

  RETURNS:
		pointer to data

**********************************************************************/
WAVE  *LoadWave(CHAR *wavefile, CHAR *errstring)
{
  DWORD ii;
	short int *tempdata;
  WAVE *newwave,*hold;
  BYTE dummydata[255];
	FILE *input;
  DWORD rlen,flen,blen,length,l,s_per_sec,b_per_sec;
  WORD num_channels,tag,b_a,f_s;
	CHAR riffid[5],waveid[5],fmtid[5],dataid[5];

	if (!wavefile || !*wavefile || !errstring) {
    if (errstring)
			sprintf (errstring, "Empty filename");
		return(NULL);
  }

	input = fopen(wavefile,"rb");
  if(!input) {                              // If unsuccesful...
    sprintf(errstring,"Cannot open file %s",wavefile);
		return(NULL);                           // REturn a null pointer
  }
                                            // Get WAVE header data

  fread(riffid,1,4,input);                  // wave files staqrt with "Riff"
  riffid[4] = 0;
//DEBUGME("Riffid=%s\n",riffid);
	fread(&rlen,1,4,input);                   // File size
//DEBUGME("rlen=%ld\n",rlen);
	fread(waveid,1,4,input);                  // Wave id string  ("Wave")
	waveid[4] = 0;
//DEBUGME("waveid=%s\n",waveid);
	if(strcmp(waveid,"WAVE")) {               // is it a wave file?
		fclose(input);
		sprintf(errstring,"%s is not a WAVE file",wavefile);
		return(NULL);
	}

	fread(fmtid,1,4,input);                   // Format id string ("fmt ")
	fmtid[4] = 0;
//DEBUGME("fmtid=%s\n",fmtid);
	fread(&flen,1,4,input);                   // offset to data
//DEBUGME("flen=%ld\n",flen);
	if(flen > 240) flen = 240;                // Just a precaution so that
																						// We do not overload dummydata

	fread(&tag,1,2,input);                    // tag
//DEBUGME("tag=%d\n",tag);
	fread(&num_channels,1,2,input);           // number of channels
//DEBUGME("num_channels=%d\n",num_channels);
	fread(&s_per_sec,1,4,input);              // sample rate (hz)
//DEBUGME("s_per_sec=%ld\n",s_per_sec);
	fread(&b_per_sec,1,4,input);              // bytes per seconf rate
//DEBUGME("b_per_sec=%ld\n",b_per_sec);
	fread(&b_a,1,2,input);
//DEBUGME("b_a=%d\n",b_a);
	fread(&f_s,1,2,input);                    // format specific (8 or 16)
//DEBUGME("f_s=%d\n",f_s);
	fread(dummydata,1,(size_t)flen-16,input); // Skip ahead
	fread(dataid,1,4,input);                  // Dataid string
	dataid[4] = 0;
//DEBUGME("dataid=%s\n",dataid);
	fread(&length,1,4,input);                 // length of data
//DEBUGME("length=%ld\n",length);

																						// create top mem structure
	newwave = (WAVE  *)VMALLOC(sizeof(WAVE));
	if(!newwave) {                            // out of mem?
		fclose(input);
		sprintf(errstring,"Out of memory");
		return(NULL);
	}
	hold = newwave;                           // Set working pointer
	hold->next = NULL;

	l = length;                    // dummy holder for length


	while(l > 0) {
		blen = MAXCHUNKSIZE;                    // Number of bytes to read
		if(l < MAXCHUNKSIZE) blen = l;

		if(f_s == 16) {
			tempdata = (short int *)VMALLOC(blen+1);
			if(!tempdata) {                       // oops.  Not enough mem!
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
		}
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

		if(f_s==8) fread(hold->data,1,(size_t)blen,input);
		else fread(tempdata,2,(size_t)blen,input);

		for(ii = 0; ii < blen; ii++) {
			if(f_s==16) {
				*(hold->data +ii) = (BYTE)(tempdata[ii]>>8);
			}
			else {
				*(hold->data + ii) = ((BYTE)*(hold->data +ii))-128;
			}
		}
																				 // Fill in structure
		hold->id = wave_id;
		hold->sample_rate = s_per_sec;
		hold->byte_rate = b_per_sec;
		if(f_s==8){
			if(num_channels==2){
				hold->chunk_size = blen/2;           // size of this chunk in bytes
				hold->sample_size = length/2;        // size of entire linked sample
			} else {
				hold->chunk_size = blen;           // size of this chunk in bytes
				hold->sample_size = length;        // size of entire linked sample
			}
		} else {
			if(num_channels==2){
				hold->chunk_size = blen/4;         // size of this chunk in bytes
				hold->sample_size = length/4;      // size of entire linked sample
			} else {
				hold->chunk_size = blen/2;         // size of this chunk in bytes
				hold->sample_size = length/2;      // size of entire linked sample
			}
		}
		hold->stereo = (num_channels == 2);
		hold->loaded = 1;
		hold->head = newwave;                // points to top link.

																				 // Allocate next link
		if(l-blen > 0) {
			hold->next = (WAVE  *)VMALLOC(sizeof(WAVE));
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
		if (f_s == 16)
			VFREE(tempdata);
	}

	fclose(input);                            // Wrap it up
	wave_id --;
	return(newwave);
}

/*********************************************************************
	int SaveWave(CHAR *wavefile, WAVE *saveme, CHAR *errstring)

	DESCRIPTION:  saves wave files  (mono, 8bit)

	INTPUTS:

		wavefile    filename of wave file
		saveme			The wave to save!
    errstring   preallocated string for storing errors (256 bytes min)

  RETURNS:
		TRUE on success

**********************************************************************/
int SaveWave(CHAR *wavefile, WAVE *saveme, CHAR *errstring)
{
  DWORD ii;
	short int *tempdata;
  WAVE *newwave,*hold;
	BYTE dummydata[255],*bdata;
	FILE *output;
  DWORD rlen,flen,blen,length,l,s_per_sec,b_per_sec;
  WORD num_channels,tag,b_a,f_s;
	CHAR 	riffid[5]=			{"RIFF"},
				waveid[5]=			{"WAVE"},
				fmtid[5]=				{"fmt "},
				dataid[5]=      {"data"};

	if (!wavefile || !*wavefile || !errstring) {
    if (errstring)
			sprintf (errstring, "Empty filename");
		return(v_false);
	}

	if(!saveme) {
		sprintf (errstring, "No Wave to Save");
		return(v_false);
	}
																						// Get a stream to write to.
	output = fopen(wavefile,"wb");
	if(!output) {                             // If unsuccesful...
    sprintf(errstring,"Cannot open file %s",wavefile);
		return(v_false);                        // REturn false
  }
																						// Write WAVE header data

	length=saveme->chunk_size * (saveme->stereo+1);
	rlen = 16 + 12 + length + 8;
	flen=16;

	fwrite(riffid,1,4,output);                 // wave files staqrt with "Riff"
	fwrite(&rlen,1,4,output);                  // File size (total file-8)
	fwrite(waveid,1,4,output);                 // Wave id string  ("Wave")
	fwrite(fmtid,1,4,output);                  // Format id string ("fmt ")
	fwrite(&flen,1,4,output);                  // offset to data (size of wave
																						 //	description chunk)

	memset(dummydata,0,254);
	tag = 1;                          				// Wave type (PCM = 1)
	num_channels=saveme->stereo+1;
	s_per_sec=saveme->sample_rate;
	if(!s_per_sec) s_per_sec = SampleRate();
	b_per_sec=s_per_sec;
	b_a=1;    																// Block Alignment (1)
	f_s=8;                          					// Bits/sample

	fwrite(&tag,1,2,output);                    // tag
	fwrite(&num_channels,1,2,output);           // number of channels
	fwrite(&s_per_sec,1,4,output);              // sample rate (hz)
	fwrite(&b_per_sec,1,4,output);              // bytes per seconf rate
	fwrite(&b_a,1,2,output);
	fwrite(&f_s,1,2,output);                    // format specific (8 or 16)
	fwrite(dummydata,1,(size_t)flen-16,output); // Skip ahead
	fwrite(dataid,1,4,output);                  // Dataid string
	dataid[4] = 0;
	fwrite(&length,1,4,output);                 // length of data


																							// Convert data tounsigned
	bdata = saveme->data;
	for(ii = 0; ii < length; ii++) {
//		*(bdata+ii) = (BYTE)((int)(*(saveme->data +ii)) + 0);
//		*(bdata+ii) = ii % 256;
			*(bdata+ii) ^= 0x80;
	}

	fwrite(saveme->data,1,length,output);       // Write the data

																							// Convert Back to signed
	for(ii = 0; ii < length; ii++) {
		*(saveme->data + ii) = ((BYTE)*(saveme->data +ii))-128;
	}

	return v_true;

	/*
																						// create top mem structure
	newwave = (WAVE  *)VMALLOC(sizeof(WAVE));
	if(!newwave) {                            // out of mem?
		fclose(input);
		sprintf(errstring,"Out of memory");
		return(NULL);
	}
	hold = newwave;                           // Set working pointer
	hold->next = NULL;

	l = length;                    // dummy holder for length


	while(l > 0) {
		blen = MAXCHUNKSIZE;                    // Number of bytes to read
		if(l < MAXCHUNKSIZE) blen = l;

		if(f_s == 16) {
			tempdata = (short int *)VMALLOC(blen+1);
			if(!tempdata) {                       // oops.  Not enough mem!
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
		}
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

		if(f_s==8) fread(hold->data,1,(size_t)blen,input);
		else fread(tempdata,2,(size_t)blen,input);

		for(ii = 0; ii < blen; ii++) {
			if(f_s==16) {
				*(hold->data +ii) = (BYTE)(tempdata[ii]>>8);
			}
			else {
				*(hold->data + ii) = ((BYTE)*(hold->data +ii))-128;
			}
		}
																				 // Fill in structure
		hold->id = wave_id;
		hold->sample_rate = s_per_sec;
		hold->byte_rate = b_per_sec;
		if(f_s==8){
			if(num_channels==2){
				hold->chunk_size = blen/2;           // size of this chunk in bytes
				hold->sample_size = length/2;        // size of entire linked sample
			} else {
				hold->chunk_size = blen;           // size of this chunk in bytes
				hold->sample_size = length;        // size of entire linked sample
			}
		} else {
			if(num_channels==2){
				hold->chunk_size = blen/4;         // size of this chunk in bytes
				hold->sample_size = length/4;      // size of entire linked sample
			} else {
				hold->chunk_size = blen/2;         // size of this chunk in bytes
				hold->sample_size = length/2;      // size of entire linked sample
			}
		}
		hold->stereo = (num_channels == 2);
		hold->loaded = 1;
		hold->head = newwave;                // points to top link.

																				 // Allocate next link
		if(l-blen > 0) {
			hold->next = (WAVE  *)VMALLOC(sizeof(WAVE));
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
		if (f_s == 16)
			VFREE(tempdata);
	}

	fclose(input);                            // Wrap it up
	wave_id --;
	return(newwave); */

}


/**************************************************************************
	WAVE *LoadWaveFromMemory(WAVE VFAR *w,SAMPLE *data, LONG l)

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
WAVE *LoadWaveFromMemory(WAVE *w,SAMPLE *data, LONG l)
{
	WAVE *nw,*hold;
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
		nw->id = wave_id;                // Give it a handle
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
}


/**************************************************************************
  void FreeWave(WAVE  *w)

  DESCRIPTION:  Frees all the memory associated with a sound effect.

  INPUTS:
    w   pointer to wave structure

**************************************************************************/
void FreeWave(WAVE  *wav)
{
  SOUNDEFFECT *s;
  WAVE  *hold;

  if (!wav || !wav->loaded) return;

  for (s=soundlist; s && s->wav != wav; s=s->next);
  if (s)
    WaveCommand (s->handle, v_remove);

  while(wav){                         // We are going to free the whole list
    if(wav->data) VFREE(wav->data);     // Free sound data
    hold = wav;
    wav = wav->next;                    // move down
    VFREE(hold);                    // Free the struct
  }
}

/**************************************************************************
  void initwav(void)

  DESCRIPTION:  Initializes all of the wav stuff to prepare for fresh
                Wave playing.

**************************************************************************/
void initwav(void)
{
  int i;
                                        // Set up sound tokens
  for(i = 0; i < MAXSOUNDTOKENS; i++) soundtoken[i].type = v_unused;
  soundlist = NULL;                     // Make sure list is empty
  sounds_in_queue=0;
  sound_handle=1;
}

