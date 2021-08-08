#include "vat.h"
#include "internal.h"


  /************************************************************************\
 |*                           /               \                            *|
 |*                          <  MPU Functions  >                           *|
 |*                           \_______________/                            *|
  \                                                                        / 
  *|  INT:                                                                |* 
  *|        void  mpu_init    (void);                                     |* 
  *|        void  mpu_reset   (void);                                     |* 
  /                                                                        \ 
 |*   EXT:                                                                 *|
 |*      VATBOOL  MPUEnable       (void);                                  *|
 |*         void  MPUDisable      (void);                                  *|
 |*    VATSTATUS  MPUStatus       (void);                                  *|
 |*         void  MPUPatch        (BYTE channel, BYTE patch);              *|
 |*         void  MPUPlayNote     (BYTE channel, BYTE note, BYTE volume);  *|
 |*         void  MPUStopNote     (BYTE channel, BYTE note);               *|
 |*         void  MPUWrite        (BYTE data);                             *|
 |*                                                                        *|
  \************************************************************************/


                    /*____ EXTERNAL VARIABLES ____*/



                    /*____ EXTERNAL FUNCTIONS ____*/

extern VATSTATUS internal_status;


                    /*____ INTERNAL VARIABLES ____*/


     WORD  mpu_addr;
VATSTATUS  mpu_status;

#define MPU_RETRIES    2
#define MPU_TIMEOUT 5000


                    /*____ INTERNAL FUNCTIONS ____*/


  /************************************************************************\
 |*                                                                        *|
 |*  void mpu_init (void);                                          v1.1   *|
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
 |*    mpu_status                                                          *|
 |*                                                                        *|
  \************************************************************************/

void mpu_init ()
{
  // init mpu_addr to standard location
  mpu_addr = 0x330;

  // init mpu_status to undetected/uninitialized
  mpu_status = v_nonexist;
}



  /************************************************************************\
 |*                                                                        *|
 |*  void mpu_reset (void);                                         v1.1   *|
  \                                                                        / 
  *|  Reset MPU-401 output.  Doesn't init in UART mode.                   |*
  /                                                                        \ 
 |*  IN:                                                                   *|
 |*    (none)                                                              *|
 |*                                                                        *|
 |*  OUT:                                                                  *|
 |*    (none)                                                              *|
 |*                                                                        *|
 |*  INCIDENTALS:                                                          *|
 |*    mpu_status                                                          *|
 |*                                                                        *|
  \************************************************************************/

void mpu_reset ()
{
  int timeout;

  if (mpu_status == v_started || mpu_status == v_stopped) {
    // disable interrupts
    vdisable ();

    // try to find the port in a command-ready state
    for (timeout=0; timeout<MPU_TIMEOUT; timeout++)
      if (!(VINPORTB (mpu_addr + 1) & 0x40))
        break;

    // debug report
    if (timeout >= MPU_TIMEOUT)
      dbprintf ("MPU init timed out on command-ready check.\n");
    else
      dbprintf ("MPU init command-ready check time: %u\n", timeout);

    // send reset command
    VOUTPORTB (mpu_addr + 1, 0xFF);

    // re-enable interrupts
    venable ();

    // re-init status as uninitialized (initialized means put in UART mode)
    mpu_status = v_nonexist;
  }
}


                    /*____ EXTERNAL FUNCTIONS ____*/


  /************************************************************************\
 |*                                                                        *|
 |*  VATBOOL MPUEnable (void);                                      v1.1   *|
  \                                                                        / 
  *|  Enable MPU-401 output.  If the port has not been set up yet, try    |*
  *|  to do so.  Set mpu_status accordingly.                              |*
  /                                                                        \ 
 |*  IN:                                                                   *|
 |*    (none)                                                              *|
 |*                                                                        *|
 |*  OUT:                                                                  *|
 |*    VATBOOL success                                                     *|
 |*      v_true on success, v_false on failure                             *|
 |*                                                                        *|
 |*  INCIDENTALS:                                                          *|
 |*    mpu_status                                                          *|
 |*                                                                        *|
  \************************************************************************/

