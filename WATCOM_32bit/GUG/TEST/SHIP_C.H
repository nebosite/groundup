// Compiled Sprites output from spr2asm
//  command line : spr2asm ship ship 
//  entry point name : ship
//  asm output file  : ship_A.ASM
//  c   output file  : ship_C.C
//  h   output file  : ship_C.H
//  spr input  file  : ship.SPR

#ifdef __cplusplus
extern "C" {
#endif

extern void draw_ship(int who, int x, int y);

extern int ship_height[];
extern int ship_width[];
#define MAX_SHIP_SPRITES 59

#ifdef __cplusplus
};
#endif

