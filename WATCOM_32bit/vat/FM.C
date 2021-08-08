#include <stdio.h>
#include "vat.h"
#include "internal.h"


  /************************************************************************\
 |*                            /              \                            *|
 |*                           <  FM Functions  >                           *|
 |*                            \______________/                            *|
  \                                                                        / 
  *|  INT:                                                                |* 
  *|        void  fm_init      (void);                                    |* 
  *|        void  fm_reset     (void);                                    |* 
  /                                                                        \ 
 |*   EXT:                                                                 *|
 |*      VATBOOL  FMEnable     (void);                                     *|
 |*         void  FMDisable    (void);                                     *|
 |*    VATSTATUS  FMStatus     (void);                                     *|
 |*          int  FMRhythm     (int mode);                                 *|
 |*         void  FMVoice      (BYTE channel, BYTE *data);                 *|
 |*          int  FMVolume     (BYTE channel, int volume);                 *|
 |*          int  FMNote       (BYTE channel, int note);                   *|
 |*          int  FMFrequency  (BYTE channel, int freq);                   *|
 |*         void  FMKeyOn      (BYTE channel);                             *|
 |*         void  FMKeyOff     (BYTE channel);                             *|
 |*         void  FMWrite      (WORD data);                                *|
 |*         BYTE  FMChipStatus (void);                                     *|
 |*                                                                        *|
  \************************************************************************/


                    /*____ EXTERNAL VARIABLES ____*/


extern WORD io_addr;


                    /*____ EXTERNAL FUNCTIONS ____*/


WORD mcalc (WORD micro);
void _saveregs mdelay(DWORD delay);
#pragma aux mdelay=\
  "loop2: loop loop2"\
  parm [ecx];


                    /*____ INTERNAL VARIABLES ____*/


     WORD  fm_addr;
VATSTATUS  fm_status;
     BYTE  fm_keyscale1[9], fm_keyscale2[9], fm_volume[9], fm_rhythm;
     WORD  fm_keydata[9];
    DWORD  md6, md46, md160;
     WORD  fm_opoffset[9] = {0x0000, 0x0100, 0x0200,
                             0x0800, 0x0900, 0x0A00,
                             0x1000, 0x1100, 0x1200};

#define FM_ADLIB_ADDRESS  0x0388
#define FM_SB_ADDRESS (io_addr + 0x0008)


                    /*____ INTERNAL FUNCTIONS ____*/


  /************************************************************************\
 |*                                                                        *|
 |*  void fm_init (void);                                           v1.1   *|
  \                                                                        / 
  *|  Variable init function.  Called from SBSetUp.                       |*
  /                                                                        \ 
 |*  IN:                                                                   *|
 |*    (none)                                                              *|
 |*                                                                        *|
 |*  OUT:                                                                  *|
 |*    (none)                                                              *|
 |*                                                                        *|
 |*  INCIDENTALS:                                                          *|
 |*    fm_status, fm_volume, fm_keydata                                    *|
 |*                                                                        *|
  \************************************************************************/

void fm_init ()
{
  int channel;

  // calculate delays
  md6 = mcalc (6);
  md46 = mcalc (46);
  md160 = mcalc (160);

  // set volumes to zero (63 to FM chip)
  for (channel=0; channel<9; channel++)
    fm_volume[channel] = 63;

  // clear octave/f-number values
  for (channel=0; channel<9; channel++)
    fm_keydata[channel] = 0;

  // clear rhythm settings
  fm_rhythm = 0;

  // reset fm registers - only called here and in SBCleanUp
  fm_reset ();
}



  /************************************************************************\
 |*                                                                        *|
 |*  void fm_reset (void);                                          v1.1   *|
  \                                                                        / 
  *|  Reset FM output.  Clear all registers, set a few appropriate bits.  |*
  *|  Called from fm_init and SBCleanUp.                                  |*
  /                                                                        \ 
 |*  IN:                                                                   *|
 |*    (none)                                                              *|
 |*                                                                        *|
 |*  OUT:                                                                  *|
 |*    (none)                                                              *|
 |*                                                                        *|
 |*  INCIDENTALS:                                                          *|
 |*    (none)                                                              *|
 |*                                                                        *|
  \************************************************************************/

void fm_reset ()
{
  WORD reg;

  // reset fm_status to undetected/uninitialized
  fm_status = v_nonexist;

  // clear registers (1-244) <- why F5 then?
  for (reg=0x0100; reg<=0xF500; reg+=0x0100)
    FMWrite (reg);

  // turn on wave form control
  FMWrite (0x0120);

  // set AM and vibrato to high (AM depth to 4.8 dB, VIB depth to 14 cent)
  FMWrite (0xBDC0);
}


                    /*____ EXTERNAL FUNCTIONS ____*/


  /************************************************************************\
 |*                                                                        *|
 |*  VATBOOL FMEnable (void);                                       v1.1   *|
  \                                                                        / 
  *|  Enable FM output.  If the FM chip has not been set up yet, try      |*
  *|  to do so.  Set fm_status accordingly.                               |*
  /                                                                        \ 
 |*  IN:                                                                   *|
 |*    (none)                                                              *|
 |*                                                                        *|
 |*  OUT:                                                                  *|
 |*    VATBOOL success                                                     *|
 |*      v_true on success, v_false on failure                             *|
 |*                                                                        *|
 |*  INCIDENTALS:                                                          *|
 |*    fm_status, fm_addr                                                  *|
 |*                                                                        *|
  \************************************************************************/