VATBOOL MPUEnable ()
{
  int retries, timeout;

  // check MPU status
  if (mpu_status == v_unavail)
    return v_false;
  if (mpu_status == v_started)
    return v_true;

  if (mpu_status == v_nonexist) {
    // disable interrupts
    vdisable ();

    // try this whole process MPU_RETRIES times
    for (retries=0; retries<MPU_RETRIES; retries++) {
      // reset the MPU-401 port
      mpu_reset ();

      // wait for the port ready bit to clear
      for (timeout=0; timeout<MPU_TIMEOUT; timeout++)
        if (!(VINPORTB (mpu_addr + 1) & 0x80))
          break;

      // debug report
      if (timeout >= MPU_TIMEOUT)
        dbprintf ("MPU init timed out on ready clear.\n");
      else
        dbprintf ("MPU init ready clear time: %u\n", timeout);

      // check for acknowledgement of command
      if (VINPORTB (mpu_addr) == 0xFE)
        break;
    }

    if (retries >= MPU_RETRIES) {
      mpu_status = v_unavail;
      venable ();
      return v_false;
    }

    // try to find the port in a command-ready state
    for (timeout=0; timeout<MPU_TIMEOUT; timeout++)
      if (!(VINPORTB (mpu_addr + 1) & 0x40))
        break;

    // debug report
    if (timeout >= MPU_TIMEOUT)
      dbprintf ("MPU init timed out on command-ready check.\n");
    else
      dbprintf ("MPU init command-ready check time: %u\n", timeout);

    // send uart mode command
    VOUTPORTB (mpu_addr + 1, 0x3F);

    // re-enable interrupts
    venable();
  }

  // if status is v_stopped or v_nonexist (and above was successful)
  mpu_status = v_started;
  return v_true;
}



  /************************************************************************\
 |*                                                                        *|
 |*  void MPUDisable (void);                                        v1.1   *|
  \                                                                        / 
  *|  Disable MPU-401 output.  Do not reset the port.                     |*
  /                                                                        \ 
 |*  IN:                                                                   *|
 |*    (none)                                                              *|
 |*                                                                        *|
 |*  OUT:                                                                  *|
 |*    (none)                                                              *|
 |*                                                                        *|
 |*  INCIDENTALS:                                                          *|
 |*    mpu_status                                                          *|
 |*                                                                        *|
  \************************************************************************/

void MPUDisable ()
{
  if (mpu_status == v_started)
    mpu_status = v_stopped;
}



  /************************************************************************\
 |*                                                                        *|
 |*  VATSTATUS MPUStatus (void);                                    v1.1   *|
  \                                                                        / 
  *|  Retrieve status of MPU-401 output and port initialization.          |*
  /                                                                        \ 
 |*  IN:                                                                   *|
 |*    (none)                                                              *|
 |*                                                                        *|
 |*  OUT:                                                                  *|
 |*    VATSTATUS status                                                    *|
 |*      v_nonexist: MPU port has not been detected/initialized            *|
 |*      v_unavail: attempt to detect/initialize MPU port has failed       *|
 |*      v_stopped: midi output is not being directed to MPU port          *|
 |*      v_started: midi output is being directed to MPU port              *|
 |*                                                                        *|
 |*  INCIDENTALS:                                                          *|
 |*    (none)                                                              *|
 |*                                                                        *|
  \************************************************************************/

VATSTATUS MPUStatus ()
{
  return mpu_status;
}



  /************************************************************************\
 |*                                                                        *|
 |*  void MPUPatch (BYTE channel, BYTE patch);                      v1.1   *|
  \                                                                        / 
  *|  Set the specified instrument index to the specified channel on      |*
  *|  MPU-104 port.  Requires MPU init, but not Midi-MPU output.          |*
  /                                                                        \ 
 |*  IN:                                                                   *|
 |*    BYTE channel                                                        *|
 |*      the channel index, from 0 to 15                                   *|
 |*    BYTE patch                                                          *|
 |*      the instrument index, from 0 to 127, to assign the channel        *|
 |*                                                                        *|
 |*  OUT:                                                                  *|
 |*    (none)                                                              *|
 |*                                                                        *|
 |*  INCIDENTALS:                                                          *|
 |*    (none)                                                              *|
 |*                                                                        *|
  \************************************************************************/

void MPUPatch (BYTE channel, BYTE patch)
{
  // check MPU status
  if (mpu_status == v_nonexist || mpu_status == v_unavail)
    return;

  // check parameters
  if (channel > 15 || patch > 127)
    return;

  // send 'program change' for channel
  MPUWrite (0xC0 + channel);
  MPUWrite (patch);
}



  /************************************************************************\
 |*                                                                        *|
 |*  void MPUPlayNote (BYTE channel, BYTE note, BYTE volume);       v1.1   *|
  \                                                                        / 
  *|  Play the specified note on the specified MPU-401 channel at the     |*
  *|  specified volume.  Same requirements as above.                      |*
  /                                                                        \ 
 |*  IN:                                                                   *|
 |*    BYTE channel                                                        *|
 |*      the channel index, from 0 to 15                                   *|
 |*    BYTE note                                                           *|
 |*      the note, from 0 to 127, to play                                  *|
 |*    BYTE volume                                                         *|
 |*      the volume, from 0 to 127, to play the note at                    *|
 |*                                                                        *|
 |*  OUT:                                                                  *|
 |*    (none)                                                              *|
 |*                                                                        *|
 |*  INCIDENTALS:                                                          *|
 |*    (none)                                                              *|
 |*                                                                        *|
  \************************************************************************/

