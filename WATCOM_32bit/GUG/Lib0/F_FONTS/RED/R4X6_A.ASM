; Compiled Sprites output from spr2asm
;  command line : spr2asm r4x6 r4x6.spr 
;  entry point name : r4x6
;  asm output file  : r4x6_A.ASM
;  c   output file  : r4x6_C.C
;  spr input  file  : r4x6.spr
;
.386
DGROUP group _DATA
_DATA  segment 'DATA'
_DATA  ends
_TEXT  segment BYTE PUBLIC USE32 'CODE'
       ASSUME CS:_TEXT
       ASSUME DS:DGROUN

PUBLIC r4x6_0_
r4x6_0_ PROC
  mov BYTE  PTR eax+0x1,0x05;
  mov BYTE  PTR eax+0x281,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  ret
r4x6_0_ ENDP

PUBLIC r4x6_1_
r4x6_1_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  ret
r4x6_1_ ENDP

PUBLIC r4x6_2_
r4x6_2_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x2,0x05;
  mov WORD  PTR eax+0x280,0x0505;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov WORD  PTR eax+0x780,0x0505;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_2_ ENDP

PUBLIC r4x6_3_
r4x6_3_ PROC
  mov BYTE  PTR eax+0x1,0x05;
  mov WORD  PTR eax+0x281,0x0505;
  mov WORD  PTR eax+0x500,0x0505;
  mov WORD  PTR eax+0x781,0x0505;
  mov WORD  PTR eax+0xa00,0x0505;
  mov BYTE  PTR eax+0xc81,0x05;
  ret
r4x6_3_ ENDP

PUBLIC r4x6_4_
r4x6_4_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_4_ ENDP

PUBLIC r4x6_5_
r4x6_5_ PROC
  mov BYTE  PTR eax+0x1,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov WORD  PTR eax+0x501,0x0505;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_5_ ENDP

PUBLIC r4x6_6_
r4x6_6_ PROC
  mov WORD  PTR eax+0x0,0x0505;
  mov BYTE  PTR eax+0x280,0x05;
  ret
r4x6_6_ ENDP

PUBLIC r4x6_7_
r4x6_7_ PROC
  mov BYTE  PTR eax+0x1,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  ret
r4x6_7_ ENDP

PUBLIC r4x6_8_
r4x6_8_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x281,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  ret
r4x6_8_ ENDP

PUBLIC r4x6_9_
r4x6_9_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x281,0x05;
  mov WORD  PTR eax+0x500,0x0505;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_9_ ENDP

PUBLIC r4x6_10_
r4x6_10_ PROC
  mov BYTE  PTR eax+0x281,0x05;
  mov WORD  PTR eax+0x500,0x0505;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  ret
r4x6_10_ ENDP

PUBLIC r4x6_11_
r4x6_11_ PROC
  mov WORD  PTR eax+0xa00,0x0505;
  mov BYTE  PTR eax+0xc80,0x05;
  ret
r4x6_11_ ENDP

PUBLIC r4x6_12_
r4x6_12_ PROC
  mov WORD  PTR eax+0x500,0x0505;
  mov BYTE  PTR eax+0x502,0x05;
  ret
r4x6_12_ ENDP

PUBLIC r4x6_13_
r4x6_13_ PROC
  mov BYTE  PTR eax+0xa01,0x05;
  ret
r4x6_13_ ENDP

PUBLIC r4x6_14_
r4x6_14_ PROC
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  ret
r4x6_14_ ENDP

PUBLIC r4x6_15_
r4x6_15_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  ret
r4x6_15_ ENDP

PUBLIC r4x6_16_
r4x6_16_ PROC
  mov BYTE  PTR eax+0x1,0x05;
  mov WORD  PTR eax+0x280,0x0505;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_16_ ENDP

PUBLIC r4x6_17_
r4x6_17_ PROC
  mov WORD  PTR eax+0x0,0x0505;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_17_ ENDP

PUBLIC r4x6_18_
r4x6_18_ PROC
  mov WORD  PTR eax+0x0,0x0505;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  ret
r4x6_18_ ENDP

PUBLIC r4x6_19_
r4x6_19_ PROC
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov WORD  PTR eax+0x500,0x0505;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_19_ ENDP

PUBLIC r4x6_20_
r4x6_20_ PROC
  mov WORD  PTR eax+0x0,0x0505;
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov WORD  PTR eax+0x500,0x0505;
  mov BYTE  PTR eax+0x782,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  ret
r4x6_20_ ENDP

PUBLIC r4x6_21_
r4x6_21_ PROC
  mov BYTE  PTR eax+0x1,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov WORD  PTR eax+0x500,0x0505;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  ret
r4x6_21_ ENDP

