/**************************************************************************
                        VARMINT'S AUDIO TOOLS 1.13

  VAT.C

    This file contains source code for Sound Blaster initialization
    and DSP access, plus some random stuff that does not belong
    anywhere else.


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
#include <dos.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include "vat.h"
#include "internal.h"
#include "varmint1.h"
#include "varmint2.h"



#ifdef COMMERCIAL
                               //12345678901234567890123456789012345678901234567890
CHAR       *checkstring1 = "GRID                                                   ";
#endif



                        /*  VAT VERSION NUMBER  */

/**************************************************************************/

WORD vat_version_number=0x010f;  // major version 1, minor version 15

/**************************************************************************/

                        /*  VAT VERSION NUMBER  */



extern WORD    fm_addr;
extern WORD    mpu_addr;

//-------------------------------- Local Defs

#define FM_DETECT         0x01
#define DSP_DETECT        0x02

#define DSP_GET_VERS      0xE1
#define DSP_INVOKE_INTR   0xF2
#define DSP_RESET         0x06
#define DSP_READ          0x0A
#define DSP_RSTATUS       0x0E
#define DSP_SAMPLE_RATE   0x40
#define DSP_SILENCE       0x80
#define DSP_SPKR_ON       0xD1
#define DSP_SPKR_OFF      0xD3
#define DSP_WRITE         0x0C
#define DSP_WSTATUS       0x0C

#define DMAAUTOINIT   0x58
#define DMAONESHOT    0x48

typedef enum {none,
              nodsp,
              adlib,
              sb20,
              sbpro
             } cardtype;

//-------------------------------- External functions used locally

void                  dbprintf(CHAR *string,...);
WORD                  mcalc(WORD micro);
void _saveregs        mdelay(DWORD delay);
#pragma aux mdelay=\
  "loop2: loop loop2"\
  parm [ecx];

void                  midiplayer(void);
void                  modplayer(void);
void                  wavplayer(void);
void                  s3mplayer(void);
void                  fm_init (void);
void                  mpu_init (void);


//-------------------------------- Internal Function prototypes

SHORT                 cardcheck(void);
static cardtype       checkhard(void);
void                  dmaset(BYTE  *sound_address,WORD len,BYTE channel);
void                  enableint(BYTE nr);
void                  disableint(BYTE nr);
SHORT                 getsbenv(void);
BYTE                  int2vect(BYTE intnr);
void  _saveregs _loadds interrupt sbint(void);
void                  sbremovevector(void);
void                  sbsetvector(void);
static SHORT          scanint(void);
static SHORT          testint(void);
void                  venable(void);
void                  vdisable(void);
cardtype              whichcard(void);
void                  real_free(WORD handle);
void                  *real_malloc(DWORD size,WORD* handle);
LONG                  SetSampleRate(LONG rate);

//-------------------------------- Global function pointers
                                // These are used by the interrupt routines
                                // To help keep track of interrupts that
                                // Get shuffled around.

void  _saveregs _loadds (interrupt  *handlerint)(void) = sbint;
static void  (interrupt *orgint)(void) = NULL;
static void  (interrupt *orgirqint)(void) = NULL;


//-------------------------------- setup data and variables

static WORD ioaddr[6]={0x220,0x240,0x210,0x230,0x250,0x260};
static BYTE intrx[8]={5,7,2,3,10,11,12,15};
WORD        io_addr= 0x220;
WORD        intnr= 5;
WORD        dma_ch=1;
WORD        card_id=1;
WORD        dsp_vers;
VATBOOL     dsp_high_speed=0;      // 0=low speed, 1=high speed
VATBOOL     allow_stereo_flag=1;   // 1=allow stereo, 0=block stereo
VATSTART    card_detect_flag=0;    // 0=Auto, 1=Blaster String, 2=Cfg File
WORD        mue3,mue23;
static WORD dma_adr[8]= {0x00,0x02,0x04,0x06,0xc0,0xc4,0xc8,0xcc};
static WORD dma_len[8]= {0x01,0x03,0x05,0x07,0xc2,0xc6,0xca,0xce};
static WORD dma_page[8]={0x87,0x83,0x81,0x82,0x8f,0x8b,0x89,0x8a};
SBERROR     sberr = 0;

CHAR        *errname[] = {
              "Cannot detect FMchip",
              "Cannot detect DSP",
              "Cannot find an open IRQ",
              "Cannot find an open DMA channel",
              "Cannot allocate memory for DMA buffer",
              "Cannot detect registration info"};
volatile SHORT         tst_cnt;
BYTE        dma_controlbyte = DMAAUTOINIT;

//-------------------------------- DMA/DSP mixer varaibles and data

SHORT       vol_table[64][256];        // Volume Table
SHORT       wav_vol_table[64][256];
SHORT       lpan[64][60],rpan[64][60];
DWORD       vat_stereo = 0;
DWORD       dma_bufferlen = 220;
BYTE    *dma_buffer[2] = {NULL,NULL};
SHORT       dma_currentbuffer = 0;
SHORT   *mix_buffer = NULL;
DWORD       internal_sample_rate = 11000;
WORD        realhandle;
DWORD       HZ;

BYTE		*longbuffer = NULL;
DWORD		longbufferpointer = 0;
DWORD 	longbuffersize = 1;

//-------------------------------- Miscellaneous varaibles

                                   // Used by MOD and S3M for vibrato calcs
SHORT         vsin[100] = {0,16,32,47,63,79,94,108,123,137,150,163,175,186,
              197,207,216,224,231,238,243,247,251,253,255,256,255,253,251,
              247,243,238,231,224,216,207,197,186,175,163,150,137,123,108,
              94,79,63,47,32,16,0,-16,-32,-47,-63,-79,-94,-108,-123,-137,
              -150,-163,-175,-186,-197,-207,-216,-224,-231,-238,-243,-247,
              -251,-253,-255,-256,-255,-253,-251,-247,-243,-238,-231,-224,
              -216,-207,-197,-186,-175,-163,-150,-137,-123,-108,-94,-79,
              -63,-47,-32,-16};

                                   // midi tempo counters used in sbint
