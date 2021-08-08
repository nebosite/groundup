; Compiled Sprites output from spr2asm
;  command line : spr2asm o4x6 o4x6.spr 
;  entry point name : o4x6
;  asm output file  : o4x6_A.ASM
;  c   output file  : o4x6_C.C
;  spr input  file  : o4x6.spr
;
.386
DGROUP group _DATA
_DATA  segment 'DATA'
_DATA  ends
_TEXT  segment BYTE PUBLIC USE32 'CODE'
       ASSUME CS:_TEXT
       ASSUME DS:DGROUN

PUBLIC o4x6_0_
o4x6_0_ PROC
  mov BYTE  PTR eax+0x1,0x11;
  mov BYTE  PTR eax+0x281,0x11;
  mov BYTE  PTR eax+0x501,0x11;
  mov BYTE  PTR eax+0xa01,0x11;
  ret
o4x6_0_ ENDP

PUBLIC o4x6_1_
o4x6_1_ PROC
  mov BYTE  PTR eax+0x0,0x11;
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  ret
o4x6_1_ ENDP

PUBLIC o4x6_2_
o4x6_2_ PROC
  mov BYTE  PTR eax+0x0,0x11;
  mov BYTE  PTR eax+0x2,0x11;
  mov WORD  PTR eax+0x280,0x1111;
  mov BYTE  PTR eax+0x282,0x11;
  mov BYTE  PTR eax+0x500,0x11;
  mov BYTE  PTR eax+0x502,0x11;
  mov WORD  PTR eax+0x780,0x1111;
  mov BYTE  PTR eax+0x782,0x11;
  mov BYTE  PTR eax+0xa00,0x11;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_2_ ENDP

PUBLIC o4x6_3_
o4x6_3_ PROC
  mov BYTE  PTR eax+0x1,0x11;
  mov WORD  PTR eax+0x281,0x1111;
  mov WORD  PTR eax+0x500,0x1111;
  mov WORD  PTR eax+0x781,0x1111;
  mov WORD  PTR eax+0xa00,0x1111;
  mov BYTE  PTR eax+0xc81,0x11;
  ret
o4x6_3_ ENDP

PUBLIC o4x6_4_
o4x6_4_ PROC
  mov BYTE  PTR eax+0x0,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov BYTE  PTR eax+0x501,0x11;
  mov BYTE  PTR eax+0x780,0x11;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_4_ ENDP

PUBLIC o4x6_5_
o4x6_5_ PROC
  mov BYTE  PTR eax+0x1,0x11;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov WORD  PTR eax+0x501,0x1111;
  mov BYTE  PTR eax+0x780,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov WORD  PTR eax+0xa00,0x1111;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_5_ ENDP

PUBLIC o4x6_6_
o4x6_6_ PROC
  mov WORD  PTR eax+0x0,0x1111;
  mov BYTE  PTR eax+0x280,0x11;
  ret
o4x6_6_ ENDP

PUBLIC o4x6_7_
o4x6_7_ PROC
  mov BYTE  PTR eax+0x1,0x11;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x500,0x11;
  mov BYTE  PTR eax+0x780,0x11;
  mov BYTE  PTR eax+0xa01,0x11;
  ret
o4x6_7_ ENDP

PUBLIC o4x6_8_
o4x6_8_ PROC
  mov BYTE  PTR eax+0x0,0x11;
  mov BYTE  PTR eax+0x281,0x11;
  mov BYTE  PTR eax+0x501,0x11;
  mov BYTE  PTR eax+0x781,0x11;
  mov BYTE  PTR eax+0xa00,0x11;
  ret
o4x6_8_ ENDP

PUBLIC o4x6_9_
o4x6_9_ PROC
  mov BYTE  PTR eax+0x0,0x11;
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x281,0x11;
  mov WORD  PTR eax+0x500,0x1111;
  mov BYTE  PTR eax+0x502,0x11;
  mov BYTE  PTR eax+0x781,0x11;
  mov BYTE  PTR eax+0xa00,0x11;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_9_ ENDP

