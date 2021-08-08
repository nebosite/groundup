//
// SPREDIT - Ground Up's Sprite Editor
//  Neil B. Breeden II
//

#include <stdio.h>
#include <i86.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <gug.h>
#include <colors.h>
#include <widgets.h>

// Index into spredit.spr
#define DRAW      0
#define LINE      1
#define PAINT     2
#define RECT      3
#define FILL      4
#define PICK      5
#define SUP       6
#define SDOWN     7
#define SRIGHT    8
#define SLEFT     9
#define HFLIP    10
#define VFLIP    11
#define ROTATE   12
#define CUT      13
#define PASTE    14
#define LARROW   15
#define RARROW   16
#define UARROW   17
#define DARROW   18
#define DLARROW  19
#define DRARROW  20
#define DUARROW  21
#define DDARROW  22
#define ADDEND   23
#define DELCUR   24
#define ADDCUR   25
#define UNDO     26
#define PLAY     27
#define PAUSE    28
#define FASTER   29
#define SLOWER   30
#define RED_UP   31
#define RED_DN   32
#define GREEN_UP 33
#define GREEN_DN 34
#define BLUE_UP  35
#define BLUE_DN  36
#define BACK_1   37
#define BACK_2   38
#define INT_UP   39
#define INT_DN   40

// button indices
#define EXIT_UP     1
#define HIDDEN_1_UP 2
#define HIDDEN_2_UP 3
#define HIDDEN_3_UP 4
#define SAVE_UP     5
#define ABORT_UP    6

// sprite buttons on control panel
#define DRAW_SPR_UP     101
#define LINE_SPR_UP     102
#define PAINT_SPR_UP    103
#define RECT_SPR_UP     104
#define FILL_SPR_UP     105
#define PICK_SPR_UP     106
#define SDOWN_SPR_UP    107
#define SUP_SPR_UP      108
#define SRIGHT_SPR_UP   109
#define SLEFT_SPR_UP    110
#define HFLIP_SPR_UP    111
#define VFLIP_SPR_UP    112
#define ROTATE_SPR_UP   113
#define CUT_SPR_UP      114
#define PASTE_SPR_UP    115
#define UNDO_SPR_UP     116

// sprite buttons on sprite controls
#define RA_SPR_UP       201
#define LA_SPR_UP       202
#define DRA_SPR_UP      203
#define DLA_SPR_UP      204
#define ADDEND_SPR_UP   205
#define DELCUR_SPR_UP   206
#define ADDCUR_SPR_UP   207

// Sprite Drawing/Selector areas
#define SPRITE_DRAW_DN   301       // Draw Control Event
#define SPRITE_SELECT_UP 302
     
// Sprite sizing
#define DLARROW_SPR_UP   401
#define DRARROW_SPR_UP   402
#define DDARROW_SPR_UP   403
#define DUARROW_SPR_UP   404

// Play controls
#define PLAY_SPR_UP      501
#define PAUSE_SPR_UP     502
#define FASTER_SPR_UP    503
#define SLOWER_SPR_UP    504

// Color Controls
#define RED_SPRUP_UP     601
#define RED_SPRDN_UP     602
#define GREEN_SPRUP_UP   603
#define GREEN_SPRDN_UP   604
#define BLUE_SPRUP_UP    605
#define BLUE_SPRDN_UP    606
#define INT_SPRUP_UP     607
#define INT_SPRDN_UP     608

// Groups
#define DRAW_GROUP 101

// Other Defines
#define IDLY   450  // initial delay aftyer button is pressed
#define SDLY    50	// short repeating delay
#define MDLY   200	// medium repeating delay
#define LDLY   400	// long repeating delay

// Internal functions
void draw_sprites(int sprite_count,
						int first_sprite,
						int a_sprite,
						char *sprites[],
						char *controls[]);
void draw_big_sprite(int sprite_count,char *sprite);
void fill_sprite(char *sprites,int x,int y,int c);
void color_values(int a_color,char *palette);
void draw_colors(int a_color); 
void palette_up(int *color, int *flag, char *palette, int offset, int jump);
void palette_dn(int *color, int *flag, char *palette, int offset, int jump);
 
// Globals
#define MAX_CONTROLS 100
struct GUG_cntrl *main_controls[MAX_CONTROLS];

