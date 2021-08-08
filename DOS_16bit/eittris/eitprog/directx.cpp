// Varmint's EITTRIS
// Copyright (C) 1996-2000, Purple Planet Software
//
// Miscellaneous functions and data to facilitate multimedia

#include "stdafx.h"
#include "eittris.h"
#include "resource.h"

int maxx = 800,maxy = 600;
CDVDraw *g_lpdvdrawobject = NULL;
CDVInput *g_lpdvinputobject = NULL;
CDVSound *g_lpdvsoundobject = NULL;

DWORD col_White;
DWORD col_Black;
DWORD col_Blue;
DWORD col_Green;
DWORD col_Red;
DWORD col_Magenta;
DWORD col_Yellow;
DWORD col_Orange;
DWORD col_Cyan;
DWORD col_SkyBlue;
DWORD col_Gray[16];

extern int bgcolor;
extern int labelcolor;
extern int valuecolor;


/*===========================================================================
	DWORD col(int r, int g, int b)

	DESCRIPTION:	Convenience color function

	  REVISIONS:
			12/4/99		Eric Jorgensen		Initial Version

============================================================================*/
DWORD col(int r, int g, int b)
{
	return 	g_lpdvdrawobject->RGBColor(r,g,b);
}

/*===========================================================================
	void SetDrawHandle(CDVDraw *drawobject)

	DESCRIPTION:	Sets the global drawing handle and gets important
					graphics data.

	  REVISIONS:
			12/3/99		Eric Jorgensen		Initial Version

============================================================================*/
void SetDrawHandle(CDVDraw *drawobject)
{
	_ASSERT(drawobject);

	g_lpdvdrawobject = drawobject;

	maxx = drawobject->m_iMaxx;
	maxy = drawobject->m_iMaxy;

	col_White = drawobject->RGBColor(255,255,255);  
	col_Black = drawobject->RGBColor(0,0,0);  
	col_Blue = drawobject->RGBColor(0,0,255);   
	col_Green = drawobject->RGBColor(0,255,0);  
	col_Red = drawobject->RGBColor(255,0,0);    
	col_Magenta = drawobject->RGBColor(255,0,255);
	col_Yellow = drawobject->RGBColor(255,255,0); 
	col_Orange = drawobject->RGBColor(255,127,0); 
	col_Cyan = drawobject->RGBColor(0,255,255);   
	col_SkyBlue = drawobject->RGBColor(80,80,255);
	for(int i = 0; i < 16; i++) {
		col_Gray[i] = drawobject->RGBColor(i*17,i*17,i*17);
	}

	bgcolor = col_Gray[5];
	labelcolor = drawobject->RGBColor(0,200,230);
	valuecolor = col_Red;

								// Set up the fade table
	int r,g,b;
	for(i = 0; i <= 0xffff; i++) {
		r = drawobject->RGBRed(i)/3;
		g = drawobject->RGBGreen(i)/3;
		b = drawobject->RGBBlue(i)/3;
		fadetable[i] = drawobject->RGBColor(r,g,b);
	}
}

/*===========================================================================
	void SetInputHandle(CDVInput *inputobject)

	DESCRIPTION:	Sets the global input handle

	  REVISIONS:
			12/4/99		Eric Jorgensen		Initial Version

============================================================================*/
void SetInputHandle(CDVInput *inputobject)
{
	g_lpdvinputobject = inputobject;	
}

