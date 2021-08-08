// Header file for player structure
#define GRIDMEMSIZE 250

#define PHASE_NEW 0
#define PHASE_QUICK 1
#define PHASE_EXTENDED 2
#define PHASE_CONCENTRATION 3

typedef struct piece {
//	BYTE data[25];
	int bloc[4][8];
	BYTE rotation;
	BYTE type;
  BYTE visible;
} PIECE;

typedef struct think {
	BYTE grid[GRIDMEMSIZE];                     // Thinking space
	PIECE holdpiece;
	int exx,exy;                                // extended piece locations
	int phase;																	// Thinking phase
																							// 0 = New thought
																							// 1 = Finding Quick move
																							// 2 = Finding extended move
																							// 3 = Concentration

																							// Thought speed varaibles
	int ticksperturn;                           // ticks between turns
	int thinksperturn;                          // #thinks during turn
	int thinktick;                              // tick counter
	int turnthink;                              // think counter
	int rowscleared;													  // Number of rows cleared on
																							// this pick.

																							// Thinking bookmarks
	int gx,grot;
	int empties;

																							// Best move holders
	int bestmovex,bestmoverot,bestmovelow;
	int movespecial;
	double bestmovescore;
	double cscore;                                 // Score holderfor concentrating
	double cxscore;

} THINK;





typedef struct player {
	BYTE dummtdata[50];                       // Holders for whatever
	BYTE spot[GRIDMEMSIZE];                   // Main playing Grid
	int gridx,gridy,bw,bh;                    // Screen Coordinates
	int plaindraw;                            // Flag for ordinary-type tiles
	int background;                           // Background ID

																						// General Player info
	char name[20];
	int scoreblock[10];
	long int lastscore;
	int tainted;
	long int rows;
	long int tscore,trows;
	int wins;
																						// Keyboard Stuff
	int pkey[8];
	int storekey[8];
	int alive;
	int win;

																						// In-play data
	PIECE active,buffer;
  int px,py,count,countmaster,countrate;
	int special_probability;
  WORD special_lifetime;
  WORD special_counter;
  int fallstart;
	DWORD afflicted;
	int antedotes;
	WORD specialgrid[60];
	int timer[5];

  void (*gridanimation)(struct player *);
	int ganimdata[10];
  struct player *enemy;

																						// Computer player stuff
	THINK brain;
  char controltype;
  long int computer_counter;
	int computer_speed,computer_accuracy;
	int accstore,computer_smarts;
  int computer_translation;
  int computer_rotations;
  int computer_droptime;
	int computer_inposition;
	int computer_justhosed;
} PLAYER;
