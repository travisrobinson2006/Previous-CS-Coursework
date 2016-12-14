; Travis Robinson
; CS271
; Fall2015
;Assignment 4
;Compute Composite numbers using procedures and loops
;Due 11.08.2015
;robitrav@oregonstate.edu

.386
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword
WriteString proto
WriteInt proto
WriteDec proto
Crlf proto
ReadInt proto

.data
	; declare variables here
	;byte variables declared in the functions that use them for ease of readability
	userSelection dword ?
	upperLimit equ<400>
	lowerLimit equ<1>

.code
main proc
	; write your code here
	;call on function from main
	call introduction
	call getUserData
	call showComposites
	call farewell

	invoke ExitProcess,0
main endp


;description: this function displays the intro to the program-it also displays the instructions
;receives: N/A-strings declared as global
;returns: N/A
;preconditions: N/A
;registers changed: N/A

introduction PROC

	.data ;declare values for display
	program_name_author byte "Composite Numbers Programmed by Travis Robinson",0
	program_directions byte "Enter the number of composite numbers you'd like to see, between 1 and 400.",0
	class_name byte "CS271 Fall 2015",0
	.code
	push edx
	mov edx, offset program_name_author
	call writestring
	call crlf
	mov edx, offset class_name
	call writestring
	call crlf
	mov edx,offset program_directions
	call writestring
	call crlf
	pop edx
	ret

introduction ENDP


;description: this function tells the user goodbye
;receives: N/A-strings declared as global
;returns: N/A
;preconditions: N/A
;registers changed: N/A

farewell proc

	.data
	goodbye byte "Results certified by Travis Robinson. Goodbye",0
	.code
	push edx
	mov edx, offset goodbye
	call writestring
	call crlf
	pop edx
	ret

farewell endp

;description: this function gets user data
;recieves: N/A
;returns: the number of composite numbers the user would like to use, stored in a global variable declared earlier
;preconditions: N/A
;registers changed: N/A

getUserData proc
	
	.data
	directions byte "Enter the number of composites to display [1..400]: ",0

	.code
	push edx;push unused registers onto stack for safekeeping
	push eax
	push ebx
	mov ebx,0

AskForValue:
	mov edx, offset directions
	call writestring
	call readint
	mov userSelection, eax
	call validate;
	;mov eax, ebx
	;call writeint
	;call crlf
	cmp ebx,0;validate function uses ebx to tell us if user input is okay
	je AskForValue;if it's not okay ask again
	mov eax, ebx
	;call writeint
	;call crlf
	pop ebx;return registers to original values
	pop eax
	pop edx
	ret

getUserData endp

;description: this function is called on by getUserData to ensure that the data received is within the bounds
;receives: N/A
;returns: alters ebx to determine validity of user input
;preconditions:N/A
;registers changed: modifies ebx,edx register


validate proc
	
	.data
	isBad byte "Out of range. Try again.",0

	.code
	cmp userSelection,upperLimit
	jg badValue
	cmp userSelection,lowerLimit
	jl badValue
	mov ebx,1;if value is good change ebx so calling function can continue with work
	ret

badValue:;jump here if values are bad, print statement and return to calling function
	mov edx, offset isBad
	call writestring
	call crlf
	ret

validate endp

;description: prints the number of composite values
;recieves: the number of composite values the user would like to print, as determined in a global variable
;returns: a number of composite values, printed to the screen
;preconditions: a number of composite values be declared
;registers changed: N/A

showComposites proc
	
	.data;declare variables here for ease of readability
	outerLoopCounter dword ?
	space byte "   ",0
	lastLine dword ?
	numberPerLine dword 10
	
	.code
	push eax;save registers
	push ebx
	push ecx
	push edx

	;mov ecx,userSelection
	mov eax, userSelection
	cdq
	mov ebx,10
	div ebx;divide by 10 to determine number of lines that need to be written
	add eax,1
	mov ecx, eax
	mov lastLine, edx;determine length of the last line
	mov eax,3;move this value here so loop doesn't output 1,2,3 as composites

WriteComposites: ;outer loop for writing composites, counts the number of lines
	mov outerLoopCounter,ecx
	cmp outerLoopCounter,1
	jne normalLine
	mov ebx,lastLine;if it's the last line, use the length of the last line to determine how many need to be written
	mov numberPerLine,ebx

normalLine:
	mov ecx,numberPerLine
	tenPerLine:;this loop writes out each line
		CompositeCheck:
			inc eax
			call isComposite
			cmp ebp,0
			jne CompositeCheck
			call WriteDec
			mov edx, offset space
			call WriteString

	loop tenPerLine

	mov ecx,outerLoopCounter
	call crlf
loop WriteComposites

	pop edx;restore registers
	pop ecx
	pop ebx
	pop eax
	ret

showComposites endp

;descriptions: checks to see if eax is a composite number
;receives: EAX, which it tests for being a composite value
;returns: ebx changed, based on if a value is a prime/composite
;preconditions: EAX must hold a vale
;registers changed: EBX

isComposite proc
	push edx;save registers
	push ecx
	push ebx
	push eax
	push esi
	mov ecx,eax
	cdq
	mov ebx,2;if n%2==0
	div ebx
	cmp edx,0
	je Zero;return false
	mov eax,ecx
	cdq
	mov ebx,3;if n%3==0
	div ebx
	cmp edx,0
	je Zero;return false
	mov ebx,5

Is_Prime: ;source from https://en.wikipedia.org/wiki/Primality_test
	mov eax,ebx
	mul ebx ;square i
	cdq
	cmp eax,ecx
	jg One ;if i-squared greater than n terminate while loop, return true
	mov eax,ecx
	cdq
	div ebx
	cmp edx,0
	je Zero ;n%i = 0, return false
	mov eax,ecx
	cdq
	mov esi,ebx
	add esi,2
	div esi ;n%(i+2) = 0, return false
	cmp edx,0
	je Zero
	add ebx,6 ;increment i by 6
	jmp Is_Prime ;loop through while loop again


Zero:;return false
	mov ebp,0
	jmp EndIsComposite

One:;return true
	mov ebp,1
	jmp EndIsComposite

EndIsComposite:;end function
	pop esi;restore registers
	pop eax
	pop ebx
	pop ecx
	pop edx
	ret

isComposite endp

end main
