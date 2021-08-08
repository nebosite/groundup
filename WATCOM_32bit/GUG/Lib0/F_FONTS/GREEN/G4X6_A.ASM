; Compiled Sprites output from spr2asm
;  command line : spr2asm g4x6 g4x6.spr 
;  entry point name : g4x6
;  asm output file  : g4x6_A.ASM
;  c   output file  : g4x6_C.C
;  spr input  file  : g4x6.spr
;
.386
DGROUP group _DATA
_DATA  segment 'DATA'
_DATA  ends
_TEXT  segment BYTE PUBLIC USE32 'CODE'
       ASSUME CS:_TEXT
       ASSUME DS:DGROUN

PUBLIC g4x6_0_
g4x6_0_ PROC
  mov BYTE  PTR eax+0x1,0x1e;
  mov BYTE  PTR eax+0x281,0x1e;
  mov BYTE  PTR eax+0x501,0x1e;
  mov BYTE  PTR eax+0xa01,0x1e;
  ret
g4x6_0_ ENDP

PUBLIC g4x6_1_
g4x6_1_ PROC
  mov BYTE  PTR eax+0x0,0x1e;
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  ret
g4x6_1_ ENDP

PUBLIC g4x6_2_
g4x6_2_ PROC
  mov BYTE  PTR eax+0x0,0x1e;
  mov BYTE  PTR eax+0x2,0x1e;
  mov WORD  PTR eax+0x280,0x1e1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov BYTE  PTR eax+0x500,0x1e;
  mov BYTE  PTR eax+0x502,0x1e;
  mov WORD  PTR eax+0x780,0x1e1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov BYTE  PTR eax+0xa00,0x1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_2_ ENDP

PUBLIC g4x6_3_
g4x6_3_ PROC
  mov BYTE  PTR eax+0x1,0x1e;
  mov WORD  PTR eax+0x281,0x1e1e;
  mov WORD  PTR eax+0x500,0x1e1e;
  mov WORD  PTR eax+0x781,0x1e1e;
  mov WORD  PTR eax+0xa00,0x1e1e;
  mov BYTE  PTR eax+0xc81,0x1e;
  ret
g4x6_3_ ENDP

PUBLIC g4x6_4_
g4x6_4_ PROC
  mov BYTE  PTR eax+0x0,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov BYTE  PTR eax+0x501,0x1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_4_ ENDP

PUBLIC g4x6_5_
g4x6_5_ PROC
  mov BYTE  PTR eax+0x1,0x1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov WORD  PTR eax+0x501,0x1e1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov WORD  PTR eax+0xa00,0x1e1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_5_ ENDP

PUBLIC g4x6_6_
g4x6_6_ PROC
  mov WORD  PTR eax+0x0,0x1e1e;
  mov BYTE  PTR eax+0x280,0x1e;
  ret
g4x6_6_ ENDP

PUBLIC g4x6_7_
g4x6_7_ PROC
  mov BYTE  PTR eax+0x1,0x1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x500,0x1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov BYTE  PTR eax+0xa01,0x1e;
  ret
g4x6_7_ ENDP

PUBLIC g4x6_8_
g4x6_8_ PROC
  mov BYTE  PTR eax+0x0,0x1e;
  mov BYTE  PTR eax+0x281,0x1e;
  mov BYTE  PTR eax+0x501,0x1e;
  mov BYTE  PTR eax+0x781,0x1e;
  mov BYTE  PTR eax+0xa00,0x1e;
  ret
g4x6_8_ ENDP

PUBLIC g4x6_9_
g4x6_9_ PROC
  mov BYTE  PTR eax+0x0,0x1e;
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x281,0x1e;
  mov WORD  PTR eax+0x500,0x1e1e;
  mov BYTE  PTR eax+0x502,0x1e;
  mov BYTE  PTR eax+0x781,0x1e;
  mov BYTE  PTR eax+0xa00,0x1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_9_ ENDP

PUBLIC g4x6_10_
g4x6_10_ PROC
  mov BYTE  PTR eax+0x281,0x1e;
  mov WORD  PTR eax+0x500,0x1e1e;
  mov BYTE  PTR eax+0x502,0x1e;
  mov BYTE  PTR eax+0x781,0x1e;
  ret
g4x6_10_ ENDP

PUBLIC g4x6_11_
g4x6_11_ PROC
  mov WORD  PTR eax+0xa00,0x1e1e;
  mov BYTE  PTR eax+0xc80,0x1e;
  ret
