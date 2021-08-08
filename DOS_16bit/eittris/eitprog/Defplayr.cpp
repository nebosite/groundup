// Varmint's EITTRIS
// Copyright (C) 1996-2000, Purple Planet Software

#include "stdafx.h"
#include "eittris.h"


int cspeed[10] = {10,15,20,25,30,40,50,60,80,100};
int caccuracy[10] = {500,666,800,900,950,975,983,990,995,1000};
char *ctypes[10] = {"Senator","DoorKnob","Moron","Easy","Ordinary","Tough","Tougher","HONIG","Mr. EIT","Completely unfair"};

/**************************************************************************
	PLAYER *newplayer(int num)

	INPUT:
		num			Player number

  DESCRIPTION:  Generates a new player and sets default values

**************************************************************************/
PLAYER  *newplayer(int num)
{
	int i;
	PLAYER  *p;

	p = new PLAYER;
	if(!p) return NULL;

	p->bw = block_width;                               // Set piece size
	p->bh = block_height;
	strcpy(p->name,names[random(13)]);                 // make a name
	p->controltype = 'H';
	p->computer_counter = 0;
	p->special_probability = maxtime_to_special;       // Av. num of ticks to next sp.
	p->special_lifetime = special_lifetime;   				 // LIfetime in ticks
	p->special_counter = 0;
	p->pkey[PKEYLEFT]     = DIK_NUMPAD7; // 'KP7';
	p->pkey[PKEYRIGHT]		= DIK_NUMPAD9; // 'KP9';
	p->pkey[PKEYDOWN]		 	= DIK_NUMPAD5; // 'KP5';
	p->pkey[PKEYDROP]		 	= DIK_NUMPAD4; // 'KP4';
	p->pkey[PKEYRLEFT]		= DIK_NUMPAD8; // 'KP8';
	p->pkey[PKEYRRIGHT]	 	= DIK_NUMPAD6; // 'KP6';
	p->pkey[PKEYVICTIM]	 	= DIK_ADD; // 'KP+';
	p->pkey[PKEYANTEDOTE] = DIK_NUMPAD1; // 'KP1';
	p->computer_smarts = 5;
	p->computer_speed = cspeed[p->computer_smarts];
	p->computer_accuracy = caccuracy[p->computer_smarts];
	p->plaindraw = FALSE;
	for(i = 0; i < 5; i++) p->timer[i] = 0;
	p->gridx=5 + num * 200 + (maxx-800)/2;
	p->gridy=5 + (maxy - 600)/2;


	return(p);

}