PUBLIC r4x6_22_
r4x6_22_ PROC
  mov WORD  PTR eax+0x0,0x0505;
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov WORD  PTR eax+0x501,0x0505;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  ret
r4x6_22_ ENDP

PUBLIC r4x6_23_
r4x6_23_ PROC
  mov BYTE  PTR eax+0x1,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  ret
r4x6_23_ ENDP

PUBLIC r4x6_24_
r4x6_24_ PROC
  mov BYTE  PTR eax+0x1,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov WORD  PTR eax+0x501,0x0505;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  ret
r4x6_24_ ENDP

PUBLIC r4x6_25_
r4x6_25_ PROC
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  ret
r4x6_25_ ENDP

PUBLIC r4x6_26_
r4x6_26_ PROC
  mov BYTE  PTR eax+0x501,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  mov BYTE  PTR eax+0xc80,0x05;
  ret
r4x6_26_ ENDP

PUBLIC r4x6_27_
r4x6_27_ PROC
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x281,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_27_ ENDP

PUBLIC r4x6_28_
r4x6_28_ PROC
  mov WORD  PTR eax+0x500,0x0505;
  mov BYTE  PTR eax+0x502,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_28_ ENDP

PUBLIC r4x6_29_
r4x6_29_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x281,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  ret
r4x6_29_ ENDP

PUBLIC r4x6_30_
r4x6_30_ PROC
  mov WORD  PTR eax+0x0,0x0505;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  ret
r4x6_30_ ENDP

PUBLIC r4x6_31_
r4x6_31_ PROC
  mov WORD  PTR eax+0x0,0x0505;
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_31_ ENDP

PUBLIC r4x6_32_
r4x6_32_ PROC
  mov BYTE  PTR eax+0x1,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov WORD  PTR eax+0x500,0x0505;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_32_ ENDP

PUBLIC r4x6_33_
r4x6_33_ PROC
  mov WORD  PTR eax+0x0,0x0505;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov WORD  PTR eax+0x500,0x0505;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  ret
r4x6_33_ ENDP

PUBLIC r4x6_34_
r4x6_34_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov WORD  PTR eax+0xa01,0x0505;
  ret
r4x6_34_ ENDP

PUBLIC r4x6_35_
r4x6_35_ PROC
  mov WORD  PTR eax+0x0,0x0505;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  ret
r4x6_35_ ENDP

PUBLIC r4x6_36_
r4x6_36_ PROC
  mov WORD  PTR eax+0x0,0x0505;
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov WORD  PTR eax+0x500,0x0505;
  mov BYTE  PTR eax+0x780,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_36_ ENDP

PUBLIC r4x6_37_
r4x6_37_ PROC
  mov WORD  PTR eax+0x0,0x0505;
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov WORD  PTR eax+0x500,0x0505;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  ret
r4x6_37_ ENDP

PUBLIC r4x6_38_
r4x6_38_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov WORD  PTR eax+0xa01,0x0505;
  ret
r4x6_38_ ENDP

PUBLIC r4x6_39_
r4x6_39_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov WORD  PTR eax+0x500,0x0505;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_39_ ENDP

PUBLIC r4x6_40_
r4x6_40_ PROC
  mov WORD  PTR eax+0x0,0x0505;
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x281,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_40_ ENDP

PUBLIC r4x6_41_
r4x6_41_ PROC
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  ret
r4x6_41_ ENDP

PUBLIC r4x6_42_
r4x6_42_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov WORD  PTR eax+0x500,0x0505;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_42_ ENDP

PUBLIC r4x6_43_
r4x6_43_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_43_ ENDP

PUBLIC r4x6_44_
r4x6_44_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x2,0x05;
  mov WORD  PTR eax+0x280,0x0505;
  mov BYTE  PTR eax+0x282,0x05;
  mov WORD  PTR eax+0x500,0x0505;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_44_ ENDP

PUBLIC r4x6_45_
r4x6_45_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x2,0x05;
  mov WORD  PTR eax+0x280,0x0505;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_45_ ENDP

PUBLIC r4x6_46_
r4x6_46_ PROC
  mov BYTE  PTR eax+0x1,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  ret
r4x6_46_ ENDP

PUBLIC r4x6_47_
r4x6_47_ PROC
  mov WORD  PTR eax+0x0,0x0505;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov WORD  PTR eax+0x500,0x0505;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  ret
r4x6_47_ ENDP

PUBLIC r4x6_48_
r4x6_48_ PROC
  mov BYTE  PTR eax+0x1,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov WORD  PTR eax+0x780,0x0505;
  mov BYTE  PTR eax+0x782,0x05;
  mov WORD  PTR eax+0xa01,0x0505;
  ret