g4x6_11_ ENDP

PUBLIC g4x6_12_
g4x6_12_ PROC
  mov WORD  PTR eax+0x500,0x1e1e;
  mov BYTE  PTR eax+0x502,0x1e;
  ret
g4x6_12_ ENDP

PUBLIC g4x6_13_
g4x6_13_ PROC
  mov BYTE  PTR eax+0xa01,0x1e;
  ret
g4x6_13_ ENDP

PUBLIC g4x6_14_
g4x6_14_ PROC
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov BYTE  PTR eax+0x501,0x1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov BYTE  PTR eax+0xa00,0x1e;
  ret
g4x6_14_ ENDP

PUBLIC g4x6_15_
g4x6_15_ PROC
  mov WORD  PTR eax+0x1,0x1e1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov BYTE  PTR eax+0x500,0x1e;
  mov BYTE  PTR eax+0x502,0x1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov WORD  PTR eax+0xa00,0x1e1e;
  ret
g4x6_15_ ENDP

PUBLIC g4x6_16_
g4x6_16_ PROC
  mov BYTE  PTR eax+0x1,0x1e;
  mov WORD  PTR eax+0x280,0x1e1e;
  mov BYTE  PTR eax+0x501,0x1e;
  mov BYTE  PTR eax+0x781,0x1e;
  mov WORD  PTR eax+0xa00,0x1e1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_16_ ENDP

PUBLIC g4x6_17_
g4x6_17_ PROC
  mov WORD  PTR eax+0x0,0x1e1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov BYTE  PTR eax+0x501,0x1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov WORD  PTR eax+0xa00,0x1e1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_17_ ENDP

PUBLIC g4x6_18_
g4x6_18_ PROC
  mov WORD  PTR eax+0x0,0x1e1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov BYTE  PTR eax+0x501,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov WORD  PTR eax+0xa00,0x1e1e;
  ret
g4x6_18_ ENDP

PUBLIC g4x6_19_
g4x6_19_ PROC
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov WORD  PTR eax+0x500,0x1e1e;
  mov BYTE  PTR eax+0x502,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_19_ ENDP

PUBLIC g4x6_20_
g4x6_20_ PROC
  mov WORD  PTR eax+0x0,0x1e1e;
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov WORD  PTR eax+0x500,0x1e1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov WORD  PTR eax+0xa00,0x1e1e;
  ret
g4x6_20_ ENDP

PUBLIC g4x6_21_
g4x6_21_ PROC
  mov BYTE  PTR eax+0x1,0x1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov WORD  PTR eax+0x500,0x1e1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov BYTE  PTR eax+0xa01,0x1e;
  ret
g4x6_21_ ENDP

PUBLIC g4x6_22_
g4x6_22_ PROC
  mov WORD  PTR eax+0x0,0x1e1e;
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov WORD  PTR eax+0x501,0x1e1e;
  mov BYTE  PTR eax+0x781,0x1e;
  mov BYTE  PTR eax+0xa01,0x1e;
  ret
g4x6_22_ ENDP

PUBLIC g4x6_23_
g4x6_23_ PROC
  mov BYTE  PTR eax+0x1,0x1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov BYTE  PTR eax+0x501,0x1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov BYTE  PTR eax+0xa01,0x1e;
  ret
g4x6_23_ ENDP

PUBLIC g4x6_24_
g4x6_24_ PROC
  mov BYTE  PTR eax+0x1,0x1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov WORD  PTR eax+0x501,0x1e1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov BYTE  PTR eax+0xa01,0x1e;
  ret
g4x6_24_ ENDP

PUBLIC g4x6_25_
g4x6_25_ PROC
  mov BYTE  PTR eax+0x501,0x1e;
  mov BYTE  PTR eax+0xa01,0x1e;
  ret
g4x6_25_ ENDP

PUBLIC g4x6_26_
g4x6_26_ PROC
  mov BYTE  PTR eax+0x501,0x1e;
  mov WORD  PTR eax+0xa00,0x1e1e;
  mov BYTE  PTR eax+0xc80,0x1e;
  ret
g4x6_26_ ENDP

PUBLIC g4x6_27_
g4x6_27_ PROC
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x281,0x1e;
  mov BYTE  PTR eax+0x500,0x1e;
  mov BYTE  PTR eax+0x781,0x1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_27_ ENDP

