; Compiled Sprites output from spr2asm
;  command line : spr2asm y4x6 y4x6.spr 
;  entry point name : y4x6
;  asm output file  : y4x6_A.ASM
;  c   output file  : y4x6_C.C
;  spr input  file  : y4x6.spr
;
.386
DGROUP group _DATA
_DATA  segment 'DATA'
_DATA  ends
_TEXT  segment BYTE PUBLIC USE32 'CODE'
       ASSUME CS:_TEXT
       ASSUME DS:DGROUN

PUBLIC y4x6_0_
y4x6_0_ PROC
  mov BYTE  PTR eax+0x1,0x23;
  mov BYTE  PTR eax+0x281,0x23;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  ret
y4x6_0_ ENDP

PUBLIC y4x6_1_
y4x6_1_ PROC
  mov BYTE  PTR eax+0x0,0x23;
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  ret
y4x6_1_ ENDP

PUBLIC y4x6_2_
y4x6_2_ PROC
  mov BYTE  PTR eax+0x0,0x23;
  mov BYTE  PTR eax+0x2,0x23;
  mov WORD  PTR eax+0x280,0x2323;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x502,0x23;
  mov WORD  PTR eax+0x780,0x2323;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_2_ ENDP

PUBLIC y4x6_3_
y4x6_3_ PROC
  mov BYTE  PTR eax+0x1,0x23;
  mov WORD  PTR eax+0x281,0x2323;
  mov WORD  PTR eax+0x500,0x2323;
  mov WORD  PTR eax+0x781,0x2323;
  mov WORD  PTR eax+0xa00,0x2323;
  mov BYTE  PTR eax+0xc81,0x23;
  ret
y4x6_3_ ENDP

PUBLIC y4x6_4_
y4x6_4_ PROC
  mov BYTE  PTR eax+0x0,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_4_ ENDP

PUBLIC y4x6_5_
y4x6_5_ PROC
  mov BYTE  PTR eax+0x1,0x23;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov WORD  PTR eax+0x501,0x2323;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov WORD  PTR eax+0xa00,0x2323;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_5_ ENDP

PUBLIC y4x6_6_
y4x6_6_ PROC
  mov WORD  PTR eax+0x0,0x2323;
  mov BYTE  PTR eax+0x280,0x23;
  ret
y4x6_6_ ENDP

PUBLIC y4x6_7_
y4x6_7_ PROC
  mov BYTE  PTR eax+0x1,0x23;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  ret
y4x6_7_ ENDP

PUBLIC y4x6_8_
y4x6_8_ PROC
  mov BYTE  PTR eax+0x0,0x23;
  mov BYTE  PTR eax+0x281,0x23;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  ret
y4x6_8_ ENDP

PUBLIC y4x6_9_
y4x6_9_ PROC
  mov BYTE  PTR eax+0x0,0x23;
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x281,0x23;
  mov WORD  PTR eax+0x500,0x2323;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_9_ ENDP

PUBLIC y4x6_10_
y4x6_10_ PROC
  mov BYTE  PTR eax+0x281,0x23;
  mov WORD  PTR eax+0x500,0x2323;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x781,0x23;
  ret
y4x6_10_ ENDP

PUBLIC y4x6_11_
y4x6_11_ PROC
  mov WORD  PTR eax+0xa00,0x2323;
  mov BYTE  PTR eax+0xc80,0x23;
  ret
y4x6_11_ ENDP

PUBLIC y4x6_12_
y4x6_12_ PROC
  mov WORD  PTR eax+0x500,0x2323;
  mov BYTE  PTR eax+0x502,0x23;
  ret
y4x6_12_ ENDP

PUBLIC y4x6_13_
y4x6_13_ PROC
  mov BYTE  PTR eax+0xa01,0x23;
  ret
y4x6_13_ ENDP

PUBLIC y4x6_14_
y4x6_14_ PROC
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  ret
y4x6_14_ ENDP

PUBLIC y4x6_15_
y4x6_15_ PROC
  mov WORD  PTR eax+0x1,0x2323;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov WORD  PTR eax+0xa00,0x2323;
  ret
y4x6_15_ ENDP

PUBLIC y4x6_16_
y4x6_16_ PROC
  mov BYTE  PTR eax+0x1,0x23;
  mov WORD  PTR eax+0x280,0x2323;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x781,0x23;
  mov WORD  PTR eax+0xa00,0x2323;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_16_ ENDP

