; Travis Robinson
; CS271
; Fall2015
;Assignment 3
;Integer Accumulator and Arithmetic-accumulate a negative number, find it's average
;Due 11.01.2015
;robitrav@oregonstate.edu
;using even integer function per https://en.wikipedia.org/wiki/Nearest_integer_function
;rounds up or down as usual math, except on .5, then rounds to nearest even integer

.386
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword
WriteString proto
Crlf proto
ReadString proto
ReadInt proto
WriteInt proto
WriteDec proto

.data
	; declare variables here
	;intro and user instructions here
	intro_message byte "Welcome to the Integer Acumulator by Travis Robinson",0
	intro_message2 byte "Written for CS271, Fall 2015",0
	name_prompt byte "What is your name? ",0
	hello byte "Hello, ",0
	instructions1 byte "Please enter a number in the range of [-100,-1]",0
	instructions2 byte "Enter a non-negative number when you are ready to see results",0
	ask_for_number byte "Enter number: ",0
	too_small byte "Your number was too small. It must be between -100 and -1.",0


	;variables, user input here
	upperLimit equ -1
	lowerLimit equ -100
	user_name byte 31 dup(0)
	running_total dword 0
	quotient dword 0
	remainder dword 0

	;goodbye message here, results displayers here
	goodbye byte "Goodybye, ",0
	special_goodbye byte "You chose not to enter any negative numbers.",0
	you_entered byte "You entered ",0
	valid_numbers byte " valid numbers.",0
	sum_numbers byte "The sum of your valid numbers is: ",0
	rounded_average byte "The rounded average of your numbers is: ",0

.code
main proc
	; write your code here
	
	;display intro messages
	mov edx, offset intro_message
	call writestring
	call crlf
	mov edx, offset intro_message2
	call writestring
	call crlf
	
	;ask for user name
	mov edx, offset name_prompt
	call writestring
	mov edx, offset user_name
	mov ecx, sizeof user_name
	call readstring
	call crlf
	mov edx, offset hello
	call writestring
	mov edx, offset user_name
	call writestring
	call crlf

	;give user instructions
	mov edx, offset instructions1
	call writestring
	call crlf
	mov edx, offset instructions2
	call writestring
	call crlf

	mov esi,0 ;esi used to count numbers, need to initialize it
	
UserEntersNumber:;loop goes until user enters number >=0
	mov edx, offset ask_for_number
	call writestring
	call crlf
	call readint
	cmp eax,lowerLimit ;user entered number <-100, jump to special condition ;make sure it's a valid number
	jl NumberTooSmall
	cmp eax,upperLimit ;user enters positive number, jump to end
	jg GetResults
	inc esi ;increase count of numbers
	add running_total, eax ;add number to total
	jmp UserEntersNumber ;restart loop

NumberTooSmall: ;user enters a number that is less than -100
	mov edx, offset too_small
	call writestring
	call crlf
	jmp UserEntersNumber ;jump back to the loop

GetResults:
	cmp esi,0
	je SpecialMessage ;jump to special message if no valid numbers entered
	
	mov edx, offset you_entered ;display how many valid numbers entered
	call writestring
	mov eax, esi
	call writedec
	mov edx, offset valid_numbers
	call writestring
	call crlf

	mov edx, offset sum_numbers ;display sum of numbers
	call writestring
	mov eax, running_total
	call writeint
	call crlf
	
	mov eax, running_total
	cdq
	mov ebx,esi
	idiv ebx
	mov quotient, eax;store here while division to find rounding amount
	
	mov remainder, edx
	mov eax,esi
	cdq
	mov ebx,2
	idiv ebx
	neg eax
	cmp eax,remainder
	jl WriteNumber ;if remainder < 1/2 count, round down
	cmp eax, remainder
	je QuotientEven ;if remainder == 1/2 count, find if quotient is even
	dec quotient ;else round up
	jmp WriteNumber

QuotientEven:
	mov eax, quotient
	cdq
	mov ebx,2
	idiv ebx
	cmp edx,0
	je WriteNumber ;if quotient % 2 == 0, qoutient even, round down, else round up
	dec Quotient
	jmp WriteNumber

WriteNumber:
	mov edx, offset rounded_average ;display average
	call writestring
	mov eax, quotient
	call writeint
	call crlf
	jmp EndProgram

SpecialMessage: ;if user never enters a negative
mov edx, offset special_goodbye
call writestring
call crlf
jmp EndProgram

EndProgram:
	mov edx, offset goodbye
	call writestring
	mov edx, offset user_name
	call writestring
	call crlf

	invoke ExitProcess,0
main endp
end main