PUBLIC g4x6_28_
g4x6_28_ PROC
  mov WORD  PTR eax+0x500,0x1e1e;
  mov BYTE  PTR eax+0x502,0x1e;
  mov WORD  PTR eax+0xa00,0x1e1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_28_ ENDP

PUBLIC g4x6_29_
g4x6_29_ PROC
  mov BYTE  PTR eax+0x0,0x1e;
  mov BYTE  PTR eax+0x281,0x1e;
  mov BYTE  PTR eax+0x502,0x1e;
  mov BYTE  PTR eax+0x781,0x1e;
  mov BYTE  PTR eax+0xa00,0x1e;
  ret
g4x6_29_ ENDP

PUBLIC g4x6_30_
g4x6_30_ PROC
  mov WORD  PTR eax+0x0,0x1e1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov BYTE  PTR eax+0x501,0x1e;
  mov BYTE  PTR eax+0xa01,0x1e;
  ret
g4x6_30_ ENDP

PUBLIC g4x6_31_
g4x6_31_ PROC
  mov WORD  PTR eax+0x0,0x1e1e;
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov BYTE  PTR eax+0x500,0x1e;
  mov BYTE  PTR eax+0x502,0x1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov WORD  PTR eax+0xa00,0x1e1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_31_ ENDP

PUBLIC g4x6_32_
g4x6_32_ PROC
  mov BYTE  PTR eax+0x1,0x1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov WORD  PTR eax+0x500,0x1e1e;
  mov BYTE  PTR eax+0x502,0x1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov BYTE  PTR eax+0xa00,0x1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_32_ ENDP

PUBLIC g4x6_33_
g4x6_33_ PROC
  mov WORD  PTR eax+0x0,0x1e1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov WORD  PTR eax+0x500,0x1e1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov WORD  PTR eax+0xa00,0x1e1e;
  ret
g4x6_33_ ENDP

PUBLIC g4x6_34_
g4x6_34_ PROC
  mov WORD  PTR eax+0x1,0x1e1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x500,0x1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov WORD  PTR eax+0xa01,0x1e1e;
  ret
g4x6_34_ ENDP

PUBLIC g4x6_35_
g4x6_35_ PROC
  mov WORD  PTR eax+0x0,0x1e1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov BYTE  PTR eax+0x500,0x1e;
  mov BYTE  PTR eax+0x502,0x1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov WORD  PTR eax+0xa00,0x1e1e;
  ret
g4x6_35_ ENDP

PUBLIC g4x6_36_
g4x6_36_ PROC
  mov WORD  PTR eax+0x0,0x1e1e;
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov WORD  PTR eax+0x500,0x1e1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov WORD  PTR eax+0xa00,0x1e1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_36_ ENDP

PUBLIC g4x6_37_
g4x6_37_ PROC
  mov WORD  PTR eax+0x0,0x1e1e;
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov WORD  PTR eax+0x500,0x1e1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov BYTE  PTR eax+0xa00,0x1e;
  ret
g4x6_37_ ENDP

PUBLIC g4x6_38_
g4x6_38_ PROC
  mov WORD  PTR eax+0x1,0x1e1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x500,0x1e;
  mov BYTE  PTR eax+0x502,0x1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov WORD  PTR eax+0xa01,0x1e1e;
  ret
g4x6_38_ ENDP

PUBLIC g4x6_39_
g4x6_39_ PROC
  mov BYTE  PTR eax+0x0,0x1e;
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov WORD  PTR eax+0x500,0x1e1e;
  mov BYTE  PTR eax+0x502,0x1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov BYTE  PTR eax+0xa00,0x1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_39_ ENDP

PUBLIC g4x6_40_
g4x6_40_ PROC
  mov WORD  PTR eax+0x0,0x1e1e;
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x281,0x1e;
  mov BYTE  PTR eax+0x501,0x1e;
  mov BYTE  PTR eax+0x781,0x1e;
  mov WORD  PTR eax+0xa00,0x1e1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_40_ ENDP

PUBLIC g4x6_41_
g4x6_41_ PROC
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov BYTE  PTR eax+0x502,0x1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov BYTE  PTR eax+0xa01,0x1e;
  ret
g4x6_41_ ENDP