PUBLIC o4x6_10_
o4x6_10_ PROC
  mov BYTE  PTR eax+0x281,0x11;
  mov WORD  PTR eax+0x500,0x1111;
  mov BYTE  PTR eax+0x502,0x11;
  mov BYTE  PTR eax+0x781,0x11;
  ret
o4x6_10_ ENDP

PUBLIC o4x6_11_
o4x6_11_ PROC
  mov WORD  PTR eax+0xa00,0x1111;
  mov BYTE  PTR eax+0xc80,0x11;
  ret
o4x6_11_ ENDP

PUBLIC o4x6_12_
o4x6_12_ PROC
  mov WORD  PTR eax+0x500,0x1111;
  mov BYTE  PTR eax+0x502,0x11;
  ret
o4x6_12_ ENDP

PUBLIC o4x6_13_
o4x6_13_ PROC
  mov BYTE  PTR eax+0xa01,0x11;
  ret
o4x6_13_ ENDP

PUBLIC o4x6_14_
o4x6_14_ PROC
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov BYTE  PTR eax+0x501,0x11;
  mov BYTE  PTR eax+0x780,0x11;
  mov BYTE  PTR eax+0xa00,0x11;
  ret
o4x6_14_ ENDP

PUBLIC o4x6_15_
o4x6_15_ PROC
  mov WORD  PTR eax+0x1,0x1111;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov BYTE  PTR eax+0x500,0x11;
  mov BYTE  PTR eax+0x502,0x11;
  mov BYTE  PTR eax+0x780,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov WORD  PTR eax+0xa00,0x1111;
  ret
o4x6_15_ ENDP

PUBLIC o4x6_16_
o4x6_16_ PROC
  mov BYTE  PTR eax+0x1,0x11;
  mov WORD  PTR eax+0x280,0x1111;
  mov BYTE  PTR eax+0x501,0x11;
  mov BYTE  PTR eax+0x781,0x11;
  mov WORD  PTR eax+0xa00,0x1111;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_16_ ENDP

PUBLIC o4x6_17_
o4x6_17_ PROC
  mov WORD  PTR eax+0x0,0x1111;
  mov BYTE  PTR eax+0x282,0x11;
  mov BYTE  PTR eax+0x501,0x11;
  mov BYTE  PTR eax+0x780,0x11;
  mov WORD  PTR eax+0xa00,0x1111;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_17_ ENDP

PUBLIC o4x6_18_
o4x6_18_ PROC
  mov WORD  PTR eax+0x0,0x1111;
  mov BYTE  PTR eax+0x282,0x11;
  mov BYTE  PTR eax+0x501,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov WORD  PTR eax+0xa00,0x1111;
  ret
o4x6_18_ ENDP

PUBLIC o4x6_19_
o4x6_19_ PROC
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov WORD  PTR eax+0x500,0x1111;
  mov BYTE  PTR eax+0x502,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_19_ ENDP

PUBLIC o4x6_20_
o4x6_20_ PROC
  mov WORD  PTR eax+0x0,0x1111;
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x280,0x11;
  mov WORD  PTR eax+0x500,0x1111;
  mov BYTE  PTR eax+0x782,0x11;
  mov WORD  PTR eax+0xa00,0x1111;
  ret
o4x6_20_ ENDP

PUBLIC o4x6_21_
o4x6_21_ PROC
  mov BYTE  PTR eax+0x1,0x11;
  mov BYTE  PTR eax+0x280,0x11;
  mov WORD  PTR eax+0x500,0x1111;
  mov BYTE  PTR eax+0x780,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov BYTE  PTR eax+0xa01,0x11;
  ret
o4x6_21_ ENDP

PUBLIC o4x6_22_
o4x6_22_ PROC
  mov WORD  PTR eax+0x0,0x1111;
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov WORD  PTR eax+0x501,0x1111;
  mov BYTE  PTR eax+0x781,0x11;
  mov BYTE  PTR eax+0xa01,0x11;
  ret
o4x6_22_ ENDP

