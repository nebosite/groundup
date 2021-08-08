; Compiled Sprites output from spr2asm
;  command line : spr2asm b4x6 b4x6.spr 
;  entry point name : b4x6
;  asm output file  : b4x6_A.ASM
;  c   output file  : b4x6_C.C
;  spr input  file  : b4x6.spr
;
.386
DGROUP group _DATA
_DATA  segment 'DATA'
_DATA  ends
_TEXT  segment BYTE PUBLIC USE32 'CODE'
       ASSUME CS:_TEXT
       ASSUME DS:DGROUN

PUBLIC b4x6_0_
b4x6_0_ PROC
  mov BYTE  PTR eax+0x1,0xb4;
  mov BYTE  PTR eax+0x281,0xb4;
  mov BYTE  PTR eax+0x501,0xb4;
  mov BYTE  PTR eax+0xa01,0xb4;
  ret
b4x6_0_ ENDP

PUBLIC b4x6_1_
b4x6_1_ PROC
  mov BYTE  PTR eax+0x0,0xb4;
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  ret
b4x6_1_ ENDP

PUBLIC b4x6_2_
b4x6_2_ PROC
  mov BYTE  PTR eax+0x0,0xb4;
  mov BYTE  PTR eax+0x2,0xb4;
  mov WORD  PTR eax+0x280,0xb4b4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov BYTE  PTR eax+0x500,0xb4;
  mov BYTE  PTR eax+0x502,0xb4;
  mov WORD  PTR eax+0x780,0xb4b4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov BYTE  PTR eax+0xa00,0xb4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_2_ ENDP

PUBLIC b4x6_3_
b4x6_3_ PROC
  mov BYTE  PTR eax+0x1,0xb4;
  mov WORD  PTR eax+0x281,0xb4b4;
  mov WORD  PTR eax+0x500,0xb4b4;
  mov WORD  PTR eax+0x781,0xb4b4;
  mov WORD  PTR eax+0xa00,0xb4b4;
  mov BYTE  PTR eax+0xc81,0xb4;
  ret
b4x6_3_ ENDP

PUBLIC b4x6_4_
b4x6_4_ PROC
  mov BYTE  PTR eax+0x0,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov BYTE  PTR eax+0x501,0xb4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_4_ ENDP

PUBLIC b4x6_5_
b4x6_5_ PROC
  mov BYTE  PTR eax+0x1,0xb4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov WORD  PTR eax+0x501,0xb4b4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov WORD  PTR eax+0xa00,0xb4b4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_5_ ENDP

PUBLIC b4x6_6_
b4x6_6_ PROC
  mov WORD  PTR eax+0x0,0xb4b4;
  mov BYTE  PTR eax+0x280,0xb4;
  ret
b4x6_6_ ENDP

PUBLIC b4x6_7_
b4x6_7_ PROC
  mov BYTE  PTR eax+0x1,0xb4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x500,0xb4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov BYTE  PTR eax+0xa01,0xb4;
  ret
b4x6_7_ ENDP

PUBLIC b4x6_8_
b4x6_8_ PROC
  mov BYTE  PTR eax+0x0,0xb4;
  mov BYTE  PTR eax+0x281,0xb4;
  mov BYTE  PTR eax+0x501,0xb4;
  mov BYTE  PTR eax+0x781,0xb4;
  mov BYTE  PTR eax+0xa00,0xb4;
  ret
b4x6_8_ ENDP

PUBLIC b4x6_9_
b4x6_9_ PROC
  mov BYTE  PTR eax+0x0,0xb4;
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x281,0xb4;
  mov WORD  PTR eax+0x500,0xb4b4;
  mov BYTE  PTR eax+0x502,0xb4;
  mov BYTE  PTR eax+0x781,0xb4;
  mov BYTE  PTR eax+0xa00,0xb4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_9_ ENDP

PUBLIC b4x6_10_
b4x6_10_ PROC
  mov BYTE  PTR eax+0x281,0xb4;
  mov WORD  PTR eax+0x500,0xb4b4;
  mov BYTE  PTR eax+0x502,0xb4;
  mov BYTE  PTR eax+0x781,0xb4;
  ret
b4x6_10_ ENDP

PUBLIC b4x6_11_
b4x6_11_ PROC
  mov WORD  PTR eax+0xa00,0xb4b4;
  mov BYTE  PTR eax+0xc80,0xb4;
  ret
b4x6_11_ ENDP

