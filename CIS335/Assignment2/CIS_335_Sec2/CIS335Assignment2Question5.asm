.386				;InstuctionInstruction list. Default is .8086

.model flat,stdcall
	;.MODEL i=is an assembler directive that specifies memory model of your program.
	;Under Win32, there's only on model, FLAT model. Where data segment and code segment share the same 4GB segment
	;STDCALL tells MASM about parameter passing convention. For Windows API, we use stdcall

.stack 4096						;Reserve 4096-Byte stack
ExitProcess PROTO dwExitCode:dword
	; FunctionName PROTO [ParameterName]: DataType, [ParameterName]: DataType, ...

.data				;reserve storage for data
	;data segment

		arrayA DWORD 210 DUP(?)						; An array of 210 uninitialized unsigned doubleword values.

		arrayB BYTE 'A', 'B', 'C', 'D', 'E'			; An array of byte and initialize it to the first 5 letters of the alphabet.

		Sec2Array WORD 8, 16						; An unsigned 16-bit integer variable named Sec2Array that uses two initializers.

		favoriteCar BYTE "Tesla Model X",0			; A string variable containing the name of your favorite car. Initialize it as a nullterminated string.

		Sec2Array2 SDWORD 20 DUP(?)					; An uninitialized array of 20 signed doublewords named Sec2Array. 

		Sec2String BYTE 200 DUP("TESTSec2") 		; A string variable containing the word “TESTSec2” repeated 200 times. 

		Array2 BYTE 2000  DUP(0)					; An array of 2000 unsigned bytes named Array2 and initialize all elements to zero. 
	

.code
main proc

;No code required other than terminating the program properly

invoke ExitProcess,0	;INVOKE expression [, arguments]
main endp				;proc and endp is like bracket.
end main