//**********************************************************************
main(int argc,char *argv[]) {
  int          status,i;
  unsigned int mb,mx,my;

  int          exit  =  0;     // Exit Program Flag
  int          event = -1;;    // Actual Event
  int          x,y,c;
  int          lc;             // Last Control Used
  char         cr;

  int          sx,sy,sz,xs,ys,y1;
  char         spr_save[1028];
  char         cut_buffer[1028];
  char         undo_buffer[1028];

  char         palette[768];
  int          pal_changed = 0;

  char         spr_name[80];
  char         pal_name[80];

  // Track the handles for these buttons
  int draw,line,paint,rect,fill,pick,cut,paste,undo;

  // sprites for control buttons
  extern char  *controls[];
  int          control_count = 39;

  // sprites for editing
  char         *sprites[1024];
  int          sprite_count  = 1;
  int          first_sprite  = 0;
  int          a_sprite      = 0;

  char         mes[120];
  int          a_color = 60;

  char         *p1;

  int          dlay   = 100;
  int          rdelay = 250;
  int          udelay = 150;

  if (argc < 2) {
     printf("Ground Up's Sprite Editor - Version 0.1h - GUG Version %s\n",GUGVersion());
	 printf("  Copyright 1995-1996 Ground Up Software\n");
	 printf("  usage: spredit sprfile.spr");
	 return;
  }

  p1 = strchr(argv[1],'.');
  if (p1 != NULL) *p1 = '\0';
  strcpy(spr_name,argv[1]);
  strcpy(pal_name,argv[1]);
  strcat(spr_name,".spr");
  strcat(pal_name,".pal");

  cut_buffer[0]  = 0;
  cut_buffer[2]  = 0;
  undo_buffer[0] = 0;
  undo_buffer[0] = 0;

  // Intialize the controls
  GUGInitControl(main_controls,MAX_CONTROLS);

  GUGInitialize();
  GUGMouseReset((int *)&status,(unsigned int *)&mb);
//  GUGStartKeyboard();
  GUGClearDisplay();
  for (x=0; x<10; x+=2) {
    for (y=0; y<7; ++y) {
	  GUGPutBGSprite(x*32    ,y*32,controls[37]);
	  GUGPutBGSprite((x+1)*32,y*32,controls[38]);
	}
  }

  // Introduce ourself
//  GUGMouseShow();
//  GUGMessageBox("|Ground Up's Sprite Editor|Version 0.1g|By Neil B. Breeden II",
//                " OK ");
//  GUGMouseHide();

   // Load the sprite file or see if we are making a new one
  if ((sprite_count = GUGLoadSprite(spr_name,(char **)sprites)) < 1)
  {
    GUGMouseShow();
	 sprintf(mes,"%s||The sprite file was not found!|Are you creating a new file?",spr_name);
    x = GUGMessageBox(mes," YES | NO ");
    GUGMouseHide();
    if (x == 1) {
	   GUGEnd();
      return;
	 }
	 sprites[0] = calloc(1,32*32+4);
    sprites[0][0] = 32;
	 sprites[0][2] = 32;
    sprite_count  =  1;
	 a_sprite      =  0;
	 first_sprite  =  0;
  }

 if (GUGLoadPalette(pal_name,(char *)palette) == 1) {
    GUGSetPalette(palette);
  }
  else {
    GUGGetPalette(palette);
  }

  // Register the sprite buttons
#define CXORG 153
#define CYORG   3
  // These are RADIO buttons in group 'DRAW_GROUP'
  draw  = GUGRegRadioSprite(CXORG    ,CYORG,DRAW_SPR_UP ,controls[DRAW],
                            DRAW_GROUP,GUG_SELECTED,main_controls);
  lc = draw;
  line  = GUGRegRadioSprite(CXORG+ 20,CYORG,LINE_SPR_UP ,controls[LINE],
                            DRAW_GROUP,GUG_UNSELECTED,main_controls);
  paint = GUGRegRadioSprite(CXORG+ 40,CYORG,PAINT_SPR_UP,controls[PAINT],
						          DRAW_GROUP,GUG_UNSELECTED,main_controls);
  rect  = GUGRegRadioSprite(CXORG+ 60,CYORG,RECT_SPR_UP ,controls[RECT],
						          DRAW_GROUP,GUG_UNSELECTED,main_controls);
  fill  = GUGRegRadioSprite(CXORG+ 80,CYORG,FILL_SPR_UP ,controls[FILL],
						          DRAW_GROUP,GUG_UNSELECTED,main_controls);
  pick  = GUGRegRadioSprite(CXORG+100,CYORG,PICK_SPR_UP ,controls[PICK],
									 DRAW_GROUP,GUG_UNSELECTED,main_controls);

 // These are controls
  GUGRegControlSprite(CXORG+120,CYORG,CUT_SPR_UP  ,
                     controls[CUT],main_controls);
  GUGRegControlSprite(CXORG+140,CYORG,PASTE_SPR_UP,
                     controls[PASTE],main_controls);

  GUGRegSpinSprite(CXORG    ,CYORG+21,SDOWN_SPR_UP ,
							controls[SDOWN],IDLY,MDLY,main_controls);
  GUGRegSpinSprite(CXORG+ 20,CYORG+21,SUP_SPR_UP   ,
                     controls[SUP],IDLY,MDLY,main_controls);
  GUGRegSpinSprite(CXORG+ 40,CYORG+21,SRIGHT_SPR_UP,
                     controls[SRIGHT],IDLY,MDLY,main_controls);
  GUGRegSpinSprite(CXORG+ 60,CYORG+21,SLEFT_SPR_UP ,
                     controls[SLEFT],IDLY,MDLY,main_controls);
  GUGRegControlSprite(CXORG+ 80,CYORG+21,HFLIP_SPR_UP ,
                     controls[HFLIP],main_controls);
  GUGRegControlSprite(CXORG+100,CYORG+21,VFLIP_SPR_UP ,
                     controls[VFLIP],main_controls);
  GUGRegControlSprite(CXORG+120,CYORG+21,ROTATE_SPR_UP,
                     controls[ROTATE],main_controls);
  GUGRegControlSprite(CXORG+140,CYORG+21,UNDO_SPR_UP,
							controls[UNDO],main_controls);

  // Controls for sizing the sprite
#define BSXORG 130
#define BSYORG  93
  GUGRegSpinSprite(BSXORG,BSYORG   ,DLARROW_SPR_UP,controls[DLARROW],IDLY,SDLY,main_controls);
  GUGRegSpinSprite(BSXORG,BSYORG+16,DRARROW_SPR_UP,controls[DRARROW],IDLY,SDLY,main_controls);
#define RSXORG 130
#define RSYORG   5
  GUGRegSpinSprite(RSXORG,RSYORG   ,DUARROW_SPR_UP,controls[DUARROW],IDLY,SDLY,main_controls);
  GUGRegSpinSprite(RSXORG,RSYORG+16,DDARROW_SPR_UP,controls[DDARROW],IDLY,SDLY,main_controls);
  
   // Register the SPRITE Selector controls
#define SSXORG   0
#define SSYORG 130
  GUGRegControlSprite(SSXORG   ,SSYORG,DLA_SPR_UP   ,
                     controls[DLARROW],main_controls);
  GUGRegSpinSprite(SSXORG+16,SSYORG,LA_SPR_UP    ,
                     controls[LARROW],IDLY,LDLY,main_controls);
  GUGRegControlSprite(SSXORG+29,SSYORG,DELCUR_SPR_UP,
                     controls[DELCUR],main_controls);
  GUGRegControlSprite(SSXORG+46,SSYORG,ADDCUR_SPR_UP,
                     controls[ADDCUR],main_controls);
  GUGRegSpinSprite(SSXORG+62,SSYORG,RA_SPR_UP    ,
                     controls[RARROW],IDLY,LDLY,main_controls);
  GUGRegControlSprite(SSXORG+75,SSYORG,DRA_SPR_UP   ,
                     controls[DRARROW],main_controls);
  GUGRegControlSprite(SSXORG+91,SSYORG,ADDEND_SPR_UP,
                     controls[ADDEND],main_controls);
  GUGRegControlSprite(SSXORG+111,SSYORG,PLAY_SPR_UP ,
                     controls[PLAY],main_controls);

  // Register the EXIT Control
  GUGRegControlText(275,157,SAVE_UP ,"SAVE",B_BLUE,main_controls);
  GUGRegControlText(275,171,ABORT_UP,"ABRT",B_RED,main_controls);
  GUGRegControlText(275,185,EXIT_UP ,"EXIT",B_GREEN,main_controls);

  // Register the control for the SPRITE drawing area
  GUGRegDraw(1,1,128,128,SPRITE_DRAW_DN,main_controls);

  // Register the control for the SPRITE selector area
  GUGRegHidden(0,167,254,32,SPRITE_SELECT_UP,main_controls);

  // Register hidden controls for the palette selectors
#define XORG 137
#define YORG 48
  GUGRegHidden(XORG   ,YORG   ,180,30,HIDDEN_1_UP,main_controls);
  GUGRegHidden(XORG+50,YORG+33, 80, 5,HIDDEN_2_UP,main_controls);
  GUGRegHidden(XORG+30,YORG+41,120, 5,HIDDEN_3_UP,main_controls);

  // And the color controls
#define CSXORG  210
#define CSYORG  105
  GUGRegSpinSprite(CSXORG-17,CSYORG+13,INT_SPRUP_UP  ,controls[INT_UP],IDLY,SDLY,main_controls);
  GUGRegSpinSprite(CSXORG-17,CSYORG+25,INT_SPRDN_UP  ,controls[INT_DN],IDLY,SDLY,main_controls);

  GUGRegSpinSprite(CSXORG   ,CSYORG+13,RED_SPRUP_UP  ,controls[RED_UP],IDLY,SDLY,main_controls);
  GUGRegSpinSprite(CSXORG   ,CSYORG+25,RED_SPRDN_UP  ,controls[RED_DN],IDLY,SDLY,main_controls);

  GUGRegSpinSprite(CSXORG+17,CSYORG+13,GREEN_SPRUP_UP,controls[GREEN_UP],IDLY,SDLY,main_controls);
  GUGRegSpinSprite(CSXORG+17,CSYORG+25,GREEN_SPRDN_UP,controls[GREEN_DN],IDLY,SDLY,main_controls);

  GUGRegSpinSprite(CSXORG+34,CSYORG+13,BLUE_SPRUP_UP ,controls[BLUE_UP],IDLY,SDLY,main_controls);
  GUGRegSpinSprite(CSXORG+34,CSYORG+25,BLUE_SPRDN_UP ,controls[BLUE_DN],IDLY,SDLY,main_controls);
      
  color_values(a_color,palette);

  // Draw in a palette selector
  draw_colors(a_color);

  // Draw in the sprites
  draw_sprites(sprite_count,first_sprite,a_sprite,sprites,controls);
  draw_big_sprite(sprite_count,sprites[a_sprite]);

//  GUGPutText(152,120,GREEN," Ground Up");
//  GUGPutText(152,130,BLUE ,"   NBBII");
//  GUGPutText(148,140,RED  ,"SPREDIT 0.1f");
  
  GUGMouseShow();
  do {
    event = GUGProcessControls(main_controls,
                               (unsigned int *)&mb,
                               (unsigned int *)&mx,
                               (unsigned int *)&my); 
    switch (event)
    {
		case      -1: break;

//        case FASTER_SPR_UP: if (dlay > 0) dlay -= 10;
//		                      break;
//		  case SLOWER_SPR_UP: dlay += 10;
//		                      break;

        case PLAY_SPR_UP: x = 0;
		                    GUGFillRectangle(10,10,52,52,0);
                          GUGMouseHide();
                          do {
		                      GUGFillRectangle(10,10,52,52,0);
 		                      GUGPutFGSprite(15,15,sprites[x]);
								    GUGCopyToDisplay();
									 delay(dlay/10);
							       if (++x == sprite_count) x = 0;
                            GUGMousePosition((unsigned int *)&mb,
                                             (unsigned int *)&mx,
                                             (unsigned int *)&my);
									 if ((mb == 1) && (dlay > 0)) dlay--;
									 if (mb == 2) dlay++;
						        }
						        while ((mb != 3) && (!kbhit()));
								  if (kbhit()) getch();
								  draw_sprites(sprite_count,first_sprite,
									              a_sprite,sprites,controls);
								  draw_big_sprite(sprite_count,
 						                          sprites[a_sprite]);
								  GUGCopyToDisplay();
								  GUGMouseShow();
                          do {
                            GUGMousePosition((unsigned int *)&mb,
                                             (unsigned int *)&mx,
                                             (unsigned int *)&my);
								  }
								  while (mb != 0);
								  break;

        case INT_SPRUP_UP: if (a_color < 216) {
                             if ((palette[(a_color*3)]   == 63) ||
									      (palette[(a_color*3)+1] == 63) ||
                                 (palette[(a_color*3)+2] == 63)) break;
									}
                           if (((palette[(a_color*3)]   != 63)  &&
									       (palette[(a_color*3)+1] != 63)  &&
                                  (palette[(a_color*3)+2] != 63)) ||
											 (a_color > 215)) {
	                             palette_up(&a_color,&pal_changed,palette,0,1);
                                palette_up(&a_color,&pal_changed,palette,1,6);
                                palette_up(&a_color,&pal_changed,palette,2,36);
                                draw_colors(a_color);
                                color_values(a_color,palette);
									}
                           break;

        case INT_SPRDN_UP: if (a_color < 216) {
                             if ((palette[(a_color*3)] ==   0) ||
									      (palette[(a_color*3)+1] == 0) ||
                                 (palette[(a_color*3)+2] == 0)) break;
									}
                           if (((palette[(a_color*3)]   != 0)  &&
									       (palette[(a_color*3)+1] != 0)  &&
                                  (palette[(a_color*3)+2] != 0)) ||
											 (a_color > 215)) {
	                             palette_dn(&a_color,&pal_changed,palette,0,1);
                                palette_dn(&a_color,&pal_changed,palette,1,6);
                                palette_dn(&a_color,&pal_changed,palette,2,36);
										  draw_colors(a_color);
                                color_values(a_color,palette);
									}
                           break;


        case RED_SPRUP_UP: palette_up(&a_color,&pal_changed,palette,0,1);
								   draw_colors(a_color);
									color_values(a_color,palette);
									break;

        case RED_SPRDN_UP: palette_dn(&a_color,&pal_changed,palette,0,1);
								   draw_colors(a_color);
									color_values(a_color,palette);
									break;

        case GREEN_SPRUP_UP: palette_up(&a_color,&pal_changed,palette,1,6);
									  draw_colors(a_color);
									  color_values(a_color,palette);
									  break;

        case GREEN_SPRDN_UP: palette_dn(&a_color,&pal_changed,palette,1,6);
									  draw_colors(a_color);
									  color_values(a_color,palette);
									  break;

        case BLUE_SPRUP_UP: palette_up(&a_color,&pal_changed,palette,2,36);
		                      draw_colors(a_color);
									 color_values(a_color,palette);
									 break;

        case BLUE_SPRDN_UP: palette_dn(&a_color,&pal_changed,palette,2,36);
		                      draw_colors(a_color);
									 color_values(a_color,palette);
									 break;

    } // of the switch


	 switch (event)
    {
		case      -1: break;

		  case CUT_SPR_UP: sz = GUGSpriteSize(sprites[a_sprite]);
                         memcpy(cut_buffer,sprites[a_sprite],sz);
								 break;


		  case PASTE_SPR_UP: if (cut_buffer[0] > 0) {
		                       sz = GUGSpriteSize(sprites[a_sprite]);
									  memcpy(undo_buffer,sprites[a_sprite],sz);
								     sz = GUGSpriteSize(cut_buffer);
								     free(sprites[a_sprite]);
								     sprites[a_sprite] = malloc(sz);
                             memcpy(sprites[a_sprite],cut_buffer,sz);
									  draw_sprites(sprite_count,first_sprite,
									              a_sprite,sprites,controls);
									  draw_big_sprite(sprite_count,
 						                          sprites[a_sprite]);
                             GUGMouseHide();
									  GUGCopyToDisplay();
									  GUGMouseShow();
									}
									break;

		  case UNDO_SPR_UP: if (undo_buffer[0] > 0) {
		                      sz = GUGSpriteSize(undo_buffer);
								    free(sprites[a_sprite]);
								    sprites[a_sprite] = malloc(sz);
                            memcpy(sprites[a_sprite],undo_buffer,sz);
								    draw_sprites(sprite_count,first_sprite,
									              a_sprite,sprites,controls);
								    draw_big_sprite(sprite_count,
 						                          sprites[a_sprite]);
                            GUGMouseHide();
								    GUGCopyToDisplay();
									 GUGMouseShow();
                          }
								  break;

		  case ROTATE_SPR_UP: sz = GUGSpriteSize(sprites[a_sprite]);
									 memcpy(undo_buffer,sprites[a_sprite],sz);
                            GUGSpriteRotate90(sprites[a_sprite]);
									 draw_sprites(sprite_count,first_sprite,
									              a_sprite,sprites,controls);
									 draw_big_sprite(sprite_count,
 						                          sprites[a_sprite]);
                            GUGMouseHide();
									 GUGCopyToDisplay();
									 GUGMouseShow();
									 break;

	        case VFLIP_SPR_UP: sz = GUGSpriteSize(sprites[a_sprite]);
									   memcpy(undo_buffer,sprites[a_sprite],sz);
                             GUGSpriteVFlip(sprites[a_sprite]);
									  draw_sprites(sprite_count,first_sprite,
									             a_sprite,sprites,controls);
 						           draw_big_sprite(sprite_count,
 						                         sprites[a_sprite]);
                             GUGMouseHide();
									  GUGCopyToDisplay();
									  GUGMouseShow();
									  break;
	
        case HFLIP_SPR_UP: sz = GUGSpriteSize(sprites[a_sprite]);
								   memcpy(undo_buffer,sprites[a_sprite],sz);
                           GUGSpriteHFlip(sprites[a_sprite]);
									draw_sprites(sprite_count,first_sprite,
									             a_sprite,sprites,controls);
 						         draw_big_sprite(sprite_count,
 						                         sprites[a_sprite]);
                           GUGMouseHide();
									GUGCopyToDisplay();
									GUGMouseShow();
									break;
	

        case DUARROW_SPR_UP: sz = GUGSpriteSize(sprites[a_sprite]);
									  memcpy(undo_buffer,sprites[a_sprite],sz);
									  sx = GUGSpriteWidth(sprites[a_sprite]);
									  sy = GUGSpriteHeight(sprites[a_sprite]);
									  if (sy < 3) break;
									  memcpy(spr_save,sprites[a_sprite],sz);
 									  sy--;
									  GUGPutBGSprite(5+((a_sprite-first_sprite)*35),
														  167,sprites[a_sprite]);
									  GUGMouseHide();
									  GUGCopyToDisplay();
									  GUGMouseShow();
									  free(sprites[a_sprite]);
									  sprites[a_sprite] = 
										 GUGClipSprite(5+((a_sprite-first_sprite)*35),
										               167,
                                           	sx+4+((a_sprite-first_sprite)*35),
                                           	sy+166);
									  draw_sprites(sprite_count,first_sprite,
									                 a_sprite,sprites,controls);
 						           draw_big_sprite(sprite_count,
 						                             sprites[a_sprite]);
                             GUGMouseHide();
									  GUGCopyToDisplay();
									  GUGMouseShow();
									  break;
	
        case DDARROW_SPR_UP: sz = GUGSpriteSize(sprites[a_sprite]);
									  memcpy(undo_buffer,sprites[a_sprite],sz);
									  sx = GUGSpriteWidth(sprites[a_sprite]);
									  sy = GUGSpriteHeight(sprites[a_sprite]);
									  if (sy > 31) break;
									  memcpy(spr_save,sprites[a_sprite],sz);
 									  sy++;
									  GUGPutBGSprite(5+((a_sprite-first_sprite)*35),
														  167,sprites[a_sprite]);
									  free(sprites[a_sprite]);
									  GUGRectangle(4+((a_sprite-first_sprite)*35),
										               166,
                                           	sx+5+((a_sprite-first_sprite)*35),
                                           	sy+166,
                                           	BLACK);	
                             GUGMouseHide();
									  GUGCopyToDisplay();
									  sprites[a_sprite] = 
                               GUGClipSprite(5+((a_sprite-first_sprite)*35),
										               167,
                                           	sx+4+((a_sprite-first_sprite)*35),
                                           	sy+166);
									  GUGRectangle(4+((a_sprite-first_sprite)*35),
										               166,
                                           	sx+5+((a_sprite-first_sprite)*35),
                                           	sy+166,
                                           	WHITE);	
									  draw_sprites(sprite_count,first_sprite,
									                 a_sprite,sprites,controls);
 						           draw_big_sprite(sprite_count,
 						                             sprites[a_sprite]);
									  GUGCopyToDisplay();
									  GUGMouseShow();
									  break;
	

        case DLARROW_SPR_UP: sz = GUGSpriteSize(sprites[a_sprite]);
									  memcpy(undo_buffer,sprites[a_sprite],sz);
									  sx = GUGSpriteWidth(sprites[a_sprite]);
									  sy = GUGSpriteHeight(sprites[a_sprite]);
									  if (sx < 2) break;
									  memcpy(spr_save,sprites[a_sprite],sz);
									  sx--;
									  GUGPutBGSprite(5+((a_sprite-first_sprite)*35),
														  167,sprites[a_sprite]);
									  GUGMouseHide();
									  GUGCopyToDisplay();
									  GUGMouseShow();
									  free(sprites[a_sprite]);
									  sprites[a_sprite] = 
									    GUGClipSprite(5+((a_sprite-first_sprite)*35),
										               167,
                                           	sx+4+((a_sprite-first_sprite)*35),
                                           	sy+166);
									  draw_sprites(sprite_count,first_sprite,
									                 a_sprite,sprites,controls);
 						           draw_big_sprite(sprite_count,
 						                             sprites[a_sprite]);
                             GUGMouseHide();
									  GUGCopyToDisplay();
									  GUGMouseShow();
									  break;
	
		  case DRARROW_SPR_UP: sz = GUGSpriteSize(sprites[a_sprite]);
									  memcpy(undo_buffer,sprites[a_sprite],sz);
									  sx = GUGSpriteWidth(sprites[a_sprite]);
									  sy = GUGSpriteHeight(sprites[a_sprite]);
									  if (sx > 31) break;
									  memcpy(spr_save,sprites[a_sprite],sz);
 									  sx++;
									  GUGPutBGSprite(5+((a_sprite-first_sprite)*35),
														  167,sprites[a_sprite]);

                             free(sprites[a_sprite]);
									  GUGRectangle(4+((a_sprite-first_sprite)*35),
										               166,
                                           	sx+4+((a_sprite-first_sprite)*35),
                                           	sy+167,
                                           	BLACK);	
                             GUGMouseHide();
									  GUGCopyToDisplay();
									  sprites[a_sprite] = 
									    GUGClipSprite(5+((a_sprite-first_sprite)*35),
										               167,
                                           	sx+4+((a_sprite-first_sprite)*35),
                                           	sy+166);
									  GUGRectangle(4+((a_sprite-first_sprite)*35),
										               166,
                                           	sx+4+((a_sprite-first_sprite)*35),
                                           	sy+167,
                                           	WHITE);	
 									  draw_sprites(sprite_count,first_sprite,
									                 a_sprite,sprites,controls);
 						           draw_big_sprite(sprite_count,
 						                             sprites[a_sprite]);
									  GUGCopyToDisplay();
									  GUGMouseShow();
									  break;
	

		case SPRITE_DRAW_DN:
					  //Paint
									 if (main_controls[paint]->state == GUG_SELECTED) {
										 sz = GUGSpriteSize(sprites[a_sprite]);
									    memcpy(undo_buffer,sprites[a_sprite],sz);
										 lc = paint;
										 x  = (mx-1) / 4;
		                         y  = (my-1) / 4;
								       GUGPutText(0,0,WHITE,"PAINT");
										 fill_sprite(sprites[a_sprite],x,y,a_color);
						 		       draw_sprites(sprite_count,first_sprite,
						  		  				 a_sprite,sprites,controls);
 						             draw_big_sprite(sprite_count,
 						                      sprites[a_sprite]);
                               GUGMouseHide();
										 GUGCopyToDisplay();
                               GUGMouseShow();
                               do {
                                 GUGMousePosition((unsigned int *)&mb,
                                                  (unsigned int *)&mx,
                                                  (unsigned int *)&my);
										 }
										 while (mb != 0);
										 break;
									  }

									  if (main_controls[draw]->state == GUG_SELECTED) {
                             lc = draw;
								  //   GUGMouseHide();
									  GUGMouseHorizontalLimit(1,
										 (GUGSpriteWidth(sprites[a_sprite])*4));
									  GUGMouseVerticalLimit(1,
										 (GUGSpriteHeight(sprites[a_sprite])*4));
                             do {
                               GUGMousePosition((unsigned int *)&mb,
                                                (unsigned int *)&mx,
                                                (unsigned int *)&my);
			                      x  = (mx-1) / 4;
								       y  = (my-1) / 4;
										 c  = GUGSpriteWidth(sprites[a_sprite]);
								       sprites[a_sprite][(y*c)+x+4] = a_color;
							          draw_sprites(sprite_count,first_sprite,
									                 a_sprite,sprites,controls);
 						             draw_big_sprite(sprite_count,
															  sprites[a_sprite]);
                               GUGMouseHide();
										 GUGCopyToDisplay();
										 GUGMouseShow();
									  }
								     while (mb == 1);
									  GUGMouseHorizontalLimit(0,319);
									  GUGMouseVerticalLimit(0,199);
 								  //	  GUGMouseShow();
									  break;
		                     }
                     
						// Line
						         if (main_controls[line]->state == GUG_SELECTED) {
									  sz = GUGSpriteSize(sprites[a_sprite]);
									  memcpy(undo_buffer,sprites[a_sprite],sz);
									  lc = line;
                             GUGMouseHide();
									  GUGMouseHorizontalLimit(1,
										 (GUGSpriteWidth(sprites[a_sprite])*4));
									  GUGMouseVerticalLimit(1,
										 (GUGSpriteHeight(sprites[a_sprite])*4));
									  sx = (mx-1) / 4;
									  sy = (my-1) / 4;
									  sz = GUGSpriteSize(sprites[a_sprite]);
                             memcpy(spr_save,sprites[a_sprite],sz);
                             do {
                               GUGMousePosition((unsigned int *)&mb,
                                                (unsigned int *)&mx,
                                                (unsigned int *)&my);
			                      x  = (mx-1) / 4;
								       y  = (my-1) / 4;
								       xs = GUGSpriteWidth(sprites[a_sprite]); 
                               ys = GUGSpriteHeight(sprites[a_sprite]);                                       
                               memcpy(sprites[a_sprite],spr_save,sz);
										 GUGPutBGSprite(5+((a_sprite-first_sprite)*35),167,
										                sprites[a_sprite]);
										 GUGLine(sx+5+((a_sprite-first_sprite)*35),sy+167,
										         x+5+((a_sprite-first_sprite)*35), y+167,
												   a_color);
										 GUGCopyToDisplay();
                               free(sprites[a_sprite]);
										 sprites[a_sprite] = 
										   GUGClipSprite(5+((a_sprite-first_sprite)*35),167,
                                           	  xs+4+((a_sprite-first_sprite)*35),ys+166);
							          draw_sprites(sprite_count,first_sprite,
									                 a_sprite,sprites,controls);
 						             draw_big_sprite(sprite_count,
 						                             sprites[a_sprite]);
									    GUGCopyToDisplay();
								     }
								     while (mb == 1);
									  GUGMouseHorizontalLimit(0,319);
									  GUGMouseVerticalLimit(0,199);
 									  GUGMouseShow();
									  break;
								   }

					   // RECT
			                  if (main_controls[rect]->state == GUG_SELECTED) {
									  sz = GUGSpriteSize(sprites[a_sprite]);
									  memcpy(undo_buffer,sprites[a_sprite],sz);
									  lc = rect;
                             GUGMouseHide();
									  GUGMouseHorizontalLimit(1,
										 (GUGSpriteWidth(sprites[a_sprite])*4));
									  GUGMouseVerticalLimit(1,
										 (GUGSpriteHeight(sprites[a_sprite])*4));
									  sx = (mx-1) / 4;
									  sy = (my-1) / 4;
									  sz = GUGSpriteSize(sprites[a_sprite]);
                             memcpy(spr_save,sprites[a_sprite],sz);
                             do {
                               GUGMousePosition((unsigned int *)&mb,
                                                (unsigned int *)&mx,
                                                (unsigned int *)&my);
			                      x  = (mx-1) / 4;
								       y  = (my-1) / 4;
								       xs = GUGSpriteWidth(sprites[a_sprite]); 
                               ys = GUGSpriteHeight(sprites[a_sprite]);                                       
                               memcpy(sprites[a_sprite],spr_save,sz);
										 GUGPutBGSprite(5+((a_sprite-first_sprite)*35),167,
										               sprites[a_sprite]);
										 GUGRectangle(sx+5+((a_sprite-first_sprite)*35),sy+167,
										              x+5+((a_sprite-first_sprite)*35), y+167,
												        a_color);
										 GUGCopyToDisplay();
                               free(sprites[a_sprite]);
										 sprites[a_sprite] = 
										   GUGClipSprite(5+((a_sprite-first_sprite)*35),167,
                                               xs+4+((a_sprite-first_sprite)*35),ys+166);
							          draw_sprites(sprite_count,first_sprite,
									                 a_sprite,sprites,controls);
 						             draw_big_sprite(sprite_count,
 						                             sprites[a_sprite]);
									    GUGCopyToDisplay();
								     }
								     while (mb == 1);
									  GUGMouseHorizontalLimit(0,319);
									  GUGMouseVerticalLimit(0,199);
 									  GUGMouseShow();
									  break;
								   }

					   // FILL RECT
			                  if (main_controls[fill]->state == GUG_SELECTED) {
									  sz = GUGSpriteSize(sprites[a_sprite]);
									  memcpy(undo_buffer,sprites[a_sprite],sz);
                             lc = fill;
                             GUGMouseHide();
									  GUGMouseHorizontalLimit(1,
										 (GUGSpriteWidth(sprites[a_sprite])*4));
									  GUGMouseVerticalLimit(1,
										 (GUGSpriteHeight(sprites[a_sprite])*4));
									  sx = (mx-1) / 4;
									  sy = (my-1) / 4;
									  sz = GUGSpriteSize(sprites[a_sprite]);
                             memcpy(spr_save,sprites[a_sprite],sz);
                             do {
                               GUGMousePosition((unsigned int *)&mb,
                                                (unsigned int *)&mx,
                                                (unsigned int *)&my);
			                      x  = (mx-1) / 4;
								       y  = (my-1) / 4;
								       xs = GUGSpriteWidth(sprites[a_sprite]); 
                               ys = GUGSpriteHeight(sprites[a_sprite]);                                       
                               memcpy(sprites[a_sprite],spr_save,sz);
										 GUGPutBGSprite(5+((a_sprite-first_sprite)*35),167,
										               sprites[a_sprite]);
										 GUGFillRectangle(sx+5+((a_sprite-first_sprite)*35),sy+167,
										                  x+5+((a_sprite-first_sprite)*35), y+167,
												            a_color);
										 GUGCopyToDisplay();
                               free(sprites[a_sprite]);
										 sprites[a_sprite] = 
										 GUGClipSprite(5+((a_sprite-first_sprite)*35),167,
                                      		   xs+4+((a_sprite-first_sprite)*35),ys+166);
							          draw_sprites(sprite_count,first_sprite,
									                 a_sprite,sprites,controls);
 						             draw_big_sprite(sprite_count,
 						                             sprites[a_sprite]);
									    GUGCopyToDisplay();
								     }
								     while (mb == 1);
									  GUGMouseHorizontalLimit(0,319);
									  GUGMouseVerticalLimit(0,199);
 									  GUGMouseShow();
									  break;
								   }

					   // PICK Color
			                  if (main_controls[pick]->state == GUG_SELECTED) {
 								     a_color = GUGGetPixel(mx,my);
                             main_controls[PICK]->state = GUG_UNSELECTED;
                             main_controls[lc]->state   = GUG_SELECTED;
                             do {
										 GUGMousePosition((unsigned int *)&mb,
                                                (unsigned int *)&mx,
                                                (unsigned int *)&my);
									  }
									  while (mb != 0);
   		                    draw_colors(a_color);
                             color_values(a_color,palette);
                             mb = -1; // force screen redraw
    							     break;
   			   				}

			                  break;

			 case SPRITE_SELECT_UP: x = mx / 35;
											y = first_sprite + x;
											if (y >= sprite_count) break;
											a_sprite = y;
							            draw_sprites(sprite_count,first_sprite,
									                   a_sprite,sprites,controls);
 						               draw_big_sprite(sprite_count,sprites[a_sprite]);
											break;

          case SLEFT_SPR_UP:if (sprite_count > 0) {
										GUGShiftSpriteLeft(sprites[a_sprite]);
							         draw_sprites(sprite_count,first_sprite,
										             a_sprite,sprites,controls);
 						            draw_big_sprite(sprite_count,sprites[a_sprite]);
                            }
							       break;

          case SRIGHT_SPR_UP:if (sprite_count > 0) {
										 GUGShiftSpriteRight(sprites[a_sprite]);
										 draw_sprites(sprite_count,first_sprite,
										              a_sprite,sprites,controls);
										 draw_big_sprite(sprite_count,
										                 sprites[a_sprite]);
                             }
							        break;

         case SDOWN_SPR_UP:  if (sprite_count > 0) {
			 							 GUGShiftSpriteDown(sprites[a_sprite]);
							          draw_sprites(sprite_count,first_sprite,
										              a_sprite,sprites,controls);
 						             draw_big_sprite(sprite_count,sprites[a_sprite]);
									  }
							        break;
 
        case SUP_SPR_UP:     if (sprite_count > 0) {
										 GUGShiftSpriteUp(sprites[a_sprite]);
							          draw_sprites(sprite_count,first_sprite,
										              a_sprite,sprites,controls);
									    draw_big_sprite(sprite_count,
									                    sprites[a_sprite]);
                             }
							        break;
 


        case ADDEND_SPR_UP: if (sprite_count < 1024) {
							         sprites[sprite_count] = calloc(1,32*32+4);
                              sprites[sprite_count][0] = 32;
							         sprites[sprite_count][2] = 32;
                              sprite_count++;
							         a_sprite = sprite_count - 1; // a_sprite++;
                              if ((a_sprite - 6) > 0)
							           first_sprite = a_sprite - 6; // first_sprite++;
										else
										  first_sprite = 0;
										draw_sprites(sprite_count,first_sprite,
										             a_sprite,sprites,controls);
										draw_big_sprite(sprite_count,
										                sprites[a_sprite]);
                            }
							       break;

        case ADDCUR_SPR_UP: if (a_sprite == sprite_count-1) {
		                        sprite_count++;
							         a_sprite++;
										if ((a_sprite - 6) > 0)
										  first_sprite = a_sprite - 6;
										else
										  first_sprite = 0;
							         sprites[a_sprite] = calloc(1,32*32+4);
                              sprites[a_sprite][0] = 32;
							         sprites[a_sprite][2] = 32;
							         draw_sprites(sprite_count,first_sprite,
										             a_sprite,sprites,controls);
										draw_big_sprite(sprite_count,
										                sprites[a_sprite]);
							         break;
		                      }
							       else
							       {
							         if (sprite_count < 1023) {
							           sprite_count++;
							           for (x=sprite_count; x>a_sprite; --x) {
							             sprites[x] = sprites[x-1];
							           }
							           sprites[a_sprite] = calloc(1,32*32+4);
                                sprites[a_sprite][0] = 32;
							           sprites[a_sprite][2] = 32;
							           draw_sprites(sprite_count,first_sprite,
								  		               a_sprite,sprites,controls);
										  draw_big_sprite(sprite_count,
										                  sprites[a_sprite]);
							           break;
							         }
		                      }
							       break;

        case DELCUR_SPR_UP: if (sprite_count < 2) break;
		                      sz = GUGSpriteSize(sprites[a_sprite]);
									 memcpy(undo_buffer,sprites[a_sprite],sz);
									 if (a_sprite == sprite_count-1) {
                              free(sprites[a_sprite]);
		                        sprite_count--;
                              a_sprite--;
							         draw_sprites(sprite_count,first_sprite,
										             a_sprite,sprites,controls);
										draw_big_sprite(sprite_count,
										                sprites[a_sprite]);
							         break;
							       }
							       free(sprites[a_sprite]);
							       for (x=a_sprite;x<=sprite_count;++x) {
							         sprites[x] = sprites[x+1];
							       }
							       sprite_count--;
							       draw_sprites(sprite_count,first_sprite,
									           	  a_sprite,sprites,controls);
									 draw_big_sprite(sprite_count,
									                 sprites[a_sprite]);
							       break;

		case DLA_SPR_UP:  first_sprite  = 0;
								a_sprite = 0;
								draw_sprites(sprite_count,first_sprite,
												 a_sprite,sprites,controls);
								draw_big_sprite(sprite_count,sprites[a_sprite]);
								break;

		case DRA_SPR_UP:  first_sprite  = sprite_count-7;
		                  if (first_sprite < 0) first_sprite = 0;
						      a_sprite = sprite_count-1;
						      draw_sprites(sprite_count,first_sprite,
								   	       a_sprite,sprites,controls);
						      draw_big_sprite(sprite_count,sprites[a_sprite]);
						      break;

		case RA_SPR_UP:   if (a_sprite < sprite_count-1) {
								  a_sprite++;
								  if (a_sprite > first_sprite+6) {
									 first_sprite++;
								  }
								  draw_sprites(sprite_count,first_sprite,
													a_sprite,sprites,controls);
								  draw_big_sprite(sprite_count,sprites[a_sprite]);
								}
								break;

		case LA_SPR_UP:   if (a_sprite > 0) {
								  a_sprite--;
								  if (a_sprite < first_sprite) {
									 first_sprite--;
								  }
								  draw_sprites(sprite_count,first_sprite,
													a_sprite,sprites,controls);
								  draw_big_sprite(sprite_count,sprites[a_sprite]);
								}
								break;

      case HIDDEN_1_UP: x = mx - XORG;
                        x = x / 5;
                        y = my - YORG;
                        y = y / 5;
						      a_color = (y * 36) + x;
   			            draw_colors(a_color);
                        color_values(a_color,palette);
                        break;

		case HIDDEN_2_UP: x = mx - XORG - 50;
                        x = x / 5;
					         a_color = 216 + x;
   		               draw_colors(a_color);
                        color_values(a_color,palette);
                        break;

		case HIDDEN_3_UP: x = mx - XORG - 30;
                        x = x / 5;
						      a_color = 232 + x;
   			            draw_colors(a_color);
                        color_values(a_color,palette);
                        break;

		case EXIT_UP: GUGSaveSprite(spr_name,sprites,sprite_count-1);
                    if (pal_changed) {
						    GUGSavePalette(pal_name,palette);
	                   GUGMessageBox("||Sprites and Palette saved."," OK ");
						  }
						  else
						  {
	                   GUGMessageBox("||Sprites have been saved."," OK ");
						  }
						  exit  =  1;
                    break;

		case SAVE_UP: GUGSaveSprite(spr_name,sprites,sprite_count-1);
                    if (pal_changed) {
						    GUGSavePalette(pal_name,palette);
	                   GUGMessageBox("||Sprites and Palette saved."," OK ");
						  }
						  else
						  {
	                   GUGMessageBox("||Sprites have been saved."," OK ");
						  }
	                 break;

		case ABORT_UP: x = GUGMessageBox("||Abort and lose all edits?",
		                                 " Yes | No ");
 							if (x == 0)
		                 exit  =  1;
                     break;
	 };
  }
  while (!exit);


  GUGMouseHide();
//  GUGStopKeyboard();
  GUGMouseReset((int *)&status,(unsigned int *)&mb);
  GUGEnd();

}