PUBLIC g4x6_42_
g4x6_42_ PROC
  mov BYTE  PTR eax+0x0,0x1e;
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov WORD  PTR eax+0x500,0x1e1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov BYTE  PTR eax+0xa00,0x1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_42_ ENDP

PUBLIC g4x6_43_
g4x6_43_ PROC
  mov BYTE  PTR eax+0x0,0x1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x500,0x1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov WORD  PTR eax+0xa00,0x1e1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_43_ ENDP

PUBLIC g4x6_44_
g4x6_44_ PROC
  mov BYTE  PTR eax+0x0,0x1e;
  mov BYTE  PTR eax+0x2,0x1e;
  mov WORD  PTR eax+0x280,0x1e1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov WORD  PTR eax+0x500,0x1e1e;
  mov BYTE  PTR eax+0x502,0x1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov BYTE  PTR eax+0xa00,0x1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_44_ ENDP

PUBLIC g4x6_45_
g4x6_45_ PROC
  mov BYTE  PTR eax+0x0,0x1e;
  mov BYTE  PTR eax+0x2,0x1e;
  mov WORD  PTR eax+0x280,0x1e1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov BYTE  PTR eax+0x500,0x1e;
  mov BYTE  PTR eax+0x502,0x1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov BYTE  PTR eax+0xa00,0x1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_45_ ENDP

PUBLIC g4x6_46_
g4x6_46_ PROC
  mov BYTE  PTR eax+0x1,0x1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov BYTE  PTR eax+0x500,0x1e;
  mov BYTE  PTR eax+0x502,0x1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov BYTE  PTR eax+0xa01,0x1e;
  ret
g4x6_46_ ENDP

PUBLIC g4x6_47_
g4x6_47_ PROC
  mov WORD  PTR eax+0x0,0x1e1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov WORD  PTR eax+0x500,0x1e1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov BYTE  PTR eax+0xa00,0x1e;
  ret
g4x6_47_ ENDP

PUBLIC g4x6_48_
g4x6_48_ PROC
  mov BYTE  PTR eax+0x1,0x1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov BYTE  PTR eax+0x500,0x1e;
  mov BYTE  PTR eax+0x502,0x1e;
  mov WORD  PTR eax+0x780,0x1e1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov WORD  PTR eax+0xa01,0x1e1e;
  ret
g4x6_48_ ENDP

PUBLIC g4x6_49_
g4x6_49_ PROC
  mov WORD  PTR eax+0x0,0x1e1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov WORD  PTR eax+0x500,0x1e1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov BYTE  PTR eax+0xa00,0x1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_49_ ENDP

PUBLIC g4x6_50_
g4x6_50_ PROC
  mov WORD  PTR eax+0x1,0x1e1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov WORD  PTR eax+0x500,0x1e1e;
  mov BYTE  PTR eax+0x502,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov WORD  PTR eax+0xa00,0x1e1e;
  ret
g4x6_50_ ENDP

PUBLIC g4x6_51_
g4x6_51_ PROC
  mov WORD  PTR eax+0x0,0x1e1e;
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x281,0x1e;
  mov BYTE  PTR eax+0x501,0x1e;
  mov BYTE  PTR eax+0x781,0x1e;
  mov BYTE  PTR eax+0xa01,0x1e;
  ret
g4x6_51_ ENDP

PUBLIC g4x6_52_
g4x6_52_ PROC
  mov BYTE  PTR eax+0x0,0x1e;
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov BYTE  PTR eax+0x500,0x1e;
  mov BYTE  PTR eax+0x502,0x1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov WORD  PTR eax+0xa00,0x1e1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_52_ ENDP

PUBLIC g4x6_53_
g4x6_53_ PROC
  mov BYTE  PTR eax+0x0,0x1e;
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov BYTE  PTR eax+0x500,0x1e;
  mov BYTE  PTR eax+0x502,0x1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov BYTE  PTR eax+0xa01,0x1e;
  ret
g4x6_53_ ENDP

PUBLIC g4x6_54_
g4x6_54_ PROC
  mov BYTE  PTR eax+0x0,0x1e;
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov WORD  PTR eax+0x500,0x1e1e;
  mov BYTE  PTR eax+0x502,0x1e;
  mov WORD  PTR eax+0x780,0x1e1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov BYTE  PTR eax+0xa00,0x1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_54_ ENDP