PUBLIC o4x6_23_
o4x6_23_ PROC
  mov BYTE  PTR eax+0x1,0x11;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov BYTE  PTR eax+0x501,0x11;
  mov BYTE  PTR eax+0x780,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov BYTE  PTR eax+0xa01,0x11;
  ret
o4x6_23_ ENDP

PUBLIC o4x6_24_
o4x6_24_ PROC
  mov BYTE  PTR eax+0x1,0x11;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov WORD  PTR eax+0x501,0x1111;
  mov BYTE  PTR eax+0x782,0x11;
  mov BYTE  PTR eax+0xa01,0x11;
  ret
o4x6_24_ ENDP

PUBLIC o4x6_25_
o4x6_25_ PROC
  mov BYTE  PTR eax+0x501,0x11;
  mov BYTE  PTR eax+0xa01,0x11;
  ret
o4x6_25_ ENDP

PUBLIC o4x6_26_
o4x6_26_ PROC
  mov BYTE  PTR eax+0x501,0x11;
  mov WORD  PTR eax+0xa00,0x1111;
  mov BYTE  PTR eax+0xc80,0x11;
  ret
o4x6_26_ ENDP

PUBLIC o4x6_27_
o4x6_27_ PROC
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x281,0x11;
  mov BYTE  PTR eax+0x500,0x11;
  mov BYTE  PTR eax+0x781,0x11;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_27_ ENDP

PUBLIC o4x6_28_
o4x6_28_ PROC
  mov WORD  PTR eax+0x500,0x1111;
  mov BYTE  PTR eax+0x502,0x11;
  mov WORD  PTR eax+0xa00,0x1111;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_28_ ENDP

PUBLIC o4x6_29_
o4x6_29_ PROC
  mov BYTE  PTR eax+0x0,0x11;
  mov BYTE  PTR eax+0x281,0x11;
  mov BYTE  PTR eax+0x502,0x11;
  mov BYTE  PTR eax+0x781,0x11;
  mov BYTE  PTR eax+0xa00,0x11;
  ret
o4x6_29_ ENDP

PUBLIC o4x6_30_
o4x6_30_ PROC
  mov WORD  PTR eax+0x0,0x1111;
  mov BYTE  PTR eax+0x282,0x11;
  mov BYTE  PTR eax+0x501,0x11;
  mov BYTE  PTR eax+0xa01,0x11;
  ret
o4x6_30_ ENDP

PUBLIC o4x6_31_
o4x6_31_ PROC
  mov WORD  PTR eax+0x0,0x1111;
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov BYTE  PTR eax+0x500,0x11;
  mov BYTE  PTR eax+0x502,0x11;
  mov BYTE  PTR eax+0x780,0x11;
  mov WORD  PTR eax+0xa00,0x1111;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_31_ ENDP

PUBLIC o4x6_32_
o4x6_32_ PROC
  mov BYTE  PTR eax+0x1,0x11;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov WORD  PTR eax+0x500,0x1111;
  mov BYTE  PTR eax+0x502,0x11;
  mov BYTE  PTR eax+0x780,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov BYTE  PTR eax+0xa00,0x11;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_32_ ENDP

PUBLIC o4x6_33_
o4x6_33_ PROC
  mov WORD  PTR eax+0x0,0x1111;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov WORD  PTR eax+0x500,0x1111;
  mov BYTE  PTR eax+0x780,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov WORD  PTR eax+0xa00,0x1111;
  ret
o4x6_33_ ENDP

PUBLIC o4x6_34_
o4x6_34_ PROC
  mov WORD  PTR eax+0x1,0x1111;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x500,0x11;
  mov BYTE  PTR eax+0x780,0x11;
  mov WORD  PTR eax+0xa01,0x1111;
  ret
o4x6_34_ ENDP

PUBLIC o4x6_35_
o4x6_35_ PROC
  mov WORD  PTR eax+0x0,0x1111;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov BYTE  PTR eax+0x500,0x11;
  mov BYTE  PTR eax+0x502,0x11;
  mov BYTE  PTR eax+0x780,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov WORD  PTR eax+0xa00,0x1111;
  ret
o4x6_35_ ENDP

