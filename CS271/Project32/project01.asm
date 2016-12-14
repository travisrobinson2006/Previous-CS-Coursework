; Travis Robinson
;CS271
;Assignment1

.386
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword
WriteString proto
WriteDec proto
Crlf proto
ReadInt proto

.data
	; declare variables here
	intro_1 BYTE "Programming Assignment 1: Elementary Arithmetic",0
	intro_2 BYTE "Enter 2 numbers, and I'll show you the sum, difference, product, quotient, and remainder." ,0
	requestFirstNumber BYTE "First Number: ",0
	requestSecondNumber BYTE "Second Number: ",0
	addition_result BYTE "The sum",0
	plus BYTE " + ",0
	minus BYTE " - ",0
	multiply BYTE " x ",0
	divide BYTE " / ",0
	equal BYTE " = ",0
	remainder BYTE " with remainder ",0
	
	goodbye BYTE "Thank you. Goodbye.",0

	num_1 dword 0
	num_2 dword 0
	sum dword 0
	difference dword 0
	product dword 0
	quotient dword 0
	modulus dword 0

.code
main proc
	; write your code here
	
	;make introduction
	mov edx, OFFSET intro_1
	call WriteString
	call Crlf
	call Crlf
	mov edx, OFFSET intro_2
	call WriteString
	call crlf

	;request number 1
	mov edx, OFFSET requestFirstNumber
	call WriteString
	call ReadInt
	mov num_1, eax
	call crlf

	;request number 2
	mov edx, OFFSET requestSecondNumber
	call WriteString
	call ReadInt
	mov num_2, eax
	call crlf

	;addition
	mov eax, 0
	mov eax, num_1
	add eax, num_2
	mov sum, eax
	mov eax, 0

	;subtraction
	mov eax, num_1
	sub eax, num_2
	mov difference, eax
	mov eax, 0

	;multiply
	mov eax, num_1
	mul num_2
	mov product, eax
	mov eax, 0

	;divide
	mov eax, num_1
	div num_2
	mov quotient, eax
	mov modulus, edx
	mov eax, 0
	mov edx, 0

	;print results
	;addition
	mov eax, num_1
	call WriteDec
	mov eax, 0
	mov edx, OFFSET plus
	call WriteString
	mov eax, num_2
	call WriteDec
	mov edx, OFFSET equal
	call WriteString
	mov eax, sum
	call WriteDec
	call crlf
	call crlf

	;subtraction
	mov eax, num_1
	call WriteDec
	mov eax, 0
	mov edx, OFFSET minus
	call WriteString
	mov eax, num_2
	call WriteDec
	mov edx, OFFSET equal
	call WriteString
	mov eax, difference
	call WriteDec
	call crlf
	call crlf

	;multiplication
	mov eax, num_1
	call WriteDec
	mov eax, 0
	mov edx, OFFSET multiply
	call WriteString
	mov eax, num_2
	call WriteDec
	mov edx, OFFSET equal
	call WriteString
	mov eax, product
	call WriteDec
	call crlf
	call crlf

	;division
	mov eax, num_1
	call WriteDec
	mov eax, 0
	mov edx, OFFSET divide
	call WriteString
	mov eax, num_2
	call WriteDec
	mov edx, OFFSET equal
	call WriteString
	mov eax, quotient
	call WriteDec
	mov edx, OFFSET remainder
	call WriteString
	mov eax, modulus
	call WriteDec
	call crlf
	call crlf

	mov edx, OFFSET goodbye
	call WriteString
	call crlf


	invoke ExitProcess,0
main endp
end main