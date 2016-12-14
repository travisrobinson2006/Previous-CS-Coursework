; Program template
; Travis Robinson
; CS271
; Fall2015
;Assignment 5
;Generate Random Numbers, sort in descending order, and find the median
;Due 11.22.2015
;robitrav@oregonstate.edu

.386
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword
WriteString proto
WriteDec proto
Crlf proto
Randomize proto
RandomRange proto
ReadInt proto

.data
	; declare variables here
	
	;declare global constants here
	min equ<10>
	max equ<200>
	lo equ<100>
	hi equ<999>

	;declare strings here
	program_name byte "Sorting Random Integers   Programmed by Travis Robinson",0
	introduction1 byte "This program generates random numbers in the range [",0
	introduction2 byte "], displays the original list, sorts the list, and calculates the median value. Finally, it displays the list sorted in descending order.",0
	introduction_between_values byte "..",0
	request_user_input byte "How many numbers should be generated?",0
	invalid_request byte "Invalid Request.",0
	left_bracket byte " [",0
	right_bracket byte "] ",0
	space byte " ",0
	titlePreSort byte "The Unsorted Random Numbers:",0
	titlePostSort byte "The Sorted Random Numbers:",0
	median_is byte "The median is: ",0

	;declare array-use max for size, then only count used elements
	arrayList dword max dup(?)

	request dword ? ;value of the users request


.code
main proc
	; write your code here
	call Randomize ;generate random number seed
	call introduction

	push offset request ;pass request by value
	call get_data
	;mov eax,request
	;call writedec
	;call crlf

	;fill the array	
	push request
	push offset arrayList
	call fillArray

	;print before sorting
	push offset titlePreSort
	push request
	push offset arrayList
	call displayList

	;sort the array
	push request
	push offset arrayList
	call arraySort

	;find the median
	push request
	push offset arrayList
	call median

	;print after sorting
	push offset titlePostSort
	push request
	push offset arrayList
	call displayList
	invoke ExitProcess,0
main endp

;description: this function displays the intro to the program-it also displays the instructions
;receives: N/A-strings declared as global; allowed as per professor in discussion board
;returns: N/A
;preconditions: N/A ;strings declared
;registers changed: N/A
introduction PROC

	.code
	push edx
	push eax
	mov edx, offset program_name
	call writestring
	call crlf
	mov edx, offset introduction1
	call writestring
	mov eax,lo
	call writedec
	mov edx, offset introduction_between_values
	call writestring
	mov eax, hi
	call writedec
	mov edx, offset introduction2
	call writestring
	call crlf
	pop eax
	pop edx
	ret
introduction ENDP

;description: receives data from the user and puts it into the 'request' variable via reference
;receives: pointer to request
;returns: alters value of request
;preconditions: request exists
;registers changed: N/A
get_data PROC
	.code
	push ebp
	mov ebp,esp
	push edx
	push eax
	mov ebx, [ebp+8] ;8 from dword and from return address
	GetUserRequest: ;using strings as global, allowed as per professor
		mov edx, offset request_user_input
		call writestring
		mov edx, offset left_bracket
		call writestring
		mov eax, min
		call writedec
		mov edx, offset introduction_between_values
		call writestring
		mov eax,max
		call writedec
		mov edx, offset right_bracket
		call writestring
		call readint ;recieve user request
		cmp eax,min ;verify user request
		jl BadRequest
		cmp eax,max
		jg BadRequest
		jmp GoodRequest

	BadRequest: ;jump here if user enters an invalid requeset
		mov edx,offset invalid_request
		call writestring
		call crlf
		jmp GetUserRequest ;repeat until valid request received	

	GoodRequest:;request is good, store it
		mov [ebx],eax
		pop eax
		pop edx
		pop ebp
		ret 4
get_data ENDP

