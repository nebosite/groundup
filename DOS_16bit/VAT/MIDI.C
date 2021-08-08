/**************************************************************************
												VARMINT'S AUDIO TOOLS 0.71

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
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <alloc.h>
#include <string.h>
#include "vat.h"


#define TD            midi_data->track[i] + midi_trackloc[i]

#define DOSYNC1  if(sync_on && inportb(0x3da)&0x08) vsyncclock = 1000

//-------------------------------- internal functions

LONG readlong(FILE *infile);
SHORT readvarlen(BYTE *data,LONG *value);
SHORT readshort(FILE *infile);
void initmid(void);


//-------------------------------- External functions used locally

void dbprintf(CHAR *string,...);
void vdisable(void);
void venable(void);


//-------------------------------- External Variables

extern SHORT         midi_callfreq,dma_bufferlen;
extern WORD          midi_mpuport;
extern SHORT         mpu_available;



//-------------------------------- MIDI/MPU varaibles

MIDI VFAR     *midi_data = NULL;
SHORT         midi_reset = TRUE;
SHORT         midi_on = FALSE;
SHORT         midi_mpuout = FALSE;
SHORT         midi_fmout = TRUE;
SHORT         midi_usertempo = 100;
SHORT         midi_tempoadjust = 256;
BYTE          midi_volume = 0x16;
BYTE          defaultpatchmap[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
SHORT					midi_fmpatchmapoverride = FALSE;
BYTE         *midi_patchmap;
BYTE         *midi_fmpatchmap;
BYTE          defaultfmpatchmap[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
																		 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
WORD          mpu_timeout;
SHORT         mpu_checked = FALSE;
VOICE         midi_voice[MAXSTOREDVOICES];
BYTE          midi_lastevent[32];
BYTE          midi_trackon[32];
WORD          midi_trackloc[32];
LONG          midi_timer[32];
SHORT         midi_divisions = 96;
SHORT         midi_msperdiv=5000;
SHORT         midi_livetracks;
BYTE          midi_instrument[128][11]= {        // General midi instruments
	{0x30,0x30,0x40,0x00,0xE1,0xE2,0xDD,0xD3,0x00,0x01,0x00},//ACGPIANO   0
	{0x30,0x31,0x40,0x00,0xE1,0xE3,0xDD,0xD3,0x00,0x01,0x00},//ACPiano    1
	{0x30,0x30,0x40,0x00,0xE1,0xE2,0xDD,0xD3,0x04,0x01,0x00},//ELGPIANO   2
	{0x31,0x30,0x40,0x00,0xE1,0xE2,0xDD,0xD3,0x04,0x01,0x00},//HONKTONK   3
	{0x30,0x30,0x40,0x00,0xE1,0xE2,0x87,0x63,0x06,0x01,0x00},//ELPIANO1   4
	{0x30,0x33,0x40,0x00,0xE1,0xE2,0x87,0x63,0x06,0x01,0x00},//ElPiano2   5
	{0x03,0x01,0x00,0x00,0xF3,0xE4,0x64,0x35,0x00,0x01,0x00},//HARPSCHD   6
	{0x01,0x11,0x49,0x02,0xF1,0xF1,0x53,0x74,0x06,0x01,0x02},//CLAVICHD   7
	{0x16,0x11,0x4F,0x0A,0xF2,0xF2,0x61,0x74,0x08,0x00,0x00},//CELESTA    8
	{0x34,0x36,0x00,0x00,0xB3,0xD3,0xC3,0xB3,0x02,0x01,0x00},//GLOCK      9
	{0x35,0x35,0x00,0x00,0xF3,0xF3,0xC3,0xB3,0x01,0x01,0x00},//MUSICBOX  10
	{0xB1,0xB1,0x00,0x00,0xA3,0xB3,0xC3,0xB3,0x01,0x01,0x00},//VIBES     11
	{0x85,0x81,0x4D,0x80,0xDA,0xF9,0x16,0x05,0x0A,0x00,0x00},//MARIMBA   12
	{0x05,0xC4,0x05,0x00,0xFE,0xF8,0x65,0x85,0x0E,0x00,0x00},//XYLOPHON  13
	{0x13,0x01,0x4F,0x10,0xF2,0xF2,0x60,0x72,0x08,0x00,0x00},//TUBEBELL  14
	{0x03,0x17,0x4F,0x0B,0xF1,0xF2,0x53,0x74,0x06,0x00,0x00},//Dulcimer  15
	{0x64,0x21,0x86,0x80,0xFF,0xFF,0x0F,0x0F,0x01,0x00,0x00},//DrawOrgn  16
	{0x24,0x21,0x80,0x80,0xFF,0xFF,0x0F,0x0F,0x01,0x00,0x00},//PRCORGAN  17
	{0x72,0x71,0x00,0x00,0x80,0x80,0xC3,0xB3,0x01,0x01,0x00},//ROCKORGN  18
	{0xB2,0xB0,0x43,0x00,0x9F,0x95,0x06,0x0F,0x09,0x04,0x01},//PIPEORGN  19
	{0x01,0x33,0x4F,0x05,0xF0,0x90,0xFF,0x0F,0x06,0x00,0x00},//REEDORGN  20
	{0x24,0x31,0x4F,0x10,0xF2,0x52,0x0B,0x0B,0x04,0x01,0x00},//ACCORDN   21
	{0x21,0xA2,0x15,0x80,0x61,0x62,0x03,0x67,0x04,0x00,0x00},//HARMNICA  22
	{0xE1,0xE1,0xD0,0x00,0xF5,0xF4,0xAF,0x0F,0x0C,0x00,0x01},//TANGOAcc  23
	{0x13,0x11,0x96,0x80,0xFF,0xFF,0x21,0x03,0x0A,0x00,0x00},//NYLONGtr  24
	{0x11,0x11,0x8D,0x80,0xFF,0xFF,0x01,0x03,0x00,0x00,0x00},//STEELGtr  25
	{0x03,0x11,0x5E,0x00,0xF5,0xF2,0x71,0x83,0x0E,0x01,0x00},//JAXXGTR   26
	{0x21,0x06,0x40,0x85,0xF1,0xF4,0x31,0x44,0x00,0x00,0x00},//ELGTR     27
	{0x01,0x01,0x11,0x00,0xF2,0xF5,0x1F,0x88,0x08,0x00,0x00},//ELGTRMut  28
	{0x31,0x32,0x48,0x00,0xF1,0xF2,0x53,0x27,0x06,0x00,0x02},//OVERDGtr  29
	{0x61,0xE6,0x40,0x03,0x91,0xC1,0x1A,0x1A,0x08,0x00,0x00},//DISTRGtr  30
	{0xC8,0xC4,0x12,0x03,0x73,0xF4,0xBF,0x9F,0x08,0x00,0x00},//GtrHARMN  31
	{0x00,0x01,0x00,0x00,0x94,0x83,0xB6,0x26,0x01,0x00,0x00},//ACOUBASS  32
	{0x00,0x00,0x62,0x00,0xC1,0xF3,0xEE,0xDE,0x0A,0x00,0x00},//ELBASSfn  33
	{0x10,0x00,0x00,0x00,0xFB,0xF3,0x71,0xB9,0x00,0x00,0x00},//ELBASEpk  34
	{0x31,0x22,0x1E,0x00,0xF2,0xF5,0xEF,0x78,0x00,0x00,0x00},//FRETLESS  35
	{0x31,0x23,0x0B,0x00,0x72,0xD5,0xB5,0x98,0x08,0x01,0x00},//SLAPBAS1  36
	{0x31,0x22,0x10,0x04,0x83,0xF4,0x9F,0x78,0x0A,0x00,0x00},//SLAPBAS2  37
	{0x11,0x31,0x05,0x00,0xF9,0xF1,0x25,0x34,0x0A,0x00,0x00},//SYNTHBS1  38
	{0x01,0x11,0x0F,0x00,0xD5,0x85,0x24,0x22,0x0A,0x00,0x00},//SYNTHBS2  39
	{0x43,0x03,0x40,0x00,0x80,0x80,0x82,0xF5,0x00,0x01,0x00},//VIOLIN    40
	{0x42,0x02,0x40,0x00,0x80,0x80,0x82,0xF5,0x00,0x01,0x00},//VIOLA     41
	{0x40,0x00,0x40,0x00,0x80,0x80,0x82,0xF5,0x00,0x01,0x00},//CELLO     42
	{0xC1,0xC1,0xCA,0x80,0x72,0x61,0x75,0xFE,0x06,0x00,0x01},//CNTBASS   43
	{0xB1,0x61,0x8B,0x80,0x71,0x42,0x21,0x25,0x06,0x00,0x01},//StrTREM   44
	{0x31,0x31,0x5A,0x80,0xF1,0xF7,0xA7,0xC6,0x06,0x03,0x03},//StrPIZZ   45
	{0x02,0x11,0x60,0x40,0xF5,0xF2,0x71,0x83,0x04,0x01,0x00},//StrHARP   46
	{0x10,0x11,0x25,0x80,0xF0,0xF0,0x05,0x04,0x0A,0x00,0x00},//TIMPANI   47
	{0x21,0xA2,0x16,0x07,0x70,0x73,0x81,0x2C,0x06,0x01,0x01},//StrSEC1   48
	{0xB1,0x61,0x8B,0x40,0x51,0x42,0x11,0x15,0x06,0x00,0x01},//StrSEC2   49
	{0x31,0x62,0x1A,0x40,0x75,0x54,0x03,0x44,0x06,0x01,0x00},//SYNTHST1  50
	{0xB3,0x61,0x5C,0x00,0x51,0x54,0x00,0x65,0x04,0x01,0x02},//SNYTHST2  51
	{0x41,0xC2,0x4F,0x40,0x71,0x62,0x53,0x7C,0x08,0x00,0x00},//AHHS      52
	{0x60,0xE2,0xA7,0x81,0x22,0x10,0xD6,0x75,0x01,0x00,0x00},//OOHS      53
	{0x41,0x41,0x4F,0x10,0xF1,0xF2,0x73,0x74,0x06,0x01,0x00},//VOXSYTHN  54
	{0xC1,0xC1,0x0F,0x00,0x91,0x62,0x06,0x05,0x0C,0x01,0x02},//ORCHHIT   55
	{0x31,0x61,0x1C,0x80,0x61,0x62,0x1F,0x3B,0x00,0x01,0x00},//TRUMPET   56
	{0xB1,0x61,0x1C,0x80,0x41,0x92,0x0B,0x3B,0x08,0x01,0x00},//TROMB     57
	{0x60,0x00,0x1D,0x00,0x52,0x73,0x68,0x76,0x09,0x01,0x00},//TUBA      58
	{0x21,0x31,0x59,0x80,0x43,0x85,0x8C,0x2F,0x06,0x01,0x00},//SOFTRUMP  59
	{0x20,0x30,0x9F,0xC0,0x53,0xAA,0x1A,0x5A,0x09,0x00,0x00},//FRHORN    60
	{0xB1,0x61,0x95,0x8A,0x41,0x92,0xF6,0xF6,0x06,0x01,0x00},//BRASSECT  61
	{0x21,0x21,0x8E,0x80,0xBB,0x90,0x29,0x0A,0x08,0x00,0x00},//SYNTHBR1  62
	{0xA1,0xA1,0x56,0x8A,0x71,0x81,0xAE,0x9E,0x06,0x01,0x00},//SYNTHBR2  63
	{0x01,0x12,0x63,0x00,0x71,0x52,0x53,0x7C,0x0A,0x00,0x00},//SOPRANSX  64
	{0x01,0x12,0x4F,0x00,0x71,0x52,0x53,0x7C,0x0A,0x00,0x00},//ALTOSAX   65
	{0x21,0x32,0x4E,0x00,0x71,0x52,0x68,0x5E,0x0A,0x00,0x00},//TENORSAX  66
	{0x11,0x12,0x56,0x00,0x71,0x52,0x5B,0x7B,0x0A,0x00,0x00},//BARISAX   67
	{0x21,0x24,0x94,0x05,0xF0,0x90,0x09,0x0A,0x08,0x00,0x00},//OBOE      68
	{0xB1,0xA1,0xC5,0x80,0x6E,0x8B,0x17,0x0E,0x02,0x00,0x00},//ENGHORN   69
	{0x31,0x32,0xD1,0x80,0xD5,0x61,0x19,0x1B,0x0C,0x00,0x00},//BASSOON   70
	{0x32,0x61,0x9A,0x82,0x51,0xA2,0x3B,0x3B,0x08,0x01,0x00},//CLARINET  71
	{0xA3,0xA3,0xDD,0x05,0xBF,0x50,0xF4,0xFA,0x00,0x00,0x00},//PICCOLO   72
	{0xA1,0xA1,0xDD,0x05,0xBF,0x50,0xF4,0xFA,0x00,0x00,0x00},//FLUTE     73
	{0xA2,0xA2,0xDD,0x05,0x96,0x50,0x24,0x9A,0x00,0x00,0x00},//RECORDER  74
	{0xA2,0xA1,0x52,0x8B,0xF5,0x61,0x30,0x3A,0x04,0x00,0x00},//PANPIPE   75
	{0xE2,0x61,0x6D,0x00,0x57,0x57,0x04,0x77,0x0C,0x00,0x00},//BOTTLE    76
	{0xF1,0xE1,0x28,0x00,0x57,0x67,0x34,0x5D,0x0E,0x03,0x00},//SHAKU     77
	{0xF4,0xF3,0x9A,0x80,0xEC,0x60,0xC7,0xA5,0x0D,0x00,0x00},//WHISTLE   78
	{0x02,0x11,0x4F,0x05,0x71,0x52,0x53,0x7C,0x0A,0x00,0x00},//OCARINA   79
	{0x04,0x01,0x08,0x05,0xF8,0x82,0x07,0x74,0x08,0x00,0x00},//SL1sqr    80
	{0x60,0x60,0x03,0x04,0xF6,0x76,0x4F,0x0F,0x02,0x00,0x00},//SL2saw    81
	{0x82,0xF1,0x0D,0x00,0x97,0x97,0x08,0x08,0x00,0x00,0x00},//SL3call   82
	{0x51,0x01,0x80,0x00,0x55,0x55,0xF5,0xF5,0x08,0x00,0x00},//SL4chif   83
	{0x61,0x21,0x00,0x02,0x96,0x55,0x33,0x2B,0x06,0x00,0x00},//SL5char   84
	{0x51,0x41,0x0D,0x00,0xF2,0xF2,0xF2,0xF2,0x00,0x00,0x02},//SL6vox    85
	{0x11,0x03,0x80,0x80,0xA3,0xA1,0xE1,0xE4,0x06,0x00,0x00},//SL7fifth  86
	{0x11,0x31,0x05,0x00,0xF9,0xF1,0x25,0x34,0x0A,0x00,0x00},//SL8bs&ld  87
	{0x71,0x23,0x00,0x00,0xF1,0xF4,0x45,0x44,0x05,0x01,0x00},//SP1new    88
	{0xE0,0xF0,0x16,0x03,0xB1,0xE0,0x51,0x75,0x00,0x02,0x02},//SP2warm   89
	{0x51,0x01,0x03,0x08,0xFF,0xFF,0x02,0x02,0x04,0x01,0x00},//SP3poly   90
	{0xE1,0xE1,0xD0,0x00,0xF5,0xF4,0xAF,0x0F,0x0C,0x00,0x01},//SP4choir  91
	{0xF1,0xF1,0x46,0x80,0x22,0x31,0x11,0x2E,0x0C,0x01,0x00},//SP5bow    92
	{0x05,0x46,0x40,0x80,0xB3,0xF2,0xD3,0x24,0x02,0x00,0x00},//SP6metal  93
	{0x01,0x11,0x0D,0x80,0xF1,0x50,0xFF,0xFF,0x06,0x00,0x00},//SP7halo   94
	{0x00,0x11,0x12,0x80,0x10,0x50,0xFF,0xFF,0x0A,0x00,0x00},//SP8sweep  95
	{0xB4,0xF5,0x87,0x80,0xA4,0x45,0x02,0x42,0x06,0x00,0x00},//SE1rain   96
	{0xF1,0xF1,0x41,0x41,0x11,0x11,0x11,0x11,0x02,0x00,0x00},//SE2track  97
	{0x38,0x38,0x40,0x00,0x83,0x83,0xF2,0xF5,0x00,0x00,0x00},//SE3cryst  98
	{0x61,0x60,0x54,0x03,0x78,0xA2,0x00,0x47,0x06,0x01,0x02},//SE4atmos  99
	{0x40,0x08,0x0D,0x00,0xFF,0xFF,0x03,0x01,0x08,0x00,0x00},//SE5brite 100
	{0x00,0x00,0x00,0x00,0x5F,0xFF,0x0F,0x05,0x00,0x00,0x00},//SE6gobln 101
	{0x21,0x21,0x56,0x00,0x7F,0x35,0x41,0x21,0x0E,0x00,0x00},//SE7echo  102
	{0x71,0x31,0x00,0x40,0xF1,0xF1,0x01,0x01,0x04,0x03,0x00},//SE8sf    103
	{0x01,0x08,0x40,0x40,0xF1,0xF1,0x53,0x53,0x00,0x00,0x00},//SITAR    104
	{0x21,0x12,0x47,0x80,0xA1,0x7D,0xC6,0x13,0x00,0x00,0x00},//BANJO    105
	{0x01,0x19,0x4F,0x00,0xF1,0xF2,0x53,0x74,0x06,0x00,0x00},//SHAMISEN 106
	{0x01,0x00,0x00,0x40,0xE7,0xE3,0xFB,0xF8,0x00,0x00,0x00},//KOTO     107
	{0x02,0x01,0x99,0x80,0xF5,0xF6,0x55,0x53,0x00,0x00,0x00},//KALIMBA  108
	{0x31,0x22,0x43,0x05,0x6E,0x8B,0x17,0x0C,0x02,0x01,0x02},//BAGPIPE  109
	{0x31,0x62,0x1C,0x00,0x75,0x54,0x03,0x44,0x06,0x01,0x00},//FIDDLE   110
	{0x80,0x95,0x4D,0x00,0x78,0x85,0x42,0x54,0x0E,0x00,0x00},//SHANAI   111
	{0x07,0x08,0x48,0x80,0xF1,0xFC,0x72,0x04,0x00,0x00,0x00},//HANDBELL 112
	{0x0E,0x0E,0x00,0x00,0xF8,0xF8,0xF6,0xF6,0x00,0x00,0x00},//AGOGO    113
	{0x02,0x00,0xC0,0x00,0x8F,0xFF,0x06,0x05,0x0A,0x01,0x00},//STEELDRM 114
	{0x02,0x02,0x00,0x00,0xC8,0xC8,0x97,0x97,0x01,0x00,0x00},//WOODBLK  115
	{0x01,0x01,0x00,0x00,0xFF,0xFF,0x07,0x07,0x07,0x00,0x00},//TAIKODRM 116
	{0x01,0x01,0x00,0x00,0xD8,0xD8,0x96,0x96,0x0A,0x00,0x00},//MELDYDRM 117
	{0x06,0x00,0x00,0x00,0xF0,0xF6,0xF0,0xB4,0x0E,0x00,0x00},//SYNTHDRM 118
	{0x01,0x01,0x80,0x80,0x5F,0x5F,0x0B,0x0B,0x04,0x01,0x01},//REVCYMB  119
	{0x51,0x42,0x00,0x05,0x66,0x66,0x05,0x06,0x00,0x02,0x00},//FRET     120
	{0x53,0x00,0x05,0x00,0x5F,0x7F,0x66,0x07,0x06,0x00,0x00},//BREATH   121
	{0x0E,0x0E,0x00,0x00,0x20,0x21,0x00,0x01,0x0E,0x00,0x00},//SEASHORE 122
	{0xC0,0x7E,0x4F,0x0C,0xF1,0x10,0x03,0x01,0x02,0x00,0x00},//TWEET    123
	{0xF4,0xF3,0x50,0x80,0x85,0x74,0x87,0x99,0x0C,0x00,0x00},//RING     124
	{0xF0,0xE2,0x00,0xC0,0x1E,0x11,0x11,0x11,0x08,0x01,0x01},//HELICPTR 125
	{0x7E,0x6E,0x00,0x00,0xFF,0x3F,0x0F,0x0F,0x0E,0x00,0x00},//APPLAUD  126
	{0x06,0x84,0x00,0x00,0xA0,0xC5,0xF0,0x75,0x0E,0x00,0x00}};//GUNSHOT 127


/**************************************************************************
	void MidiCommand(VATCOMMAND c)

	DESCRIPTION:  Simple Interface for working With Midi playback

	INPUTS:
		c           VAT command (See sound.h)

**************************************************************************/
void MidiCommand(VATCOMMAND c)
{
	SHORT i;

	switch(c){
		case v_play:
			midi_reset = TRUE;
			midi_on = TRUE;
			break;
		case v_stop:
			midi_on = FALSE;
			midi_reset = TRUE;
			for(i = 0; i < 9; i++) FMSetVolume(1,0);
			FMReset();
			break;
		case v_pause:
			midi_on = FALSE;
			break;
		case v_resume:
			midi_on = TRUE;
			break;
		case v_rewind:
			midi_reset = TRUE;
			break;
		default:
			break;
	}
}