PUBLIC g4x6_55_
g4x6_55_ PROC
  mov BYTE  PTR eax+0x0,0x1e;
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov BYTE  PTR eax+0x501,0x1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov BYTE  PTR eax+0xa00,0x1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_55_ ENDP

PUBLIC g4x6_56_
g4x6_56_ PROC
  mov BYTE  PTR eax+0x0,0x1e;
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov BYTE  PTR eax+0x501,0x1e;
  mov BYTE  PTR eax+0x781,0x1e;
  mov BYTE  PTR eax+0xa01,0x1e;
  ret
g4x6_56_ ENDP

PUBLIC g4x6_57_
g4x6_57_ PROC
  mov WORD  PTR eax+0x0,0x1e1e;
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov BYTE  PTR eax+0x501,0x1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov WORD  PTR eax+0xa00,0x1e1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_57_ ENDP

PUBLIC g4x6_58_
g4x6_58_ PROC
  mov WORD  PTR eax+0x0,0x1e1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x500,0x1e;
  mov BYTE  PTR eax+0x780,0x1e;
  mov WORD  PTR eax+0xa00,0x1e1e;
  ret
g4x6_58_ ENDP

PUBLIC g4x6_59_
g4x6_59_ PROC
  mov BYTE  PTR eax+0x0,0x1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x501,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_59_ ENDP

PUBLIC g4x6_60_
g4x6_60_ PROC
  mov WORD  PTR eax+0x0,0x1e1e;
  mov BYTE  PTR eax+0x281,0x1e;
  mov BYTE  PTR eax+0x501,0x1e;
  mov BYTE  PTR eax+0x781,0x1e;
  mov WORD  PTR eax+0xa00,0x1e1e;
  ret
g4x6_60_ ENDP

PUBLIC g4x6_61_
g4x6_61_ PROC
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x281,0x1e;
  mov BYTE  PTR eax+0x283,0x1e;
  ret
g4x6_61_ ENDP

PUBLIC g4x6_62_
g4x6_62_ PROC
  mov DWORD PTR eax+0xc80,0x1e1e1e1e;
  ret
g4x6_62_ ENDP

PUBLIC g4x6_63_
g4x6_63_ PROC
  mov WORD  PTR eax+0x1,0x1e1e;
  mov BYTE  PTR eax+0x282,0x1e;
  ret
g4x6_63_ ENDP

PUBLIC g4x6_64_
g4x6_64_ PROC
  mov WORD  PTR eax+0x502,0x1e1e;
  mov BYTE  PTR eax+0x781,0x1e;
  mov BYTE  PTR eax+0x783,0x1e;
  mov WORD  PTR eax+0xa01,0x1e1e;
  mov BYTE  PTR eax+0xa03,0x1e;
  ret
g4x6_64_ ENDP

PUBLIC g4x6_65_
g4x6_65_ PROC
  mov BYTE  PTR eax+0x1,0x1e;
  mov BYTE  PTR eax+0x281,0x1e;
  mov WORD  PTR eax+0x501,0x1e1e;
  mov BYTE  PTR eax+0x781,0x1e;
  mov BYTE  PTR eax+0x783,0x1e;
  mov WORD  PTR eax+0xa01,0x1e1e;
  ret
g4x6_65_ ENDP

PUBLIC g4x6_66_
g4x6_66_ PROC
  mov WORD  PTR eax+0x502,0x1e1e;
  mov BYTE  PTR eax+0x781,0x1e;
  mov WORD  PTR eax+0xa02,0x1e1e;
  ret
g4x6_66_ ENDP

PUBLIC g4x6_67_
g4x6_67_ PROC
  mov BYTE  PTR eax+0x3,0x1e;
  mov BYTE  PTR eax+0x283,0x1e;
  mov WORD  PTR eax+0x502,0x1e1e;
  mov BYTE  PTR eax+0x781,0x1e;
  mov BYTE  PTR eax+0x783,0x1e;
  mov WORD  PTR eax+0xa02,0x1e1e;
  ret
g4x6_67_ ENDP

PUBLIC g4x6_68_
g4x6_68_ PROC
  mov WORD  PTR eax+0x501,0x1e1e;
  mov BYTE  PTR eax+0x503,0x1e;
  mov WORD  PTR eax+0x781,0x1e1e;
  mov WORD  PTR eax+0xa02,0x1e1e;
  ret
g4x6_68_ ENDP

