// define specific stuff for VGA
#define SCREEN_AREA           0xa000
#define SCREEN_LINEAR_ADDRESS ((SCREEN_AREA) << 4)

extern char *VGA_MEMORY;    // Points to the 100K memory buffer
extern char *VGA_START;     // Points to the displayed part of VGA_MEMORY
extern char *VGA_POINTER;	// Points to the VGA Cards memory

extern int GUG_Font_Height;     // height of the font in pixels
extern int GUG_Font_Width;      // width of the font in pixels

extern char GUG_Old_Palette[];  // Holds the original palette
extern char GUG_666_Palette[];	// Holds the 666 palette

extern char font[];             // Copy of the GLYPH font

