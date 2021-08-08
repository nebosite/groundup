#include <stdio.h>
#include <i86.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "..\gug.h"
#include "..\keydefs.h"

// Button Style Offset
#define OFFSET +1

// control types
#define GUG_CONTROL_BUTTON 1
#define GUG_SPRITE_BUTTON  2
#define GUG_SPRITE_SPIN    3
#define GUG_RADIO_TEXT     4
#define GUG_RADIO_SPRITE   5
#define GUG_DRAW_CONTROL   6
#define GUG_HIDDEN_CONTROL 7
#define GUG_HOT_KEY        8

// General Defines
#define GUG_FAIL   -1
#define GUG_SUCCESS 1

#define GUG_UNSELECTED 0
#define GUG_SELECTED   1

#define OPEN       0
#define USED       1
#define LAST       2
#define LAST_USED  3

struct GUG_cntrl
{
  int  used;       // 0 = OPEN  1 = USED  2 = LAST  3 = LAST_USED
  int  x_pos;      // X Position
  int  y_pos;      // Y Position
  int  x_size;     // X Size in Pixels
  int  y_size;     // Y Size in Pixels
  int  event;      // Event ID
  char *text;      // Button Text
  int  color;      // Text Color
  int  type;       // Control Type
  int  group;      // Control group
  int  state;      // On/Off etc
  int  delay;      // Intitial Delay for spin buttons
  int  repeat;     // Delay between steps on spin buttons
};

// Initialize a control set
void GUGInitControl(struct GUG_cntrl *GUG_Controls[],
                      int    MAX_Control);

// Register the various controls
int GUG_reg_control( struct GUG_cntrl *GUG_Controls[],
                     int  x_pos,
                     int  y_pos,
                     int  x_size,
                     int  y_size,
                     int  event,
                     char *text,
                     int  color,
                     int  type,
                     int  group,
                     int  state,
                     int  delay,
                     int  repeat);

// Using the registered controls return events
int GUGProcessControls(struct GUG_cntrl *GUG_Controls[],
                       unsigned int *b,
                       unsigned int *x,
                       unsigned int *y);

// Draw Control buttons
void GUG_draw_control_up(struct GUG_cntrl *control);
void GUG_draw_control_dn(struct GUG_cntrl *control);

// Draw Control sprites
void GUG_draw_sprite_up(struct GUG_cntrl *control);
void GUG_draw_sprite_dn(struct GUG_cntrl *control);

// Handle/Draw Text Radio Buttons
void GUG_handle_radio_text(struct GUG_cntrl *GUG_Controls[],
                           int i, int con_used);
void GUG_draw_radio_text(struct GUG_cntrl *control);
// Handle/Draw Text Radio Buttons
void GUG_handle_radio_sprite(struct GUG_cntrl *GUG_Controls[],
                             int i, int con_used);
void GUG_draw_radio_sprite(struct GUG_cntrl *control);

// Get Radio Button Status
int GUGGetRadioStatus(int handle,struct GUG_cntrl *GUG_Controls[]);



//****************************************************************
// Function to Initialize controls
//
void GUGInitControl(struct GUG_cntrl *GUG_Controls[],
                      int    MAX_Control) {
  int x;

  for (x=0; x<MAX_Control; ++x) { // mark controls as open
      GUG_Controls[x] = NULL;
  }
}



