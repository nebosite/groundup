; Compiled Sprites output from spr2asm
;  command line : spr2asm y5x10 y5x10.spr 
;  entry point name : y5x10
;  asm output file  : y5x10_A.ASM
;  c   output file  : y5x10_C.C
;  spr input  file  : y5x10.spr
;
.386
DGROUP group _DATA
_DATA  segment 'DATA'
_DATA  ends
_TEXT  segment BYTE PUBLIC USE32 'CODE'
       ASSUME CS:_TEXT
       ASSUME DS:DGROUN

PUBLIC y5x10_0_
y5x10_0_ PROC
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  mov BYTE  PTR eax+0xc82,0x23;
  mov BYTE  PTR eax+0xf02,0x23;
  mov BYTE  PTR eax+0x1402,0x23;
  mov BYTE  PTR eax+0x1682,0x23;
  ret
y5x10_0_ ENDP

PUBLIC y5x10_1_
y5x10_1_ PROC
  mov BYTE  PTR eax+0x1,0x23;
  mov BYTE  PTR eax+0x3,0x23;
  mov BYTE  PTR eax+0x281,0x23;
  mov BYTE  PTR eax+0x283,0x23;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  ret
y5x10_1_ ENDP

PUBLIC y5x10_2_
y5x10_2_ PROC
  mov BYTE  PTR eax+0x281,0x23;
  mov BYTE  PTR eax+0x283,0x23;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov DWORD PTR eax+0x780,0x23232323;
  mov BYTE  PTR eax+0x784,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc81,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov DWORD PTR eax+0xf00,0x23232323;
  mov BYTE  PTR eax+0xf04,0x23;
  mov BYTE  PTR eax+0x1181,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1401,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  ret
y5x10_2_ ENDP

PUBLIC y5x10_3_
y5x10_3_ PROC
  mov BYTE  PTR eax+0x281,0x23;
  mov WORD  PTR eax+0x501,0x2323;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xc81,0x23;
  mov BYTE  PTR eax+0xf02,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  mov BYTE  PTR eax+0x1902,0x23;
  ret
y5x10_3_ ENDP

PUBLIC y5x10_4_
y5x10_4_ PROC
  mov WORD  PTR eax+0x280,0x2323;
  mov BYTE  PTR eax+0x283,0x23;
  mov WORD  PTR eax+0x500,0x2323;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  mov BYTE  PTR eax+0xc81,0x23;
  mov BYTE  PTR eax+0xf01,0x23;
  mov BYTE  PTR eax+0x1181,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov WORD  PTR eax+0x1402,0x2323;
  mov BYTE  PTR eax+0x1680,0x23;
  mov WORD  PTR eax+0x1682,0x2323;
  ret
y5x10_4_ ENDP

PUBLIC y5x10_5_
y5x10_5_ PROC
  mov BYTE  PTR eax+0x281,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  mov BYTE  PTR eax+0xc81,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf02,0x23;
  mov BYTE  PTR eax+0xf04,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  mov BYTE  PTR eax+0x1684,0x23;
  ret
y5x10_5_ ENDP

PUBLIC y5x10_6_
y5x10_6_ PROC
  mov WORD  PTR eax+0x2,0x2323;
  mov WORD  PTR eax+0x282,0x2323;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  ret
y5x10_6_ ENDP

PUBLIC y5x10_7_
y5x10_7_ PROC
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  mov BYTE  PTR eax+0xc81,0x23;
  mov BYTE  PTR eax+0xf01,0x23;
  mov BYTE  PTR eax+0x1181,0x23;
  mov BYTE  PTR eax+0x1401,0x23;
  mov BYTE  PTR eax+0x1682,0x23;
  ret
y5x10_7_ ENDP

PUBLIC y5x10_8_
y5x10_8_ PROC
  mov BYTE  PTR eax+0x281,0x23;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  mov BYTE  PTR eax+0xc82,0x23;
  mov BYTE  PTR eax+0xf02,0x23;
  mov BYTE  PTR eax+0x1182,0x23;
  mov BYTE  PTR eax+0x1402,0x23;
  mov BYTE  PTR eax+0x1681,0x23;
  ret
