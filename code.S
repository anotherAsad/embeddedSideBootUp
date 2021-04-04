.equ	TCCR0A = 0x24		; {COM0A[1:0], COM0B[1:0], 2'b00, WGM[1:0]}
.equ	TCCR0B = 0x25		; {FOC0A, FOC0B, 2'b0, WGM[2], CS[2:0]}
.equ	TCNT0  = 0x26		; TCNT0[7:0]
.equ	OCR0A  = 0x27		; OCR0A[7:0]
.equ	OCR0B  = 0x28		; OCR0B[7:0]
.equ	TIMSK0 = 0x6E		; !PORT! ; {5'b0, OCIE0B, OCIE0A, TOIE0}
.equ	TIFR   = 0x15		; {5'b0, OCF0B, OCF0A, TOV0}

.org	0x00		; reset interrupt vector
rjmp	0x40

.org	0x20		; TOV0 interrupt vector
rmjp	ISR_TIM0OV

.org	0x40
clr		r0
clr		r26			; X_HI set to 0
sei					; enable interrupts
; Setup TIMER0
out		TCCR0A, r0
ldi		r16, 0x05
out		TCCR0B, r16		; Write 3'b101 to CS[2:0] so prescalar 1/1024 is set
out		TCNT0, r0		; Init Val for TCNT
ldi		r27, TIMSK0
ldi		r16, 0x01
st		X, r16			; Enable Timer Overflow interrupt
; Main Thread
loop:
nop
nop
rjmp



ISR_TIM0OV:
; the usual blink light interrupt should follow
reti		; Interrupt flag is also cleared when this ISR is returned from
