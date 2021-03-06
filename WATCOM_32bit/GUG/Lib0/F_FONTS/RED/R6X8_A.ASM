; Compiled Sprites output from spr2asm
;  command line : spr2asm r6x8 r6x8.spr 
;  entry point name : r6x8
;  asm output file  : r6x8_A.ASM
;  c   output file  : r6x8_C.C
;  spr input  file  : r6x8.spr
;
.386
DGROUP group _DATA
_DATA  segment 'DATA'
_DATA  ends
_TEXT  segment BYTE PUBLIC USE32 'CODE'
       ASSUME CS:_TEXT
       ASSUME DS:DGROUN

PUBLIC r6x8_0_
r6x8_0_ PROC
  mov BYTE  PTR eax+0x2,0x05;
  mov WORD  PTR eax+0x281,0x0505;
  mov BYTE  PTR eax+0x283,0x05;
  mov WORD  PTR eax+0x501,0x0505;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  ret
r6x8_0_ ENDP

PUBLIC r6x8_1_
r6x8_1_ PROC
  mov WORD  PTR eax+0x0,0x0505;
  mov WORD  PTR eax+0x3,0x0505;
  mov WORD  PTR eax+0x280,0x0505;
  mov WORD  PTR eax+0x283,0x0505;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  ret
r6x8_1_ ENDP

PUBLIC r6x8_2_
r6x8_2_ PROC
  mov BYTE  PTR eax+0x281,0x05;
  mov BYTE  PTR eax+0x283,0x05;
  mov DWORD PTR eax+0x500,0x05050505;
  mov BYTE  PTR eax+0x504,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov DWORD PTR eax+0xc80,0x05050505;
  mov BYTE  PTR eax+0xc84,0x05;
  mov BYTE  PTR eax+0xf01,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_2_ ENDP

PUBLIC r6x8_3_
r6x8_3_ PROC
  mov BYTE  PTR eax+0x1,0x05;
  mov WORD  PTR eax+0x281,0x0505;
  mov BYTE  PTR eax+0x283,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov WORD  PTR eax+0x781,0x0505;
  mov BYTE  PTR eax+0xa03,0x05;
  mov WORD  PTR eax+0xc80,0x0505;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  ret
r6x8_3_ ENDP

PUBLIC r6x8_4_
r6x8_4_ PROC
  mov WORD  PTR eax+0x0,0x0505;
  mov BYTE  PTR eax+0x4,0x05;
  mov WORD  PTR eax+0x280,0x0505;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov WORD  PTR eax+0xc83,0x0505;
  mov BYTE  PTR eax+0xf00,0x05;
  mov WORD  PTR eax+0xf03,0x0505;
  ret
r6x8_4_ ENDP

PUBLIC r6x8_5_
r6x8_5_ PROC
  mov BYTE  PTR eax+0x1,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  mov BYTE  PTR eax+0xf04,0x05;
  ret
r6x8_5_ ENDP

PUBLIC r6x8_6_
r6x8_6_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov WORD  PTR eax+0x281,0x0505;
  mov BYTE  PTR eax+0x501,0x05;
  ret
r6x8_6_ ENDP

PUBLIC r6x8_7_
r6x8_7_ PROC
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x281,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xc81,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  ret
r6x8_7_ ENDP

PUBLIC r6x8_8_
r6x8_8_ PROC
  mov BYTE  PTR eax+0x1,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf01,0x05;
  ret
r6x8_8_ ENDP

PUBLIC r6x8_9_
r6x8_9_ PROC
  mov BYTE  PTR eax+0x281,0x05;
  mov BYTE  PTR eax+0x283,0x05;
  mov WORD  PTR eax+0x501,0x0505;
  mov BYTE  PTR eax+0x503,0x05;
  mov DWORD PTR eax+0x780,0x05050505;
  mov BYTE  PTR eax+0x784,0x05;
  mov WORD  PTR eax+0xa01,0x0505;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc81,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  ret
