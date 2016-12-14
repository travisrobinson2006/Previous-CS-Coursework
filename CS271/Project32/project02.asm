; Travis Robinson
; CS271
; Assignment 2
; Due 10/18/2015
; robitrav@oregonstate.edu

.386
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword
WriteString proto
WriteDec proto
Crlf proto
ReadString proto
ReadInt proto
SetTextColor proto


.data
	; declare variables here

	upperLimit equ 46
	
	;assignment details
	programTitle BYTE "Fibonacci Numbers",0
	programmerName BYTE "by Travis Robinson",0

	;requests and instructions for user
	requestUserName BYTE "What's your name?",0
	hello BYTE "Hello, ",0
	instructions_1 BYTE "Enter the number of Fibonacci numbers to be displayed",0
	instructions_2 BYTE "Give the number as an integer in the range [1..46]",0

	requestNumberTerms BYTE "How many terms would you like displayed?",0
	requestOutOfRange BYTE "Out of range. Please make a request in the range [1..46]",0

	;goodbye messages
	resultsCertified BYTE "Results certified by Travis Robinson",0
	goodbyeMessage BYTE "Goodbye, ",0

	;create terms
	termOne DWORD 1
	termTwo DWORD 0
	userRequest DWORD ?
	userName BYTE 31 dup(0)
	spacing BYTE "     "



.code
main proc
	; write your code here
	;mov eax,1
	;call SetTextColor

	;display intro and instructions
	mov edx, offset programTitle
	call WriteString
	call Crlf
	mov edx, offset programmerName
	call WriteString
	call Crlf
	call Crlf

	;make requests from user
	;user name request
	mov edx, offset requestUserName
	call writestring	
	mov edx, offset userName
	mov ecx, sizeof userName
	call readstring
	mov edx, offset hello
	call writestring
	mov edx, offset userName
	call writestring
	call crlf

	;number request
	mov edx, offset instructions_1
	call writestring
	call crlf
	mov edx, offset instructions_2
	call writestring
	call readint
	mov userRequest, eax

	;compare user request to number limitations
	;if user request too high, request new number
	mov eax, userRequest
	cmp userRequest, upperLimit
	jg requestAgain
	cmp userRequest, 1
	jl requestAgain
	jle requestFine

requestAgain: ;for if user requests number out of range
	mov edx, offset requestOutOfRange
	call WriteString
	call readint
	mov userRequest, eax
	cmp userRequest, upperLimit
	jg requestAgain
	cmp userRequest, 1
	jl requestAgain
	jle requestFine

requestFine: ;for if user request is in range
	
	mov esi, userRequest ;used to track number of terms printed
	;calculate fibinacci
outerLoop:	
	mov ecx,5
	innerLoop:	
		mov eax, termOne
		mov ebx, termTwo
		call writedec
		mov edx, offset spacing
		call WriteString
		dec esi ;decrement for counting
		add ebx, eax
		mov termOne, ebx
		mov termTwo, eax
		cmp esi,1
		jl endFib
		loop innerLoop
	call crlf
	cmp esi,1
	jge outerLoop

	;print fibonacci, say goodbye
endFib:
	call crlf
	mov edx, offset resultsCertified
	call WriteString
	call crlf
	mov edx, offset goodbyeMessage
	call WriteString
	mov edx, offset userName
	call WriteString
	call crlf

	invoke ExitProcess,0
main endp
end main