LONG        midi_count = 256;
SHORT       midi_callfreq = 256;

SHORT       debug_lowdsp = v_false;
volatile SHORT       debug_reverseflipflop = v_false;
SHORT       debug_forceflipflop = -1;
SHORT       disabled = 0;
volatile WORD        DSP_overhead = 0;

WORD vsync_toolong = 4;           // This is the number of vclock ticks that
DWORD l=0;                        // tells us we have waited to long in
                                  // the VarmintVSync() function.
volatile DWORD       vclock=0;
volatile WORD        vsyncclock = 0;
                                  // This string is here to help debug
                                  // startup problems
CHAR        vatdebugstring[5000];
CHAR        vatapstr[255];

VAT_STATE internal_state;
VATSTATUS internal_status=v_nonexist;

#ifdef COMMERCIAL
                               //12345678901234567890123456789012345678901234567890
CHAR       *checkstring2 = "GUPC                                                   ";
#endif


/**************************************************************************
  void GoVarmint(void)
  void DropDeadVarmint(void)

  DESCRIPTION:  Starts/stops the interrupt routine for Varmint's audio tools

**************************************************************************/
void GoVarmint(void)
{
  LONG n;
  LONG id;
  int i;
  static int first=1;

  if (internal_status != v_stopped)
    return;

#if 0
  i = 0;
  n = 0L;
  for (i=0; i<22000; ++i) // // 22K = aprox length of sound
    n += varmintsound[i];

  if (n != -12513)
  {
    printf("VAT has been modified and will not be started!\n");
    fflush(stdout);
    while (1) {};
  }

#endif

  sbsetvector();                          // Install the sound kernel

                                          // Seems like later DSP versions
                                          // need to have the flipflop in
                                          // reverse order to remove static

  if(dsp_vers >= 0x400) debug_reverseflipflop = v_true;

  if(debug_forceflipflop != -1) debug_reverseflipflop = debug_forceflipflop;

  if(dsp_vers >= 0x400) {                 // SB 4.0(SB16) or better?
                                          // Set up DMA channel.
    dmaset(dma_buffer[0],dma_bufferlen*2-1,dma_ch);
                                          // (8 bit, DAC, Auto-init)
    DSPWrite(0xC6);                       // Generic DSP command

#ifdef SHAREWARE
    DSPWrite(0x00);                       // Send Mode byte (unsigned, not stereo)
    vat_stereo=0;
#else
    DSPWrite(0x20);                       // Send Mode byte (stereo,unsigned)
    vat_stereo=(DWORD)allow_stereo_flag;
#endif
    DSPWrite((dma_bufferlen-1) & 0xff);   // Write length low byte
    DSPWrite((dma_bufferlen-1) >> 8);     // Write length high byte
  }
  else if(dsp_vers >= 0x300) {                 // SB Pro or better?

    DSPWrite(0x48);                       // Set DMA
    DSPWrite((dma_bufferlen-1) & 0xff);   // Write length low byte
    DSPWrite((dma_bufferlen-1) >> 8);     // Write length high byte
    dmaset(dma_buffer[0],dma_bufferlen*2-1,dma_ch);

    DSPWrite(0x1c);                       // Set DSP for High speed
                                          // Autoinit 8bit DMA
  }  else if(dsp_vers >= 0x200) {            // SB2.0 or better?

    DSPWrite(0x48);                       // Set DMA
    DSPWrite((dma_bufferlen-1) & 0xff);   // Write length low byte
    DSPWrite((dma_bufferlen-1) >> 8);     // Write length high byte
    dmaset(dma_buffer[0],dma_bufferlen*2-1,dma_ch);

    DSPWrite(0x1C);                       // Set DSP for Autoinit 8bit DMA
  }
  else {                                  // SB 1.x?
    dma_controlbyte = DMAONESHOT;
  }

  DSPWrite(DSP_INVOKE_INTR);              // Ignition!

  n = vclock;
  while(n == vclock);                     // Wait for at least one interrupt
                                          // to happen so that the internal
                                          // initilizations happens.
  internal_state.status = v_started;
  internal_status = v_started;
#if defined(DEMO) || defined(SHAREWARE)
  if (first) {
    showvatlogo2();
    id = PlayWave (varmint1, 0, v_fancy);
    while (WaveStatus (id) == v_started);
    for (i=0; i<3; i++) {
      id = PlayWave (varmint2, 0, v_fancy);
      WaveSetting (id, v_volume, 63-i*20);
      MilliDelay (300);
    }
    while (WaveStatus (id) == v_started);
    endvatlogo();
    first = 0;
  }
#endif
}

void DropDeadVarmint(void)
{
  if (internal_status != v_started)
    return;

  DSPWrite(0xD0);                         // Halt DMA
  if(dsp_vers >= 0x200) DSPWrite(0xDA);   // Halt Autoinitialized DMA
  DSPWrite(0xD0);                         // Halt DMA
  sbremovevector();                       // Clean up sound kernel
  internal_state.status = v_stopped;
  internal_status = v_stopped;
}



/*  ---------------  DSP  Stuff ------------ */