r6x8_9_ ENDP

PUBLIC r6x8_10_
r6x8_10_ PROC
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov DWORD PTR eax+0x780,0x05050505;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  ret
r6x8_10_ ENDP

PUBLIC r6x8_11_
r6x8_11_ PROC
  mov WORD  PTR eax+0x1181,0x0505;
  mov WORD  PTR eax+0x1401,0x0505;
  mov BYTE  PTR eax+0x1681,0x05;
  ret
r6x8_11_ ENDP

PUBLIC r6x8_12_
r6x8_12_ PROC
  mov DWORD PTR eax+0x780,0x05050505;
  mov BYTE  PTR eax+0x784,0x05;
  ret
r6x8_12_ ENDP

PUBLIC r6x8_13_
r6x8_13_ PROC
  mov BYTE  PTR eax+0xf02,0x05;
  ret
r6x8_13_ ENDP

PUBLIC r6x8_14_
r6x8_14_ PROC
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  ret
r6x8_14_ ENDP

PUBLIC r6x8_15_
r6x8_15_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov BYTE  PTR eax+0x3,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov WORD  PTR eax+0x503,0x0505;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_15_ ENDP

PUBLIC r6x8_16_
r6x8_16_ PROC
  mov BYTE  PTR eax+0x2,0x05;
  mov WORD  PTR eax+0x281,0x0505;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_16_ ENDP

PUBLIC r6x8_17_
r6x8_17_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov BYTE  PTR eax+0x3,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x504,0x05;
  mov WORD  PTR eax+0x782,0x0505;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov DWORD PTR eax+0xf00,0x05050505;
  mov BYTE  PTR eax+0xf04,0x05;
  ret
r6x8_17_ ENDP

PUBLIC r6x8_18_
r6x8_18_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov BYTE  PTR eax+0x3,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x504,0x05;
  mov WORD  PTR eax+0x781,0x0505;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_18_ ENDP

PUBLIC r6x8_19_
r6x8_19_ PROC
  mov BYTE  PTR eax+0x3,0x05;
  mov WORD  PTR eax+0x282,0x0505;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov DWORD PTR eax+0xa00,0x05050505;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_19_ ENDP

PUBLIC r6x8_20_
r6x8_20_ PROC
  mov DWORD PTR eax+0x0,0x05050505;
  mov BYTE  PTR eax+0x4,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov DWORD PTR eax+0x780,0x05050505;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_20_ ENDP

PUBLIC r6x8_21_
r6x8_21_ PROC
  mov WORD  PTR eax+0x2,0x0505;
  mov BYTE  PTR eax+0x281,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov DWORD PTR eax+0x780,0x05050505;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_21_ ENDP

PUBLIC r6x8_22_
r6x8_22_ PROC
  mov DWORD PTR eax+0x0,0x05050505;
  mov BYTE  PTR eax+0x4,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xc81,0x05;
  mov BYTE  PTR eax+0xf01,0x05;
  ret
r6x8_22_ ENDP

PUBLIC r6x8_23_
r6x8_23_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov BYTE  PTR eax+0x3,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x504,0x05;
  mov WORD  PTR eax+0x781,0x0505;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_23_ ENDP

PUBLIC r6x8_24_
r6x8_24_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov BYTE  PTR eax+0x3,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x504,0x05;
  mov DWORD PTR eax+0x781,0x05050505;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  ret
r6x8_24_ ENDP

PUBLIC r6x8_25_
r6x8_25_ PROC
  mov WORD  PTR eax+0x501,0x0505;
  mov WORD  PTR eax+0x781,0x0505;
  mov WORD  PTR eax+0xc81,0x0505;
  mov WORD  PTR eax+0xf01,0x0505;
  ret
r6x8_25_ ENDP

