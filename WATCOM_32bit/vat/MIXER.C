/**************************************************************************                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           VARMINT'S AUDIO TOOLS 1.1

  MIXER.C

    This file contains source code to control the SB mixers

  Authors: Neil Breeden
           Grant Culbertson

  Copyright 1995,96 - Ground Up

  If you are reading this heading you are in copyright violation.
  This file and the methods therein are property of Ground Up.

  12/07/96 - Added SB20 code

**************************************************************************/
#include <stdio.h>
#include <malloc.h>
#include <dos.h>
#include <string.h>
#include "vat.h"
#include "internal.h"

//-------------------------------- External Varaibles

extern WORD  io_addr;     // SB base address
extern WORD  dsp_vers;    // SB version number
extern SHORT debug_reverseflipflop;

//-------------------------------- Internal Variables

MIXER_STATE v_mixer_status;    // Used by VAT to track the soundcard

int SB20Command(VATMIXER command, int value);     // 2.01 to 2.99
int SBProCommand(VATMIXER command, int value);    // 3.00 to 3.99
int SB16Command(VATMIXER command,  int value);    // 4.00 to 4.99

//-------------------------------- MixerSetting()

int MixerSetting(VATMIXER command, int value)
{
  int status;

  if (command == dma_flip_flop)
  {
    if (value == GET_SETTING)
    {
      return(debug_reverseflipflop);
    }
    else if (value == v_true)
    {
      debug_reverseflipflop = v_true;
      return(v_true);
    }
    else if (value == v_false)
    {
      debug_reverseflipflop = v_false;
      return(v_false);
    }
  }

  // SB1.5,SBMCV     1.xx to 2.00
  // SB2.0           2.01 to 2.99  CT1335 Mixer
  // SBPRO,SBPRO MCV 3.00 to 3.99  CT1345 Mixer
  // SB16, AWE32     4.00 to 4.99  CT1745 Mixer

  if (dsp_vers < 0x201) return(NO_MIXER);
  else if (dsp_vers < 0x300) status = SB20Command(command,value);
  else if (dsp_vers < 0x400) status = SBProCommand(command,value);
  else if (dsp_vers < 0x500) status = SB16Command(command,value);
  else return(DSP_NOT_SUPPORTED);
  return(status);
}

//////////////////////////////////////////////////////////////////////////
int SB20Command(VATMIXER command, int value)
{

  int v1,v2;  // Used when multiple settings (Right/Left) are read

  if (value != GET_SETTING)
  {
    switch(command)
    {
      // Master volume controls
      case v_mas_lvolume:
      case v_mas_rvolume:
      case v_mas_volume:      if (value < 0) value = 0;
                              if (value > 7) value = 7;
                              value <<= 1;
                              VOUTPORTB(io_addr+4,0x02);  // set Volume
                              VOUTPORTB(io_addr+5,value);
                              value >>= 1;
                              v_mixer_status.mas_lvolume = value;
                              return(value);
                              break;


      // Wave volume controls
      case v_wave_lvolume:
      case v_wave_rvolume:
      case v_wave_volume:     if (value < 0) value = 0;
                              if (value > 3) value = 3;
                              value <<= 1;
                              VOUTPORTB(io_addr+4,0x0a);
                              VOUTPORTB(io_addr+5,value);
                              value >>= 1;
                              v_mixer_status.wave_lvolume = value;
                              return(value);
                              break;

      // CD volume controls
      case v_cd_lvolume:
      case v_cd_rvolume:
      case v_cd_volume:       if (value < 0) value = 0;
                              if (value > 7) value = 7;
                              value <<= 1;
                              VOUTPORTB(io_addr+4,0x08);
                              VOUTPORTB(io_addr+5,value);
                              value >>= 1;
                              v_mixer_status.cd_lvolume = value;
                              return(value);
                              break;

      // FM volume controls
      case v_midi_lvolume:
      case v_midi_rvolume:
      case v_midi_volume:
      case v_fm_lvolume:
      case v_fm_rvolume:
      case v_fm_volume:       if (value < 0) value = 0;
                              if (value > 7) value = 7;
                              value <<= 1;
                              VOUTPORTB(io_addr+4,0x06);  // set Left
                              VOUTPORTB(io_addr+5,value);
                              value >>= 1;
                              v_mixer_status.fm_lvolume = value;
                              v_mixer_status.midi_lvolume = value;
                              return(value);
                              break;

      default:                return(DSP_NOT_SUPPORTED);
                              break;

    } // End of switch
  }
  else if (value == GET_SETTING)
  {
    switch(command)
    {
      // Master volume controls
      case v_mas_lvolume:
      case v_mas_rvolume:
      case v_mas_volume:      VOUTPORTB(io_addr+4,0x02);
                              return(VINPORTB(io_addr+5)>>1);
                              break;

      // Wave volume controls
      case v_wave_lvolume:
      case v_wave_rvolume:
      case v_wave_volume:     VOUTPORTB(io_addr+4,0x0A);
                              return(VINPORTB(io_addr+5)>>1);
                              break;

      // FM volume controls
      case v_midi_lvolume:
      case v_midi_rvolume:
      case v_midi_volume:
      case v_fm_lvolume:
      case v_fm_rvolume:
      case v_fm_volume:       VOUTPORTB(io_addr+4,0x06);
                              return(VINPORTB(io_addr+5)>>1);
                              break;

      // CD volume controls
      case v_cd_lvolume:
      case v_cd_rvolume:
      case v_cd_volume:       VOUTPORTB(io_addr+4,0x08);  // get left
                              return(VINPORTB(io_addr+5)>>1);
                              break;

      default:                return(DSP_NOT_SUPPORTED);
                              break;


    } // End of switch
  }   // End of else if

  return(v_false);
}