r4x6_48_ ENDP

PUBLIC r4x6_49_
r4x6_49_ PROC
  mov WORD  PTR eax+0x0,0x0505;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov WORD  PTR eax+0x500,0x0505;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_49_ ENDP

PUBLIC r4x6_50_
r4x6_50_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov BYTE  PTR eax+0x280,0x05;
  mov WORD  PTR eax+0x500,0x0505;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  ret
r4x6_50_ ENDP

PUBLIC r4x6_51_
r4x6_51_ PROC
  mov WORD  PTR eax+0x0,0x0505;
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x281,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  ret
r4x6_51_ ENDP

PUBLIC r4x6_52_
r4x6_52_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_52_ ENDP

PUBLIC r4x6_53_
r4x6_53_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  ret
r4x6_53_ ENDP

PUBLIC r4x6_54_
r4x6_54_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov WORD  PTR eax+0x500,0x0505;
  mov BYTE  PTR eax+0x502,0x05;
  mov WORD  PTR eax+0x780,0x0505;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_54_ ENDP

PUBLIC r4x6_55_
r4x6_55_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_55_ ENDP

PUBLIC r4x6_56_
r4x6_56_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  ret
r4x6_56_ ENDP

PUBLIC r4x6_57_
r4x6_57_ PROC
  mov WORD  PTR eax+0x0,0x0505;
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_57_ ENDP

PUBLIC r4x6_58_
r4x6_58_ PROC
  mov WORD  PTR eax+0x0,0x0505;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  ret
r4x6_58_ ENDP

PUBLIC r4x6_59_
r4x6_59_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_59_ ENDP

PUBLIC r4x6_60_
r4x6_60_ PROC
  mov WORD  PTR eax+0x0,0x0505;
  mov BYTE  PTR eax+0x281,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  ret
r4x6_60_ ENDP

PUBLIC r4x6_61_
r4x6_61_ PROC
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x281,0x05;
  mov BYTE  PTR eax+0x283,0x05;
  ret
r4x6_61_ ENDP

PUBLIC r4x6_62_
r4x6_62_ PROC
  mov DWORD PTR eax+0xc80,0x05050505;
  ret
r4x6_62_ ENDP

PUBLIC r4x6_63_
r4x6_63_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov BYTE  PTR eax+0x282,0x05;
  ret
r4x6_63_ ENDP

PUBLIC r4x6_64_
r4x6_64_ PROC
  mov WORD  PTR eax+0x502,0x0505;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov WORD  PTR eax+0xa01,0x0505;
  mov BYTE  PTR eax+0xa03,0x05;
  ret
r4x6_64_ ENDP

PUBLIC r4x6_65_
r4x6_65_ PROC
  mov BYTE  PTR eax+0x1,0x05;
  mov BYTE  PTR eax+0x281,0x05;
  mov WORD  PTR eax+0x501,0x0505;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov WORD  PTR eax+0xa01,0x0505;
  ret
r4x6_65_ ENDP

PUBLIC r4x6_66_
r4x6_66_ PROC
  mov WORD  PTR eax+0x502,0x0505;
  mov BYTE  PTR eax+0x781,0x05;
  mov WORD  PTR eax+0xa02,0x0505;
  ret
r4x6_66_ ENDP

PUBLIC r4x6_67_
r4x6_67_ PROC
  mov BYTE  PTR eax+0x3,0x05;
  mov BYTE  PTR eax+0x283,0x05;
  mov WORD  PTR eax+0x502,0x0505;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov WORD  PTR eax+0xa02,0x0505;
  ret
r4x6_67_ ENDP

PUBLIC r4x6_68_
r4x6_68_ PROC
  mov WORD  PTR eax+0x501,0x0505;
  mov BYTE  PTR eax+0x503,0x05;
  mov WORD  PTR eax+0x781,0x0505;
  mov WORD  PTR eax+0xa02,0x0505;
  ret
r4x6_68_ ENDP

PUBLIC r4x6_69_
r4x6_69_ PROC
  mov BYTE  PTR eax+0x3,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov WORD  PTR eax+0x501,0x0505;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_69_ ENDP

PUBLIC r4x6_70_
r4x6_70_ PROC
  mov WORD  PTR eax+0x501,0x0505;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov WORD  PTR eax+0xc81,0x0505;
  mov BYTE  PTR eax+0xc83,0x05;
  ret
r4x6_70_ ENDP

PUBLIC r4x6_71_
r4x6_71_ PROC
  mov BYTE  PTR eax+0x1,0x05;
  mov BYTE  PTR eax+0x281,0x05;
  mov WORD  PTR eax+0x501,0x0505;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  ret
r4x6_71_ ENDP