//*****************************************************************
// Function to register controls
//
int GUG_reg_control(struct GUG_cntrl *GUG_Controls[],
                    int  xpos,
                    int  ypos,
                    int  x_size,
                    int  y_size,
                    int  event,
                    char *text,
                    int  color,
                    int  type,
                    int  group,
                    int  state,
                    int  delay,
                    int  repeat) {

  int con_used;

  // Find an OPEN control slot for the control
  for (con_used=0; con_used < 1024; ++con_used) {
    if (GUG_Controls[con_used] == NULL) {
      GUG_Controls[con_used] = malloc(sizeof(struct GUG_cntrl));
          break;
        }
  }

  GUG_Controls[con_used]->x_pos  = xpos;
  GUG_Controls[con_used]->y_pos  = ypos;

  switch (type)
  {
    case GUG_SPRITE_SPIN:
            GUG_Controls[con_used]->x_size = GUGSpriteWidth(text)  + 5;
            GUG_Controls[con_used]->y_size = GUGSpriteHeight(text) + 5;
            break;
     case GUG_SPRITE_BUTTON:
            GUG_Controls[con_used]->x_size = GUGSpriteWidth(text)  + 5;
            GUG_Controls[con_used]->y_size = GUGSpriteHeight(text) + 5;
            break;
     case GUG_CONTROL_BUTTON:
            GUG_Controls[con_used]->x_size = GUGTextWidth(text) + 8;
            GUG_Controls[con_used]->y_size = GUG_Font_Height    + 6;
            break;
         case GUG_RADIO_TEXT:
            GUG_Controls[con_used]->x_size = GUGTextWidth(text) + 8;
            GUG_Controls[con_used]->y_size = GUG_Font_Height    + 2;
            break;
         case GUG_RADIO_SPRITE:
            GUG_Controls[con_used]->x_size = GUGSpriteWidth(text)  + 5;
            GUG_Controls[con_used]->y_size = GUGSpriteHeight(text) + 5;
            break;
         case GUG_DRAW_CONTROL:
            GUG_Controls[con_used]->x_size = x_size;
            GUG_Controls[con_used]->y_size = y_size;
            break;
    case GUG_HIDDEN_CONTROL:
            GUG_Controls[con_used]->x_size = x_size;
            GUG_Controls[con_used]->y_size = y_size;
            break;
  }

  GUG_Controls[con_used]->delay  = delay;
  GUG_Controls[con_used]->repeat = repeat;
  GUG_Controls[con_used]->event  = event;
  GUG_Controls[con_used]->text   = text;
  GUG_Controls[con_used]->color  = color;
  GUG_Controls[con_used]->type   = type;
  GUG_Controls[con_used]->group  = group;
  GUG_Controls[con_used]->state  = state;

  return(con_used);
}



