
																		 // Hiscore display structure
typedef struct hiscore {
	char far *name;
	long int score;
	int rows;
	struct hiscore *next;

} HISCORE;


HISCORE far *newscore(char *name,long int score, int rows);
HISCORE far *readscores(void);
void freescore(HISCORE far *hs);
long int hihash(char *name, long int score, long int rows, int rnum);
int insertscore(HISCORE far **head,HISCORE far *hs);
void writescores(HISCORE *hs);

extern HISCORE far *scores;