PUBLIC o4x6_36_
o4x6_36_ PROC
  mov WORD  PTR eax+0x0,0x1111;
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x280,0x11;
  mov WORD  PTR eax+0x500,0x1111;
  mov BYTE  PTR eax+0x780,0x11;
  mov WORD  PTR eax+0xa00,0x1111;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_36_ ENDP

PUBLIC o4x6_37_
o4x6_37_ PROC
  mov WORD  PTR eax+0x0,0x1111;
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x280,0x11;
  mov WORD  PTR eax+0x500,0x1111;
  mov BYTE  PTR eax+0x780,0x11;
  mov BYTE  PTR eax+0xa00,0x11;
  ret
o4x6_37_ ENDP

PUBLIC o4x6_38_
o4x6_38_ PROC
  mov WORD  PTR eax+0x1,0x1111;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x500,0x11;
  mov BYTE  PTR eax+0x502,0x11;
  mov BYTE  PTR eax+0x780,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov WORD  PTR eax+0xa01,0x1111;
  ret
o4x6_38_ ENDP

PUBLIC o4x6_39_
o4x6_39_ PROC
  mov BYTE  PTR eax+0x0,0x11;
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov WORD  PTR eax+0x500,0x1111;
  mov BYTE  PTR eax+0x502,0x11;
  mov BYTE  PTR eax+0x780,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov BYTE  PTR eax+0xa00,0x11;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_39_ ENDP

PUBLIC o4x6_40_
o4x6_40_ PROC
  mov WORD  PTR eax+0x0,0x1111;
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x281,0x11;
  mov BYTE  PTR eax+0x501,0x11;
  mov BYTE  PTR eax+0x781,0x11;
  mov WORD  PTR eax+0xa00,0x1111;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_40_ ENDP

PUBLIC o4x6_41_
o4x6_41_ PROC
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov BYTE  PTR eax+0x502,0x11;
  mov BYTE  PTR eax+0x780,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov BYTE  PTR eax+0xa01,0x11;
  ret
o4x6_41_ ENDP

PUBLIC o4x6_42_
o4x6_42_ PROC
  mov BYTE  PTR eax+0x0,0x11;
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov WORD  PTR eax+0x500,0x1111;
  mov BYTE  PTR eax+0x780,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov BYTE  PTR eax+0xa00,0x11;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_42_ ENDP

PUBLIC o4x6_43_
o4x6_43_ PROC
  mov BYTE  PTR eax+0x0,0x11;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x500,0x11;
  mov BYTE  PTR eax+0x780,0x11;
  mov WORD  PTR eax+0xa00,0x1111;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_43_ ENDP

PUBLIC o4x6_44_
o4x6_44_ PROC
  mov BYTE  PTR eax+0x0,0x11;
  mov BYTE  PTR eax+0x2,0x11;
  mov WORD  PTR eax+0x280,0x1111;
  mov BYTE  PTR eax+0x282,0x11;
  mov WORD  PTR eax+0x500,0x1111;
  mov BYTE  PTR eax+0x502,0x11;
  mov BYTE  PTR eax+0x780,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov BYTE  PTR eax+0xa00,0x11;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_44_ ENDP

PUBLIC o4x6_45_
o4x6_45_ PROC
  mov BYTE  PTR eax+0x0,0x11;
  mov BYTE  PTR eax+0x2,0x11;
  mov WORD  PTR eax+0x280,0x1111;
  mov BYTE  PTR eax+0x282,0x11;
  mov BYTE  PTR eax+0x500,0x11;
  mov BYTE  PTR eax+0x502,0x11;
  mov BYTE  PTR eax+0x780,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov BYTE  PTR eax+0xa00,0x11;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_45_ ENDP

PUBLIC o4x6_46_
o4x6_46_ PROC
  mov BYTE  PTR eax+0x1,0x11;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov BYTE  PTR eax+0x500,0x11;
  mov BYTE  PTR eax+0x502,0x11;
  mov BYTE  PTR eax+0x780,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov BYTE  PTR eax+0xa01,0x11;
  ret
o4x6_46_ ENDP