PUBLIC y4x6_17_
y4x6_17_ PROC
  mov WORD  PTR eax+0x0,0x2323;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov WORD  PTR eax+0xa00,0x2323;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_17_ ENDP

PUBLIC y4x6_18_
y4x6_18_ PROC
  mov WORD  PTR eax+0x0,0x2323;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov WORD  PTR eax+0xa00,0x2323;
  ret
y4x6_18_ ENDP

PUBLIC y4x6_19_
y4x6_19_ PROC
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov WORD  PTR eax+0x500,0x2323;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_19_ ENDP

PUBLIC y4x6_20_
y4x6_20_ PROC
  mov WORD  PTR eax+0x0,0x2323;
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x280,0x23;
  mov WORD  PTR eax+0x500,0x2323;
  mov BYTE  PTR eax+0x782,0x23;
  mov WORD  PTR eax+0xa00,0x2323;
  ret
y4x6_20_ ENDP

PUBLIC y4x6_21_
y4x6_21_ PROC
  mov BYTE  PTR eax+0x1,0x23;
  mov BYTE  PTR eax+0x280,0x23;
  mov WORD  PTR eax+0x500,0x2323;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  ret
y4x6_21_ ENDP

PUBLIC y4x6_22_
y4x6_22_ PROC
  mov WORD  PTR eax+0x0,0x2323;
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov WORD  PTR eax+0x501,0x2323;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  ret
y4x6_22_ ENDP

PUBLIC y4x6_23_
y4x6_23_ PROC
  mov BYTE  PTR eax+0x1,0x23;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  ret
y4x6_23_ ENDP

PUBLIC y4x6_24_
y4x6_24_ PROC
  mov BYTE  PTR eax+0x1,0x23;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov WORD  PTR eax+0x501,0x2323;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  ret
y4x6_24_ ENDP

PUBLIC y4x6_25_
y4x6_25_ PROC
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  ret
y4x6_25_ ENDP

PUBLIC y4x6_26_
y4x6_26_ PROC
  mov BYTE  PTR eax+0x501,0x23;
  mov WORD  PTR eax+0xa00,0x2323;
  mov BYTE  PTR eax+0xc80,0x23;
  ret
y4x6_26_ ENDP

PUBLIC y4x6_27_
y4x6_27_ PROC
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x281,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_27_ ENDP

PUBLIC y4x6_28_
y4x6_28_ PROC
  mov WORD  PTR eax+0x500,0x2323;
  mov BYTE  PTR eax+0x502,0x23;
  mov WORD  PTR eax+0xa00,0x2323;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_28_ ENDP

PUBLIC y4x6_29_
y4x6_29_ PROC
  mov BYTE  PTR eax+0x0,0x23;
  mov BYTE  PTR eax+0x281,0x23;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  ret
y4x6_29_ ENDP

PUBLIC y4x6_30_
y4x6_30_ PROC
  mov WORD  PTR eax+0x0,0x2323;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  ret
y4x6_30_ ENDP

PUBLIC y4x6_31_
y4x6_31_ PROC
  mov WORD  PTR eax+0x0,0x2323;
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov WORD  PTR eax+0xa00,0x2323;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_31_ ENDP

PUBLIC y4x6_32_
y4x6_32_ PROC
  mov BYTE  PTR eax+0x1,0x23;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov WORD  PTR eax+0x500,0x2323;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_32_ ENDP

PUBLIC y4x6_33_
y4x6_33_ PROC
  mov WORD  PTR eax+0x0,0x2323;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov WORD  PTR eax+0x500,0x2323;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov WORD  PTR eax+0xa00,0x2323;
  ret
y4x6_33_ ENDP

PUBLIC y4x6_34_
y4x6_34_ PROC
  mov WORD  PTR eax+0x1,0x2323;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov WORD  PTR eax+0xa01,0x2323;
  ret
y4x6_34_ ENDP

PUBLIC y4x6_35_
y4x6_35_ PROC
  mov WORD  PTR eax+0x0,0x2323;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov WORD  PTR eax+0xa00,0x2323;
  ret
y4x6_35_ ENDP

PUBLIC y4x6_36_
y4x6_36_ PROC
  mov WORD  PTR eax+0x0,0x2323;
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x280,0x23;
  mov WORD  PTR eax+0x500,0x2323;
  mov BYTE  PTR eax+0x780,0x23;
  mov WORD  PTR eax+0xa00,0x2323;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_36_ ENDP

