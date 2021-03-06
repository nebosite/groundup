; Compiled Sprites output from spr2asm
;  command line : spr2asm r5x10 r5x10.spr 
;  entry point name : r5x10
;  asm output file  : r5x10_A.ASM
;  c   output file  : r5x10_C.C
;  spr input  file  : r5x10.spr
;
.386
DGROUP group _DATA
_DATA  segment 'DATA'
_DATA  ends
_TEXT  segment BYTE PUBLIC USE32 'CODE'
       ASSUME CS:_TEXT
       ASSUME DS:DGROUN

PUBLIC r5x10_0_
r5x10_0_ PROC
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  mov BYTE  PTR eax+0x1402,0x05;
  mov BYTE  PTR eax+0x1682,0x05;
  ret
r5x10_0_ ENDP

PUBLIC r5x10_1_
r5x10_1_ PROC
  mov BYTE  PTR eax+0x1,0x05;
  mov BYTE  PTR eax+0x3,0x05;
  mov BYTE  PTR eax+0x281,0x05;
  mov BYTE  PTR eax+0x283,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  ret
r5x10_1_ ENDP

PUBLIC r5x10_2_
r5x10_2_ PROC
  mov BYTE  PTR eax+0x281,0x05;
  mov BYTE  PTR eax+0x283,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov DWORD PTR eax+0x780,0x05050505;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc81,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov DWORD PTR eax+0xf00,0x05050505;
  mov BYTE  PTR eax+0xf04,0x05;
  mov BYTE  PTR eax+0x1181,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1401,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  ret
r5x10_2_ ENDP

PUBLIC r5x10_3_
r5x10_3_ PROC
  mov BYTE  PTR eax+0x281,0x05;
  mov WORD  PTR eax+0x501,0x0505;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xc81,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  mov BYTE  PTR eax+0x1902,0x05;
  ret
r5x10_3_ ENDP

PUBLIC r5x10_4_
r5x10_4_ PROC
  mov WORD  PTR eax+0x280,0x0505;
  mov BYTE  PTR eax+0x283,0x05;
  mov WORD  PTR eax+0x500,0x0505;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc81,0x05;
  mov BYTE  PTR eax+0xf01,0x05;
  mov BYTE  PTR eax+0x1181,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov WORD  PTR eax+0x1402,0x0505;
  mov BYTE  PTR eax+0x1680,0x05;
  mov WORD  PTR eax+0x1682,0x0505;
  ret
r5x10_4_ ENDP

PUBLIC r5x10_5_
r5x10_5_ PROC
  mov BYTE  PTR eax+0x281,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc81,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  mov BYTE  PTR eax+0xf04,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  mov BYTE  PTR eax+0x1684,0x05;
  ret
r5x10_5_ ENDP

PUBLIC r5x10_6_
r5x10_6_ PROC
  mov WORD  PTR eax+0x2,0x0505;
  mov WORD  PTR eax+0x282,0x0505;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  ret
r5x10_6_ ENDP

PUBLIC r5x10_7_
r5x10_7_ PROC
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xc81,0x05;
  mov BYTE  PTR eax+0xf01,0x05;
  mov BYTE  PTR eax+0x1181,0x05;
  mov BYTE  PTR eax+0x1401,0x05;
  mov BYTE  PTR eax+0x1682,0x05;
  ret
r5x10_7_ ENDP

PUBLIC r5x10_8_
r5x10_8_ PROC
  mov BYTE  PTR eax+0x281,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  mov BYTE  PTR eax+0x1182,0x05;
  mov BYTE  PTR eax+0x1402,0x05;
  mov BYTE  PTR eax+0x1681,0x05;
  ret
r5x10_8_ ENDP

PUBLIC r5x10_9_
r5x10_9_ PROC
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov WORD  PTR eax+0xa01,0x0505;
  mov BYTE  PTR eax+0xa03,0x05;
  mov WORD  PTR eax+0xc81,0x0505;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  mov BYTE  PTR eax+0xf04,0x05;
  mov BYTE  PTR eax+0x1182,0x05;
  ret
