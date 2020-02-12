
; Brandon Kelley 2716916

; Assignment 3 Question 5
; Program to output string based on grade


INCLUDE Irvine32.inc ; Include authors Library to have access to proper functions

; Proper Directives from author template
.386 
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

.data	

	; inital prompt message
	promptEnterScore byte "Student Score = ",0

	; ERROR MESSAGES
	promptLess0ERRORMESSAGE byte "ERROR: Score Can not be below 0",0
	promptOver100ERRORMESSAGE byte "ERROR: Score can not be above 100",0

	; Newline for formatting
	promptNewLine byte " ",13,10,0 ; 13 is carraige return and 10 is new line

	; Grade Ranges Messages
	promptAGradeRange byte "Excellent",0
	promptBGradeRange byte "Very Good",0
	promptCGradeRange byte "Good",0
	promptDGradeRange byte "Fair",0
	promptFGradeRange byte "Fail",0

.code
	main proc ; begin program

	mov edx, offset promptEnterScore ; prompt user for students score
	call writestring
	call readdec

	mov edx, offset promptNewLine 
	call writestring ; newline for formatting

	

	.IF eax > 100
	mov edx, offset promptOver100ERRORMESSAGE ; number entered was over 100

	.ELSEIF eax >= 90
	mov edx, offset promptAGradeRange ; number was in A range

	.ELSEIF eax >= 80
	mov edx, offset promptBGradeRange ; number was in B range

	.ELSEIF eax >= 70
	mov edx, offset promptCGradeRange ; number was in C Range

	.ELSEIF eax >= 60
	mov edx, offset promptDGradeRange ; number was in D Range

	.ELSEIF eax < 60 && eax >= 0
	mov edx, offset promptFGradeRange ; number was in F Range

	.ELSE
	mov edx, offset promptLess0ERRORMESSAGE ; number entered was less than 0

	.ENDIF

	call writestring ; Print out proper message based on grade range

	mov edx, offset promptNewLine
	call writestring ; newline for formatting

	
	
	invoke ExitProcess,0 ; Exit program

main endp
end main