PUBLIC b4x6_12_
b4x6_12_ PROC
  mov WORD  PTR eax+0x500,0xb4b4;
  mov BYTE  PTR eax+0x502,0xb4;
  ret
b4x6_12_ ENDP

PUBLIC b4x6_13_
b4x6_13_ PROC
  mov BYTE  PTR eax+0xa01,0xb4;
  ret
b4x6_13_ ENDP

PUBLIC b4x6_14_
b4x6_14_ PROC
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov BYTE  PTR eax+0x501,0xb4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov BYTE  PTR eax+0xa00,0xb4;
  ret
b4x6_14_ ENDP

PUBLIC b4x6_15_
b4x6_15_ PROC
  mov WORD  PTR eax+0x1,0xb4b4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov BYTE  PTR eax+0x500,0xb4;
  mov BYTE  PTR eax+0x502,0xb4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov WORD  PTR eax+0xa00,0xb4b4;
  ret
b4x6_15_ ENDP

PUBLIC b4x6_16_
b4x6_16_ PROC
  mov BYTE  PTR eax+0x1,0xb4;
  mov WORD  PTR eax+0x280,0xb4b4;
  mov BYTE  PTR eax+0x501,0xb4;
  mov BYTE  PTR eax+0x781,0xb4;
  mov WORD  PTR eax+0xa00,0xb4b4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_16_ ENDP

PUBLIC b4x6_17_
b4x6_17_ PROC
  mov WORD  PTR eax+0x0,0xb4b4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov BYTE  PTR eax+0x501,0xb4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov WORD  PTR eax+0xa00,0xb4b4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_17_ ENDP

PUBLIC b4x6_18_
b4x6_18_ PROC
  mov WORD  PTR eax+0x0,0xb4b4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov BYTE  PTR eax+0x501,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov WORD  PTR eax+0xa00,0xb4b4;
  ret
b4x6_18_ ENDP

PUBLIC b4x6_19_
b4x6_19_ PROC
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov WORD  PTR eax+0x500,0xb4b4;
  mov BYTE  PTR eax+0x502,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_19_ ENDP

PUBLIC b4x6_20_
b4x6_20_ PROC
  mov WORD  PTR eax+0x0,0xb4b4;
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov WORD  PTR eax+0x500,0xb4b4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov WORD  PTR eax+0xa00,0xb4b4;
  ret
b4x6_20_ ENDP

PUBLIC b4x6_21_
b4x6_21_ PROC
  mov BYTE  PTR eax+0x1,0xb4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov WORD  PTR eax+0x500,0xb4b4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov BYTE  PTR eax+0xa01,0xb4;
  ret
b4x6_21_ ENDP

PUBLIC b4x6_22_
b4x6_22_ PROC
  mov WORD  PTR eax+0x0,0xb4b4;
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov WORD  PTR eax+0x501,0xb4b4;
  mov BYTE  PTR eax+0x781,0xb4;
  mov BYTE  PTR eax+0xa01,0xb4;
  ret
b4x6_22_ ENDP

PUBLIC b4x6_23_
b4x6_23_ PROC
  mov BYTE  PTR eax+0x1,0xb4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov BYTE  PTR eax+0x501,0xb4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov BYTE  PTR eax+0xa01,0xb4;
  ret
b4x6_23_ ENDP

PUBLIC b4x6_24_
b4x6_24_ PROC
  mov BYTE  PTR eax+0x1,0xb4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov WORD  PTR eax+0x501,0xb4b4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov BYTE  PTR eax+0xa01,0xb4;
  ret
b4x6_24_ ENDP

PUBLIC b4x6_25_
b4x6_25_ PROC
  mov BYTE  PTR eax+0x501,0xb4;
  mov BYTE  PTR eax+0xa01,0xb4;
  ret
b4x6_25_ ENDP

PUBLIC b4x6_26_
b4x6_26_ PROC
  mov BYTE  PTR eax+0x501,0xb4;
  mov WORD  PTR eax+0xa00,0xb4b4;
  mov BYTE  PTR eax+0xc80,0xb4;
  ret
b4x6_26_ ENDP

PUBLIC b4x6_27_
b4x6_27_ PROC
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x281,0xb4;
  mov BYTE  PTR eax+0x500,0xb4;
  mov BYTE  PTR eax+0x781,0xb4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_27_ ENDP