PUBLIC r6x8_26_
r6x8_26_ PROC
  mov WORD  PTR eax+0x501,0x0505;
  mov WORD  PTR eax+0x781,0x0505;
  mov WORD  PTR eax+0xc81,0x0505;
  mov WORD  PTR eax+0xf01,0x0505;
  mov BYTE  PTR eax+0x1181,0x05;
  ret
r6x8_26_ ENDP

PUBLIC r6x8_27_
r6x8_27_ PROC
  mov BYTE  PTR eax+0x3,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_27_ ENDP

PUBLIC r6x8_28_
r6x8_28_ PROC
  mov DWORD PTR eax+0x500,0x05050505;
  mov BYTE  PTR eax+0x504,0x05;
  mov DWORD PTR eax+0xc80,0x05050505;
  mov BYTE  PTR eax+0xc84,0x05;
  ret
r6x8_28_ ENDP

PUBLIC r6x8_29_
r6x8_29_ PROC
  mov BYTE  PTR eax+0x1,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf01,0x05;
  ret
r6x8_29_ ENDP

PUBLIC r6x8_30_
r6x8_30_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov BYTE  PTR eax+0x3,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x504,0x05;
  mov WORD  PTR eax+0x782,0x0505;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  ret
r6x8_30_ ENDP

PUBLIC r6x8_31_
r6x8_31_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov BYTE  PTR eax+0x3,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov WORD  PTR eax+0x502,0x0505;
  mov BYTE  PTR eax+0x504,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov WORD  PTR eax+0xa02,0x0505;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_31_ ENDP

PUBLIC r6x8_32_
r6x8_32_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov BYTE  PTR eax+0x3,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x504,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov DWORD PTR eax+0xa00,0x05050505;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf04,0x05;
  ret
r6x8_32_ ENDP

PUBLIC r6x8_33_
r6x8_33_ PROC
  mov DWORD PTR eax+0x0,0x05050505;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x504,0x05;
  mov DWORD PTR eax+0x780,0x05050505;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov DWORD PTR eax+0xf00,0x05050505;
  ret
r6x8_33_ ENDP

PUBLIC r6x8_34_
r6x8_34_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov BYTE  PTR eax+0x3,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_34_ ENDP

PUBLIC r6x8_35_
r6x8_35_ PROC
  mov DWORD PTR eax+0x0,0x05050505;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x504,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov DWORD PTR eax+0xf00,0x05050505;
  ret
r6x8_35_ ENDP

PUBLIC r6x8_36_
r6x8_36_ PROC
  mov DWORD PTR eax+0x0,0x05050505;
  mov BYTE  PTR eax+0x4,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov DWORD PTR eax+0x780,0x05050505;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov DWORD PTR eax+0xf00,0x05050505;
  mov BYTE  PTR eax+0xf04,0x05;
  ret
r6x8_36_ ENDP

PUBLIC r6x8_37_
r6x8_37_ PROC
  mov DWORD PTR eax+0x0,0x05050505;
  mov BYTE  PTR eax+0x4,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov DWORD PTR eax+0x780,0x05050505;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  ret
r6x8_37_ ENDP

PUBLIC r6x8_38_
r6x8_38_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov BYTE  PTR eax+0x3,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov WORD  PTR eax+0x782,0x0505;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov DWORD PTR eax+0xf01,0x05050505;
  ret
r6x8_38_ ENDP

PUBLIC r6x8_39_
r6x8_39_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x4,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x504,0x05;
  mov DWORD PTR eax+0x780,0x05050505;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf04,0x05;
  ret
r6x8_39_ ENDP

PUBLIC r6x8_40_
r6x8_40_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov BYTE  PTR eax+0x3,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_40_ ENDP

PUBLIC r6x8_41_
r6x8_41_ PROC
  mov BYTE  PTR eax+0x4,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x504,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_41_ ENDP

PUBLIC r6x8_42_
r6x8_42_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x4,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x283,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov WORD  PTR eax+0x780,0x0505;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf04,0x05;
  ret
