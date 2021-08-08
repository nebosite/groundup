; Compiled Sprites output from spr2asm
;  command line : spr2asm w4x6 w4x6.spr 
;  entry point name : w4x6
;  asm output file  : w4x6_A.ASM
;  c   output file  : w4x6_C.C
;  spr input  file  : w4x6.spr
;
.386
DGROUP group _DATA
_DATA  segment 'DATA'
_DATA  ends
_TEXT  segment BYTE PUBLIC USE32 'CODE'
       ASSUME CS:_TEXT
       ASSUME DS:DGROUN

PUBLIC w4x6_0_
w4x6_0_ PROC
  mov BYTE  PTR eax+0x1,0xd7;
  mov BYTE  PTR eax+0x281,0xd7;
  mov BYTE  PTR eax+0x501,0xd7;
  mov BYTE  PTR eax+0xa01,0xd7;
  ret
w4x6_0_ ENDP

PUBLIC w4x6_1_
w4x6_1_ PROC
  mov BYTE  PTR eax+0x0,0xd7;
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  ret
w4x6_1_ ENDP

PUBLIC w4x6_2_
w4x6_2_ PROC
  mov BYTE  PTR eax+0x0,0xd7;
  mov BYTE  PTR eax+0x2,0xd7;
  mov WORD  PTR eax+0x280,0xd7d7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov BYTE  PTR eax+0x500,0xd7;
  mov BYTE  PTR eax+0x502,0xd7;
  mov WORD  PTR eax+0x780,0xd7d7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov BYTE  PTR eax+0xa00,0xd7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_2_ ENDP

PUBLIC w4x6_3_
w4x6_3_ PROC
  mov BYTE  PTR eax+0x1,0xd7;
  mov WORD  PTR eax+0x281,0xd7d7;
  mov WORD  PTR eax+0x500,0xd7d7;
  mov WORD  PTR eax+0x781,0xd7d7;
  mov WORD  PTR eax+0xa00,0xd7d7;
  mov BYTE  PTR eax+0xc81,0xd7;
  ret
w4x6_3_ ENDP

PUBLIC w4x6_4_
w4x6_4_ PROC
  mov BYTE  PTR eax+0x0,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov BYTE  PTR eax+0x501,0xd7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_4_ ENDP

PUBLIC w4x6_5_
w4x6_5_ PROC
  mov BYTE  PTR eax+0x1,0xd7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov WORD  PTR eax+0x501,0xd7d7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov WORD  PTR eax+0xa00,0xd7d7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_5_ ENDP

PUBLIC w4x6_6_
w4x6_6_ PROC
  mov WORD  PTR eax+0x0,0xd7d7;
  mov BYTE  PTR eax+0x280,0xd7;
  ret
w4x6_6_ ENDP

PUBLIC w4x6_7_
w4x6_7_ PROC
  mov BYTE  PTR eax+0x1,0xd7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x500,0xd7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov BYTE  PTR eax+0xa01,0xd7;
  ret
w4x6_7_ ENDP

PUBLIC w4x6_8_
w4x6_8_ PROC
  mov BYTE  PTR eax+0x0,0xd7;
  mov BYTE  PTR eax+0x281,0xd7;
  mov BYTE  PTR eax+0x501,0xd7;
  mov BYTE  PTR eax+0x781,0xd7;
  mov BYTE  PTR eax+0xa00,0xd7;
  ret
w4x6_8_ ENDP

PUBLIC w4x6_9_
w4x6_9_ PROC
  mov BYTE  PTR eax+0x0,0xd7;
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x281,0xd7;
  mov WORD  PTR eax+0x500,0xd7d7;
  mov BYTE  PTR eax+0x502,0xd7;
  mov BYTE  PTR eax+0x781,0xd7;
  mov BYTE  PTR eax+0xa00,0xd7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_9_ ENDP

PUBLIC w4x6_10_
w4x6_10_ PROC
  mov BYTE  PTR eax+0x281,0xd7;
  mov WORD  PTR eax+0x500,0xd7d7;
  mov BYTE  PTR eax+0x502,0xd7;
  mov BYTE  PTR eax+0x781,0xd7;
  ret
w4x6_10_ ENDP

PUBLIC w4x6_11_
w4x6_11_ PROC
  mov WORD  PTR eax+0xa00,0xd7d7;
  mov BYTE  PTR eax+0xc80,0xd7;
  ret
w4x6_11_ ENDP