r5x10_9_ ENDP

PUBLIC r5x10_10_
r5x10_10_ PROC
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov DWORD PTR eax+0xc80,0x05050505;
  mov BYTE  PTR eax+0xc84,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  mov BYTE  PTR eax+0x1182,0x05;
  ret
r5x10_10_ ENDP

PUBLIC r5x10_11_
r5x10_11_ PROC
  mov WORD  PTR eax+0x1402,0x0505;
  mov WORD  PTR eax+0x1682,0x0505;
  mov BYTE  PTR eax+0x1903,0x05;
  mov BYTE  PTR eax+0x1b82,0x05;
  ret
r5x10_11_ ENDP

PUBLIC r5x10_12_
r5x10_12_ PROC
  mov DWORD PTR eax+0xc80,0x05050505;
  ret
r5x10_12_ ENDP

PUBLIC r5x10_13_
r5x10_13_ PROC
  mov BYTE  PTR eax+0x1681,0x05;
  ret
r5x10_13_ ENDP

PUBLIC r5x10_14_
r5x10_14_ PROC
  mov BYTE  PTR eax+0x283,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc81,0x05;
  mov BYTE  PTR eax+0xf01,0x05;
  mov BYTE  PTR eax+0x1181,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1680,0x05;
  ret
r5x10_14_ ENDP

PUBLIC r5x10_15_
r5x10_15_ PROC
  mov WORD  PTR eax+0x281,0x0505;
  mov BYTE  PTR eax+0x283,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov WORD  PTR eax+0x1680,0x0505;
  mov BYTE  PTR eax+0x1682,0x05;
  ret
r5x10_15_ ENDP

PUBLIC r5x10_16_
r5x10_16_ PROC
  mov BYTE  PTR eax+0x282,0x05;
  mov WORD  PTR eax+0x501,0x0505;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  mov BYTE  PTR eax+0x1182,0x05;
  mov BYTE  PTR eax+0x1402,0x05;
  mov DWORD PTR eax+0x1680,0x05050505;
  ret
r5x10_16_ ENDP

PUBLIC r5x10_17_
r5x10_17_ PROC
  mov WORD  PTR eax+0x281,0x0505;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf01,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov DWORD PTR eax+0x1680,0x05050505;
  ret
r5x10_17_ ENDP

PUBLIC r5x10_18_
r5x10_18_ PROC
  mov WORD  PTR eax+0x281,0x0505;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov WORD  PTR eax+0xc81,0x0505;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  ret
r5x10_18_ ENDP

PUBLIC r5x10_19_
r5x10_19_ PROC
  mov BYTE  PTR eax+0x283,0x05;
  mov WORD  PTR eax+0x502,0x0505;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov DWORD PTR eax+0xf00,0x05050505;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_19_ ENDP

PUBLIC r5x10_20_
r5x10_20_ PROC
  mov DWORD PTR eax+0x280,0x05050505;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov WORD  PTR eax+0xc80,0x0505;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  ret
r5x10_20_ ENDP

PUBLIC r5x10_21_
r5x10_21_ PROC
  mov WORD  PTR eax+0x282,0x0505;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  ret
r5x10_21_ ENDP

PUBLIC r5x10_22_
r5x10_22_ PROC
  mov DWORD PTR eax+0x280,0x05050505;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  mov BYTE  PTR eax+0x1181,0x05;
  mov BYTE  PTR eax+0x1401,0x05;
  mov BYTE  PTR eax+0x1681,0x05;
  ret
r5x10_22_ ENDP

PUBLIC r5x10_23_
r5x10_23_ PROC
  mov WORD  PTR eax+0x281,0x0505;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov WORD  PTR eax+0xc81,0x0505;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  ret
r5x10_23_ ENDP

PUBLIC r5x10_24_
r5x10_24_ PROC
  mov WORD  PTR eax+0x281,0x0505;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1402,0x05;
  mov WORD  PTR eax+0x1680,0x0505;
  ret