;description: this function fills the array with random values
;receives: pointer to array, and request as value
;returns: the array is filled
;preconditions: array must exist
;registers changed: N/A
fillArray PROC
	.code
	push ebp
	mov ebp,esp
	push eax
	push ebx
	push ecx
	push edx

	;mov edx,[ebp+8]
	
	mov ecx, [ebp+12]
	ArrayFiller:
		;select element of array
		mov esi,[ebp+8]
		mov eax,ecx
		dec eax
		mov ebx,4
		mul ebx
		add esi,eax

		;generate random values
		mov eax,hi
		sub eax,lo ;sub lo because randomRange will only generate starting at 0
		call RandomRange
		add eax,lo ;add lo back in to create proper range
		inc eax ;inc because randomRange generates between 0 and n-1

		mov [esi],eax


	loop ArrayFiller ;repeat until array is full

	pop edx
	pop ecx
	pop ebx
	pop eax
	pop ebp
	ret 8
fillArray ENDP
;description: this function displays array and receives a title string to indicate if it is pre- or post- sorted
;receives: pointer to array, array size, pointer to title
;returns: N/A
;preconditions: array and title must be pointers
;registers changed: N/A
displayList PROC
	.code
	push ebp ;store registers
	mov ebp,esp
	push eax
	push ebx
	push ecx
	push edx
	push edi
	
	mov edx, [ebp+16]
	call crlf
	call writestring
	call crlf
	mov ecx, [ebp+12]
	mov edi,10 ;edi used to determine if new line needs to be printed
	ArrayPrinter:
		;select element of array
		mov esi,[ebp+8]
		mov eax,ecx
		dec eax
		mov edx,4
		mul edx
		add esi,eax

		mov eax,[esi]
		call writedec
		dec edi ;count elements left until new line
		mov edx, offset space
		call writestring
		cmp edi,0 ;determine if a new line needs to printed
		jne noNewLine
		call crlf
		mov edi,10 ;if new line, move 10 to start count again
		noNewLine: ;come here if a new line doesn't need to be printed
	loop ArrayPrinter
	
	pop edi ;restore registers
	pop edx
	pop ecx
	pop ebx
	pop eax
	pop ebp
	ret 12 ;+12 because of pushed values
displayList ENDP
;description: this function sorts the array in descending order
;receives: pointer to array and array size
;returns: sorted array
;preconditions: array must be filled
;registers changed: N/A
arraySort proc
	.code
	push ebp
	mov ebp,esp
	push eax
	push ebx
	push ecx
	push edx
	push edi
	push esi

	;using sort function provided in assignment
	mov esi,[ebp+8] ;store array
	mov ecx,[ebp+12] ;initialize counter
	dec ecx ;array starts at 0, don't count too far
	;mov eax,0 ;eax=k
	mov edi,0 ;edi=k
	OuterLoop:
		mov ebx,edi ;ebx = i
		push edi ;store edi for use
		push ecx
		InnerLoop:
			inc edi;edi currently j
			cmp edi,[ebp+12];end loop if j>=request
			jge endInnerLoop
			mov eax,4
			mul edi
			mov edx,eax;edx now holds j*4
			mov eax,4
			push edx ;push edx because it gets cleared by mul
			mul ebx ;eax now holds i*4
			pop edx
			mov edx,[esi+edx] ;j ;compare elements
			mov eax,[esi+eax] ;i
			cmp edx,eax
			jle noChange
			mov ebx,edi

			noChange:
		jmp InnerLoop
		endInnerLoop:
		pop ecx
		pop edi;restore eax/k
		
		;exchange
		push edi
		push ebx
		push [ebp+8]
		call exchangeElements
		inc edi
		cmp edi,ecx
		jle OuterLoop

	mov eax, [ebp+12]
	cdq
	mov ebx,2
	div ebx
	mov ecx,eax

	;call reverse array because function sorts in ascending order
	push [ebp+12]
	push [ebp+8]
	call reverseArray

	pop esi
	pop edi
	pop edx
	pop ecx
	pop ebx
	pop eax
	pop ebp
	ret 8
