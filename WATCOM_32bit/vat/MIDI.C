/**************************************************************************
                        VARMINT'S AUDIO TOOLS 1.1

  MIDI.C

    This file contains source code far all MIDI related functions in VAT.


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
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <malloc.h>
#include <string.h>
#include "vat.h"
#include "internal.h"


#define TD        (midi_data->track[tracknum] + midi_trackloc[tracknum])
#define	debugf nullf

//-------------------------------- internal functions

LONG readlong(FILE *infile);
SHORT readvarlen(BYTE *data,LONG *value);
SHORT readshort(FILE *infile);
void initmid(void);


//-------------------------------- External functions used locally

void dbprintf(CHAR *string,...);
void vdisable(void);
void venable(void);
void makedefaultpatches(void);


//-------------------------------- External Variables

extern VATSTATUS     	internal_status;
extern SHORT         	midi_callfreq,vat_stereo;
extern DWORD         	internal_sample_rate;
extern VATSTATUS     	fm_status, mpu_status;
extern PATCH					defaultinstrument;
extern PATCH					defaultdrum;


//-------------------------------- MIDI/MPU varaibles

DWORD mididebugtimer;
static VATSTATUS     midi_status=v_nonexist;
static MIDI         *midi_data = NULL;
static SHORT         midi_reset = v_true;
static volatile SHORT         midi_on = v_false;
SHORT         midi_usertempo = 100;
SHORT         midi_tempoadjust = 256;
static BYTE          midi_volume = 32;
BYTE          default_patchmap[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
BYTE         *midi_patchmap;
BYTE         *midi_fmpatchmap;
SHORT         midi_fmpatchmapoverride=v_false;
BYTE          default_fmpatchmap[MAXMIDITRACKS];
LONG					midi_track_instrument[MAXMIDITRACKS];


VOICE         midi_voice[MAXSTOREDVOICES];
BYTE          midi_lastevent[MAXMIDITRACKS];
BYTE          midi_trackon[MAXMIDITRACKS];
WORD          midi_trackloc[MAXMIDITRACKS];
LONG          midi_timer[MAXMIDITRACKS];
SHORT         midi_divisions = 96;
SHORT         midi_msperdiv=5000;
SHORT         midi_livetracks;
SHORT					fmchannelreserved[9] = {0,0,0,0,0,0,0,0,0};

PATCH				 *midi_instrument_patch[128];
PATCH				 *midi_percussion_patch[128];

INSTRUMENT   *midi_instruments;
INSTRUMENT    default_instruments[128] = {
  {{0x30,0x30,0x40,0x00,0xE1,0xE2,0xDD,0xD3,0x00,0x01,0x00}, "Acoustic Grand Piano"},
  {{0x30,0x31,0x40,0x00,0xE1,0xE3,0xDD,0xD3,0x00,0x01,0x00}, "Bright Acoustic Piano"},
  {{0x30,0x30,0x40,0x00,0xE1,0xE2,0xDD,0xD3,0x04,0x01,0x00}, "Electric Grand Piano"},
  {{0x31,0x30,0x40,0x00,0xE1,0xE2,0xDD,0xD3,0x04,0x01,0x00}, "Honky-Tonk Piano"},
  {{0x30,0x30,0x40,0x00,0xE1,0xE2,0x87,0x63,0x06,0x01,0x00}, "Rhodes Piano"},
  {{0x30,0x33,0x40,0x00,0xE1,0xE2,0x87,0x63,0x06,0x01,0x00}, "Chorused Piano"},
  {{0x03,0x01,0x00,0x00,0xF3,0xE4,0x64,0x35,0x00,0x01,0x00}, "Harpsichord"},
  {{0x01,0x11,0x49,0x02,0xF1,0xF1,0x53,0x74,0x06,0x01,0x02}, "Clavinet"},
  {{0x16,0x11,0x4F,0x0A,0xF2,0xF2,0x61,0x74,0x08,0x00,0x00}, "Celesta"},
  {{0x34,0x36,0x00,0x00,0xB3,0xD3,0xC3,0xB3,0x02,0x01,0x00}, "Glockenspeil"},
  {{0x35,0x35,0x00,0x00,0xF3,0xF3,0xC3,0xB3,0x01,0x01,0x00}, "Music Box"},
  {{0xB1,0xB1,0x00,0x00,0xA3,0xB3,0xC3,0xB3,0x01,0x01,0x00}, "Vibraphone"},
  {{0x85,0x81,0x4D,0x80,0xDA,0xF9,0x16,0x05,0x0A,0x00,0x00}, "Marimba"},
  {{0x05,0xC4,0x05,0x00,0xFE,0xF8,0x65,0x85,0x0E,0x00,0x00}, "Xylophone"},
  {{0x13,0x01,0x4F,0x10,0xF2,0xF2,0x60,0x72,0x08,0x00,0x00}, "Tubular Bells"},
  {{0x03,0x17,0x4F,0x0B,0xF1,0xF2,0x53,0x74,0x06,0x00,0x00}, "Dulcimer"},
  {{0x64,0x21,0x86,0x80,0xFF,0xFF,0x0F,0x0F,0x01,0x00,0x00}, "Hammond Organ"},
  {{0x24,0x21,0x80,0x80,0xFF,0xFF,0x0F,0x0F,0x01,0x00,0x00}, "Percussive Organ"},
  {{0x72,0x71,0x00,0x00,0x80,0x80,0xC3,0xB3,0x01,0x01,0x00}, "Rock Organ"},
  {{0xB2,0xB0,0x43,0x00,0x9F,0x95,0x06,0x0F,0x09,0x04,0x01}, "Pipe Organ"},
  {{0x01,0x33,0x4F,0x05,0xF0,0x90,0xFF,0x0F,0x06,0x00,0x00}, "Reed Organ"},
  {{0x24,0x31,0x4F,0x10,0xF2,0x52,0x0B,0x0B,0x04,0x01,0x00}, "Accordian"},
  {{0x21,0xA2,0x15,0x80,0x61,0x62,0x03,0x67,0x04,0x00,0x00}, "Harmonica"},
  {{0xE1,0xE1,0xD0,0x00,0xF5,0xF4,0xAF,0x0F,0x0C,0x00,0x01}, "Tango Accordian"},
  {{0x13,0x11,0x96,0x80,0xFF,0xFF,0x21,0x03,0x0A,0x00,0x00}, "Acoustic Guitar (Nylon)"},
  {{0x11,0x11,0x8D,0x80,0xFF,0xFF,0x01,0x03,0x00,0x00,0x00}, "Acoustic Guitar (Steel)"},
  {{0x03,0x11,0x5E,0x00,0xF5,0xF2,0x71,0x83,0x0E,0x01,0x00}, "Electric Guitar (Jazz)"},
  {{0x21,0x06,0x40,0x85,0xF1,0xF4,0x31,0x44,0x00,0x00,0x00}, "Electric Guitar (Clean)"},
  {{0x01,0x01,0x11,0x00,0xF2,0xF5,0x1F,0x88,0x08,0x00,0x00}, "Electric Guitar (Muted)"},
	{{0x31,0x32,0x48,0x00,0xF1,0xF2,0x53,0x27,0x06,0x00,0x02}, "Overdriven Guitar"},
  {{0x61,0xE6,0x40,0x03,0x91,0xC1,0x1A,0x1A,0x08,0x00,0x00}, "Distortion Guitar"},
  {{0xC8,0xC4,0x12,0x03,0x73,0xF4,0xBF,0x9F,0x08,0x00,0x00}, "Guitar Harmonics"},
  {{0x00,0x01,0x00,0x00,0x94,0x83,0xB6,0x26,0x01,0x00,0x00}, "Acoustic Bass"},
  {{0x00,0x00,0x62,0x00,0xC1,0xF3,0xEE,0xDE,0x0A,0x00,0x00}, "Electric Bass (Finger)"},
  {{0x10,0x00,0x00,0x00,0xFB,0xF3,0x71,0xB9,0x00,0x00,0x00}, "Electric Bass (Pick)"},
  {{0x31,0x22,0x1E,0x00,0xF2,0xF5,0xEF,0x78,0x00,0x00,0x00}, "Fretless Bass"},
  {{0x31,0x23,0x0B,0x00,0x72,0xD5,0xB5,0x98,0x08,0x01,0x00}, "Slap Bass 1"},
  {{0x31,0x22,0x10,0x04,0x83,0xF4,0x9F,0x78,0x0A,0x00,0x00}, "Slap Bass 2"},
  {{0x11,0x31,0x05,0x00,0xF9,0xF1,0x25,0x34,0x0A,0x00,0x00}, "Synth Bass 1"},
  {{0x01,0x11,0x0F,0x00,0xD5,0x85,0x24,0x22,0x0A,0x00,0x00}, "Synth Bass 2"},
  {{0x43,0x03,0x40,0x00,0x80,0x80,0x82,0xF5,0x00,0x01,0x00}, "Violin"},
  {{0x42,0x02,0x40,0x00,0x80,0x80,0x82,0xF5,0x00,0x01,0x00}, "Viola"},
  {{0x40,0x00,0x40,0x00,0x80,0x80,0x82,0xF5,0x00,0x01,0x00}, "Cello"},
  {{0xC1,0xC1,0xCA,0x80,0x72,0x61,0x75,0xFE,0x06,0x00,0x01}, "Contrabass"},
  {{0xB1,0x61,0x8B,0x80,0x71,0x42,0x21,0x25,0x06,0x00,0x01}, "Tremolo Strings"},
  {{0x31,0x31,0x5A,0x80,0xF1,0xF7,0xA7,0xC6,0x06,0x03,0x03}, "Pizzicato Strings"},
  {{0x02,0x11,0x60,0x40,0xF5,0xF2,0x71,0x83,0x04,0x01,0x00}, "Orchestral Harp"},
  {{0x10,0x11,0x25,0x80,0xF0,0xF0,0x05,0x04,0x0A,0x00,0x00}, "Timpani"},
  {{0x21,0xA2,0x16,0x07,0x70,0x73,0x81,0x2C,0x06,0x01,0x01}, "String Ensemble 1"},
  {{0xB1,0x61,0x8B,0x40,0x51,0x42,0x11,0x15,0x06,0x00,0x01}, "String Ensemble 2"},
  {{0x31,0x62,0x1A,0x40,0x75,0x54,0x03,0x44,0x06,0x01,0x00}, "Synth Strings 1"},
  {{0xB3,0x61,0x5C,0x00,0x51,0x54,0x00,0x65,0x04,0x01,0x02}, "Synth Strings 2"},
  {{0x41,0xC2,0x4F,0x40,0x71,0x62,0x53,0x7C,0x08,0x00,0x00}, "Choir Ahhs"},
  {{0x60,0xE2,0xA7,0x81,0x22,0x10,0xD6,0x75,0x01,0x00,0x00}, "Voice Oohs"},
  {{0x41,0x41,0x4F,0x10,0xF1,0xF2,0x73,0x74,0x06,0x01,0x00}, "Synth Voice"},
  {{0xC1,0xC1,0x0F,0x00,0x91,0x62,0x06,0x05,0x0C,0x01,0x02}, "Orchestra Hit"},
  {{0x31,0x61,0x1C,0x80,0x61,0x62,0x1F,0x3B,0x00,0x01,0x00}, "Trumpet"},
  {{0xB1,0x61,0x1C,0x80,0x41,0x92,0x0B,0x3B,0x08,0x01,0x00}, "Trombone"},
  {{0x60,0x00,0x1D,0x00,0x52,0x73,0x68,0x76,0x09,0x01,0x00}, "Tuba"},
  {{0x21,0x31,0x59,0x80,0x43,0x85,0x8C,0x2F,0x06,0x01,0x00}, "Muted Trumpet"},
  {{0x20,0x30,0x9F,0xC0,0x53,0xAA,0x1A,0x5A,0x09,0x00,0x00}, "French Horn"},
  {{0xB1,0x61,0x95,0x8A,0x41,0x92,0xF6,0xF6,0x06,0x01,0x00}, "Brass Section"},
  {{0x21,0x21,0x8E,0x80,0xBB,0x90,0x29,0x0A,0x08,0x00,0x00}, "Synth Brass 1"},
  {{0xA1,0xA1,0x56,0x8A,0x71,0x81,0xAE,0x9E,0x06,0x01,0x00}, "Synth Brass 2"},
  {{0x01,0x12,0x63,0x00,0x71,0x52,0x53,0x7C,0x0A,0x00,0x00}, "Soprano Sax"},
  {{0x01,0x12,0x4F,0x00,0x71,0x52,0x53,0x7C,0x0A,0x00,0x00}, "Alto Sax"},
	{{0x21,0x32,0x4E,0x00,0x71,0x52,0x68,0x5E,0x0A,0x00,0x00}, "Tenor Sax"},
  {{0x11,0x12,0x56,0x00,0x71,0x52,0x5B,0x7B,0x0A,0x00,0x00}, "Baritone Sax"},
  {{0x21,0x24,0x94,0x05,0xF0,0x90,0x09,0x0A,0x08,0x00,0x00}, "Oboe"},
  {{0xB1,0xA1,0xC5,0x80,0x6E,0x8B,0x17,0x0E,0x02,0x00,0x00}, "English Horn"},
	{{0x31,0x32,0xD1,0x80,0xD5,0x61,0x19,0x1B,0x0C,0x00,0x00}, "Bassoon"},
	{{0x32,0x61,0x9A,0x82,0x51,0xA2,0x3B,0x3B,0x08,0x01,0x00}, "Clarinet"},
  {{0xA3,0xA3,0xDD,0x05,0xBF,0x50,0xF4,0xFA,0x00,0x00,0x00}, "Piccolo"},
  {{0xA1,0xA1,0xDD,0x05,0xBF,0x50,0xF4,0xFA,0x00,0x00,0x00}, "Flute"},
  {{0xA2,0xA2,0xDD,0x05,0x96,0x50,0x24,0x9A,0x00,0x00,0x00}, "Recorder"},
  {{0xA2,0xA1,0x52,0x8B,0xF5,0x61,0x30,0x3A,0x04,0x00,0x00}, "Pan Flute"},
  {{0xE2,0x61,0x6D,0x00,0x57,0x57,0x04,0x77,0x0C,0x00,0x00}, "Bottle Blow"},
  {{0xF1,0xE1,0x28,0x00,0x57,0x67,0x34,0x5D,0x0E,0x03,0x00}, "Shakuhachi"},
  {{0xF4,0xF3,0x9A,0x80,0xEC,0x60,0xC7,0xA5,0x0D,0x00,0x00}, "Whistle"},
  {{0x02,0x11,0x4F,0x05,0x71,0x52,0x53,0x7C,0x0A,0x00,0x00}, "Ocarina"},
  {{0x04,0x01,0x08,0x05,0xF8,0x82,0x07,0x74,0x08,0x00,0x00}, "Lead 1 (square)"},
  {{0x60,0x60,0x03,0x04,0xF6,0x76,0x4F,0x0F,0x02,0x00,0x00}, "Lead 2 (sawtooth)"},
  {{0x82,0xF1,0x0D,0x00,0x97,0x97,0x08,0x08,0x00,0x00,0x00}, "Lead 3 (calliope)"},
  {{0x51,0x01,0x80,0x00,0x55,0x55,0xF5,0xF5,0x08,0x00,0x00}, "Lead 4 (chiff)"},
  {{0x61,0x21,0x00,0x02,0x96,0x55,0x33,0x2B,0x06,0x00,0x00}, "Lead 5 (charang)"},
  {{0x51,0x41,0x0D,0x00,0xF2,0xF2,0xF2,0xF2,0x00,0x00,0x02}, "Lead 6 (voice)"},
  {{0x11,0x03,0x80,0x80,0xA3,0xA1,0xE1,0xE4,0x06,0x00,0x00}, "Lead 7 (fifths)"},
  {{0x11,0x31,0x05,0x00,0xF9,0xF1,0x25,0x34,0x0A,0x00,0x00}, "Lead 8 (bass + lead)"},
  {{0x71,0x23,0x00,0x00,0xF1,0xF4,0x45,0x44,0x05,0x01,0x00}, "Pad 1 (new age)"},
  {{0xE0,0xF0,0x16,0x03,0xB1,0xE0,0x51,0x75,0x00,0x02,0x02}, "Pad 2 (warm)"},
  {{0x51,0x01,0x03,0x08,0xFF,0xFF,0x02,0x02,0x04,0x01,0x00}, "Pad 3 (polysynth)"},
  {{0xE1,0xE1,0xD0,0x00,0xF5,0xF4,0xAF,0x0F,0x0C,0x00,0x01}, "Pad 4 (choir)"},
  {{0xF1,0xF1,0x46,0x80,0x22,0x31,0x11,0x2E,0x0C,0x01,0x00}, "Pad 5 (bowed)"},
  {{0x05,0x46,0x40,0x80,0xB3,0xF2,0xD3,0x24,0x02,0x00,0x00}, "Pad 6 (metallic)"},
  {{0x01,0x11,0x0D,0x80,0xF1,0x50,0xFF,0xFF,0x06,0x00,0x00}, "Pad 7 (halo)"},
  {{0x00,0x11,0x12,0x80,0x10,0x50,0xFF,0xFF,0x0A,0x00,0x00}, "Pad 8 (sweep)"},
  {{0xB4,0xF5,0x87,0x80,0xA4,0x45,0x02,0x42,0x06,0x00,0x00}, "FX 1 (rain)"},
  {{0xF1,0xF1,0x41,0x41,0x11,0x11,0x11,0x11,0x02,0x00,0x00}, "FX 2 (soundtrack)"},
  {{0x38,0x38,0x40,0x00,0x83,0x83,0xF2,0xF5,0x00,0x00,0x00}, "FX 3 (crystal)"},
  {{0x61,0x60,0x54,0x03,0x78,0xA2,0x00,0x47,0x06,0x01,0x02}, "FX 4 (atmosphere)"},
  {{0x40,0x08,0x0D,0x00,0xFF,0xFF,0x03,0x01,0x08,0x00,0x00}, "FX 5 (brightness)"},
  {{0x00,0x00,0x00,0x00,0x5F,0xFF,0x0F,0x05,0x00,0x00,0x00}, "FX 6 (goblins)"},
  {{0x21,0x21,0x56,0x00,0x7F,0x35,0x41,0x21,0x0E,0x00,0x00}, "FX 7 (echoes)"},
  {{0x71,0x31,0x00,0x40,0xF1,0xF1,0x01,0x01,0x04,0x03,0x00}, "FX 8 (sci-fi)"},
  {{0x01,0x08,0x40,0x40,0xF1,0xF1,0x53,0x53,0x00,0x00,0x00}, "Sitar"},
  {{0x21,0x12,0x47,0x80,0xA1,0x7D,0xC6,0x13,0x00,0x00,0x00}, "Banjo"},
  {{0x01,0x19,0x4F,0x00,0xF1,0xF2,0x53,0x74,0x06,0x00,0x00}, "Shamisen"},
  {{0x01,0x00,0x00,0x40,0xE7,0xE3,0xFB,0xF8,0x00,0x00,0x00}, "Koto"},
  {{0x02,0x01,0x99,0x80,0xF5,0xF6,0x55,0x53,0x00,0x00,0x00}, "Kalimba"},
  {{0x31,0x22,0x43,0x05,0x6E,0x8B,0x17,0x0C,0x02,0x01,0x02}, "Bagpipe"},
  {{0x31,0x62,0x1C,0x00,0x75,0x54,0x03,0x44,0x06,0x01,0x00}, "Fiddle"},
  {{0x80,0x95,0x4D,0x00,0x78,0x85,0x42,0x54,0x0E,0x00,0x00}, "Shanai"},
  {{0x07,0x08,0x48,0x80,0xF1,0xFC,0x72,0x04,0x00,0x00,0x00}, "Tinkle Bell"},
  {{0x0E,0x0E,0x00,0x00,0xF8,0xF8,0xF6,0xF6,0x00,0x00,0x00}, "Agogo"},
  {{0x02,0x00,0xC0,0x00,0x8F,0xFF,0x06,0x05,0x0A,0x01,0x00}, "Steel Drums"},
  {{0x02,0x02,0x00,0x00,0xC8,0xC8,0x97,0x97,0x01,0x00,0x00}, "Woodblock"},
  {{0x01,0x01,0x00,0x00,0xFF,0xFF,0x07,0x07,0x07,0x00,0x00}, "Taiko Drum"},
  {{0x01,0x01,0x00,0x00,0xD8,0xD8,0x96,0x96,0x0A,0x00,0x00}, "Melodic Tom"},
  {{0x06,0x00,0x00,0x00,0xF0,0xF6,0xF0,0xB4,0x0E,0x00,0x00}, "Synth Drum"},
  {{0x01,0x01,0x80,0x80,0x5F,0x5F,0x0B,0x0B,0x04,0x01,0x01}, "Reverse Cymbal"},
  {{0x51,0x42,0x00,0x05,0x66,0x66,0x05,0x06,0x00,0x02,0x00}, "Guitar Fret Noise"},
  {{0x53,0x00,0x05,0x00,0x5F,0x7F,0x66,0x07,0x06,0x00,0x00}, "Breath Noise"},
  {{0x0E,0x0E,0x00,0x00,0x20,0x21,0x00,0x01,0x0E,0x00,0x00}, "Seashore"},
  {{0xC0,0x7E,0x4F,0x0C,0xF1,0x10,0x03,0x01,0x02,0x00,0x00}, "Bird Tweet"},
  {{0xF4,0xF3,0x50,0x80,0x85,0x74,0x87,0x99,0x0C,0x00,0x00}, "Telephone Ring"},
  {{0xF0,0xE2,0x00,0xC0,0x1E,0x11,0x11,0x11,0x08,0x01,0x01}, "Helicopter"},
  {{0x7E,0x6E,0x00,0x00,0xFF,0x3F,0x0F,0x0F,0x0E,0x00,0x00}, "Applause"},
  {{0x06,0x84,0x00,0x00,0xA0,0xC5,0xF0,0x75,0x0E,0x00,0x00}, "Gunshot"}};

/**************************************************************************
	void nullf(CHAR *string,...)

	DESCRIPTION:  For yuks

**************************************************************************/
void nullf(CHAR *string,...)
{
	va_list ap;

//  _disable();

	va_start(ap, string);                  // sort out variable argument list
//	printf(string,ap);
	va_end(ap);                            // clean up
//  _enable();
}