VATBOOL FMEnable ()
{
  BYTE result1, result2;

  // check FM status
  if (fm_status == v_unavail)
    return v_false;
  if (fm_status == v_started)
    return v_true;

  if (fm_status == v_nonexist) {
    fm_addr = FM_ADLIB_ADDRESS;

    // check two addresses: FM_ADLIB_ADDRESS and FM_SB_ADDRESS
    //  loop exits when FM chip is detected and initialized or
    //  detection fails at both addresses
    while (1) {
      // reset LSI test register
      FMWrite (0x0100);

      /*
      *  Check for existence of FM chip:
      *    1. Reset timers.
      *    2. Reset expiration flags in status register.
      *    3. Read and store status register.
      *    4. Set timer 1 to 0xFF so it will immediately overflow.
      *    5. Start timer 1.
      *    6. Delay at least 80 microseconds.
      *    7. Read and store status register.
      *    8. Reset timers.
      *    9. Reset expiration flags in status register.
      *   10. Check stored results of #3 and #7 above:
      *        #3 & 0xE0 should be 0x00, meaning no timers have expired.
      *        #7 & 0xE0 should be 0xC0, meaning timer 1 has expired.
      */ 

      // reset timers
      FMWrite (0x0460);

      // reset expiration flags in status register
      FMWrite (0x0480);

      // read and store status register
      result1 = FMChipStatus ();

      // set timer 1 to 0xFF so it will immediately overflow
      FMWrite (0x02FF);

      // start timer 1 (mask out timer 2 and turn on timer 1 control)
      FMWrite (0x0421);

      // delay at least 80 microseconds
      if (fm_addr == FM_ADLIB_ADDRESS)
        MilliDelay (42);  // why?
      else
        mdelay(md160);

      // read and store status register
      result2 = FMChipStatus ();

      // reset timers
      FMWrite (0x0460);

      // reset expiration flags in status register
      FMWrite (0x0480);

      // check stored results
      if ((result1 & 0xE0) != 0x00 || (result2 & 0xE0) != 0xC0) {
        if (fm_addr != FM_ADLIB_ADDRESS) {
          fm_status = v_unavail;   // if this is the second try, give up
          return v_false;
        } else
          fm_addr = FM_SB_ADDRESS; // otherwise, try a different address
      } else
        break; // successful detection
    }
  }

  // if status is v_stopped or v_nonexist (and above was successful)
  fm_status = v_started;
  return v_true;
}



  /************************************************************************\
 |*                                                                        *|
 |*  void FMDisable (void);                                         v1.1   *|
  \                                                                        / 
  *|  Disable FM output.  Do not reset the port.                          |*
  /                                                                        \ 
 |*  IN:                                                                   *|
 |*    (none)                                                              *|
 |*                                                                        *|
 |*  OUT:                                                                  *|
 |*    (none)                                                              *|
 |*                                                                        *|
 |*  INCIDENTALS:                                                          *|
 |*    fm_status                                                           *|
 |*                                                                        *|
  \************************************************************************/

void FMDisable ()
{
  if (fm_status == v_started)
    fm_status = v_stopped;
}



  /************************************************************************\
 |*                                                                        *|
 |*  VATSTATUS FMStatus (void);                                     v1.1   *|
  \                                                                        / 
  *|  Retrieve status of FM output and chip initialization.               |*
  /                                                                        \ 
 |*  IN:                                                                   *|
 |*    (none)                                                              *|
 |*                                                                        *|
 |*  OUT:                                                                  *|
 |*    VATSTATUS status                                                    *|
 |*      v_nonexist: FM chip has not been detected/initialized             *|
 |*      v_unavail: attempt to detect/initialize FM chip has failed        *|
 |*      v_stopped: midi output is not being directed to FM chip           *|
 |*      v_started: midi output is being directed to FM chip               *|
 |*                                                                        *|
 |*  INCIDENTALS:                                                          *|
 |*    (none)                                                              *|
 |*                                                                        *|
  \************************************************************************/

