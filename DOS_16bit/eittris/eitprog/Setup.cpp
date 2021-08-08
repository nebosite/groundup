// Varmint's EITTRIS
// Copyright (C) 1996-2000, Purple Planet Software

#include "stdafx.h"
#include "eittris.h"
#include "hiscore.h"
#include "resource.h"

#define FONT_SIZE 12

DWORD dateearly=19960203L;
DWORD datelate=19960504L;

WORD tetrissamplerate = 22000;

DVFONT *font;
extern WORD		dsp_vers;
extern SHORT	debug_lowdsp;


int speedtest();

/**************************************************************************
	int setup(void)

	DESCRIPTION:  Sets up graphics and everything


**************************************************************************/
int eitsetup(void)
{
	void eittimer(void);
	int i,j=0,k,n,end;
	CString msg;
	DWORD transcolor;
	//struct date today;
	//DWORD date1;

									// Check the date
	//getdate(&today);
	//date1 = today.da_year*10000L + today.da_mon * 100L + (DWORD)today.da_day;


/*  if(date1 < dateearly || date1 > datelate) {
  	printf("\nThe current date is (%d/%d/%d).\n",
						(int)today.da_mon,(int)today.da_day,(int)today.da_year );
    printf("This beta version is not valid at this time.  Please check\n");
		printf("     http://www.ericjorgensen.com/eittris\n");
    printf("For the most recent version.\n");
    exit(2);
	}*/

	HKEY regkey;
	HRESULT r;
	DWORD size = sizeof(DWORD);

	srand(time(NULL));

	r = RegCreateKeyEx(HKEY_CURRENT_USER,"Software\\PurplePlanet\\EITtris",0,NULL,
			REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&regkey,NULL);
	if(ERROR_SUCCESS == r) {
		RegQueryValueEx(regkey,"Z",0,NULL,(LPBYTE)&localkey,&size);
		if(localkey < 1 || localkey > 63000) {
			localkey = (random(9000)+1) * 7;
			RegSetValueEx(regkey,"Z",0,REG_DWORD,(LPBYTE)&localkey,sizeof(DWORD));
		}
	}
	else {
		localkey = 63000;
	}


	if(!highscoreson) {
		msg.Format("Notice:  \n\n"
			"High scores have been deactivated because you have altered game play\n"
			"options in EITTRIS.CFG.  If you want to play with high scores enabled,\n"
			"you need to comment out any game play option settings.\n\n"
			"Please press any key to continue...\n");
		AfxMessageBox(msg);
	}


	for(i=0; i < MAXPLAYERS; i++) person[i] = NULL;  		// reset all player pointers
	for(i = 0; i < 50; i++) bgrnd[i] = NULL;    // reset backgroun pointers

	// Make sure we have hi scores loaded
	if(!scores) scores = readscores();

								// Set up font
//	font = g_lpdvdrawobject->FontLoadTT("Arial Narrow",FONT_SIZE,col_White);
//	font = g_lpdvdrawobject->FontLoadTT("Tempus Sans ITC",FONT_SIZE,col_White);
	font = g_lpdvdrawobject->FontLoadTT("Arial",FONT_SIZE,col_White);
	g_lpdvdrawobject->FontSet(font);

//	txtht = g_lpdvdrawobject->GetTextHeight("A")+2;


	// allocate dummy blocks

	dummy[0] = new DVSPRITE();
	if(!dummy[0]->Create(g_lpdvdrawobject->GetDrawingObject(),maxx,maxy,1)) {
		msg.Format("Sprite create error: %s",dummy[0]->m_szErrorMessage);
		AfxMessageBox(msg);
		return false;
	}

								// Load the graphics
	g_lpdvdrawobject->BitmapPut(MAKEINTRESOURCE(IDB_BITMAP_BLOCKS),0,0);
	for(i = 0; i < 256; i++) shape[i] = NULL;
	transcolor = g_lpdvdrawobject->GetPixel(153,0);

    end = SPECIALBASE + NUMBEROFSPECIALS;
	if(end < ANIMBASE + 12) end = ANIMBASE + 12;
	for(i = 0; i < end; i++) {           // Read the normal blocks
		shape[i] = g_lpdvdrawobject->SpriteGet(NULL,
			(i%20)*block_width,
			(i/20)*block_height,
			(i%20)*block_width+block_width,
			(i/20)*block_height+block_height, 0);
		if(!shape[i]) {
			msg.Format("Sprite create error: %s",g_lpdvdrawobject->m_szErrorMessage);
			AfxMessageBox(msg);
			return false;
		}
	}

	for(i = 8; i < 16; i++) {
		shape[i]->SetTransparentIndex(COLORKEY_EXPLICIT,transcolor);
	}

	for(i  = 0; i < numbackgrounds; i++) {  // Read backgrounds
		// Create the structures
		bgrnd[i] = new BGROUND;
		if(!bgrnd[i]) {
			msg.Format("Out of memory allocating backgrounds");
			AfxMessageBox(msg);
			return false;
		}
		// Fill them up
		for(j = 0; j < 2; j++) {
			for(k = 0; k < 2; k++) {
				n = (i%10)*2 +(i/10)*40 + 80 + j + k*20;
				bgrnd[i]->b[j][k] = g_lpdvdrawobject->SpriteGet(NULL,
					(n%20)*block_width,(n/20)*block_height,
					(n%20)*block_width+block_width,
					(n/20)*block_height+block_height, 0);

				if(!bgrnd[i]->b[j][k]) {
					msg.Format("Sprite create error: %s",g_lpdvdrawobject->m_szErrorMessage);
					AfxMessageBox(msg);
					return false;
				}
			}
		}
	}



	for(i = 0; i < 256; i++) {          // Assign all the shapes for kicks
		if(!shape[i]) shape[i] = shape[0];
	}

	g_lpdvdrawobject->Clear(0);			// clear the screen

	return true;
}

/*===========================================================================
	void eitcleanup()

	DESCRIPTION:	Clean up data allocated in eitsetup

	  REVISIONS:
			12/4/99		Eric Jorgensen		Initial Version

============================================================================*/
void eitcleanup()
{

}