PUBLIC o4x6_47_
o4x6_47_ PROC
  mov WORD  PTR eax+0x0,0x1111;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov WORD  PTR eax+0x500,0x1111;
  mov BYTE  PTR eax+0x780,0x11;
  mov BYTE  PTR eax+0xa00,0x11;
  ret
o4x6_47_ ENDP

PUBLIC o4x6_48_
o4x6_48_ PROC
  mov BYTE  PTR eax+0x1,0x11;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov BYTE  PTR eax+0x500,0x11;
  mov BYTE  PTR eax+0x502,0x11;
  mov WORD  PTR eax+0x780,0x1111;
  mov BYTE  PTR eax+0x782,0x11;
  mov WORD  PTR eax+0xa01,0x1111;
  ret
o4x6_48_ ENDP

PUBLIC o4x6_49_
o4x6_49_ PROC
  mov WORD  PTR eax+0x0,0x1111;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov WORD  PTR eax+0x500,0x1111;
  mov BYTE  PTR eax+0x780,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov BYTE  PTR eax+0xa00,0x11;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_49_ ENDP

PUBLIC o4x6_50_
o4x6_50_ PROC
  mov WORD  PTR eax+0x1,0x1111;
  mov BYTE  PTR eax+0x280,0x11;
  mov WORD  PTR eax+0x500,0x1111;
  mov BYTE  PTR eax+0x502,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov WORD  PTR eax+0xa00,0x1111;
  ret
o4x6_50_ ENDP

PUBLIC o4x6_51_
o4x6_51_ PROC
  mov WORD  PTR eax+0x0,0x1111;
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x281,0x11;
  mov BYTE  PTR eax+0x501,0x11;
  mov BYTE  PTR eax+0x781,0x11;
  mov BYTE  PTR eax+0xa01,0x11;
  ret
o4x6_51_ ENDP

PUBLIC o4x6_52_
o4x6_52_ PROC
  mov BYTE  PTR eax+0x0,0x11;
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov BYTE  PTR eax+0x500,0x11;
  mov BYTE  PTR eax+0x502,0x11;
  mov BYTE  PTR eax+0x780,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov WORD  PTR eax+0xa00,0x1111;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_52_ ENDP

PUBLIC o4x6_53_
o4x6_53_ PROC
  mov BYTE  PTR eax+0x0,0x11;
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov BYTE  PTR eax+0x500,0x11;
  mov BYTE  PTR eax+0x502,0x11;
  mov BYTE  PTR eax+0x780,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov BYTE  PTR eax+0xa01,0x11;
  ret
o4x6_53_ ENDP

PUBLIC o4x6_54_
o4x6_54_ PROC
  mov BYTE  PTR eax+0x0,0x11;
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov WORD  PTR eax+0x500,0x1111;
  mov BYTE  PTR eax+0x502,0x11;
  mov WORD  PTR eax+0x780,0x1111;
  mov BYTE  PTR eax+0x782,0x11;
  mov BYTE  PTR eax+0xa00,0x11;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_54_ ENDP

PUBLIC o4x6_55_
o4x6_55_ PROC
  mov BYTE  PTR eax+0x0,0x11;
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov BYTE  PTR eax+0x501,0x11;
  mov BYTE  PTR eax+0x780,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov BYTE  PTR eax+0xa00,0x11;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_55_ ENDP

PUBLIC o4x6_56_
o4x6_56_ PROC
  mov BYTE  PTR eax+0x0,0x11;
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov BYTE  PTR eax+0x501,0x11;
  mov BYTE  PTR eax+0x781,0x11;
  mov BYTE  PTR eax+0xa01,0x11;
  ret
o4x6_56_ ENDP

PUBLIC o4x6_57_
o4x6_57_ PROC
  mov WORD  PTR eax+0x0,0x1111;
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov BYTE  PTR eax+0x501,0x11;
  mov BYTE  PTR eax+0x780,0x11;
  mov WORD  PTR eax+0xa00,0x1111;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_57_ ENDP

