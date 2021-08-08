#ifndef _VAT_H_
#define _VAT_H_

/*_________________________________________________________________________*\
														 \/ /         \ \/
                               <   INTRO   >
                                \_________/


													VARMINT'S AUDIO TOOLS 1.1
                                HEADER FILE


        Authors (in order of appearance):
          Eric Jorgenson ...... smeagol@rt66.com
          Bryan Wilkins ....... bwilkins@groundup.com
          Neil Breeden ........ nbreeden@groundup.com
          Grant Culbertson .... webmaster@groundup.com


  This is the header file for Varmint's Audio Tools v1.1, containing all
  external definitions and prototypes needed to compile source code using
  VAT v1.1.  It has been copiously commented for your benefit.  Please
  look here first if the included documentation is not enough to satiate
  your curiosity about some element of VAT.  Further questions, criticisms,
  suggestions, or tokens of adoration should be directed to:

    support@groundup.com

  We very much encourage your comments and suggestions.  We want VAT to
  be useful and enjoyable for you.


    Please visit our web site at:

        http://www.groundup.com/


                                            Copyright 1995,1996 Ground Up  */


/*_________________________________________________________________________*\
                            \/ /           \ \/
                              <   DEFINES   >
                               \*_________*/


  // VAT version number string

#define VAT_VERSION "1.20"


  // Types (portability)

#define BYTE    unsigned char     // 1 byte,  unsigned
#define WORD    unsigned short    // 2 bytes, unsigned
#define DWORD   unsigned int      // 4 bytes, unsigned
#define CHAR      signed char     // 1 byte,    signed
#define SHORT     signed short    // 2 bytes,   signed
#define LONG      signed int      // 4 bytes,   signed
#define SAMPLE    signed char


  // Special settings

#define GET_SETTING                    -127
#define GET_INSTRUMENTS  (INSTRUMENT *)-127
#define GET_PATCHMAP           (BYTE *)-127
#define GET_STATE       (MIXER_STATE *)-127

#define MAXMIDITRACKS 256

/*_________________________________________________________________________*\
													\/ /                \ \/
														<      TYPES       >
														 \*______________*/

typedef void (*VOIDFUNCVOID)(void);// VOIDFUNCVOID;
typedef void (*VOIDFUNCLONG)(LONG);// VOIDFUNCLONG;

/*_________________________________________________________________________*\
													\/ /                \ \/
														<   ENUMERATIONS   >
														 \*______________*/

  // VATSTART: How should VAT be started

typedef enum {v_detect,    // Auto detect the sound card
              v_blaster,   // Use the blaster string
              v_config     // Use a configuration file
             } VATSTART;


  // VATBOOL: return value on many functions

typedef enum {v_false,  // false, failure, or unset
              v_true    // true, success, or set
             } VATBOOL;


  // VATSTATUS: WaveStatus, ModStatus, S3MStatus,
  //            MidiStatus, FMStatus, MPUStatus

typedef enum {v_nonexist,   // nonexistent or undetected
              v_unavail,    // not available
              v_stopped,    // disabled or not playing
              v_started,    // enabled or playing
              v_paused,     // waiting or paused
             } VATSTATUS;


  // VATCOMMAND: WaveCommand, ModCommand, S3MCommand, MidiCommand

typedef enum {v_remove,     // remove from play queue or current Mod/S3M/Midi
              v_play,       // play or resume playing
              v_stop,       // stop playing (and reset to beginning)
                             // equivalent to v_remove for Waves
              v_pause,      // pause
              v_rewind,     // rewind to beginning
             } VATCOMMAND;

// backward compatibility
#define v_resume v_play


  // VATSETTING: WaveSetting, ModSetting, S3MSetting, MidiSetting

typedef enum {v_volume,     // volume
              v_repeat,     // repeat count, < 0 is nonterminating
              v_rate,       // rate or tempo
              v_panpos,     // panning position (wave only so far)
              v_position    // position in sound/song (wave only so far)
             } VATSETTING;


  // VATPLAYTYPE: PlaySound, WaveChain