//************************************************************************
// Internal functions

void draw_sprites(int sprite_count,
						int first_sprite,
						int a_sprite,
						char *sprites[],
						char *controls[]) {
  int  x,y,c,os;
  char mes[80];

  sprintf(mes,"Sprite %d of %d",a_sprite,sprite_count);
//  GUGFillRectangle(0,154,160,163,0);
  for (x=0; x<8; x+=2) {
    GUGPutBGSprite(x*32    ,153,controls[37]);
	 GUGPutBGSprite((x+1)*32,153,controls[38]);
    GUGPutBGSprite(x*32    ,183,controls[37]);
	 GUGPutBGSprite((x+1)*32,183,controls[38]);
  }
  GUGPutText(1,154,BLUE,mes);

//  GUGFillRectangle(4,166,251,199,0);
  if (sprite_count > 0) {
	 x = first_sprite + 7;
	 if (x > sprite_count) x = sprite_count;
     os = first_sprite;
	 for (c=first_sprite; c<x; ++c) {
		GUGPutFGSprite(5+((c-os)*35),167,sprites[c]);
	   GUGRectangle(4+((c-os)*35),166,
					  4+((c-os)*35)+1+GUGSpriteWidth(sprites[c]),
					  167+GUGSpriteHeight(sprites[c]),BLACK);
 	 }
	 x =   4 + ((a_sprite-os) * 35);
    y = 166;
	 GUGRectangle(x,y,
					  x+1+GUGSpriteWidth(sprites[a_sprite]),
					  y+1+GUGSpriteHeight(sprites[a_sprite]),WHITE);
  }
  else
  {
    GUGRectangle(4,167,36,199,WHITE);
  }
}