y5x10_8_ ENDP

PUBLIC y5x10_9_
y5x10_9_ PROC
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0x784,0x23;
  mov WORD  PTR eax+0xa01,0x2323;
  mov BYTE  PTR eax+0xa03,0x23;
  mov WORD  PTR eax+0xc81,0x2323;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf02,0x23;
  mov BYTE  PTR eax+0xf04,0x23;
  mov BYTE  PTR eax+0x1182,0x23;
  ret
y5x10_9_ ENDP

PUBLIC y5x10_10_
y5x10_10_ PROC
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  mov DWORD PTR eax+0xc80,0x23232323;
  mov BYTE  PTR eax+0xc84,0x23;
  mov BYTE  PTR eax+0xf02,0x23;
  mov BYTE  PTR eax+0x1182,0x23;
  ret
y5x10_10_ ENDP

PUBLIC y5x10_11_
y5x10_11_ PROC
  mov WORD  PTR eax+0x1182,0x2323;
  mov WORD  PTR eax+0x1402,0x2323;
  mov BYTE  PTR eax+0x1683,0x23;
  mov BYTE  PTR eax+0x1902,0x23;
  ret
y5x10_11_ ENDP

PUBLIC y5x10_12_
y5x10_12_ PROC
  mov DWORD PTR eax+0xc80,0x23232323;
  ret
y5x10_12_ ENDP

PUBLIC y5x10_13_
y5x10_13_ PROC
  mov BYTE  PTR eax+0x1681,0x23;
  ret
y5x10_13_ ENDP

PUBLIC y5x10_14_
y5x10_14_ PROC
  mov BYTE  PTR eax+0x283,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  mov BYTE  PTR eax+0xc81,0x23;
  mov BYTE  PTR eax+0xf01,0x23;
  mov BYTE  PTR eax+0x1181,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1680,0x23;
  ret
y5x10_14_ ENDP

PUBLIC y5x10_15_
y5x10_15_ PROC
  mov WORD  PTR eax+0x281,0x2323;
  mov BYTE  PTR eax+0x283,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov WORD  PTR eax+0x1680,0x2323;
  mov BYTE  PTR eax+0x1682,0x23;
  ret
y5x10_15_ ENDP

PUBLIC y5x10_16_
y5x10_16_ PROC
  mov BYTE  PTR eax+0x282,0x23;
  mov WORD  PTR eax+0x501,0x2323;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  mov BYTE  PTR eax+0xc82,0x23;
  mov BYTE  PTR eax+0xf02,0x23;
  mov BYTE  PTR eax+0x1182,0x23;
  mov BYTE  PTR eax+0x1402,0x23;
  mov DWORD PTR eax+0x1680,0x23232323;
  ret
y5x10_16_ ENDP

PUBLIC y5x10_17_
y5x10_17_ PROC
  mov WORD  PTR eax+0x281,0x2323;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc82,0x23;
  mov BYTE  PTR eax+0xf01,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov DWORD PTR eax+0x1680,0x23232323;
  ret
y5x10_17_ ENDP

PUBLIC y5x10_18_
y5x10_18_ PROC
  mov WORD  PTR eax+0x281,0x2323;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov WORD  PTR eax+0xc81,0x2323;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  ret
y5x10_18_ ENDP

PUBLIC y5x10_19_
y5x10_19_ PROC
  mov BYTE  PTR eax+0x283,0x23;
  mov WORD  PTR eax+0x502,0x2323;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov DWORD PTR eax+0xf00,0x23232323;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_19_ ENDP

PUBLIC y5x10_20_
y5x10_20_ PROC
  mov DWORD PTR eax+0x280,0x23232323;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov WORD  PTR eax+0xc80,0x2323;
  mov BYTE  PTR eax+0xc82,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  ret