PUBLIC b4x6_28_
b4x6_28_ PROC
  mov WORD  PTR eax+0x500,0xb4b4;
  mov BYTE  PTR eax+0x502,0xb4;
  mov WORD  PTR eax+0xa00,0xb4b4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_28_ ENDP

PUBLIC b4x6_29_
b4x6_29_ PROC
  mov BYTE  PTR eax+0x0,0xb4;
  mov BYTE  PTR eax+0x281,0xb4;
  mov BYTE  PTR eax+0x502,0xb4;
  mov BYTE  PTR eax+0x781,0xb4;
  mov BYTE  PTR eax+0xa00,0xb4;
  ret
b4x6_29_ ENDP

PUBLIC b4x6_30_
b4x6_30_ PROC
  mov WORD  PTR eax+0x0,0xb4b4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov BYTE  PTR eax+0x501,0xb4;
  mov BYTE  PTR eax+0xa01,0xb4;
  ret
b4x6_30_ ENDP

PUBLIC b4x6_31_
b4x6_31_ PROC
  mov WORD  PTR eax+0x0,0xb4b4;
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov BYTE  PTR eax+0x500,0xb4;
  mov BYTE  PTR eax+0x502,0xb4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov WORD  PTR eax+0xa00,0xb4b4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_31_ ENDP

PUBLIC b4x6_32_
b4x6_32_ PROC
  mov BYTE  PTR eax+0x1,0xb4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov WORD  PTR eax+0x500,0xb4b4;
  mov BYTE  PTR eax+0x502,0xb4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov BYTE  PTR eax+0xa00,0xb4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_32_ ENDP

PUBLIC b4x6_33_
b4x6_33_ PROC
  mov WORD  PTR eax+0x0,0xb4b4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov WORD  PTR eax+0x500,0xb4b4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov WORD  PTR eax+0xa00,0xb4b4;
  ret
b4x6_33_ ENDP

PUBLIC b4x6_34_
b4x6_34_ PROC
  mov WORD  PTR eax+0x1,0xb4b4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x500,0xb4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov WORD  PTR eax+0xa01,0xb4b4;
  ret
b4x6_34_ ENDP

PUBLIC b4x6_35_
b4x6_35_ PROC
  mov WORD  PTR eax+0x0,0xb4b4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov BYTE  PTR eax+0x500,0xb4;
  mov BYTE  PTR eax+0x502,0xb4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov WORD  PTR eax+0xa00,0xb4b4;
  ret
b4x6_35_ ENDP

PUBLIC b4x6_36_
b4x6_36_ PROC
  mov WORD  PTR eax+0x0,0xb4b4;
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov WORD  PTR eax+0x500,0xb4b4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov WORD  PTR eax+0xa00,0xb4b4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_36_ ENDP

PUBLIC b4x6_37_
b4x6_37_ PROC
  mov WORD  PTR eax+0x0,0xb4b4;
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov WORD  PTR eax+0x500,0xb4b4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov BYTE  PTR eax+0xa00,0xb4;
  ret
b4x6_37_ ENDP

PUBLIC b4x6_38_
b4x6_38_ PROC
  mov WORD  PTR eax+0x1,0xb4b4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x500,0xb4;
  mov BYTE  PTR eax+0x502,0xb4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov WORD  PTR eax+0xa01,0xb4b4;
  ret
b4x6_38_ ENDP

PUBLIC b4x6_39_
b4x6_39_ PROC
  mov BYTE  PTR eax+0x0,0xb4;
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov WORD  PTR eax+0x500,0xb4b4;
  mov BYTE  PTR eax+0x502,0xb4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov BYTE  PTR eax+0xa00,0xb4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_39_ ENDP

PUBLIC b4x6_40_
b4x6_40_ PROC
  mov WORD  PTR eax+0x0,0xb4b4;
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x281,0xb4;
  mov BYTE  PTR eax+0x501,0xb4;
  mov BYTE  PTR eax+0x781,0xb4;
  mov WORD  PTR eax+0xa00,0xb4b4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_40_ ENDP

PUBLIC b4x6_41_
b4x6_41_ PROC
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov BYTE  PTR eax+0x502,0xb4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov BYTE  PTR eax+0xa01,0xb4;
  ret
b4x6_41_ ENDP

PUBLIC b4x6_42_
b4x6_42_ PROC
  mov BYTE  PTR eax+0x0,0xb4;
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov WORD  PTR eax+0x500,0xb4b4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov BYTE  PTR eax+0xa00,0xb4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_42_ ENDP