//*********************************************************************
// Event Processor
//
int GUGProcessControls(struct GUG_cntrl *GUG_Controls[],
                       unsigned int *b,
                       unsigned int *x,
                       unsigned int *y) {

  int          in_a_control;
  int          e1,event,i,con_used;
  unsigned int mb,mdx1,mdy1,mdx2,mdy2,mux,muy;

  static int flag      =   1;   // redraw flag
  static int loop      =   0;
  static int last_code =  -1;   // last message code returned
  static int idelay;            // initial delay for spin
  static int repeat;            // repeat delay for spin

  // Force a redraw if *b is passed in as -1
  if (*b == -1) flag = 1;

  // give user time to release the button
  if ((loop == 0) && (last_code > 0)) {
         delay(120);
  }

  // Are we entering the loop with a mouse button down
  GUGMousePosition((unsigned int *)&mb,
                   (unsigned int *)&mdx1,
                   (unsigned int *)&mdy1);

  // No do the repeating button
  if ((mb == 1) && (last_code > 0)) {
    if (loop == 0) {  // first time in this pass
      GUGMouseHide();
      GUGVSync();
      GUGCopyToDisplay();
      GUGMouseShow();
      delay(idelay);
      loop++;
      GUGMousePosition((unsigned int *)&mb,
                       (unsigned int *)&mdx1,
                       (unsigned int *)&mdy1);
      if (mb == 1) { // button is still down
        return(last_code);  // return the last event
      }
    }
    else
    {
      GUGMouseHide();
      GUGVSync();
      GUGCopyToDisplay();
      GUGMouseShow();
      delay(repeat);  // repeat delay
      GUGMousePosition((unsigned int *)&mb,
                       (unsigned int *)&mdx1,
                       (unsigned int *)&mdy1);
      if (mb == 1) { // button is still down
        return(last_code);  // return the last event
      }
    }
  }

  // Find the ID of the last control
  for (con_used=0; con_used < 1024; ++con_used) {
    if (GUG_Controls[con_used] == NULL) {
      break;
    }
  }

  loop = 0;  // we are not in a repeating loop
  if (flag) {
    for (i=0; i<con_used; ++i) {
      switch (GUG_Controls[i]->type) {
        case GUG_SPRITE_SPIN:    GUG_draw_sprite_up(GUG_Controls[i]);
                                 break;
        case GUG_SPRITE_BUTTON:  GUG_draw_sprite_up(GUG_Controls[i]);
                                 break;
        case GUG_CONTROL_BUTTON: GUG_draw_control_up(GUG_Controls[i]);
                                 break;
        case GUG_RADIO_TEXT:     GUG_draw_radio_text(GUG_Controls[i]);
                                 break;
        case GUG_RADIO_SPRITE:   GUG_draw_radio_sprite(GUG_Controls[i]);
                                 break;
      }
    }
    GUGMouseHide();
    GUGCopyToDisplay();
    GUGMouseShow();
    flag = 0;
  }

  // Must click in a control BEFORE we continue
  in_a_control = 0;
  do {

     // Wait for a button down or a keyboard event
    do {
      GUGMousePosition((unsigned int *)&mb,
                       (unsigned int *)&mdx1,
                       (unsigned int *)&mdy1);
    }
    while ((mb != 1) && (!GUGKeyDown()));

    if (GUGKeyDown())
    {
      for (i=0; i<con_used; ++i)
      {
        if (GUG_Controls[i]->type == GUG_HOT_KEY)
        {
          if (GUG_key_table[GUG_Controls[i]->color] == KEY_IS_DOWN)
          {
            GUG_key_table[GUG_Controls[i]->color] = KEY_IS_UP;
            if (GUGKeyHit()) GUGGetKey();
            return(GUG_Controls[i]->event);
          }
        }
      }
      if (GUGKeyHit()) GUGGetKey();
    }
    else
    {
      e1 = -1;
      last_code = -1;
      for (i=0; i<con_used; ++i) {
        if ((mdx1 >= GUG_Controls[i]->x_pos) &&
            (mdx1 <= GUG_Controls[i]->x_pos + GUG_Controls[i]->x_size) &&
            (mdy1 >= GUG_Controls[i]->y_pos) &&
            (mdy1 <= GUG_Controls[i]->y_pos + GUG_Controls[i]->y_size)) {
        switch (GUG_Controls[i]->type) {
          case GUG_HIDDEN_CONTROL: in_a_control = 1;
                                   break;
          case GUG_SPRITE_BUTTON:  GUG_draw_sprite_dn(GUG_Controls[i]);
                                   in_a_control = 1;
                                   break;
          case GUG_CONTROL_BUTTON: GUG_draw_control_dn(GUG_Controls[i]);
                                   in_a_control = 1;
                                   break;
          case GUG_RADIO_TEXT:     GUG_handle_radio_text(GUG_Controls,i,con_used);
                                   in_a_control = 1;
                                   break;
          case GUG_RADIO_SPRITE:   GUG_handle_radio_sprite(GUG_Controls,i,con_used);
                                   in_a_control = 1;
                                   break;
          case GUG_SPRITE_SPIN:    GUG_draw_sprite_dn(GUG_Controls[i]);
                                   flag = 1;
                                   GUGMouseHide();
                                   GUGCopyToDisplay();
                                   GUGMouseShow();
                                   last_code = GUG_Controls[i]->event;
                                   idelay    = GUG_Controls[i]->delay;
                                   repeat    = GUG_Controls[i]->repeat;
                                   return(last_code);
                                   break;
          case GUG_DRAW_CONTROL:   *x = mdx1;   // returns on DOWN event
                                   *y = mdy1;
                                   *b = mb;
                                   last_code = GUG_Controls[i]->event;
                                   return(last_code);
                                   break;
          } // end of the switch
          mdx1   = GUG_Controls[i]->x_pos;
          mdy1   = GUG_Controls[i]->y_pos;
          mdx2   = mdx1 + GUG_Controls[i]->x_size;
          mdy2   = mdy1 + GUG_Controls[i]->y_size;
          e1     = GUG_Controls[i]->event;
          i      = con_used+1;
        }  // End of if
      }    // End of for
    }    // of not a key hit
  }
  while (!in_a_control);


  if (e1 == -1) return (-1);
  flag = 1;
  GUGMouseHide();
  GUGCopyToDisplay();
  GUGMouseShow();

  // Wait for Button Up
  do {
    GUGMousePosition((unsigned int *)&mb,
                     (unsigned int *)&mux,
                       (unsigned int *)&muy);
    // Return the button ID
    *b = mb;
  }
  while (mb != 0);

  // Return the X/Y location
  *x = mux;
  *y = muy;

  // Did we release on the same control
  if ((mux >= mdx1) &&
      (mux <= mdx2) &&
      (muy >= mdy1) &&
      (muy <= mdy2))
         event = e1; // Signal an button up event
  else
    event = -1; // Cancel Event

  return(event);
}