/*===========================================================================
	void SetSoundHandle(CDVSound *soundtobject)

	DESCRIPTION:	Sets the global sound handle and initializes sound data.

	  REVISIONS:
			12/4/99		Eric Jorgensen		Initial Version

  
	char *soundfilename[]={
	"!PCEFUL1.WAV",              // 0
	"AGONY.WAV",                 // 1
	"ALARMCLK.WAV",              // 2
	"AWWWWW.WAV",                // 3
	"BIGPIPE.WAV",               // 4
	"BIGSMSH.WAV",               // 5
	"CAMEL.WAV",                 // 6
	"CARHORN.WAV",               // 7
	"CRICKET.WAV",               // 8
	"DENTDRIL.WAV",              // 9
	"DOCOE.WAV",                 // 10
	"DRIP.WAV",                  // 11
	"NELSON.WAV",                // 12
	"THIP.WAV",                  // 13
	"THUP.WAV",                  // 14
	"TAP.WAV",                   // 15
	"BING.WAV",                  // 16
	"DOK.WAV",                   // 17
	"PFFEHH.WAV",                // 18
	"DANK.WAV",                  // 19
	"PMP.WAV",                   // 20
	"DROP.WAV"};                 // 21  

============================================================================*/
void SetSoundHandle(CDVSound *soundtobject)
{
	int i;
	int notloaded = 0;

	g_lpdvsoundobject = soundtobject;
	
	soundbite[0] = g_lpdvsoundobject->WaveLoad(MAKEINTRESOURCE(IDR_WAVE_0));	
	soundbite[1] = g_lpdvsoundobject->WaveLoad(MAKEINTRESOURCE(IDR_WAVE_1));	
	soundbite[2] = g_lpdvsoundobject->WaveLoad(MAKEINTRESOURCE(IDR_WAVE_2));	
	soundbite[3] = g_lpdvsoundobject->WaveLoad(MAKEINTRESOURCE(IDR_WAVE_3));	
	soundbite[4] = g_lpdvsoundobject->WaveLoad(MAKEINTRESOURCE(IDR_WAVE_4));	
	soundbite[5] = g_lpdvsoundobject->WaveLoad(MAKEINTRESOURCE(IDR_WAVE_5));	
	soundbite[6] = g_lpdvsoundobject->WaveLoad(MAKEINTRESOURCE(IDR_WAVE_6));	
	soundbite[7] = g_lpdvsoundobject->WaveLoad(MAKEINTRESOURCE(IDR_WAVE_7));	
	soundbite[8] = g_lpdvsoundobject->WaveLoad(MAKEINTRESOURCE(IDR_WAVE_8));	
	soundbite[9] = g_lpdvsoundobject->WaveLoad(MAKEINTRESOURCE(IDR_WAVE_9));	
	soundbite[10] = g_lpdvsoundobject->WaveLoad(MAKEINTRESOURCE(IDR_WAVE_10));	
	soundbite[11] = g_lpdvsoundobject->WaveLoad(MAKEINTRESOURCE(IDR_WAVE_11));	
	soundbite[12] = g_lpdvsoundobject->WaveLoad(MAKEINTRESOURCE(IDR_WAVE_12));	
	soundbite[13] = g_lpdvsoundobject->WaveLoad(MAKEINTRESOURCE(IDR_WAVE_13));	
	soundbite[14] = g_lpdvsoundobject->WaveLoad(MAKEINTRESOURCE(IDR_WAVE_14));	
	soundbite[15] = g_lpdvsoundobject->WaveLoad(MAKEINTRESOURCE(IDR_WAVE_15));	
	soundbite[16] = g_lpdvsoundobject->WaveLoad(MAKEINTRESOURCE(IDR_WAVE_16));	
	soundbite[17] = g_lpdvsoundobject->WaveLoad(MAKEINTRESOURCE(IDR_WAVE_17));	
	soundbite[18] = g_lpdvsoundobject->WaveLoad(MAKEINTRESOURCE(IDR_WAVE_18));	
	soundbite[19] = g_lpdvsoundobject->WaveLoad(MAKEINTRESOURCE(IDR_WAVE_19));	
	soundbite[20] = g_lpdvsoundobject->WaveLoad(MAKEINTRESOURCE(IDR_WAVE_20));	
	soundbite[21] = g_lpdvsoundobject->WaveLoad(MAKEINTRESOURCE(IDR_WAVE_21));
	soundbite[22] = NULL;

	for(i = 0; i < 22; i++) {
		if(!soundbite[i]) notloaded++;
	}

	if(notloaded)  AfxMessageBox("WARNING:  Some sound data could not be loaded.");


}