void MPUPlayNote (BYTE channel, BYTE note, BYTE volume)
{
  /* check VAT status */
  if (internal_status != v_started)
    return;

  // check MPU status
  if (mpu_status == v_nonexist || mpu_status == v_unavail)
    return;

  // check parameters
  if (channel > 15 || note > 127 || volume > 127)
    return;

  // send 'note on' for channel
  MPUWrite (0x90 + channel);
  MPUWrite (note);
  MPUWrite (volume);
}



  /************************************************************************\
 |*                                                                        *|
 |*  void MPUStopNote (BYTE channel, BYTE note);                    v1.1   *|
  \                                                                        / 
  *|  Stop playing the specified note on the specified MPU-401 channel.   |*
  *|  Same requirements as above.                                         |*
  /                                                                        \ 
 |*  IN:                                                                   *|
 |*    BYTE channel                                                        *|
 |*      the channel index, from 0 to 15                                   *|
 |*    BYTE volume                                                         *|
 |*      the volume, from 0 to 127, to play the channel at                 *|
 |*                                                                        *|
 |*  OUT:                                                                  *|
 |*    (none)                                                              *|
 |*                                                                        *|
 |*  INCIDENTALS:                                                          *|
 |*    (none)                                                              *|
 |*                                                                        *|
  \************************************************************************/

void MPUStopNote (BYTE channel, BYTE note)
{
  // check MPU status
  if (mpu_status == v_nonexist || mpu_status == v_unavail)
    return;

  // check parameters
  if (channel > 15 || note > 127)
    return;

  // send 'note off' for channel
  MPUWrite (0x80 + channel);
  MPUWrite (note);
  MPUWrite (0);
}



  /************************************************************************\
 |*                                                                        *|
 |*  void MPUWrite (BYTE data);                                     v1.1   *|
  \                                                                        / 
  *|  If the MPU-401 port has been initialized, writes the specified      |*
  *|  byte to it.                                                         |*
  /                                                                        \ 
 |*  IN:                                                                   *|
 |*    BYTE data                                                           *|
 |*      the data to send to the MPU-401 port                              *|
 |*                                                                        *|
 |*  OUT:                                                                  *|
 |*    (none)                                                              *|
 |*                                                                        *|
 |*  INCIDENTALS:                                                          *|
 |*    (none)                                                              *|
 |*                                                                        *|
  \************************************************************************/

void MPUWrite (BYTE data)
{
  int timeout;

  // check MPU status
  if (mpu_status == v_nonexist || mpu_status == v_unavail)
    return;

  // try to find the port in a command-ready state
  for (timeout=0; timeout<MPU_TIMEOUT; timeout++)
    if (!(VINPORTB (mpu_addr + 1) & 0x40))
      break;

  // send the value
  VOUTPORTB (mpu_addr, data);
}



/*** UNUSED ***
SHORT MPUEnter ()
{
  SHORT flag = 2;
  BYTE ack;

  vdisable();

  mpu_checked = v_true;

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
    mpu_available = v_false;
    venable();
    return v_false;
  }


  while(mpu_timeout<TIMEOUT) {            // Wait for ready bit to clear
    mpu_timeout++;
    if(!(VINPORTB(midi_mpuport+1)&0x40)) break;
  }
  dbprintf("MPUENTER() - wait for UART t.o.: %u\n",mpu_timeout);
  mpu_timeout = 0;

  VOUTPORTB(midi_mpuport+1,0x3F);          // Put it in UART mode

  mpu_available = v_true;
  venable();
  return(v_true);
}

void MPUExit(void)
{
  if (MPUStatus () == v_nonexist || MPUStatus () == v_unavail)
    return;
  if (MPUStatus () == v_started)
    MPUDisable ();
  vdisable ();
  VOUTPORTB (midi_mpuport+1, 0xFF);          // Reset the MPU
  venable ();
}

void MPUWrite(BYTE b)
{

  if(!mpu_available) return;

  mpu_timeout = 0;

  while(mpu_timeout<TIMEOUT) {        // Wait for ready bit to clear
    mpu_timeout++;
    if(!(VINPORTB(midi_mpuport+1)&0x40)) break;
  }

  VOUTPORTB(midi_mpuport,b);           // Write the byte!
}


SHORT MPUEnable ()
{
  if (!mpu_checked) {
    if (MPUEnter () == v_true) {
      midi_mpuout = v_true;
      return v_true;
    } else
      return v_false;
  } else if (mpu_available) {
    midi_mpuout = v_true;
    return v_true;
  } else
    return v_false;
}

void MPUDisable ()
{
  midi_mpuout = v_false;
}

*** UNUSED ***/

