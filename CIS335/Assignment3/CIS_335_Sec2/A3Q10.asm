; Brandon Kelley 2716916

; Assignment 3 Question 10
; Calculate the sum of the gaps between each number in the array


INCLUDE Irvine32.inc ; Include authors Library to have access to proper functions

; Proper Directives from author template
.386 
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword
.data
	numArray DWORD 0,2,5,9,10 ;given data
	sum DWORD 0 ; cumalitive sum

	; Newline for formatting
	promptNewLine byte " ",13,10,0 ; 13 is carraige return and 10 is new line

	resultString byte "The sum of the gap is: ",0 ; format output

.code
main PROC ; begin program

	mov ecx, LENGTHOF numArray ; counter to size of array
	mov esi, OFFSET numArray ; use esi for offset of array

	mov edx, offset promptNewLine 
	call writestring ; newline for formatting

	calcSum: ; start loop

	mov eax,[esi] ; get first num
	mov ebx,[esi + TYPE numArray] ; get second num, use type of numArray (dword in this case)
	sub ebx,eax ; subtract the two to get the gap

	mov	eax,ebx ; move size of gap to eax

	add sum,ebx ; add the inviduel gap to the cumalitive sume
	add esi, TYPE numArray ; increment the pointer to the next number, dword in this case

	Loop calcSum ;end loop

	mov edx, offset resultString 
	call writestring ; print for formatting

	mov	eax,sum ; print out the sum
	call writeint

	mov edx, offset promptNewLine 
	call writestring ; newline for formatting

INVOKE ExitProcess,0 ; end program
main ENDP
END main