//**********************************************************************
// Draw Sprite Buttons
//
void GUG_draw_sprite_up(struct GUG_cntrl *c) {
  GUGFillRectangle(c->x_pos,c->y_pos,
                   c->x_pos+c->x_size,c->y_pos+c->y_size,
                   GUG_GREY_2);
  GUGRectangle(c->x_pos,c->y_pos,
               c->x_pos+c->x_size,c->y_pos+c->y_size,
               GUG_GREY_3);
  GUGHLine(c->x_pos+1,c->x_pos+c->x_size-1,c->y_pos+1,GUG_WHITE);
  GUGVLine(c->y_pos+1,c->y_pos+c->y_size-1,c->x_pos+1,GUG_WHITE);

  GUGHLine(c->x_pos+2,c->x_pos+c->x_size-1,
           c->y_pos+c->y_size-1,GUG_BLACK);
  GUGVLine(c->y_pos+2,c->y_pos+c->y_size-1,
           c->x_pos+c->x_size-1,GUG_BLACK);

  GUGPutFGSprite(c->x_pos+3,c->y_pos+3,c->text);
}

void GUG_draw_sprite_dn(struct GUG_cntrl *c) {
  GUGFillRectangle(c->x_pos,c->y_pos,
                   c->x_pos+c->x_size,c->y_pos+c->y_size,
                   GUG_GREY_2);
  GUGRectangle(c->x_pos,c->y_pos,
               c->x_pos+c->x_size,c->y_pos+c->y_size,
               GUG_GREY_3);
  GUGHLine(c->x_pos+1,c->x_pos+c->x_size-1,c->y_pos+1,GUG_BLACK);
  GUGVLine(c->y_pos+1,c->y_pos+c->y_size-1,c->x_pos+1,GUG_BLACK);

  GUGHLine(c->x_pos+2,c->x_pos+c->x_size-1,
           c->y_pos+c->y_size-1,GUG_WHITE);
  GUGVLine(c->y_pos+2,c->y_pos+c->y_size-1,
           c->x_pos+c->x_size-1,GUG_WHITE);

    GUGPutFGSprite(c->x_pos+3+OFFSET,c->y_pos+3+OFFSET,c->text);
}

//**********************************************************************
// Draw Control Buttons
//
void GUG_draw_control_up(struct GUG_cntrl *c) {
  GUGFillRectangle(c->x_pos,c->y_pos,
                   c->x_pos+c->x_size,c->y_pos+c->y_size,
                   GUG_GREY_2);
  GUGRectangle(c->x_pos,c->y_pos,
               c->x_pos+c->x_size,c->y_pos+c->y_size,
               GUG_GREY_3);
  GUGHLine(c->x_pos+1,c->x_pos+c->x_size-1,c->y_pos+1,GUG_WHITE);
  GUGVLine(c->y_pos+1,c->y_pos+c->y_size-1,c->x_pos+1,GUG_WHITE);

  GUGHLine(c->x_pos+2,c->x_pos+c->x_size-1,
           c->y_pos+c->y_size-1,GUG_BLACK);
  GUGVLine(c->y_pos+2,c->y_pos+c->y_size-1,
           c->x_pos+c->x_size-1,GUG_BLACK);

  GUGPutText(c->x_pos+5,c->y_pos+4,c->color,c->text);
}