PUBLIC r4x6_72_
r4x6_72_ PROC
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_72_ ENDP

PUBLIC r4x6_73_
r4x6_73_ PROC
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov WORD  PTR eax+0xc81,0x0505;
  ret
r4x6_73_ ENDP

PUBLIC r4x6_74_
r4x6_74_ PROC
  mov BYTE  PTR eax+0x1,0x05;
  mov BYTE  PTR eax+0x281,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov WORD  PTR eax+0x781,0x0505;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  ret
r4x6_74_ ENDP

PUBLIC r4x6_75_
r4x6_75_ PROC
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_75_ ENDP

PUBLIC r4x6_76_
r4x6_76_ PROC
  mov WORD  PTR eax+0x501,0x0505;
  mov BYTE  PTR eax+0x503,0x05;
  mov WORD  PTR eax+0x781,0x0505;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  ret
r4x6_76_ ENDP

PUBLIC r4x6_77_
r4x6_77_ PROC
  mov WORD  PTR eax+0x501,0x0505;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  ret
r4x6_77_ ENDP

PUBLIC r4x6_78_
r4x6_78_ PROC
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_78_ ENDP

PUBLIC r4x6_79_
r4x6_79_ PROC
  mov WORD  PTR eax+0x501,0x0505;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov WORD  PTR eax+0xa01,0x0505;
  mov BYTE  PTR eax+0xc81,0x05;
  ret
r4x6_79_ ENDP

PUBLIC r4x6_80_
r4x6_80_ PROC
  mov WORD  PTR eax+0x502,0x0505;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov WORD  PTR eax+0xa02,0x0505;
  mov BYTE  PTR eax+0xc83,0x05;
  ret
r4x6_80_ ENDP

PUBLIC r4x6_81_
r4x6_81_ PROC
  mov WORD  PTR eax+0x501,0x0505;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  ret
r4x6_81_ ENDP

PUBLIC r4x6_82_
r4x6_82_ PROC
  mov WORD  PTR eax+0x502,0x0505;
  mov BYTE  PTR eax+0x782,0x05;
  mov WORD  PTR eax+0xa01,0x0505;
  ret
r4x6_82_ ENDP

PUBLIC r4x6_83_
r4x6_83_ PROC
  mov BYTE  PTR eax+0x282,0x05;
  mov WORD  PTR eax+0x501,0x0505;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov WORD  PTR eax+0xa02,0x0505;
  ret
r4x6_83_ ENDP

PUBLIC r4x6_84_
r4x6_84_ PROC
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov WORD  PTR eax+0xa01,0x0505;
  mov BYTE  PTR eax+0xa03,0x05;
  ret
r4x6_84_ ENDP

PUBLIC r4x6_85_
r4x6_85_ PROC
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_85_ ENDP

PUBLIC r4x6_86_
r4x6_86_ PROC
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov WORD  PTR eax+0x781,0x0505;
  mov BYTE  PTR eax+0x783,0x05;
  mov WORD  PTR eax+0xa01,0x0505;
  mov BYTE  PTR eax+0xa03,0x05;
  ret
r4x6_86_ ENDP

PUBLIC r4x6_87_
r4x6_87_ PROC
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  ret
r4x6_87_ ENDP

PUBLIC r4x6_88_
r4x6_88_ PROC
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc81,0x05;
  ret
r4x6_88_ ENDP

PUBLIC r4x6_89_
r4x6_89_ PROC
  mov WORD  PTR eax+0x501,0x0505;
  mov BYTE  PTR eax+0x782,0x05;
  mov WORD  PTR eax+0xa02,0x0505;
  ret
r4x6_89_ ENDP

PUBLIC r4x6_90_
r4x6_90_ PROC
  mov WORD  PTR eax+0x2,0x0505;
  mov BYTE  PTR eax+0x282,0x05;
  mov WORD  PTR eax+0x501,0x0505;
  mov BYTE  PTR eax+0x782,0x05;
  mov WORD  PTR eax+0xa02,0x0505;
  ret
r4x6_90_ ENDP

PUBLIC r4x6_91_
r4x6_91_ PROC
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  ret
r4x6_91_ ENDP

PUBLIC r4x6_92_
r4x6_92_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov BYTE  PTR eax+0x282,0x05;
  mov WORD  PTR eax+0x502,0x0505;
  mov BYTE  PTR eax+0x782,0x05;
  mov WORD  PTR eax+0xa01,0x0505;
  ret
r4x6_92_ ENDP

PUBLIC r4x6_93_
r4x6_93_ PROC
  mov BYTE  PTR eax+0x1,0x05;
  mov BYTE  PTR eax+0x3,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  ret
r4x6_93_ ENDP

_TEXT ENDS
END