/**************************************************************************
  VATBOOL DSPReset()

  DESCRIPTION: Resets the DSP

  RETURNS:
    v_true or v_false to indicate wether reset was sucsessful

**************************************************************************/
VATBOOL DSPReset(void)
{
  SHORT i;

  dbprintf("DSPReset() - <entry>\n");

  mdelay((DWORD)mue3);                         // Wait 3 microseconds
  VOUTPORTB(io_addr+DSP_RESET,1);        // Write a 1 to the DSP reset port
  mdelay((DWORD)mue3);                         // Wait 3 microseconds
  VOUTPORTB(io_addr+DSP_RESET,0);        // Write a 0 to the DSP reset port


  for(i=0;i<50;i++) {                   // DSP should send back an 0xaa
    mdelay((DWORD)mue3);
    if(DSPRead()==0xaa) return(v_true);
  }

  return(v_false);
}


/**************************************************************************
  BYTE DSPRead()

  DESCRIPTION:  reads a byte from the dsp

  RETURNS:
    The byte that was read

**************************************************************************/
BYTE DSPRead(void)
{
                                      // Read until high bit of status port
                                      // is set.
  while(!(VINPORTB(io_addr+DSP_RSTATUS) &  0x80));
  return (VINPORTB(io_addr+DSP_READ)); // Send back the value of the read port
}

/**************************************************************************
  void DSPWrite(BYTE data)

  DESCRIPTION: Writes a byte to the DSP

  INPUT:
    output  byte to write to the DSP

**************************************************************************/
void DSPWrite(BYTE data)
{
                                      // Read until high bit of status port
                                      // is clear.
  while((VINPORTB(io_addr+DSP_WSTATUS) &  0x80));
  VOUTPORTB(io_addr+DSP_WRITE,data); // Write our byte
}



/**************************************************************************
  WORD DSPVersion()

  DESCRIPTION:  Get the version number of the DSP

  RETURNS:
    DSP version number. High byte = major version, low byte = minor version

**************************************************************************/
WORD DSPVersion(void)
{
  DSPWrite(DSP_GET_VERS);
  return((WORD)DSPRead()*256+DSPRead());
}


/**************************************************************************
  SHORT getsbenv()

  DESCRIPTION:  Get sound blaster information from the environment
                variable "BLASTER"

  RETURNS:
    v_true if successful, v_false if there was a problem

**************************************************************************/
SHORT getsbenv(void)
{
  static CHAR *envstr;                    // Environment strings must be
                                          // static or global
  CHAR str[255];
  SHORT i;
  SHORT outvalue = v_true;

  dbprintf("getsbenv() - <entry>\n");

  envstr=getenv("BLASTER");
  if(!envstr) return(v_false);              // no blaster variable? go home
  strcpy(str,envstr);

  dbprintf("getsbenv() - Raw BLASTER=%s\n",str);

                                          // Convert string to upper case
  for(i = 0 ; i < strlen(str); i++) *(str+i) = toupper(*(str+i));
                                          // pick apart variable for info.
                                          // Io address
  for(i = 0; *(str+i) != 0 && *(str + i) != 'A'; i++);
  if(*(str+i)){
    sscanf(str+i+1,"%hx",&io_addr);
    if(io_addr<0x210 || io_addr>0x260) outvalue = v_false;
  }
                                          // MIDI port address
  for(i = 0; *(str+i) != 0 && *(str + i) != 'P'; i++);
  if(*(str+i)) sscanf(str+i+1,"%hx", &mpu_addr);

                                          // Dma channel number
  for(i = 0; *(str+i) != 0 && *(str + i) != 'D'; i++);
  if(*(str+i)){
    sscanf(str+i+1,"%hd",&dma_ch);
    if(dma_ch > 7) {
      outvalue = (v_false);                 // only 0-7 allowed
      dma_ch = 1;                         // Set a reasonable default
    }
  }

                                          // IRQ interrupt number
  for(i = 0; *(str+i) != 0 && *(str + i) != 'I'; i++);
  if(*(str+i)){
    sscanf(str+i+1,"%hd",&intnr);
    if(intnr < 2  || intnr > 15) {
      outvalue =  (v_false);
      intnr = 7;
    }
  }

                                          // card_id
  for(i = 0; *(str+i) != 0 && *(str + i) != 'T'; i++);
  if(*(str+i)){
    sscanf(str+i+1,"%hd",&card_id);
    if(card_id < 1 && card_id > 6) outvalue = v_false; // 1 = SB 1.x, 6 = SB AWE
  }

  dbprintf("getsbenv() - Processed BLASTER=A%X P%X I%u D%u T%u\n",io_addr,mpu_addr,intnr,dma_ch,card_id);

  return(outvalue);
}



/*  ---------------  Misc.  Stuff ------------ */



/**************************************************************************
  SHORT cardcheck()

  DESCRIPTION:  Check for both FM chip and DSP

  RETURNS:
    Returns a value that has FM and DSP status information

**************************************************************************/
SHORT cardcheck(void)
{
  SHORT ret=0;

  if (FMEnable ())
    ret |= FM_DETECT;
  if (DSPReset ())
    ret |= DSP_DETECT;
  return (ret);
}


/**************************************************************************
static void  _saveregs interrupt testnint()

  DESCRIPTION:  This function is stored as an interrupt to test
                various interrupt vectors by testint()

**************************************************************************/
static void  _saveregs interrupt testnint(void)
{
  tst_cnt++;                               // increment our test counter

  VINPORTB(io_addr+DSP_RSTATUS);            // Acknowledge DSP interrupt

  VOUTPORTB(0x20,0x20);                     // Clear PIC
  VOUTPORTB(0xa0,0x20);
}