PUBLIC b4x6_43_
b4x6_43_ PROC
  mov BYTE  PTR eax+0x0,0xb4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x500,0xb4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov WORD  PTR eax+0xa00,0xb4b4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_43_ ENDP

PUBLIC b4x6_44_
b4x6_44_ PROC
  mov BYTE  PTR eax+0x0,0xb4;
  mov BYTE  PTR eax+0x2,0xb4;
  mov WORD  PTR eax+0x280,0xb4b4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov WORD  PTR eax+0x500,0xb4b4;
  mov BYTE  PTR eax+0x502,0xb4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov BYTE  PTR eax+0xa00,0xb4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_44_ ENDP

PUBLIC b4x6_45_
b4x6_45_ PROC
  mov BYTE  PTR eax+0x0,0xb4;
  mov BYTE  PTR eax+0x2,0xb4;
  mov WORD  PTR eax+0x280,0xb4b4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov BYTE  PTR eax+0x500,0xb4;
  mov BYTE  PTR eax+0x502,0xb4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov BYTE  PTR eax+0xa00,0xb4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_45_ ENDP

PUBLIC b4x6_46_
b4x6_46_ PROC
  mov BYTE  PTR eax+0x1,0xb4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov BYTE  PTR eax+0x500,0xb4;
  mov BYTE  PTR eax+0x502,0xb4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov BYTE  PTR eax+0xa01,0xb4;
  ret
b4x6_46_ ENDP

PUBLIC b4x6_47_
b4x6_47_ PROC
  mov WORD  PTR eax+0x0,0xb4b4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov WORD  PTR eax+0x500,0xb4b4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov BYTE  PTR eax+0xa00,0xb4;
  ret
b4x6_47_ ENDP

PUBLIC b4x6_48_
b4x6_48_ PROC
  mov BYTE  PTR eax+0x1,0xb4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov BYTE  PTR eax+0x500,0xb4;
  mov BYTE  PTR eax+0x502,0xb4;
  mov WORD  PTR eax+0x780,0xb4b4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov WORD  PTR eax+0xa01,0xb4b4;
  ret
b4x6_48_ ENDP

PUBLIC b4x6_49_
b4x6_49_ PROC
  mov WORD  PTR eax+0x0,0xb4b4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov WORD  PTR eax+0x500,0xb4b4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov BYTE  PTR eax+0xa00,0xb4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_49_ ENDP

PUBLIC b4x6_50_
b4x6_50_ PROC
  mov WORD  PTR eax+0x1,0xb4b4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov WORD  PTR eax+0x500,0xb4b4;
  mov BYTE  PTR eax+0x502,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov WORD  PTR eax+0xa00,0xb4b4;
  ret
b4x6_50_ ENDP

PUBLIC b4x6_51_
b4x6_51_ PROC
  mov WORD  PTR eax+0x0,0xb4b4;
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x281,0xb4;
  mov BYTE  PTR eax+0x501,0xb4;
  mov BYTE  PTR eax+0x781,0xb4;
  mov BYTE  PTR eax+0xa01,0xb4;
  ret
b4x6_51_ ENDP

PUBLIC b4x6_52_
b4x6_52_ PROC
  mov BYTE  PTR eax+0x0,0xb4;
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov BYTE  PTR eax+0x500,0xb4;
  mov BYTE  PTR eax+0x502,0xb4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov WORD  PTR eax+0xa00,0xb4b4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_52_ ENDP

PUBLIC b4x6_53_
b4x6_53_ PROC
  mov BYTE  PTR eax+0x0,0xb4;
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov BYTE  PTR eax+0x500,0xb4;
  mov BYTE  PTR eax+0x502,0xb4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov BYTE  PTR eax+0xa01,0xb4;
  ret
b4x6_53_ ENDP

PUBLIC b4x6_54_
b4x6_54_ PROC
  mov BYTE  PTR eax+0x0,0xb4;
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov WORD  PTR eax+0x500,0xb4b4;
  mov BYTE  PTR eax+0x502,0xb4;
  mov WORD  PTR eax+0x780,0xb4b4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov BYTE  PTR eax+0xa00,0xb4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_54_ ENDP