r6x8_42_ ENDP

PUBLIC r6x8_43_
r6x8_43_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov DWORD PTR eax+0xf00,0x05050505;
  mov BYTE  PTR eax+0xf04,0x05;
  ret
r6x8_43_ ENDP

PUBLIC r6x8_44_
r6x8_44_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x4,0x05;
  mov WORD  PTR eax+0x280,0x0505;
  mov WORD  PTR eax+0x283,0x0505;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x504,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf04,0x05;
  ret
r6x8_44_ ENDP

PUBLIC r6x8_45_
r6x8_45_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x4,0x05;
  mov WORD  PTR eax+0x280,0x0505;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x504,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov WORD  PTR eax+0x783,0x0505;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf04,0x05;
  ret
r6x8_45_ ENDP

PUBLIC r6x8_46_
r6x8_46_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov BYTE  PTR eax+0x3,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x504,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_46_ ENDP

PUBLIC r6x8_47_
r6x8_47_ PROC
  mov DWORD PTR eax+0x0,0x05050505;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x504,0x05;
  mov DWORD PTR eax+0x780,0x05050505;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  ret
r6x8_47_ ENDP

PUBLIC r6x8_48_
r6x8_48_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov BYTE  PTR eax+0x3,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x504,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  mov BYTE  PTR eax+0xf04,0x05;
  ret
r6x8_48_ ENDP

PUBLIC r6x8_49_
r6x8_49_ PROC
  mov DWORD PTR eax+0x0,0x05050505;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x504,0x05;
  mov DWORD PTR eax+0x780,0x05050505;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf04,0x05;
  ret
r6x8_49_ ENDP

PUBLIC r6x8_50_
r6x8_50_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov BYTE  PTR eax+0x3,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov WORD  PTR eax+0x781,0x0505;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_50_ ENDP

PUBLIC r6x8_51_
r6x8_51_ PROC
  mov DWORD PTR eax+0x0,0x05050505;
  mov BYTE  PTR eax+0x4,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  ret
r6x8_51_ ENDP

PUBLIC r6x8_52_
r6x8_52_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x4,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x504,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_52_ ENDP

PUBLIC r6x8_53_
r6x8_53_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x4,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x504,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc81,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  ret
r6x8_53_ ENDP

PUBLIC r6x8_54_
r6x8_54_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x4,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x504,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov BYTE  PTR eax+0xf01,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_54_ ENDP

PUBLIC r6x8_55_
r6x8_55_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x4,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf04,0x05;
  ret
r6x8_55_ ENDP

PUBLIC r6x8_56_
r6x8_56_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x4,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x504,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  ret
r6x8_56_ ENDP

PUBLIC r6x8_57_
r6x8_57_ PROC
  mov DWORD PTR eax+0x0,0x05050505;
  mov BYTE  PTR eax+0x283,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov DWORD PTR eax+0xf00,0x05050505;
  ret
r6x8_57_ ENDP

PUBLIC r6x8_58_
r6x8_58_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov BYTE  PTR eax+0x3,0x05;
  mov BYTE  PTR eax+0x281,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xc81,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_58_ ENDP

PUBLIC r6x8_59_
r6x8_59_ PROC
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  ret
r6x8_59_ ENDP

PUBLIC r6x8_60_
r6x8_60_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov BYTE  PTR eax+0x3,0x05;
  mov BYTE  PTR eax+0x283,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_60_ ENDP

PUBLIC r6x8_61_
r6x8_61_ PROC
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x4,0xd8;
  mov BYTE  PTR eax+0x281,0x05;
  mov WORD  PTR eax+0x283,0xd805;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x504,0x05;
  mov BYTE  PTR eax+0x784,0xd8;
  mov BYTE  PTR eax+0xa04,0xd8;
  mov BYTE  PTR eax+0xc84,0xd8;
  mov BYTE  PTR eax+0xf04,0xd8;
  mov BYTE  PTR eax+0x1184,0xd8;
  mov BYTE  PTR eax+0x1404,0xd8;
  mov BYTE  PTR eax+0x1684,0xd8;
  mov BYTE  PTR eax+0x1904,0xd8;
  ret