/**************************************************************************
  static SHORT testint()

  DESCRIPTION:  This function is used by scanint() to test interrupt
                stuff.  It installs a test interrupt in the
                requested spot (intnr) then sees if the DSP can
                use it.

  RETURNS:
    v_true if successful, v_false if not

**************************************************************************/
static SHORT testint(void)
{
  SHORT i;
  BYTE int1,int2;

  orgint=_dos_getvect(int2vect(intnr));     // Save original interrupt
  tst_cnt=0;                                // reset our test interrupt counter.

  int1 = VINPORTB(0x21);                     // Save PIC settings
  int2 = VINPORTB(0xa1);

  vdisable();                               // Disable interrupts
  VOUTPORTB(0x21,0xff);                      // Turn off all interrupts
  VOUTPORTB(0xa1,0xff);

                                            // put in our test interrupt
  _dos_setvect(int2vect(intnr),testnint);
  enableint(intnr);                         //  Turn on that interrupt
  venable();                                // Enable interrupts

  DSPWrite(DSP_INVOKE_INTR);                // Force DSP interrupt

  for (i=0;i<30000;i++) if(tst_cnt) break;   // wait for interrupt code to happen

  if(i == 30000) {                          // normalize things if the interrupt
                                            // did not get called.
    VINPORTB(io_addr+DSP_RSTATUS);           // Acknowledge DSP interrupt

    VOUTPORTB(0x20,0x20);                    // Clear PIC
    VOUTPORTB(0xa0,0x20);
  }

  vdisable();                               // disable inerrupts
  disableint(intnr);                        // put original interrupt back
  _dos_setvect(int2vect(intnr),orgint);

  VOUTPORTB(0x21,int1);                      // restore PIC settings
  VOUTPORTB(0xa1,int2);
  venable();                                // enable interrupts

  if(i==30000) return(v_false);               // Timed out? No good!
  else return(v_true);
}


/**************************************************************************
  static SHORT scanint()

  DESCRIPTION: This makes sure that the interrupt number picked by the
                IRQ specification is a good choice.

  RETURNS:
    0 if failed, Interrupt number if successful
**************************************************************************/
static SHORT scanint(void)
{
  SHORT i;

  dbprintf("scanint() - <entry>\n");

  if(testint()) return(intnr);   // Original choice good?

  dbprintf("scanint() - original interrupt failed (%d)\n",intnr);

  for(i=0;i<8;i++)                // Try our eight best guesses
  {
    intnr=intrx[i];
    sprintf(vatapstr,"scanint() - trying interrupt: %d\n",intnr);
    if(testint()) return(intnr);
  }

  dbprintf("scanint() - All interrupt tries failed\n");

  return(0);
}


/**************************************************************************
  static cardtype checkhard()

  DESCRIPTION:  Checks hardware for DSP and FM chip

  RETURNS:
    The  detected Card Type.  (For now this is only an SB2.0)

**************************************************************************/
static cardtype checkhard(void)
{
  SHORT ret;

  dbprintf("checkhard() - <entry>\n");

  ret=DSPReset();

  dbprintf("checkhard() - DSPreset: %d\n",ret);

  if(ret)
  {
    if(!scanint()) {                    // Scan IRQ's
      sberr= irqerr;
      return(none);
    }
    dbprintf("checkhard() - scanint chose: %d\n",intnr);

/*** OLD (address checking now encoded into FMEnable()
    fm_addr=FM_ADLIB_ADDRESS;           // Check adlib chip first
    if(!FMDetect()) {
      fm_addr=io_addr+FM_BOTH_OFF;      // Check SB chip
      if(!FMDetect()) {
        sberr = fmerr;
        return(none);                   // no fm? -> damaged!
      }
    }
***/
    if (!FMEnable ()) {
      sberr = fmerr;
      return (none);
    }
    dbprintf("checkhard() - FM address: %X\n",fm_addr);

    return(sb20);
  }
  sberr = nodsperr;
  return(none);
}


/**************************************************************************
  cardtype whichcard()

  DESCRIPTION:  Calls various functions to make sure you've
                got a Sound Blaster.  Also checks to make sure that
                it has the right sound blaster environment settings.

  RETURNS:
    0 on failure, cardtype on success
**************************************************************************/
cardtype whichcard(void)
{
  cardtype cret = nodsp;
  SHORT i;

  dbprintf("whichcard() - <entry>\n");

  if(getsbenv()) cret=checkhard();      // grab environment variable
  if(cret!=nodsp) return(cret);         // If dsp is there, then go home

  dbprintf("whichcard() - Original settings failed\n");


  for(i=0;i<6;i++)                      // scan around for a better io address
  {
    io_addr=ioaddr[i];
    sprintf(vatapstr,"whichcard() - Trying new io address: %X\n",io_addr);

    cret=checkhard();
    if(cret!=nodsp) return(cret);
  }
  dbprintf("whichcard() - FAILED COMPLETELY\n");

  return(none);                         // Uh oh.
}


/**************************************************************************
  Void VATShutDown()

  DESCRIPTION: Shut VAT Down!

**************************************************************************/
void VATShutDown(void)
{
  DropDeadVarmint();
  SBCleanUp();
}


/**************************************************************************
  void SBCleanUp()

  DESCRIPTION: This conveniently cleans up all the stuff done by SBSetUp()
               and other sound functions

  RETURNS:
    v_true on success, v_false on failure

**************************************************************************/
void SBCleanUp(void)
{
  SHORT i;

  switch (internal_status) {
  case v_nonexist:
    return;
  case v_started:
    DropDeadVarmint ();
  }

  DSPWrite (DSP_SPKR_OFF);

  real_free (realhandle);
  VFREE (mix_buffer);
  fm_reset ();
  for (i=0; i<9; i++)
    FMVolume (i, 0);
  mpu_reset ();
  internal_state.status = v_nonexist;
  internal_status = v_nonexist;
}

