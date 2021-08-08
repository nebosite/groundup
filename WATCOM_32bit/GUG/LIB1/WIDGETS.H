//
// Various defines and function prototypes for the GUG widgets
//

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
#define GUG_NO_GROUP  -1

// The GUG Widget Control Struct
struct GUG_cntrl
{
  int  used;       // For GUG use only
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
  int  delay;      // Initial delay on spin buttons
  int  repeat;     // Delay between steps on spin buttons
};

// Hot Key Functions
#define GUGRegHotKey(e,c,cs)               GUG_reg_control(cs,-1,-1,-1,-1,e,"",c,GUG_HOT_KEY,-1,-1,-1,-1);

// Control Functions
#define GUGRegControlText(x,y,u,t,c,cs)    GUG_reg_control(cs,x,y,-1,-1,u,t, c,GUG_CONTROL_BUTTON,-1,-1,-1,-1);
#define GUGRegControlSprite(x,y,u,t,cs)    GUG_reg_control(cs,x,y,-1,-1,u,t,-1,GUG_SPRITE_BUTTON ,-1,-1,-1,-1);
#define GUGRegSpinSprite(x,y,u,t,d,r,cs)   GUG_reg_control(cs,x,y,-1,-1,u,t,-1,GUG_SPRITE_SPIN   ,-1,-1, d, r);

// Radio Functions
#define GUGRegRadioText(x,y,u,t,c,g,s,cs)  GUG_reg_control(cs,x,y,-1,-1,u,t, c,GUG_RADIO_TEXT  ,g,s,-1,-1);
#define GUGRegRadioSprite(x,y,u,t,g,s,cs)  GUG_reg_control(cs,x,y,-1,-1,u,t,-1,GUG_RADIO_SPRITE,g,s,-1,-1);

// Toggle Functions
#define GUGRegToggleText(x,y,u,t,c,s,cs)  GUG_reg_control(cs,x,y,-1,-1,u,t, c,GUG_RADIO_TEXT  ,-1,s,-1,-1);

// Other Functions
#define GUGRegDraw(x,y,xs,ys,u,cs)         GUG_reg_control(cs,x,y,xs,ys,u,"",-1,GUG_DRAW_CONTROL  ,-1,-1,-1,-1);
#define GUGRegHidden(x,y,xs,ys,u,cs)       GUG_reg_control(cs,x,y,xs,ys,u,"",-1,GUG_HIDDEN_CONTROL,-1,-1,-1,-1);

// Initialize the controls
extern void GUGInitControl(struct GUG_cntrl *GUG_Controls[],int MAX);

// Message Box's
extern int GUGMessageBox(char *messages, char *buttons);
extern int GUGPCXMessageBox(char *messages, char *buttons, GUG_PCX *pcx);


// Register the various controls
extern int GUG_reg_control(struct GUG_cntrl *GUG_Controls[],
                           int x_pos,
                           int y_pos,
                           int x_size,
                           int y_size,
                           int event,
                           char *text,
                           int  color,
                           int  type,
                           int  group,
                           int  state,
                           int  delay,
                           int  repeat);

// Using the registered controls return events
extern int GUGProcessControls(struct GUG_cntrl *GUG_Controls[],
                              unsigned int *b,
                              unsigned int *x,
                              unsigned int *y);

// Get Radio Button Status
extern int  GUGGetRadioStatus(int handle,struct GUG_cntrl *GUG_Controls[]);