PUBLIC w4x6_12_
w4x6_12_ PROC
  mov WORD  PTR eax+0x500,0xd7d7;
  mov BYTE  PTR eax+0x502,0xd7;
  ret
w4x6_12_ ENDP

PUBLIC w4x6_13_
w4x6_13_ PROC
  mov BYTE  PTR eax+0xa01,0xd7;
  ret
w4x6_13_ ENDP

PUBLIC w4x6_14_
w4x6_14_ PROC
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov BYTE  PTR eax+0x501,0xd7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov BYTE  PTR eax+0xa00,0xd7;
  ret
w4x6_14_ ENDP

PUBLIC w4x6_15_
w4x6_15_ PROC
  mov WORD  PTR eax+0x1,0xd7d7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov BYTE  PTR eax+0x500,0xd7;
  mov BYTE  PTR eax+0x502,0xd7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov WORD  PTR eax+0xa00,0xd7d7;
  ret
w4x6_15_ ENDP

PUBLIC w4x6_16_
w4x6_16_ PROC
  mov BYTE  PTR eax+0x1,0xd7;
  mov WORD  PTR eax+0x280,0xd7d7;
  mov BYTE  PTR eax+0x501,0xd7;
  mov BYTE  PTR eax+0x781,0xd7;
  mov WORD  PTR eax+0xa00,0xd7d7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_16_ ENDP

PUBLIC w4x6_17_
w4x6_17_ PROC
  mov WORD  PTR eax+0x0,0xd7d7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov BYTE  PTR eax+0x501,0xd7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov WORD  PTR eax+0xa00,0xd7d7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_17_ ENDP

PUBLIC w4x6_18_
w4x6_18_ PROC
  mov WORD  PTR eax+0x0,0xd7d7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov BYTE  PTR eax+0x501,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov WORD  PTR eax+0xa00,0xd7d7;
  ret
w4x6_18_ ENDP

PUBLIC w4x6_19_
w4x6_19_ PROC
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov WORD  PTR eax+0x500,0xd7d7;
  mov BYTE  PTR eax+0x502,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_19_ ENDP

PUBLIC w4x6_20_
w4x6_20_ PROC
  mov WORD  PTR eax+0x0,0xd7d7;
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov WORD  PTR eax+0x500,0xd7d7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov WORD  PTR eax+0xa00,0xd7d7;
  ret
w4x6_20_ ENDP

PUBLIC w4x6_21_
w4x6_21_ PROC
  mov BYTE  PTR eax+0x1,0xd7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov WORD  PTR eax+0x500,0xd7d7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov BYTE  PTR eax+0xa01,0xd7;
  ret
w4x6_21_ ENDP

PUBLIC w4x6_22_
w4x6_22_ PROC
  mov WORD  PTR eax+0x0,0xd7d7;
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov WORD  PTR eax+0x501,0xd7d7;
  mov BYTE  PTR eax+0x781,0xd7;
  mov BYTE  PTR eax+0xa01,0xd7;
  ret
w4x6_22_ ENDP

PUBLIC w4x6_23_
w4x6_23_ PROC
  mov BYTE  PTR eax+0x1,0xd7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov BYTE  PTR eax+0x501,0xd7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov BYTE  PTR eax+0xa01,0xd7;
  ret
w4x6_23_ ENDP

PUBLIC w4x6_24_
w4x6_24_ PROC
  mov BYTE  PTR eax+0x1,0xd7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov WORD  PTR eax+0x501,0xd7d7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov BYTE  PTR eax+0xa01,0xd7;
  ret
w4x6_24_ ENDP

PUBLIC w4x6_25_
w4x6_25_ PROC
  mov BYTE  PTR eax+0x501,0xd7;
  mov BYTE  PTR eax+0xa01,0xd7;
  ret
w4x6_25_ ENDP

PUBLIC w4x6_26_
w4x6_26_ PROC
  mov BYTE  PTR eax+0x501,0xd7;
  mov WORD  PTR eax+0xa00,0xd7d7;
  mov BYTE  PTR eax+0xc80,0xd7;
  ret
w4x6_26_ ENDP

PUBLIC w4x6_27_
w4x6_27_ PROC
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x281,0xd7;
  mov BYTE  PTR eax+0x500,0xd7;
  mov BYTE  PTR eax+0x781,0xd7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_27_ ENDP