/**************************************************************************
  VATBOOL VATStartUp()

  DESCRIPTION: Get VAT up and running!

  RETURNS:
    v_true on success, v_false on failure

**************************************************************************/
  VATBOOL VATStartUp(LONG     newrate,
                     DWORD    Hertz,
                     VATBOOL  allow_stereo,
                     VATSTART card_detect)
{
  // FIX!
  allow_stereo_flag = v_true;

  card_detect_flag  = card_detect;

  if (!SBSetUp(newrate,Hertz))
  {
    return(v_false);
  }
  GoVarmint();
  return(v_true);
}

/**************************************************************************
  VATBOOL SBSetUp()

  DESCRIPTION: Sets up the sound blaster for action.  This is the only
               function a programmer should really use.  Most of the
               nitty gritty is handled internally.

  RETURNS:
    v_true on success, v_false on failure

**************************************************************************/
VATBOOL SBSetUp(LONG newrate,DWORD Hertz)
{
  SHORT i,x,y;
  char tempstring[56];

  if (internal_status != v_nonexist)
    return v_false;

#ifdef COMMERCIAL
  for (i=5; i<55; i++)
    tempstring[i] = checkstring2[i] ^ ((191 * i) % 256);
  tempstring[i] = '\0';
  if (strcmp (checkstring1+5, tempstring+5)) {
    sberr = 5;
    return (v_false);
  }
#endif

  HZ=Hertz;
                                   // clear out the mixing buffer
  strcpy (vatdebugstring, "*** DEBUGGING STRING ***\n");
  dma_currentbuffer = 0;

  dbprintf("Varmint's Audio Tools Version %s\n",VAT_VERSION);
  dbprintf("SBSetUp() - InitTimerFunctions\n");

  InitTimerFunctions();         // Initialize counter 2 for timing functions

  // GC moved these here so inits will occur immediately, regardless of
  // whether GoVarmint is called. This means SBSetUp () *MUST* be called
  // before using ANY other element of VAT.
  initwav();         // Initialize the different modules.
  initmod();         // Some initializations here aren't
  inits3m();         // necessary unless we're going into
	initmid();         // GoVarmint, but most are.
	initnote();
	fm_init ();
  mpu_init ();

                                // Calculate some special delays.
  mue3=mcalc(6) ;
  mue23=mcalc(46) ;

  dbprintf("SBSetUp() - mcalcs- [m3: %u] [m23: %u]\n",mue3,mue23);

                                        // Go and check the hardware

  if(whichcard()==none) return(v_false);

                                        // Get DSP ready
  dsp_vers=DSPGetVersion();
  if(debug_lowdsp) dsp_vers = debug_lowdsp;

  if(dsp_vers>=0x400)vat_stereo=(DWORD)allow_stereo_flag;

  DSPWrite(DSP_SPKR_ON);

  dbprintf("SBSetUp() - DSP version: %d.%02d\n",dsp_vers>>8, dsp_vers & 0xFF);

  // Some cards require a different low speed/high speed DSP command
  //  depending on the mixing rate, this flag tells the DSP handler
  //  which command to issue for these cards.
  dsp_high_speed = v_false;

  if (dsp_vers <= 0x200)  // SB1.5 or SB MCV
  {
    if (newrate <  4000) newrate =  4000;
    if (newrate > 22000) newrate = 22000;
  }
  if (dsp_vers == 0x201)  // SB2.0
  {
    if (newrate <  4000) newrate =  4000;
    if (newrate > 22000) newrate = 22000;
//    if (newrate > 44100) newrate = 44100;
//    if (newrate > 22000) dsp_high_speed = v_true;
  }
  if (dsp_vers < 0x400)  // SBPro
  {
    if (newrate <  4000) newrate =  4000;
    if (newrate > 22000) newrate = 22000;
//    if (newrate > 44100) newrate = 44100;
//    if (newrate > 22000) dsp_high_speed = v_true;
  }
  if (dsp_vers < 0x500)  // SB-16
  {
    if (newrate <  5000) newrate =  5000;
    if (newrate > 44100) newrate = 44100;
  }

#ifdef SHAREWARE
  newrate=11000;
  vat_stereo=0;
#endif

  dma_bufferlen=(SetSampleRate(newrate)*(vat_stereo+1))/Hertz/4;
  if(dma_bufferlen&1)dma_bufferlen++;
                                        // Set the dma buffer to the
                                        // max allowed.
  for (y=0; y<64; ++y){                 // Make pre-calculated Volume Table
    for (x=0; x<256; ++x){
      vol_table[y][x] = (y * (x-128)) / 64;
      wav_vol_table[y][x] = (y * (x-128)) / 32;
    }
  }
  for (y=0; y<64; ++y){                 // Make pre-calculated Volume Table
    for (x=0; x<60; ++x){
      rpan[y][x] = (y*x)/60;
    }
  }
  for (y=0; y<64; ++y){                 // Make pre-calculated Volume Table
    for (x=0; x<60; ++x){
      lpan[y][x] = rpan[y][59-x];
    }
  }

                                        // Allocate space for playback buffer
  dma_buffer[0] = (BYTE *)real_malloc(dma_bufferlen*2+5,&realhandle);
  if(!dma_buffer[0]) {
    sberr = nomem;
    return(v_false);
  }
  dma_buffer[1] = dma_buffer[0]+dma_bufferlen;


                                        // Allocate space for Mixing buffer
  mix_buffer = (SHORT *)VMALLOC(dma_bufferlen*2+10);
  if(!mix_buffer) {
    sberr = nomem;
    return(v_false);
  }
                                        // Silence the buffers
  for(i = 0; i <= dma_bufferlen; i++) {
    *(dma_buffer[0]+i) = 127;
    *(dma_buffer[1]+i) = 127;
    *(mix_buffer+i) = 127;
  }

  dbprintf("SBSetUp() - Processed BLASTER=A%X P%X I%u D%u T%u\n",io_addr,mpu_addr,intnr,dma_ch,card_id);

  internal_state.vat_vers_maj = vat_version_number >> 8;
  internal_state.vat_vers_min = vat_version_number & 0xFF;
#ifdef COMMERCIAL
  internal_state.commercial = v_true;
  internal_state.register_string = strdup (checkstring1+5);
#else
  internal_state.commercial = v_false;
  internal_state.register_string = strdup ("Demo Version (unregistered, non-commercial)");
#endif
  internal_state.sample_rate = internal_sample_rate;
  internal_state.refresh_rate = HZ;
  internal_state.allow_stereo = vat_stereo;
  internal_state.bit_depth = 8;
  internal_state.dsp_vers_maj = dsp_vers >> 8;
  internal_state.dsp_vers_min = dsp_vers & 0xFF;
  internal_state.blaster_string = getenv("BLASTER");
  if (!internal_state.blaster_string)
    internal_state.blaster_string = strdup ("Undefined");
  internal_state.blaster_ioport = io_addr;
  internal_state.blaster_irq = intnr;
  internal_state.blaster_lowdma = dma_ch;
  internal_state.blaster_highdma = -1;
  internal_state.blaster_mpuport = mpu_addr;
  internal_state.blaster_effects = -1;
  internal_state.blaster_cardtype = card_id;
  internal_state.fm_addr = fm_addr;
  internal_state.midi_string = strdup ("Unused");
  internal_state.midi_synth = -1;
  internal_state.midi_map = -1;
  internal_state.midi_mode = -1;
  internal_state.status = v_stopped;
  internal_status = v_stopped;

  return(v_true);
}

