// Varmint's EITTRIS
// Copyright (C) 1996-2000, Purple Planet Software

#include "stdafx.h"
#include "eittris.h"



/**************************************************************************
	void sticksound(int i)

  DESCRIPTION:  Plays the sound that a piece makes when it sticks.

  INPUTS:
  	p		Player number

**************************************************************************/
void sticksound(int p)
{
	dosound(17,random(60)+20,p*50+150);
}

/**************************************************************************
	void menuclicksound(int f)

	DESCRIPTION:  Makes a nice menu-type tap sound

	INPUTS:

		f		frequency

**************************************************************************/
void menuclicksound(int f)
{
	dosound(10,50,f);
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
	LONG id,v;

	if(!soundon) return;

	id = g_lpdvsoundobject->WavePlay(soundbite[sn]);
	v = (100-vol) * 100;
	if(v > 0) v = 0;
	if(v < -10000) v = -10000;
	if(freq)  g_lpdvsoundobject->WaveSetting(id,DVS_RATE,(freq * 11000)/100);
	if(vol)  g_lpdvsoundobject->WaveSetting(id,DVS_VOLUME,v);
}