y5x10_20_ ENDP

PUBLIC y5x10_21_
y5x10_21_ PROC
  mov WORD  PTR eax+0x282,0x2323;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov WORD  PTR eax+0xa00,0x2323;
  mov BYTE  PTR eax+0xa02,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  ret
y5x10_21_ ENDP

PUBLIC y5x10_22_
y5x10_22_ PROC
  mov DWORD PTR eax+0x280,0x23232323;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc82,0x23;
  mov BYTE  PTR eax+0xf02,0x23;
  mov BYTE  PTR eax+0x1181,0x23;
  mov BYTE  PTR eax+0x1401,0x23;
  mov BYTE  PTR eax+0x1681,0x23;
  ret
y5x10_22_ ENDP

PUBLIC y5x10_23_
y5x10_23_ PROC
  mov WORD  PTR eax+0x281,0x2323;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov WORD  PTR eax+0xc81,0x2323;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  ret
y5x10_23_ ENDP

PUBLIC y5x10_24_
y5x10_24_ PROC
  mov WORD  PTR eax+0x281,0x2323;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov WORD  PTR eax+0xf01,0x2323;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1402,0x23;
  mov WORD  PTR eax+0x1680,0x2323;
  ret
y5x10_24_ ENDP

PUBLIC y5x10_25_
y5x10_25_ PROC
  mov WORD  PTR eax+0xa01,0x2323;
  mov WORD  PTR eax+0xc81,0x2323;
  mov WORD  PTR eax+0x1401,0x2323;
  mov WORD  PTR eax+0x1681,0x2323;
  ret
y5x10_25_ ENDP

PUBLIC y5x10_26_
y5x10_26_ PROC
  mov WORD  PTR eax+0xa01,0x2323;
  mov WORD  PTR eax+0xc81,0x2323;
  mov WORD  PTR eax+0x1401,0x2323;
  mov WORD  PTR eax+0x1681,0x2323;
  mov BYTE  PTR eax+0x1902,0x23;
  mov BYTE  PTR eax+0x1b81,0x23;
  ret
y5x10_26_ ENDP

PUBLIC y5x10_27_
y5x10_27_ PROC
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0x1181,0x23;
  mov BYTE  PTR eax+0x1402,0x23;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_27_ ENDP

PUBLIC y5x10_28_
y5x10_28_ PROC
  mov DWORD PTR eax+0xc80,0x23232323;
  mov DWORD PTR eax+0x1180,0x23232323;
  ret
y5x10_28_ ENDP

PUBLIC y5x10_29_
y5x10_29_ PROC
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1182,0x23;
  mov BYTE  PTR eax+0x1401,0x23;
  mov BYTE  PTR eax+0x1680,0x23;
  ret
y5x10_29_ ENDP

PUBLIC y5x10_30_
y5x10_30_ PROC
  mov WORD  PTR eax+0x281,0x2323;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc82,0x23;
  mov BYTE  PTR eax+0xf02,0x23;
  mov BYTE  PTR eax+0x1402,0x23;
  mov BYTE  PTR eax+0x1682,0x23;
  ret
y5x10_30_ ENDP

PUBLIC y5x10_31_
y5x10_31_ PROC
  mov WORD  PTR eax+0x281,0x2323;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov WORD  PTR eax+0xc82,0x2323;
  mov BYTE  PTR eax+0xf00,0x23;
  mov WORD  PTR eax+0xf02,0x2323;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_31_ ENDP

PUBLIC y5x10_32_
y5x10_32_ PROC
  mov WORD  PTR eax+0x281,0x2323;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov DWORD PTR eax+0xc80,0x23232323;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov BYTE  PTR eax+0x1680,0x23;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_32_ ENDP