r6x8_61_ ENDP

PUBLIC r6x8_62_
r6x8_62_ PROC
  mov DWORD PTR eax+0x1180,0x05050505;
  mov WORD  PTR eax+0x1184,0x0505;
  ret
r6x8_62_ ENDP

PUBLIC r6x8_63_
r6x8_63_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov WORD  PTR eax+0x281,0x0505;
  mov BYTE  PTR eax+0x502,0x05;
  ret
r6x8_63_ ENDP

PUBLIC r6x8_64_
r6x8_64_ PROC
  mov WORD  PTR eax+0x501,0x0505;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov DWORD PTR eax+0xa01,0x05050505;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov DWORD PTR eax+0xf01,0x05050505;
  ret
r6x8_64_ ENDP

PUBLIC r6x8_65_
r6x8_65_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov DWORD PTR eax+0x500,0x05050505;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov DWORD PTR eax+0xf00,0x05050505;
  ret
r6x8_65_ ENDP

PUBLIC r6x8_66_
r6x8_66_ PROC
  mov WORD  PTR eax+0x501,0x0505;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_66_ ENDP

PUBLIC r6x8_67_
r6x8_67_ PROC
  mov BYTE  PTR eax+0x4,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov DWORD PTR eax+0x501,0x05050505;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov DWORD PTR eax+0xf01,0x05050505;
  ret
r6x8_67_ ENDP

PUBLIC r6x8_68_
r6x8_68_ PROC
  mov WORD  PTR eax+0x501,0x0505;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov DWORD PTR eax+0xa00,0x05050505;
  mov BYTE  PTR eax+0xc80,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_68_ ENDP

PUBLIC r6x8_69_
r6x8_69_ PROC
  mov WORD  PTR eax+0x2,0x0505;
  mov BYTE  PTR eax+0x281,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov DWORD PTR eax+0x780,0x05050505;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xc81,0x05;
  mov BYTE  PTR eax+0xf01,0x05;
  ret
r6x8_69_ ENDP

PUBLIC r6x8_70_
r6x8_70_ PROC
  mov DWORD PTR eax+0x501,0x05050505;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov DWORD PTR eax+0xc81,0x05050505;
  mov BYTE  PTR eax+0xf04,0x05;
  mov WORD  PTR eax+0x1181,0x0505;
  mov BYTE  PTR eax+0x1183,0x05;
  ret
r6x8_70_ ENDP

PUBLIC r6x8_71_
r6x8_71_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov WORD  PTR eax+0x500,0x0505;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_71_ ENDP

PUBLIC r6x8_72_
r6x8_72_ PROC
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov WORD  PTR eax+0xf02,0x0505;
  ret
r6x8_72_ ENDP

PUBLIC r6x8_73_
r6x8_73_ PROC
  mov BYTE  PTR eax+0x3,0x05;
  mov WORD  PTR eax+0x502,0x0505;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov WORD  PTR eax+0x1181,0x0505;
  ret
r6x8_73_ ENDP

PUBLIC r6x8_74_
r6x8_74_ PROC
  mov BYTE  PTR eax+0x0,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_74_ ENDP

PUBLIC r6x8_75_
r6x8_75_ PROC
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov WORD  PTR eax+0xf02,0x0505;
  ret
r6x8_75_ ENDP

PUBLIC r6x8_76_
r6x8_76_ PROC
  mov WORD  PTR eax+0x500,0x0505;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf04,0x05;
  ret
r6x8_76_ ENDP

PUBLIC r6x8_77_
r6x8_77_ PROC
  mov WORD  PTR eax+0x500,0x0505;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_77_ ENDP