PUBLIC y4x6_37_
y4x6_37_ PROC
  mov WORD  PTR eax+0x0,0x2323;
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x280,0x23;
  mov WORD  PTR eax+0x500,0x2323;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  ret
y4x6_37_ ENDP

PUBLIC y4x6_38_
y4x6_38_ PROC
  mov WORD  PTR eax+0x1,0x2323;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov WORD  PTR eax+0xa01,0x2323;
  ret
y4x6_38_ ENDP

PUBLIC y4x6_39_
y4x6_39_ PROC
  mov BYTE  PTR eax+0x0,0x23;
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov WORD  PTR eax+0x500,0x2323;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_39_ ENDP

PUBLIC y4x6_40_
y4x6_40_ PROC
  mov WORD  PTR eax+0x0,0x2323;
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x281,0x23;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x781,0x23;
  mov WORD  PTR eax+0xa00,0x2323;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_40_ ENDP

PUBLIC y4x6_41_
y4x6_41_ PROC
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  ret
y4x6_41_ ENDP

PUBLIC y4x6_42_
y4x6_42_ PROC
  mov BYTE  PTR eax+0x0,0x23;
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov WORD  PTR eax+0x500,0x2323;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_42_ ENDP

PUBLIC y4x6_43_
y4x6_43_ PROC
  mov BYTE  PTR eax+0x0,0x23;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov WORD  PTR eax+0xa00,0x2323;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_43_ ENDP

PUBLIC y4x6_44_
y4x6_44_ PROC
  mov BYTE  PTR eax+0x0,0x23;
  mov BYTE  PTR eax+0x2,0x23;
  mov WORD  PTR eax+0x280,0x2323;
  mov BYTE  PTR eax+0x282,0x23;
  mov WORD  PTR eax+0x500,0x2323;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_44_ ENDP

PUBLIC y4x6_45_
y4x6_45_ PROC
  mov BYTE  PTR eax+0x0,0x23;
  mov BYTE  PTR eax+0x2,0x23;
  mov WORD  PTR eax+0x280,0x2323;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_45_ ENDP

PUBLIC y4x6_46_
y4x6_46_ PROC
  mov BYTE  PTR eax+0x1,0x23;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  ret
y4x6_46_ ENDP

PUBLIC y4x6_47_
y4x6_47_ PROC
  mov WORD  PTR eax+0x0,0x2323;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov WORD  PTR eax+0x500,0x2323;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  ret
y4x6_47_ ENDP

PUBLIC y4x6_48_
y4x6_48_ PROC
  mov BYTE  PTR eax+0x1,0x23;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x502,0x23;
  mov WORD  PTR eax+0x780,0x2323;
  mov BYTE  PTR eax+0x782,0x23;
  mov WORD  PTR eax+0xa01,0x2323;
  ret
y4x6_48_ ENDP

PUBLIC y4x6_49_
y4x6_49_ PROC
  mov WORD  PTR eax+0x0,0x2323;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov WORD  PTR eax+0x500,0x2323;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_49_ ENDP

PUBLIC y4x6_50_
y4x6_50_ PROC
  mov WORD  PTR eax+0x1,0x2323;
  mov BYTE  PTR eax+0x280,0x23;
  mov WORD  PTR eax+0x500,0x2323;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov WORD  PTR eax+0xa00,0x2323;
  ret
y4x6_50_ ENDP

PUBLIC y4x6_51_
y4x6_51_ PROC
  mov WORD  PTR eax+0x0,0x2323;
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x281,0x23;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  ret
y4x6_51_ ENDP

PUBLIC y4x6_52_
y4x6_52_ PROC
  mov BYTE  PTR eax+0x0,0x23;
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov WORD  PTR eax+0xa00,0x2323;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_52_ ENDP

PUBLIC y4x6_53_
y4x6_53_ PROC
  mov BYTE  PTR eax+0x0,0x23;
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  ret
y4x6_53_ ENDP

PUBLIC y4x6_54_
y4x6_54_ PROC
  mov BYTE  PTR eax+0x0,0x23;
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov WORD  PTR eax+0x500,0x2323;
  mov BYTE  PTR eax+0x502,0x23;
  mov WORD  PTR eax+0x780,0x2323;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_54_ ENDP

PUBLIC y4x6_55_
y4x6_55_ PROC
  mov BYTE  PTR eax+0x0,0x23;
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_55_ ENDP

