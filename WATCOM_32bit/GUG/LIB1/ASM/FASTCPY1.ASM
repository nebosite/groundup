;
;  void GUGFastCopy(char *from);
;  From is the address of the image buffer in system ram
;  3.36mS
;
.386
DGROUP group _DATA
_DATA  segment 'DATA'
_DATA  ends
_TEXT  segment BYTE PUBLIC USE32 'CODE'
       ASSUME CS:_TEXT
       ASSUME DS:DGROUN

PUBLIC GUGFastCopy_
GUGFastCopy_ PROC

  push esi
  push edi
  push edx
  push ecx

;  cli				  ; disable interupts

  mov  edi,0x000a0000 ; start of VGA memory
  mov  esi,eax        ; start of buffer

  mov  edx,200		  ; 200 lines to copy

label1:
  mov  ecx,80		  ; each line is 320 bytes (80 x 4 bytes)

label2:
  mov eax,[esi]	      ; fetch from buffer into eax
  mov [edi],eax		  ; store eax in VGA memory
  add esi,4			  ; moving 4 bytes at a time
  add edi,4
  dec ecx			  ; have moved 4 bytes
  jnz label2		  ; is ecx != 0 loop again

  add esi,320		  ; from offset is 640 bytes line to line (320 + 320)
  dec edx			  ; have moved another line
  jnz label1		  ; if edx != 0 loop again

;  sti				  ; reenable interupts

  pop ecx
  pop edx
  pop edi
  pop esi

  ret

GUGFastCopy_ ENDP

_TEXT ENDS
END