PUBLIC y5x10_33_
y5x10_33_ PROC
  mov WORD  PTR eax+0x280,0x2323;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov WORD  PTR eax+0xc80,0x2323;
  mov BYTE  PTR eax+0xc82,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov WORD  PTR eax+0x1680,0x2323;
  mov BYTE  PTR eax+0x1682,0x23;
  ret
y5x10_33_ ENDP

PUBLIC y5x10_34_
y5x10_34_ PROC
  mov WORD  PTR eax+0x281,0x2323;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  ret
y5x10_34_ ENDP

PUBLIC y5x10_35_
y5x10_35_ PROC
  mov WORD  PTR eax+0x280,0x2323;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov WORD  PTR eax+0x1680,0x2323;
  mov BYTE  PTR eax+0x1682,0x23;
  ret
y5x10_35_ ENDP

PUBLIC y5x10_36_
y5x10_36_ PROC
  mov DWORD PTR eax+0x280,0x23232323;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov DWORD PTR eax+0xc80,0x23232323;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov DWORD PTR eax+0x1680,0x23232323;
  ret
y5x10_36_ ENDP

PUBLIC y5x10_37_
y5x10_37_ PROC
  mov DWORD PTR eax+0x280,0x23232323;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov DWORD PTR eax+0xc80,0x23232323;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1680,0x23;
  ret
y5x10_37_ ENDP

PUBLIC y5x10_38_
y5x10_38_ PROC
  mov WORD  PTR eax+0x281,0x2323;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov WORD  PTR eax+0xf02,0x2323;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  ret
y5x10_38_ ENDP

PUBLIC y5x10_39_
y5x10_39_ PROC
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x283,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov DWORD PTR eax+0xc80,0x23232323;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov BYTE  PTR eax+0x1680,0x23;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_39_ ENDP

PUBLIC y5x10_40_
y5x10_40_ PROC
  mov WORD  PTR eax+0x281,0x2323;
  mov BYTE  PTR eax+0x283,0x23;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  mov BYTE  PTR eax+0xc82,0x23;
  mov BYTE  PTR eax+0xf02,0x23;
  mov BYTE  PTR eax+0x1182,0x23;
  mov BYTE  PTR eax+0x1402,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_40_ ENDP

PUBLIC y5x10_41_
y5x10_41_ PROC
  mov WORD  PTR eax+0x281,0x2323;
  mov BYTE  PTR eax+0x283,0x23;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  mov BYTE  PTR eax+0xc82,0x23;
  mov BYTE  PTR eax+0xf02,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1182,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1402,0x23;
  mov BYTE  PTR eax+0x1681,0x23;
  ret
y5x10_41_ ENDP

PUBLIC y5x10_42_
y5x10_42_ PROC
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x283,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  mov WORD  PTR eax+0xc80,0x2323;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf02,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1182,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov BYTE  PTR eax+0x1680,0x23;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_42_ ENDP

PUBLIC y5x10_43_
y5x10_43_ PROC
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov DWORD PTR eax+0x1680,0x23232323;
  ret
y5x10_43_ ENDP

PUBLIC y5x10_44_
y5x10_44_ PROC
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x283,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov DWORD PTR eax+0x780,0x23232323;
  mov DWORD PTR eax+0xa00,0x23232323;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov BYTE  PTR eax+0x1680,0x23;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_44_ ENDP

PUBLIC y5x10_45_
y5x10_45_ PROC
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x283,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov WORD  PTR eax+0x780,0x2323;
  mov BYTE  PTR eax+0x783,0x23;
  mov WORD  PTR eax+0xa00,0x2323;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov WORD  PTR eax+0xc82,0x2323;
  mov BYTE  PTR eax+0xf00,0x23;
  mov WORD  PTR eax+0xf02,0x2323;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov BYTE  PTR eax+0x1680,0x23;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_45_ ENDP

PUBLIC y5x10_46_
y5x10_46_ PROC
  mov WORD  PTR eax+0x281,0x2323;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  ret
y5x10_46_ ENDP