PUBLIC w4x6_28_
w4x6_28_ PROC
  mov WORD  PTR eax+0x500,0xd7d7;
  mov BYTE  PTR eax+0x502,0xd7;
  mov WORD  PTR eax+0xa00,0xd7d7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_28_ ENDP

PUBLIC w4x6_29_
w4x6_29_ PROC
  mov BYTE  PTR eax+0x0,0xd7;
  mov BYTE  PTR eax+0x281,0xd7;
  mov BYTE  PTR eax+0x502,0xd7;
  mov BYTE  PTR eax+0x781,0xd7;
  mov BYTE  PTR eax+0xa00,0xd7;
  ret
w4x6_29_ ENDP

PUBLIC w4x6_30_
w4x6_30_ PROC
  mov WORD  PTR eax+0x0,0xd7d7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov BYTE  PTR eax+0x501,0xd7;
  mov BYTE  PTR eax+0xa01,0xd7;
  ret
w4x6_30_ ENDP

PUBLIC w4x6_31_
w4x6_31_ PROC
  mov WORD  PTR eax+0x0,0xd7d7;
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov BYTE  PTR eax+0x500,0xd7;
  mov BYTE  PTR eax+0x502,0xd7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov WORD  PTR eax+0xa00,0xd7d7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_31_ ENDP

PUBLIC w4x6_32_
w4x6_32_ PROC
  mov BYTE  PTR eax+0x1,0xd7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov WORD  PTR eax+0x500,0xd7d7;
  mov BYTE  PTR eax+0x502,0xd7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov BYTE  PTR eax+0xa00,0xd7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_32_ ENDP

PUBLIC w4x6_33_
w4x6_33_ PROC
  mov WORD  PTR eax+0x0,0xd7d7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov WORD  PTR eax+0x500,0xd7d7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov WORD  PTR eax+0xa00,0xd7d7;
  ret
w4x6_33_ ENDP

PUBLIC w4x6_34_
w4x6_34_ PROC
  mov WORD  PTR eax+0x1,0xd7d7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x500,0xd7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov WORD  PTR eax+0xa01,0xd7d7;
  ret
w4x6_34_ ENDP

PUBLIC w4x6_35_
w4x6_35_ PROC
  mov WORD  PTR eax+0x0,0xd7d7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov BYTE  PTR eax+0x500,0xd7;
  mov BYTE  PTR eax+0x502,0xd7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov WORD  PTR eax+0xa00,0xd7d7;
  ret
w4x6_35_ ENDP

PUBLIC w4x6_36_
w4x6_36_ PROC
  mov WORD  PTR eax+0x0,0xd7d7;
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov WORD  PTR eax+0x500,0xd7d7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov WORD  PTR eax+0xa00,0xd7d7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_36_ ENDP

PUBLIC w4x6_37_
w4x6_37_ PROC
  mov WORD  PTR eax+0x0,0xd7d7;
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov WORD  PTR eax+0x500,0xd7d7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov BYTE  PTR eax+0xa00,0xd7;
  ret
w4x6_37_ ENDP

PUBLIC w4x6_38_
w4x6_38_ PROC
  mov WORD  PTR eax+0x1,0xd7d7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x500,0xd7;
  mov BYTE  PTR eax+0x502,0xd7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov WORD  PTR eax+0xa01,0xd7d7;
  ret
w4x6_38_ ENDP

PUBLIC w4x6_39_
w4x6_39_ PROC
  mov BYTE  PTR eax+0x0,0xd7;
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov WORD  PTR eax+0x500,0xd7d7;
  mov BYTE  PTR eax+0x502,0xd7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov BYTE  PTR eax+0xa00,0xd7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_39_ ENDP

PUBLIC w4x6_40_
w4x6_40_ PROC
  mov WORD  PTR eax+0x0,0xd7d7;
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x281,0xd7;
  mov BYTE  PTR eax+0x501,0xd7;
  mov BYTE  PTR eax+0x781,0xd7;
  mov WORD  PTR eax+0xa00,0xd7d7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_40_ ENDP

PUBLIC w4x6_41_
w4x6_41_ PROC
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov BYTE  PTR eax+0x502,0xd7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov BYTE  PTR eax+0xa01,0xd7;
  ret
w4x6_41_ ENDP

PUBLIC w4x6_42_
w4x6_42_ PROC
  mov BYTE  PTR eax+0x0,0xd7;
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov WORD  PTR eax+0x500,0xd7d7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov BYTE  PTR eax+0xa00,0xd7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_42_ ENDP