void GUG_draw_control_dn(struct GUG_cntrl *c) {
  GUGFillRectangle(c->x_pos,c->y_pos,
                   c->x_pos+c->x_size,c->y_pos+c->y_size,
                   GUG_GREY_2);
  GUGRectangle(c->x_pos,c->y_pos,
               c->x_pos+c->x_size,c->y_pos+c->y_size,
               GUG_GREY_3);
  GUGHLine(c->x_pos+1,c->x_pos+c->x_size-1,c->y_pos+1,GUG_BLACK);
  GUGVLine(c->y_pos+1,c->y_pos+c->y_size-1,c->x_pos+1,GUG_BLACK);

  GUGHLine(c->x_pos+2,c->x_pos+c->x_size-1,
           c->y_pos+c->y_size-1,GUG_WHITE);
  GUGVLine(c->y_pos+2,c->y_pos+c->y_size-1,
           c->x_pos+c->x_size-1,GUG_WHITE);

  GUGPutText(c->x_pos+5+OFFSET,
             c->y_pos+4+OFFSET,c->color,c->text);
}

//**********************************************************************
// Handle Radio Text Buttons
//
void GUG_handle_radio_text(struct GUG_cntrl *GUG_Controls[],
                           int i, int con_used) {

  int group;
  int j,k;

  group = GUG_Controls[i]->group;

  if (group == -1)
  {
    GUG_Controls[i]->state = !GUG_Controls[i]->state;
    GUG_draw_radio_text(GUG_Controls[i]);
    return;
  }

  for (j=0; j<con_used; ++j) {
         if ((GUG_Controls[j]->type  == GUG_RADIO_TEXT) &&
        (GUG_Controls[j]->group == group)) {
      if (j == i)
        GUG_Controls[j]->state = GUG_SELECTED;
      else
        GUG_Controls[j]->state = GUG_UNSELECTED;
      GUG_draw_radio_text(GUG_Controls[i]);
    }
  }
}

void GUG_draw_radio_text(struct GUG_cntrl *c) {
  GUGFillRectangle(c->x_pos,c->y_pos,
                   c->x_pos+c->x_size,c->y_pos+c->y_size,
                   GUG_GREY_2);
  GUGRectangle(c->x_pos,c->y_pos,
               c->x_pos+c->x_size,c->y_pos+c->y_size,
               GUG_GREY_3);

  if (c->state == GUG_SELECTED)
    GUGFillRectangle(c->x_pos+2,c->y_pos+2,
                     c->x_pos+6,c->y_pos+7,
                   GUG_GREY_3);
  else
    GUGRectangle(c->x_pos+2,c->y_pos+2,
                 c->x_pos+6,c->y_pos+7,
                 GUG_GREY_3);

  GUGPutText(c->x_pos+8,c->y_pos+2,c->color,c->text);
}

int GUGGetRadioStatus(int handle,struct GUG_cntrl *GUG_Controls[]) {
  return(GUG_Controls[handle]->state);
}

//**********************************************************************
// Handle Radio Sprite Buttons
//
void GUG_handle_radio_sprite(struct GUG_cntrl *GUG_Controls[],
                             int i, int con_used) {
  int group;
  int j,k;

  group = GUG_Controls[i]->group;

  for (j=0; j<con_used; ++j) {
         if ((GUG_Controls[j]->type  == GUG_RADIO_SPRITE) &&
                  (GUG_Controls[j]->group == group)) {
      if (j == i)
        GUG_Controls[j]->state = GUG_SELECTED;
      else
        GUG_Controls[j]->state = GUG_UNSELECTED;
      GUG_draw_radio_sprite(GUG_Controls[i]);
         }
  }
}

void GUG_draw_radio_sprite(struct GUG_cntrl *c) {
  if (c->state == GUG_SELECTED)
         GUG_draw_sprite_dn(c);
  else
    GUG_draw_sprite_up(c);
}