void draw_big_sprite(int sprite_count, char *sprite) {
  int x,y;
  int xs,ys;
  char *s;
  char mes[80];
 
  int size;

  xs = GUGSpriteWidth(sprite);
  ys = GUGSpriteHeight(sprite);

//  if ((xs < 17) && (ys < 17))
//    size = 8;
//  else if ((xs < 33) && (ys < 33))
    size = 4;
//  else if ((xs < 65) && (ys < 65))
//    size = 2;
//  else if ((xs < 129) && (ys < 129))
//    size = 1;

  sprintf(mes,"X:%2d x Y:%2d",xs,ys);
//  GUGFillRectangle(161,154,260,163,0);
  GUGPutText(161,154,BLUE,mes);

  GUGFillRectangle(0,0,129,129,0);

  if (sprite_count > 0) {
    s = sprite + 4;
    for (y=0; y<ys; ++y) {
	   for (x=0; x<xs; ++x) {
          if ((x*size+size < 129) && (y*size+size < 129))
	        GUGFillRectangle(x*size+1,
	                         y*size+1,
	                         x*size+size,
	                         y*size+size,
	                         (int)*s);
		  s++;
	   }
    }
  }
  GUGRectangle(0,0,129,129,WHITE);
  xs = xs * size + 1;
  ys = ys * size + 1;
  if (xs > 129) xs = 129;
  if (ys > 129) ys = 129;
  if (sprite_count > 0) {
    GUGRectangle(0,0,xs,ys,BLUE);
  }
}