PUBLIC y5x10_47_
y5x10_47_ PROC
  mov WORD  PTR eax+0x280,0x2323;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov WORD  PTR eax+0xc80,0x2323;
  mov BYTE  PTR eax+0xc82,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1680,0x23;
  ret
y5x10_47_ ENDP

PUBLIC y5x10_48_
y5x10_48_ PROC
  mov WORD  PTR eax+0x281,0x2323;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  mov BYTE  PTR eax+0x1902,0x23;
  mov BYTE  PTR eax+0x1b83,0x23;
  ret
y5x10_48_ ENDP

PUBLIC y5x10_49_
y5x10_49_ PROC
  mov WORD  PTR eax+0x280,0x2323;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov WORD  PTR eax+0xc80,0x2323;
  mov BYTE  PTR eax+0xc82,0x23;
  mov WORD  PTR eax+0xf00,0x2323;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1182,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov BYTE  PTR eax+0x1680,0x23;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_49_ ENDP

PUBLIC y5x10_50_
y5x10_50_ PROC
  mov WORD  PTR eax+0x281,0x2323;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov WORD  PTR eax+0xc81,0x2323;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  ret
y5x10_50_ ENDP

PUBLIC y5x10_51_
y5x10_51_ PROC
  mov DWORD PTR eax+0x280,0x23232323;
  mov BYTE  PTR eax+0x284,0x23;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  mov BYTE  PTR eax+0xc82,0x23;
  mov BYTE  PTR eax+0xf02,0x23;
  mov BYTE  PTR eax+0x1182,0x23;
  mov BYTE  PTR eax+0x1402,0x23;
  mov BYTE  PTR eax+0x1682,0x23;
  ret
y5x10_51_ ENDP

PUBLIC y5x10_52_
y5x10_52_ PROC
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x283,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  ret
y5x10_52_ ENDP

PUBLIC y5x10_53_
y5x10_53_ PROC
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x283,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf01,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1181,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1402,0x23;
  mov BYTE  PTR eax+0x1682,0x23;
  ret
y5x10_53_ ENDP

PUBLIC y5x10_54_
y5x10_54_ PROC
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x283,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov DWORD PTR eax+0x1180,0x23232323;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov BYTE  PTR eax+0x1680,0x23;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_54_ ENDP

PUBLIC y5x10_55_
y5x10_55_ PROC
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x283,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov WORD  PTR eax+0xa01,0x2323;
  mov WORD  PTR eax+0xc81,0x2323;
  mov WORD  PTR eax+0xf01,0x2323;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov BYTE  PTR eax+0x1680,0x23;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_55_ ENDP

PUBLIC y5x10_56_
y5x10_56_ PROC
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x284,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x504,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0x784,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc81,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf02,0x23;
  mov BYTE  PTR eax+0x1182,0x23;
  mov BYTE  PTR eax+0x1402,0x23;
  mov BYTE  PTR eax+0x1682,0x23;
  ret
y5x10_56_ ENDP

PUBLIC y5x10_57_
y5x10_57_ PROC
  mov DWORD PTR eax+0x280,0x23232323;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  mov BYTE  PTR eax+0xc81,0x23;
  mov BYTE  PTR eax+0xf01,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov DWORD PTR eax+0x1680,0x23232323;
  ret
y5x10_57_ ENDP

PUBLIC y5x10_58_
y5x10_58_ PROC
  mov WORD  PTR eax+0x281,0x2323;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  mov BYTE  PTR eax+0xc81,0x23;
  mov BYTE  PTR eax+0xf01,0x23;
  mov BYTE  PTR eax+0x1181,0x23;
  mov BYTE  PTR eax+0x1401,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  ret
y5x10_58_ ENDP

PUBLIC y5x10_59_
y5x10_59_ PROC
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  mov BYTE  PTR eax+0xc82,0x23;
  mov BYTE  PTR eax+0xf02,0x23;
  mov BYTE  PTR eax+0x1182,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_59_ ENDP

