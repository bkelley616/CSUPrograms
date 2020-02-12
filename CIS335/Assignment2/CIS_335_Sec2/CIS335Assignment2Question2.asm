.386				;InstuctionInstruction list. Default is .8086

.model flat,stdcall
	;.MODEL i=is an assembler directive that specifies memory model of your program.
	;Under Win32, there's only on model, FLAT model. Where data segment and code segment share the same 4GB segment
	;STDCALL tells MASM about parameter passing convention. For Windows API, we use stdcall

.stack 4096						;Reserve 4096-Byte stack
ExitProcess PROTO dwExitCode:dword
	; FunctionName PROTO [ParameterName]: DataType, [ParameterName]: DataType, ...



	; set each month to a constant integer
	January = 1
	February = 2
	March = 3
	April = 4
	May = 5
	June = 6
	July = 7
	August = 8
	September = 9
	October = 10
	November = 11
	December = 12



.data				;reserve storage for data
	;data segment

	;use the symbolic constants to intialize the month array
	monthArray BYTE January, February, March, April, May, June, July, August, September, October, November, December 
	

.code
main proc

;No code required other than terminating the program properly

invoke ExitProcess,0	;INVOKE expression [, arguments]
main endp				;proc and endp is like bracket.
end main