VATSTATUS FMStatus ()
{
  return fm_status;
}



  /************************************************************************\
 |*                                                                        *|
 |*  int FMRhythm (int mode);                                       v1.1   *|
  \                                                                        / 
  *|  If mode is GET_SETTING, return the stored rhythm settings.          |*
  *|  Otherwise, set the specified FM rhythm mode(s).   If any modes      |*
  *|  are set, set the "rhythm-on" bit.  If all modes are unset, clear    |*
  *|  the "rhythm-on" bit.  Will not accept values outside valid range:   |*
  *|    mode:   0 - v_all_rhythm                                          |*
  /                                                                        \
 |*  IN:                                                                   *|
 |*    int mode                                                            *|
 |*      the rhythm mode(s) to set, as a bitfield                          *|
 |*                                                                        *|
 |*  OUT:                                                                  *|
 |*    int mode                                                            *|
 |*      the stored rhythm settings, as a bitfield                         *|
 |*                                                                        *|
 |*  INCIDENTALS:                                                          *|
 |*    fm_rhythm                                                           *|
 |*                                                                        *|
  \************************************************************************/

int FMRhythm (int mode)
{
  // check fm_status
  if (fm_status == v_nonexist || fm_status == v_unavail)
    return -1;

  if (mode == GET_SETTING)
    // return rhythm settings as a bitfield
    return fm_rhythm;

  // check mode range
  if (mode < 0 || mode > v_all_rhythm)
    return -1;

  if (!mode)
    // clear the rhythm mode(s) and the "rhythm-on" bit, preserving AM/Vib
    FMWrite (0xBDC0);
  else
    // set the rhythm mode(s) and the "rhythm-on" bit, preserving AM/Vib
    FMWrite (0xBDE0 | mode);

  // store the current mode
  fm_rhythm = mode;

  // return rhythm settings as a bitfield
  return mode;
}



  /************************************************************************\
 |*                                                                        *|
 |*  void FMVoice (BYTE channel, BYTE *data);                       v1.1   *|
  \                                                                        / 
  *|  "Load" an "instrument", defined as an 11-byte array, into the       |*
  *|  specified FM channel.  Requires FM init, but not Midi-FM output.    |*
  /                                                                        \
 |*  IN:                                                                   *|
 |*    BYTE channel                                                        *|
 |*      the FM channel number to assign the specified data to             *|
 |*    BYTE *data                                                          *|
 |*      the 11-byte data to assign:                                       *|
 |*        0  AM / vib / envtype / scale rate / mod freq mult (oper 1)     *|
 |*        1  AM / vib / envtype / scale rate / mod freq mult (oper 2)     *|
 |*        2  Key level scaling / total level (oper 1)                     *|
 |*        3  Key level scaling / total level (oper 2)                     *|
 |*        4  Attack Rate / Decay rate  (oper 1)                           *|
 |*        5  Attack Rate / Decay rate  (oper 2)                           *|
 |*        6  Sustain Level / Release rate (oper 1)                        *|
 |*        7  Sustain Level / Release rate (oper 2)                        *|
 |*        8  Feedback / Algorithm                                         *|
 |*        9  Waveform Select (oper 1)                                     *|
 |*       10  Waveform Select (oper 2)                                     *|
 |*                                                                        *|
 |*  OUT:                                                                  *|
 |*    (none)                                                              *|
 |*                                                                        *|
 |*  INCIDENTALS:                                                          *|
 |*    fm_keyscale1, fm_keyscale2                                          *|
 |*                                                                        *|
  \************************************************************************/

void FMVoice (BYTE channel, BYTE *data)
{
  BYTE data2, data3;

  // check data validity
  if (!data)
    return;

  // check fm_status
  if (fm_status == v_nonexist || fm_status == v_unavail)
    return;

  // check channel number
  if (channel > 8)
    return;

  // since keyscaling is set here (and volume is preserved), and volume
  // is set elsewhere (in FMVolume), keep track of each voice's keyscaling
  fm_keyscale1[channel] = (data[2] & 0xC0);
  fm_keyscale2[channel] = (data[3] & 0xC0);

  // calculate new keyscale/volume data elements to preserve volume
  data2 = fm_keyscale1[channel] | fm_volume[channel];
  data3 = fm_keyscale2[channel] | fm_volume[channel];

  // assign voice data
  FMWrite ((0x2000 + fm_opoffset[channel]) | data[0]);
  FMWrite ((0x2300 + fm_opoffset[channel]) | data[1]);
  FMWrite ((0x4000 + fm_opoffset[channel]) | data2);
  FMWrite ((0x4300 + fm_opoffset[channel]) | data3);
  FMWrite ((0x6000 + fm_opoffset[channel]) | data[4]);
  FMWrite ((0x6300 + fm_opoffset[channel]) | data[5]);
  FMWrite ((0x8000 + fm_opoffset[channel]) | data[6]);
  FMWrite ((0x8300 + fm_opoffset[channel]) | data[7]);
  FMWrite ((0xC000 + channel*0x100)        | data[8]);
  FMWrite ((0xE000 + fm_opoffset[channel]) | data[9]);
  FMWrite ((0xE300 + fm_opoffset[channel]) | data[10]);
}



  /************************************************************************\
 |*                                                                        *|
 |*  BYTE FMVolume (BYTE channel, BYTE volume);                     v1.1   *|
  \                                                                        / 
  *|  If volume is GET_SETTING, return the specified channel's stored     |*
  *|  volume setting.  Otherwise, assign the specified volume to the      |*
  *|  specified FM channel.  Will clip volume to valid range:             |*
  *|    volume:   0 - 63                                                  |*
  /                                                                        \ 
 |*  IN:                                                                   *|
 |*    BYTE channel                                                        *|
 |*      the FM channel to assign the specified volume to                  *|
 |*    int volume                                                          *|
 |*      the volume to assign                                              *|
 |*                                                                        *|
 |*  OUT:                                                                  *|
 |*    int volume                                                          *|
 |*      the channel's stored volume setting, inverted                     *|
 |*                                                                        *|
 |*  INCIDENTALS:                                                          *|
 |*    fm_volume                                                           *|
 |*                                                                        *|
  \************************************************************************/