/**************************************************************************
	SHORT getvoice(VOICE midi_voice[],SHORT track,SHORT channel, SHORT note)

	DESCRIPTION: Find the first matching voice (or first inactive voice if
								a match is not found).   This function is used by midiplayer()
								as an interface to get FM voices.

	INPUTS:
		v         pointer to an array of voice structtures
		track     MIDI track that is generating this request
		channel   MIDI channel that is generating this request
		note      MIDI note requested

	RETURNS:
		Open number if successful, -1 if not.
**************************************************************************/
SHORT getvoice(VOICE midi_voice[],SHORT track,SHORT channel, SHORT note)
{
	SHORT i;


	for(i = 0; i < MAXSTOREDVOICES; i++) {   // find matching active note
		DOSYNC1;
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

	DOSYNC1;
																	// no available voices... error
	return -1;
}




/**************************************************************************
	midiplayer()

	DESCRIPTION: Routine for playing midi files.  THis is designed to be
							 called from a timer interrupt.  To use, set these values
							 in this order:

									 midi_data    (must point to a filled MIDI structure.)
									midi_reset = TRUE;
									midi_on = TRUE;

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
	SHORT spot,i,j,vidx;
	BYTE event,ev,ch,b1,b2,etype;
	LONG itmr,l2,length;
	CHAR tdata[256];
	WORD mpuloc,m;

	DOSYNC1;

	if(!midi_data) {                        // must have data to play!
		midi_on = FALSE;
		return;
	}
	if(midi_reset) {                        // Reset?  zero track pointers and timers
		for(i = 0; i < 32; i++ ) {
			DOSYNC1;
			midi_trackloc[i] = 1;               // no need to read first time offset
			midi_timer[i] = 0;                  // all timers start at zero
			midi_trackon[i] = TRUE;
			if(i < MAXSTOREDVOICES) midi_voice[i].active = 0; // unreserve all voices
			midi_lastevent[i] = 0x80;           // set last event to note off
		}
		midi_reset = 0;                       // clear midi reset flag
		midi_livetracks = midi_data->num_tracks;// set number of active tracks so
																					// we know when to stop.
		midi_divisions = midi_data->divisions;// ticks per quarter note
		if(midi_divisions < 0) midi_divisions = -midi_divisions;  // some midi files have
																					// negative division values
		if(!midi_divisions) midi_divisions = 96; // Pick a default if they give us a zero

		if(midi_mpuout) MPUReset();
	}

	if(!midi_on) return;                    // logical switch for midi on/off

																					// loop over tracks
	for(i = 0 ; i < midi_data->num_tracks; i++) {
		DOSYNC1;
		while(midi_timer[i] <= 0) {           // Process while timer is < 0;
			DOSYNC1;
			event = *(TD);                    	// get next event (TD is a macro)
			mpuloc = midi_trackloc[i];

			midi_trackloc[i]++;                 // advance track location pointer

			if(event == 0xFF) {                 // META event?
				etype = *(TD);
				midi_trackloc[i] ++;
																					// read length of meta event
				spot = readvarlen(TD,&length);
				midi_trackloc[i] += spot;
																					// grab any text data for text events
				for(j = 0; j < length; j++) tdata[j] = *(TD + j);
				tdata[j] = 0;


				switch(etype) {
					case 0x00:
						j = *(TD)*256 + *(TD+1);
						//printf("[%d] SEQUENCE NUMBER (%d)\n",i,j);
						break;
					case 0x01:
						//printf("[%d] TEXT EVENT (%s)\n",i,tdata);
						break;
					case 0x02:
						//printf("[%d] COPYWRITE EVENT (%s)\n",i,tdata);
						break;
					case 0x03:
						//printf("[%d] TRACK NAME EVENT (%s)\n",i,tdata);
						break;
					case 0x04:
						//printf("[%d] INSTRUMENT NAME EVENT (%s)\n",i,tdata);
						break;
					case 0x05:
						//printf("[%d] LYRIC EVENT (%s)\n",i,tdata);
						break;
					case 0x06:
						//printf("[%d] MARKER EVENT (%s)\n",i,tdata);
						break;
					case 0x07:
						//printf("[%d] CUE EVENT (%s)\n",i,tdata);
						break;
					 case 0x2f:                   		// End of track
						//printf("[%d] END OF TRACK\n",i);
						midi_timer[i] = 2147000000L;    // set timer to highest value
						midi_trackon[i] = FALSE;        // turn off track
						midi_livetracks--;              // decrement track counter
						if(midi_livetracks == 0) {      // last track?  Turn off midi!
							midi_on = FALSE;
							midi_reset = TRUE;            // Make sure we start over

							if(midi_data->repeat) {       // check for repeats
								if(midi_data->repeat > 0) midi_data->repeat --;
								midi_on = TRUE;
							}
																						// Check for a chain function
							if(midi_data->chainfunc) midi_data->chainfunc(midi_data);

																						// Check for a chain
							if(midi_data->chain) {
								midi_data = midi_data->chain;
								midi_on = TRUE;
							}
							return;
						}
						break;
					case 0x51:                   // TEMPO event (microsecs per 1/4 note)
						l2 = *(TD) * 0x10000L + *(TD+1) * 0x100 + *(TD+2);
						//printf("[%d] TEMPO EVENT (%ld)\n",i,l2);
						midi_msperdiv = (SHORT)(l2/midi_divisions); // micro secnds/tick
																			 // Convert number to number of
																			 // sb interrupts per tick. (fixed poit)

						midi_callfreq = (WORD)(256L*(((LONG)midi_msperdiv *
											(LONG)sample_rate) / 1000000L)/ (LONG)dma_bufferlen);
						break;
					case 0x58:
						//printf("[%d] TIME SIG EVENT (%X,%X,%X,%X)\n",i,
						//        *(TD),*(TD+1),*(TD+2),*(TD+3));
						break;
					case 0x59:
						//printf("[%d] KEY SIG EVENT (%X,%X)\n",i,*(TD),*(TD+1));
						break;
					case 0x7F:
						//printf("[%d] SEQUENCER DATA EVENT\n",i);
						break;
					default:
						//printf("[%d] *** undefined event *** (%X,type: %X,length %ld)\n",i,event,etype,length);
						break;
				}
				midi_trackloc[i] += (WORD)length;
			}
			else if(event == 0xF0 || event == 0xF7) { // sysex event
				midi_trackloc[i] += readvarlen(TD,&length);
				//printf("Sysex type 1 [length: %ld]\n",length);
				midi_trackloc[i] += (WORD)length;
			}
			else {                           			// PROCESS MIDI EVENTS

				if(!(event & 0x80)) {          			// top bit Not set? Running status!

					b1 = event;                  			// b1 = note   (usually)
					b2 = *(TD);              					// b2 = volume? (usually)


					event = midi_lastevent[i];        // use last event
					//printf("Running status >>");
					//for(j = 0; j < 9; j++) printf("%d",midi_voice[j].active);
					//printf("\n");
					midi_trackloc[i] --;              // one less byte for running status.

				}
				else {                         			// Else it was a regular event
					ch = event & 0x0f;
					ev = event & 0xF0;
					event = ev + midi_patchmap[ch];

					midi_lastevent[i] = event;        // set to last event
					b1 = *(TD);                   		// get next two bytes
					b2 = *(TD+1);
				}
				ev = event & 0xF0;             			// strip lower four bits
				ch = event & 0x0f;             			// get channel from low bits

				if(midi_mpuout) {
					//ECODE
					//dbprintf("\n");

					MPUWrite(event);
					MPUWrite(b1);
					if(ev != 0xC0 && ev != 0xD0) MPUWrite(b2);
				}

				vidx = getvoice(midi_voice,i,ch,b1);    // Get a voice index
				DOSYNC1;
				switch(ev) {
					case 0x80:                   			// Note off
						//printf("[%d] Note off (%d,%d)\n",i,b1,b2);
						midi_trackloc[i] += 2;
						if(vidx > -1) {            			// If a matching voice was found,
																						// kill it.
							FMKeyOff(vidx);
							DOSYNC1;
							FMSetVolume(vidx,0);
							midi_voice[vidx].active = FALSE;
							DOSYNC1;
						}
						break;
					case 0x90:                   			// Note On
						//printf("[%d] Note on (%X,%d,%d)\n",i,event,b1,b2);
						//printf("%X",ch);
						midi_trackloc[i] += 2;
						if(vidx > -1) {            			// Voice found?
							if(midi_voice[vidx].active) { // already active? Turn it off.
								midi_voice[vidx].active = FALSE;
								FMKeyOff(vidx);
								DOSYNC1;
								FMSetVolume(vidx,0);
								DOSYNC1;
							}
							else {                   // Wasn't active?  Turn it on.
								midi_voice[vidx].owner_track = i;
								midi_voice[vidx].owner_channel = ch;
								midi_voice[vidx].note = b1;
								midi_voice[vidx].volume = b2;
								if(!midi_fmout) midi_voice[vidx].volume = 0;

								midi_voice[vidx].active = TRUE;
								if(vidx < 9) {
									FMSetNote(vidx,b1);
									DOSYNC1;
									j = (midi_volume * midi_voice[vidx].volume/2) >> 4  ;
									if(j > 63) j = 63;
									FMSetVolume(vidx,j);
									DOSYNC1;
									FMSetVoice(vidx,midi_instrument[midi_fmpatchmap[i]]);
									DOSYNC1;
									FMKeyOn(vidx);
									DOSYNC1;
								}

							}
						}
						break;
					case 0xA0:                   // Key pressure
						//printf("[%d] Note presure (%d,%d)\n",i,b1,b2);
						midi_trackloc[i] += 2;
						break;
					case 0xB0:                   // Control CHange
						//printf("[%d] Control Change (%d,%d)\n",i,b1,b2);
						midi_trackloc[i] += 2;
						break;
					case 0xC0:                   // Program change
						//printf("[%d] Program change (%d)\n",i,b1);
						if(!midi_fmpatchmapoverride) midi_fmpatchmap[i] = b1;
						midi_trackloc[i] += 1;
						break;
					case 0xD0:                   // Channel Pressure
						//printf("[%d] Channel Pressure (%d,%d)\n",i,b1);
						midi_trackloc[i] += 1;
						break;
					case 0xE0:                   // Pitch wheel change
						//printf("[%d] Pitch change (%d,%d)\n",i,b1,b2);
						midi_trackloc[i] += 2;
						break;
					default:                     // Uh-OH
						//printf("MIDI ERROR (F0 midi command)\n");
						midi_on = FALSE;
						return;
				}

			}

																				 // read next time offset
			if(midi_trackon[i]) {
				midi_trackloc[i] += readvarlen(TD,&itmr);
				midi_timer[i] += itmr*256;
				//printf(" T: %ld\n",midi_timer[i]);
			}
																				 // Write MPU data

		}
		midi_timer[i]-= midi_tempoadjust;   // decrement timer.
	}


}

/**************************************************************************
	MIDI VFAR *LoadMidi(CHAR *filename, CHAR *errstring)

	DESCRIPTION: Reads a midi file and stores it to a MIDI data structure

	INPUTS:

		filename    Pointer to full midi filename
		errstring    Pointer to a pre-allocated string.

	RETURNS:
		returns point to MIDI structure if successful.
		NULL otherwise.

**************************************************************************/
MIDI VFAR *LoadMidi(CHAR *filename, CHAR *errstring)
{
	SHORT i;
	FILE *input;
	CHAR sdata[256];
	LONG lidata;
	SHORT idata;
	DWORD lread;
	MIDI VFAR *mdata;

	mdata = (MIDI VFAR *)VMALLOC(sizeof(MIDI));    // make room for music!
	if(!mdata) {
		sprintf(errstring,"Out of memory.");
		return(NULL);
	}

	mdata->chain = NULL;
	mdata->chainfunc = NULL;
	mdata->repeat = 0;

	input = fopen(filename,"rb");            // open a midi file
	if(!input) {
		sprintf(errstring,"cannot open %s",filename);
		return(NULL);
	}
																					 // Read the header

	fread(sdata,1,4,input);                  // midi id there?
	sdata[4] = 0;
	if(strcmp(sdata,"MThd")) {
		sprintf(errstring,"Not a  midi file.");
		fclose(input);
		return(NULL);
	}

	lidata = readlong(input);                // length of remaining header chunk?
	if(lidata > 250) {
		VFREE(mdata);
		sprintf(errstring,"Header chunk has a weird length");
		fclose(input);
		return(NULL);
	}


	idata = readshort(input);                // Read MIDI Format specifier
	if(idata != 0 && idata != 1) {
		VFREE(mdata);
		sprintf(errstring,"Unrecognized MIDI format");
		fclose(input);
		return(NULL);
	}

	mdata->format = idata;

	idata = readshort(input);                // number of tracks
	if(idata < 1 || idata > 32) {
		VFREE(mdata);
		sprintf(errstring,"Bad number of tracks [%d]",idata);
		fclose(input);
		return(NULL);
	}
	mdata->num_tracks = idata;

	idata = readshort(input);                // division number (tempo)
	mdata->divisions = abs(idata);

																					 // Read individual track data
	for(i = 0; i < mdata->num_tracks; i++) {
		fread(sdata,1,4,input);                // midi track id there?
		sdata[4] = 0;
		if(strcmp(sdata,"MTrk")) {
			VFREE(mdata);
			sprintf(errstring,"Error reading track #%d",i);
			fclose(input);
			return(NULL);
		}

		lidata = readlong(input);              // length of remaining track chunk?

																					 // Allocate space for track
		mdata->track[i] = (BYTE VFAR *)VMALLOC(lidata);
		if(!mdata->track[i]) {
			while(i) {
				i--;
				VFREE(mdata->track[i]);
			}
			VFREE(mdata);
			sprintf(errstring,"Out of memory.");
			fclose(input);
			return(NULL);
		}
																					 // read in entire track
		lread = fread(mdata->track[i],1,(size_t)lidata,input);
		if(lread < lidata) {
			while(i) {
				i--;
				VFREE(mdata->track[i]);
			}
			VFREE(mdata);
			sprintf(errstring,"Premature end of midi file [track %d]",i);
			fclose(input);
			return(NULL);
		}
	}

	fclose(input);
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
	LONG readshort(FILE *inflile)

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
	SHORT MPUEnter(void)

	DESCRIPTION:  This function resets the MPU-401 chip and starts UART
								transfer mode.

                Note that the timeout is pretty much ignored for "dumb"
                uart devices since many of them dispense with things like
                data ready bits...

	RETURNS:

		True if successful, False if not

**************************************************************************/
SHORT MPUEnter(void)
{
  SHORT flag = 2;
  BYTE ack;

  vdisable();

  mpu_checked = TRUE;

  while(flag) {
																					   // Check command ready bit
	  for(mpu_timeout = 0; mpu_timeout < TIMEOUT; mpu_timeout++) {
			if(!(VINPORTB(midi_mpuport+1) & 0x40)) break;
	  }
	  dbprintf("MPUENTER() - check ready t.o.: %u\n",mpu_timeout);
    mpu_timeout =0;                         // reset timeout.

		VOUTPORTB(midi_mpuport+1,0xFF);          // Send reset command

	  while(mpu_timeout<TIMEOUT) {            // Wait for ready bit to clear
		  mpu_timeout++;
			if(!(VINPORTB(midi_mpuport+1)&0x80)) break;
	  }

		dbprintf("MPUENTER() - wait ready clear t.o.: %u\n",mpu_timeout);
		mpu_timeout = 0;

		ack = VINPORTB(midi_mpuport);                     // Read the ACK byte
		flag --;

		if(ack == 0xFE) flag = 0;             // if we get an FE, were done!
	}

	if(ack != 0xFE) {                       // Did it not work?
		mpu_available = FALSE;
		venable();
		return FALSE;
	}


	VOUTPORTB(midi_mpuport+1,0x3F);          // Put it in UART mode
	dbprintf("MPUENTER() - wait for UART t.o.: %u\n",mpu_timeout);


	mpu_available = TRUE;
	venable();
//	MPUReset();
	return(TRUE);
}


/**************************************************************************
	void MPUReset(void)

	DESCRIPTION:  Resets all of the midi parameters

**************************************************************************/
void MPUReset(void)
{
	int i;

	if(!mpu_available) return;
	vdisable();
	for(i = 0; i < 15; i++) {
																		 // Turn off damper
		MPUWrite(0xB0 | i);
		MPUWrite(64);
		MPUWrite(0);

																		 // Turn off sound
		MPUWrite(0xB0 | i);
		MPUWrite(120);
		MPUWrite(0);

																		 // Reset controller
		MPUWrite(0xB0 | i);
		MPUWrite(121);
		MPUWrite(0);

																		 // Turn off note
		MPUWrite(0xB0 | i);
		MPUWrite(123);
		MPUWrite(0);

	}
	venable();
}

/**************************************************************************
	void MPUWrite(BYTE b)

	DESCRIPTION:  Writes a byte  the midi data port

	INPUTS:
		b    byte to write to the MPU-401 chip

**************************************************************************/
void MPUWrite(BYTE b)
{

	if(!mpu_available) return;

	mpu_timeout = 0;

	while(mpu_timeout<TIMEOUT) {        // Wait for ready bit to clear
		mpu_timeout++;
		if(!(VINPORTB(midi_mpuport+1)&0x40)) break;
	}
																			// Write the byte!
	vdisable();
	if(mpu_timeout < TIMEOUT) {
		VOUTPORTB(midi_mpuport,b);
		//ECODE
		//dbprintf("%x ",b);
	}
///	else dbprintf("[%x] ",b);
	venable();

	//ECODE
	debugnum++;
	debugnum+=mpu_timeout*256;
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
	void LoadInstruments(CHAR *filename,BYTE inst[128][11])

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
SHORT LoadInstruments(CHAR *filename,BYTE inst[128][11])
{
	FILE *input;
	SHORT i=0,j;
	CHAR string[255];

	input = fopen(filename,"r");     // open the file
	if(!input) return(0);
																	 // read  it's contents
	while(fgets(string,255,input) && i < 128) {
		for(j = 0; j < 11; j++) sscanf(string+j*3,"%X ",&inst[i][j]);
		i++;
	}
																	 // clean up and go home
	fclose(input);
	return(i);
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

	if(!m) return;

	for(i = 0; i < m->num_tracks; i++) VFREE(m->track[i]);
	VFREE(m);
}


/**************************************************************************
	void initmid(void)

	DESCRIPTION:  Sets up the midi stuff before any playing happens

**************************************************************************/
void initmid(void)
{
	midi_data=NULL;
	midi_patchmap = defaultpatchmap;
	midi_fmpatchmap = defaultfmpatchmap;
	midi_callfreq = 256;
	midi_reset = TRUE;
	midi_on = FALSE;
	midi_mpuout = FALSE;
	midi_fmout = TRUE;
	midi_usertempo = 100;
	midi_tempoadjust = 256;
	midi_volume = 0x16;
}


