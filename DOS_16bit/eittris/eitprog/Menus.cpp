// Varmint's EITTRIS
// Copyright (C) 1996-2000, Purple Planet Software

#include "stdafx.h"
#include "eittris.h"
#include "hiscore.h"
#include "resource.h"

void playersetup(void);
void showscores(void);
void egg2(void);

const int NUMOPTIONS = 6;
/**************************************************************************
	void mainmenu(void)

	DESCRIPTION:  Handles everything

**************************************************************************/
void mainmenu(void)
{
	int menuflag = 1,drawflag = 1,flag = 1;
	int opt = 0;
	static int egg2on = 0;
	int left,top;
	int i,j;
	int px,py,eddie=0;
	char easterstring[20] = {"                   "};
	char *option[] = {"PLAY","PLAYER SET UP","INSTRUCTIONS","HIGH SCORES",
		"ABOUT EITTRIS","QUIT"};
	int c=' ';
	int timeout=0;
	int runthroughs = 0;
	char instring[1000];

	easterstring[19] = 0;

	left = (maxx-800)/2;
	top = (maxy-600)/2;


	while(flag) {                         // main input loop
		if(drawflag) {                      // Put title page in the screen
			g_lpdvdrawobject->Clear(0);
			g_lpdvdrawobject->BitmapPut(MAKEINTRESOURCE(IDB_BITMAP_TITLE),left,top);
			drawflag = 0;
		}
		if(menuflag) {                      // Draw the main menu
			g_lpdvdrawobject->DrawFillRectangle(col_Black,left,top+150,left+520,maxy);

			for(i = 0; i < NUMOPTIONS; i++) { // Draw all the entries
				g_lpdvdrawobject->Print(col_SkyBlue,240,250 + i*18,option[i]);
			}
			// Draw player list
			g_lpdvdrawobject->Print(col_Yellow,230,380,"Current Players");
			for(i = 0;i < 4; i++) {
				if(person[i]) {
					g_lpdvdrawobject->Print(col_Green,200,400+i*16,person[i]->name);
					g_lpdvdrawobject->Print(col_Green,350,400+i*16,
						person[i]->controltype=='C'?"Computer ":"Human     ");
				}
			}
			menuflag = 0;
		}
		// animate the palette while we
		// wait for the keyboard.


		timeout=0;																										  
		while(!eitkbhit()) {
			g_lpdvdrawobject->SpritePut(215,250+opt*18,0,shape[ANIMBASE + 2 + arrowseq[frame++ % 18]]);
			for(i = 0; i < 10; i++) {
				if(egg2on) {
					egg2();
					Sleep(1);
				}
				else Sleep(3);
			}

			if(g_lpdvdrawobject->GetPixel(0,0) != g_lpdvdrawobject->RGBColor(0,0,0)) {
				drawflag = 1;
				menuflag = 1;
			}
		}

		menuclicksound(350);
		c = egetch();                        // grab a keystroke

		if(c == 'd') {
			g_lpdvdrawobject->DrawPixel(1,0,0); 
		}

		// easter egg code
		if(c >= ' ') {
			for(i = 0; i < 18; i++) easterstring[i] = easterstring[i+1];
			easterstring[18] = tolower(c);
			if(strstr(easterstring,"eddietwo")) {
				g_lpdvdrawobject->DrawFillCircle(col_Gray[12],left+641,top+487,13);
				g_lpdvdrawobject->DrawFillCircle(col_Gray[12],left+680,top+480,13);
				g_lpdvdrawobject->DrawCircle    (col_Gray[5],left+641,top+487,13);
				g_lpdvdrawobject->DrawCircle    (col_Gray[5],left+680,top+480,13);
				eddie = 1;
			}
			if(strstr(easterstring,"snow")) {
				egg2on = 1;
			}
		}



		if(c == DVCHAR_ARROWUP) {
			g_lpdvdrawobject->SpritePut(215,250+opt*18,0,shape[0]);
			opt--;
			if(opt < 0) opt = NUMOPTIONS-1;
		}
		else if(c == DVCHAR_ARROWDOWN) {
			g_lpdvdrawobject->SpritePut(215,250+opt*18,0,shape[0]);
			opt++;
			if(opt >= NUMOPTIONS) opt = 0;
		}
		else if(c == 's' && eitdebugfile) {
//			instring[0] = 0;
//			getinput(10,550,col_White,0,"Enter special: ",instring,15);
//			j = atoi(instring);
//			for(i = 0; i < NUMBEROFSPECIALS; i++) {
//				specialgrid[i] = 0;
//				if(i == j) specialgrid[i] = 0xffff;
//			}
		}
		else if(c == ' ' || c == 13) {
			switch(opt) {
			case 0:                         // play a game
				playgame();
				menuflag=1;
				drawflag =1;
				break;
			case 1:                          // Setup
				playersetup();
				menuflag = 1;
				break;
			case 2:                            // Instructions
				g_lpdvdrawobject->DrawFillRectangle(col_Black,left+0,top+150,left+520,maxy);
				g_lpdvdrawobject->Print(col_Yellow,left+10,top+151,"Instructions-");
				g_lpdvdrawobject->Print(col_Cyan,left+10,top+165,
					"   Varmint's Eittris is a competitive game.  You can play for");
				g_lpdvdrawobject->Print(col_Cyan,left+10,top+179,
					"points or for survival against human and/or computer");
				g_lpdvdrawobject->Print(col_Cyan,left+10,top+193,
					"opponents.  The game play is pretty straight forward except");
				g_lpdvdrawobject->Print(col_Cyan,left+10,top+207,
					"for twists provided by special pieces.  To activate one");
				g_lpdvdrawobject->Print(col_Cyan,left+10,top+221,
					"of these special pieces, simply clear the row it is in.");

				g_lpdvdrawobject->Print(col_Cyan,left+10,top+240,
					"   All specials are listed below-  You can have fun\n");
				g_lpdvdrawobject->Print(col_Cyan,left+10,top+254,
					"figuring out on your own what they do:");

				g_lpdvdrawobject->Print(col_Cyan,left+10,top+470,
					"Special keys you can press during play:");
				g_lpdvdrawobject->Print(col_Yellow,left+30,top+490,
					"F1  - Pause/Continue Game");
				g_lpdvdrawobject->Print(col_Yellow,left+30,top+504,
					"F2  - Toggle Music");
				g_lpdvdrawobject->Print(col_Yellow,left+30,top+518,
					"F3  - Toggle Sound Effects");
				g_lpdvdrawobject->Print(col_Yellow,left+30,top+532,
					"F4  - Toggle Turbo Mode");
				g_lpdvdrawobject->Print(col_Yellow,left+30,top+546,
					"ESC - End Round");


				for(i = 0 ; i < NUMBEROFSPECIALS; i++) {
					px = (i% 3) *150 + 30 + left;
					py = (i /3) *22 + 284 + top;
					g_lpdvdrawobject->SpritePut(px,py,0,shape[SPECIALBASE+i]);
					g_lpdvdrawobject->Print(col_Yellow,px+25,py,"%s",specialname[i]);
				}
				egetch();
				menuflag=1;
				break;
			case 3:
				g_lpdvdrawobject->DrawFillRectangle(col_Black,left+0,top+150,left+520,maxy);
				showscores();
				menuflag = 1;
				break;
			case 4:                          // credits
				g_lpdvdrawobject->DrawFillRectangle(col_Black,left+0,top+150,left+520,maxy);
				drawbox(left+30,top+240,left+510,top+500,5,215,120,43);
				g_lpdvdrawobject->Print(col_Yellow,left+50,top+250,
					"Varmint's EITTris %s",VERSION);
				g_lpdvdrawobject->Print(col_White,left+50,top+265,
					"Copyright (c) 1996-2000 - Purple Planet Software, a division");
				g_lpdvdrawobject->Print(col_White,left+50,top+285,
					"\t\tof Alpine Development Associates.");
				g_lpdvdrawobject->Print(col_Green,left+50,top+310,
					"Written by: Eric Jorgensen (varmint@purpleplanet.com)");
				g_lpdvdrawobject->Print(col_Green,left+50,top+330,
					"DirectX by: DirectVarmint (v %s)",gszDVVersion);
				g_lpdvdrawobject->Print(col_Green,left+50,top+350,
					"\t\tWorld Wide Web Site: www.mightybits.com");
				g_lpdvdrawobject->Print(col_Green,left+50,top+370,
					"Music: Various artists. (P.D. MODs and S3Ms)");
				g_lpdvdrawobject->Print(col_Cyan,left+50,top+400,
					"World Wide Web Site:");
				g_lpdvdrawobject->Print(col_Cyan,left+50,top+420,
					"     http://www.purpleplanet.com");
				menuflag = 1;
				egetch();
				break;
			case 5:                            // Quit
				flag = 0;
				break;
			default:
				break;
			}
		}
		// Easter egg on?
		if(eddie) {
			g_lpdvdrawobject->DrawFillCircle(col_Gray[12],left+641,top+487,11);
			g_lpdvdrawobject->DrawFillCircle(col_Gray[14],left+636,top+481+opt,5);
			g_lpdvdrawobject->DrawFillCircle(col_Gray[0],left+636,top+481+opt,2);
			g_lpdvdrawobject->DrawCircle    (col_Gray[10],left+636,top+481+opt,5);
			g_lpdvdrawobject->DrawFillCircle(col_Gray[12],left+680,top+480,11);
			g_lpdvdrawobject->DrawFillCircle(col_Gray[14],left+677,top+474+opt,5);
			g_lpdvdrawobject->DrawFillCircle(col_Gray[0],left+677,top+474+opt,2);
			g_lpdvdrawobject->DrawCircle    (col_Gray[10],left+677,top+474+opt,5);
		}


	}

}