PUBLIC y4x6_56_
y4x6_56_ PROC
  mov BYTE  PTR eax+0x0,0x23;
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  ret
y4x6_56_ ENDP

PUBLIC y4x6_57_
y4x6_57_ PROC
  mov WORD  PTR eax+0x0,0x2323;
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov WORD  PTR eax+0xa00,0x2323;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_57_ ENDP

PUBLIC y4x6_58_
y4x6_58_ PROC
  mov WORD  PTR eax+0x0,0x2323;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov WORD  PTR eax+0xa00,0x2323;
  ret
y4x6_58_ ENDP

PUBLIC y4x6_59_
y4x6_59_ PROC
  mov BYTE  PTR eax+0x0,0x23;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_59_ ENDP

PUBLIC y4x6_60_
y4x6_60_ PROC
  mov WORD  PTR eax+0x0,0x2323;
  mov BYTE  PTR eax+0x281,0x23;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x781,0x23;
  mov WORD  PTR eax+0xa00,0x2323;
  ret
y4x6_60_ ENDP

PUBLIC y4x6_61_
y4x6_61_ PROC
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x281,0x23;
  mov BYTE  PTR eax+0x283,0x23;
  ret
y4x6_61_ ENDP

PUBLIC y4x6_62_
y4x6_62_ PROC
  mov DWORD PTR eax+0xc80,0x23232323;
  ret
y4x6_62_ ENDP

PUBLIC y4x6_63_
y4x6_63_ PROC
  mov WORD  PTR eax+0x1,0x2323;
  mov BYTE  PTR eax+0x282,0x23;
  ret
y4x6_63_ ENDP

PUBLIC y4x6_64_
y4x6_64_ PROC
  mov WORD  PTR eax+0x502,0x2323;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov WORD  PTR eax+0xa01,0x2323;
  mov BYTE  PTR eax+0xa03,0x23;
  ret
y4x6_64_ ENDP

PUBLIC y4x6_65_
y4x6_65_ PROC
  mov BYTE  PTR eax+0x1,0x23;
  mov BYTE  PTR eax+0x281,0x23;
  mov WORD  PTR eax+0x501,0x2323;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov WORD  PTR eax+0xa01,0x2323;
  ret
y4x6_65_ ENDP

PUBLIC y4x6_66_
y4x6_66_ PROC
  mov WORD  PTR eax+0x502,0x2323;
  mov BYTE  PTR eax+0x781,0x23;
  mov WORD  PTR eax+0xa02,0x2323;
  ret
y4x6_66_ ENDP

PUBLIC y4x6_67_
y4x6_67_ PROC
  mov BYTE  PTR eax+0x3,0x23;
  mov BYTE  PTR eax+0x283,0x23;
  mov WORD  PTR eax+0x502,0x2323;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov WORD  PTR eax+0xa02,0x2323;
  ret
y4x6_67_ ENDP

PUBLIC y4x6_68_
y4x6_68_ PROC
  mov WORD  PTR eax+0x501,0x2323;
  mov BYTE  PTR eax+0x503,0x23;
  mov WORD  PTR eax+0x781,0x2323;
  mov WORD  PTR eax+0xa02,0x2323;
  ret
y4x6_68_ ENDP

PUBLIC y4x6_69_
y4x6_69_ PROC
  mov BYTE  PTR eax+0x3,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov WORD  PTR eax+0x501,0x2323;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_69_ ENDP

PUBLIC y4x6_70_
y4x6_70_ PROC
  mov WORD  PTR eax+0x501,0x2323;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov WORD  PTR eax+0xc81,0x2323;
  mov BYTE  PTR eax+0xc83,0x23;
  ret
y4x6_70_ ENDP

PUBLIC y4x6_71_
y4x6_71_ PROC
  mov BYTE  PTR eax+0x1,0x23;
  mov BYTE  PTR eax+0x281,0x23;
  mov WORD  PTR eax+0x501,0x2323;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  ret
y4x6_71_ ENDP

PUBLIC y4x6_72_
y4x6_72_ PROC
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_72_ ENDP

PUBLIC y4x6_73_
y4x6_73_ PROC
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  mov WORD  PTR eax+0xc81,0x2323;
  ret
y4x6_73_ ENDP

PUBLIC y4x6_74_
y4x6_74_ PROC
  mov BYTE  PTR eax+0x1,0x23;
  mov BYTE  PTR eax+0x281,0x23;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov WORD  PTR eax+0x781,0x2323;
  mov BYTE  PTR eax+0xa01,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  ret