PUBLIC w4x6_43_
w4x6_43_ PROC
  mov BYTE  PTR eax+0x0,0xd7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x500,0xd7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov WORD  PTR eax+0xa00,0xd7d7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_43_ ENDP

PUBLIC w4x6_44_
w4x6_44_ PROC
  mov BYTE  PTR eax+0x0,0xd7;
  mov BYTE  PTR eax+0x2,0xd7;
  mov WORD  PTR eax+0x280,0xd7d7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov WORD  PTR eax+0x500,0xd7d7;
  mov BYTE  PTR eax+0x502,0xd7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov BYTE  PTR eax+0xa00,0xd7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_44_ ENDP

PUBLIC w4x6_45_
w4x6_45_ PROC
  mov BYTE  PTR eax+0x0,0xd7;
  mov BYTE  PTR eax+0x2,0xd7;
  mov WORD  PTR eax+0x280,0xd7d7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov BYTE  PTR eax+0x500,0xd7;
  mov BYTE  PTR eax+0x502,0xd7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov BYTE  PTR eax+0xa00,0xd7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_45_ ENDP

PUBLIC w4x6_46_
w4x6_46_ PROC
  mov BYTE  PTR eax+0x1,0xd7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov BYTE  PTR eax+0x500,0xd7;
  mov BYTE  PTR eax+0x502,0xd7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov BYTE  PTR eax+0xa01,0xd7;
  ret
w4x6_46_ ENDP

PUBLIC w4x6_47_
w4x6_47_ PROC
  mov WORD  PTR eax+0x0,0xd7d7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov WORD  PTR eax+0x500,0xd7d7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov BYTE  PTR eax+0xa00,0xd7;
  ret
w4x6_47_ ENDP

PUBLIC w4x6_48_
w4x6_48_ PROC
  mov BYTE  PTR eax+0x1,0xd7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov BYTE  PTR eax+0x500,0xd7;
  mov BYTE  PTR eax+0x502,0xd7;
  mov WORD  PTR eax+0x780,0xd7d7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov WORD  PTR eax+0xa01,0xd7d7;
  ret
w4x6_48_ ENDP

PUBLIC w4x6_49_
w4x6_49_ PROC
  mov WORD  PTR eax+0x0,0xd7d7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov WORD  PTR eax+0x500,0xd7d7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov BYTE  PTR eax+0xa00,0xd7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_49_ ENDP

PUBLIC w4x6_50_
w4x6_50_ PROC
  mov WORD  PTR eax+0x1,0xd7d7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov WORD  PTR eax+0x500,0xd7d7;
  mov BYTE  PTR eax+0x502,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov WORD  PTR eax+0xa00,0xd7d7;
  ret
w4x6_50_ ENDP

PUBLIC w4x6_51_
w4x6_51_ PROC
  mov WORD  PTR eax+0x0,0xd7d7;
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x281,0xd7;
  mov BYTE  PTR eax+0x501,0xd7;
  mov BYTE  PTR eax+0x781,0xd7;
  mov BYTE  PTR eax+0xa01,0xd7;
  ret
w4x6_51_ ENDP

PUBLIC w4x6_52_
w4x6_52_ PROC
  mov BYTE  PTR eax+0x0,0xd7;
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov BYTE  PTR eax+0x500,0xd7;
  mov BYTE  PTR eax+0x502,0xd7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov WORD  PTR eax+0xa00,0xd7d7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_52_ ENDP

PUBLIC w4x6_53_
w4x6_53_ PROC
  mov BYTE  PTR eax+0x0,0xd7;
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov BYTE  PTR eax+0x500,0xd7;
  mov BYTE  PTR eax+0x502,0xd7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov BYTE  PTR eax+0xa01,0xd7;
  ret
w4x6_53_ ENDP

PUBLIC w4x6_54_
w4x6_54_ PROC
  mov BYTE  PTR eax+0x0,0xd7;
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov WORD  PTR eax+0x500,0xd7d7;
  mov BYTE  PTR eax+0x502,0xd7;
  mov WORD  PTR eax+0x780,0xd7d7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov BYTE  PTR eax+0xa00,0xd7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_54_ ENDP