r5x10_24_ ENDP

PUBLIC r5x10_25_
r5x10_25_ PROC
  mov WORD  PTR eax+0xa01,0x0505;
  mov WORD  PTR eax+0xc81,0x0505;
  mov WORD  PTR eax+0x1401,0x0505;
  mov WORD  PTR eax+0x1681,0x0505;
  ret
r5x10_25_ ENDP

PUBLIC r5x10_26_
r5x10_26_ PROC
  mov WORD  PTR eax+0xa01,0x0505;
  mov WORD  PTR eax+0xc81,0x0505;
  mov WORD  PTR eax+0x1401,0x0505;
  mov WORD  PTR eax+0x1681,0x0505;
  mov BYTE  PTR eax+0x1902,0x05;
  mov BYTE  PTR eax+0x1b81,0x05;
  ret
r5x10_26_ ENDP

PUBLIC r5x10_27_
r5x10_27_ PROC
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0x1181,0x05;
  mov BYTE  PTR eax+0x1402,0x05;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_27_ ENDP

PUBLIC r5x10_28_
r5x10_28_ PROC
  mov DWORD PTR eax+0xc80,0x05050505;
  mov DWORD PTR eax+0x1180,0x05050505;
  ret
r5x10_28_ ENDP

PUBLIC r5x10_29_
r5x10_29_ PROC
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1182,0x05;
  mov BYTE  PTR eax+0x1401,0x05;
  mov BYTE  PTR eax+0x1680,0x05;
  ret
r5x10_29_ ENDP

PUBLIC r5x10_30_
r5x10_30_ PROC
  mov WORD  PTR eax+0x281,0x0505;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  mov BYTE  PTR eax+0x1402,0x05;
  mov BYTE  PTR eax+0x1682,0x05;
  ret
r5x10_30_ ENDP

PUBLIC r5x10_31_
r5x10_31_ PROC
  mov WORD  PTR eax+0x281,0x0505;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov WORD  PTR eax+0xc82,0x0505;
  mov BYTE  PTR eax+0xf00,0x05;
  mov WORD  PTR eax+0xf02,0x0505;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_31_ ENDP

PUBLIC r5x10_32_
r5x10_32_ PROC
  mov WORD  PTR eax+0x281,0x0505;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov DWORD PTR eax+0xc80,0x05050505;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov BYTE  PTR eax+0x1680,0x05;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_32_ ENDP

PUBLIC r5x10_33_
r5x10_33_ PROC
  mov WORD  PTR eax+0x280,0x0505;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov WORD  PTR eax+0xc80,0x0505;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov WORD  PTR eax+0x1680,0x0505;
  mov BYTE  PTR eax+0x1682,0x05;
  ret
r5x10_33_ ENDP

PUBLIC r5x10_34_
r5x10_34_ PROC
  mov WORD  PTR eax+0x281,0x0505;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  ret
r5x10_34_ ENDP

PUBLIC r5x10_35_
r5x10_35_ PROC
  mov WORD  PTR eax+0x280,0x0505;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov WORD  PTR eax+0x1680,0x0505;
  mov BYTE  PTR eax+0x1682,0x05;
  ret
r5x10_35_ ENDP

PUBLIC r5x10_36_
r5x10_36_ PROC
  mov DWORD PTR eax+0x280,0x05050505;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov DWORD PTR eax+0xc80,0x05050505;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov DWORD PTR eax+0x1680,0x05050505;
  ret
r5x10_36_ ENDP

PUBLIC r5x10_37_
r5x10_37_ PROC
  mov DWORD PTR eax+0x280,0x05050505;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov DWORD PTR eax+0xc80,0x05050505;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1680,0x05;
  ret
r5x10_37_ ENDP

PUBLIC r5x10_38_
r5x10_38_ PROC
  mov WORD  PTR eax+0x281,0x0505;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov WORD  PTR eax+0xf02,0x0505;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  ret
r5x10_38_ ENDP

