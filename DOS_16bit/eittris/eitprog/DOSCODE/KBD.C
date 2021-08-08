/*****************************************************************************
** Ground Up Keyboard handler
**   Original Code          - Neil B. Breeden II
**   Extensive Updates      - Eric Jorgensen May,1995
**   Ported to Watcom DOS4G - Neil B. Breeden II Jun 19,1995
*/

#include <stdio.h>
#include <alloc.h>
#include <dos.h>
#include <ctype.h>
#include "kbd.h"

#define KEYBOARD_INT 0x09		// keyboard interrput vector
#define KEY_BUFFER	0x60		// keybaord buffer area
#define KEY_CONTROL	0x61		// keyboard control register
#define INT_CONTROL	0x20		// interrupt control register

#define KEYSTACKDEPTH 127

void interrupt _saveregs new_kbd_int();

//**************************************************************************
//keyboard handling functions


//globals
unsigned char raw_key;				   	// global raw keyboard data aquired from the Isr
unsigned char key_table[128];		 	// key state table for arrow keys
char key_stack[KEYSTACKDEPTH];
char scankey_stack[KEYSTACKDEPTH];
int key_stackspot         = -1;
int scankey_stackspot     = -1;
unsigned char scantrigger =  0;
int aproposkeys = 0;
char aproposscanlist[127];

char *scancodename[159] = {        // Scancode name strings

	 "NULL",
	 "Esc",
	 "1","2","3","4","5","6","7","8","9","0","-","=",
	 "Backspace",
	 "TAB",
	 "q","w","e","r","t","y","u","i","o","p","[","]",
	 "Enter",
	 "Left Ctrl",
   "a","s","d","f","g","h","j","k","l",";","'","`",
   "Left Shift",
   "\\","z","x","c","v","b","n","m",",",".","/",
   "Right Shift",
   "Keypad *",
   "Left Alt",
   "Spacebar",
   "Caps lock",
   "F1","F2","F3","F4","F5","F6","F7","F8","F9","F10",
   "Num Lock",
   "Scroll lock",
   "KeyPad 7","KeyPad 8","KeyPad 9","KeyPad -","KeyPad 4","KeyPad 5",
	 "KeyPad 6","KeyPad +","KeyPad 1","KeyPad 2","KeyPad 3",
   "KeyPad Insert",
	 "KeyPad Delete",
   "???","???","???",
	 "F11","F12",
	 "???","???","???","???",
   "???","???","???",
                                   //  The following are extended codes
                                   //  with remappings unique to this
                                   //  library.
   "Right alt",
   "Right Ctrl",
   "Arrow Up",
   "Arrow left",
   "Arrow Right",
   "Arrow Down",
   "Insert",
   "Home",
   "Page Up",
   "Delete",
   "End",
   "Page Down",
   "Print Screen",
   "Keypad /",
   "Keypad enter",
	 "???","???","???","???","???","???","???","???",
	 "???","???","???","???","???","???","???","???"
	 "???","???","???","???","???","???","???","???",
	 "???","???","???","???","???","???","???","???"
	 "???","???","???","???","???","???","???","???",
	 "???","???","???","???","???","???","???","???"
	};

char key_lower_array[127] = {        /// Key translation arrays

	 0,                   // NULL
	 1,                   // ESC
	 '1','2','3','4','5','6','7','8','9','0','-','=',
	 8,                   // Backsace
	 0,                   // TAB
	 'q','w','e','r','t','y','u','i','o','p','[',']',
	 13,                  // ENTER
	 0,                   // CNTRL
   'a','s','d','f','g','h','j','k','l',';','\'','`',
   0,										// Left SHIFT
   '\\','z','x','c','v','b','n','m',',','.','/',
   0,										// right SHIFT
   0,										// Print Screen
   0,										// ALT
   ' ',
   0,                   // Caps lock
   0,0,0,0,0,0,0,0,0,0, // Function keys
   0,                   // Num lock
   0,                   // Scroll lock
   '7','8','9','-','4','5','6','+','1','2','3',
   0,                   // Insert
	 0,                   // Delete
   0,0,0,0,0,0,0,0,0,0, // The rest are undefined
	 0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0};