PUBLIC o4x6_58_
o4x6_58_ PROC
  mov WORD  PTR eax+0x0,0x1111;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x500,0x11;
  mov BYTE  PTR eax+0x780,0x11;
  mov WORD  PTR eax+0xa00,0x1111;
  ret
o4x6_58_ ENDP

PUBLIC o4x6_59_
o4x6_59_ PROC
  mov BYTE  PTR eax+0x0,0x11;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x501,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_59_ ENDP

PUBLIC o4x6_60_
o4x6_60_ PROC
  mov WORD  PTR eax+0x0,0x1111;
  mov BYTE  PTR eax+0x281,0x11;
  mov BYTE  PTR eax+0x501,0x11;
  mov BYTE  PTR eax+0x781,0x11;
  mov WORD  PTR eax+0xa00,0x1111;
  ret
o4x6_60_ ENDP

PUBLIC o4x6_61_
o4x6_61_ PROC
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x281,0x11;
  mov BYTE  PTR eax+0x283,0x11;
  ret
o4x6_61_ ENDP

PUBLIC o4x6_62_
o4x6_62_ PROC
  mov DWORD PTR eax+0xc80,0x11111111;
  ret
o4x6_62_ ENDP

PUBLIC o4x6_63_
o4x6_63_ PROC
  mov WORD  PTR eax+0x1,0x1111;
  mov BYTE  PTR eax+0x282,0x11;
  ret
o4x6_63_ ENDP

PUBLIC o4x6_64_
o4x6_64_ PROC
  mov WORD  PTR eax+0x502,0x1111;
  mov BYTE  PTR eax+0x781,0x11;
  mov BYTE  PTR eax+0x783,0x11;
  mov WORD  PTR eax+0xa01,0x1111;
  mov BYTE  PTR eax+0xa03,0x11;
  ret
o4x6_64_ ENDP

PUBLIC o4x6_65_
o4x6_65_ PROC
  mov BYTE  PTR eax+0x1,0x11;
  mov BYTE  PTR eax+0x281,0x11;
  mov WORD  PTR eax+0x501,0x1111;
  mov BYTE  PTR eax+0x781,0x11;
  mov BYTE  PTR eax+0x783,0x11;
  mov WORD  PTR eax+0xa01,0x1111;
  ret
o4x6_65_ ENDP

PUBLIC o4x6_66_
o4x6_66_ PROC
  mov WORD  PTR eax+0x502,0x1111;
  mov BYTE  PTR eax+0x781,0x11;
  mov WORD  PTR eax+0xa02,0x1111;
  ret
o4x6_66_ ENDP

PUBLIC o4x6_67_
o4x6_67_ PROC
  mov BYTE  PTR eax+0x3,0x11;
  mov BYTE  PTR eax+0x283,0x11;
  mov WORD  PTR eax+0x502,0x1111;
  mov BYTE  PTR eax+0x781,0x11;
  mov BYTE  PTR eax+0x783,0x11;
  mov WORD  PTR eax+0xa02,0x1111;
  ret
o4x6_67_ ENDP

PUBLIC o4x6_68_
o4x6_68_ PROC
  mov WORD  PTR eax+0x501,0x1111;
  mov BYTE  PTR eax+0x503,0x11;
  mov WORD  PTR eax+0x781,0x1111;
  mov WORD  PTR eax+0xa02,0x1111;
  ret
o4x6_68_ ENDP

PUBLIC o4x6_69_
o4x6_69_ PROC
  mov BYTE  PTR eax+0x3,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov WORD  PTR eax+0x501,0x1111;
  mov BYTE  PTR eax+0x503,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_69_ ENDP

PUBLIC o4x6_70_
o4x6_70_ PROC
  mov WORD  PTR eax+0x501,0x1111;
  mov BYTE  PTR eax+0x503,0x11;
  mov BYTE  PTR eax+0x781,0x11;
  mov BYTE  PTR eax+0x783,0x11;
  mov BYTE  PTR eax+0xa03,0x11;
  mov WORD  PTR eax+0xc81,0x1111;
  mov BYTE  PTR eax+0xc83,0x11;
  ret
o4x6_70_ ENDP