PUBLIC r5x10_39_
r5x10_39_ PROC
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x283,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov DWORD PTR eax+0xc80,0x05050505;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov BYTE  PTR eax+0x1680,0x05;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_39_ ENDP

PUBLIC r5x10_40_
r5x10_40_ PROC
  mov WORD  PTR eax+0x281,0x0505;
  mov BYTE  PTR eax+0x283,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  mov BYTE  PTR eax+0x1182,0x05;
  mov BYTE  PTR eax+0x1402,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_40_ ENDP

PUBLIC r5x10_41_
r5x10_41_ PROC
  mov WORD  PTR eax+0x281,0x0505;
  mov BYTE  PTR eax+0x283,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1182,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1402,0x05;
  mov BYTE  PTR eax+0x1681,0x05;
  ret
r5x10_41_ ENDP

PUBLIC r5x10_42_
r5x10_42_ PROC
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x283,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov WORD  PTR eax+0xc80,0x0505;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1182,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov BYTE  PTR eax+0x1680,0x05;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_42_ ENDP

PUBLIC r5x10_43_
r5x10_43_ PROC
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov DWORD PTR eax+0x1680,0x05050505;
  ret
r5x10_43_ ENDP

PUBLIC r5x10_44_
r5x10_44_ PROC
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x283,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov DWORD PTR eax+0x780,0x05050505;
  mov DWORD PTR eax+0xa00,0x05050505;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov BYTE  PTR eax+0x1680,0x05;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_44_ ENDP

PUBLIC r5x10_45_
r5x10_45_ PROC
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x283,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov WORD  PTR eax+0x780,0x0505;
  mov BYTE  PTR eax+0x783,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov WORD  PTR eax+0xc82,0x0505;
  mov BYTE  PTR eax+0xf00,0x05;
  mov WORD  PTR eax+0xf02,0x0505;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov BYTE  PTR eax+0x1680,0x05;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_45_ ENDP

PUBLIC r5x10_46_
r5x10_46_ PROC
  mov WORD  PTR eax+0x281,0x0505;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  ret
r5x10_46_ ENDP

PUBLIC r5x10_47_
r5x10_47_ PROC
  mov WORD  PTR eax+0x280,0x0505;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov WORD  PTR eax+0xc80,0x0505;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1680,0x05;
  ret
r5x10_47_ ENDP

PUBLIC r5x10_48_
r5x10_48_ PROC
  mov WORD  PTR eax+0x281,0x0505;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  mov BYTE  PTR eax+0x1902,0x05;
  mov BYTE  PTR eax+0x1b83,0x05;
  ret
r5x10_48_ ENDP

PUBLIC r5x10_49_
r5x10_49_ PROC
  mov WORD  PTR eax+0x280,0x0505;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov WORD  PTR eax+0xc80,0x0505;
  mov BYTE  PTR eax+0xc82,0x05;
  mov WORD  PTR eax+0xf00,0x0505;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1182,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov BYTE  PTR eax+0x1680,0x05;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_49_ ENDP

PUBLIC r5x10_50_
r5x10_50_ PROC
  mov WORD  PTR eax+0x281,0x0505;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov WORD  PTR eax+0xc81,0x0505;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  ret
r5x10_50_ ENDP

PUBLIC r5x10_51_
r5x10_51_ PROC
  mov DWORD PTR eax+0x280,0x05050505;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  mov BYTE  PTR eax+0x1182,0x05;
  mov BYTE  PTR eax+0x1402,0x05;
  mov BYTE  PTR eax+0x1682,0x05;
  ret
r5x10_51_ ENDP

PUBLIC r5x10_52_
r5x10_52_ PROC
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x283,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  ret
r5x10_52_ ENDP

PUBLIC r5x10_53_
r5x10_53_ PROC
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x283,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf01,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1181,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1402,0x05;
  mov BYTE  PTR eax+0x1682,0x05;
  ret
r5x10_53_ ENDP

PUBLIC r5x10_54_
r5x10_54_ PROC
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x283,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov DWORD PTR eax+0x1180,0x05050505;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov BYTE  PTR eax+0x1680,0x05;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_54_ ENDP

