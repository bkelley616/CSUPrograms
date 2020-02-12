
;Brandon Kelley 2716916 Question 6 Program

include Irvine32.inc

.data
	N=5 ; hard code array size , change manually in code to get arrays of different sizes
	numArray dword N DUP(?)
	j dword ?
	k dword ?

	; Newline for formatting
	promptNewLine byte " ",13,10,0 ; 13 is carraige return and 10 is new line
	msg1 byte "First Example:",13,10,0 ; message for  first example	13 is carraige return and 10 is new line
	msg2 byte "Second Example:",13,10,0 ; message for second example	13 is carraige return and 10 is new line

	;prompts for user to enter range
	promptj byte "j = ",0 
	promptk byte "k = ",0



.code
    main proc

		
		mov edx, offset promptNewLine 
		call writestring ; newline for formatting

		mov edx, offset msg1
		call writestring ; newline for formatting

		mov edx, offset promptNewLine 
		call writestring ; newline for formatting


		mov edx, offset promptj ; prompt user for j
		call writestring
		call readint
		mov j, eax

        mov edx, offset promptk ; prompt user for k
		call writestring
		call readint
		mov k, eax

		;call procedure
        mov ESI, offset numArray
        mov ECX, N
        call generateArray



		mov edx, offset promptNewLine 
		call writestring ; newline for formatting

		mov edx, offset promptNewLine 
		call writestring ; newline for formatting




		mov edx, offset promptNewLine 
		call writestring ; newline for formatting

		mov edx, offset msg2
		call writestring ; newline for formatting

		mov edx, offset promptNewLine 
		call writestring ; newline for formatting

		mov edx, offset promptj ; prompt user for j
		call writestring
		call readint
		mov j, eax

        mov edx, offset promptk ; prompt user for k
		call writestring
		call readint
		mov k, eax

		;call procedure
        mov ESI, offset numArray
        mov ECX, N
        call generateArray

		mov edx, offset promptNewLine 
		call writestring ; newline for formatting
      
        
        exit
    main ENDP

	;procedure to generate random array
    generateArray proc
		; push proper regs
        push ecx
        push esi

        pick:

			;move range variables to eax and ebx respectfully
            mov eax, j
            mov ebx, k


            dec ebx  
            sub ebx, eax        ;subtract to get abs of range

            ;swap values to use randomRange (eax)
			mov edx,eax
			mov eax,ebx
			mov ebx,edx

            call RandomRange    ; get random int from j to k
            neg ebx                ;get negative of ebx
            sub eax, ebx        ;sub from eax to define range
            
			mov edx, offset promptNewLine 
			call writestring ; newline for formatting

            call WriteInt ; write the num

            mov [esi], eax ;go to next location
            add esi, type numArray ; go to next location base on type of numArray


        loop pick

		;pop off stack to return to proper location
        pop esi
        pop ecx
        ret

    generateArray ENDP

END main