//*********************************************************************
// Fill sprite with a color
void fill_sprite(char * spr,int px, int py,int c) {
  char data[32][32];
  char *s;
  int  x,y,f;
  int  xsize,ysize;

  void recur_fill(char data[32][32],int px,int py,int f,int c);

  for (x=0; x<32; ++x) {
    for (y=0; y<32; ++y) {
	   data[x][y] = 255;
	 }
  }

  xsize = GUGSpriteWidth(spr);
  ysize = GUGSpriteHeight(spr);
  s     = spr + 4;

  for (y=0; y<ysize; ++y) {
	 for (x=0; x<xsize; ++x) {
		data[x][y] = s[(y*xsize)+x];
	 }
  }

//  if (data[px][py] != 0) return;

  f = data[px][py];
  if (f == c) return;

  recur_fill(data,px,py,f,c);

  for (y=0; y<ysize; ++y) {
	 for (x=0; x<xsize; ++x) {
		s[(y*xsize)+x] = data[x][y];
	 }
  }
}


void recur_fill(char data[32][32],int px,int py,int f,int c) {
  if (px <  0) return;
  if (py <  0) return;
  if (px > 31) return;
  if (py > 31) return;

  if (data[px][py] == f) {
	 data[px][py] = c;
	 recur_fill(data,px-1,py,f,c);
	 recur_fill(data,px+1,py,f,c);
	 recur_fill(data,px,py-1,f,c);
	 recur_fill(data,px,py+1,f,c);
  }
}