/**************************************************************************
  LONG SetSampleRate(LONG rate)

  DESCRIPTION:  Sets the sample rate (specified in hz).

                Note:  The sample rate most likely will not be exactly
                equal to the rate specified in the argument argument since
                the Sound blaster can only accept rates in increments of
                400 hz.

  INPUTS:
    rate    playback rate in hertz

  RETURNS:
    The actual value of the new sample rate.

**************************************************************************/
LONG SetSampleRate(LONG rate)
{
  LONG val;

  val=256-1000000L/rate;

  DSPWrite(DSP_SAMPLE_RATE);
  DSPWrite((BYTE)val);
                                      // This helps other functions
                                      // To know how fast the DSP is going
  internal_sample_rate = (DWORD)(1000000L/(256-val));
  return (LONG)internal_sample_rate;
}

LONG SampleRate ()
{
  return (LONG)internal_sample_rate;
}

WORD VATVersion ()
{
  return (vat_version_number);
}

/**************************************************************************
  void dmaset(BYTE  *sound_address,WORD len,BYTE channel)

  DESCRIPTION:  This programs the DMA controller to start a single pass
                output transfer.

                (Draeden of VLA has provided some good information for
                DMA programming in his INTRO to DMA document)

  INPUTS:
    sound_address   Regular address of the DMA playback buffer
    len             length of the DMA buffer in bytes minus one
    channel         DMA  channel to use

**************************************************************************/
void dmaset(BYTE  *sound_address,WORD len,BYTE channel)
{
  DWORD adrl;
  WORD adr;
  BYTE page;

  adrl=(DWORD)sound_address;          // convert address to 20 bit format
  adr=(WORD)adrl;                     // extract page address
  page=(BYTE)(adrl>>16);              // extract page number

                                      // PREPARE DMA.
                                      //   (Channels 0-3 have different
                                      //   command ports than 4-7.)

                                      // SET CHANNEL, MASK BIT AND MODE

  if(channel <4) {                    // Chanels 0-3?
    VOUTPORTB(0x0a,channel+4);          // write channel number with 3rd bit set
    VOUTPORTB(0x0c,0);                  // Clear Byte Pointer

                                      // Set the mode.  The mode is determined
                                      // in GoVarmint().
    VOUTPORTB(0x0b,dma_controlbyte+channel);
  }
  else {                              // channels 4-7
    VOUTPORTB(0xd4,channel);            // write channel number
    VOUTPORTB(0xd8,0);                  // Clear Byte Pointer

                                      // Set the mode.  The mode is determined
                                      // in GoVarmint().
    VOUTPORTB(0xd6,dma_controlbyte+channel-4);
  }
                                      // SET TRANSFER INFORMATION

  VOUTPORTB(dma_adr[channel],adr&0xff);// Write address low byte
  VOUTPORTB(dma_adr[channel],adr>>8);  // Write address high byte

  VOUTPORTB(dma_len[channel],len&0xff);// Write length  low byte
  VOUTPORTB(dma_len[channel],len>>8);  // Write length  high byte

  VOUTPORTB(dma_page[channel],page);   // Write page

                                      // CLEAR MASK BITS
  if(channel < 4) VOUTPORTB(0x0a,channel);
  else VOUTPORTB(0xd4,channel & 0x03);

}

/**************************************************************************
  void polldma(BYTE channel)

  DESCRIPTION:  This function poles the DMA controller to find out how many
                bytes are left in the current transfer.

                As of version 0.4, this function is no longer used, but
                I thought it might be useful to someone else, so I've only
                commented it out.
**************************************************************************/
/*WORD polldma(BYTE channel)
{
  BYTE low1,high1,low2,high2;

  disableint(intnr);             // Turn off the interrupt so we don't get
                                  // caught with our pants down.
  asm {
    mov dx,0x0c                   // Flip the master reset switch
    mov al,0
    out dx,al
  }
  _DX = dma_len[channel];         // Load in the counter address
                                  // read position twice, becasue sometimes
                                  // there is a problem
  asm{
    in al,dx                      // read the low byte first
    mov low1,al
    in al,dx                      // read the high byte next
    mov high1,al

    in al,dx                      // read the low byte first
    mov low2,al
    in al,dx                      // read the high byte next
    mov high2,al

  }
  enableint(intnr);              // Done, so we'll put the interrupt back.

                                  // High bytes the same? Use second reading
  if(high1 == high2)return((WORD)high2*256+low2);
                                  // else the First reading is accurate
  return(high1*256+low1);

}*/


