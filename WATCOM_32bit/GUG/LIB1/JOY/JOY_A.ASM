;
; GUG Joystick Handler
;  Original Code         : Bryan Wilkins
;  Asm Conversion        : Dan Hust
;  Watcom/GUG Conversion : Neil Breeden
;
; int GUGReadX1Axis();
; int GUGReadY1Axis();
; int GUGReadX2Axis();
; int GUGReadY2Axis();
; int GUGReadButton();
;

.386
DGROUP group _DATA
_DATA segment 'DATA'
_DATA ends
_TEXT segment BYTE PUBLIC USE32 'CODE'
      ASSUME CS:_TEXT
	  ASSUME DS:DGROUN

PUBLIC GUGReadX1Axis_
GUGReadX1Axis_ PROC
  cli

  push ebp	      ; save ebp
  mov  ebp,esp

  mov ah, 1                           ; Load axis mask.
  xor al,al
  xor ecx, ecx                         ; Clear counter.
  mov dx,  0201h
  out dx,  al                          ; Trigger joystick.
@X1discharge:
  in al, dx                            ; Get value from joystick.
  test al, ah
  loopnz @X1discharge                   ; Repeat until match.
  xor ax, ax
  sub ax, cx                           ; Calculate offset from counter.

  sub esp,00000008H	          ; place eax on stack for return
  mov dword ptr -8H[ebp],eax

  mov esp,ebp	  ; update stack pointer
  pop ebp		  ; restore ebp

  sti
  ret
GUGReadX1Axis_ ENDP

PUBLIC GUGReadY1Axis_
GUGReadY1Axis_ PROC
  cli

  push ebp	      ; save ebp
  mov  ebp,esp

  mov ah, 2                           ; Load axis mask.
  xor al,al
  xor ecx, ecx                         ; Clear counter.
  mov dx,  0201h
  out dx,  al                          ; Trigger joystick.
@Y1discharge:
  in al, dx                            ; Get value from joystick.
  test al, ah
  loopnz @Y1discharge                   ; Repeat until match.
  xor ax, ax
  sub ax, cx                           ; Calculate offset from counter.

  sub esp,00000008H	          ; place eax on stack for return
  mov dword ptr -8H[ebp],eax

  mov esp,ebp	  ; update stack pointer
  pop ebp		  ; restore ebp

  sti
  ret
GUGReadY1Axis_ ENDP

PUBLIC GUGReadX2Axis_
GUGReadX2Axis_ PROC
  cli

  push ebp	      ; save ebp
  mov  ebp,esp

  mov ah, 4                           ; Load axis mask.
  xor al,al
  xor ecx, ecx                         ; Clear counter.
  mov dx,  0201h
  out dx,  al                          ; Trigger joystick.
@X2discharge:
  in al, dx                            ; Get value from joystick.
  test al, ah
  loopnz @X2discharge                   ; Repeat until match.
  xor ax, ax
  sub ax, cx                           ; Calculate offset from counter.

  sub esp,00000008H	          ; place eax on stack for return
  mov dword ptr -8H[ebp],eax

  mov esp,ebp	  ; update stack pointer
  pop ebp		  ; restore ebp

  sti
  ret
GUGReadX2Axis_ ENDP

PUBLIC GUGReadY2Axis_
GUGReadY2Axis_ PROC
  cli

  push ebp	      ; save ebp
  mov  ebp,esp

  mov ah, 8                           ; Load axis mask.
  xor al,al
  xor ecx, ecx                         ; Clear counter.
  mov dx,  0201h
  out dx,  al                          ; Trigger joystick.
@Y2discharge:
  in al, dx                            ; Get value from joystick.
  test al, ah
  loopnz @Y2discharge                   ; Repeat until match.
  xor ax, ax
  sub ax, cx                           ; Calculate offset from counter.

  sub esp,00000008H	          ; place eax on stack for return
  mov dword ptr -8H[ebp],eax

  mov esp,ebp	  ; update stack pointer
  pop ebp		  ; restore ebp

  sti
  ret
GUGReadY2Axis_ ENDP


PUBLIC GUGReadButtons_
GUGReadButtons_ PROC
  cli

  push ebp	      ; save ebp
  mov  ebp,esp

  xor eax,eax
  mov dx,  0201h
  out dx,  al                          ; Trigger joystick.
  in  al, dx                           ; Get button values from joystick.
  shr al,4
  xor al,0ffH

  sub esp,00000008H	          ; place eax on stack for return
  mov dword ptr -8H[ebp],eax

  mov esp,ebp	  ; update stack pointer
  pop ebp		  ; restore ebp

  sti
  ret
GUGReadButtons_ ENDP

PUBLIC GUGX1Detect_
GUGX1Detect_ PROC
  cli

  push ebp	      ; save ebp
  mov  ebp,esp

  mov ah, 1                           ; Load axis mask.
  xor al,al
  mov ecx, 00ffffffh                   ; Clear counter.
  mov dx,  0201h
  out dx,  al                          ; Trigger joystick.
@X1detect:
  jcxz @X1notfound
  in al, dx                            ; Get value from joystick.
  test al, ah
  loopnz @X1detect                     ; Repeat until match.
  mov ax, 00000001h                    ; Return Joystick 1 found

  sub esp,00000008H	          ; place eax on stack for return
  mov dword ptr -8H[ebp],eax

  mov esp,ebp	  ; update stack pointer
  pop ebp		  ; restore ebp

  sti
  ret

@X1notfound:
  mov ax, 00000000h                     ; Return Joystick 1 NOT found

  sub esp,00000008H	                    ; place eax on stack for return
  mov dword ptr -8H[ebp],eax

  mov esp,ebp	  ; update stack pointer
  pop ebp		  ; restore ebp

  sti
  ret

GUGX1Detect_ ENDP


PUBLIC GUGX2Detect_
GUGX2Detect_ PROC
  cli

  push ebp	      ; save ebp
  mov  ebp,esp

  mov ah, 4                            ; Load axis mask.
  xor al,al
  mov ecx, 00ffffffh                   ; Clear counter.
  mov dx,  0201h
  out dx,  al                          ; Trigger joystick.
@X2detect:
  jcxz @X2notfound
  in al, dx                            ; Get value from joystick.
  test al, ah
  loopnz @X2detect                     ; Repeat until match.
  mov ax, 00000001h                    ; Return Joystick 2 found

  sub esp,00000008H	          ; place eax on stack for return
  mov dword ptr -8H[ebp],eax

  mov esp,ebp	  ; update stack pointer
  pop ebp		  ; restore ebp

  sti
  ret

@X2notfound:
  mov ax, 00000000h                     ; Return Joystick 2 NOT found

  sub esp,00000008H	                    ; place eax on stack for return
  mov dword ptr -8H[ebp],eax

  mov esp,ebp	  ; update stack pointer
  pop ebp		  ; restore ebp

  sti
  ret

GUGX2Detect_ ENDP


_TEXT ENDS
END