//*************************************************************************
// Color Values
void color_values(int a_color,char *palette) {
  
  int r,g,b,c;
  char mes[10];
 
  r = palette[a_color*3];
  g = palette[(a_color*3)+1];
  b = palette[(a_color*3)+2];

//  GUGFillRectangle(CSXORG,CSYORG+13,CSXORG+52,CSYORG+25,a_color);
  GUGFillRectangle(CSXORG-17,CSYORG,CSXORG+52,CSYORG+12,a_color);


  if ((r > 42) || (g > 42) || (b > 42))
    c = BLACK;
  else
    c = WHITE;

  if (a_color > 15)
    sprintf(mes,"%2X",a_color);
  else
    sprintf(mes,"0%1X",a_color);
  GUGPutText(CSXORG-16,CSYORG+4,c,mes);

  if (r > 15)
    sprintf(mes,"%2X",r);
  else
    sprintf(mes,"0%1X",r);
  GUGPutText(CSXORG+1,CSYORG+4,c,mes);

  if (g > 15)
    sprintf(mes,"%2X",g);
  else
    sprintf(mes,"0%1X",g);
  GUGPutText(CSXORG+19,CSYORG+4,c,mes);

  if (b > 15)
    sprintf(mes,"%2X",b);
  else
    sprintf(mes,"0%1X",b);
  GUGPutText(CSXORG+37,CSYORG+4,c,mes);
} 