/**************************************************************************
  void sbsetvector()

  DESCRIPTION:  Installs the DMA interrupt vector.  This makes it so that
                sbint() is called whenever a DMA transfer is finished

**************************************************************************/
void sbsetvector(void)
{
  orgirqint=_dos_getvect(int2vect(intnr));
  _dos_setvect(int2vect(intnr),handlerint);     /* set vector to our routine */
  enableint(intnr);                             /* enable sb interrupt */
}


/**************************************************************************
  void sbremovevector()

  DESCRIPTION:  Removes the DMA interrupt vector

**************************************************************************/
void sbremovevector(void)
{
  disableint(intnr);                            /* disable sb interrupt */
  _dos_setvect(int2vect(intnr),orgirqint);      /* restore org intr vector */
}

/**************************************************************************
  BYTE int2vect(BYTE intnr)

  DESCRIPTION:  This function converts a PIC irq number to a true
                interrupt vector number.  For PC's with a 286 or greater,
                irq's 0-7  refer to interrupts 0x08 - 0x0F and
                irq's 8-15 refer to interrupts 0x70 - 0x77.

  INPUTS:
    intnr   IRQ number

  RETURNS:
    Actual vector corresponding to the IRQ

**************************************************************************/
BYTE int2vect(BYTE intnr)
{
  if(intnr>7) return(intnr + 0x68);
  else return(intnr+8);
}


/**************************************************************************
  void enableint(BYTE nr)

  DESCRIPTION:  Enables an IRQ interrupt using the Programmable
                interrupt controller (PIC)

                To enable a interrupt, you want to turn its PIC bit off.
                Let's say that you want to turn on interrupt 3.  The
                code works something like this:


                    BIT:                 76543210

                    1 << nr             00001000
                    ~(1 << nr)          11110111 (mask)
                                        01001101 (setting)
                    setting & mask      01000101
                                            ^
                                            |
                          Notice how bit 3 is set to zero.

  INPUTS;
    nr    IRQ number

**************************************************************************/
void enableint(BYTE nr)
{
  BYTE mask,setting;

  if(nr<8) {                             // First controller?
    mask = ~(1 << nr);                  // Create interrupt mask
    setting = VINPORTB(0x21) & mask;     // Turn off the proper bit
    VOUTPORTB(0x21,setting);             // Write back the result
  }
  else {                                // Second Controller?
    mask = ~(1 << (nr-8));              // Create interrupt mask
    setting = VINPORTB(0xa1) & mask;     // Turn off the proper bit
    VOUTPORTB(0xa1,setting);             // Write back the result
  }
}


/**************************************************************************
  void disableint(BYTE nr)

  DESCRIPTION:  Disables an IRQ interrupt using the Programmable
                interrupt controller.

                To disable a interrupt, you want to turn its PIC bit on.
                Let's say that you want to turn off interrupt 3.  The
                code works something like this:


                    BIT:                 76543210

                    1 << nr             00001000
                    ~(1 << nr)          11110111 (mask)
                                        01000101 (setting)
                    ~setting            10111010
                    (~setting) & mask    10110010 (new value of setting)
                    ~setting            01001101

                                            ^
                                            |
                          Notice how bit 3 is set to one.
  INPUTS;
    nr    IRQ number

**************************************************************************/
void disableint(BYTE nr)
{
  BYTE mask,setting;

  if(nr<8) {                            // First controller?
    mask = ~(1 << nr);                  // Create interrupt mask
    setting = (~VINPORTB(0x21)) & mask;  // Turn on the proper bit
    VOUTPORTB(0x21,~setting);            // Write back the result
  }
  else {                                // Second Controller?
    mask = ~(1 << (nr-8));              // Create interrupt mask
    setting = (~VINPORTB(0xa1)) & mask;  // Turn on the proper bit
    VOUTPORTB(0xa1,~setting);            // Write back the result
  }
}
void testdisableint(BYTE nr,BYTE *test)
{
  BYTE mask,setting;

  mask = ~(1 << nr);                  // Create interrupt mask
  setting = (~(*test)) & mask;  // Turn on the proper bit
  *test = ~setting;            // Write back the result
}


/**************************************************************************
  void VarmintVSync(void)

  DESCRIPTION: This vsync function pays attention to vsyncclock so that we
                 never miss a vsync.  The vsync can be missed if sbint
                gets called while we are waiting for the retrace.

                The variable vsync_toolong should be roughly equalt to
                the number of times you expect sbint to get called between
                vertical retraces.  The will be afffected by dma_bufferlen,
                sample_rate, and the frequency of the VGA monitor

**************************************************************************/
void VarmintVSync(void)
{
  while(!(VINPORTB(0x3da)&0x08)) {}
/*
  while(!(VINPORTB(0x3da)&0x08)) {        // Wait for retrace to start
    if(vsyncclock>vsync_toolong) break;   // Have we waited too long?
  }

  while(VINPORTB(0x3da)&0x08);              // Wait for retrace to finish
  vsyncclock = 0;                         // reset the clock
*/
}


