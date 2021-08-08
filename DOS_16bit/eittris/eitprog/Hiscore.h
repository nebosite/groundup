// Varmint's EITTRIS
// Copyright (C) 1996-2000, Purple Planet Software


																		 // Hiscore display structure
																		 // Hiscore display structure
typedef struct hiscore {
	char  *name;
	LONG score;
	SHORT rows;
	struct hiscore *next;

} HISCORE;


HISCORE  *newscore(char *name,LONG score, SHORT rows);
HISCORE  *readscores(void);
void freescore(HISCORE  *hs);
LONG hihash(char *name, LONG score, LONG rows, SHORT rnum);
SHORT insertscore(HISCORE  **head,HISCORE  *hs);
void writescores(HISCORE *hs);

extern HISCORE  *scores;




