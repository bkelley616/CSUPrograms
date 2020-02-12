; Brandon Kelley 2716916
; A5Q3

; get library and set mode
INCLUDE Irvine32.inc
.386
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

;data section, define gradeReceived to be tested and each grade
.data
	gradeReceived BYTE ?,0 ;grade that gets tested

	Agrade BYTE "A",0 ;define each grade string
	Bgrade BYTE "B",0
	Cgrade BYTE "C",0
	Dgrade BYTE "D",0
	Fgrade BYTE "F",0

	above100 BYTE "ERROR: the grade is above 100%",0 ;error strings for above 100 or below 0
	below0 BYTE "ERROR: the grade is below 0%",0


.code
	main PROC

		
		mov ecx,10 ; generate 10 grades

		getGrade: ; loop to get 10 grades

			mov eax,51 ; set range to 50 - 100
			call RandomRange
			add eax,50

			call CalcGrade ; call the procedure

			mov edx,0 ; use al to get grade received from procedure
			mov gradeReceived,al
			mov edx, OFFSET gradeReceived ; mov to edx for printing

			call WriteString ; write the grade to console and newline for formatting
			call Crlf

		loop getGrade

		exit ; end code
	main ENDP

	CalcGrade PROC ; CalcGrade procedure

		.IF (eax <= 100 && eax >= 0) ; inside proper range, if not go to else block

			.IF (eax <= 100) && (eax > 90) ; A range
				mov al, Agrade
			.ELSEIF (eax < 89) && (eax > 80); B range
				mov al, Bgrade
			.ELSEIF (eax < 79) && (eax > 70); C range
				mov al, Cgrade
			.ELSEIF (eax < 69) && (eax > 60); D range
				mov al, Dgrade
			.ELSE ; else F range
				mov al, Fgrade
			.ENDIF

		.ELSE ; not in range

			.IF ( eax > 100 ) ; above range
				mov edx,OFFSET above100
			.ELSE; below range
				mov edx,OFFSET below0
			.ENDIF

		.ENDIF 

		ret ; end proc

	CalcGrade ENDP
	END main