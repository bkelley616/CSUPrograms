.386				;InstuctionInstruction list. Default is .8086

.model flat,stdcall
	;.MODEL i=is an assembler directive that specifies memory model of your program.
	;Under Win32, there's only on model, FLAT model. Where data segment and code segment share the same 4GB segment
	;STDCALL tells MASM about parameter passing convention. For Windows API, we use stdcall

.stack 4096						;Reserve 4096-Byte stack
ExitProcess PROTO dwExitCode:dword
	; FunctionName PROTO [ParameterName]: DataType, [ParameterName]: DataType, ...


	;define text symbolic constants
	myname EQU <"Brandon">
	school EQU <"CSU">
	city EQU <"North Royalton">
	grade EQU <"Junior">
	major EQU <"Computer Science">


.data				;reserve storage for data
	;data segment
	
	;use text symbolic constants to define variables
	username BYTE myname
	university BYTE school
	hometown BYTE city
	gradeLevel BYTE grade
	currentMajor BYTE major



.code
main proc

; no code needed other than terminating the program properly

invoke ExitProcess,0	;INVOKE expression [, arguments]
main endp				;proc and endp is like bracket.
end main