PUBLIC g4x6_69_
g4x6_69_ PROC
  mov BYTE  PTR eax+0x3,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov WORD  PTR eax+0x501,0x1e1e;
  mov BYTE  PTR eax+0x503,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_69_ ENDP

PUBLIC g4x6_70_
g4x6_70_ PROC
  mov WORD  PTR eax+0x501,0x1e1e;
  mov BYTE  PTR eax+0x503,0x1e;
  mov BYTE  PTR eax+0x781,0x1e;
  mov BYTE  PTR eax+0x783,0x1e;
  mov BYTE  PTR eax+0xa03,0x1e;
  mov WORD  PTR eax+0xc81,0x1e1e;
  mov BYTE  PTR eax+0xc83,0x1e;
  ret
g4x6_70_ ENDP

PUBLIC g4x6_71_
g4x6_71_ PROC
  mov BYTE  PTR eax+0x1,0x1e;
  mov BYTE  PTR eax+0x281,0x1e;
  mov WORD  PTR eax+0x501,0x1e1e;
  mov BYTE  PTR eax+0x781,0x1e;
  mov BYTE  PTR eax+0x783,0x1e;
  mov BYTE  PTR eax+0xa01,0x1e;
  mov BYTE  PTR eax+0xa03,0x1e;
  ret
g4x6_71_ ENDP

PUBLIC g4x6_72_
g4x6_72_ PROC
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x502,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_72_ ENDP

PUBLIC g4x6_73_
g4x6_73_ PROC
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x502,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  mov WORD  PTR eax+0xc81,0x1e1e;
  ret
g4x6_73_ ENDP

PUBLIC g4x6_74_
g4x6_74_ PROC
  mov BYTE  PTR eax+0x1,0x1e;
  mov BYTE  PTR eax+0x281,0x1e;
  mov BYTE  PTR eax+0x501,0x1e;
  mov BYTE  PTR eax+0x503,0x1e;
  mov WORD  PTR eax+0x781,0x1e1e;
  mov BYTE  PTR eax+0xa01,0x1e;
  mov BYTE  PTR eax+0xa03,0x1e;
  ret
g4x6_74_ ENDP

PUBLIC g4x6_75_
g4x6_75_ PROC
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov BYTE  PTR eax+0x502,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_75_ ENDP

PUBLIC g4x6_76_
g4x6_76_ PROC
  mov WORD  PTR eax+0x501,0x1e1e;
  mov BYTE  PTR eax+0x503,0x1e;
  mov WORD  PTR eax+0x781,0x1e1e;
  mov BYTE  PTR eax+0x783,0x1e;
  mov BYTE  PTR eax+0xa01,0x1e;
  mov BYTE  PTR eax+0xa03,0x1e;
  ret
g4x6_76_ ENDP

PUBLIC g4x6_77_
g4x6_77_ PROC
  mov WORD  PTR eax+0x501,0x1e1e;
  mov BYTE  PTR eax+0x781,0x1e;
  mov BYTE  PTR eax+0x783,0x1e;
  mov BYTE  PTR eax+0xa01,0x1e;
  mov BYTE  PTR eax+0xa03,0x1e;
  ret
g4x6_77_ ENDP

PUBLIC g4x6_78_
g4x6_78_ PROC
  mov BYTE  PTR eax+0x502,0x1e;
  mov BYTE  PTR eax+0x781,0x1e;
  mov BYTE  PTR eax+0x783,0x1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_78_ ENDP

PUBLIC g4x6_79_
g4x6_79_ PROC
  mov WORD  PTR eax+0x501,0x1e1e;
  mov BYTE  PTR eax+0x781,0x1e;
  mov BYTE  PTR eax+0x783,0x1e;
  mov WORD  PTR eax+0xa01,0x1e1e;
  mov BYTE  PTR eax+0xc81,0x1e;
  ret
g4x6_79_ ENDP

PUBLIC g4x6_80_
g4x6_80_ PROC
  mov WORD  PTR eax+0x502,0x1e1e;
  mov BYTE  PTR eax+0x781,0x1e;
  mov BYTE  PTR eax+0x783,0x1e;
  mov WORD  PTR eax+0xa02,0x1e1e;
  mov BYTE  PTR eax+0xc83,0x1e;
  ret
g4x6_80_ ENDP

