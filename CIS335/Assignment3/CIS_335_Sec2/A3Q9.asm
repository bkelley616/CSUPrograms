; Brandon Kelley 2716916

; Assignment 3 Question 9
; Program to reverse given string


INCLUDE Irvine32.inc ; Include authors Library to have access to proper functions

; Proper Directives from author template
.386 
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

.data ;define source, target and newline
    source BYTE "This is the CIS 335 Sec 2",0 
	target BYTE SIZEOF source DUP('0') 

	; Newline for formatting
	promptNewLine byte " ",13,10,0 ; 13 is carraige return and 10 is new line
 

.code ;need to use esi and edi for transfering operations
    main PROC ; begin program

		mov edx, OFFSET promptNewLine ; print new line for formatting
        call WriteString

        mov esi,- 1 ; start at -1? was getting leading/tailing 0 if I started at 0
        mov edi,LENGTHOF source - 1 ; dont copy null terminato /0
        mov ecx,SIZEOF source ; counter variable is size of source

    reverseString: ; loop to reveres string, have esi start at beginning of source and edi at the end of target

        mov al,source[esi] ; cant directly transfer between two variables, use itermediate register
        mov target[edi],al ; swap a byte from source to targer

        inc esi ; increment esi location
        dec edi ; decrement edi location

        loop reverseString ; end loop

        mov edx, OFFSET target ; print reversed string
        call WriteString

		mov edx, OFFSET promptNewLine ; print new line for formatting
        call WriteString

		exit

	invoke ExitProcess,0 ; end program

main endp
end main