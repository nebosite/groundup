
/**************************************************************************

	SFX.C

  Sound effects code for Varmint's EITTRIS.

  Written by: Eric Jorgensen (1995)

**************************************************************************/
#include "tetris.h"



/**************************************************************************
	void sticksound(int i)

  DESCRIPTION:  Plays the sound that a piece makes when it sticks.

  INPUTS:
  	p		Player number

**************************************************************************/
void sticksound(int p)
{

	if(!soundon) return;

	if(soundtype == SBSOUND) {
		dosound(17,random(60)+20,p*50+150);
	}
  else if(soundtype == PCSOUND) {
  	sound(200+p*5);
  }

}

/**************************************************************************
	void menuclicksound(int f)

	DESCRIPTION:  Makes a nice menu-type tap sound

	INPUTS:

		f		frequency

**************************************************************************/
void menuclicksound(int f)
{

	if(soundtype == SBSOUND) {
		dosound(10,50,f);
	}
  else if(soundtype == PCSOUND) {
		pcsound(f);
		MilliDelay(10);
		nosound();
  }

}



/**************************************************************************
	void pcsound(int s)

	DESCRIPTION: controllable pc speaker sound function

	INPUTS:
		s		The frequency of the PC beep to make

**************************************************************************/
void pcsound(int s)
{
	if(!soundon) return;

	sound(s);

}

/**************************************************************************
	void dosound(int sn,int vol, int freq)

	DESCRIPTION:  General sound handler for tetris.  This takes sample rate
								into effect so that the sounds are the same no matter
								what it is.

	INPUTS:
		sn		Sound number
		vol		Sound Volume (0-100)
		freq  Frequency 100 = normal

**************************************************************************/
void dosound(int sn,int vol, int freq)
{
	LONG id;

	if(!soundon) return;

	id = PlaySound(soundbite[sn],v_fancy);
	if(freq) AlterSoundEffect(id,v_setrate,(freq * 256L * 110L)/sample_rate);
	if(vol)  AlterSoundEffect(id,v_setvolume,(vol * 32)/100);
}