//////////////////////////////////////////////////////////////////////////
int SBProCommand(VATMIXER command, int value)
{

  int v1,v2;  // Used when multiple settings (Right/Left) are read

  if (value != GET_SETTING)
  {
    switch(command)
    {
      // Input Filter Control
      case v_in_filter:       VOUTPORTB(io_addr+4,0x0c);
                              v1 = VINPORTB(io_addr+5);
                              v1 = v1 & 0xDF;
                              if (value == v_true) v1 = v1 | 0x20;
                              VOUTPORTB(io_addr+4,0x0c);
                              VOUTPORTB(io_addr+5,v1);
                              return(value);
                              break;

      // Lowpass Filter Control
      case v_lowpass_filter:  VOUTPORTB(io_addr+4,0x0c);
                              v1 = VINPORTB(io_addr+5);
                              v1 = v1 & 0xF7;
                              if (value == v_true) v1 = v1 | 0x08;
                              VOUTPORTB(io_addr+4,0x0c);
                              VOUTPORTB(io_addr+5,v1);
                              return(value);
                              break;

      // Output Filter Control
      case v_out_filter:      VOUTPORTB(io_addr+4,0x0e);
                              v1 = VINPORTB(io_addr+5);
                              v1 = v1 & 0xDF;
                              if (value == v_true) v1 = v1 | 0x20;
                              VOUTPORTB(io_addr+4,0x0e);
                              VOUTPORTB(io_addr+5,v1);
                              return(value);
                              break;

      // Stereo Switch
      case v_stereo_switch:   VOUTPORTB(io_addr+4,0x0e);
                              v1 = VINPORTB(io_addr+5);
                              v1 = v1 & 0xFD;
                              if (value == v_true) v1 = v1 | 0x02;
                              VOUTPORTB(io_addr+4,0x0e);
                              VOUTPORTB(io_addr+5,v1);
                              return(value);
                              break;

      // Mic Input Control
      case v_mic_in:          if (value == v_false) return(DSP_NOT_SUPPORTED);
                              VOUTPORTB(io_addr+4,0x0c);
                              v1 = VINPORTB(io_addr+5);
                              v1 = v1 & 0xF8;
                              VOUTPORTB(io_addr+4,0x0c);
                              VOUTPORTB(io_addr+5,v1);
                              return(v_true);
                              break;

      // CD Input Control
      case v_cd_in:          if (value == v_false) return(DSP_NOT_SUPPORTED);
                              VOUTPORTB(io_addr+4,0x0c);
                              v1 = VINPORTB(io_addr+5);
                              v1 = v1 & 0xF8;
                              v1 = v1 | 0x02;  // Enable CD input
                              VOUTPORTB(io_addr+4,0x0c);
                              VOUTPORTB(io_addr+5,v1);
                              return(v_true);
                              break;

      // Line Input Control
      case v_line_in:         if (value == v_false) return(DSP_NOT_SUPPORTED);
                              VOUTPORTB(io_addr+4,0x0c);
                              v1 = VINPORTB(io_addr+5);
                              v1 = v1 & 0xF8;
                              v1 = v1 | 0x06;  // Enable Line input
                              VOUTPORTB(io_addr+4,0x0c);
                              VOUTPORTB(io_addr+5,v1);
                              return(v_true);
                              break;

      // Wave volume controls
      case v_wave_volume:     v1 = SBProCommand(v_wave_lvolume,value);
                              v2 = SBProCommand(v_wave_rvolume,value);
                              return(v1);
                              break;
      case v_wave_lvolume:    if (value < 0) value = 0;
                              if (value > 7) value = 7;
                              value <<= 5;
                              v1 = SBProCommand(v_wave_rvolume,GET_SETTING);
                              v1 <<= 1;
                              v1 = value | v1;
                              VOUTPORTB(io_addr+4,0x04);  // set Left
                              VOUTPORTB(io_addr+5,v1);
                              value >>= 5;
                              v_mixer_status.wave_lvolume = value;
                              return(value);
                              break;
      case v_wave_rvolume:    if (value < 0) value = 0;
                              if (value > 7) value = 7;
                              value <<= 1;
                              v1 = SBProCommand(v_wave_lvolume,GET_SETTING);
                              v1 <<= 5;
                              v1 = value | v1;
                              VOUTPORTB(io_addr+4,0x04);  // set right
                              VOUTPORTB(io_addr+5,v1);
                              value >>= 1;
                              v_mixer_status.wave_rvolume = value;
                              return(value);
                              break;

      // Master volume controls
      case v_mas_volume:      v1 = SBProCommand(v_mas_lvolume,value);
                              v2 = SBProCommand(v_mas_rvolume,value);
                              return(v1);
                              break;
      case v_mas_lvolume:     if (value < 0) value = 0;
                              if (value > 7) value = 7;
                              value <<= 5;
                              v1 = SBProCommand(v_mas_rvolume,GET_SETTING);
                              v1 <<= 1;
                              v1 = value | v1;
                              VOUTPORTB(io_addr+4,0x22);
                              VOUTPORTB(io_addr+5,v1);
                              value >>= 5;
                              v_mixer_status.mas_lvolume = value;
                              return(value);
                              break;
      case v_mas_rvolume:     if (value < 0) value = 0;
                              if (value > 7) value = 7;
                              value <<= 1;
                              v1 = SBProCommand(v_mas_lvolume,GET_SETTING);
                              v1 <<= 5;
                              v1 = value | v1;
                              VOUTPORTB(io_addr+4,0x22);  // set right
                              VOUTPORTB(io_addr+5,v1);
                              value >>= 1;
                              v_mixer_status.mas_rvolume = value;
                              return(value);
                              break;

      // MIDI/FM volume controls
      case v_fm_volume:
      case v_midi_volume:     v1 = SBProCommand(v_midi_lvolume,value);
                              v2 = SBProCommand(v_midi_rvolume,value);
                              return(v1);
                              break;
      case v_fm_lvolume:
      case v_midi_lvolume:    if (value < 0) value = 0;
                              if (value > 7) value = 7;
                              value <<= 5;
                              v1 = SBProCommand(v_midi_rvolume,GET_SETTING);
                              v1 <<= 1;
                              v1 = value | v1;
                              VOUTPORTB(io_addr+4,0x26);  // set Left
                              VOUTPORTB(io_addr+5,v1);
                              value >>= 5;
                              v_mixer_status.fm_lvolume = value;
                              v_mixer_status.midi_lvolume = value;
                              return(value);
                              break;
      case v_fm_rvolume:
      case v_midi_rvolume:    if (value < 0) value = 0;
                              if (value > 7) value = 7;
                              value <<= 1;
                              v1 = SBProCommand(v_midi_lvolume,GET_SETTING);
                              v1 <<= 5;
                              v1 = value | v1;
                              VOUTPORTB(io_addr+4,0x26);  // set right
                              VOUTPORTB(io_addr+5,v1);
                              value >>= 1;
                              v_mixer_status.fm_rvolume = value;
                              v_mixer_status.midi_rvolume = value;
                              return(value);
                              break;

      // CD volume controls
      case v_cd_volume:       v1 = SBProCommand(v_cd_lvolume,value);
                              v2 = SBProCommand(v_cd_rvolume,value);
                              return(v1);
                              break;
      case v_cd_lvolume:      if (value < 0) value = 0;
                              if (value > 7) value = 7;
                              value <<= 5;
                              v1 = SBProCommand(v_cd_rvolume,GET_SETTING);
                              v1 <<= 1;
                              v1 = value | v1;
                              VOUTPORTB(io_addr+4,0x28);  // set Left
                              VOUTPORTB(io_addr+5,v1);
                              value >>= 5;
                              v_mixer_status.cd_lvolume = value;
                              return(value);
                              break;
      case v_cd_rvolume:      if (value < 0) value = 0;
                              if (value > 7) value = 7;
                              value <<= 1;
                              v1 = SBProCommand(v_cd_lvolume,GET_SETTING);
                              v1 <<= 5;
                              v1 = value | v1;
                              VOUTPORTB(io_addr+4,0x28);  // set right
                              VOUTPORTB(io_addr+5,v1);
                              value >>= 1;
                              v_mixer_status.cd_rvolume = value;
                              return(value);
                              break;

      // Line volume controls
      case v_line_volume:     v1 = SBProCommand(v_line_lvolume,value);
                              v2 = SBProCommand(v_line_rvolume,value);
                              return(v1);
                              break;
      case v_line_lvolume:    if (value < 0) value = 0;
                              if (value > 7) value = 7;
                              value <<= 5;
                              v1 = SBProCommand(v_line_rvolume,GET_SETTING);
                              v1 <<= 1;
                              v1 = value | v1;
                              VOUTPORTB(io_addr+4,0x2e);  // set Left
                              VOUTPORTB(io_addr+5,v1);
                              value >>= 5;
                              v_mixer_status.line_lvolume = value;
                              return(value);
                              break;
      case v_line_rvolume:    if (value < 0) value = 0;
                              if (value > 7) value = 7;
                              value <<= 1;
                              v1 = SBProCommand(v_line_lvolume,GET_SETTING);
                              v1 <<= 5;
                              v1 = value | v1;
                              VOUTPORTB(io_addr+4,0x2e);  // set right
                              VOUTPORTB(io_addr+5,v1);
                              value >>= 1;
                              v_mixer_status.line_rvolume = value;
                              return(value);
                              break;

      // Mic volume control
      case v_mic_volume:      if (value < 0) value = 0;
                              if (value > 3) value = 3;
                              value <<= 1;
                              VOUTPORTB(io_addr+4,0x0a);  // set volume
                              VOUTPORTB(io_addr+5,value);
                              value >>= 1;
                              v_mixer_status.mic_volume = value;
                              return(value);
                              break;

      default:                return(DSP_NOT_SUPPORTED);
                              break;

    } // End of switch
  }
  else if (value == GET_SETTING)
  {
    switch(command)
    {
      // Input Filter Control
      case v_in_filter:       VOUTPORTB(io_addr+4,0x0c);
                              v1 = VINPORTB(io_addr+5);
                              v1 = v1 & 0x20;
                              if (v1 > 0) return(v_true);
                              return(v_false);
                              break;

      // Lowpass Filter Control
      case v_lowpass_filter:  VOUTPORTB(io_addr+4,0x0c);
                              v1 = VINPORTB(io_addr+5);
                              v1 = v1 & 0x08;
                              if (v1 > 0) return(v_true);
                              return(v_false);
                              break;

      // Output Filter Control
      case v_out_filter:      VOUTPORTB(io_addr+4,0x0e);
                              v1 = VINPORTB(io_addr+5);
                              v1 = v1 & 0x20;
                              if (v1  > 0) return(v_true);
                              return(v_false);
                              break;

      // Stereo Switch Control
      case v_stereo_switch:   VOUTPORTB(io_addr+4,0x0e);
                              v1 = VINPORTB(io_addr+5);
                              v1 = v1 & 0x02;
                              if (v1  > 0) return(v_true);
                              return(v_false);
                              break;

      // Mic Input Control
      case v_mic_in:          VOUTPORTB(io_addr+4,0x0c);
                              v1 = VINPORTB(io_addr+5);
                              if ((v1 & 0x06) == 0x00) return(v_true);
                              if ((v1 & 0x06) == 0x04) return(v_true);
                              return(v_false);
                              break;

      // CD Input Control
      case v_cd_in:           VOUTPORTB(io_addr+4,0x0c);
                              v1 = VINPORTB(io_addr+5);
                              if ((v1 & 0x06) == 0x02) return(v_true);
                              return(v_false);
                              break;

      // Line Input Control
      case v_line_in:         VOUTPORTB(io_addr+4,0x0c);
                              v1 = VINPORTB(io_addr+5);
                              if ((v1 & 0x06) == 0x06) return(v_true);
                              return(v_false);
                              break;

      // Master volume controls
      case v_mas_volume:      VOUTPORTB(io_addr+4,0x22);  // get left
                              v1 = VINPORTB(io_addr+5)>>5;
                              VOUTPORTB(io_addr+4,0x22);  // get right
                              v2 = VINPORTB(io_addr+5)>>1;
                              v2 = v2 & 0x07;
                              if (v1<v2)
                                return(v2);
                              else
                                return(v1);
                              break;
      case v_mas_lvolume:     VOUTPORTB(io_addr+4,0x22);  // get left
                              return(VINPORTB(io_addr+5)>>5);
                              break;
      case v_mas_rvolume:     VOUTPORTB(io_addr+4,0x22);  // get right
                              return((VINPORTB(io_addr+5)>>1) & 0x07);
                              break;

      // Wave volume controls
      case v_wave_volume:     VOUTPORTB(io_addr+4,0x04);  // get left
                              v1 = VINPORTB(io_addr+5)>>5;
                              VOUTPORTB(io_addr+4,0x04);  // get right
                              v2 = VINPORTB(io_addr+5)>>1;
                              v2 = v2 & 0x07;
                              if (v1<v2)
                                return(v2);
                              else
                                return(v1);
                              break;
      case v_wave_lvolume:    VOUTPORTB(io_addr+4,0x04);  // get left
                              return(VINPORTB(io_addr+5)>>5);
                              break;
      case v_wave_rvolume:    VOUTPORTB(io_addr+4,0x04);  // get right
                              return((VINPORTB(io_addr+5)>>1) & 0x07);
                              break;

      // FM volume controls
      case v_midi_volume:
      case v_fm_volume:       VOUTPORTB(io_addr+4,0x26);  // get left
                              v1 = VINPORTB(io_addr+5)>>5;
                              VOUTPORTB(io_addr+4,0x26);  // get right
                              v2 = VINPORTB(io_addr+5)>>1;
                              v2 = v2 & 0x07;
                              if (v1<v2)
                                return(v2);
                              else
                                return(v1);
                              break;
      case v_midi_lvolume:
      case v_fm_lvolume:      VOUTPORTB(io_addr+4,0x26);  // get left
                              return(VINPORTB(io_addr+5)>>5);
                              break;
      case v_midi_rvolume:
      case v_fm_rvolume:      VOUTPORTB(io_addr+4,0x26);  // get right
                              return((VINPORTB(io_addr+5)>>1) & 0x07);
                              break;

      // Wave volume controls
      case v_cd_volume:       VOUTPORTB(io_addr+4,0x28);  // get left
                              v1 = VINPORTB(io_addr+5)>>5;
                              VOUTPORTB(io_addr+4,0x28);  // get right
                              v2 = VINPORTB(io_addr+5)>>1;
                              v2 = v2 & 0x07;
                              if (v1<v2)
                                return(v2);
                              else
                                return(v1);
                              break;
      case v_cd_lvolume:      VOUTPORTB(io_addr+4,0x28);  // get left
                              return(VINPORTB(io_addr+5)>>5);
                              break;
      case v_cd_rvolume:      VOUTPORTB(io_addr+4,0x28);  // get right
                              return((VINPORTB(io_addr+5)>>1) & 0x07);
                              break;

      // Line volume controls
      case v_line_volume:     VOUTPORTB(io_addr+4,0x2e);  // get left
                              v1 = VINPORTB(io_addr+5)>>5;
                              VOUTPORTB(io_addr+4,0x2e);  // get right
                              v2 = VINPORTB(io_addr+5)>>1;
                              v2 = v2 & 0x07;
                              if (v1<v2)
                                return(v2);
                              else
                                return(v1);
                              break;
      case v_line_lvolume:    VOUTPORTB(io_addr+4,0x2e);  // get left
                              return(VINPORTB(io_addr+5)>>5);
                              break;
      case v_line_rvolume:    VOUTPORTB(io_addr+4,0x2e);  // get right
                              return((VINPORTB(io_addr+5)>>1) & 0x07);
                              break;


      // Mic volume control
      case v_mic_volume:      VOUTPORTB(io_addr+4,0x0a);  // get volume
                              return((VINPORTB(io_addr+5)>>1)&3);
                              break;

      default:                return(DSP_NOT_SUPPORTED);
                              break;


    } // End of switch
  }   // End of else if

  return(v_false);
}