PUBLIC y5x10_60_
y5x10_60_ PROC
  mov WORD  PTR eax+0x281,0x2323;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  mov BYTE  PTR eax+0xc82,0x23;
  mov BYTE  PTR eax+0xf02,0x23;
  mov BYTE  PTR eax+0x1182,0x23;
  mov BYTE  PTR eax+0x1402,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  ret
y5x10_60_ ENDP

PUBLIC y5x10_61_
y5x10_61_ PROC
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  ret
y5x10_61_ ENDP

PUBLIC y5x10_62_
y5x10_62_ PROC
  mov DWORD PTR eax+0x1b80,0x23232323;
  mov BYTE  PTR eax+0x1b84,0x23;
  ret
y5x10_62_ ENDP

PUBLIC y5x10_63_
y5x10_63_ PROC
  mov WORD  PTR eax+0x1,0x2323;
  mov WORD  PTR eax+0x281,0x2323;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  ret
y5x10_63_ ENDP

PUBLIC y5x10_64_
y5x10_64_ PROC
  mov WORD  PTR eax+0xa01,0x2323;
  mov BYTE  PTR eax+0xc83,0x23;
  mov WORD  PTR eax+0xf01,0x2323;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_64_ ENDP

PUBLIC y5x10_65_
y5x10_65_ PROC
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov WORD  PTR eax+0xa00,0x2323;
  mov BYTE  PTR eax+0xa02,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov WORD  PTR eax+0x1680,0x2323;
  mov BYTE  PTR eax+0x1682,0x23;
  ret
y5x10_65_ ENDP

PUBLIC y5x10_66_
y5x10_66_ PROC
  mov WORD  PTR eax+0xa01,0x2323;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_66_ ENDP

PUBLIC y5x10_67_
y5x10_67_ PROC
  mov BYTE  PTR eax+0x283,0x23;
  mov BYTE  PTR eax+0x503,0x23;
  mov BYTE  PTR eax+0x783,0x23;
  mov WORD  PTR eax+0xa01,0x2323;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_67_ ENDP

PUBLIC y5x10_68_
y5x10_68_ PROC
  mov WORD  PTR eax+0xa01,0x2323;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov DWORD PTR eax+0x1180,0x23232323;
  mov BYTE  PTR eax+0x1400,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_68_ ENDP

PUBLIC y5x10_69_
y5x10_69_ PROC
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x781,0x23;
  mov WORD  PTR eax+0xa00,0x2323;
  mov BYTE  PTR eax+0xa02,0x23;
  mov BYTE  PTR eax+0xc81,0x23;
  mov BYTE  PTR eax+0xf01,0x23;
  mov BYTE  PTR eax+0x1181,0x23;
  mov BYTE  PTR eax+0x1401,0x23;
  mov BYTE  PTR eax+0x1681,0x23;
  ret
y5x10_69_ ENDP

PUBLIC y5x10_70_
y5x10_70_ PROC
  mov WORD  PTR eax+0xa01,0x2323;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  mov BYTE  PTR eax+0x1683,0x23;
  mov BYTE  PTR eax+0x1903,0x23;
  mov WORD  PTR eax+0x1b81,0x2323;
  ret
y5x10_70_ ENDP

PUBLIC y5x10_71_
y5x10_71_ PROC
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov WORD  PTR eax+0xa00,0x2323;
  mov BYTE  PTR eax+0xa02,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov BYTE  PTR eax+0x1680,0x23;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_71_ ENDP

PUBLIC y5x10_72_
y5x10_72_ PROC
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  mov BYTE  PTR eax+0xc82,0x23;
  mov BYTE  PTR eax+0xf02,0x23;
  mov BYTE  PTR eax+0x1182,0x23;
  mov BYTE  PTR eax+0x1402,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_72_ ENDP

