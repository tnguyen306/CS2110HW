;;==============================================
;; NAME:
;;==============================================


.orig x3000

	LEA R0, ARRAY		; R0 is the array address

	; Start your code here



	HALT

MIN_VAL .fill 0			; Store the mininum value in the array at this label
SUM	.fill 0			; Store the sum of all of the entries in the array at this label
LENGTH	.fill 0			; Store the length of the array at this label

ARRAY	.fill 1			; The first element of the array
	.fill 3
	.fill 7
	.fill 4
	.fill 2
	.fill 9
	.fill 3
	.fill 4			; The last element of the array
	.fill -1		; -1 will follow the last element of the array	


.end