PUBLIC r5x10_55_
r5x10_55_ PROC
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x283,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov WORD  PTR eax+0xa01,0x0505;
  mov WORD  PTR eax+0xc81,0x0505;
  mov WORD  PTR eax+0xf01,0x0505;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov BYTE  PTR eax+0x1680,0x05;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_55_ ENDP

PUBLIC r5x10_56_
r5x10_56_ PROC
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x284,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x504,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0x784,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc81,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  mov BYTE  PTR eax+0x1182,0x05;
  mov BYTE  PTR eax+0x1402,0x05;
  mov BYTE  PTR eax+0x1682,0x05;
  ret
r5x10_56_ ENDP

PUBLIC r5x10_57_
r5x10_57_ PROC
  mov DWORD PTR eax+0x280,0x05050505;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc81,0x05;
  mov BYTE  PTR eax+0xf01,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov DWORD PTR eax+0x1680,0x05050505;
  ret
r5x10_57_ ENDP

PUBLIC r5x10_58_
r5x10_58_ PROC
  mov WORD  PTR eax+0x281,0x0505;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xc81,0x05;
  mov BYTE  PTR eax+0xf01,0x05;
  mov BYTE  PTR eax+0x1181,0x05;
  mov BYTE  PTR eax+0x1401,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  ret
r5x10_58_ ENDP

PUBLIC r5x10_59_
r5x10_59_ PROC
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  mov BYTE  PTR eax+0x1182,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_59_ ENDP

PUBLIC r5x10_60_
r5x10_60_ PROC
  mov WORD  PTR eax+0x281,0x0505;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  mov BYTE  PTR eax+0x1182,0x05;
  mov BYTE  PTR eax+0x1402,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  ret
r5x10_60_ ENDP

PUBLIC r5x10_61_
r5x10_61_ PROC
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  ret
r5x10_61_ ENDP

PUBLIC r5x10_62_
r5x10_62_ PROC
  mov DWORD PTR eax+0x1b80,0x05050505;
  mov BYTE  PTR eax+0x1b84,0x05;
  ret
r5x10_62_ ENDP

PUBLIC r5x10_63_
r5x10_63_ PROC
  mov WORD  PTR eax+0x1,0x0505;
  mov WORD  PTR eax+0x281,0x0505;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  ret
r5x10_63_ ENDP

PUBLIC r5x10_64_
r5x10_64_ PROC
  mov WORD  PTR eax+0xa01,0x0505;
  mov BYTE  PTR eax+0xc83,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_64_ ENDP

PUBLIC r5x10_65_
r5x10_65_ PROC
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov WORD  PTR eax+0x1680,0x0505;
  mov BYTE  PTR eax+0x1682,0x05;
  ret
r5x10_65_ ENDP

PUBLIC r5x10_66_
r5x10_66_ PROC
  mov WORD  PTR eax+0xa01,0x0505;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_66_ ENDP

PUBLIC r5x10_67_
r5x10_67_ PROC
  mov BYTE  PTR eax+0x283,0x05;
  mov BYTE  PTR eax+0x503,0x05;
  mov BYTE  PTR eax+0x783,0x05;
  mov WORD  PTR eax+0xa01,0x0505;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_67_ ENDP

PUBLIC r5x10_68_
r5x10_68_ PROC
  mov WORD  PTR eax+0xa01,0x0505;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov DWORD PTR eax+0x1180,0x05050505;
  mov BYTE  PTR eax+0x1400,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_68_ ENDP

PUBLIC r5x10_69_
r5x10_69_ PROC
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc81,0x05;
  mov BYTE  PTR eax+0xf01,0x05;
  mov BYTE  PTR eax+0x1181,0x05;
  mov BYTE  PTR eax+0x1401,0x05;
  mov BYTE  PTR eax+0x1681,0x05;
  ret
r5x10_69_ ENDP