/**************************************************************************
  VATBOOL MidiCommand(VATCOMMAND c)

  DESCRIPTION:  Simple Interface for working With Midi playback

  INPUTS:
    c           VAT command (See sound.h)

**************************************************************************/
VATBOOL MidiCommand (VATCOMMAND cmd)
{
  SHORT i;

  // check for a current s3m
  if (midi_status == v_nonexist)
    return v_false;

  // process command
  switch (cmd) {
  case v_remove:
    if (midi_status != v_nonexist) {
      midi_on = v_false;         /* turn off */
      midi_data = NULL;
      midi_status = v_nonexist;
      for (i=0; i<9; i++)
        FMVolume (i, 0);
    }
    break;
  case v_play:
		if (midi_status == v_stopped ||
        midi_status == v_paused) {
      midi_on = v_true;          /* start or resume playing */
      midi_status = v_started;
//      MilliDelay(50);  // why? seems to work fine without..
    }
    break;
	case v_stop:
    if (midi_status == v_started ||
        midi_status == v_paused) {
			midi_on = v_false;         /* stop and reset */
      midi_reset = v_true;
			midi_status = v_stopped;
//			for (i=0; i<9; i++)
//				FMVolume (i, 0);
			for(i = 0; i < MAXSTOREDVOICES; i++) stopvoice(i);
    }
    break;
  case v_pause:
    if (midi_status == v_started) {
      midi_on = v_false;         /* set inactive */
      midi_status = v_paused;
    }
    break;
  case v_rewind:
    if (midi_status == v_started ||
        midi_status == v_paused) {
      midi_reset = v_true;        /* reset without altering state */
    }
    break;
  default:
    return v_false;              /* invalid command */
  }

  // return confirmation
  return v_true;
}