char key_upper_array[127] = {        /// Key translation arrays

	 0,                   // NULL
	 1,                   // ESC
	 '!','@','#','$','%','^','&','*','(',')','_','+',
	 8,                   // Backsace
	 0,                   // TAB
	 'Q','W','E','R','T','Y','U','I','O','P','{','}',
	 13,                  // ENTER
	 0,                   // CNTRL
   'A','S','D','F','G','H','J','K','L',':','\"','~',
   0,										// Left SHIFT
   '|','Z','X','C','V','B','N','M','<','>','?',
   0,										// right SHIFT
   0,										// Print Screen
   0,										// ALT
   ' ',
   0,                   // Caps lock
   0,0,0,0,0,0,0,0,0,0, // Function keys
   0,                   // Num lock
   0,                   // Scroll lock
   '7','8','9','-','4','5','6','+','1','2','3',
   0,                   // Insert
	 0,                   // Delete
   0,0,0,0,0,0,0,0,0,0, // The rest are undefined
	 0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0};

//holder for old keyboard interrupt handler
void interrupt far _saveregs (*old_key_isr)() = NULL;



/**************************************************************************
	void startkeyboard(void)
	void stopkeyboard(void)

  DESCRIPTION:  Functions to setup and deinstall our keyboard interrupt

**************************************************************************/
void startkeyboard(void)
{
	_disable();
  old_key_isr = _dos_getvect(KEYBOARD_INT);  	// get a ptr to the old Isr
  _dos_setvect(KEYBOARD_INT, new_kbd_int);		// install our Isr
  _enable();
  flushkey();
}

void stopkeyboard(void)
{
	if(old_key_isr) {
	  _disable();
    _dos_setvect(KEYBOARD_INT,old_key_isr);		// install our Isr
    _enable();
  }
}

