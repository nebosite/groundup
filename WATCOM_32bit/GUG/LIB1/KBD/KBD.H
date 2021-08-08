//functions

int  GUGKeyHit(void);
int  GUGScanKeyHit(void);
char GUGGetKey(void);
void GUGStartKeyboard(void);
void GUGStopKeyboard(void);
void GUGFlushKey(void);
unsigned char GUGGetScanCode(void);


// globals
extern char GUG_key_lower_array[127];
extern char GUG_key_upper_array[127];
//extern unsigned char GUG_key_table[256]; // [128];                      // key state table
extern int GUGDebugNum;
extern char *GUGScanCodeName[127];           // Scancode name strings

