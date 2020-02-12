; Brandon Kelley 2716916

; Assignment 3 Question 6
; Program to output first seven Fib numbers starting from fib(1) = 1 and fib(2) = 1


INCLUDE Irvine32.inc ; Include authors Library to have access to proper functions

; Proper Directives from author template
.386 
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

.data
	; Newline for formatting
	promptNewLine byte " ",13,10,0 ; 13 is carraige return and 10 is new line
	tempVar dword ? ;declare tempVar for calculating fib sequence itertively

.code
main proc ;begin program

	mov	eax,1	; start at 1 and write 1 fib(1) = 1
	call writeint

		mov   ebx,0 ; start ebx at 0 so it will print out 1 for fib(2)
		mov   tempVar,1
		mov   ecx,6 ; loop counter, goes until ecx = 0

		mov edx, offset promptNewLine 
		call writestring ; newline for formatting

	Calculate:
		mov  eax,ebx    ; eax = ebx + tempVar
		add  eax,tempVar
			
		call writeint   ; display eax
		call writestring ; newline for formatting

		mov  ebx,tempVar ;swap tempVar to ebx
		mov  tempVar,eax ; swap eax tp tempVar
    Loop Calculate

	

	exit ; exit/end program
	invoke ExitProcess,0

main endp
end main