#ifndef flilib_h
#define flilib_h

#define LINE_SKIP 0xc000

typedef struct fli_typ {
  unsigned short int     frames;
  unsigned short int     width;
  unsigned short int     height;
  unsigned short int     speed;
  unsigned short int     current;
  unsigned long          crntoff;
  unsigned short int     handle;
} fli, *GUG_fli_ptr;

/*	description of a fli structure
	Any of these variables can be used directly, by fliptr->variable
	where fliptr is the pointer returned by the load_fli function.
	To go to the first frame execute the following code:
		fliptr->current=0;
		fliptr->crntoff=(long)sizeof(fli);
	(this only works if all of the fli was loaded into the ram)

	The data can only be used if the fli was loaded with the FLI_RAM 
        or possibly the FLI_AUTO option.

	Handle is equal to 0 if all of the fli was loaded into the ram.

byte offset     size    name    meaning
0               2       frames  Number of frames in fly, a maximum of 4000
2               2       width   Screen width (320)
4               2       height  Screen height (200)
6               2       speed   Number of video ticks between frames
8               2       current Current frame (=0 initilly)
10              4       crntoff offset from begining to current frame (=14 initially)
14              2       handle  handle of the file if playing from disk
16              ?       data    data for the frames (only if handle>1)
*/

// an array of 256*3 bytes which represent the 256 rgb indexes
extern unsigned char *fli_pal;

// if set to 1, the color palette fli_pal is not used by the flic player
// if set to 0, the user has to use allocate fli_pal buffer
extern int fli_use_pal;

// FLI_RAM forces load_fli to play the entire flic from memory 
// FLI_DISK forces play from disk
// FLI_AUTO tries loading flic into memory, if it fails it plays from disk 
enum fli_source {FLI_RAM, FLI_DISK, FLI_AUTO};

// returns NULL if it didn't find the file or your out of memory
// the file can be either a fli or flc
GUG_fli_ptr GUGLoadFLI(char *filename, enum fli_source);

// plays a single frame and if it is the last frame, automatically
// sets the current and crntoff to the first frame
// dest is the memory buffer to play into, can be the screen of mode 0x13

short int GUGPlayFLIToDisplay(GUG_fli_ptr);
short int GUGPlayFLIToBuffer(GUG_fli_ptr);
short int GUGPlayFLI(GUG_fli_ptr,char *dest);

// closes the handle used if playing from DISK
// frees up all the memory used by the fli
void GUGCloseFLI(GUG_fli_ptr);

#endif //flilib_H