PUBLIC r5x10_70_
r5x10_70_ PROC
  mov WORD  PTR eax+0xa01,0x0505;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  mov BYTE  PTR eax+0x1683,0x05;
  mov BYTE  PTR eax+0x1903,0x05;
  mov WORD  PTR eax+0x1b81,0x0505;
  ret
r5x10_70_ ENDP

PUBLIC r5x10_71_
r5x10_71_ PROC
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov BYTE  PTR eax+0x1680,0x05;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_71_ ENDP

PUBLIC r5x10_72_
r5x10_72_ PROC
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  mov BYTE  PTR eax+0x1182,0x05;
  mov BYTE  PTR eax+0x1402,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_72_ ENDP

PUBLIC r5x10_73_
r5x10_73_ PROC
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  mov BYTE  PTR eax+0x1182,0x05;
  mov BYTE  PTR eax+0x1402,0x05;
  mov BYTE  PTR eax+0x1682,0x05;
  mov BYTE  PTR eax+0x1900,0x05;
  mov BYTE  PTR eax+0x1902,0x05;
  mov BYTE  PTR eax+0x1b81,0x05;
  ret
r5x10_73_ ENDP

PUBLIC r5x10_74_
r5x10_74_ PROC
  mov BYTE  PTR eax+0x280,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x780,0x05;
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov WORD  PTR eax+0xf00,0x0505;
  mov WORD  PTR eax+0x1180,0x0505;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1402,0x05;
  mov BYTE  PTR eax+0x1680,0x05;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_74_ ENDP

PUBLIC r5x10_75_
r5x10_75_ PROC
  mov WORD  PTR eax+0x281,0x0505;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  mov BYTE  PTR eax+0x1182,0x05;
  mov BYTE  PTR eax+0x1402,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_75_ ENDP

PUBLIC r5x10_76_
r5x10_76_ PROC
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov DWORD PTR eax+0xc80,0x05050505;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov BYTE  PTR eax+0x1680,0x05;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_76_ ENDP

PUBLIC r5x10_77_
r5x10_77_ PROC
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov WORD  PTR eax+0xc80,0x0505;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov BYTE  PTR eax+0x1680,0x05;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_77_ ENDP

PUBLIC r5x10_78_
r5x10_78_ PROC
  mov WORD  PTR eax+0xa01,0x0505;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  ret
r5x10_78_ ENDP

PUBLIC r5x10_79_
r5x10_79_ PROC
  mov WORD  PTR eax+0xa00,0x0505;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov WORD  PTR eax+0x1680,0x0505;
  mov BYTE  PTR eax+0x1682,0x05;
  mov BYTE  PTR eax+0x1900,0x05;
  mov BYTE  PTR eax+0x1b80,0x05;
  ret
r5x10_79_ ENDP

PUBLIC r5x10_80_
r5x10_80_ PROC
  mov WORD  PTR eax+0xa01,0x0505;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  mov BYTE  PTR eax+0x1683,0x05;
  mov BYTE  PTR eax+0x1903,0x05;
  mov BYTE  PTR eax+0x1b83,0x05;
  ret
r5x10_80_ ENDP

PUBLIC r5x10_81_
r5x10_81_ PROC
  mov BYTE  PTR eax+0xa00,0x05;
  mov WORD  PTR eax+0xa02,0x0505;
  mov BYTE  PTR eax+0xc81,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf01,0x05;
  mov BYTE  PTR eax+0x1181,0x05;
  mov BYTE  PTR eax+0x1401,0x05;
  mov BYTE  PTR eax+0x1681,0x05;
  ret
r5x10_81_ ENDP

PUBLIC r5x10_82_
r5x10_82_ PROC
  mov WORD  PTR eax+0xa01,0x0505;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf01,0x05;
  mov BYTE  PTR eax+0x1182,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  ret
r5x10_82_ ENDP

PUBLIC r5x10_83_
r5x10_83_ PROC
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov WORD  PTR eax+0xa00,0x0505;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc81,0x05;
  mov BYTE  PTR eax+0xf01,0x05;
  mov BYTE  PTR eax+0x1181,0x05;
  mov BYTE  PTR eax+0x1401,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  ret