PUBLIC y5x10_73_
y5x10_73_ PROC
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  mov BYTE  PTR eax+0xc82,0x23;
  mov BYTE  PTR eax+0xf02,0x23;
  mov BYTE  PTR eax+0x1182,0x23;
  mov BYTE  PTR eax+0x1402,0x23;
  mov BYTE  PTR eax+0x1682,0x23;
  mov BYTE  PTR eax+0x1900,0x23;
  mov BYTE  PTR eax+0x1902,0x23;
  mov BYTE  PTR eax+0x1b81,0x23;
  ret
y5x10_73_ ENDP

PUBLIC y5x10_74_
y5x10_74_ PROC
  mov BYTE  PTR eax+0x280,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x780,0x23;
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc82,0x23;
  mov WORD  PTR eax+0xf00,0x2323;
  mov WORD  PTR eax+0x1180,0x2323;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1402,0x23;
  mov BYTE  PTR eax+0x1680,0x23;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_74_ ENDP

PUBLIC y5x10_75_
y5x10_75_ PROC
  mov WORD  PTR eax+0x281,0x2323;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  mov BYTE  PTR eax+0xc82,0x23;
  mov BYTE  PTR eax+0xf02,0x23;
  mov BYTE  PTR eax+0x1182,0x23;
  mov BYTE  PTR eax+0x1402,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_75_ ENDP

PUBLIC y5x10_76_
y5x10_76_ PROC
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov DWORD PTR eax+0xc80,0x23232323;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov BYTE  PTR eax+0x1680,0x23;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_76_ ENDP

PUBLIC y5x10_77_
y5x10_77_ PROC
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  mov WORD  PTR eax+0xc80,0x2323;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov BYTE  PTR eax+0x1680,0x23;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_77_ ENDP

PUBLIC y5x10_78_
y5x10_78_ PROC
  mov WORD  PTR eax+0xa01,0x2323;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  ret
y5x10_78_ ENDP

PUBLIC y5x10_79_
y5x10_79_ PROC
  mov WORD  PTR eax+0xa00,0x2323;
  mov BYTE  PTR eax+0xa02,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov WORD  PTR eax+0x1680,0x2323;
  mov BYTE  PTR eax+0x1682,0x23;
  mov BYTE  PTR eax+0x1900,0x23;
  mov BYTE  PTR eax+0x1b80,0x23;
  ret
y5x10_79_ ENDP

PUBLIC y5x10_80_
y5x10_80_ PROC
  mov WORD  PTR eax+0xa01,0x2323;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  mov BYTE  PTR eax+0x1683,0x23;
  mov BYTE  PTR eax+0x1903,0x23;
  mov BYTE  PTR eax+0x1b83,0x23;
  ret
y5x10_80_ ENDP

PUBLIC y5x10_81_
y5x10_81_ PROC
  mov BYTE  PTR eax+0xa00,0x23;
  mov WORD  PTR eax+0xa02,0x2323;
  mov BYTE  PTR eax+0xc81,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf01,0x23;
  mov BYTE  PTR eax+0x1181,0x23;
  mov BYTE  PTR eax+0x1401,0x23;
  mov BYTE  PTR eax+0x1681,0x23;
  ret
y5x10_81_ ENDP

PUBLIC y5x10_82_
y5x10_82_ PROC
  mov WORD  PTR eax+0xa01,0x2323;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf01,0x23;
  mov BYTE  PTR eax+0x1182,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  ret
y5x10_82_ ENDP

PUBLIC y5x10_83_
y5x10_83_ PROC
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x781,0x23;
  mov WORD  PTR eax+0xa00,0x2323;
  mov BYTE  PTR eax+0xa02,0x23;
  mov BYTE  PTR eax+0xc81,0x23;
  mov BYTE  PTR eax+0xf01,0x23;
  mov BYTE  PTR eax+0x1181,0x23;
  mov BYTE  PTR eax+0x1401,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  ret
y5x10_83_ ENDP

PUBLIC y5x10_84_
y5x10_84_ PROC
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_84_ ENDP