BYTE FMVolume (BYTE channel, BYTE volume)
{
  BYTE data2, data3;

  // check fm_status
  if (fm_status == v_nonexist || fm_status == v_unavail)
    return (BYTE)-1;

  // check channel number
  if (channel > 8)
    return (BYTE)-1;

  if (volume == (BYTE)GET_SETTING)
    // return the volume (must invert for human consumption)
    return 63 - fm_volume[channel];

  // check volume range
  if (volume > 63)
    volume = 63;

  // since volume is set here (and keyscaling is preserved), and keyscaling
  // is set elsewhere (in FMSetVoice), keep track of each voice's volume
  // The value is reversed on the FM chip - 0 is loudest, 63 is quietest.
  fm_volume[channel] = 63 - volume;

  // calculate new keyscale/volume data elements to preserve keyscaling
  data2 = fm_keyscale1[channel] | fm_volume[channel];
  data3 = fm_keyscale2[channel] | fm_volume[channel];

  // assign voice data to set new volume
  FMWrite ((0x4000 + fm_opoffset[channel]) | data2);
  FMWrite ((0x4300 + fm_opoffset[channel]) | data3);

  // return the volume
  return volume;
}



  /************************************************************************\
 |*                                                                        *|
 |*  BYTE FMNote (BYTE channel, BYTE note);                         v1.1   *|
  \                                                                        / 
  *|  If note is GET_SETTING, calculate a note from the specified         |*
  *|  channel's stored keydata and return it.  Otherwise, assign the      |*
  *|  octave/f-number corresponding with the specified note to the        |*
  *|  specified FM channel.  Will clip note to valid range:               |*
  *|    note:    24 - 119                                                 |*
  /                                                                        \
 |*  IN:                                                                   *|
 |*    BYTE channel                                                        *|
 |*      the FM channel to assign the specified frequency to               *|
 |*    BYTE note                                                           *|
 |*      the note used to calculate the octave/f-number to assign          *|
 |*                                                                        *|
 |*  OUT:                                                                  *|
 |*    BYTE note                                                           *|
 |*      the channel's stored keydata as a note value                      *|
 |*                                                                        *|
 |*  INCIDENTALS:                                                          *|
 |*    fm_keydata                                                          *|
 |*                                                                        *|
  \************************************************************************/

BYTE FMNote (BYTE channel, BYTE note)
{
  int i;
  SHORT octave;
  WORD fnum, fdiff;
  static WORD fnumbers[12] = {0x0157, 0x016B, 0x0181, 0x0198, 0x01B0, 0x01CA,
                              0x01E5, 0x0202, 0x0220, 0x0241, 0x0263, 0x0287};

  // check fm_status
  if (fm_status == v_nonexist || fm_status == v_unavail)
    return (BYTE)-1;

  // check channel number
  if (channel > 8)
    return (BYTE)-1;

  if (note == (BYTE)GET_SETTING) {
    // mask out octave from channel's stored keydata
    octave = (fm_keydata[channel] & 0x1C00) >> 10;

    // mask out f-number from channel's stored keydata
    fnum = fm_keydata[channel] & 0x03FF;

    // determine octave-independent note based on f-number
    note = -1;
    fdiff = 0xFFFF;
    for (i=0; i<12; i++)
      if (abs (fnum - fnumbers[i]) < fdiff) {
        note = i;
        fdiff = abs (fnum - fnumbers[i]);
      }

    // adjust note based on octave
    note += (octave + 1) * 12;  // octave 1 begins at 24

    // return the note
    return note;
  }

  // check note range
  if (note < 24)
    note = 24;
  else if (note > 119)
    note = 119;

   // determine the corresponding octave and octave-independent note
  octave = (note - 12) / 12;  // octave 1 begins at 24
  note %= 12;

  // save the two bytes representing the new octave/f-number assignment
  fm_keydata[channel] = (octave << 10) | fnumbers[note];

//  FMWrite ((0xA000 + channel*0x100) | (fm_keydata[channel] & 0x00FF));

  // return the note
  return note;
}



  /************************************************************************\
 |*                                                                        *|
 |*  int FMFrequency (BYTE channel, int freq);                      v1.1   *|
  \                                                                        / 
  *|  If freq is GET_SETTING, calculate a frequency from the specified    |*
  *|  channel's stored keydata and return it.  Otherwise, assign the      |*
  *|  octave/f-number corresponding with the specified frequency to the   |*
  *|  specified FM channel.  Will clip freq to valid range:               |*
  *|    freq:    16 - 4095                                                |*
  /                                                                        \ 
 |*  IN:                                                                   *|
 |*    BYTE channel                                                        *|
 |*      the FM channel to assign the octave/f-number to                   *|
 |*    WORD freq                                                           *|
 |*      the frequency used to calculate the octave/f-number to assign     *|
 |*                                                                        *|
 |*  OUT:                                                                  *|
 |*    WORD freq                                                           *|
 |*      the channel's stored keydata as a frequency value                 *|
 |*                                                                        *|
 |*  INCIDENTALS:                                                          *|
 |*    fm_keydata                                                          *|
 |*                                                                        *|
  \************************************************************************/

