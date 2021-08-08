
//functions

int keyhit(void);
int scankeyhit(void);
char getkey(void);
void startkeyboard(void);
void stopkeyboard(void);
void flushkey(void);
unsigned char getscancode(void);


// globals
extern char key_lower_array[];
extern char key_upper_array[];
extern unsigned char key_table[];		 	// key state table
// extern int debugnum;
extern char *scancodename[];           // Scancode name strings