typedef enum {v_unused,     // unused token - internal marker
              v_plain,      // plain mode - mono only, no change allowed
              v_fancy,      // fancy mode - mono only, volume/freq change
              v_pan,        // pan mode - mono only, volume/freq/pan change
              v_stereo      // stereo mode - stereo only, volume/freq change
             } VATPLAYTYPE;


	// VATRHYTHM: FMRhythm

typedef enum {v_no_rhythm=0x00,     // no rhythm modes
              v_hihat_rhythm=0x01,  // "hihat" rhythm mode
              v_topcym_rhythm=0x02, // "topcym" rhythm mode
              v_tomtom_rhythm=0x04, // "tomtom" rhythm mode
              v_snare_rhythm=0x08,  // "snare" rhythm mode
              v_bass_rhythm=0x10,   // "bass" rhythm mode
              v_all_rhythm=0x1F     // all rhythm modes
						 } VATRHYTHM;

	// VATVOICETYPE: Midi stuff

typedef enum {v_patch,              // Voice is derived from a Gravis patch
							v_fm_voice            // Voice is generated on the FM chip
						 } VATVOICETYPE;

	// MUSICTYPE: Id's for various music file types

typedef enum {v_musictype_error=0,
							v_musictype_unknown,
							v_musictype_mod,
							v_musictype_s3m,
							v_musictype_midi
						 } VATMUSICTYPE;

// backward compatibility
#define FM_HIHAT   v_hihat_rhythm
#define FM_TOPCYM  v_topcym_rhythm
#define FM_TOMTOM  v_tomtom_rhythm
#define FM_SNARE   v_snare_rhythm
#define FM_BASS    v_bass_rhythm


  // VATMIXER: Errors
#define NO_MIXER          -9998
#define DSP_NOT_SUPPORTED -9999

  // VATMIXER: MixerCommand

typedef enum {        /*__ Output Control __*/
                v_cd_out,    v_cd_lout,    v_cd_rout,
              v_line_out,  v_line_lout,  v_line_rout,
               v_mic_out,

                      /*__ Input Control __*/
              v_midi_in,       v_midi_lin_to_left,   v_midi_rin_to_right,
              v_midi_in_swap,  v_midi_lin_to_right,  v_midi_rin_to_left,
                v_cd_in,         v_cd_lin_to_left,     v_cd_rin_to_right,
                v_cd_in_swap,    v_cd_lin_to_right,    v_cd_rin_to_left,
              v_line_in,       v_line_lin_to_left,   v_line_rin_to_right,
              v_line_in_swap,  v_line_lin_to_right,  v_line_rin_to_left,
               v_mic_in,        v_mic_in_to_left,     v_mic_in_to_right,

                           /*__ Mute __*/
               v_mas_mute,   v_mas_lmute,   v_mas_rmute,
              v_wave_mute,  v_wave_lmute,  v_wave_rmute,
              v_midi_mute,  v_midi_lmute,  v_midi_rmute,
                v_fm_mute,    v_fm_lmute,    v_fm_rmute,
                v_cd_mute,    v_cd_lmute,    v_cd_rmute,
              v_line_mute,  v_line_lmute,  v_line_rmute,
               v_mic_mute,   v_mic_lmute,   v_mic_rmute,
              v_spkr_mute,  v_spkr_lmute,  v_spkr_rmute,

                          /*__ Volume __*/
               v_mas_volume,   v_mas_lvolume,   v_mas_rvolume,
              v_wave_volume,  v_wave_lvolume,  v_wave_rvolume,
              v_midi_volume,  v_midi_lvolume,  v_midi_rvolume,
                v_fm_volume,    v_fm_lvolume,    v_fm_rvolume,
                v_cd_volume,    v_cd_lvolume,    v_cd_rvolume,
              v_line_volume,  v_line_lvolume,  v_line_rvolume,
               v_mic_volume,
              v_spkr_volume,

                    /*__ Treble, Bass, Gain __*/
              v_mas_treble,  v_left_treble,  v_right_treble,
              v_mas_bass,    v_left_bass,    v_right_bass,
              v_out_gain,    v_lout_gain,     v_rout_gain,
               v_in_gain,     v_lin_gain,      v_rin_gain,
               v_in_agc,

                         /*__ Filters __*/
              v_in_filter,       v_out_filter,
              v_lowpass_filter,  v_stereo_switch,

                         /*__ Generic __*/
              dma_flip_flop

             } VATMIXER;