void draw_colors(int a_color) {
  int x,y,c,o;

  o = WHITE;   // 255 - a_color;

  for (c=0,y=0;y<6;++y) {
    for (x=0; x<36; ++x) {
     GUGFillRectangle(x*5+XORG,y*5+YORG,x*5+5+XORG,y*5+5+YORG,c);
     GUGRectangle(x*5+XORG,y*5+YORG,x*5+5+XORG,y*5+5+YORG,87);
     c++;
   }
  }

  y = c + 16;
  for (x=0;c<y;++c,++x) {
	GUGFillRectangle(x*5+XORG+50,YORG+33,x*5+5+XORG+50,YORG+38,c);
 	GUGRectangle(x*5+XORG+50,YORG+33,x*5+5+XORG+50,YORG+38,87);
  }   

  for (x=0;c<256;++c,++x) {
   GUGFillRectangle(x*5+XORG+30,YORG+41,x*5+5+XORG+30,YORG+46,c);
   GUGRectangle(x*5+XORG+30,YORG+41,x*5+5+XORG+30,YORG+46,87);
  }   

  for (x=0;x<8;++x) {
	GUGFillRectangle(x*5+XORG+70,YORG+49,x*5+5+XORG+70,YORG+54,c);
 	GUGRectangle(x*5+XORG+70,YORG+49,x*5+5+XORG+70,YORG+54,87);
  }   


  //
  // Draw a white rectangle around the selected color
  for (c=0,y=0;y<6;++y) {
    for (x=0; x<36; ++x) {
      if (c == a_color) {
        GUGRectangle(x*5+XORG,y*5+YORG,x*5+5+XORG,y*5+5+YORG,o);
		  return;
	   }
      c++;
    }
  }

  y = c + 16;
  for (x=0;c<y;++c,++x) {
    if (c == a_color) {
	   GUGRectangle(x*5+XORG+50,YORG+33,x*5+5+XORG+50,YORG+38,o);
	   return;
	 }
  }   

  for (x=0;c<256;++c,++x) {
    if (c == a_color) {
      GUGRectangle(x*5+XORG+30,YORG+41,x*5+5+XORG+30,YORG+46,o);
      return;
	 }
  }   

}

//***********************************************************************
// Palette Adjustment Funcs()

void palette_up(int *color, int *flag, char *palette, int offset, int jump) {
  int a_color;
  int c;

  a_color = *color;
  if (a_color < 216) {
    c = palette[(a_color*3)+offset];
	 if (c != 63) {
	   a_color+=jump;
	   if (a_color > 215) a_color-=jump;
	 }
  }
  else
  {
    c = palette[(a_color*3)+offset];
	 if (c != 63) { 
	   palette[(a_color*3)+offset]++;
      GUGSetPalette(palette);
      *flag = 1;
    }
  }
  *color = a_color;
}

void palette_dn(int *color, int *flag, char *palette, int offset, int jump) {
  int a_color;
  int c;

  a_color = *color;
		
  if (a_color < 216) {
    c = palette[(a_color*3)+offset];
	 if (c != 0) {
	   a_color-=jump;
	   if (a_color < 0) a_color+=jump;
	 }
  }
  else
  {
    c = palette[(a_color*3)+offset];
	 if (c > 0) { 
	   palette[(a_color*3)+offset]--;
      GUGSetPalette(palette);
      *flag = 1;
    }
  }
  *color = a_color;
}