PUBLIC r6x8_78_
r6x8_78_ PROC
  mov WORD  PTR eax+0x501,0x0505;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_78_ ENDP

PUBLIC r6x8_79_
r6x8_79_ PROC
  mov DWORD PTR eax+0x500,0x05050505;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov DWORD PTR eax+0xf00,0x05050505;
  mov BYTE  PTR eax+0x1180,0x05;
  ret
r6x8_79_ ENDP

PUBLIC r6x8_80_
r6x8_80_ PROC
  mov DWORD PTR eax+0x501,0x05050505;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov DWORD PTR eax+0xf01,0x05050505;
  mov BYTE  PTR eax+0x1184,0x05;
  ret
r6x8_80_ ENDP

PUBLIC r6x8_81_
r6x8_81_ PROC
  mov BYTE  PTR eax+0x500,0x05;
  mov WORD  PTR eax+0x502,0x0505;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xc81,0x05;
  mov WORD  PTR eax+0xf00,0x0505;
  mov BYTE  PTR eax+0xf02,0x05;
  ret
r6x8_81_ ENDP

PUBLIC r6x8_82_
r6x8_82_ PROC
  mov WORD  PTR eax+0x501,0x0505;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov WORD  PTR eax+0xa01,0x0505;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc84,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_82_ ENDP

PUBLIC r6x8_83_
r6x8_83_ PROC
  mov BYTE  PTR eax+0x281,0x05;
  mov DWORD PTR eax+0x500,0x05050505;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xc81,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  ret
r6x8_83_ ENDP

PUBLIC r6x8_84_
r6x8_84_ PROC
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov WORD  PTR eax+0xc82,0x0505;
  mov BYTE  PTR eax+0xf01,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_84_ ENDP

PUBLIC r6x8_85_
r6x8_85_ PROC
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x504,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov BYTE  PTR eax+0xc81,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  ret
r6x8_85_ ENDP

PUBLIC r6x8_86_
r6x8_86_ PROC
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x504,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xa04,0x05;
  mov DWORD PTR eax+0xc80,0x05050505;
  mov BYTE  PTR eax+0xc84,0x05;
  mov BYTE  PTR eax+0xf01,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_86_ ENDP

PUBLIC r6x8_87_
r6x8_87_ PROC
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov WORD  PTR eax+0xa01,0x0505;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  ret
r6x8_87_ ENDP

PUBLIC r6x8_88_
r6x8_88_ PROC
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov WORD  PTR eax+0xc81,0x0505;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  mov WORD  PTR eax+0x1180,0x0505;
  ret
r6x8_88_ ENDP

PUBLIC r6x8_89_
r6x8_89_ PROC
  mov DWORD PTR eax+0x500,0x05050505;
  mov BYTE  PTR eax+0x783,0x05;
  mov WORD  PTR eax+0xa01,0x0505;
  mov BYTE  PTR eax+0xc80,0x05;
  mov DWORD PTR eax+0xf00,0x05050505;
  ret
r6x8_89_ ENDP

PUBLIC r6x8_90_
r6x8_90_ PROC
  mov WORD  PTR eax+0x2,0x0505;
  mov BYTE  PTR eax+0x281,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov WORD  PTR eax+0x780,0x0505;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xc81,0x05;
  mov WORD  PTR eax+0xf02,0x0505;
  ret
r6x8_90_ ENDP

PUBLIC r6x8_91_
r6x8_91_ PROC
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  ret
r6x8_91_ ENDP

PUBLIC r6x8_92_
r6x8_92_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov BYTE  PTR eax+0x283,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov WORD  PTR eax+0x783,0x0505;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  ret
r6x8_92_ ENDP

PUBLIC r6x8_93_
r6x8_93_ PROC
  mov BYTE  PTR eax+0x1,0x05;
  mov BYTE  PTR eax+0x3,0x05;
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  ret
r6x8_93_ ENDP

_TEXT ENDS
END