PUBLIC w4x6_55_
w4x6_55_ PROC
  mov BYTE  PTR eax+0x0,0xd7;
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov BYTE  PTR eax+0x501,0xd7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov BYTE  PTR eax+0xa00,0xd7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_55_ ENDP

PUBLIC w4x6_56_
w4x6_56_ PROC
  mov BYTE  PTR eax+0x0,0xd7;
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov BYTE  PTR eax+0x501,0xd7;
  mov BYTE  PTR eax+0x781,0xd7;
  mov BYTE  PTR eax+0xa01,0xd7;
  ret
w4x6_56_ ENDP

PUBLIC w4x6_57_
w4x6_57_ PROC
  mov WORD  PTR eax+0x0,0xd7d7;
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov BYTE  PTR eax+0x501,0xd7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov WORD  PTR eax+0xa00,0xd7d7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_57_ ENDP

PUBLIC w4x6_58_
w4x6_58_ PROC
  mov WORD  PTR eax+0x0,0xd7d7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x500,0xd7;
  mov BYTE  PTR eax+0x780,0xd7;
  mov WORD  PTR eax+0xa00,0xd7d7;
  ret
w4x6_58_ ENDP

PUBLIC w4x6_59_
w4x6_59_ PROC
  mov BYTE  PTR eax+0x0,0xd7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x501,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_59_ ENDP

PUBLIC w4x6_60_
w4x6_60_ PROC
  mov WORD  PTR eax+0x0,0xd7d7;
  mov BYTE  PTR eax+0x281,0xd7;
  mov BYTE  PTR eax+0x501,0xd7;
  mov BYTE  PTR eax+0x781,0xd7;
  mov WORD  PTR eax+0xa00,0xd7d7;
  ret
w4x6_60_ ENDP

PUBLIC w4x6_61_
w4x6_61_ PROC
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x281,0xd7;
  mov BYTE  PTR eax+0x283,0xd7;
  ret
w4x6_61_ ENDP

PUBLIC w4x6_62_
w4x6_62_ PROC
  mov DWORD PTR eax+0xc80,0xd7d7d7d7;
  ret
w4x6_62_ ENDP

PUBLIC w4x6_63_
w4x6_63_ PROC
  mov WORD  PTR eax+0x1,0xd7d7;
  mov BYTE  PTR eax+0x282,0xd7;
  ret
w4x6_63_ ENDP

PUBLIC w4x6_64_
w4x6_64_ PROC
  mov WORD  PTR eax+0x502,0xd7d7;
  mov BYTE  PTR eax+0x781,0xd7;
  mov BYTE  PTR eax+0x783,0xd7;
  mov WORD  PTR eax+0xa01,0xd7d7;
  mov BYTE  PTR eax+0xa03,0xd7;
  ret
w4x6_64_ ENDP

PUBLIC w4x6_65_
w4x6_65_ PROC
  mov BYTE  PTR eax+0x1,0xd7;
  mov BYTE  PTR eax+0x281,0xd7;
  mov WORD  PTR eax+0x501,0xd7d7;
  mov BYTE  PTR eax+0x781,0xd7;
  mov BYTE  PTR eax+0x783,0xd7;
  mov WORD  PTR eax+0xa01,0xd7d7;
  ret
w4x6_65_ ENDP

PUBLIC w4x6_66_
w4x6_66_ PROC
  mov WORD  PTR eax+0x502,0xd7d7;
  mov BYTE  PTR eax+0x781,0xd7;
  mov WORD  PTR eax+0xa02,0xd7d7;
  ret
w4x6_66_ ENDP

PUBLIC w4x6_67_
w4x6_67_ PROC
  mov BYTE  PTR eax+0x3,0xd7;
  mov BYTE  PTR eax+0x283,0xd7;
  mov WORD  PTR eax+0x502,0xd7d7;
  mov BYTE  PTR eax+0x781,0xd7;
  mov BYTE  PTR eax+0x783,0xd7;
  mov WORD  PTR eax+0xa02,0xd7d7;
  ret
w4x6_67_ ENDP

PUBLIC w4x6_68_
w4x6_68_ PROC
  mov WORD  PTR eax+0x501,0xd7d7;
  mov BYTE  PTR eax+0x503,0xd7;
  mov WORD  PTR eax+0x781,0xd7d7;
  mov WORD  PTR eax+0xa02,0xd7d7;
  ret
w4x6_68_ ENDP