///////////////////////////////////////////////////////////////////////////
int SB16Command(VATMIXER command, int value)
{
  int v1,v2;  // Used when multiple settings (Right/Left) are read

  if (value != GET_SETTING)
  {
    switch(command)
    {
      // Master volume controls
      case v_mas_volume:      v1 = SB16Command(v_mas_lvolume,value);
                              v2 = SB16Command(v_mas_rvolume,value);
                              return(v1);
                              break;
      case v_mas_lvolume:     if (value <  0) value =  0;
                              if (value > 31) value = 31;
                              value <<= 3;
                              VOUTPORTB(io_addr+4,48);  // set left
                              VOUTPORTB(io_addr+5,value);
                              value >>= 3;
                              v_mixer_status.mas_lvolume = value;
                              return(value);
                              break;
      case v_mas_rvolume:     if (value <  0) value =  0;
                              if (value > 31) value = 31;
                              value <<= 3;
                              VOUTPORTB(io_addr+4,49);  // set right
                              VOUTPORTB(io_addr+5,value);
                              value >>= 3;
                              v_mixer_status.mas_rvolume = value;
                              return(value);
                              break;

      // Wave volume
      case v_wave_volume:     v1 = SB16Command(v_wave_lvolume,value);
                              v2 = SB16Command(v_wave_rvolume,value);
                              return(v1);
                              break;
      case v_wave_lvolume:    if (value <  0) value =  0;
                              if (value > 15) value = 15;
                              value <<= 4;
                              VOUTPORTB(io_addr+4,50);  // set left
                              VOUTPORTB(io_addr+5,value);
                              value >>= 4;
                              v_mixer_status.wave_lvolume = value;
                              return(value);
                              break;
      case v_wave_rvolume:    if (value <  0) value =  0;
                              if (value > 15) value = 15;
                              value <<= 4;
                              VOUTPORTB(io_addr+4,51);  // set right
                              VOUTPORTB(io_addr+5,value);
                              value >>= 4;
                              v_mixer_status.wave_rvolume = value;
                              return(value);
                              break;

      // Midi volume controls
      case v_fm_volume:
      case v_midi_volume:     v1 = SB16Command(v_midi_lvolume,value);
                              v2 = SB16Command(v_midi_rvolume,value);
                              return(v1);
                              break;
      case v_fm_lvolume:
      case v_midi_lvolume:    if (value <  0) value =  0;
                              if (value > 15) value = 15;
                              value <<= 4;
                              VOUTPORTB(io_addr+4,52);  // set left
                              VOUTPORTB(io_addr+5,value);
                              value >>= 4;
                              v_mixer_status.midi_lvolume = value;
                              v_mixer_status.fm_lvolume = value;
                              return(value);
                              break;
      case v_fm_rvolume:
      case v_midi_rvolume:    if (value <  0) value =  0;
                              if (value > 15) value = 15;
                              value <<= 4;
                              VOUTPORTB(io_addr+4,53);  // set right
                              VOUTPORTB(io_addr+5,value);
                              value >>= 4;
                              v_mixer_status.midi_rvolume = value;
                              v_mixer_status.fm_rvolume = value;
                              return(value);
                              break;

      // CD volume controls
      case v_cd_volume:       v1 = SB16Command(v_cd_lvolume,value);
                              v2 = SB16Command(v_cd_rvolume,value);
                              return(v1);
                              break;
      case v_cd_lvolume:      if (value <  0) value =  0;
                              if (value > 15) value = 15;
                              value <<= 4;
                              VOUTPORTB(io_addr+4,54);  // set left
                              VOUTPORTB(io_addr+5,value);
                              value >>= 4;
                              v_mixer_status.cd_lvolume = value;
                              return(value);
                              break;
      case v_cd_rvolume:      if (value <  0) value =  0;
                              if (value > 15) value = 15;
                              value <<= 4;
                              VOUTPORTB(io_addr+4,55);  // set right
                              VOUTPORTB(io_addr+5,value);
                              value >>= 4;
                              v_mixer_status.cd_rvolume = value;
                              return(value);
                              break;

      // Line volume controls
      case v_line_volume:     v1 = SB16Command(v_line_lvolume,value);
                              v2 = SB16Command(v_line_rvolume,value);
                              return(v1);
                              break;
      case v_line_lvolume:    if (value <  0) value =  0;
                              if (value > 15) value = 15;
                              value <<= 4;
                              VOUTPORTB(io_addr+4,56);  // set left
                              VOUTPORTB(io_addr+5,value);
                              value >>= 4;
                              v_mixer_status.line_lvolume = value;
                              return(value);
                              break;
      case v_line_rvolume:    if (value <  0) value =  0;
                              if (value > 15) value = 15;
                              value <<= 4;
                              VOUTPORTB(io_addr+4,57);  // set right
                              VOUTPORTB(io_addr+5,value);
                              value >>= 4;
                              v_mixer_status.line_rvolume = value;
                              return(value);
                              break;

      // Mic volume control
      case v_mic_volume:      if (value <  0) value =  0;
                              if (value > 15) value = 15;
                              value <<= 4;
                              VOUTPORTB(io_addr+4,58);  // set volume
                              VOUTPORTB(io_addr+5,value);
                              value >>= 4;
                              v_mixer_status.mic_volume = value;
                              return(value);
                              break;

      // PC Speaker volume control
      case v_spkr_volume:     if (value <  0) value =  0;
                              if (value > 3) value = 3;
                              value <<= 6;
                              VOUTPORTB(io_addr+4,59);  // set volume
                              VOUTPORTB(io_addr+5,value);
                              value >>= 6;
                              v_mixer_status.spkr_volume = value;
                              return(value);
                              break;

      // Treble controls
      case v_mas_treble:      v1 = SB16Command(v_left_treble ,value);
                              v2 = SB16Command(v_right_treble,value);
                              return(v1);
                              break;
      case v_left_treble:     if (value <  0) value =  0;
                              if (value > 15) value = 15;
                              value <<= 4;
                              VOUTPORTB(io_addr+4,68);  // set left
                              VOUTPORTB(io_addr+5,value);
                              value >>= 4;
                              v_mixer_status.left_treble = value;
                              return(value);
                              break;
      case v_right_treble:    if (value <  0) value =  0;
                              if (value > 15) value = 15;
                              value <<= 4;
                              VOUTPORTB(io_addr+4,69);  // set right
                              VOUTPORTB(io_addr+5,value);
                              value >>= 4;
                              v_mixer_status.right_treble = value;
                              return(value);
                              break;

      // Bass controls
      case v_mas_bass:        v1 = SB16Command(v_left_bass ,value);
                              v2 = SB16Command(v_right_bass,value);
                              return(v1);
                              break;
      case v_left_bass:       if (value <  0) value =  0;
                              if (value > 15) value = 15;
                              value <<= 4;
                              VOUTPORTB(io_addr+4,70);  // set left
                              VOUTPORTB(io_addr+5,value);
                              value >>= 4;
                              v_mixer_status.left_bass = value;
                              return(value);
                              break;
      case v_right_bass:      if (value <  0) value =  0;
                              if (value > 15) value = 15;
                              value <<= 4;
                              VOUTPORTB(io_addr+4,71);  // set right
                              VOUTPORTB(io_addr+5,value);
                              value >>= 4;
                              v_mixer_status.right_bass = value;
                              return(value);
                              break;

      // Output gain controls
      case v_out_gain:        v1 = SB16Command (v_lout_gain, value);
                              v2 = SB16Command (v_rout_gain, value);
                              return(v1);
                              break;
      case v_lout_gain:       if (value <  0) value =  0;
                              if (value >  2) value =  2;
                              value <<= 6;
                              VOUTPORTB(io_addr+4,65);
                              VOUTPORTB(io_addr+5,value);
                              value >>= 6;
                              v_mixer_status.lout_gain = value;
                              return(value);
                              break;
      case v_rout_gain:       if (value <  0) value =  0;
                              if (value >  2) value =  2;
                              value <<= 6;
                              VOUTPORTB(io_addr+4,66);
                              VOUTPORTB(io_addr+5,value);
                              value >>= 6;
                              v_mixer_status.rout_gain = value;
                              return(value);
                              break;

      // Auto gain control
      case v_in_agc:          if (value <  0) value =  0;
                              if (value >  1) value =  1;
                              VOUTPORTB(io_addr+4,67);
                              if (value == 0) VOUTPORTB(io_addr+5,1);
                              if (value == 1) VOUTPORTB(io_addr+5,0);
                              v_mixer_status.in_agc = value;
                              return(value);
                              break;

      // CD output control
      case v_cd_out:          v1 = SB16Command(v_cd_lout,value);
                              v2 = SB16Command(v_cd_rout,value);
                              return(v1);
                              break;
      case v_cd_lout:         if (value != v_false)  // Enable Output
                              {
                                VOUTPORTB(io_addr+4,60);
                                value = 4 | VINPORTB(io_addr+5); // 4 = CD-L
                                VOUTPORTB(io_addr+4,60);
                                VOUTPORTB(io_addr+5,value);
                                v_mixer_status.cd_lout = v_true;
                                return(v_true);
                              }
                              else
                              {
                                VOUTPORTB(io_addr+4,60);
                                value = ~4 & VINPORTB(io_addr+5);
                                VOUTPORTB(io_addr+4,60);
                                VOUTPORTB(io_addr+5,value);
                                v_mixer_status.cd_lout = v_false;
                                return(v_false);
                              }
                              break;
      case v_cd_rout:         if (value != v_false)  // Enable Output
                              {
                                VOUTPORTB(io_addr+4,60);
                                value = 2 | VINPORTB(io_addr+5); // 2 = CD-R
                                VOUTPORTB(io_addr+4,60);
                                VOUTPORTB(io_addr+5,value);
                                v_mixer_status.cd_rout = v_true;
                                return(v_true);
                              }
                              else
                              {
                                VOUTPORTB(io_addr+4,60);
                                value = ~2 & VINPORTB(io_addr+5);
                                VOUTPORTB(io_addr+4,60);
                                VOUTPORTB(io_addr+5,value);
                                v_mixer_status.cd_rout = v_false;
                                return(v_false);
                              }
                              break;

      // Line output control
      case v_line_out:        v1 = SB16Command(v_line_lout,value);
                              v2 = SB16Command(v_line_rout,value);
                              return(v1);
                              break;
      case v_line_lout:       if (value != v_false)  // Enable Output
                              {
                                VOUTPORTB(io_addr+4,60);
                                value = 16 | VINPORTB(io_addr+5); // 16 = LN-L
                                VOUTPORTB(io_addr+4,60);
                                VOUTPORTB(io_addr+5,value);
                                v_mixer_status.line_lout = v_true;
                                return(v_true);
                              }
                              else
                              {
                                VOUTPORTB(io_addr+4,60);
                                value = ~16 & VINPORTB(io_addr+5);
                                VOUTPORTB(io_addr+4,60);
                                VOUTPORTB(io_addr+5,value);
                                v_mixer_status.line_lout = v_false;
                                return(v_false);
                              }
                              break;
      case v_line_rout:       if (value != v_false)  // Enable Output
                              {
                                VOUTPORTB(io_addr+4,60);
                                value = 8 | VINPORTB(io_addr+5); // 8 = LN-R
                                VOUTPORTB(io_addr+4,60);
                                VOUTPORTB(io_addr+5,value);
                                v_mixer_status.line_rout = v_true;
                                return(v_true);
                              }
                              else
                              {
                                VOUTPORTB(io_addr+4,60);
                                value = ~8 & VINPORTB(io_addr+5);
                                VOUTPORTB(io_addr+4,60);
                                VOUTPORTB(io_addr+5,value);
                                v_mixer_status.line_rout = v_false;
                                return(v_false);
                              }
                              break;

      // MIC output control                             
      case v_mic_out:         if (value != v_false)  // Enable Output
                              {
                                VOUTPORTB(io_addr+4,60);
                                value = 1 | VINPORTB(io_addr+5); // 1 = MIC
                                VOUTPORTB(io_addr+4,60);
                                VOUTPORTB(io_addr+5,value);
                                v_mixer_status.mic_out = v_true;
                                return(v_true);
                              }
                              else
                              {
                                VOUTPORTB(io_addr+4,60);
                                value = ~1 & VINPORTB(io_addr+5);
                                VOUTPORTB(io_addr+4,60);
                                VOUTPORTB(io_addr+5,value);
                                v_mixer_status.mic_out = v_false;
                                return(v_false);
                              }
                              break;

      // Midi input controls
      case v_midi_in:           v1 = SB16Command(v_midi_lin_to_left ,value);
                                v2 = SB16Command(v_midi_rin_to_right,value);
                                return(v1);
                                break;
      case v_midi_lin_to_left:  if (value != v_false)
                                {
                                  VOUTPORTB(io_addr+4,61);
                                  value = 64 | VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,61);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.midi_lin_to_left = v_true;
                                  return(v_true);
                                }
                                else
                                {
                                  VOUTPORTB(io_addr+4,61);
                                  value = ~64 & VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,61);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.midi_lin_to_left = v_false;
                                  return(v_false);
                                }
                                break;
      case v_midi_rin_to_right: if (value != v_false)
                                {
                                  VOUTPORTB(io_addr+4,62);
                                  value = 32 | VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,62);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.midi_rin_to_right = v_true;
                                  return(v_true);
                                }
                                else
                                {
                                  VOUTPORTB(io_addr+4,62);
                                  value = ~32 & VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,62);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.midi_rin_to_right = v_false;
                                  return(v_false);
                                }
                                break;
      case v_midi_in_swap:      v1 = SB16Command(v_midi_rin_to_left ,value);
                                v2 = SB16Command(v_midi_lin_to_right,value);
                                return(v1);
                                break;
      case v_midi_rin_to_left:  if (value != v_false)
                                {
                                  VOUTPORTB(io_addr+4,61);
                                  value = 32 | VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,61);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.midi_rin_to_left = v_true;
                                  return(v_true);
                                }
                                else
                                {
                                  VOUTPORTB(io_addr+4,61);
                                  value = ~32 & VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,61);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.midi_rin_to_left = v_false;
                                  return(v_false);
                                }
                                break;
      case v_midi_lin_to_right: if (value != v_false)
                                {
                                  VOUTPORTB(io_addr+4,62);
                                  value = 64 | VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,62);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.midi_lin_to_right = v_true;
                                  return(v_true);
                                }
                                else
                                {
                                  VOUTPORTB(io_addr+4,62);
                                  value = ~64 & VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,62);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.midi_lin_to_right = v_false;
                                  return(v_false);
                                }
                                break;


      // CD input controls
      case v_cd_in:             v1 = SB16Command(v_cd_lin_to_left ,value);
                                v2 = SB16Command(v_cd_rin_to_right,value);
                                return(v1);
                                break;
      case v_cd_lin_to_left:    if (value != v_false)
                                {
                                  VOUTPORTB(io_addr+4,61);
                                  value = 4 | VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,61);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.cd_lin_to_left = v_true;
                                  return(v_true);
                                }
                                else
                                {
                                  VOUTPORTB(io_addr+4,61);
                                  value = ~4 & VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,61);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.cd_lin_to_left = v_false;
                                  return(v_false);
                                }
                                break;
      case v_cd_rin_to_right:   if (value != v_false)
                                {
                                  VOUTPORTB(io_addr+4,62);
                                  value = 2 | VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,62);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.cd_rin_to_right= v_true;
                                  return(v_true);
                                }
                                else
                                {
                                  VOUTPORTB(io_addr+4,62);
                                  value = ~2 & VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,62);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.cd_rin_to_right= v_false;
                                  return(v_false);
                                }
                                break;
      case v_cd_in_swap:        v1 = SB16Command(v_cd_rin_to_left ,value);
                                v2 = SB16Command(v_cd_lin_to_right,value);
                                return(v1);
                                break;
      case v_cd_rin_to_left:    if (value != v_false)
                                {
                                  VOUTPORTB(io_addr+4,61);
                                  value = 2 | VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,61);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.cd_rin_to_left = v_true;
                                  return(v_true);
                                }
                                else
                                {
                                  VOUTPORTB(io_addr+4,61);
                                  value = ~2 & VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,61);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.cd_rin_to_left = v_true;
                                  return(v_false);
                                }
                                break;
      case v_cd_lin_to_right:   if (value != v_false)
                                {
                                  VOUTPORTB(io_addr+4,62);
                                  value = 4 | VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,62);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.cd_lin_to_right = v_true;
                                  return(v_true);
                                }
                                else
                                {
                                  VOUTPORTB(io_addr+4,62);
                                  value = ~4 & VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,62);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.cd_lin_to_right = v_false;
                                  return(v_false);
                                }
                                break;

      // Line input controls
      case v_line_in:           v1 = SB16Command(v_line_lin_to_left ,value);
                                v2 = SB16Command(v_line_rin_to_right,value);
                                return(v1);
                                break;
      case v_line_lin_to_left:  if (value != v_false)
                                {
                                  VOUTPORTB(io_addr+4,61);
                                  value = 16 | VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,61);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.line_lin_to_left = v_true;
                                  return(v_true);
                                }
                                else
                                {
                                  VOUTPORTB(io_addr+4,61);
                                  value = ~16 & VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,61);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.line_lin_to_left = v_false;
                                  return(v_false);
                                }
                                break;
      case v_line_rin_to_right: if (value != v_false)
                                {
                                  VOUTPORTB(io_addr+4,62);
                                  value = 8 | VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,62);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.line_rin_to_right = v_true;
                                  return(v_true);
                                }
                                else
                                {
                                  VOUTPORTB(io_addr+4,62);
                                  value = ~8 & VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,62);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.line_rin_to_right = v_false;
                                  return(v_false);
                                }
                                break;
      case v_line_in_swap:      v1 = SB16Command(v_line_rin_to_left ,value);
                                v2 = SB16Command(v_line_lin_to_right,value);
                                return(v1);
                                break;
      case v_line_rin_to_left:  if (value != v_false)
                                {
                                  VOUTPORTB(io_addr+4,61);
                                  value = 8 | VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,61);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.line_rin_to_left = v_true;
                                  return(v_true);
                                }
                                else
                                {
                                  VOUTPORTB(io_addr+4,61);
                                  value = ~8 & VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,61);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.line_rin_to_left = v_false;
                                  return(v_false);
                                }
                                break;
      case v_line_lin_to_right: if (value != v_false)
                                {
                                  VOUTPORTB(io_addr+4,62);
                                  value = 16 | VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,62);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.line_lin_to_right = v_true;
                                  return(v_true);
                                }
                                else
                                {
                                  VOUTPORTB(io_addr+4,62);
                                  value = ~16 & VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,62);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.line_lin_to_right = v_false;
                                  return(v_false);
                                }
                                break;

      // Mic input controls
      case v_mic_in:            v1 = SB16Command(v_mic_in_to_left ,value);
                                v2 = SB16Command(v_mic_in_to_right,value);
                                return(v1);
                                break;
      case v_mic_in_to_left:    if (value != v_false)
                                {
                                  VOUTPORTB(io_addr+4,61);
                                  value = 1 | VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,61);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.mic_in_to_left = v_true;
                                  return(v_true);
                                }
                                else
                                {
                                  VOUTPORTB(io_addr+4,61);
                                  value = ~1 & VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,61);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.mic_in_to_left = v_false;
                                  return(v_false);
                                }
                                break;
      case v_mic_in_to_right:   if (value != v_false)
                                {
                                  VOUTPORTB(io_addr+4,62);
                                  value = 1 | VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,62);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.mic_in_to_right = v_true;
                                  return(v_true);
                                }
                                else
                                {
                                  VOUTPORTB(io_addr+4,62);
                                  value = ~1 & VINPORTB(io_addr+5);
                                  VOUTPORTB(io_addr+4,62);
                                  VOUTPORTB(io_addr+5,value);
                                  v_mixer_status.mic_in_to_right = v_false;
                                  return(v_false);
                                }
                                break;

      // Input gain control
      case v_in_gain:           v1 = SB16Command(v_lin_gain,value);
                                v2 = SB16Command(v_rin_gain,value);
                                return(v1);
                                break;
      case v_lin_gain:          if (value <  0) value =  0;
                                if (value >  2) value =  2;
                                value <<= 6;
                                VOUTPORTB(io_addr+4,63);
                                VOUTPORTB(io_addr+5,value);
                                value >>= 6;
                                v_mixer_status.lin_gain = value;
                                return(value);
                                break;
      case v_rin_gain:          if (value <  0) value =  0;
                                if (value >  2) value =  2;
                                value <<= 6;
                                VOUTPORTB(io_addr+4,64);
                                VOUTPORTB(io_addr+5,value);
                                value >>= 6;
                                v_mixer_status.rin_gain = value;
                                return(value);
                                break;


      default:                  return(DSP_NOT_SUPPORTED);
                                break;

    } // End of switch
  }
  else if (value == GET_SETTING)
  {
    switch(command)
    {
      // Master volume controls
      case v_mas_volume:      VOUTPORTB(io_addr+4,48);  // get left
                              v1 = VINPORTB(io_addr+5)>>3;
                              VOUTPORTB(io_addr+4,49);  // get right
                              v2 = VINPORTB(io_addr+5)>>3;
                              if (v1<v2)
                                return(v2);
                              else
                                return(v1);
                              break;
      case v_mas_lvolume:     VOUTPORTB(io_addr+4,48);  // get left
                              return(VINPORTB(io_addr+5)>>3);
                              break;
      case v_mas_rvolume:     VOUTPORTB(io_addr+4,49);  // get right
                              return(VINPORTB(io_addr+5)>>3);
                              break;

      // Wave volume controls
      case v_wave_volume:     VOUTPORTB(io_addr+4,50);  // get left
                              v1 = VINPORTB(io_addr+5)>>4;
                              VOUTPORTB(io_addr+4,51);  // get right
                              v2 = VINPORTB(io_addr+5)>>4;
                              if (v1<v2)
                                return(v2);
                              else
                                return(v1);
                              break;
      case v_wave_lvolume:    VOUTPORTB(io_addr+4,50);  // get left
                              return(VINPORTB(io_addr+5)>>4);
                              break;
      case v_wave_rvolume:    VOUTPORTB(io_addr+4,51);  // get right
                              return(VINPORTB(io_addr+5)>>4);
                              break;

      // Midi volume controls
      case v_fm_volume:
      case v_midi_volume:     VOUTPORTB(io_addr+4,52);  // get left
                              v1 = VINPORTB(io_addr+5)>>4;
                              VOUTPORTB(io_addr+4,53);  // get right
                              v2 = VINPORTB(io_addr+5)>>4;
                              if (v1<v2)
                                return(v2);
                              else
                                return(v1);
                              break;
      case v_fm_lvolume:
      case v_midi_lvolume:    VOUTPORTB(io_addr+4,52);  // get left
                              return(VINPORTB(io_addr+5)>>4);
                              break;
      case v_fm_rvolume:
      case v_midi_rvolume:    VOUTPORTB(io_addr+4,53);  // get right
                              return(VINPORTB(io_addr+5)>>4);
                              break;

      // CD volume controls
      case v_cd_volume:       VOUTPORTB(io_addr+4,54);  // get left
                              v1 = VINPORTB(io_addr+5)>>4;
                              VOUTPORTB(io_addr+4,55);  // get right
                              v2 = VINPORTB(io_addr+5)>>4;
                              if (v1<v2)
                                return(v2);
                              else
                                return(v1);
                              break;
      case v_cd_lvolume:      VOUTPORTB(io_addr+4,54);  // get left
                              return(VINPORTB(io_addr+5)>>4);
                              break;
      case v_cd_rvolume:      VOUTPORTB(io_addr+4,55);  // get right
                              return(VINPORTB(io_addr+5)>>4);
                              break;

      // Line volume controls
      case v_line_volume:     VOUTPORTB(io_addr+4,56);  // get left
                              v1 = VINPORTB(io_addr+5)>>4;
                              VOUTPORTB(io_addr+4,57);  // get right
                              v2 = VINPORTB(io_addr+5)>>4;
                              if (v1<v2)
                                return(v2);
                              else
                                return(v1);
                              break;
      case v_line_lvolume:    VOUTPORTB(io_addr+4,56);  // get left
                              return(VINPORTB(io_addr+5)>>4);
                              break;
      case v_line_rvolume:    VOUTPORTB(io_addr+4,57);  // get right
                              return(VINPORTB(io_addr+5)>>4);
                              break;

      // Mic volume control
      case v_mic_volume:      VOUTPORTB(io_addr+4,58);  // get volume
                              return(VINPORTB(io_addr+5)>>4);
                              break;

      // PC Speaker volume control
      case v_spkr_volume:     VOUTPORTB(io_addr+4,59);  // get volume
                              return(VINPORTB(io_addr+5)>>6);
                              break;

      // Treble controls
      case v_mas_treble:      VOUTPORTB(io_addr+4,68);  // get left
                              v1 = VINPORTB(io_addr+5)>>4;
                              VOUTPORTB(io_addr+4,69);  // get right
                              v2 = VINPORTB(io_addr+5)>>4;
                              if (v1<v2)
                                return(v2);
                              else
                                return(v1);
                              break;
      case v_left_treble:     VOUTPORTB(io_addr+4,68);  // get left
                              return(VINPORTB(io_addr+5)>>4);
                              break;
      case v_right_treble:    VOUTPORTB(io_addr+4,69);  // get right
                              return(VINPORTB(io_addr+5)>>4);
                              break;

      // Bass controls
      case v_mas_bass:        VOUTPORTB(io_addr+4,70);  // get left
                              v1 = VINPORTB(io_addr+5)>>4;
                              VOUTPORTB(io_addr+4,71);  // get right
                              v2 = VINPORTB(io_addr+5)>>4;
                              if (v1<v2)
                                return(v2);
                              else
                                return(v1);
                              break;
      case v_left_bass:       VOUTPORTB(io_addr+4,70);  // get left
                              return(VINPORTB(io_addr+5)>>4);
                              break;
      case v_right_bass:      VOUTPORTB(io_addr+4,71);  // get right
                              return(VINPORTB(io_addr+5)>>4);
                              break;

      // Output gain control
      case v_out_gain:        VOUTPORTB(io_addr+4,65);  // get left
                              v1 = VINPORTB(io_addr+5)>>6;
                              VOUTPORTB(io_addr+4,66);  // get right
                              v2 = VINPORTB(io_addr+5)>>6;
                              if (v1<v2)
                                return(v2);
                              else
                                return(v1);
                              break;
      case v_lout_gain:       VOUTPORTB(io_addr+4,65);
                              return(VINPORTB(io_addr+5)>>6);
                              break;
      case v_rout_gain:       VOUTPORTB(io_addr+4,66);
                              return(VINPORTB(io_addr+5)>>6);
                              break;

      // Input gain control
      case v_in_gain:         VOUTPORTB(io_addr+4,63);  // get left
                              v1 = VINPORTB(io_addr+5)>>6;
                              VOUTPORTB(io_addr+4,64);  // get right
                              v2 = VINPORTB(io_addr+5)>>6;
                              if (v1<v2)
                                return(v2);
                              else
                                return(v1);
                              break;
      case v_lin_gain:        VOUTPORTB(io_addr+4,63);
                              return(VINPORTB(io_addr+5)>>6);
                              break;
      case v_rin_gain:        VOUTPORTB(io_addr+4,64);
                              return(VINPORTB(io_addr+5)>>6);
                              break;

      // Gain control
      case v_in_agc:          VOUTPORTB(io_addr+4,67);
                              return(VINPORTB(io_addr+5));
                              break;

      //
      // Output Control Block
      //

      // CD output control
      case v_cd_out:          VOUTPORTB(io_addr+4,60);
                              v1 = VINPORTB(io_addr+5) & 2;  // Right
                              VOUTPORTB(io_addr+4,60);
                              v2 = VINPORTB(io_addr+5) & 4;  // Left
                              if ((v1) && (v2))
                                return(v_true);
                              else
                                return(v_false);
                              break;
      case v_cd_lout:         VOUTPORTB(io_addr+4,60);
                              v1 = VINPORTB(io_addr+5) & 4;   // Left
                              if (v1)
                                return(v_true);
                              else
                                return(v_false);
                              break;
      case v_cd_rout:         VOUTPORTB(io_addr+4,60);
                              v1 = VINPORTB(io_addr+5) & 2;   // Right
                              if (v1)
                                return(v_true);
                              else
                                return(v_false);
                              break;

      // Line output control
      case v_line_out:        VOUTPORTB(io_addr+4,60);
                              v1 = VINPORTB(io_addr+5) &  8;  // Right
                              VOUTPORTB(io_addr+4,60);
                              v2 = VINPORTB(io_addr+5) & 16;  // Left
                              if ((v1) && (v2))
                                return(v_true);
                              else
                                return(v_false);
                              break;
      case v_line_lout:       VOUTPORTB(io_addr+4,60);
                              v1 = VINPORTB(io_addr+5) & 16;   // Left
                              if (v1)
                                return(v_true);
                              else
                                return(v_false);
                              break;
      case v_line_rout:       VOUTPORTB(io_addr+4,60);
                              v1 = VINPORTB(io_addr+5) & 8;   // Right
                              if (v1)
                                return(v_true);
                              else
                                return(v_false);
                              break;

      // Mic output control
      case v_mic_out:         VOUTPORTB(io_addr+4,60);
                              v1 = VINPORTB(io_addr+5) & 1;   // Mic
                              if (v1)
                                return(v_true);
                              else
                                return(v_false);
                              break;

      //
      // Input Control Block
      //

      // Midi input control
      case v_midi_in:            VOUTPORTB(io_addr+4,61);
                                 v1 = VINPORTB(io_addr+5);
                                 VOUTPORTB(io_addr+4,62);
                                 v2= VINPORTB(io_addr+5);
                                 if ((v1 & 64) && (v2 & 32))
                                   return(v_true);
                                 else
                                   return(v_false);
                                 break;
      case v_midi_lin_to_left:   VOUTPORTB(io_addr+4,61);
                                 if (VINPORTB(io_addr+5) & 64)
                                   return(v_true);
                                 else
                                   return(v_false);
                                 break;
      case v_midi_rin_to_right:  VOUTPORTB(io_addr+4,62);
                                 if (VINPORTB(io_addr+5) & 32)
                                   return(v_true);
                                 else
                                   return(v_false);
                                 break;
      case v_midi_in_swap:       VOUTPORTB(io_addr+4,61);
                                 v1 = VINPORTB(io_addr+5);
                                 VOUTPORTB(io_addr+4,62);
                                 v2= VINPORTB(io_addr+5);
                                 if ((v1 & 32) && (v2 & 64))
                                   return(v_true);
                                 else
                                   return(v_false);
                                 break;
      case v_midi_rin_to_left:   VOUTPORTB(io_addr+4,61);
                                 if (VINPORTB(io_addr+5) & 32)
                                   return(v_true);
                                 else
                                   return(v_false);
                                 break;
      case v_midi_lin_to_right:  VOUTPORTB(io_addr+4,62);
                                 if (VINPORTB(io_addr+5) & 64)
                                   return(v_true);
                                 else
                                   return(v_false);
                                 break;

      // CD input control
      case v_cd_in:              VOUTPORTB(io_addr+4,61);
                                 v1 = VINPORTB(io_addr+5);
                                 VOUTPORTB(io_addr+4,62);
                                 v2= VINPORTB(io_addr+5);
                                 if ((v1 & 4) && (v2 & 2))
                                   return(v_true);
                                 else
                                   return(v_false);
                                 break;
      case v_cd_lin_to_left:     VOUTPORTB(io_addr+4,61);
                                 if (VINPORTB(io_addr+5) & 4)
                                   return(v_true);
                                 else
                                   return(v_false);
                                 break;
      case v_cd_rin_to_right:    VOUTPORTB(io_addr+4,62);
                                 if (VINPORTB(io_addr+5) & 2)
                                   return(v_true);
                                 else
                                   return(v_false);
                                 break;
      case v_cd_in_swap:         VOUTPORTB(io_addr+4,61);
                                 v1 = VINPORTB(io_addr+5);
                                 VOUTPORTB(io_addr+4,62);
                                 v2= VINPORTB(io_addr+5);
                                 if ((v1 & 2) && (v2 & 4))
                                   return(v_true);
                                 else
                                   return(v_false);
                                 break;
      case v_cd_rin_to_left:     VOUTPORTB(io_addr+4,61);
                                 if (VINPORTB(io_addr+5) & 2)
                                   return(v_true);
                                 else
                                   return(v_false);
                                 break;
      case v_cd_lin_to_right:    VOUTPORTB(io_addr+4,62);
                                 if (VINPORTB(io_addr+5) & 4)
                                   return(v_true);
                                 else
                                   return(v_false);
                                 break;

      // Line input control
      case v_line_in:            VOUTPORTB(io_addr+4,61);
                                 v1 = VINPORTB(io_addr+5);
                                 VOUTPORTB(io_addr+4,62);
                                 v2= VINPORTB(io_addr+5);
                                 if ((v1 & 16) && (v2 & 8))
                                   return(v_true);
                                 else
                                   return(v_false);
                                 break;
      case v_line_lin_to_left:   VOUTPORTB(io_addr+4,61);
                                 if (VINPORTB(io_addr+5) & 16)
                                   return(v_true);
                                 else
                                   return(v_false);
                                 break;
      case v_line_rin_to_right:  VOUTPORTB(io_addr+4,62);
                                 if (VINPORTB(io_addr+5) & 8)
                                   return(v_true);
                                 else
                                   return(v_false);
                                 break;
      case v_line_in_swap:       VOUTPORTB(io_addr+4,61);
                                 v1 = VINPORTB(io_addr+5);
                                 VOUTPORTB(io_addr+4,62);
                                 v2= VINPORTB(io_addr+5);
                                 if ((v1 & 8) && (v2 & 16))
                                   return(v_true);
                                 else
                                   return(v_false);
                                 break;
      case v_line_rin_to_left:   VOUTPORTB(io_addr+4,61);
                                 if (VINPORTB(io_addr+5) & 8)
                                   return(v_true);
                                 else
                                   return(v_false);
                                 break;
      case v_line_lin_to_right:  VOUTPORTB(io_addr+4,62);
                                 if (VINPORTB(io_addr+5) & 16)
                                   return(v_true);
                                 else
                                   return(v_false);
                                 break;

      // Micinput control
      case v_mic_in:             VOUTPORTB(io_addr+4,61);
                                 v1 = VINPORTB(io_addr+5);
                                 VOUTPORTB(io_addr+4,62);
                                 v2= VINPORTB(io_addr+5);
                                 if ((v1 & 1) && (v2 & 1))
                                   return(v_true);
                                 else
                                   return(v_false);
                                 break;
      case v_mic_in_to_left:     VOUTPORTB(io_addr+4,61);
                                 if (VINPORTB(io_addr+5) & 1)
                                   return(v_true);
                                 else
                                   return(v_false);
                                 break;
      case v_mic_in_to_right:    VOUTPORTB(io_addr+4,62);
                                 if (VINPORTB(io_addr+5) & 1)
                                   return(v_true);
                                 else
                                   return(v_false);
                                 break;

      default:                   return(DSP_NOT_SUPPORTED);
                                 break;

    } // End of switch
  }   // End of else if

  return(v_false);
}     // End of SB16Command()