/**************************************************************************
	void defineplayer(int num)

	DESCRIPTION:  Allows the users to set player options

	char name[20];
	char controltype;
	int computer_speed,computer_accuracy;

**************************************************************************/
void defineplayer(int num)
{
	int drawflag=1,flag = 1,color,choice = 0,x,y;
	int r;
	char instring[255];
	PLAYER *p;
	int timeout = 0;

	// Center coordinates
	x = (maxx-800)/2 + 150;
	y = (maxy-600)/2 + 200;

	if(!person[num]) {                      // Slot empty?
		person[num] = newplayer(num);            // Make a new player
		// set up playing grid location
	}

	p = person[num];                        // abbreviated pointer name



	while(flag) {                           // Main input loop

		if(drawflag) {                        //  Draw choices
			g_lpdvdrawobject->DrawFillRectangle(0,0,y-50,x+370,maxy);   // clear area
			color = g_lpdvdrawobject->RGBColor(230,230,230);                   //  Light gray color for valid stats
			g_lpdvdrawobject->Print(color,x,y,"Name:          %s",p->name);
			g_lpdvdrawobject->Print(color,x,y + 20,"Controltype:   %s",
				(p->controltype == 'H')?"Human   ":"Computer");
			if(p->controltype == 'C') color = g_lpdvdrawobject->RGBColor(127,127,127);
			g_lpdvdrawobject->Print(color,x,y+ 40,"Key controls:\tLeft: %s",
				g_lpdvinputobject->KeyName(p->pkey[PKEYLEFT]));
			g_lpdvdrawobject->Print(color,x,y+60, "\t\tRight: %s",
				g_lpdvinputobject->KeyName(p->pkey[PKEYRIGHT]));
			g_lpdvdrawobject->Print(color,x,y+80, "\t\tDown: %s",
				g_lpdvinputobject->KeyName(p->pkey[PKEYDOWN]));
			g_lpdvdrawobject->Print(color,x,y+100,"\t\tDrop: %s",
				g_lpdvinputobject->KeyName(p->pkey[PKEYDROP]));
			g_lpdvdrawobject->Print(color,x,y+120,"\t\tRotate Left: %s",
				g_lpdvinputobject->KeyName(p->pkey[PKEYRLEFT]));
			g_lpdvdrawobject->Print(color,x,y+140,"\t\tRotate Right: %s",
				g_lpdvinputobject->KeyName(p->pkey[PKEYRRIGHT]));
			g_lpdvdrawobject->Print(color,x,y+160,"\t\tChange Victim: %s",
				g_lpdvinputobject->KeyName(p->pkey[PKEYVICTIM]));
			g_lpdvdrawobject->Print(color,x,y+180,"\t\tUse Antedote: %s",
				g_lpdvinputobject->KeyName(p->pkey[PKEYANTEDOTE]));

			if(p->controltype == 'C') color = g_lpdvdrawobject->RGBColor(230,230,230);
			else color = g_lpdvdrawobject->RGBColor(127,127,127);

			g_lpdvdrawobject->Print(color,x,y+200,"Intelligence: [%d]  %s   ",
				p->computer_smarts+1,ctypes[p->computer_smarts]);
			color = col_Green;                   // Green for action items
			g_lpdvdrawobject->Print(color,x,y+220,"Delete this Player");
			g_lpdvdrawobject->Print(color,x,y+240,"Done -> Go back");
			drawflag = 0;
		}
		// Grab a keystroke
		while(!eitkbhit()) {
			g_lpdvdrawobject->SpritePut(x-25,y+choice*20,0,shape[ANIMBASE + 2 + arrowseq[frame++ % 18]]);
			Sleep(30);
		}
		menuclicksound(500);
		r = egetch();
		if(!r  && eitkbhit()) r = egetch();

		if(r == 27 || toupper(r) == 'Q') flag = 0;
		else if(r == DVCHAR_ARROWUP) {                        // Down
			g_lpdvdrawobject->SpritePut(x-25,y+choice*20,0,shape[0]);
			choice --;
			if(choice == 9) choice = 2;
			if(choice < 0) choice = 12;
		}
		else if(r == DVCHAR_ARROWDOWN) {                  // Up
			g_lpdvdrawobject->SpritePut(x-25,y+choice*20,0,shape[0]);
			choice ++;
			if(choice == 3)  choice = 10;
			if(choice > 12) choice = 0;
		}
		else if(r == 13 || r == ' ' ) {       // Choose it!
			switch(choice) {
			case 0:                           // name
				instring[0] = 0;
				getinput(x,y+300,col_White,0,"Enter player name: ",instring,15);
				strcpy(p->name,instring);
				drawflag = 1;
				break;
			case 1:                           // control type
				if(p->controltype == 'H') p->controltype = 'C';
				else p->controltype = 'H';
				drawflag = 1;
				break;
			case 2:                           // Key Controls
				g_lpdvinputobject->FlushKeyboard();
				g_lpdvdrawobject->DrawFillRectangle(0,x,y+300,x+300,y+320);
				g_lpdvdrawobject->Print(col_White,x,y+300,"Key to Move Left:");
				p->pkey[PKEYLEFT] = getscancode();
				g_lpdvdrawobject->DrawFillRectangle(0,x,y+300,x+300,y+320);
				g_lpdvdrawobject->Print(col_White,x,y+300,"Key to Move Right:");
				p->pkey[PKEYRIGHT] = getscancode();
				g_lpdvdrawobject->DrawFillRectangle(0,x,y+300,x+300,y+320);
				g_lpdvdrawobject->Print(col_White,x,y+300,"Key to Move Down:");
				p->pkey[PKEYDOWN] = getscancode();
				g_lpdvdrawobject->DrawFillRectangle(0,x,y+300,x+300,y+320);
				g_lpdvdrawobject->Print(col_White,x,y+300,"Key to Drop:");
				p->pkey[PKEYDROP] = getscancode();
				g_lpdvdrawobject->DrawFillRectangle(0,x,y+300,x+300,y+320);
				g_lpdvdrawobject->Print(col_White,x,y+300,"Key to Rotate Left:");
				p->pkey[PKEYRLEFT] = getscancode();
				g_lpdvdrawobject->DrawFillRectangle(0,x,y+300,x+300,y+320);
				g_lpdvdrawobject->Print(col_White,x,y+300,"Key to Rotate Right:");
				p->pkey[PKEYRRIGHT]= getscancode();
				g_lpdvdrawobject->DrawFillRectangle(0,x,y+300,x+300,y+320);
				g_lpdvdrawobject->Print(col_White,x,y+300,"Key to Change Victim:");
				p->pkey[PKEYVICTIM]= getscancode();
				g_lpdvdrawobject->DrawFillRectangle(0,x,y+300,x+300,y+320);
				g_lpdvdrawobject->Print(col_White,x,y+300,"Key to Use Antedote:");
				p->pkey[PKEYANTEDOTE]= getscancode();
				drawflag = 1;
				break;
			case 10:                           // Intelligence
				p->computer_smarts++;
				if(p->computer_smarts > 9) p->computer_smarts= 0;
				p->computer_speed = cspeed[p->computer_smarts];
				p->computer_accuracy = caccuracy[p->computer_smarts];
				drawflag = 1;
				break;
			case 11:                          // Delete
				delete person[num];
				person[num] = NULL;
				flag = 0;
				break;
			case 12:                          // Done
				flag = 0;
				break;
			default: break;
			}
		}
	}

}

