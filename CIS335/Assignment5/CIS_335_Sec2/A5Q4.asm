; Brandon Kelley 2716916
; A5Q4 Validate pin program

INCLUDE Irvine32.inc 

.data
	; response arrays
	validStr BYTE "Valid", 0
	invalidStr BYTE "Invalid", 0
	; min and max arrays
	minArray BYTE 5,1,5,3,6
	maxArray BYTE 9,5,8,4,6
	; 5 test arrays test all cases. lower,higher,lower bound, upper bound, and in range
	test1 BYTE 5,1,5,3,6 
	test2 BYTE 9,5,8,4,6
	test3 BYTE 1,1,1,1,1
	test4 BYTE 9,9,9,9,9
	test5 BYTE 6,1,5,3,6

.code ;begin code

	main PROC
	;test 1
	mov ebx, OFFSET test1 ; move first test to ebx reg
	mov esi, OFFSET minArray ; set min and max to esi and edi respectively
	mov edi, OFFSET maxArray
	call Validate_PIN

	.IF (eax == 0) ; check return value and print out correct string
		mov edx, OFFSET validStr
		call WriteString
		call Crlf
	.ELSE
		mov edx, OFFSET invalidStr
		call WriteString
		call Crlf
	.ENDIF
	;repeat for other tests


	;test 2
	mov ebx, OFFSET test2
	mov esi, OFFSET minArray
	mov edi, OFFSET maxArray
	call Validate_PIN

	.IF (eax == 0)
		mov edx, OFFSET validStr
		call WriteString
		call Crlf
	.ELSE
		mov edx, OFFSET invalidStr
		call WriteString
		call Crlf
	.ENDIF


	;test 3
	mov ebx, OFFSET test3
	mov esi, OFFSET minArray
	mov edi, OFFSET maxArray
	call Validate_PIN

	.IF (eax == 0)
		mov edx, OFFSET validStr
		call WriteString
		call Crlf
	.ELSE
		mov edx, OFFSET invalidStr
		call WriteString
		call Crlf
	.ENDIF


	;test 4
	mov ebx, OFFSET test4
	mov esi, OFFSET minArray
	mov edi, OFFSET maxArray
	call Validate_PIN

	.IF (eax == 0)
		mov edx, OFFSET validStr
		call WriteString
		call Crlf
	.ELSE
		mov edx, OFFSET invalidStr
		call WriteString
		call Crlf
	.ENDIF


	;test 5
	mov ebx, OFFSET test5
	mov esi, OFFSET minArray
	mov edi, OFFSET maxArray
	call Validate_PIN

	.IF (eax == 0)
		mov edx, OFFSET validStr
		call WriteString
		call Crlf
	.ELSE
		mov edx, OFFSET invalidStr
		call WriteString
		call Crlf
	.ENDIF

	exit
main ENDP

;Validate_PIN Proc return 0 if true 1 if false
; uses ecx,edx,esi,edi
Validate_PIN PROC uses ecx edx esi edi

	mov ecx, 5 ;pin length as loop
	mov eax, 0 ; reset eax to 0

	L1:; out loop
		mov al, [ebx] ; first digit

		.IF ( al >= [esi]) && ( al <= [edi]) ; test digit for correct range
			inc ebx; digit tested inc
			inc esi ; min inc
			inc edi ; max inc
		.ELSE ; digit not in range
			mov eax, 6 
			sub eax, ecx
			ja L2 ; jump to end
		.ENDIF
		loop L1 ; continue outer loop
		mov eax,0

		L2: 
			ret
		Validate_PIN ENDP ; end proc
END main
			