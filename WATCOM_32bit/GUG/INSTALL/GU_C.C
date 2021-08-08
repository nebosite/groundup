// Compiled Sprites output from spr2asm
//  command line : spr2asm gu gu.spr 
//  entry point name : gu
//  asm output file  : gu_A.ASM
//  c   output file  : gu_C.C
//  h   output file  : gu_C.H
//  spr input  file  : gu.spr

typedef void (*GUG_CSprFunc) (char *where);  // Function Pointer Type

extern void gu_0(char *where);  // Sprite 0


static GUG_CSprFunc gu[] = {
  gu_0
};


int gu_height[] = {
  76 };

int gu_width[] = {
  77 };

void draw_gu(int who, int x, int y) {
  extern char *VGA_START;
  char *where;

  // make sure it's a valid sprite
  if (who > 0) return;

  // Clip the x coordinate
  if (x > 319) return;
  if (x < (0-gu_width[who])) return;

  // Clip the y coordinate
  if (y > 199) return;
  if (y < (0-gu_height[who])) return;

  // Write sprite starting at
  where = VGA_START + (y * 640) + x;

  // call the sprite
  gu[who](where);
}

