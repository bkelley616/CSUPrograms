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
 
	; no data needed for this program
	
.code
main proc

	add EAX, 5		;add 5 to the EAX register
	add EDX, 5		;add 5 to the EDX register

invoke ExitProcess,0	;INVOKE expression [, arguments]
main endp				;proc and endp is like bracket.
end main