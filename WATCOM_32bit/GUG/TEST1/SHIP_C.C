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

typedef void (*GUG_CSprFunc) (char *where);  // Function Pointer Type

extern void ship_0(char *where);  // Sprite 0
extern void ship_1(char *where);  // Sprite 1
extern void ship_2(char *where);  // Sprite 2
extern void ship_3(char *where);  // Sprite 3
extern void ship_4(char *where);  // Sprite 4
extern void ship_5(char *where);  // Sprite 5
extern void ship_6(char *where);  // Sprite 6
extern void ship_7(char *where);  // Sprite 7
extern void ship_8(char *where);  // Sprite 8
extern void ship_9(char *where);  // Sprite 9
extern void ship_10(char *where);  // Sprite 10
extern void ship_11(char *where);  // Sprite 11
extern void ship_12(char *where);  // Sprite 12
extern void ship_13(char *where);  // Sprite 13
extern void ship_14(char *where);  // Sprite 14
extern void ship_15(char *where);  // Sprite 15
extern void ship_16(char *where);  // Sprite 16
extern void ship_17(char *where);  // Sprite 17
extern void ship_18(char *where);  // Sprite 18
extern void ship_19(char *where);  // Sprite 19
extern void ship_20(char *where);  // Sprite 20
extern void ship_21(char *where);  // Sprite 21
extern void ship_22(char *where);  // Sprite 22
extern void ship_23(char *where);  // Sprite 23
extern void ship_24(char *where);  // Sprite 24
extern void ship_25(char *where);  // Sprite 25
extern void ship_26(char *where);  // Sprite 26
extern void ship_27(char *where);  // Sprite 27
extern void ship_28(char *where);  // Sprite 28
extern void ship_29(char *where);  // Sprite 29
extern void ship_30(char *where);  // Sprite 30
extern void ship_31(char *where);  // Sprite 31
extern void ship_32(char *where);  // Sprite 32
extern void ship_33(char *where);  // Sprite 33
extern void ship_34(char *where);  // Sprite 34
extern void ship_35(char *where);  // Sprite 35
extern void ship_36(char *where);  // Sprite 36
extern void ship_37(char *where);  // Sprite 37
extern void ship_38(char *where);  // Sprite 38
extern void ship_39(char *where);  // Sprite 39
extern void ship_40(char *where);  // Sprite 40
extern void ship_41(char *where);  // Sprite 41
extern void ship_42(char *where);  // Sprite 42
extern void ship_43(char *where);  // Sprite 43
extern void ship_44(char *where);  // Sprite 44
extern void ship_45(char *where);  // Sprite 45
extern void ship_46(char *where);  // Sprite 46
extern void ship_47(char *where);  // Sprite 47
extern void ship_48(char *where);  // Sprite 48
extern void ship_49(char *where);  // Sprite 49
extern void ship_50(char *where);  // Sprite 50
extern void ship_51(char *where);  // Sprite 51
extern void ship_52(char *where);  // Sprite 52
extern void ship_53(char *where);  // Sprite 53
extern void ship_54(char *where);  // Sprite 54
extern void ship_55(char *where);  // Sprite 55
extern void ship_56(char *where);  // Sprite 56
extern void ship_57(char *where);  // Sprite 57
extern void ship_58(char *where);  // Sprite 58
extern void ship_59(char *where);  // Sprite 59


static GUG_CSprFunc ship[] = {
  ship_0,
  ship_1,
  ship_2,
  ship_3,
  ship_4,
  ship_5,
  ship_6,
  ship_7,
  ship_8,
  ship_9,
  ship_10,
  ship_11,
  ship_12,
  ship_13,
  ship_14,
  ship_15,
  ship_16,
  ship_17,
  ship_18,
  ship_19,
  ship_20,
  ship_21,
  ship_22,
  ship_23,
  ship_24,
  ship_25,
  ship_26,
  ship_27,
  ship_28,
  ship_29,
  ship_30,
  ship_31,
  ship_32,
  ship_33,
  ship_34,
  ship_35,
  ship_36,
  ship_37,
  ship_38,
  ship_39,
  ship_40,
  ship_41,
  ship_42,
  ship_43,
  ship_44,
  ship_45,
  ship_46,
  ship_47,
  ship_48,
  ship_49,
  ship_50,
  ship_51,
  ship_52,
  ship_53,
  ship_54,
  ship_55,
  ship_56,
  ship_57,
  ship_58,
  ship_59
};


int ship_height[] = {
  25,
  25,
  24,
  24,
  24,
  24,
  24,
  24,
  24,
  25,
  24,
  25,
  25,
  25,
  26,
  26,
  26,
  26,
  25,
  25,
  24,
  25,
  24,
  24,
  24,
  24,
  23,
  23,
  23,
  23,
  23,
  23,
  23,
  24,
  23,
  24,
  24,
  24,
  24,
  24,
  24,
  24,
  23,
  23,
  23,
  22,
  21,
  21,
  22,
  23,
  23,
  24,
  24,
  24,
  25,
  25,
  25,
  25,
  25,
  25 };

int ship_width[] = {
  22,
  23,
  24,
  25,
  25,
  26,
  27,
  27,
  27,
  27,
  28,
  28,
  28,
  28,
  28,
  28,
  28,
  28,
  27,
  27,
  27,
  27,
  27,
  28,
  28,
  28,
  29,
  29,
  29,
  29,
  29,
  29,
  29,
  29,
  29,
  28,
  28,
  27,
  27,
  27,
  26,
  26,
  26,
  26,
  26,
  26,
  26,
  26,
  27,
  27,
  27,
  27,
  27,
  27,
  27,
  27,
  27,
  26,
  25,
  23 };

void draw_ship(int who, int x, int y) {
  extern char *VGA_START;
  char *where;

  // make sure it's a valid sprite
  if (who > 59) return;

  // Clip the x coordinate
  if (x > 319) return;
  if (x < (0-ship_width[who])) return;

  // Clip the y coordinate
  if (y > 199) return;
  if (y < (0-ship_height[who])) return;

  // Write sprite starting at
  where = VGA_START + (y * 640) + x;

  // call the sprite
  ship[who](where);
}

#ifdef __cplusplus
};
#endif