PUBLIC g4x6_81_
g4x6_81_ PROC
  mov WORD  PTR eax+0x501,0x1e1e;
  mov BYTE  PTR eax+0x781,0x1e;
  mov BYTE  PTR eax+0xa01,0x1e;
  ret
g4x6_81_ ENDP

PUBLIC g4x6_82_
g4x6_82_ PROC
  mov WORD  PTR eax+0x502,0x1e1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov WORD  PTR eax+0xa01,0x1e1e;
  ret
g4x6_82_ ENDP

PUBLIC g4x6_83_
g4x6_83_ PROC
  mov BYTE  PTR eax+0x282,0x1e;
  mov WORD  PTR eax+0x501,0x1e1e;
  mov BYTE  PTR eax+0x503,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov WORD  PTR eax+0xa02,0x1e1e;
  ret
g4x6_83_ ENDP

PUBLIC g4x6_84_
g4x6_84_ PROC
  mov BYTE  PTR eax+0x501,0x1e;
  mov BYTE  PTR eax+0x503,0x1e;
  mov BYTE  PTR eax+0x781,0x1e;
  mov BYTE  PTR eax+0x783,0x1e;
  mov WORD  PTR eax+0xa01,0x1e1e;
  mov BYTE  PTR eax+0xa03,0x1e;
  ret
g4x6_84_ ENDP

PUBLIC g4x6_85_
g4x6_85_ PROC
  mov BYTE  PTR eax+0x501,0x1e;
  mov BYTE  PTR eax+0x503,0x1e;
  mov BYTE  PTR eax+0x781,0x1e;
  mov BYTE  PTR eax+0x783,0x1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_85_ ENDP

PUBLIC g4x6_86_
g4x6_86_ PROC
  mov BYTE  PTR eax+0x501,0x1e;
  mov BYTE  PTR eax+0x503,0x1e;
  mov WORD  PTR eax+0x781,0x1e1e;
  mov BYTE  PTR eax+0x783,0x1e;
  mov WORD  PTR eax+0xa01,0x1e1e;
  mov BYTE  PTR eax+0xa03,0x1e;
  ret
g4x6_86_ ENDP

PUBLIC g4x6_87_
g4x6_87_ PROC
  mov BYTE  PTR eax+0x501,0x1e;
  mov BYTE  PTR eax+0x503,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov BYTE  PTR eax+0xa01,0x1e;
  mov BYTE  PTR eax+0xa03,0x1e;
  ret
g4x6_87_ ENDP

PUBLIC g4x6_88_
g4x6_88_ PROC
  mov BYTE  PTR eax+0x501,0x1e;
  mov BYTE  PTR eax+0x503,0x1e;
  mov BYTE  PTR eax+0x781,0x1e;
  mov BYTE  PTR eax+0x783,0x1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  mov BYTE  PTR eax+0xc81,0x1e;
  ret
g4x6_88_ ENDP

PUBLIC g4x6_89_
g4x6_89_ PROC
  mov WORD  PTR eax+0x501,0x1e1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov WORD  PTR eax+0xa02,0x1e1e;
  ret
g4x6_89_ ENDP

PUBLIC g4x6_90_
g4x6_90_ PROC
  mov WORD  PTR eax+0x2,0x1e1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov WORD  PTR eax+0x501,0x1e1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov WORD  PTR eax+0xa02,0x1e1e;
  ret
g4x6_90_ ENDP

PUBLIC g4x6_91_
g4x6_91_ PROC
  mov BYTE  PTR eax+0x2,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov BYTE  PTR eax+0x502,0x1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov BYTE  PTR eax+0xa02,0x1e;
  ret
g4x6_91_ ENDP

PUBLIC g4x6_92_
g4x6_92_ PROC
  mov WORD  PTR eax+0x1,0x1e1e;
  mov BYTE  PTR eax+0x282,0x1e;
  mov WORD  PTR eax+0x502,0x1e1e;
  mov BYTE  PTR eax+0x782,0x1e;
  mov WORD  PTR eax+0xa01,0x1e1e;
  ret
g4x6_92_ ENDP

PUBLIC g4x6_93_
g4x6_93_ PROC
  mov BYTE  PTR eax+0x1,0x1e;
  mov BYTE  PTR eax+0x3,0x1e;
  mov BYTE  PTR eax+0x280,0x1e;
  mov BYTE  PTR eax+0x282,0x1e;
  ret
g4x6_93_ ENDP

_TEXT ENDS
END