y4x6_74_ ENDP

PUBLIC y4x6_75_
y4x6_75_ PROC
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_75_ ENDP

PUBLIC y4x6_76_
y4x6_76_ PROC
  mov WORD  PTR eax+0x501,0x2323;
  mov BYTE  PTR eax+0x503,0x23;
  mov WORD  PTR eax+0x781,0x2323;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  ret
y4x6_76_ ENDP

PUBLIC y4x6_77_
y4x6_77_ PROC
  mov WORD  PTR eax+0x501,0x2323;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  ret
y4x6_77_ ENDP

PUBLIC y4x6_78_
y4x6_78_ PROC
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_78_ ENDP

PUBLIC y4x6_79_
y4x6_79_ PROC
  mov WORD  PTR eax+0x501,0x2323;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov WORD  PTR eax+0xa01,0x2323;
  mov BYTE  PTR eax+0xc81,0x23;
  ret
y4x6_79_ ENDP

PUBLIC y4x6_80_
y4x6_80_ PROC
  mov WORD  PTR eax+0x502,0x2323;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov WORD  PTR eax+0xa02,0x2323;
  mov BYTE  PTR eax+0xc83,0x23;
  ret
y4x6_80_ ENDP

PUBLIC y4x6_81_
y4x6_81_ PROC
  mov WORD  PTR eax+0x501,0x2323;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  ret
y4x6_81_ ENDP

PUBLIC y4x6_82_
y4x6_82_ PROC
  mov WORD  PTR eax+0x502,0x2323;
  mov BYTE  PTR eax+0x782,0x23;
  mov WORD  PTR eax+0xa01,0x2323;
  ret
y4x6_82_ ENDP

PUBLIC y4x6_83_
y4x6_83_ PROC
  mov BYTE  PTR eax+0x282,0x23;
  mov WORD  PTR eax+0x501,0x2323;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov WORD  PTR eax+0xa02,0x2323;
  ret
y4x6_83_ ENDP

PUBLIC y4x6_84_
y4x6_84_ PROC
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov WORD  PTR eax+0xa01,0x2323;
  mov BYTE  PTR eax+0xa03,0x23;
  ret
y4x6_84_ ENDP

PUBLIC y4x6_85_
y4x6_85_ PROC
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_85_ ENDP

PUBLIC y4x6_86_
y4x6_86_ PROC
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov WORD  PTR eax+0x781,0x2323;
  mov BYTE  PTR eax+0x783,0x23;
  mov WORD  PTR eax+0xa01,0x2323;
  mov BYTE  PTR eax+0xa03,0x23;
  ret
y4x6_86_ ENDP

PUBLIC y4x6_87_
y4x6_87_ PROC
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  ret
y4x6_87_ ENDP

PUBLIC y4x6_88_
y4x6_88_ PROC
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  mov BYTE  PTR eax+0xc81,0x23;
  ret
y4x6_88_ ENDP

PUBLIC y4x6_89_
y4x6_89_ PROC
  mov WORD  PTR eax+0x501,0x2323;
  mov BYTE  PTR eax+0x782,0x23;
  mov WORD  PTR eax+0xa02,0x2323;
  ret
y4x6_89_ ENDP

PUBLIC y4x6_90_
y4x6_90_ PROC
  mov WORD  PTR eax+0x2,0x2323;
  mov BYTE  PTR eax+0x282,0x23;
  mov WORD  PTR eax+0x501,0x2323;
  mov BYTE  PTR eax+0x782,0x23;
  mov WORD  PTR eax+0xa02,0x2323;
  ret
y4x6_90_ ENDP

PUBLIC y4x6_91_
y4x6_91_ PROC
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  ret
y4x6_91_ ENDP

PUBLIC y4x6_92_
y4x6_92_ PROC
  mov WORD  PTR eax+0x1,0x2323;
  mov BYTE  PTR eax+0x282,0x23;
  mov WORD  PTR eax+0x502,0x2323;
  mov BYTE  PTR eax+0x782,0x23;
  mov WORD  PTR eax+0xa01,0x2323;
  ret
y4x6_92_ ENDP

PUBLIC y4x6_93_
y4x6_93_ PROC
  mov BYTE  PTR eax+0x1,0x23;
  mov BYTE  PTR eax+0x3,0x23;
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  ret
y4x6_93_ ENDP

_TEXT ENDS
END