/**************************************************************************
	int MidiSetting (VATSETTING set, int value)

	DESCRIPTION:

**************************************************************************/
int MidiSetting (VATSETTING set, int value)
{
  // no checks for current midi before processing, too many loopholes

  // process setting
  switch (set) {
  case v_volume:
    if (value == GET_SETTING)
      value = midi_volume;
    else {
      if (value < 0)             /* limit volume to 0 - 63 */
        value = 0;
      else if (value > 63)
        value = 63;
      midi_volume = value;
    }
    break;
  case v_repeat:
    if (!midi_data)              /* check for current midi */
      return -1;
    if (value == GET_SETTING)
      value = midi_data->repeat;
    else
      midi_data->repeat = value;  /* negative is unterminating */
    break;
  case v_rate:
    // no checks here, let them set it to what they like even though
    // if there's no current midi it'll be reset as soon as there is one
    if (value == GET_SETTING)
      value = midi_usertempo;
    else {
      if (value < 10)            /* limit rate to 10 - 9999 */
        value = 10;
      else if (value > 9999)
        value = 9999;
      midi_usertempo = value;
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
	SHORT getvoice(SHORT track,SHORT channel, SHORT note)

  DESCRIPTION: Find the first matching voice (or first inactive voice if
								a match is not found).

	INPUTS:
		track     MIDI track that is generating this request
		channel   MIDI channel that is generating this request
		note      MIDI note requested

	RETURNS:
		Open number if successful, -1 if not.
**************************************************************************/
SHORT getvoice(SHORT track,SHORT channel, SHORT note)
{
	SHORT i;


	for(i = 0; i < MAXSTOREDVOICES; i++) {   // find matching active note
		if(midi_voice[i].active) {
			if(midi_voice[i].owner_track == track &&
				 midi_voice[i].owner_channel == channel &&
				 midi_voice[i].note == note) return(i);
		}
	}
																	// no note, so find first inactive voice

	for(i = 0; i < MAXSTOREDVOICES; i++) {
		if(!midi_voice[i].active) return(i);
	}

																	// no available voices... error
	return -1;
}



/**************************************************************************
	void stopvoice(int v)

	DESCRIPTION:  Turns off and deactivates a voice

**************************************************************************/
void stopvoice(int v)
{

	if(v == -1) return;

	midi_voice[v].active = v_false;

																 // Stop an FM voice
	if(midi_voice[v].type == v_fm_voice) {
		if(midi_voice[v].handle < 9 && midi_voice[v].handle >=0) {
			FMKeyOff (midi_voice[v].handle);
			FMVolume (midi_voice[v].handle, 0);
			fmchannelreserved[midi_voice[v].handle] = 0;
		}
	}
																 // Stop a gravis patch voice
	else if(midi_voice[v].type == v_patch) {
		NoteCommand(midi_voice[v].handle,v_stop);
	}
}

/**************************************************************************
	void startvoice(int v)

	DESCRIPTION:  Turns on and activates a voice

**************************************************************************/
void startvoice(int v)
{
	int inst,note,i;


	if(v == -1) return;
															 // pick the instrument
	inst = midi_track_instrument[midi_voice[v].owner_track];
															 // If an instrumentis not specified,
															 // pick the one from the most recent
															 // track with an instrument
	if(inst < 0) {
		for(i = midi_voice[v].owner_track; i >= 0; i--) {
			if(midi_track_instrument[i] > -1) {
				inst = midi_track_instrument[i];
				break;
			}
		}
	}

	if(inst < 0) inst = 0;

	note = midi_voice[v].note;

	midi_voice[v].active = v_true;
	midi_voice[v].type = v_patch;
	if(midi_voice[v].owner_channel == 9) {
		midi_voice[v].handle = PlayNote(128, midi_percussion_patch[note]);
		NoteSetting (midi_voice[v].handle,v_volume ,
								 (midi_voice[v].volume * midi_volume) / 64);
	}
	else {
		midi_voice[v].handle = PlayNote(note,midi_instrument_patch[inst]);
		NoteSetting (midi_voice[v].handle,v_volume ,
								 (midi_voice[v].volume * midi_volume) / 64);
	}



	/*
								if (fm_status != v_started)
									midi_voice[vidx].volume = 0;
								midi_voice[vidx].active = v_true;
								if(vidx < 9) {
									FMNote (vidx, b1);
									j = (midi_volume * midi_voice[vidx].volume/2) >> 4  ;
									if(j > 63) j = 63;
									FMVolume (vidx, j);
									FMSetVoice(vidx,midi_instruments[midi_fmpatchmap[tracknum]].data);
									FMKeyOn(vidx);
								}
	*/
}


/**************************************************************************
	midiplayer()

  DESCRIPTION: Routine for playing midi files.  THis is designed to be
               called from a timer interrupt.  To use, set these values
               in this order:

                   midi_data    (must point to a filled MIDI structure.)
                  midi_reset = v_true;
									midi_on = v_true;

               The interrupt should pick up from there.

               It is easy to add functionality to this routine.  I've
							 already included code to flag a wide variety of MIDI
               events, so all you have to do is add your own code under
               the point an event is flagged.  I've left a bunch of
               commented print statements in to help make the code
               more readable and provide cues for accessing the data.


               ***  WARNING  ***

               If you add your own code here, make sure that it doesn't
               take more than a few milliseconds to execute.  If
							 midiplayer() is called again by the interrupt before your
							 code is done, your whole program will probably crash.

**************************************************************************/
void midiplayer(void)
{
	static SHORT spot,tracknum,j,vidx;
	BYTE event,ev,ch,b1,b2,etype;
	static LONG itmr,l2,length;
	CHAR tdata[256];


	if(!midi_data) {                        // must have data to play!
		midi_on = v_false;
		return;
	}

	if(midi_reset) {                        // Reset?  zero track pointers and timers
																					// Shut off all the voices
		for(j = 0; j < MAXSTOREDVOICES; j++) {
			if(midi_voice[j].active) stopvoice(j);
		}

		for(j = 0; j < MAXMIDITRACKS; j++ ) {
			midi_trackloc[j] = 1;               // no need to read first time offset
			midi_timer[j] = 0;                  // all timers start at zero
			midi_trackon[j] = v_true;
			midi_lastevent[j] = 0x80;           // set last event to note off
			midi_track_instrument[j] = -1;      // default to Grand piano
		}
		midi_usertempo = 100*(vat_stereo+1);
		midi_reset = 0;                       // clear midi reset flag
		midi_livetracks = midi_data->num_tracks;// set number of active tracks so
																					// we know when to stop.
		midi_divisions = midi_data->divisions;// ticks per quarter note
		if(midi_divisions < 0) midi_divisions = -midi_divisions;  // some midi files have
																					// negative division values
		if(!midi_divisions) midi_divisions = 96; // Pick a default if they give us a zero
	}

	if(!midi_on) return;                    // logical switch for midi on/off
																					// loop over tracks
	for(tracknum = 0 ; tracknum < midi_data->num_tracks; tracknum++) {
		while(midi_timer[tracknum] <= 0) {           // Process while timer is 0;
			event = *TD;                      // get next event (TD is a macro)
			midi_trackloc[tracknum]++;                 // advance track location pointer

			if(event == 0xFF) {                 // META event?
				etype = *TD;
				midi_trackloc[tracknum] ++;
																					// read length of meta event
				spot = readvarlen(TD,&length);
				midi_trackloc[tracknum] += spot;
																					// grab any text data for text events
				for(j = 0; j < length; j++) tdata[j] = *(TD + j);
				tdata[j] = 0;

				switch(etype) {
					case 0x00:
						j = *TD*256 + *(TD+1);
						//printf("[%d] SEQUENCE NUMBER (%d)\n",tracknum,j);
						break;
					case 0x01:
						//printf("[%d] TEXT EVENT (%s)\n",tracknum,tdata);
						break;
					case 0x02:
						//printf("[%d] COPYWRITE EVENT (%s)\n",tracknum,tdata);
						break;
					case 0x03:
						//printf("[%d] TRACK NAME EVENT (%s)\n",tracknum,tdata);
						break;
					case 0x04:
						//printf("[%d] INSTRUMENT NAME EVENT (%s)\n",tracknum,tdata);
						break;
					case 0x05:
						//printf("[%d] LYRIC EVENT (%s)\n",tracknum,tdata);
						break;
					case 0x06:
						//printf("[%d] MARKER EVENT (%s)\n",tracknum,tdata);
						break;
					case 0x07:
						//printf("[%d] CUE EVENT (%s)\n",tracknum,tdata);
						break;
					case 0x2f:                       // End of track
						//printf("[%d] END OF TRACK\n",tracknum);
						midi_timer[tracknum] = 2147000000L;    // set timer to highest value
						midi_trackon[tracknum] = v_false;        // turn off track
						midi_livetracks--;              // decrement track counter
						if (midi_livetracks == 0) {      // last track?  Turn off midi!
							midi_on = v_false;
							midi_reset = v_true;
							midi_status = v_stopped;
							if (midi_data->chainfunc) { // Check for a chain function
								midi_data->chainfunc ();
								midi_data->chainfunc = NULL;
							}
							if (midi_data->chain) {      // Check for a chain
								midi_data = midi_data->chain;
								midi_data->chain = NULL;
								midi_on = v_true;
								midi_status = v_started;
							} else if (midi_data->repeat) {  // repeat?
								if (midi_data->repeat > 0)
									midi_data->repeat--;
								midi_on = v_true;
								midi_status = v_started;
              }
							return;
            }
            break;
          case 0x51:                   // TEMPO event (microsecs per 1/4 note)
						l2 = *TD * 0x10000L + *(TD+1) * 0x100 + *(TD+2);
						//printf("[%d] TEMPO EVENT (%ld)\n",tracknum,l2);
            midi_msperdiv = (SHORT)(l2/midi_divisions); // micro secnds/tick
                                       // Convert number to number of
                                       // sb interrupts per tick. (fixed poit)

            midi_callfreq = (WORD)(256L*(((LONG)midi_msperdiv *
                      (LONG)internal_sample_rate) / 1000000L)/ (LONG)dma_bufferlen);
            break;
					case 0x58:
						//printf("[%d] TIME SIG EVENT (%X,%X,%X,%X)\n",tracknum,
						//				*TD,*(TD+1),*(TD+2),*(TD+3));
            break;
          case 0x59:
						//printf("[%d] KEY SIG EVENT (%X,%X)\n",tracknum,*TD,*(TD+1));
            break;
          case 0x7F:
						//printf("[%d] SEQUENCER DATA EVENT\n",tracknum);
						break;
          default:
						//printf("[%d] *** undefined event *** (%X,type: %X,length %ld)\n",tracknum,event,etype,length);
            break;
        }
				midi_trackloc[tracknum] += (WORD)length;
      }
			else if(event == 0xF0 || event == 0xF7) { // sysex event
				midi_trackloc[tracknum] += readvarlen(TD,&length);
				//printf("Sysex type 1 [length: %ld]\n",length);
				midi_trackloc[tracknum] += (WORD)length;
			}
			else {                                // PROCESS MIDI EVENTS

				MicroDelay(10);                     // Don't ask me why, but this
																						// dang code crashes if this
																						// delay is not here.

				if(!(event & 0x80)) {               // top bit Not set? Running status!

					b1 = event;                       // b1 = note   (usually)
					b2 = *TD;                       // b2 = volume? (usually)


					event = midi_lastevent[tracknum];        // use last event
					//printf("Running status >>");
					//for(j = 0; j < 9; j++) printf("%d",midi_voice[j].active);
					//printf("\n");
					midi_trackloc[tracknum] --;              // one less byte for running status.

					if (mpu_status == v_started) {
						ev = event & 0xF0;
						MPUWrite(event);
						MPUWrite(b1);
						if(ev != 0xC0 && ev != 0xD0) MPUWrite(b2);
					}
				}
				else {                              // Else it was a regular event
					ch = event & 0x0f;
					ev = event & 0xF0;
					event = ev + midi_patchmap[ch];

					midi_lastevent[tracknum] = event;        // set to last event
					b1 = *TD;                       // get next two bytes
					b2 = *(TD+1);
					if (mpu_status == v_started) {
						MPUWrite(event);
						MPUWrite(b1);
						if(ev != 0xC0 && ev != 0xD0) MPUWrite(b2);
					}
				}
				ev = event & 0xF0;                  // strip lower four bits
				ch = event & 0x0f;                  // get channel from low bits
				vidx = getvoice(tracknum,ch,b1);    // Get a voice index
				switch(ev) {
					case 0x80:                        // Note off
						//printf("[%d] Note off (%d,%d)\n",tracknum,b1,b2);
						midi_trackloc[tracknum] += 2;
						stopvoice(vidx);
						break;
					case 0x90:                        // Note On
						//printf("[%d] Note on (%X,%d,%d)\n",tracknum,event,b1,b2);
						//printf("%X",ch);
						midi_trackloc[tracknum] += 2;
						if(vidx > -1) {                 // Voice found?
							if(midi_voice[vidx].active) { // already active? Turn it off.
								stopvoice(vidx);
							}
							else {                   // Wasn't active?  Turn it on.
								midi_voice[vidx].owner_track = tracknum;
								midi_voice[vidx].owner_channel = ch;
								midi_voice[vidx].note = b1;
								midi_voice[vidx].volume = b2;
								startvoice(vidx);

							}
						}
						break;
					case 0xA0:                   // Key pressure
						//printf("[%d] Note presure (%d,%d)\n",tracknum,b1,b2);
						midi_trackloc[tracknum] += 2;
						break;
					case 0xB0:                   // Control CHange
						//printf("[%d] Control Change (%d,%d)\n",tracknum,b1,b2);
						midi_trackloc[tracknum] += 2;
						break;
					case 0xC0:                   // Program change
						//printf("[%d] Program change (%d)\n",tracknum,b1);
						if(!midi_fmpatchmapoverride)midi_fmpatchmap[tracknum]=b1;
						midi_track_instrument[tracknum] = b1;
						midi_trackloc[tracknum] += 1;
						break;
					case 0xD0:                   // Channel Pressure
						//printf("[%d] Channel Pressure (%d,%d)\n",tracknum,b1);
						midi_trackloc[tracknum] += 1;
						break;
					case 0xE0:                   // Pitch wheel change
						//printf("[%d] Pitch change (%d,%d)\n",tracknum,b1,b2);
						midi_trackloc[tracknum] += 2;
						break;
					default:                     // Uh-OH
						//printf("MIDI ERROR (F0 midi command)\n");
						midi_on = v_false;
						return;
				}

			}

																				 // read next time offset
			if(midi_trackon[tracknum]) {
				midi_trackloc[tracknum] += readvarlen(TD,&itmr);
				midi_timer[tracknum] += itmr*256;
				//printf(" T: %ld\n",midi_timer[tracknum]);
			}
		}
		midi_timer[tracknum]-= midi_tempoadjust;   // decrement timer.
	}
}

/**************************************************************************
	MIDI  *LoadMidi(CHAR *filename, CHAR *errstring)

	DESCRIPTION: Reads a midi file and stores it to a MIDI data structure

	INPUTS:

    filename    Pointer to full midi filename
    errstring    Pointer to a pre-allocated string.

  RETURNS:
    returns point to MIDI structure if successful.
		NULL otherwise.

**************************************************************************/
MIDI  *LoadMidi(CHAR *midifile, CHAR *errstring)
{
	SHORT i;
  FILE *input;
  CHAR sdata[256];
  LONG lidata;
  SHORT idata;
  DWORD lread;
	MIDI  *mdata;
	void *stretchdata;
	CHAR *namestart;

	debugf("Entering LoadMidi\n");
  if (!midifile || !*midifile || !errstring) {
    if (errstring)
      sprintf (errstring, "Empty filename");
    return(NULL);
  }

  mdata = (MIDI  *)VMALLOC(sizeof(MIDI));    // make room for music!
  if(!mdata) {
    sprintf(errstring,"Out of memory.");
    return(NULL);
	}
	debugf("Initializing\n");

  mdata->chain = NULL;
  mdata->chainfunc = NULL;
	mdata->repeat = 0;
	for(i = 0; i < MAXMIDITRACKS; i++) {
		mdata->track[i] = NULL;
		mdata->tracksize[i] = 0;
	}

  input = fopen(midifile,"rb");            // open a midi file
	if(!input) {
    sprintf(errstring,"cannot open %s",midifile);
    return(NULL);
	}
	debugf("Starting File Read\n");
																					 // Read the header

  fread(sdata,1,4,input);                  // midi id there?
  sdata[4] = 0;
  if(strcmp(sdata,"MThd")) {
    sprintf(errstring,"Not a  midi file.");
    fclose(input);
    return(NULL);
	}

																		 // Create a default name
	namestart = strrchr(midifile,'\\');
	if(!namestart) namestart = midifile;
	else namestart++;
	strcpy(mdata->title,namestart);

  lidata = readlong(input);                // length of remaining header chunk?
  if(lidata > 250) {
		FreeMidi(mdata);
    sprintf(errstring,"Header chunk has a weird length");
    fclose(input);
    return(NULL);
  }
	debugf("Reading Header chunk (%d)\n",lidata);


	debugf("Checking format\n");
	idata = readshort(input);                // Read MIDI Format specifier
  if(idata != 0 && idata != 1) {
		FreeMidi(mdata);
    sprintf(errstring,"Unrecognized MIDI format");
    fclose(input);
    return(NULL);
  }

  mdata->format = idata;

	debugf("Format = %d\n",idata);

  idata = readshort(input);                // number of tracks
	if(idata < 1 || idata > MAXMIDITRACKS) {
		FreeMidi(mdata);
    sprintf(errstring,"Bad number of tracks [%d]",idata);
    fclose(input);
    return(NULL);
  }
	mdata->num_tracks = idata;
	debugf("Num tracks = %d\n",idata);

  idata = readshort(input);                // division number (tempo)
  mdata->divisions = abs(idata);
	debugf("Num divisions = %d\n",idata);


																					 // Read individual track data
  for(i = 0; i < mdata->num_tracks; i++) {
		debugf("  Reading Track %d ",i);
		fread(sdata,1,4,input);                // midi track id there?
    sdata[4] = 0;
    if(strcmp(sdata,"MTrk")) {
			FreeMidi(mdata);
      sprintf(errstring,"Error reading track #%d",i);
      fclose(input);
      return(NULL);
    }

    lidata = readlong(input);              // length of remaining track chunk?
		mdata->tracksize[i] = lidata;
		debugf("(%d bytes)",lidata);
																					 // Allocate space for track
		mdata->track[i] = (BYTE  *)VMALLOC(lidata);
    if(!mdata->track[i]) {
			FreeMidi(mdata);
      sprintf(errstring,"Out of memory.");
      fclose(input);
			return(NULL);
		}
		debugf("Pre");
																					 // read in entire track
		lread = fread(mdata->track[i],1,(size_t)lidata,input);
		debugf("-Post");
		if(lread < lidata) {
			debugf(" ERROR!");
			FreeMidi(mdata);
			sprintf(errstring,"Premature end of midi file [track %d]",i);
			fclose(input);
			return(NULL);
		}
		debugf(".\n");
	}

	debugf("Closing\n");
	fclose(input);
	debugf("Returning\n");
	return mdata;
}


/**************************************************************************
   SHORT readvarlen(CHAR *data,LONG *value)

  DESCRIPTION:  Reads a variable length long interger from data string.
                This functionis used by LoadMidi() to grab special numbers
                from MIDI data files.

  INPUTS:
    data    pointer to a character string that we want to convert
    value   pointer to variable where we will diump the value

  RETURNS:
    Number of bytes read.

**************************************************************************/
SHORT readvarlen(BYTE *data,LONG *value)
{
  SHORT i=0;
  BYTE c;

  if ((*value = *(data + i)) & 0x80) { // Process the variable length interger
    *value &= 0x7f;
    do {
      i++;
      *value = (*value << 7) + ((c = *(data +i)) & 0x7f);
    } while (c & 0x80);
  }
  return(i+1);                         // return number of bytes read
}


/**************************************************************************
  SHORT readshort(FILE *inflile)

  DESCRIPTION:  Reads a short interger from a file

  INPUTS:
    infile    pointer to an open file stream

  RETURNS:
    value of interger read

**************************************************************************/
SHORT readshort(FILE *infile)
{
  return (fgetc(infile) << 8) | fgetc(infile);
}

/**************************************************************************
  LONG readlong(FILE *inflile)

  DESCRIPTION:  Reads a long interger from a file

  INPUTS:
    infile    pointer to an open file stream

  RETURNS:
    value of interger read

**************************************************************************/
LONG readlong(FILE *infile)
{
  SHORT i;
  LONG num = 0;

  num = (BYTE)fgetc(infile);

  for(i = 0; i < 3; i++) {
    num = (num << 8) | (BYTE)fgetc(infile);
  }

  return(num);
}
/**************************************************************************
  void MIDIWrite(BYTE b)

  DESCRIPTION:  Writes a byte to the MIDI port using the DSP.

  INPUTS:
    b    byte to write to the MIDI port

**************************************************************************/
void MIDIWrite(BYTE b)
{
  DSPWrite(0x38);
  DSPWrite(b);                        // DSP Midi outport command
}                                     // Send the byte




/**************************************************************************
  INSTRUMENT *LoadInstruments (CHAR *filename)

  DESCRIPTION:  Loads instrument defs from a file (128 total)

    File format: 11 hex values followed by a name.  eg:

      30 33 40 00 E1 E2 87 63 06 01 00 "Electric Piano 2"
      33 34 00 00 92 C3 C3 B3 02 01 00 "Harpsichord"
			32 32 00 00 92 C3 C3 B3 02 01 00 "Clavichord"
      .
      .
      .

    (The text at the end is ignored.)

    The hex values are dumped into an 2-D array.  The file can have
    more or less than 128 defs without harm to this function.

  INPUTS:
    filename    pointer to a string with the instrument file name in it
    inst        pointer to a 2D instrument array (should be [128][11])

**************************************************************************/
INSTRUMENT *LoadInstruments (CHAR *filename)
{
  int indx, hex;
  CHAR line[256];
  FILE *input;
  INSTRUMENT *inst;

  // check filename validity
  if (!filename || !*filename)
    return NULL;

  // open the instrument file
  if (!(input = fopen (filename,"r")))
    return NULL;

  // allocate space for the returned instrument set
  inst = (INSTRUMENT *)calloc (128, sizeof (INSTRUMENT));

  // read the file with no content checking
  indx = 0;
  while (!feof (input) && fgets (line, sizeof (line), input)) {
    if (*line == '#')
      continue;
    for (hex=0; hex<11; hex++)
      sscanf (line + hex*3, "%X ", &inst[indx].data[hex]);
    memset (inst[indx].name, 0, sizeof (inst[indx].name));
    strcpy (inst[indx].name, line+33);
    indx++;
  }

  // close the instrument file and return the instrument set
  fclose (input);
  return (inst);
}


/**************************************************************************
	INSTRUMENT *MidiInstruments (INSTRUMENT *inst)

	DESCRIPTION:

**************************************************************************/
INSTRUMENT *MidiInstruments (INSTRUMENT *inst)
{
  int i;

  if (!inst)
    midi_instruments = default_instruments;
  else if (inst != GET_INSTRUMENTS)
    midi_instruments = inst;
  return midi_instruments;
}


/**************************************************************************
	BYTE *MidiPatchmap (BYTE *map)

	DESCRIPTION:

**************************************************************************/
BYTE *MidiPatchmap (BYTE *map)
{
  if (!map)
    midi_patchmap = default_patchmap;
  else if (map != GET_PATCHMAP)
    midi_patchmap = map;
  return midi_patchmap;
}


/**************************************************************************
  void FreeMidi(MIDI *m)

  DESCRIPTION: Frees the data allocated for a MIDI structure

  INPUTS:
    m   pointer to MIDI structure to free up

**************************************************************************/
void FreeMidi(MIDI *m)
{
  SHORT i;

  if (!m) return;

  if (m == midi_data)
    MidiCommand (v_remove);
  
	for(i = 0; i < m->num_tracks; i++) {
		if(m->track[i]) VFREE(m->track[i]);
	}
  VFREE(m);
}


/**************************************************************************
  void initmid(void)

  DESCRIPTION:  Sets up the midi stuff before any playing happens

**************************************************************************/
void initmid(void)
{
	int i;

	for(i = 0; i < MAXSTOREDVOICES; i++) {
		midi_voice[i].active = v_false;
	}

	midi_data=NULL;
	midi_patchmap = default_patchmap;
	midi_fmpatchmap = default_fmpatchmap;
	midi_callfreq = 256;
	midi_reset = v_true;
	midi_on = v_false;
	midi_usertempo = 100;
	midi_tempoadjust = 256;
	midi_volume = 32;
	midi_instruments = default_instruments;
	midi_status = v_nonexist;

	for(i = 0; i < 128; i++) {
		MidiSetInstrumentPatch(i,&defaultinstrument);
		MidiSetPercussionPatch(i,&defaultdrum);
	}

}

/*************************************************************************
  VATSTATUS MidiStatus(void)

  DESCRIPTION:  Checks the status of the currently playing loaded Midi.

*************************************************************************/
VATSTATUS MidiStatus(void)
{
  return midi_status;
}


/**************************************************************************
	void PlayMidi (MIDI *midi)

	DESCRIPTION:

**************************************************************************/
void PlayMidi (MIDI *midi)
{
  /* check VAT status */
  if (internal_status != v_started)
    return;

  if (MidiStatus () != v_nonexist)
    MidiCommand (v_remove);
  midi_data = midi;
  if (midi) {
    midi_reset = v_true;
    midi_status = v_stopped;
		MidiCommand (v_play);
  } else
    midi_status = v_nonexist;
}


/**************************************************************************
	VATBOOL MidiChain (MIDI *midi)

	DESCRIPTION:

**************************************************************************/
VATBOOL MidiChain (MIDI *midi)
{
  if (MidiStatus () == v_nonexist)
    return v_false;

  midi_data->chain = midi;
  return v_true;
}


/**************************************************************************
	VATBOOL MidiChainFunc (void (*func)(void))

	DESCRIPTION:

**************************************************************************/
VATBOOL MidiChainFunc (void (*func)(void))
{
  if (MidiStatus () == v_nonexist)
    return v_false;

  midi_data->chainfunc = func;
  return v_true;
}




/**************************************************************************
	VATBOOL MidiSetInstrumentPatch(int instrument, PATCH *p)

	DESCRIPTION:

**************************************************************************/
VATBOOL MidiSetInstrumentPatch(int instrument, PATCH *p)
{
	if(instrument < 0 || instrument > 127 || !p) return v_false;

	midi_instrument_patch[instrument] = p;

	return v_true;
}


/**************************************************************************
	PATCH *MidiGetInstrumentPatch(int instrument)

	DESCRIPTION:

**************************************************************************/
PATCH *MidiGetInstrumentPatch(int instrument)
{
	if(instrument < 0 || instrument > 127) return NULL;

	return midi_instrument_patch[instrument];
}

/**************************************************************************
	VATBOOL MidiSetPercussionPatch(int instrument, PATCH *p)

	DESCRIPTION:

**************************************************************************/
VATBOOL MidiSetPercussionPatch(int instrument, PATCH *p)
{
	if(instrument < 0 || instrument > 127 || !p) return v_false;

	midi_percussion_patch[instrument] = p;

	return v_true;
}


/**************************************************************************
	PATCH *MidiGetPercussionPatch(int instrument)

	DESCRIPTION:

**************************************************************************/
PATCH *MidiGetPercussionPatch(int instrument)
{
	if(instrument < 0 || instrument > 127) return NULL;

	return midi_percussion_patch[instrument];
}

/* this needs to be created sometime - there is no mechanism for it yet
LONG MidiChannelMask (LONG mask)
{
  int i;

  if (mask == GET_SETTING) {
    mask = 0;
    for (i=0; i<16; i++)
      if (midi_channelselect[i])
        mask |= (1<<i);
  } else if (mask < 0 || mask >= (1<<16))
    return -1;
  else
    for (i=0; i<16; i++)
      midi_channelselect[i] = ((mask & (1<<i)) == 1);
  return mask;
}
*/