PUBLIC b4x6_55_
b4x6_55_ PROC
  mov BYTE  PTR eax+0x0,0xb4;
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov BYTE  PTR eax+0x501,0xb4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov BYTE  PTR eax+0xa00,0xb4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_55_ ENDP

PUBLIC b4x6_56_
b4x6_56_ PROC
  mov BYTE  PTR eax+0x0,0xb4;
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov BYTE  PTR eax+0x501,0xb4;
  mov BYTE  PTR eax+0x781,0xb4;
  mov BYTE  PTR eax+0xa01,0xb4;
  ret
b4x6_56_ ENDP

PUBLIC b4x6_57_
b4x6_57_ PROC
  mov WORD  PTR eax+0x0,0xb4b4;
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov BYTE  PTR eax+0x501,0xb4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov WORD  PTR eax+0xa00,0xb4b4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_57_ ENDP

PUBLIC b4x6_58_
b4x6_58_ PROC
  mov WORD  PTR eax+0x0,0xb4b4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x500,0xb4;
  mov BYTE  PTR eax+0x780,0xb4;
  mov WORD  PTR eax+0xa00,0xb4b4;
  ret
b4x6_58_ ENDP

PUBLIC b4x6_59_
b4x6_59_ PROC
  mov BYTE  PTR eax+0x0,0xb4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x501,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_59_ ENDP

PUBLIC b4x6_60_
b4x6_60_ PROC
  mov WORD  PTR eax+0x0,0xb4b4;
  mov BYTE  PTR eax+0x281,0xb4;
  mov BYTE  PTR eax+0x501,0xb4;
  mov BYTE  PTR eax+0x781,0xb4;
  mov WORD  PTR eax+0xa00,0xb4b4;
  ret
b4x6_60_ ENDP

PUBLIC b4x6_61_
b4x6_61_ PROC
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x281,0xb4;
  mov BYTE  PTR eax+0x283,0xb4;
  ret
b4x6_61_ ENDP

PUBLIC b4x6_62_
b4x6_62_ PROC
  mov DWORD PTR eax+0xc80,0xb4b4b4b4;
  ret
b4x6_62_ ENDP

PUBLIC b4x6_63_
b4x6_63_ PROC
  mov WORD  PTR eax+0x1,0xb4b4;
  mov BYTE  PTR eax+0x282,0xb4;
  ret
b4x6_63_ ENDP

PUBLIC b4x6_64_
b4x6_64_ PROC
  mov WORD  PTR eax+0x502,0xb4b4;
  mov BYTE  PTR eax+0x781,0xb4;
  mov BYTE  PTR eax+0x783,0xb4;
  mov WORD  PTR eax+0xa01,0xb4b4;
  mov BYTE  PTR eax+0xa03,0xb4;
  ret
b4x6_64_ ENDP

PUBLIC b4x6_65_
b4x6_65_ PROC
  mov BYTE  PTR eax+0x1,0xb4;
  mov BYTE  PTR eax+0x281,0xb4;
  mov WORD  PTR eax+0x501,0xb4b4;
  mov BYTE  PTR eax+0x781,0xb4;
  mov BYTE  PTR eax+0x783,0xb4;
  mov WORD  PTR eax+0xa01,0xb4b4;
  ret
b4x6_65_ ENDP

PUBLIC b4x6_66_
b4x6_66_ PROC
  mov WORD  PTR eax+0x502,0xb4b4;
  mov BYTE  PTR eax+0x781,0xb4;
  mov WORD  PTR eax+0xa02,0xb4b4;
  ret
b4x6_66_ ENDP

PUBLIC b4x6_67_
b4x6_67_ PROC
  mov BYTE  PTR eax+0x3,0xb4;
  mov BYTE  PTR eax+0x283,0xb4;
  mov WORD  PTR eax+0x502,0xb4b4;
  mov BYTE  PTR eax+0x781,0xb4;
  mov BYTE  PTR eax+0x783,0xb4;
  mov WORD  PTR eax+0xa02,0xb4b4;
  ret
b4x6_67_ ENDP

PUBLIC b4x6_68_
b4x6_68_ PROC
  mov WORD  PTR eax+0x501,0xb4b4;
  mov BYTE  PTR eax+0x503,0xb4;
  mov WORD  PTR eax+0x781,0xb4b4;
  mov WORD  PTR eax+0xa02,0xb4b4;
  ret
b4x6_68_ ENDP