WORD FMFrequency (BYTE channel, WORD freq)
{
  SHORT octave;
  WORD ftmp, fnum;

  // check fm_status
  if (fm_status == v_nonexist || fm_status == v_unavail)
    return (WORD)-1;

  // check channel number
  if (channel > 8)
    return (WORD)-1;

  if (freq == (WORD)GET_SETTING) {
    // mask out octave from channel's stored keydata
    octave = (fm_keydata[channel] & 0x1C00) >> 10;

    // mask out f-number from channel's stored keydata
    fnum = fm_keydata[channel] & 0x03FF;

    // calculate frequency based on octave and f-number
    freq = fnum * 3125L / (1 << (16-octave));

    // return the frequency
    return freq;
  }

  // check frequency range
  if (freq < 16)
    freq = 16;
  else if (freq > 4095)
    freq = 4095;

  // determine the corresponding octave
  for (ftmp=freq, octave=0; ftmp>=32; ftmp>>=1, octave++);

  // determine "f-number", an octave-independent value for a note
  //  (1 << (20-octave)) / 50000L == (1 << (16-octave)) / 3125L
  fnum = freq * (1 << (16-octave)) / 3125L;

  // save the two bytes representing the new octave/f-number assignment
  fm_keydata[channel] = (octave << 10) | fnum;

//  FMWrite ((0xA000 + channel*0x100) | (fm_keydata[channel] & 0x00FF));

  // return the frequency
  return freq;
}



  /************************************************************************\
 |*                                                                        *|
 |*  void FMKeyOn (BYTE channel);                                   v1.1   *|
  \                                                                        / 
  *|  Assign stored octave/f-number keydata to the specified FM channel   |*
  *|  and set the "key-on" bit to turn it on.                             |*
  /                                                                        \
 |*  IN:                                                                   *|
 |*    BYTE channel                                                        *|
 |*      the FM channel to turn on                                         *|
 |*                                                                        *|
 |*  OUT:                                                                  *|
 |*    (none)                                                              *|
 |*                                                                        *|
 |*  INCIDENTALS:                                                          *|
 |*    (none)                                                              *|
 |*                                                                        *|
  \************************************************************************/

void FMKeyOn (BYTE channel)
{
  // check fm_status
  if (fm_status == v_nonexist || fm_status == v_unavail)
    return;

  // check channel number
  if (channel > 8)
    return;

  // send the low bits of the stored octave/f-number data to the FM chip
  FMWrite ((0xA000 + channel*0x100) | (fm_keydata[channel] & 0x00FF));

  // send the high bits of the stored data and set the key-on bit
  FMWrite ((0xB020 + channel*0x100) | ((fm_keydata[channel] & 0xFF00) >> 8));
}



  /************************************************************************\
 |*                                                                        *|
 |*  void FMKeyOff (BYTE channel);                                  v1.1   *|
  \                                                                        / 
  *|  Clear octave/f-number keydata for the specified FM channel and      |*
  *|  clear the "key-on" bit to turn it off.                              |*
  /                                                                        \
 |*  IN:                                                                   *|
 |*    BYTE channel                                                        *|
 |*      the FM channel to turn off                                        *|
 |*                                                                        *|
 |*  OUT:                                                                  *|
 |*    (none)                                                              *|
 |*                                                                        *|
 |*  INCIDENTALS:                                                          *|
 |*    (none)                                                              *|
 |*                                                                        *|
  \************************************************************************/

