#include "vat.h"

extern VAT_STATE internal_state;

void Show_State (void);

main ()
{
  SBSetUp (11000, 70);
  Show_State ();
  GoVarmint ();
  Show_State ();
  DropDeadVarmint ();
  Show_State ();
  SBCleanUp ();
  Show_State ();
}

void Show_State ()
{
  printf ("VAT's major version number: %d\n", internal_state.vat_vers_maj);
  printf ("VAT's minor version number: %d\n", internal_state.vat_vers_min);
  printf ("commercial copy? %d\n", internal_state.commercial);
  printf ("registration info: %s\n", internal_state.register_string);
  printf ("sample rate: %d\n", internal_state.sample_rate);
  printf ("refresh rate: %d\n", internal_state.refresh_rate);
  printf ("stereo allowed? %d\n", internal_state.allow_stereo);
  printf ("8-bit / 16-bit: %d\n", internal_state.bit_depth);
  printf ("DSP major version number: %d\n", internal_state.dsp_vers_maj);
  printf ("DSP minor version number: %d\n", internal_state.dsp_vers_min);
  printf ("BLASTER environment variable: %s\n", internal_state.blaster_string);
  printf ("BLASTER string 'A' element: 0x%X\n", internal_state.blaster_ioport);
  printf ("BLASTER string 'I' element: %d\n", internal_state.blaster_irq);
  printf ("BLASTER string 'D' element: %d\n", internal_state.blaster_lowdma);
  printf ("BLASTER string 'H' element: %d\n", internal_state.blaster_highdma);
  printf ("BLASTER string 'P' element: 0x%X\n", internal_state.blaster_mpuport);
  printf ("BLASTER string 'E' element: %d\n", internal_state.blaster_effects);
  printf ("BLASTER string 'T' element: %d\n", internal_state.blaster_cardtype);
  printf ("address being used for FM: 0x%X\n", internal_state.fm_addr);
  printf ("MIDI environment variable: %s\n", internal_state.midi_string);
  printf ("MIDI string 'SYNTH' element: %d\n", internal_state.midi_synth);
  printf ("MIDI string 'MAP' element: %d\n", internal_state.midi_map);
  printf ("MIDI string 'MODE' element: %d\n", internal_state.midi_mode);
  printf ("availability of audio output: %d\n", internal_state.status);
  getchar ();
}

