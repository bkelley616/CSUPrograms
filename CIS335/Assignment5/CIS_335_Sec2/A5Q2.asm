
; Brandon Kelley 2716916 
; A5Q2
; comments represent changes to previous program (didn't copy down all comments on friday)
INCLUDE Irvine32.inc


BUFMAX = 128

.data
	KEY BYTE "ABXmv#7",0 ; move key to data section, use example key given
	SPrompt BYTE " ENTER the plain text:  ",0
	sEncrypt BYTE "Cipher text:	              ",0
	sDecrypt BYTE "Decrypted:                 ",0

	buffer BYTE BUFMAX + 1 DUP(0)
	bufSize DWORD ?


	.code 
	main PROC
		call InputTheString
		call TranslateBuffer
		mov edx,OFFSET sEncrypt
		call DisplayMessage
		call TranslateBuffer
		mov edx,OFFSET sDecrypt
		call DisplayMessage

		exit
	main ENDP


;-------------------------------------------------------------
InputTheString PROC
;-------------------------------------------------------------
	pushad 
	mov	 edx, OFFSET SPrompt	;display a prompt
	call WriteString
	mov  ecx, BUFMAX	;maximum character count
	mov  edx, OFFSET buffer		;point to the buffer
	call ReadString				;input the string
	mov  bufSize, eax			;save the length
	call Crlf
	popad
	ret

InputTheString ENDP

;-------------------------------------------------------------
DisplayMessage PROC
;-------------------------------------------------------------
	pushad
	call WriteString
	mov edx, OFFSET buffer
	call WriteString
	call Crlf
	call Crlf
	popad
	ret
DisplayMessage ENDP


	;Translate Buffer
	TranslateBuffer PROC
		pushad
		mov ecx, bufSize
		mov esi,0
		mov edi,0 ; use edi as index
	L1:
		cmp KEY[edi], 0 ; compare and jump if needed
		jne L2
		mov edi,0
	L2: ; add second loop to loop over key
		mov al, KEY[edi] ; move to al to not get error between two indirect operands
		xor buffer[esi],al ; xor as specified
		inc esi
		inc edi ; increase index pointer
		loop L1

		popad
		ret
	TranslateBuffer ENDP
	END main