PUBLIC w4x6_69_
w4x6_69_ PROC
  mov BYTE  PTR eax+0x3,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov WORD  PTR eax+0x501,0xd7d7;
  mov BYTE  PTR eax+0x503,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_69_ ENDP

PUBLIC w4x6_70_
w4x6_70_ PROC
  mov WORD  PTR eax+0x501,0xd7d7;
  mov BYTE  PTR eax+0x503,0xd7;
  mov BYTE  PTR eax+0x781,0xd7;
  mov BYTE  PTR eax+0x783,0xd7;
  mov BYTE  PTR eax+0xa03,0xd7;
  mov WORD  PTR eax+0xc81,0xd7d7;
  mov BYTE  PTR eax+0xc83,0xd7;
  ret
w4x6_70_ ENDP

PUBLIC w4x6_71_
w4x6_71_ PROC
  mov BYTE  PTR eax+0x1,0xd7;
  mov BYTE  PTR eax+0x281,0xd7;
  mov WORD  PTR eax+0x501,0xd7d7;
  mov BYTE  PTR eax+0x781,0xd7;
  mov BYTE  PTR eax+0x783,0xd7;
  mov BYTE  PTR eax+0xa01,0xd7;
  mov BYTE  PTR eax+0xa03,0xd7;
  ret
w4x6_71_ ENDP

PUBLIC w4x6_72_
w4x6_72_ PROC
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x502,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_72_ ENDP

PUBLIC w4x6_73_
w4x6_73_ PROC
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x502,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov BYTE  PTR eax+0xa02,0xd7;
  mov WORD  PTR eax+0xc81,0xd7d7;
  ret
w4x6_73_ ENDP

PUBLIC w4x6_74_
w4x6_74_ PROC
  mov BYTE  PTR eax+0x1,0xd7;
  mov BYTE  PTR eax+0x281,0xd7;
  mov BYTE  PTR eax+0x501,0xd7;
  mov BYTE  PTR eax+0x503,0xd7;
  mov WORD  PTR eax+0x781,0xd7d7;
  mov BYTE  PTR eax+0xa01,0xd7;
  mov BYTE  PTR eax+0xa03,0xd7;
  ret
w4x6_74_ ENDP

PUBLIC w4x6_75_
w4x6_75_ PROC
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov BYTE  PTR eax+0x502,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_75_ ENDP

PUBLIC w4x6_76_
w4x6_76_ PROC
  mov WORD  PTR eax+0x501,0xd7d7;
  mov BYTE  PTR eax+0x503,0xd7;
  mov WORD  PTR eax+0x781,0xd7d7;
  mov BYTE  PTR eax+0x783,0xd7;
  mov BYTE  PTR eax+0xa01,0xd7;
  mov BYTE  PTR eax+0xa03,0xd7;
  ret
w4x6_76_ ENDP

PUBLIC w4x6_77_
w4x6_77_ PROC
  mov WORD  PTR eax+0x501,0xd7d7;
  mov BYTE  PTR eax+0x781,0xd7;
  mov BYTE  PTR eax+0x783,0xd7;
  mov BYTE  PTR eax+0xa01,0xd7;
  mov BYTE  PTR eax+0xa03,0xd7;
  ret
w4x6_77_ ENDP

PUBLIC w4x6_78_
w4x6_78_ PROC
  mov BYTE  PTR eax+0x502,0xd7;
  mov BYTE  PTR eax+0x781,0xd7;
  mov BYTE  PTR eax+0x783,0xd7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_78_ ENDP

PUBLIC w4x6_79_
w4x6_79_ PROC
  mov WORD  PTR eax+0x501,0xd7d7;
  mov BYTE  PTR eax+0x781,0xd7;
  mov BYTE  PTR eax+0x783,0xd7;
  mov WORD  PTR eax+0xa01,0xd7d7;
  mov BYTE  PTR eax+0xc81,0xd7;
  ret
w4x6_79_ ENDP

PUBLIC w4x6_80_
w4x6_80_ PROC
  mov WORD  PTR eax+0x502,0xd7d7;
  mov BYTE  PTR eax+0x781,0xd7;
  mov BYTE  PTR eax+0x783,0xd7;
  mov WORD  PTR eax+0xa02,0xd7d7;
  mov BYTE  PTR eax+0xc83,0xd7;
  ret
w4x6_80_ ENDP

PUBLIC w4x6_81_
w4x6_81_ PROC
  mov WORD  PTR eax+0x501,0xd7d7;
  mov BYTE  PTR eax+0x781,0xd7;
  mov BYTE  PTR eax+0xa01,0xd7;
  ret