PUBLIC b4x6_69_
b4x6_69_ PROC
  mov BYTE  PTR eax+0x3,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov WORD  PTR eax+0x501,0xb4b4;
  mov BYTE  PTR eax+0x503,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_69_ ENDP

PUBLIC b4x6_70_
b4x6_70_ PROC
  mov WORD  PTR eax+0x501,0xb4b4;
  mov BYTE  PTR eax+0x503,0xb4;
  mov BYTE  PTR eax+0x781,0xb4;
  mov BYTE  PTR eax+0x783,0xb4;
  mov BYTE  PTR eax+0xa03,0xb4;
  mov WORD  PTR eax+0xc81,0xb4b4;
  mov BYTE  PTR eax+0xc83,0xb4;
  ret
b4x6_70_ ENDP

PUBLIC b4x6_71_
b4x6_71_ PROC
  mov BYTE  PTR eax+0x1,0xb4;
  mov BYTE  PTR eax+0x281,0xb4;
  mov WORD  PTR eax+0x501,0xb4b4;
  mov BYTE  PTR eax+0x781,0xb4;
  mov BYTE  PTR eax+0x783,0xb4;
  mov BYTE  PTR eax+0xa01,0xb4;
  mov BYTE  PTR eax+0xa03,0xb4;
  ret
b4x6_71_ ENDP

PUBLIC b4x6_72_
b4x6_72_ PROC
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x502,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_72_ ENDP

PUBLIC b4x6_73_
b4x6_73_ PROC
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x502,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov BYTE  PTR eax+0xa02,0xb4;
  mov WORD  PTR eax+0xc81,0xb4b4;
  ret
b4x6_73_ ENDP

PUBLIC b4x6_74_
b4x6_74_ PROC
  mov BYTE  PTR eax+0x1,0xb4;
  mov BYTE  PTR eax+0x281,0xb4;
  mov BYTE  PTR eax+0x501,0xb4;
  mov BYTE  PTR eax+0x503,0xb4;
  mov WORD  PTR eax+0x781,0xb4b4;
  mov BYTE  PTR eax+0xa01,0xb4;
  mov BYTE  PTR eax+0xa03,0xb4;
  ret
b4x6_74_ ENDP

PUBLIC b4x6_75_
b4x6_75_ PROC
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov BYTE  PTR eax+0x502,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_75_ ENDP

PUBLIC b4x6_76_
b4x6_76_ PROC
  mov WORD  PTR eax+0x501,0xb4b4;
  mov BYTE  PTR eax+0x503,0xb4;
  mov WORD  PTR eax+0x781,0xb4b4;
  mov BYTE  PTR eax+0x783,0xb4;
  mov BYTE  PTR eax+0xa01,0xb4;
  mov BYTE  PTR eax+0xa03,0xb4;
  ret
b4x6_76_ ENDP

PUBLIC b4x6_77_
b4x6_77_ PROC
  mov WORD  PTR eax+0x501,0xb4b4;
  mov BYTE  PTR eax+0x781,0xb4;
  mov BYTE  PTR eax+0x783,0xb4;
  mov BYTE  PTR eax+0xa01,0xb4;
  mov BYTE  PTR eax+0xa03,0xb4;
  ret
b4x6_77_ ENDP

PUBLIC b4x6_78_
b4x6_78_ PROC
  mov BYTE  PTR eax+0x502,0xb4;
  mov BYTE  PTR eax+0x781,0xb4;
  mov BYTE  PTR eax+0x783,0xb4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_78_ ENDP

PUBLIC b4x6_79_
b4x6_79_ PROC
  mov WORD  PTR eax+0x501,0xb4b4;
  mov BYTE  PTR eax+0x781,0xb4;
  mov BYTE  PTR eax+0x783,0xb4;
  mov WORD  PTR eax+0xa01,0xb4b4;
  mov BYTE  PTR eax+0xc81,0xb4;
  ret
b4x6_79_ ENDP

PUBLIC b4x6_80_
b4x6_80_ PROC
  mov WORD  PTR eax+0x502,0xb4b4;
  mov BYTE  PTR eax+0x781,0xb4;
  mov BYTE  PTR eax+0x783,0xb4;
  mov WORD  PTR eax+0xa02,0xb4b4;
  mov BYTE  PTR eax+0xc83,0xb4;
  ret
b4x6_80_ ENDP

PUBLIC b4x6_81_
b4x6_81_ PROC
  mov WORD  PTR eax+0x501,0xb4b4;
  mov BYTE  PTR eax+0x781,0xb4;
  mov BYTE  PTR eax+0xa01,0xb4;
  ret