/**************************************************************************
	  void showscores(void)

	  DESCRIPTION: Displays high score for the user

**************************************************************************/
void showscores(void)
{
	int scorespot= 0,tempspot,i,j;
	HISCORE *hs,*prinths;
	int flag = 1;
	char str[56],r;
	int left, top;

	left = (maxx-800)/2;
	top = (maxy-600)/2;

	g_lpdvdrawobject->Print(col_Cyan,left+20,top+220,
		"-HIGH SCORES- Use arrows to scroll. ESC exits.");
	g_lpdvdrawobject->Print(col_Yellow,left + 20, top + 250,"PLACE");
	g_lpdvdrawobject->Print(col_Yellow,left + 80, top + 250,"NAME");
	g_lpdvdrawobject->Print(col_Yellow,left + 200, top + 250,"SCORE");
	g_lpdvdrawobject->Print(col_Yellow,left + 260, top + 250,"ROWS");
	g_lpdvdrawobject->DrawLine(col_Yellow,left + 20, top + 265, left+320, top+265);
	// Main loop
	while(flag) {
		// Find where we are
		tempspot = 0;
		hs = scores;
		while(tempspot < scorespot && hs->next) {
			hs = hs->next;
			tempspot++;
		}
		// keep us off the edge
		if(!hs->next) scorespot = tempspot;

		// print up scores
		prinths = hs;
		for(i = 0; i < 20; i++) {
			memset(str,' ',50);        // clear string;
			str[50] = 0;
			// Fill it with score info
			if(prinths) {
				g_lpdvdrawobject->Print(col_Cyan,left + 35, top + 270 + i* 16,"%d)",++tempspot);
				g_lpdvdrawobject->Print(col_Cyan,left + 80, top + 270 + i* 16,"%s",prinths->name);
				g_lpdvdrawobject->Print(col_Cyan,left + 200, top + 270 + i* 16,"%6ld",prinths->score);
				g_lpdvdrawobject->Print(col_Cyan,left + 270, top + 270 + i* 16,"%3d",prinths->rows);
				prinths = prinths->next;
			}
//			g_lpdvdrawobject->Print(col_Cyan,left + 20, top + 270 + i* 16,str);

		}
		// get a keystroke
		while(!eitkbhit()); 
		r = egetch();
		menuclicksound(550);

		if(r == DVCHAR_ARROWUP) {
			scorespot -= 10;
			if(scorespot < 0) scorespot = 0;
		}
		else if(r == DVCHAR_ARROWDOWN) {
			scorespot += 10;
		}
		else if(r == 27 || r == 13 || r == ' ')		flag = 0;
	}

}