arraySort endp
;description: this function swaps two elements
;receives: pointer to array and the index values of the elements that need to be switched
;returns: the array with swapped values
;preconditions: the array must be filled
;registers changed: N/A
exchangeElements proc
	.code
	push ebp ;store registers
	mov ebp,esp
	push eax
	push ebx
	push ecx
	push edx
	push edi
	push esi

	mov edi,4 ;multiplier because of dwords
	mov esi,[ebp+8]
	mov eax,[ebp+16]
	mul edi
	mov ebx,eax

	mov eax,[ebp+12]
	;mov ebx,[ebp+16]
	mul edi

	mov ecx,[esi+eax];store the values in registers
	mov edx,[esi+ebx]

	mov [esi+eax],edx ;assign registers to elements, swapping the element values
	mov [esi+ebx],ecx


	pop esi ;restore registers
	pop edi
	pop edx
	pop ecx
	pop ebx
	pop eax
	pop ebp
	ret 12
exchangeElements endp
;description: this function reverses the array so that it descends instead of ascending
;receives: pointer to array, array size
;returns: the array in reversed direction
;preconditions: the array must be filled, and preferably sorted sorted
;registers changed: N/A
reverseArray proc
	push ebp ;store registers
	mov ebp,esp
	push eax
	push ebx
	push ecx
	push edx
	
	;intialize values
	mov eax,[ebp+12] ;calculate number of loops to make, only doing loops = 1/2 array size or we reswap them 
	cdq
	mov ebx,2
	div ebx
	mov ecx,eax
	mov esi,[ebp+8] ;store array
	mov edx,[ebp+12] ;used for finding last element
	dec edx

	mov eax,4
	mul edx
	mov edx,eax

	mov ebx,0

	ReverseLoop: ;swap elements around, number of times = 1/2 request
		mov edi,[esi+ebx]
		mov eax,[esi+edx]
		mov [esi+edx],edi
		mov [esi+ebx],eax
		add ebx,4
		sub edx,4
	loop ReverseLoop

	pop edx
	pop ecx
	pop ebx
	pop eax
	pop ebp
	ret 8
reverseArray endp

;description: this function finds and displays the median; uses strings as global, as per professor
;receives: pointer to array, array size
;returns: median printed to console
;preconditions: array is sorted
;registers changed: N/A
median proc
	push ebp
	mov ebp,esp
	push eax
	push ebx
	push ecx
	push edx

	mov esi,[ebp+8]

	mov eax,[ebp+12]
	cdq
	mov ebx,2
	div ebx
	cmp edx,1 ;determine if the array is odd or even number of elements to determine which method needed to find median
	je oddAmount

	evenAmount:;jump here if even number of values,rounded using nearest integer
		mov eax,[ebp+12] ;not necessary but will do for consistency/error control/easier to update
		cdq
		mov ebx,2
		div ebx
		mov ebx,eax
		inc ebx

		mov ecx,4 ;multiply by 4 becuase of dword
		mul ecx
		mov ecx,eax

		mov eax,ebx
		mov ebx,4
		mul ebx
		sub eax,8 ;subtract 8 due to get to correct element(was grabbing from the two away from the center value it was supposed to;should've corrected properly but this was quicker and I'm short time)

		mov ebx,[esi+eax] ;grab the values to find median
		mov ecx,[esi+ecx]


		mov eax,ebx ;find median
		add eax,ecx
		mov ebx,2
		div ebx

		cmp edx,1 ;round to nearest integer-so if median is 21.5, rounds to 22; if median is 21.0, stays 21.0
		jl dontRound
		inc eax
		dontRound: ;come here if rounding not necessary
			mov edx, offset median_is ;allowed to refer to strings, per professor
			call crlf
			call crlf
			call writestring
			call writedec
			call crlf		
			jmp endMedian
				
	oddAmount:;jump here if an odd number of values
		mov eax,[ebp+12] ;not necessary but will do for consistency/error control/easier to update
		cdq
		mov ebx,2
		div ebx

		mov edx, offset median_is
		call crlf
		call crlf
		call writestring
		mov ebx,4
		mul ebx
		mov eax,[esi+eax] ;grab center element and print
		call writedec
		call crlf

	jmp endMedian

	endMedian:
		pop edx
		pop ecx
		pop ebx
		pop eax
		pop ebp

		ret 8
median endp

end main