/*_________________________________________________________________________*\
                           \/ /              \ \/
                             <   STRUCTURES   >
                              \*____________*/

#ifdef __cplusplus                     // Wrapper for function prototypes.
extern "C" {                           // Necessary for C++ compilers.
#endif

  // The WAVE structure: holds Wave data in memory.

typedef struct wave {
	LONG id;
	DWORD sample_rate;
	DWORD byte_rate;
	BYTE stereo;
	BYTE loaded;
	SAMPLE *data;
	DWORD chunk_size;                    // size of this chunk in bytes
	DWORD sample_size;                   // size of entire linked sample
	struct wave  *next;                  				// points to next link.
	struct wave	*head;                  				// points to top link.
} WAVE;

	// PATCHSAMPLE Structure:  One patch can have serveal samples

typedef struct patchsample {
	LONG 		id;
	CHAR 		name[10];

	SAMPLE	*data;

	LONG 		start_fraction;
	LONG 		end_fraction;
	LONG 		size;

	LONG		loop_start;                  // Controls looping
	LONG		loop_end;
	LONG		sample_rate;
	LONG		low_frequency;
	LONG		high_frequency;
	LONG 		root_frequency;

	LONG		tune;
	LONG		balance;

	DWORD		envelope_rate[6];
	DWORD	  envelope_offset[6];

	LONG		tremolo_sweep;               // Tremolo controls
	LONG		tremolo_rate;
	LONG		tremolo_depth;
	LONG		vibrato_sweep;               // Vibrato controls
	LONG		vibrato_rate;
	LONG		vibrato_depth;

	BYTE		mode_looping;
	BYTE		mode_bi_dir_looping;
	BYTE		mode_backward_looping;
	BYTE		mode_sustain;
	BYTE		mode_envelopes;
	BYTE		mode_clamped_release;

	LONG		scale_frequency;
	LONG		scale_factor;

//	LONG 		note_decay;                  // Sustain conrols
//	LONG    release_decay;
	struct patchsample *next;

} PATCHSAMPLE;

	// PATCH Structure: holds a Gravis Ultrasound patch

typedef struct {
	LONG id;
	BYTE master_volume;
	CHAR name[32];
	CHAR instrument_name[17];
	PATCHSAMPLE *samplelist;

} PATCH;




	// The SOUNDEFFECT structure: holds information about playing Waves.

typedef struct soundeffect {
	SAMPLE  *data;                       // pointer to raw sound data
	WAVE    *wav;                        // pointer to sound struct
	DWORD   length;                      // length of the sample in bytes
	DWORD   dummy;
	DWORD   position;                    // data position used internally by sbint
	DWORD   dummy2;
	DWORD   *pos;                        // pointer to current byte position
	DWORD   pinc;                        // rate counter
	SHORT   repeat;                      // number of times to repeat sample
	BYTE    volume;                      // volume of the sample
	BYTE    pan;                         // panning value of the sample
	BYTE    buffer;
	BYTE    active;                      // indicates wether sample is playing
	VATSTATUS status;                    // indicates the play status
	LONG    handle;                      // unique id to perform ops with
	VATPLAYTYPE type;                    // fancy or plain or panning


	struct soundeffect  *chain;          // sound effect to jump to when done
	struct soundeffect  *next;           // Used internally for a linked list
	void  (*chainfunc)(LONG);
} SOUNDEFFECT;


	// The MOD structure: holds Mod data in memory.

typedef struct mod {
  CHAR          title[20];
  CHAR          sample_name[32][22];
  DWORD         slength[32],offset[32],repeat[32];
  CHAR          finetune[32];
  BYTE          volume[32],num_positions;
  BYTE          maxpattern,ptable[128];
  CHAR          sig[5];
  BYTE          *pattern_data[128];
  BYTE          num_samples;
  SAMPLE        *sdata[32];
  SHORT         repeatmusic;
  struct mod    *chain;
  void          (*chainfunc)(void);
} MOD;


  // The S3M structure: holds S3M data in memory.

typedef struct s3m {
  CHAR    title[28];                   // Up to 28 chars nul terminated
  CHAR    sample_name[100][28];        // Up to 100 samples.
  DWORD   slength[100];                // Sample length
  BYTE    sflag[100];                  // Sample flags like looping etc
  DWORD   loopbegin[100],loopend[100]; // Loop begin and end
  DWORD   c2spd[100];                  // Tuning of sample
  BYTE    volume[100];                 // Volume of instrument<default>
  SAMPLE  *sdata[100];                 // Pointer to sample data
  BYTE    insnum,patnum,flags;         // number of instruments and patterns
  BYTE    channelnum,orders;           // number of channels and orders in s3m
  BYTE    globalvol,initspeed,inittempo;//initial speed and tempo of song
  BYTE    mastervol;
  BYTE    order[256];                  // up to 255 orders in song
  SHORT   repeatmusic;
  struct s3m    *chain;
  void    (*chainfunc)(void);
  BYTE    *pattern_data[256];          // pointer to the pattern data
} S3M;


  // The CHANNEL structure: holds information about playing Mods and S3Ms.

typedef struct {
  DWORD         bufferdummy1;
  DWORD         position;
  DWORD         bufferdummy2;
  LONG          end;
//	DWORD         rlength,offset;
	LONG          rlength,offset;
	BYTE          sflag;
  WORD          sample_number;
  DWORD         *pos;
//	DWORD         counter,pinc;
	LONG          counter,pinc;
	LONG          period;
//	DWORD         period2,vibdepth,vibperiod;
	LONG         period2,vibdepth,vibperiod;
	WORD          count;
  LONG          data1,data2,data3,data4;
  LONG          vslide;
  LONG          porta;
  LONG          s3m_fine;
  LONG          fineperiod;
  LONG          fineadjust;
  LONG          finevol;
  CHAR          volume,volume2;
  CHAR          cut;
  BYTE          effect,x,y;
  BYTE          retrigger;
  SAMPLE        *sdata;
} CHANNEL;


  // The MIDI structure: holds Midi data in memory.

typedef struct midi {
	CHAR	title[32];
	SHORT format;                        // 0 or 1
  SHORT num_tracks;                    // 1 - 32
  SHORT divisions;                     // number ticks per quarter note
	LONG	tracksize[MAXMIDITRACKS];
	BYTE  *track[MAXMIDITRACKS];                    // Track data pointers
  SHORT repeat;
  struct midi *chain;
  void  (*chainfunc)(void);
} MIDI;


  // The VOICE structure: holds Midi Voice data for playing Midis.

typedef struct {
  SHORT owner_track;
  SHORT owner_channel;
  SHORT active;
  SHORT note;
	SHORT volume;
	LONG  handle;
	SHORT type;
} VOICE;


  // The INSTRUMENT structure: holds a Midi instrument definition.

typedef struct instrument {
  BYTE data[11];
  char name[32];
} INSTRUMENT;


  // The MIXER structure type holds the status of the sound card

typedef struct mixer_state {
  // Output Status Group    
  int cd_out;                // CD (L/R)   Output Enabled 
  int cd_lout;               // CD Left    Output Enabled 
  int cd_rout;               // CD Right   Output Enabled 
  int line_out;              // Line (L/R) Output Enabled 
  int line_lout;             // Line Left  Output Enabled 
  int line_rout;             // Line Right Output Enabled 
  int mic_out;               // MIC        Output Enabled 
   
  // Input Status Group
  int midi_lin_to_left;      // Midi Left  Input to Left  Enabled
  int midi_rin_to_right;     // Midi Right Input to Right Enabled
  int midi_lin_to_right;     // Midi Left  Input to Right Enabled
  int midi_rin_to_left;      // Midi Right Input to Left  Enabled
  int cd_lin_to_left;        // CD   Left  Input to Left  Enabled
  int cd_rin_to_right;       // CD   Right Input to Right Enabled
  int cd_lin_to_right;       // CD   Left  Input to Right Enabled
  int cd_rin_to_left;        // CD   Right Input to Left  Enabled
  int line_lin_to_left;      // Line Left  Input to Left  Enabled
  int line_rin_to_right;     // Line Right Input to Right Enabled
  int line_lin_to_right;     // Line Left  Input to Right Enabled
  int line_rin_to_left;      // Line Right Input to Left  Enabled
  int mic_in_to_left;        // Mic        Input to Left  Enabled
  int mic_in_to_right;       // Mic        Input to Right Enabled

  // Mute Status Group
  int mas_lmute;             // Master Left  Muted
  int mas_rmute;             // Master Right Muted
  int wave_lmute;            // Wave   Left  Muted
  int wave_rmute;            // Wave   Right Muted
  int midi_lmute;            // Midi   Left  Muted
  int midi_rmute;            // Midi   Right Muted
  int fm_lmute;              // FM     Left  Muted
  int fm_rmute;              // FM     Right Muted
  int cd_lmute;              // CD     Left  Muted
  int cd_rmute;              // CD     Right Muted
  int line_lmute;            // Line   Left  Muted
  int line_rmute;            // Line   Right Muted
  int mic_lmute;             // Mic    Left  Muted
  int mic_rmute;             // Mic    Right Muted
  int spkr_lmute;            // Spkr   Left  Muted
  int spkr_rmute;            // Spkr   Right Muted

  // Volume Group
  int mas_lvolume;           // Master  Left  Volume
  int mas_rvolume;           // Master  Right Volume
  int wave_lvolume;          // Wave    Left  Volume
  int wave_rvolume;          // Wave    Right Volume
  int cd_lvolume;            // CD      Left  Volume
  int cd_rvolume;            // CD      Right Volume
  int line_lvolume;          // Line    Left  Volume
  int line_rvolume;          // Line    Right Volume
  int midi_lvolume;          // Midi    Left  Volume
  int midi_rvolume;          // Midi    Right Volume
  int fm_lvolume;            // FM      Left  Volume
  int fm_rvolume;            // FM      Right Volume
  int mic_volume;            // Mic           Volume
  int spkr_volume;           // Speaker       Volume

  // Settings Group
  int left_treble;           // Master        Left  Treble
  int right_treble;          // Master        Right Treble
  int left_bass;             // Master        Left  Bass
  int right_bass;            // Master        Right Bass
  int lout_gain;             // Master Output Left  Gain
  int rout_gain;             // Master Output Right Gain
  int lin_gain;              // Master Input  Left  Gain
  int rin_gain;              // Master Input  Right Gain
  int in_agc;                // Master Input        AGC

  // Filter Group
  int input_filter;          // SB20 Input Filter
  int output_filter;         // SB20 Output Filter 
  int lowpass_filter;        // SB20 Lowpass Filter
  int stereo_switch;         // SB20 Stereo Switch

  // Generic Group
  int dma_flip_flop;         // Setting of the DMA Flip Flop
} MIXER_STATE;

typedef struct vat_state
{
  BYTE vat_vers_maj;         // VAT's major version number
  BYTE vat_vers_min;         // VAT's minor version number
  VATBOOL commercial;        // v_true: commercial copy
  char *register_string;     // registration info if commercial
  DWORD sample_rate;         // first argument to SBSetUp
  DWORD refresh_rate;        // second argument to SBSetUp
  VATBOOL allow_stereo;      // v_false: restricted to mono
  WORD bit_depth;            // 8-bit / 16-bit
  BYTE dsp_vers_maj;         // DSP major version number
  BYTE dsp_vers_min;         // DSP minor version number
  char *blaster_string;      // contents of BLASTER environment variable
  int blaster_ioport;        // BLASTER string 'A' element
  int blaster_irq;           // BLASTER string 'I' element
  int blaster_lowdma;        // BLASTER string 'D' element
  int blaster_highdma;       // BLASTER string 'H' element
  int blaster_mpuport;       // BLASTER string 'P' element
  int blaster_effects;       // BLASTER string 'E' element
  int blaster_cardtype;      // BLASTER string 'T' element
  int fm_addr;               // address being used for FM
  char *midi_string;         // contents of MIDI environment variable
  int midi_synth;            // MIDI string 'SYNTH' element
  int midi_map;              // MIDI string 'MAP' element
  int midi_mode;             // MIDI string 'MODE' element
  VATSTATUS status;          // availability of audio output
} VAT_STATE;


/*_________________________________________________________________________*\
                           \/ /             \ \/
                             <   FUNCTIONS   >
                              \*___________*/




              /*___ General Functions ___*/

       VATBOOL  VATStartUp(LONG newrate, DWORD Hertz,
                           VATBOOL allow_stereo, VATSTART card_detect);
          void  VATShutDown(void);
       VATBOOL  SBSetUp         (DWORD samplerate, DWORD hertz);
          void  SBCleanUp       (void);
          void  GoVarmint       (void);
          void  DropDeadVarmint (void);
          LONG  SampleRate      (void);
          WORD  VATVersion      (void);
					void 	SetLongBuffer		(BYTE *pointer, DWORD size);
	VATMUSICTYPE 	GetMusicType		(char *filename,char *errstring);


							/*___ Patched Note Functions ___*/
					LONG 	PlayNote 				(LONG midinote, PATCH *p);
			 VATBOOL 	NoteCommand 		(LONG handle, VATCOMMAND cmd);
		 VATSTATUS 	NoteStatus 			(LONG handle);
				 PATCH *LoadPatch				(CHAR *patchfile, CHAR *errstring);
					void 	FreePatch				(PATCH *pat);


							/*___ Wave Functions ___*/

          WAVE *LoadWave        (CHAR *wavefile, CHAR *errstring);
					int 	SaveWave				(CHAR *wavefile, WAVE *saveme, CHAR *errstring);
					WAVE *LoadWaveFromMemory(WAVE *w,SAMPLE *data, LONG l);
					void  FreeWave        (WAVE *wav);
          LONG  PlayWave        (WAVE *wav, int stop_dups, VATPLAYTYPE type);
           int  WaveSetting     (LONG handle, VATSETTING set, int value);
       VATBOOL  WaveCommand     (LONG handle, VATCOMMAND cmd);
     VATSTATUS  WaveStatus      (LONG handle);
          LONG  WaveChain       (LONG handle, WAVE  *wav, VATPLAYTYPE type);
			 VATBOOL  WaveChainFunc   (LONG handle, VOIDFUNCLONG);

// backward compatibility
#define PlaySound PlayWave
#define SoundActive WaveStatus
#define ChainSoundEffect WaveChain
#define AddChainFunction WaveChainFunc


              /*___ Mod Functions ___*/

           MOD *LoadMod         (CHAR *modfile, CHAR *errstring);
          void  FreeMod         (MOD *mod);
          void  PlayMod         (MOD *mod);
           int  ModSetting      (VATSETTING set, int value);
       VATBOOL  ModCommand      (VATCOMMAND cmd);
     VATSTATUS  ModStatus       (void);
       CHANNEL *ModChannels     (void);
          LONG  ModChannelMask  (LONG mask);
       VATBOOL  ModChain        (MOD *mod);
			 VATBOOL  ModChainFunc    (VOIDFUNCVOID);


              /*___ S3M Functions ___*/

           S3M *LoadS3M         (CHAR *s3mfile, CHAR *errstring);
          void  FreeS3M         (S3M *s3m);
          void  PlayS3M         (S3M *s3m);
           int  S3MSetting      (VATSETTING set, int value);
       VATBOOL  S3MCommand      (VATCOMMAND cmd);
     VATSTATUS  S3MStatus       (void);
       CHANNEL *S3MChannels     (void);
          LONG  S3MChannelMask  (LONG mask);
       VATBOOL  S3MChain        (S3M *s3m);
			 VATBOOL  S3MChainFunc    (VOIDFUNCVOID);


              /*___ Midi Functions ___*/

          MIDI *LoadMidi        (CHAR *midifile, CHAR *errstring);
          void  FreeMidi        (MIDI *midi);
          void  PlayMidi        (MIDI *midi);
           int  MidiSetting     (VATSETTING set, int value);
       VATBOOL  MidiCommand     (VATCOMMAND cmd);
     VATSTATUS  MidiStatus      (void);
       VATBOOL  MidiChain       (MIDI *midi);
			 VATBOOL  MidiChainFunc   (VOIDFUNCVOID);
    INSTRUMENT *LoadInstruments (CHAR *instfile);
    INSTRUMENT *MidiInstruments (INSTRUMENT *inst);
          BYTE *MidiPatchmap    (BYTE *map);
			 VATBOOL  MidiSetInstrumentPatch  (int instrument, PATCH *p);
				 PATCH *MidiGetInstrumentPatch  (int instrument);
			 VATBOOL  MidiSetPercussionPatch  (int instrument, PATCH *p);
				 PATCH *MidiGetPercussionPatch  (int instrument);


              /*___ FM Functions ___*/

       VATBOOL  FMEnable        (void);
          void  FMDisable       (void);
     VATSTATUS  FMStatus        (void);
           int  FMRhythm        (int mode);
          void  FMVoice         (BYTE channel, BYTE *data);
          BYTE  FMVolume        (BYTE channel, BYTE volume);
          BYTE  FMNote          (BYTE channel, BYTE note);
          WORD  FMFrequency     (BYTE channel, WORD freq);
          void  FMKeyOn         (BYTE channel);
          void  FMKeyOff        (BYTE channel);
          void  FMWrite         (WORD data);
          BYTE  FMChipStatus    (void);

// backward compatibility
#define FMDetect FMEnable
#define FMSetVoice FMVoice
#define FMSetVolume FMVolume
#define FMSetFrequency FMFrequency
#define FMSetNote FMNote
#define FMRythmOn FMRhythm


              /*___ MPU Functions ___*/

       VATBOOL  MPUEnable       (void);
          void  MPUDisable      (void);
     VATSTATUS  MPUStatus       (void);
          void  MPUPatch        (BYTE channel, BYTE patch);
          void  MPUPlayNote     (BYTE channel, BYTE note, BYTE volume);
          void  MPUStopNote     (BYTE channel, BYTE note);
          void  MPUWrite        (BYTE data);


              /*___ DSP Functions ___*/

       VATBOOL  DSPReset        (void);
          WORD  DSPVersion      (void);
          BYTE  DSPRead         (void);
          void  DSPWrite        (BYTE data);

// backward compatibility
#define DSPGetVersion DSPVersion


              /*___ Timer Functions ___*/

void _saveregs  MilliDelay      (WORD delay);
void _saveregs  MicroDelay      (WORD delay);
          void  TimerOn         (void);
          WORD  TimerOff        (void);


              /*___ Mixer Functions ___*/

           int  MixerSetting    (VATMIXER set, int value);
   MIXER_STATE *MixerState      (MIXER_STATE *mixer);


/*_________________________________________________________________________*\
                           \/ /             \ \/
                             <   VARIABLES   >
                              \*___________*/


  // SBERROR enumeration

typedef enum {fmerr=0,   // problem with FM
              nodsperr,  // problem with DSP
              irqerr,    // problem finding IRQ
              dmacherr,  // problem with DMA
              nomem      // problem with memory
             } SBERROR;

extern SBERROR     sberr;              // error index set by some functions
extern CHAR       *errname[];          // error list indexed by sberr
extern volatile DWORD vclock;          // VAT's internal clock counter
extern DWORD dma_bufferlen;         // Handles to Vat mix buffer
extern BYTE  *dma_buffer[2];
																		// Handles to long buffer pieces
extern BYTE		*longbuffer;
extern DWORD		longbufferpointer;
extern DWORD 	longbuffersize;


#ifdef __cplusplus
}                                      // End C++ prototype wrapper.
#endif


#endif // _VAT_H_