/**************************************************************************
  void TimeVSync(void)

  DESCRIPTION:  This times a vertical retrace and sets the variable
                vsynctoolong to an appropriate value based on the sample
                rate and dma_bufferlen.

                This should be called before GoVarmint();

**************************************************************************/
void TimeVSync(void)
{
  WORD i;

  vsync_toolong = 5;              // Make sure this does not trip us up.
                                  // These are default values
  vsyncclock = 0;

  VarmintVSync();                 // Wait for a Vync to end

  for(i = 0; i < 30; i++){        // Average 30 retrace steps
    TimerOn();                    // Time the next vsync
    VarmintVSync();
    l += TimerOff();
  }
  l /= 30;
  if(l < 100) l = 17000;          // Sanity measure  (70hz refresh rate)

                                  // Figure how many vclock ticks will occur
                                  // During a retrace.
//  printf("%d\n",l);

  vsync_toolong =
    (WORD)((l * internal_sample_rate) / 1193000L / dma_bufferlen) + 1;

}


/**************************************************************************
  WORD PercentOverhead(WORD ticks)

  DESCRIPTION:  Calculates the Percentage CPU overhead that the
                blaster interrupt consumes.

  INPUTS:
    ticks       Number of clock ticks that pass during the interrupt

  RETURNS:
    An interger percentage (* 10) based on dma_bufferlen and sample rate.
    ie:  0 = 0% overhead, 1000 = 100.0% overhead


**************************************************************************/
WORD PercentOverhead(WORD ticks)
{
  return(WORD)((ticks * HZ) / 1193);
}


/**************************************************************************
  void vdisable(void)

  DESCRIPTION:  Special interrupt disable function for VAT.  THis is really
                only designed for use once inside the varmint handler function

**************************************************************************/
void vdisable(void)
{
  if(disabled) {                 // Don't do anything if interrupts are
    disabled++;                  // already disabled.
    return;
  }

  _disable();                    // disable the interrupts
  disabled++;
}

/**************************************************************************
  void venable(void)

  DESCRIPTION:  Special interrupt enable function for VAT

**************************************************************************/
void venable(void)
{
  disabled--;

  if(!disabled) _enable();       // enable the interrupts if this is the
                                 // outermost enable.
}

/**************************************************************************
  void dbprintf(CHAR *string,...)

  DESCRIPTION:  Special printf function that writes to the debugging string.

**************************************************************************/
void dbprintf(CHAR *string,...)
{
  va_list ap;

  va_start(ap, string);                  // sort out variable argument list
  vsprintf(vatapstr,string,ap);          // dump output to a string
  strcat(vatdebugstring,vatapstr);       // add string to debug string.

  va_end(ap);                            // clean up
}

/************************************************************************
  void *real_malloc(word size,int* handle)

  description:this function allocates memory from the low 640k
              at this point no error checking is done to verify it works
*************************************************************************/

void *real_malloc(DWORD size,WORD* handle)
{
union REGS dos;

dos.x.eax=0x100;  //function in dpmi to allocate real memory
dos.x.ebx=(size+15)>>4; //change it to 16 byte block

int386(0x31,&dos,&dos);
   //ax holds segment
   //dx holds base selector of allocated block

if (dos.x.cflag)
   return(NULL);

*handle=dos.w.dx;
return((void*)((dos.x.eax &0xffff)<<4));
  //change segement to a protected mode pointer
}

/*************************************************************************
  void real_free(int handle)

  description: this function frees up memory allocated by
               the real malloc function.
**************************************************************************/

void real_free(WORD handle)
{
union REGS dos;
dos.w.ax=0x101;
dos.w.dx=handle;
int386(0x31,&dos,&dos);
}


/**************************************************************************
	void SetLongBuffer(BYTE *pointer, DWORD size)

	DESCRIPTION: Sets up the long databuffer.  The long buffer is for when
							 you need access to long streams of data without having to
							 worry about your data collection getting interrupted.

**************************************************************************/
void SetLongBuffer(BYTE *pointer, DWORD size)
{
	longbuffersize = size;
	longbuffer = pointer;
}


/**************************************************************************
	VATMUSICTYPE GetMusicType(char *filename,char *errstring)

	DESCRIPTION: Tries to determine the type of music file by looking at the
							 header of the specified file.
	INPUTS:
		errstring		Should be at least 255 allocated bytes.

**************************************************************************/
VATMUSICTYPE GetMusicType(char *filename,char *errstring)
{
	char header[2000];
	char tag[32];
	int length;
	FILE *input;
																 // Open the file in question
	input = fopen(filename,"rb");
	if(!input) {
		sprintf(errstring,"Cannot open file: %s",filename);
		return v_musictype_error;
	}
																 // read in the header
	length = fread(header,1,2000,input);
	fclose(input);
																 // Check for MIDI
	if(length>5) {
		memcpy(tag,header,4);
		tag[4] = 0;
		if(!strcmp(tag,"MThd")) return v_musictype_midi;
	}
																 // Check for MOD.  Note:  I hear that
																 // Some Mod files do not contain
																 // tag, though I have not seen any.
	if(length>1100) {
		memcpy(tag,header+1080,4);
		tag[4] = 0;
		if(!strcmp(tag,"M.K.")) return v_musictype_mod;
		if(!strcmp(tag,"M!K!")) return v_musictype_mod;
		if(!strcmp(tag,"FLT4")) return v_musictype_mod;
	}
																 // Check for S3M
																 // Note: an S3M does not have a
																 // proper tag.  The only thing I
																 // can say for sure is that if
																 // byte #29 is not 16, then this
																 // file is not an s3m.  This is
																 // why I check for it last.
	if(length>30) {
		if(header[29]== 16) return v_musictype_s3m;
	}

	return v_musictype_unknown;
}

/**************************************************************************
  void MPUExit(void)

  DESCRIPTION:  Sends the UART mode command to the MPU.  You must call
                MPUEnter first.

**************************************************************************/
/*
void MPUExit(void)
{

  if(!mpu_available) return;
  vdisable();
  VOUTPORTB(midi_mpuport+1,0xFF);          // Reset the MPU
  venable();
}
*/

