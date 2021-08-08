// Compiled Sprites output from spr2asm
//  command line : spr2asm sship sship.spr 
//  entry point name : sship
//  asm output file  : sship_A.ASM
//  c   output file  : sship_C.C
//  h   output file  : sship_C.H
//  spr input  file  : sship.spr

typedef void (*GUG_CSprFunc) (char *where);  // Function Pointer Type

extern void sship_0(char *where);  // Sprite 0


static GUG_CSprFunc sship[] = {
  sship_0
};


int sship_height[] = {
  74 };

int sship_width[] = {
  94 };

void draw_sship(int who, int x, int y) {
  extern char *VGA_START;
  char *where;

  // make sure it's a valid sprite
  if (who > 0) return;

  // Clip the x coordinate
  if (x > 319) return;
  if (x < (0-sship_width[who])) return;

  // Clip the y coordinate
  if (y > 199) return;
  if (y < (0-sship_height[who])) return;

  // Write sprite starting at
  where = VGA_START + (y * 640) + x;

  // call the sprite
  sship[who](where);
}