/**************************************************************************
	void interrupt new_kbd_int()

  DESCRIPTION: This is a replacement function for the regular
							 keyboard interrupt.

  REMAPPINGS FOR 101/102 key keyboards

  Right alt							0x60
  Right Ctrl						0x61
  Arrow Up  						0x62
  Arrow left            0x63
  Arrow Right           0x64
  Arrow Down            0x65
  Insert   							0x66
  Home                  0x67
  Page Up               0x68
  Delete                0x69
  End                   0x6A
  Page Down             0x6B
  Print Screen          0x6C
  Keypad /              0x6D
  Keypad enter          0x6E

**************************************************************************/
void interrupt _saveregs new_kbd_int()
{
	unsigned char highbit;
  static rawbit = 0;
  char *keyarray;
  int i;
  //nsigned char twobits,resetbyte;

  //twobits = inp(0x61)&0x02;
  //resetbyte = 80+twobits;

  _asm {
		sti													// re-enable interrupts

		// get the key value and save it to the global buffer
		in		al,KEY_BUFFER					// get the key that was pressed
		xor	ah,ah										// zero upper 8 bits if ax
		mov	raw_key,al							// store it in the global raw_key

		// reset the KBD flip-flop to indicate the key has been read
		in		al,KEY_CONTROL			 	// set the control register
		or		al,0x80								// set the high bit to reset the FF
		out	KEY_CONTROL,al					// send the new data to the control register
		and	al,0x7F
		out	KEY_CONTROL,al					// complete the reset

		// reset the 8259 interrupt controller
		mov	al,0x20
		out	INT_CONTROL,al
	}



  if(raw_key == 0xE0) {         // E0 signals special keys on 101 keyboards
  	rawbit = 1;                 // Set a flag and go home
    return;
  }


  if(rawbit) {          // Special keycode?
    rawbit = 0;
    highbit = raw_key & 0x80;      // Capture high bit status

    switch(raw_key & 0x7f) {       // Remap special keys to unique indices
      case 0x2A:
      	return;                    // ignore the shift
    	case 0x38:                   //Right alt
      	raw_key =0x60 + highbit;
        break;
    	case 0x1D:                   //Right Ctrl
      	raw_key =0x61 + highbit;
        break;
    	case 0x48:                   //Arrow Up
      	raw_key =0x62 + highbit;
        break;
    	case 0x4B:                   //Arrow left
      	raw_key =0x63 + highbit;
        break;
    	case 0x4D:                   //Arrow Right
      	raw_key =0x64 + highbit;
        break;
    	case 0x50:                   //Arrow Down
      	raw_key =0x65 + highbit;
        break;
    	case 0x52:                   //Insert
      	raw_key =0x66 + highbit;
        break;
    	case 0x47:                   //Home
      	raw_key =0x67 + highbit;
        break;
    	case 0x49:                   //Page Up
      	raw_key =0x68 + highbit;
        break;
    	case 0x53:                   //Delete
      	raw_key =0x69 + highbit;
        break;
    	case 0x4F:                   //End
      	raw_key =0x6A + highbit;
        break;
    	case 0x51:                   //Page Down
      	raw_key =0x6B + highbit;
        break;
    	case 0x37:                   //Print Screen
      	raw_key =0x6C + highbit;
        break;
    	case 0x35:                   //Keypad /
      	raw_key =0x6D + highbit;
        break;
    	case 0x1C:                   //Keypad enter
      	raw_key =0x6E + highbit;
        break;
			default:		  // Unrecognized code- assign on the fly!
      		for(i = 0 ; i < aproposkeys; i++) {
          	if(aproposscanlist[i] == (raw_key & 0x7f)) break;
          }
          raw_key = 0x6F+i+highbit;
          if(i == aproposkeys) {
          	aproposscanlist[i] = raw_key & 0x7f;
            aproposkeys++;
          }
		}
  }


                                // update keypress table
  key_table[raw_key&0x7f] = (raw_key>>7) ^ 1;

                                // update the scan_code stack
  if(raw_key < 0x80 && scankey_stackspot < KEYSTACKDEPTH) {
    scankey_stackspot++;
    scankey_stack[scankey_stackspot] = raw_key;
  }
                                // update stack for key functions
  if(raw_key < 0x80 && key_stackspot < KEYSTACKDEPTH) {
                                // Check for shift key
    if(key_table[0x2A] || key_table[0x36]) keyarray = key_upper_array;
    else keyarray = key_lower_array;

    if(keyarray[raw_key]) {     // Is there a character there?
  		key_stackspot++;
  		key_stack[key_stackspot] = keyarray[raw_key];
                                // Check for control keys
      if((key_table[0x1D] || key_table[0x61]) &&
					isalpha(key_stack[key_stackspot]) )
				key_stack[key_stackspot] = toupper(key_stack[key_stackspot]) - 'A' +1;
    }
  }
}


/**************************************************************************
	void flushkey(void)

  DESCRIPTION: Clears the keyboard stack

**************************************************************************/
void flushkey(void)
{
	key_stackspot = -1;
  scankey_stackspot = -1;
}

/**************************************************************************
	int keyhit(void), scankeyhit(void)

  DESCRIPTION:  Returns TRUE if a keystroke is in the buffer

**************************************************************************/
int keyhit(void)
{
	if(key_stackspot > -1) return 1;
  else return 0;
}

int scankeyhit(void)
{
	if(scankey_stackspot > -1) return 1;
  else return 0;
}



/**************************************************************************
	unsigned char getscancode(void)

  DESCRIPTION:  Grabs the next scan code and returns it

**************************************************************************/
unsigned char getscancode(void)
{
	int i;
  char r;

  while(scankey_stackspot== -1);       // Wait for a keystroke in the buffer

  r = scankey_stack[0];                // grab the top keystroke.

                                       // shift the stack over
  for(i  =0; i < scankey_stackspot;i++) {
  	scankey_stack[i] = scankey_stack[i+1];
  }
  scankey_stackspot--;

  return(r);                           // Send our character back
}

/**************************************************************************
	char getkey(void)

  DESCRIPTION:  Grabs a keystroke from the stack.  If there is not one there,
                It waits.  (Works like getch();)

**************************************************************************/
char getkey(void)
{
	int i;
  char r;

 	while(key_stackspot== -1);       // Wait for a keystroke in the buffer

  r = key_stack[0];                // grab the top keystroke.

                                   // shift the stack over
  for(i  =0; i < key_stackspot;i++) {
  	key_stack[i] = key_stack[i+1];
  }
  key_stackspot--;

  return(r);                       // Send our character back
}