void FMKeyOff (BYTE channel)
{
  // check fm_status
  if (fm_status == v_nonexist || fm_status == v_unavail)
    return;

  // check channel number
  if (channel > 8)
    return;

  // send the high bits of the stored data and clear the key-on bit
  FMWrite ((0xB000 + channel*0x100) | ((fm_keydata[channel] & 0xFF00) >> 8));
}



  /************************************************************************\
 |*                                                                        *|
 |*  void FMWrite (WORD data);                                      v1.1   *|
  \                                                                        / 
  *|  Write the specified value to the specified FM register.             |*
  /                                                                        \
 |*  IN:                                                                   *|
 |*    WORD data                                                           *|
 |*      the register to write to and the value to write, as a WORD        *|
 |*                                                                        *|
 |*  OUT:                                                                  *|
 |*    (none)                                                              *|
 |*                                                                        *|
 |*  INCIDENTALS:                                                          *|
 |*    (none)                                                              *|
 |*                                                                        *|
  \************************************************************************/

void FMWrite (WORD data)
{
  BYTE reg, value;

  // extract the register as the high bits of the value
  reg = (data & 0xFF00) >> 8;

  // extract the value as the low bits of the value
  value = data & 0x00FF;

  // delay at least 3 microseconds
  mdelay(md6);

  // write the register to the FM address/status port
  VOUTPORTB(fm_addr, reg);

  // delay at least 3 microseconds
  mdelay(md6);

  // write the value to the FM data port
  VOUTPORTB(fm_addr+1, value);

  // delay at least 23 microseconds
  mdelay(md46);
}



  /************************************************************************\
 |*                                                                        *|
 |*  BYTE FMChipStatus (void);                                      v1.1   *|
  \                                                                        / 
  *|  Read the status byte of the FM chip.                                |*
  /                                                                        \ 
 |*  IN:                                                                   *|
 |*    (none)                                                              *|
 |*                                                                        *|
 |*  OUT:                                                                  *|
 |*    (none)                                                              *|
 |*                                                                        *|
 |*  INCIDENTALS:                                                          *|
 |*    (none)                                                              *|
 |*                                                                        *|
  \************************************************************************/

BYTE FMChipStatus ()
{
  return (VINPORTB(fm_addr));
}