r5x10_83_ ENDP

PUBLIC r5x10_84_
r5x10_84_ PROC
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_84_ ENDP

PUBLIC r5x10_85_
r5x10_85_ PROC
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf01,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1181,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1402,0x05;
  mov BYTE  PTR eax+0x1682,0x05;
  ret
r5x10_85_ ENDP

PUBLIC r5x10_86_
r5x10_86_ PROC
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov DWORD PTR eax+0x1400,0x05050505;
  mov BYTE  PTR eax+0x1680,0x05;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_86_ ENDP

PUBLIC r5x10_87_
r5x10_87_ PROC
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov WORD  PTR eax+0xf01,0x0505;
  mov WORD  PTR eax+0x1181,0x0505;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov BYTE  PTR eax+0x1680,0x05;
  mov BYTE  PTR eax+0x1683,0x05;
  ret
r5x10_87_ ENDP

PUBLIC r5x10_88_
r5x10_88_ PROC
  mov BYTE  PTR eax+0xa00,0x05;
  mov BYTE  PTR eax+0xa03,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf00,0x05;
  mov BYTE  PTR eax+0xf03,0x05;
  mov BYTE  PTR eax+0x1180,0x05;
  mov BYTE  PTR eax+0x1183,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov BYTE  PTR eax+0x1403,0x05;
  mov WORD  PTR eax+0x1681,0x0505;
  mov BYTE  PTR eax+0x1683,0x05;
  mov BYTE  PTR eax+0x1903,0x05;
  mov WORD  PTR eax+0x1b80,0x0505;
  mov BYTE  PTR eax+0x1b82,0x05;
  ret
r5x10_88_ ENDP

PUBLIC r5x10_89_
r5x10_89_ PROC
  mov DWORD PTR eax+0xa00,0x05050505;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  mov BYTE  PTR eax+0x1181,0x05;
  mov BYTE  PTR eax+0x1400,0x05;
  mov DWORD PTR eax+0x1680,0x05050505;
  ret
r5x10_89_ ENDP

PUBLIC r5x10_90_
r5x10_90_ PROC
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x501,0x05;
  mov BYTE  PTR eax+0x781,0x05;
  mov BYTE  PTR eax+0xa01,0x05;
  mov BYTE  PTR eax+0xc80,0x05;
  mov BYTE  PTR eax+0xf01,0x05;
  mov BYTE  PTR eax+0x1181,0x05;
  mov BYTE  PTR eax+0x1401,0x05;
  mov BYTE  PTR eax+0x1682,0x05;
  ret
r5x10_90_ ENDP

PUBLIC r5x10_91_
r5x10_91_ PROC
  mov BYTE  PTR eax+0x2,0x05;
  mov BYTE  PTR eax+0x282,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xc82,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  mov BYTE  PTR eax+0x1182,0x05;
  mov BYTE  PTR eax+0x1402,0x05;
  mov BYTE  PTR eax+0x1682,0x05;
  ret
r5x10_91_ ENDP

PUBLIC r5x10_92_
r5x10_92_ PROC
  mov BYTE  PTR eax+0x281,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  mov BYTE  PTR eax+0x782,0x05;
  mov BYTE  PTR eax+0xa02,0x05;
  mov BYTE  PTR eax+0xc83,0x05;
  mov BYTE  PTR eax+0xf02,0x05;
  mov BYTE  PTR eax+0x1182,0x05;
  mov BYTE  PTR eax+0x1402,0x05;
  mov BYTE  PTR eax+0x1681,0x05;
  ret
r5x10_92_ ENDP

PUBLIC r5x10_93_
r5x10_93_ PROC
  mov BYTE  PTR eax+0x281,0x05;
  mov BYTE  PTR eax+0x283,0x05;
  mov BYTE  PTR eax+0x500,0x05;
  mov BYTE  PTR eax+0x502,0x05;
  ret
r5x10_93_ ENDP

_TEXT ENDS
END