PUBLIC o4x6_71_
o4x6_71_ PROC
  mov BYTE  PTR eax+0x1,0x11;
  mov BYTE  PTR eax+0x281,0x11;
  mov WORD  PTR eax+0x501,0x1111;
  mov BYTE  PTR eax+0x781,0x11;
  mov BYTE  PTR eax+0x783,0x11;
  mov BYTE  PTR eax+0xa01,0x11;
  mov BYTE  PTR eax+0xa03,0x11;
  ret
o4x6_71_ ENDP

PUBLIC o4x6_72_
o4x6_72_ PROC
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x502,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_72_ ENDP

PUBLIC o4x6_73_
o4x6_73_ PROC
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x502,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov BYTE  PTR eax+0xa02,0x11;
  mov WORD  PTR eax+0xc81,0x1111;
  ret
o4x6_73_ ENDP

PUBLIC o4x6_74_
o4x6_74_ PROC
  mov BYTE  PTR eax+0x1,0x11;
  mov BYTE  PTR eax+0x281,0x11;
  mov BYTE  PTR eax+0x501,0x11;
  mov BYTE  PTR eax+0x503,0x11;
  mov WORD  PTR eax+0x781,0x1111;
  mov BYTE  PTR eax+0xa01,0x11;
  mov BYTE  PTR eax+0xa03,0x11;
  ret
o4x6_74_ ENDP

PUBLIC o4x6_75_
o4x6_75_ PROC
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov BYTE  PTR eax+0x502,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_75_ ENDP

PUBLIC o4x6_76_
o4x6_76_ PROC
  mov WORD  PTR eax+0x501,0x1111;
  mov BYTE  PTR eax+0x503,0x11;
  mov WORD  PTR eax+0x781,0x1111;
  mov BYTE  PTR eax+0x783,0x11;
  mov BYTE  PTR eax+0xa01,0x11;
  mov BYTE  PTR eax+0xa03,0x11;
  ret
o4x6_76_ ENDP

PUBLIC o4x6_77_
o4x6_77_ PROC
  mov WORD  PTR eax+0x501,0x1111;
  mov BYTE  PTR eax+0x781,0x11;
  mov BYTE  PTR eax+0x783,0x11;
  mov BYTE  PTR eax+0xa01,0x11;
  mov BYTE  PTR eax+0xa03,0x11;
  ret
o4x6_77_ ENDP

PUBLIC o4x6_78_
o4x6_78_ PROC
  mov BYTE  PTR eax+0x502,0x11;
  mov BYTE  PTR eax+0x781,0x11;
  mov BYTE  PTR eax+0x783,0x11;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_78_ ENDP

PUBLIC o4x6_79_
o4x6_79_ PROC
  mov WORD  PTR eax+0x501,0x1111;
  mov BYTE  PTR eax+0x781,0x11;
  mov BYTE  PTR eax+0x783,0x11;
  mov WORD  PTR eax+0xa01,0x1111;
  mov BYTE  PTR eax+0xc81,0x11;
  ret
o4x6_79_ ENDP

PUBLIC o4x6_80_
o4x6_80_ PROC
  mov WORD  PTR eax+0x502,0x1111;
  mov BYTE  PTR eax+0x781,0x11;
  mov BYTE  PTR eax+0x783,0x11;
  mov WORD  PTR eax+0xa02,0x1111;
  mov BYTE  PTR eax+0xc83,0x11;
  ret
o4x6_80_ ENDP

PUBLIC o4x6_81_
o4x6_81_ PROC
  mov WORD  PTR eax+0x501,0x1111;
  mov BYTE  PTR eax+0x781,0x11;
  mov BYTE  PTR eax+0xa01,0x11;
  ret
o4x6_81_ ENDP

PUBLIC o4x6_82_
o4x6_82_ PROC
  mov WORD  PTR eax+0x502,0x1111;
  mov BYTE  PTR eax+0x782,0x11;
  mov WORD  PTR eax+0xa01,0x1111;
  ret
o4x6_82_ ENDP