//************************************************************************
// Message Box
//
#define MAX_MB   3
#define MAX_TX   5
#define TEXT_MB 30
#define BUTT_MB 10

#define GUG_CONTROL_BUTTON 1
#define GUGRegControlText(x,y,u,t,c,cs)    GUG_reg_control(cs,x,y,-1,-1,u,t, c,GUG_CONTROL_BUTTON,-1,-1,-1,-1);

int GUGMessageBox(char *mt, char *bt) {

  struct GUG_cntrl *mb_controls[MAX_MB];
  char message[MAX_TX][80];
  char button[MAX_MB][80];
  char *buffer;

  int y,x,ml,bl,p;
  int event;
  unsigned int mb,mx,my;

  buffer = malloc(64000);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  // Intialize the controls
  GUGInitControl(mb_controls,MAX_MB);

  for (x=0; x<MAX_TX; ++x) {
    message[x][0] = '\0';
  }
  for (x=0; x<MAX_MB; ++x) {
    button[x][0] = '\0';
  }

  for (p=0,ml=0,x=0; x<strlen(mt); ++x) {
    if (mt[x] == '|') {
      ml++;
      p=0;
    }
    else if ((ml < MAX_TX) && (p < TEXT_MB)) {
      message[ml][p] = mt[x];
      p++;
      message[ml][p] = '\0';
    }
  }
  for (x=0; x<MAX_TX; ++x) {
    message[x][30] = '\0';
  }

  for (p=0,bl=0,x=0; x<strlen(bt); ++x) {
    if (bt[x] == '|') {
      bl++;
      p=0;
    }
    else if ((bl < MAX_MB) && (p < BUTT_MB)) {
      button[bl][p] = bt[x];
      p++;
      button[bl][p] = '\0';
    }
  }
  for (x=0; x<MAX_MB; ++x) {
    button[x][10] = '\0';
  }

  if (ml > (MAX_TX-1))
    ml = (MAX_TX-1);
  if (bl > (MAX_MB-1))
    bl = (MAX_MB-1);

  if (bl == 0) {
    y = GUGTextWidth(button[0]);
    y = y + 6;
    y = y / 2;
    y++;
    GUGRegControlText(160-y,130,0,button[0],GUG_B_BLUE,mb_controls);
  }

  if (bl == 1) {
    y = GUGTextWidth(button[0]);
    y = y + 6;
    y = y / 2;
    y++;
    GUGRegControlText( 80-y,130,0,button[0],GUG_B_BLUE,mb_controls);
    GUGRegControlText(240-y,130,1,button[1],GUG_B_BLUE,mb_controls);
   }

  if (bl == 2) {
    y = GUGTextWidth(button[0]);
    y = y + 6;
    y = y / 2;
    y++;
    GUGRegControlText( 70-y,130,0,button[0],GUG_B_BLUE,mb_controls);
    GUGRegControlText(160-y,130,1,button[1],GUG_B_BLUE,mb_controls);
    GUGRegControlText(250-y,130,2,button[2],GUG_B_BLUE,mb_controls);
  }

  GUGFillRectangle(20,50,300,150,0x81);
  GUGRectangle(22,52,298,148,GUG_BLACK);
  GUGRectangle(23,53,297,147,GUG_WHITE);
  for (x=0; x<=ml; ++x) {
    y = GUGTextWidth(message[x]);
    y = y / 2;
    GUGPutText(160-y,65+(x*10),GUG_B_BLUE,message[x]);
  }

  do {
    event = GUGProcessControls(mb_controls,
                               (unsigned int *)&mb,
                               (unsigned int *)&mx,
                               (unsigned int *)&my);
  }
  while (event == -1);

  for (x=0; x<MAX_MB; ++x) {
    if (mb_controls[x] != NULL)
      free(mb_controls[x]);
  }

  GUGCopyToBuffer(buffer);
  GUGMouseHide();
  GUGCopyToDisplay();
  GUGMouseShow();
  free(buffer);
  return(event);

}

//************************************************************************
// Message Box
//
#define MAX_MB   3
#define MAX_TX   5
#define TEXT_MB 30
#define BUTT_MB 10