PUBLIC y5x10_85_
y5x10_85_ PROC
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf01,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1181,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1402,0x23;
  mov BYTE  PTR eax+0x1682,0x23;
  ret
y5x10_85_ ENDP

PUBLIC y5x10_86_
y5x10_86_ PROC
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov DWORD PTR eax+0x1400,0x23232323;
  mov BYTE  PTR eax+0x1680,0x23;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_86_ ENDP

PUBLIC y5x10_87_
y5x10_87_ PROC
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov WORD  PTR eax+0xf01,0x2323;
  mov WORD  PTR eax+0x1181,0x2323;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov BYTE  PTR eax+0x1680,0x23;
  mov BYTE  PTR eax+0x1683,0x23;
  ret
y5x10_87_ ENDP

PUBLIC y5x10_88_
y5x10_88_ PROC
  mov BYTE  PTR eax+0xa00,0x23;
  mov BYTE  PTR eax+0xa03,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf00,0x23;
  mov BYTE  PTR eax+0xf03,0x23;
  mov BYTE  PTR eax+0x1180,0x23;
  mov BYTE  PTR eax+0x1183,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov BYTE  PTR eax+0x1403,0x23;
  mov WORD  PTR eax+0x1681,0x2323;
  mov BYTE  PTR eax+0x1683,0x23;
  mov BYTE  PTR eax+0x1903,0x23;
  mov WORD  PTR eax+0x1b80,0x2323;
  mov BYTE  PTR eax+0x1b82,0x23;
  ret
y5x10_88_ ENDP

PUBLIC y5x10_89_
y5x10_89_ PROC
  mov DWORD PTR eax+0xa00,0x23232323;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf02,0x23;
  mov BYTE  PTR eax+0x1181,0x23;
  mov BYTE  PTR eax+0x1400,0x23;
  mov DWORD PTR eax+0x1680,0x23232323;
  ret
y5x10_89_ ENDP

PUBLIC y5x10_90_
y5x10_90_ PROC
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x501,0x23;
  mov BYTE  PTR eax+0x781,0x23;
  mov BYTE  PTR eax+0xa01,0x23;
  mov BYTE  PTR eax+0xc80,0x23;
  mov BYTE  PTR eax+0xf01,0x23;
  mov BYTE  PTR eax+0x1181,0x23;
  mov BYTE  PTR eax+0x1401,0x23;
  mov BYTE  PTR eax+0x1682,0x23;
  ret
y5x10_90_ ENDP

PUBLIC y5x10_91_
y5x10_91_ PROC
  mov BYTE  PTR eax+0x2,0x23;
  mov BYTE  PTR eax+0x282,0x23;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xc82,0x23;
  mov BYTE  PTR eax+0xf02,0x23;
  mov BYTE  PTR eax+0x1182,0x23;
  mov BYTE  PTR eax+0x1402,0x23;
  mov BYTE  PTR eax+0x1682,0x23;
  ret
y5x10_91_ ENDP

PUBLIC y5x10_92_
y5x10_92_ PROC
  mov BYTE  PTR eax+0x281,0x23;
  mov BYTE  PTR eax+0x502,0x23;
  mov BYTE  PTR eax+0x782,0x23;
  mov BYTE  PTR eax+0xa02,0x23;
  mov BYTE  PTR eax+0xc83,0x23;
  mov BYTE  PTR eax+0xf02,0x23;
  mov BYTE  PTR eax+0x1182,0x23;
  mov BYTE  PTR eax+0x1402,0x23;
  mov BYTE  PTR eax+0x1681,0x23;
  ret
y5x10_92_ ENDP

PUBLIC y5x10_93_
y5x10_93_ PROC
  mov BYTE  PTR eax+0x281,0x23;
  mov BYTE  PTR eax+0x283,0x23;
  mov BYTE  PTR eax+0x500,0x23;
  mov BYTE  PTR eax+0x502,0x23;
  ret
y5x10_93_ ENDP

_TEXT ENDS
END
