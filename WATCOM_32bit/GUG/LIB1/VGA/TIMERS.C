#include "timers.h"

/**************************************************************************
  void GUGInitTimer()

  DESCRIPTION: Initializes speaker timer for timing operations.

**************************************************************************/
void GUGInitTimer(void)
{
  char b;

  b = inp(0x61) & 0xfd;          // Read current port value.

                                     // Disable speaker output, but keep
                                     // timer 2 enabled.
  outp(0x61,b | 0x01);
}


/**************************************************************************
  void GUGStartTimer()

  DESCRIPTION: Turns on timer counter for a time measurement

**************************************************************************/
void GUGStartTimer(void)
{
  outp(0x43,0xb0);                 // Set up the timer for countdown
  outp(0x42,0xff);                // Least significant byte
  outp(0x42,0xff);                // Most significant byte
}


/**************************************************************************
  WORD GUGStopTimer()

  DESCRIPTION: Turns off time and reports clicks elapsed.  Note that this
               timer is so quick that it is wraps after only 56
               milliseconds.  If you want to timer longer stuff, I suggest
               using the global variable vclock.  It's tick frequency is
               sample_rate / dma_bufferlen.

               To convert to micro seconds, multiply the return value by
               0.838.

  RETURNS:
    Current timer count

**************************************************************************/
int GUGStopTimer(void)
{
  int timer_hold,timer_diff;

  outp(0x43,0xc0);                 // Read the timer countdown status
  timer_hold =  (int)inp(0x42);
  timer_hold += (int)inp(0x42) * 256;

  timer_diff = 0xffff - timer_hold;   // timer_diff is used later
  return (timer_diff);
}