PUBLIC o4x6_83_
o4x6_83_ PROC
  mov BYTE  PTR eax+0x282,0x11;
  mov WORD  PTR eax+0x501,0x1111;
  mov BYTE  PTR eax+0x503,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov WORD  PTR eax+0xa02,0x1111;
  ret
o4x6_83_ ENDP

PUBLIC o4x6_84_
o4x6_84_ PROC
  mov BYTE  PTR eax+0x501,0x11;
  mov BYTE  PTR eax+0x503,0x11;
  mov BYTE  PTR eax+0x781,0x11;
  mov BYTE  PTR eax+0x783,0x11;
  mov WORD  PTR eax+0xa01,0x1111;
  mov BYTE  PTR eax+0xa03,0x11;
  ret
o4x6_84_ ENDP

PUBLIC o4x6_85_
o4x6_85_ PROC
  mov BYTE  PTR eax+0x501,0x11;
  mov BYTE  PTR eax+0x503,0x11;
  mov BYTE  PTR eax+0x781,0x11;
  mov BYTE  PTR eax+0x783,0x11;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_85_ ENDP

PUBLIC o4x6_86_
o4x6_86_ PROC
  mov BYTE  PTR eax+0x501,0x11;
  mov BYTE  PTR eax+0x503,0x11;
  mov WORD  PTR eax+0x781,0x1111;
  mov BYTE  PTR eax+0x783,0x11;
  mov WORD  PTR eax+0xa01,0x1111;
  mov BYTE  PTR eax+0xa03,0x11;
  ret
o4x6_86_ ENDP

PUBLIC o4x6_87_
o4x6_87_ PROC
  mov BYTE  PTR eax+0x501,0x11;
  mov BYTE  PTR eax+0x503,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov BYTE  PTR eax+0xa01,0x11;
  mov BYTE  PTR eax+0xa03,0x11;
  ret
o4x6_87_ ENDP

PUBLIC o4x6_88_
o4x6_88_ PROC
  mov BYTE  PTR eax+0x501,0x11;
  mov BYTE  PTR eax+0x503,0x11;
  mov BYTE  PTR eax+0x781,0x11;
  mov BYTE  PTR eax+0x783,0x11;
  mov BYTE  PTR eax+0xa02,0x11;
  mov BYTE  PTR eax+0xc81,0x11;
  ret
o4x6_88_ ENDP

PUBLIC o4x6_89_
o4x6_89_ PROC
  mov WORD  PTR eax+0x501,0x1111;
  mov BYTE  PTR eax+0x782,0x11;
  mov WORD  PTR eax+0xa02,0x1111;
  ret
o4x6_89_ ENDP

PUBLIC o4x6_90_
o4x6_90_ PROC
  mov WORD  PTR eax+0x2,0x1111;
  mov BYTE  PTR eax+0x282,0x11;
  mov WORD  PTR eax+0x501,0x1111;
  mov BYTE  PTR eax+0x782,0x11;
  mov WORD  PTR eax+0xa02,0x1111;
  ret
o4x6_90_ ENDP

PUBLIC o4x6_91_
o4x6_91_ PROC
  mov BYTE  PTR eax+0x2,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  mov BYTE  PTR eax+0x502,0x11;
  mov BYTE  PTR eax+0x782,0x11;
  mov BYTE  PTR eax+0xa02,0x11;
  ret
o4x6_91_ ENDP

PUBLIC o4x6_92_
o4x6_92_ PROC
  mov WORD  PTR eax+0x1,0x1111;
  mov BYTE  PTR eax+0x282,0x11;
  mov WORD  PTR eax+0x502,0x1111;
  mov BYTE  PTR eax+0x782,0x11;
  mov WORD  PTR eax+0xa01,0x1111;
  ret
o4x6_92_ ENDP

PUBLIC o4x6_93_
o4x6_93_ PROC
  mov BYTE  PTR eax+0x1,0x11;
  mov BYTE  PTR eax+0x3,0x11;
  mov BYTE  PTR eax+0x280,0x11;
  mov BYTE  PTR eax+0x282,0x11;
  ret
o4x6_93_ ENDP

_TEXT ENDS
END
