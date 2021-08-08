/**************************************************************************
												VARMINT'S AUDIO TOOLS 0.71

	VAT.H

		Header file for VAT.


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

//------------------- BEGIN DEFINITIONS -----------------------------
#define VAT_VERSION "0.73f (beta)"


                               // Play around with these if you want to
															 // Expand the capabilities of the library.
															 // MAXSOUNDS indicates the maximum number
															 // of active sounds allowed.
															 // MAXSOUNDTOKENS should be bumped up if
															 // You chain a lot of sounds together.
															 // MAXSTOREDVOICES indicates the number of
															 // MIDI voices (from a file) that VAT can
															 // handle.
#define MAXSOUNDS 16
#define MAXSOUNDTOKENS 50
//#define MAXSTOREDVOICES  32

///////////// PORTABILITY /////////////////////////////////////////////
// These definitions help ease the pain of moving VAT around to different
// compilers.

															 // This definition indicates the largest
															 // a sound can be before it gets chopped up
															 // linked.  A protected mode compiler should
															 // have this set to a meg or something.
#define MAXCHUNKSIZE 64000L

															 // Pointer type definition for samples.
															 // This definition should be far or
															 // huge.  If you use near, you will have
															 // to change the code to use malloc()
															 // instead of farmalloc()
#define SAMPLE signed char far

																		// BYTE = 1 bytes, unsigned
																		// WORD = 2 bytes, unsigned
																		// DWORD = 4 bytes, unsigned
																		// CHAR = 1 bytes, signed
																		// SHORT = 2 bytes, signed
																		// LONG = 4 bytes, signed
#define BYTE    unsigned char
#define WORD    unsigned short int
#define DWORD   unsigned long int
#define CHAR		signed char
#define SHORT	  signed short int
#define LONG	  signed long int
																		// Fastest type of interger
#define FASTINT unsigned short int

#define VMALLOC farmalloc
#define VFREE   farfree
#define VFAR    far
															 // Arraytype referes to how the compiler
															 // casts the number in square array
															 // brakets.  ie: Real mode does not allow
															 // array elements larger than 65 K
#define ARRAYTYPE unsigned int
															 // Some compilers have different inport
															 // and outport interfaces
#define VINPORTB(X)  inportb(X)
#define VOUTPORTB(X,Y) outportb(X,Y)

////////////////////////////////////////////////////////////////////

																			// GENERAL VAT STUFF
#define FALSE   0
#define TRUE    1
																			// Number of tries before MPU times out
#define TIMEOUT           5000
																			// DSP commands
#define DSP_DETECT        0x02
#define DSP_GET_VERS      0xe1
#define DSP_INVOKE_INTR   0xf2
#define DSP_RESET         0x06
#define DSP_READ          0x0a
#define DSP_RSTATUS       0x0e
#define DSP_SAMPLE_RATE   0x40
#define DSP_SILENCE       0x80
#define DSP_SPKR_ON       0xd1
#define DSP_SPKR_OFF      0xd3
#define DSP_WRITE         0x0c
#define DSP_WSTATUS       0x0c
																			// FM chip things
#define FM_ADLIB_ADDRESS  0x388
#define FM_BOTH_OFF       0x08
#define FM_DETECT         0x01
#define FM_LEFT_OFF       0x00
#define FM_RIGHT_OFF      0x02
																			// FM rythm selectors
#define FM_HIHAT          0x01
#define FM_TOPCYM         0x02
#define FM_TOMTOM         0x04
#define FM_SNARE          0x08
#define FM_BASS           0x10

//----------------------------------- Enumerations


typedef enum {bit8=0,bit4=1,bit26=2,bit2=3,high} playmode;
typedef enum {none,nodsp,adlib,sb20,sbpro} cardtype;
typedef enum {fmerr=0,nodsperr,irqerr,dmacherr,nomem} SBERROR;
typedef enum {v_play,v_stop,v_pause,v_resume,v_rewind,v_setrepeat,v_setpos,
							v_setrate,v_setvolume } VATCOMMAND;
typedef enum {v_fancy,v_plain,v_unused} VATPLAYTYPE;

//----------------------------------- Structures

																			 // The channel structure is used
																			 // internally for playing MODs and
																			 // S3Ms.
typedef struct {
	DWORD					bufferdummy1;
	DWORD         position;
	DWORD         bufferdummy2;
	DWORD         end;
	DWORD         rlength,offset;
	BYTE          sflag;
	WORD          sample_number;
	DWORD         *pos;
	DWORD         counter,pinc;
	LONG          period;
	DWORD         period2,vibdepth,vibperiod;
	WORD          count;
	LONG          data1,data2,data3,data4;
	LONG          vslide;
	LONG          porta;
	LONG          s3m_fine;
	LONG          fineperiod;
	LONG          fineadjust;
	LONG          finevol;
	CHAR   				volume,volume2;
	CHAR   				cut;
	BYTE          effect,x,y;
	BYTE          retrigger;
	SAMPLE        *sdata;
} CHANNEL;
																			// MOD struct is used to hold mod file
																			// data.
typedef struct mod {
	CHAR          title[20];
	CHAR          sample_name[32][22];
	LONG          slength[32];
	WORD					offset[32],repeat[32];
	CHAR          finetune[32];
	BYTE          volume[32],num_positions;
	BYTE          maxpattern,ptable[128];
	CHAR			 		sig[5];
	BYTE VFAR      *pattern_data[128];
	BYTE          num_samples;
	SAMPLE        *sdata[32];
	SHORT         repeatmusic;
	struct mod    *chain;
	void VFAR      (*chainfunc)(struct mod *);
} MOD;

																			// S3M struct is used to hold s3m file
																			// data.
typedef struct s3m {
	CHAR    title[28];                   // Up to 28 chars nul terminated
	CHAR    sample_name[100][28];        // Up to 100 samples.
	DWORD   slength[100];                // Sample length
	BYTE    sflag[100];                  // Sample flags like looping etc
	DWORD   loopbegin[100],loopend[100]; // Loop begin and end
	DWORD   c2spd[100];                  // Tuning of sample
	BYTE    volume[100];                 // Volume of instrument<default>
	SAMPLE  VFAR *sdata[100];             // Pointer to sample data
	BYTE    insnum,patnum,flags;         // number of instruments and patterns
	BYTE    channelnum,orders;           // number of channels and orders in s3m
	BYTE    globalvol,initspeed,inittempo;//initial speed and tempo of song
	BYTE    mastervol;
	BYTE    order[256];                  // up to 255 orders in song
	SHORT		repeatmusic;
	struct s3m    *chain;
	void VFAR      (*chainfunc)(struct mod *);
	BYTE VFAR   *pattern_data[256];       // pointer to the pattern data
} S3M;


																			// A wave is an external structure
																			// used to store the raw data of
																			// sound effects.
typedef struct wave {
	LONG id;
	WORD sample_rate;
	WORD byte_rate;
	SAMPLE *data;
	DWORD chunk_size;                   // size of this chunk in bytes
	DWORD sample_size;                  // size of entire linked sample
	struct wave VFAR *next;             // points to next link.
	struct wave VFAR *head;             // points to top link.
} WAVE;

																			// a sound effect in an internal
																			// Data structure used to handle
																			// active sounds.
typedef struct soundeffect {
	SAMPLE  *data;                      // pointer to raw sound data
	WAVE VFAR *w;                      	// pointer to sound struct
	DWORD   length;                     // length of the sample iin bytes
	DWORD		dummy;
	DWORD   position;                   // data position used internally by sbint
	DWORD   dummy2;
	DWORD   *pos;                       // pointer to current byte position
	WORD    pinc;                       // rate counter
	SHORT   repeat;                     // number of times to repeat sample
	BYTE    volume;                     // volume of the sample
	BYTE    active;                     // indicates wether sample is playing
	LONG    id;                         // THis id is used for a handle
	VATPLAYTYPE     type;               // fancy or plain
	struct soundeffect VFAR *chain;      // sound effect to jump to when done
	struct soundeffect VFAR *next;       // Used internally for a linked list
	void VFAR (*chainfunc)(struct soundeffect *);
} SOUNDEFFECT;

																			// THis bit adds a wrapper around
																			// the function prototypes so that
																			// a C++ compiler will be able to
																			// use them.
#ifdef __cplusplus
extern "C" {
#endif



//----------------------------------- DSP functions


SHORT     DSPReset(void);
BYTE    DSPRead(void);
void    DSPWrite(BYTE output);
WORD    DSPGetVersion(void);

//----------------------------------- Timer functions

void    TimerOn(void);
WORD    TimerOff(void);
void    InstallTimer0(WORD period,void VFAR (*func)(void));
void    RemoveTimer0(void);
void _saveregs MilliDelay(WORD delay);
void _saveregs MicroDelay(WORD delay);
void    InitTimerFunctions(void);



//----------------------------------- File I/O functions

MOD VFAR   *LoadMod(CHAR *filename, CHAR *errstring);
S3M VFAR   *LoadS3M(CHAR *filename,CHAR *errstring);
WAVE VFAR *LoadWave(CHAR *wavefile, CHAR *errstring);
WAVE VFAR *LoadWaveFromMemory(WAVE VFAR *w,SAMPLE *data, LONG l);


//----------------------------------- Sound Effect interface functions

SHORT   AddChainFunction(DWORD id,void (*func)(SOUNDEFFECT VFAR *));
void    AlterSoundEffect(DWORD id,VATCOMMAND c,LONG parameter);
DWORD   ChainSoundEffect(WAVE VFAR *w,VATPLAYTYPE type,DWORD id);
DWORD 	PlaySound(WAVE VFAR *w,VATPLAYTYPE type);
LONG 		SoundActive(LONG id);

//----------------------------------- Other functions

WORD    SetSampleRate(WORD rate);
SHORT     SBSetUp(void);
void    SBCleanUp(void);
void    GoVarmint(void);
void    DropDeadVarmint(void);
void    FreeMod(MOD *freeme);
void    FreeS3M(S3M *freeme);
void 		FreeWave(WAVE VFAR *w);
void    VarmintVSync(void);
void    TimeVSync(void);
void    ModCommand(VATCOMMAND c);
void    S3MCommand(VATCOMMAND c);
WORD    PercentOverhead(WORD ticks);
CHANNEL VFAR *ModChannels(void);
CHANNEL VFAR *S3MChannels(void);

																			// Again, this is part of the C++
																			// wrapper.
#ifdef __cplusplus
}
#endif


//----------------------------------- Global Variables


																			// MOD/S3M parameters
extern MOD VFAR  *mod_data;
extern S3M VFAR  *s3m_data;
extern SHORT	   mod_on,s3m_on;
extern SHORT     mod_bytespertick,s3m_bytespertick;
extern SHORT     mod_volume;
extern SHORT     s3m_volume;
extern BYTE      channel_select[4];
																			// Miscellaneous
extern CHAR     *errname[];
extern DWORD    vclock;
extern SBERROR  sberr;
extern WORD     DSP_overhead;
extern WORD     vsyncclock;
extern BYTE     sync_on;
extern SHORT    debug_lowdsp;
extern SHORT    debug_reverseflipflop;
extern WORD     sample_rate;          // Internal sample rate- DON'T CHANGE!
extern FASTINT	bytes_per_synccheck;
extern FASTINT  syncbytecount;

extern LONG debugnum;							// used for debugging code




																			// These variables are necessary to
																			// VAT, but are not normally needed
																			// outside of the library itself.

//extern WORD         dma_bufferlen;  // Length of mixing buffer in bytes
//extern WORD         io_addr;        // SB port address
//extern WORD         intnr;          // SB interrupt number
//extern WORD         dma_ch;         // SB DMA channel
//extern WORD         card_id;        // Stand SB card id (1-6)
//extern WORD         fm_addr;        // SB port for FM commands
//extern WORD         dsp_vers;       // DSP version number
//extern WORD         vsync_toolong;  // # vclocks between vertical retraces
//extern SHORT          sounds_in_queue;     // Number of active sounds
//extern BYTE         defaultpatchmap[16]; // startup  MIDI output patchmap
//extern CHAR         vatdebugstring[];    // string with debugging data
//extern VOICE        midi_voice[];        // FM voice aray