/*** UNUSED ***

static WORD FM_off[9]={0,0x100,0x200,0x800,0x900,0xa00,0x1000,0x1100,0x1200};
static BYTE FM_fnr[12]={0x57,0x6b,0x81,0x98,0xb0,0xca,0xe5,0x02,0x20,0x41,0x63,0x87};
static BYTE FM_key_or[12]={1,1,1,1,1,1,1,2,2,2,2,2};
static BYTE FM_key[9];
static BYTE FM_keyscale1[9];
static BYTE FM_keyscale2[9];
static BYTE FM_vol[9] = {0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f};
static WORD rhythm=0xbd00;


**************************************************************************
  void FMWrite(WORD data)

  DESCRIPTION: Writes a byte to the FM chip.

  INPUTS:
      data    High byte contains the register number, low byte
              contains the data to write to that register.

**************************************************************************
void FMWrite(WORD data)
{
  BYTE reg,value;

  reg = (data & 0xff00)>>8;       // extract register and data value
  value = data & 0x00ff;

  mdelay((DWORD)mue3);                   // Wait three microseconds
  VOUTPORTB(fm_addr,reg);          // Write the register
  mdelay((DWORD)mue3);                   // Wait three microseconds

  VOUTPORTB(fm_addr+1,value);      // Write the data
  mdelay((DWORD)mue23);                  // Wait 23 microseconds

}

**************************************************************************
  void FMReset()

  DESCRIPTION:  Resets the FM chip by clearing all the registers then
                setting a few appropriate bits.

**************************************************************************
void FMReset(void)
{
  WORD i;
  for(i = 0; i <= 0xf500 ; i+= 0x100) FMWrite(i);
  FMWrite(0x0120);                 // Turn on Wave form control
  FMWrite(0xbdc0);                 // Set AM and Vibrato to high
}


**************************************************************************
  BYTE FMStatus()

  DESCRIPTION:  Reads the status byte of the FM chip

  RETURNS:  The value at fm_addr

**************************************************************************
BYTE FMStatus(void)
{
  return (VINPORTB(fm_addr));

}


**************************************************************************
  SHORT FMDetect()

  DESCRIPTION:  Detects the presence of an FM chip

  RETURNS:  A boolean value indicating wether or not test was successful

**************************************************************************
SHORT FMDetect(void)
{
  FMWrite(0x0100);                    // init Test register

  FMWrite(0x0460);                    // reset both timer
  FMWrite(0x0480);                    // enable interrupts
  if(FMStatus() & 0xe0) return(v_false);

  FMWrite(0x02ff);                    // write ffh to timer 1
  FMWrite(0x0421);                    // start timer 1

  if(fm_addr==0x388) MilliDelay(42);  // wait at least 21000 mcs
  else mdelay((DWORD)mcalc(160));            // wait at least 80 microsec
  if((FMStatus() & 0xe0)!=0xc0) return(v_false);

  FMWrite(0x0460);                    // reset both timer
  FMWrite(0x0480);                    // enable interrupts
  return(v_true);
}



**************************************************************************
  void FMSetVoice(BYTE voice,BYTE *ins)

  DESCRIPTION: Sets the voice from an 11 byte array

  INPUTS:

    voice   FM voice number (0-8)
    ins     A pointer to an array of voice descriptor  bytes

    BYTE    ID

      0      Ampmod /vib /envtype /scale rate/ mod freq mult (oper 1)
      1      Ampmod /vib /envtype /scale rate/ mod freq mult (oper 2)
      2      Key level scaling/ total level (oper 1)
      3      Key level scaling/ total level (oper 2)
      4      Attack Rate/ Decay rate  (oper 1)
      5      Attack Rate/ Decay rate  (oper 2)
      6      Sustain Level/ Release rate (oper 1)
      7      Sustain Level/ Release rate (oper 2)
      8     Feedback / Algorithm (oper 1&2)
      9      Wave Form  Select (oper 1)
      10    Wave Form  Select (oper 2)

**************************************************************************
void FMSetVoice(BYTE voice,BYTE *ins)
{
  if(voice > 8) return;

  FM_keyscale1[voice]=ins[2] & 0xc0;        // store key scaling for FM_Vol
  FM_keyscale2[voice]=ins[3] & 0xc0;
                                            // Write voice data
  FMWrite((0x2000 + FM_off[voice]) | ins[0]);
  FMWrite((0x2300 + FM_off[voice]) | ins[1]);
                                            // For the next two, we want to
                                            // make sure current volume is
                                            // preserved.
  FMWrite((0x4000 + FM_off[voice]) | (ins[2] & 0xc0) | FM_vol[voice]);
  FMWrite((0x4300 + FM_off[voice]) | (ins[3] & 0xc0) | FM_vol[voice]);
                                            // the rest of the voice is just
                                            // straight writes.
  FMWrite((0x6000 + FM_off[voice]) | ins[4]);
  FMWrite((0x6300 + FM_off[voice]) | ins[5]);
  FMWrite((0x8000 + FM_off[voice]) | ins[6]);
  FMWrite((0x8300 + FM_off[voice]) | ins[7]);
  FMWrite((0xc000 + voice * 0x100) | ins[8]);
  FMWrite((0xE000 + FM_off[voice]) | ins[9]);
  FMWrite((0xE300 + FM_off[voice]) | ins[10]);
}


**************************************************************************
  void FMSetFrequency(BYTE voice,SHORT freq)

  DESCRIPTION: sets an explicit pseudo frequency (0 - 0xffff)

  INPUTS:

    voice   FM voice (0-8)
    freq    Frequency Value in Hertz (1 - 6040)

  Special thanks:  Scott T. For making me aware of how to set real
                   Frequency Values on the SB.

**************************************************************************
void FMSetFrequency(BYTE voice,WORD freq)
{
  BYTE highbits,lowbits;
  WORD data,frac=1;
  SHORT octave;

  if(freq > 6040) freq = 6040;             // 6040 is highest freq possible
                                           // Determine the octave
  if(freq < 55) octave = 0;
  else if(freq < 110) octave = 1;
  else if(freq < 220) octave = 2;
  else if(freq < 440) octave = 3;
  else if(freq < 880) octave = 4;
  else if(freq < 1760) octave = 5;
  else if(freq < 3520) octave = 6;
  else octave = 7;

  // determine "f-number" - must be less than 1024
  // Don't need to worry about octave going above 7 here, since the max
  // value for frac when octave is 7 (and freq is 6040) is around 990,
  // so frac will only be greater than 1023 if octave is less than 7.
  // Determining octave by a base of 55 results in a frac range of
  // around 577 - 1150.  Determining octave by with a base of 48 results
  // in a frac range of around 505 - 1007.  Should we use 48?
                                           // Find the f-number
  frac = (freq * (1L << (20-octave)))/50000L;
  if(frac > 1023) {
    octave++;
    if(octave > 7) octave = 7;
    frac = (freq * (1L << (20-octave)))/50000L;
  }
                                           // extract low and high bits
  highbits = (frac & 0x300) >> 8;
  lowbits = frac & 0xff;

  data=0xa000+(voice<<8)|lowbits;         // store low bits for now
                                          // save high bits for Key_on();
                                          // (octave 4)
  FM_key[voice]=highbits|(octave<<2);
  FMWrite(data);                          // write low bits to FM chip;
}

**************************************************************************
  void FMSetNote(BYTE voice,BYTE note)

  DESCRIPTION: sets the frequency for a chromatic note

  INPUTS:
    voice   FM voice #  (0-8)
    note    Regular MIDI note (0-127)

**************************************************************************
void FMSetNote(BYTE voice,BYTE note)
{
  BYTE blk,notex;
  WORD data;
                              //  calculate freq number and octave
  notex=note-24;
  blk=1;
  while(notex>=12)
  {
    notex-=12;
    blk++;                    // octave number
  }

  data=0xa000+(voice<<8)|FM_fnr[notex];
  FM_key[voice]=FM_key_or[notex]|(blk<<2); // save part of the note for Key_on()
  FMWrite(data);             // write note to the chip
}


**************************************************************************
  void FMSetVolume(BYTE voice,BYTE vol)

  DESCRIPTION: The the volume (0-63) for a voice.

  INPUTS:
    voice   FM voice #  (0-8)
    vol     volume value (0-63)

**************************************************************************
void FMSetVolume(BYTE voice,BYTE vol)
{
  if (voice >8) return;
                               // Convert  volume from a logical value to
                               // the value that is really used.  ie: 3f is
                               // really the quietest setting, while 0 is
                               // the loudest.  Weird, eh?
  FM_vol[voice] = (0x3f - (vol & 0x3f));
                               // Write the volume while preserving the
                               // other important parts of the voice.
  FMWrite((0x4000+FM_off[voice]) |FM_vol[voice] | FM_keyscale1[voice]);
  FMWrite((0x4300+FM_off[voice]) |FM_vol[voice] | FM_keyscale2[voice]);

}

**  A NOTE ABOUT RHYTHM FUNCTIONS:

  I've only played around with these functions a little bit. Here are some
  things that I've learned:

    - only channels 6,7,and 8 are affected by the rhythm mode.
    - You will need to develop special instrument definitions to get
      the rhythm instruments to sound right.  The most important parameters
      in a rhythm instrument definition are attack/decay/sustain rates and
      the waveform (bytes 9 and 10).
    - channels 6,7, and 8 each behave differently in rhythm mode:

        6 - Instrumental.  Sounds like a triangle
        7 - White noise.  Sounds like a snare drum
        8 - High white noise.  Sounds like a Cymbal.

    - If you want to add white noise effects to your program (Gun shots
      engines, etc...)  channel 7 in rhythm  mode is a good source.

                                      - ERIC
**



**************************************************************************
  void FMSetRhythmMode(BYTE bool)

  DESCRIPTION:  Turns on/off rhythm mode based on input.

  INPUTS:
    bool    v_true or v_false value for setting the rhythm mode

**************************************************************************
void FMSetRhythmMode(BYTE bool)
{
  WORD data;

  if(bool) data=0xbde0;               // Set the rhythm mode bit
  else data=0xbdc0;

  rhythm=data;                         // This global keeps track of the
                                      // mode for other rhythm functions.
  FMWrite(data);
}


**************************************************************************
  void FMRhythmOn(BYTE inst)

  DESCRIPTION: Turns on a Specified  rhythm instrument.

  INPUTS:
    inst    FM rhythm instrument specification.

            You should use these definitions:

                      FM_HIHAT
                      FM_TOPCYM
                      FM_TOMTOM
                      FM_SNARE
                      FM_BASS

**************************************************************************
void FMRhythmOn(BYTE inst)
{
  rhythm|=inst;
  FMWrite(rhythm);
}

**************************************************************************
  void FMRhythmOff(BYTE inst)

  DESCRIPTION: Turns off a Specified  rhythm instrument.

  INPUTS:
    inst    FM rhythm instrument specification.

            You should use these definitions:

                      FM_HIHAT
                      FM_TOPCYM
                      FM_TOMTOM
                      FM_SNARE
                      FM_BASS

**************************************************************************
void FMRhythmOff(BYTE inst)
{
  rhythm&=(~inst);
  FMWrite(rhythm);
}


**************************************************************************
  void FMKeyOn(BYTE voice)

  DESCRIPTION: Turn on an FM voice.

               This description is misleading, since in my experirnce,
               FM voices are always on.  This function really just
               triggers the FM voice.

  INPUTS:
    voice   FM voice #  (0-8)

**************************************************************************
void FMKeyOn(BYTE voice)
{
  WORD data;

  if(voice > 8) return;

  data=0xb000+(voice<<8);            // set write address
  data |= FM_key[voice]|0x20;        // set key on bit and frequency
   FMWrite(data);
}


**************************************************************************
  void FMKeyOff(BYTE voice)

  DESCRIPTION: Turn off an FM voice.

                (See FMKeyOn)  Again, I've found that voices are always
                on, and to turn them off you really need to just set the
                volume to 0.  Turning off the Key_on bit may prepare
                the voice for a trigger, though.

  INPUTS:
    voice   FM voice #  (0-8)

**************************************************************************
void FMKeyOff(BYTE voice)
{
  WORD data;

  if(voice > 8) return;

  data=0xb000+(voice<<8);            // set address
  data |= FM_key[voice];              // preserve frequency data
  FMWrite(data);
                                     //  working.
}

*** UNUSED ***/
