; Brandon Kelley 2716916
; Assignment 5 Question 1
INCLUDE Irvine32.inc ; get Library

;set mode
.386
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

; L is length variable
L = 5

.data
	strArray BYTE  L DUP(0) ; intiailize array to all 0's to know if error occured rather than random values
   

.code
    main PROC
       
        mov edx, offset strArray ; get offset of array
		mov eax, L ; move length of each string to eax
        mov ecx, 20 ; call 20 times as stated in assignment directions

        getStr: ; get the str loop
            call getRanStr ; call proc
			call Crlf ; print new line
        Loop getStr ; end loop
        
        exit 
    main ENDP

    getRanStr PROC USES ecx eax ; uses ecx for counter and eax to get length of string
        mov ecx, eax ; move length of string to ecx for counter

        generate: ; generate the string

            mov eax, 26 ; used to get capital letter range
            call RandomRange
            add eax, 65 ; add to get capital
            mov edx, eax ; char to be outputted
            call WriteChar ; output char
			
        loop generate  ; end loop
		
        ret ; return
    getRanStr ENDP 

END main