w4x6_81_ ENDP

PUBLIC w4x6_82_
w4x6_82_ PROC
  mov WORD  PTR eax+0x502,0xd7d7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov WORD  PTR eax+0xa01,0xd7d7;
  ret
w4x6_82_ ENDP

PUBLIC w4x6_83_
w4x6_83_ PROC
  mov BYTE  PTR eax+0x282,0xd7;
  mov WORD  PTR eax+0x501,0xd7d7;
  mov BYTE  PTR eax+0x503,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov WORD  PTR eax+0xa02,0xd7d7;
  ret
w4x6_83_ ENDP

PUBLIC w4x6_84_
w4x6_84_ PROC
  mov BYTE  PTR eax+0x501,0xd7;
  mov BYTE  PTR eax+0x503,0xd7;
  mov BYTE  PTR eax+0x781,0xd7;
  mov BYTE  PTR eax+0x783,0xd7;
  mov WORD  PTR eax+0xa01,0xd7d7;
  mov BYTE  PTR eax+0xa03,0xd7;
  ret
w4x6_84_ ENDP

PUBLIC w4x6_85_
w4x6_85_ PROC
  mov BYTE  PTR eax+0x501,0xd7;
  mov BYTE  PTR eax+0x503,0xd7;
  mov BYTE  PTR eax+0x781,0xd7;
  mov BYTE  PTR eax+0x783,0xd7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_85_ ENDP

PUBLIC w4x6_86_
w4x6_86_ PROC
  mov BYTE  PTR eax+0x501,0xd7;
  mov BYTE  PTR eax+0x503,0xd7;
  mov WORD  PTR eax+0x781,0xd7d7;
  mov BYTE  PTR eax+0x783,0xd7;
  mov WORD  PTR eax+0xa01,0xd7d7;
  mov BYTE  PTR eax+0xa03,0xd7;
  ret
w4x6_86_ ENDP

PUBLIC w4x6_87_
w4x6_87_ PROC
  mov BYTE  PTR eax+0x501,0xd7;
  mov BYTE  PTR eax+0x503,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov BYTE  PTR eax+0xa01,0xd7;
  mov BYTE  PTR eax+0xa03,0xd7;
  ret
w4x6_87_ ENDP

PUBLIC w4x6_88_
w4x6_88_ PROC
  mov BYTE  PTR eax+0x501,0xd7;
  mov BYTE  PTR eax+0x503,0xd7;
  mov BYTE  PTR eax+0x781,0xd7;
  mov BYTE  PTR eax+0x783,0xd7;
  mov BYTE  PTR eax+0xa02,0xd7;
  mov BYTE  PTR eax+0xc81,0xd7;
  ret
w4x6_88_ ENDP

PUBLIC w4x6_89_
w4x6_89_ PROC
  mov WORD  PTR eax+0x501,0xd7d7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov WORD  PTR eax+0xa02,0xd7d7;
  ret
w4x6_89_ ENDP

PUBLIC w4x6_90_
w4x6_90_ PROC
  mov WORD  PTR eax+0x2,0xd7d7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov WORD  PTR eax+0x501,0xd7d7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov WORD  PTR eax+0xa02,0xd7d7;
  ret
w4x6_90_ ENDP

PUBLIC w4x6_91_
w4x6_91_ PROC
  mov BYTE  PTR eax+0x2,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov BYTE  PTR eax+0x502,0xd7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov BYTE  PTR eax+0xa02,0xd7;
  ret
w4x6_91_ ENDP

PUBLIC w4x6_92_
w4x6_92_ PROC
  mov WORD  PTR eax+0x1,0xd7d7;
  mov BYTE  PTR eax+0x282,0xd7;
  mov WORD  PTR eax+0x502,0xd7d7;
  mov BYTE  PTR eax+0x782,0xd7;
  mov WORD  PTR eax+0xa01,0xd7d7;
  ret
w4x6_92_ ENDP

PUBLIC w4x6_93_
w4x6_93_ PROC
  mov BYTE  PTR eax+0x1,0xd7;
  mov BYTE  PTR eax+0x3,0xd7;
  mov BYTE  PTR eax+0x280,0xd7;
  mov BYTE  PTR eax+0x282,0xd7;
  ret
w4x6_93_ ENDP

_TEXT ENDS
END