#define GUG_CONTROL_BUTTON 1
#define GUGRegControlText(x,y,u,t,c,cs)    GUG_reg_control(cs,x,y,-1,-1,u,t, c,GUG_CONTROL_BUTTON,-1,-1,-1,-1);

int GUGPCXMessageBox(char *mt, char *bt, GUG_PCX *pcx) {

  struct GUG_cntrl *mb_controls[MAX_MB];
  char message[MAX_TX][80];
  char button[MAX_MB][80];
  char *buffer;

  int y,x,ml,bl,p;
  int event;
  unsigned int mb,mx,my;

  buffer = malloc(64000);
  GUGCopyToDisplay();
  GUGSaveDisplay(buffer);

  // Intialize the controls
  GUGInitControl(mb_controls,MAX_MB);

  for (x=0; x<MAX_TX; ++x) {
    message[x][0] = '\0';
  }
  for (x=0; x<MAX_MB; ++x) {
    button[x][0] = '\0';
  }

  for (p=0,ml=0,x=0; x<strlen(mt); ++x) {
    if (mt[x] == '|') {
      ml++;
      p=0;
    }
    else if ((ml < MAX_TX) && (p < TEXT_MB)) {
      message[ml][p] = mt[x];
      p++;
      message[ml][p] = '\0';
    }
  }
  for (x=0; x<MAX_TX; ++x) {
    message[x][30] = '\0';
  }

  for (p=0,bl=0,x=0; x<strlen(bt); ++x) {
    if (bt[x] == '|') {
      bl++;
      p=0;
    }
    else if ((bl < MAX_MB) && (p < BUTT_MB)) {
      button[bl][p] = bt[x];
      p++;
      button[bl][p] = '\0';
    }
  }
  for (x=0; x<MAX_MB; ++x) {
    button[x][10] = '\0';
  }

  if (ml > (MAX_TX-1))
    ml = (MAX_TX-1);
  if (bl > (MAX_MB-1))
    bl = (MAX_MB-1);

  if (bl == 0) {
    y = GUGTextWidth(button[0]);
    y = y + 6;
    y = y / 2;
    y++;
    GUGRegControlText(230-y,140,0,button[0],GUG_B_BLUE,mb_controls);
  }

  if (bl == 1) {
    y = GUGTextWidth(button[0]);
    y = y + 6;
    y = y / 2;
    y++;
    GUGRegControlText(110-y,140,0,button[0],GUG_B_BLUE,mb_controls);
    GUGRegControlText(210-y,140,1,button[1],GUG_B_BLUE,mb_controls);
   }

  if (bl == 2) {
    y = GUGTextWidth(button[0]);
    y = y + 6;
    y = y / 2;
    y++;
    GUGRegControlText(180-y,140,0,button[0],GUG_B_BLUE,mb_controls);
    GUGRegControlText(230-y,140,1,button[1],GUG_B_BLUE,mb_controls);
    GUGRegControlText(280-y,140,2,button[2],GUG_B_BLUE,mb_controls);
  }

 GUGFillRectangle(10,40,310,160,0x81);
  GUGRectangle(12,42,308,158,GUG_BLACK);
  GUGRectangle(13,43,307,157,GUG_WHITE);

  if (pcx != NULL)
    GUGPutFGPCX(20,50,pcx);

  for (x=0; x<=ml; ++x) {
    y = GUGTextWidth(message[x]);
    y = y / 2;
    GUGPutText(230-y,65+(x*10),GUG_B_BLUE,message[x]);
  }

  do {
    event = GUGProcessControls(mb_controls,
                               (unsigned int *)&mb,
                               (unsigned int *)&mx,
                               (unsigned int *)&my);
  }
  while (event == -1);

  for (x=0; x<MAX_MB; ++x) {
    if (mb_controls[x] != NULL)
      free(mb_controls[x]);
  }

  GUGCopyToBuffer(buffer);
  GUGMouseHide();
  GUGCopyToDisplay();
  GUGMouseShow();
  free(buffer);
  return(event);

}