////////////////////////////////////////////////////////////////////////
MIXER_STATE *MixerState(MIXER_STATE *mixer)
{
  MIXER_STATE *newmixer;

  if (mixer == NULL)
  {
    return(NULL);
  }

  if (mixer == GET_STATE)
  {
    if (!(newmixer = (MIXER_STATE *)malloc (sizeof (MIXER_STATE))))
      return NULL;

    // Volume Group
    newmixer->mas_lvolume  = MixerSetting(v_mas_lvolume  ,GET_SETTING);
    newmixer->mas_rvolume  = MixerSetting(v_mas_rvolume  ,GET_SETTING);
    newmixer->wave_lvolume = MixerSetting(v_wave_lvolume ,GET_SETTING);
    newmixer->wave_rvolume = MixerSetting(v_wave_rvolume ,GET_SETTING);
    newmixer->midi_lvolume = MixerSetting(v_midi_lvolume ,GET_SETTING);
    newmixer->midi_rvolume = MixerSetting(v_midi_rvolume ,GET_SETTING);
    newmixer->fm_lvolume   = MixerSetting(v_fm_lvolume   ,GET_SETTING);
    newmixer->fm_rvolume   = MixerSetting(v_fm_rvolume   ,GET_SETTING);
    newmixer->cd_lvolume   = MixerSetting(v_cd_lvolume   ,GET_SETTING);
    newmixer->cd_rvolume   = MixerSetting(v_cd_rvolume   ,GET_SETTING);
    newmixer->line_lvolume = MixerSetting(v_line_lvolume ,GET_SETTING);
    newmixer->line_rvolume = MixerSetting(v_line_rvolume ,GET_SETTING);
    newmixer->mic_volume   = MixerSetting(v_mic_volume   ,GET_SETTING);
    newmixer->spkr_volume  = MixerSetting(v_spkr_volume  ,GET_SETTING);

    // Settings Group
    newmixer->left_treble  = MixerSetting(v_left_treble  ,GET_SETTING);
    newmixer->right_treble = MixerSetting(v_right_treble ,GET_SETTING);
    newmixer->left_bass    = MixerSetting(v_left_bass    ,GET_SETTING);
    newmixer->right_bass   = MixerSetting(v_right_bass   ,GET_SETTING);
    newmixer->lout_gain    = MixerSetting(v_lout_gain    ,GET_SETTING);
    newmixer->rout_gain    = MixerSetting(v_rout_gain    ,GET_SETTING);
    newmixer->lin_gain     = MixerSetting(v_lin_gain     ,GET_SETTING);
    newmixer->rin_gain     = MixerSetting(v_rin_gain     ,GET_SETTING);
    newmixer->in_agc       = MixerSetting(v_in_agc       ,GET_SETTING);

    // Input Status Group
    newmixer->midi_lin_to_left  = MixerSetting(v_midi_lin_to_left ,GET_SETTING);
    newmixer->midi_rin_to_right = MixerSetting(v_midi_rin_to_right,GET_SETTING);
    newmixer->midi_rin_to_left  = MixerSetting(v_midi_rin_to_left ,GET_SETTING);
    newmixer->midi_lin_to_right = MixerSetting(v_midi_lin_to_right,GET_SETTING);
    newmixer->cd_lin_to_left    = MixerSetting(v_cd_lin_to_left   ,GET_SETTING);
    newmixer->cd_rin_to_right   = MixerSetting(v_cd_rin_to_right  ,GET_SETTING);
    newmixer->cd_rin_to_left    = MixerSetting(v_cd_rin_to_left   ,GET_SETTING);
    newmixer->cd_lin_to_right   = MixerSetting(v_cd_lin_to_right  ,GET_SETTING);
    newmixer->line_lin_to_left  = MixerSetting(v_line_lin_to_left ,GET_SETTING);
    newmixer->line_rin_to_right = MixerSetting(v_line_rin_to_right,GET_SETTING);
    newmixer->line_rin_to_left  = MixerSetting(v_line_rin_to_left ,GET_SETTING);
    newmixer->line_lin_to_right = MixerSetting(v_line_lin_to_right,GET_SETTING);
    newmixer->mic_in_to_left    = MixerSetting(v_mic_in_to_left   ,GET_SETTING);
    newmixer->mic_in_to_right   = MixerSetting(v_mic_in_to_right  ,GET_SETTING);

    // Output Status Group
    newmixer->cd_lout   = MixerSetting(v_cd_lout   ,GET_SETTING);
    newmixer->cd_rout   = MixerSetting(v_cd_rout   ,GET_SETTING);
    newmixer->line_lout = MixerSetting(v_line_lout ,GET_SETTING);
    newmixer->line_rout = MixerSetting(v_line_rout ,GET_SETTING);
    newmixer->mic_out   = MixerSetting(v_mic_out   ,GET_SETTING);

    // Filter Group
    newmixer->input_filter   = MixerSetting(v_in_filter     , GET_SETTING);
    newmixer->output_filter  = MixerSetting(v_out_filter    , GET_SETTING);
    newmixer->lowpass_filter = MixerSetting(v_lowpass_filter, GET_SETTING);
    newmixer->stereo_switch  = MixerSetting(v_stereo_switch , GET_SETTING);

    // Filter Group
    newmixer->dma_flip_flop  = MixerSetting(dma_flip_flop , GET_SETTING);

    return (newmixer);
  } else {
    mixer->mas_lvolume  = MixerSetting(v_mas_lvolume  ,mixer->mas_lvolume);
    mixer->mas_rvolume  = MixerSetting(v_mas_rvolume  ,mixer->mas_rvolume);
    mixer->wave_lvolume = MixerSetting(v_wave_lvolume ,mixer->wave_lvolume);
    mixer->wave_rvolume = MixerSetting(v_wave_rvolume ,mixer->wave_rvolume);
    mixer->midi_lvolume = MixerSetting(v_midi_lvolume ,mixer->midi_lvolume);
    mixer->midi_rvolume = MixerSetting(v_midi_rvolume ,mixer->midi_rvolume);
    mixer->fm_lvolume   = MixerSetting(v_fm_lvolume   ,mixer->fm_lvolume);
    mixer->fm_rvolume   = MixerSetting(v_fm_rvolume   ,mixer->fm_rvolume);
    mixer->cd_lvolume   = MixerSetting(v_cd_lvolume   ,mixer->cd_lvolume);
    mixer->cd_rvolume   = MixerSetting(v_cd_rvolume   ,mixer->cd_rvolume);
    mixer->line_lvolume = MixerSetting(v_line_lvolume ,mixer->line_lvolume);
    mixer->line_rvolume = MixerSetting(v_line_rvolume ,mixer->line_rvolume);
    mixer->mic_volume   = MixerSetting(v_mic_volume   ,mixer->mic_volume);
    mixer->spkr_volume  = MixerSetting(v_spkr_volume  ,mixer->spkr_volume);

    // Settings Group
    mixer->left_treble  = MixerSetting(v_left_treble  ,mixer->left_treble);
    mixer->right_treble = MixerSetting(v_right_treble ,mixer->right_treble);
    mixer->left_bass    = MixerSetting(v_left_bass    ,mixer->left_bass);
    mixer->right_bass   = MixerSetting(v_right_bass   ,mixer->right_bass);
    mixer->lout_gain    = MixerSetting(v_lout_gain    ,mixer->lout_gain);
    mixer->rout_gain    = MixerSetting(v_rout_gain    ,mixer->rout_gain);
    mixer->lin_gain     = MixerSetting(v_lin_gain     ,mixer->lin_gain);
    mixer->rin_gain     = MixerSetting(v_rin_gain     ,mixer->rin_gain);
    mixer->in_agc       = MixerSetting(v_in_agc       ,mixer->in_agc);

    // Input Status Group
    mixer->midi_lin_to_left  = MixerSetting(v_midi_lin_to_left ,mixer->midi_lin_to_left);
    mixer->midi_rin_to_right = MixerSetting(v_midi_rin_to_right,mixer->midi_rin_to_right);
    mixer->midi_rin_to_left  = MixerSetting(v_midi_rin_to_left ,mixer->midi_rin_to_left);
    mixer->midi_lin_to_right = MixerSetting(v_midi_lin_to_right,mixer->midi_lin_to_right);
    mixer->cd_lin_to_left    = MixerSetting(v_cd_lin_to_left   ,mixer->cd_lin_to_left);
    mixer->cd_rin_to_right   = MixerSetting(v_cd_rin_to_right  ,mixer->cd_rin_to_right);
    mixer->cd_rin_to_left    = MixerSetting(v_cd_rin_to_left   ,mixer->cd_rin_to_left);
    mixer->cd_lin_to_right   = MixerSetting(v_cd_lin_to_right  ,mixer->cd_lin_to_right);
    mixer->line_lin_to_left  = MixerSetting(v_line_lin_to_left ,mixer->line_lin_to_left);
    mixer->line_rin_to_right = MixerSetting(v_line_rin_to_right,mixer->line_rin_to_right);
    mixer->line_rin_to_left  = MixerSetting(v_line_rin_to_left ,mixer->line_rin_to_left);
    mixer->line_lin_to_right = MixerSetting(v_line_lin_to_right,mixer->line_lin_to_right);
    mixer->mic_in_to_left    = MixerSetting(v_mic_in_to_left   ,mixer->mic_in_to_left);
    mixer->mic_in_to_right   = MixerSetting(v_mic_in_to_right  ,mixer->mic_in_to_right);

    // Output Status Group
    mixer->cd_lout   = MixerSetting(v_cd_lout   ,mixer->cd_lout);
    mixer->cd_rout   = MixerSetting(v_cd_rout   ,mixer->cd_rout);
    mixer->line_lout = MixerSetting(v_line_lout ,mixer->line_lout);
    mixer->line_rout = MixerSetting(v_line_rout ,mixer->line_rout);
    mixer->mic_out   = MixerSetting(v_mic_out   ,mixer->mic_out);

    // Filter Group
    mixer->input_filter   = MixerSetting(v_in_filter     , mixer->input_filter);
    mixer->output_filter  = MixerSetting(v_out_filter    , mixer->output_filter);
    mixer->lowpass_filter = MixerSetting(v_lowpass_filter, mixer->lowpass_filter);
    mixer->stereo_switch  = MixerSetting(v_stereo_switch , mixer->stereo_switch);

    // Generic Group
    mixer->dma_flip_flop  = MixerSetting(dma_flip_flop , mixer->dma_flip_flop);

    return (mixer);
  }
}