b4x6_81_ ENDP

PUBLIC b4x6_82_
b4x6_82_ PROC
  mov WORD  PTR eax+0x502,0xb4b4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov WORD  PTR eax+0xa01,0xb4b4;
  ret
b4x6_82_ ENDP

PUBLIC b4x6_83_
b4x6_83_ PROC
  mov BYTE  PTR eax+0x282,0xb4;
  mov WORD  PTR eax+0x501,0xb4b4;
  mov BYTE  PTR eax+0x503,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov WORD  PTR eax+0xa02,0xb4b4;
  ret
b4x6_83_ ENDP

PUBLIC b4x6_84_
b4x6_84_ PROC
  mov BYTE  PTR eax+0x501,0xb4;
  mov BYTE  PTR eax+0x503,0xb4;
  mov BYTE  PTR eax+0x781,0xb4;
  mov BYTE  PTR eax+0x783,0xb4;
  mov WORD  PTR eax+0xa01,0xb4b4;
  mov BYTE  PTR eax+0xa03,0xb4;
  ret
b4x6_84_ ENDP

PUBLIC b4x6_85_
b4x6_85_ PROC
  mov BYTE  PTR eax+0x501,0xb4;
  mov BYTE  PTR eax+0x503,0xb4;
  mov BYTE  PTR eax+0x781,0xb4;
  mov BYTE  PTR eax+0x783,0xb4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_85_ ENDP

PUBLIC b4x6_86_
b4x6_86_ PROC
  mov BYTE  PTR eax+0x501,0xb4;
  mov BYTE  PTR eax+0x503,0xb4;
  mov WORD  PTR eax+0x781,0xb4b4;
  mov BYTE  PTR eax+0x783,0xb4;
  mov WORD  PTR eax+0xa01,0xb4b4;
  mov BYTE  PTR eax+0xa03,0xb4;
  ret
b4x6_86_ ENDP

PUBLIC b4x6_87_
b4x6_87_ PROC
  mov BYTE  PTR eax+0x501,0xb4;
  mov BYTE  PTR eax+0x503,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov BYTE  PTR eax+0xa01,0xb4;
  mov BYTE  PTR eax+0xa03,0xb4;
  ret
b4x6_87_ ENDP

PUBLIC b4x6_88_
b4x6_88_ PROC
  mov BYTE  PTR eax+0x501,0xb4;
  mov BYTE  PTR eax+0x503,0xb4;
  mov BYTE  PTR eax+0x781,0xb4;
  mov BYTE  PTR eax+0x783,0xb4;
  mov BYTE  PTR eax+0xa02,0xb4;
  mov BYTE  PTR eax+0xc81,0xb4;
  ret
b4x6_88_ ENDP

PUBLIC b4x6_89_
b4x6_89_ PROC
  mov WORD  PTR eax+0x501,0xb4b4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov WORD  PTR eax+0xa02,0xb4b4;
  ret
b4x6_89_ ENDP

PUBLIC b4x6_90_
b4x6_90_ PROC
  mov WORD  PTR eax+0x2,0xb4b4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov WORD  PTR eax+0x501,0xb4b4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov WORD  PTR eax+0xa02,0xb4b4;
  ret
b4x6_90_ ENDP

PUBLIC b4x6_91_
b4x6_91_ PROC
  mov BYTE  PTR eax+0x2,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov BYTE  PTR eax+0x502,0xb4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov BYTE  PTR eax+0xa02,0xb4;
  ret
b4x6_91_ ENDP

PUBLIC b4x6_92_
b4x6_92_ PROC
  mov WORD  PTR eax+0x1,0xb4b4;
  mov BYTE  PTR eax+0x282,0xb4;
  mov WORD  PTR eax+0x502,0xb4b4;
  mov BYTE  PTR eax+0x782,0xb4;
  mov WORD  PTR eax+0xa01,0xb4b4;
  ret
b4x6_92_ ENDP

PUBLIC b4x6_93_
b4x6_93_ PROC
  mov BYTE  PTR eax+0x1,0xb4;
  mov BYTE  PTR eax+0x3,0xb4;
  mov BYTE  PTR eax+0x280,0xb4;
  mov BYTE  PTR eax+0x282,0xb4;
  ret
b4x6_93_ ENDP

_TEXT ENDS
END
