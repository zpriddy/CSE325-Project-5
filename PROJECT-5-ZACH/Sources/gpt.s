;***********************************************************************************************************************************
; FILE: gpt.s
;
; DESCRIPTION
; GPT module related functions.
;***********************************************************************************************************************************
#include "global.inc"  ; Included for IPSBAR
#include "gpt.inc"     ; Included for enumerated values

;===================================================================================================================================
; GPT registers
;
; Look at Table 25-3 on pp. 25-3 to 25-4 in the IMRM. The base address of the GPT register space is IPSBAR + 0x1A_0000. Table 25-3
; lists all of the GPT registers and their offsets from IPSBAR. Note that all of the GPT registers are 8-bits.
;===================================================================================================================================
GPT_BASE      	.equ IPSBAR + $1A0000
GPT_GPTCNT    	.equ GPT_BASE + $0004  ; 8-bit reg
GPT_GPTCTL2   	.equ GPT_BASE + $000B  ; 8-bit reg
GPT_GPTDDR    	.equ GPT_BASE + $001E
GPT_GPTFLG1		.equ GPT_BASE + $000E
GPT_GPTIE    	.equ GPT_BASE + $000C
GPT_GPTIOS   	.equ GPT_BASE + $0000
GPT_GPTPORT   	.equ GPT_BASE + $001D
GPT_GPTSCR1   	.equ GPT_BASE + $0006
GPT_GPTSCR2  	.equ GPT_BASE + $000D

;===================================================================================================================================
; Public Functions
;
; Public functions are specified using the .global directive (these names are exported to the linker so other object code files can
; reference these functions).
;===================================================================================================================================


.global _gpt_clr_flag
.global _gpt_disable
.global _gpt_enable
.global _gpt_incap_config

;===================================================================================================================================
; Text Section
;===================================================================================================================================

.text

;-----------------------------------------------------------------------------------------------------------------------------------
; FUNCTION: __declspec(register_abi) void gpt_clr_flag(gpt_pin p_pin)
;
; INPUT PARAMS
; p_pin  d0
;
; DESCRIPTION
; Clears the interrupt request flag for p_pin.
;
; RETURNS
; Nothing
;
; REGISTER USAGE
; d0-d2, a0
;
; NOTE
; This function is intended to be called from an ISR, in particular for Lab Project 3, from uc_pushb1_isr and uc_pushb2_isr. An
; ISR it not permitted to modify ANY registers (data, address, SR[CCR]) without saving and restoring the registers. Consequently
; we save and restore d0-d2 and a0.
;
; VERY IMPORTANT NOTE
; To load the value of the GPTFLG1 register into d0, we first move the address of the register into a0 using the LEA (load effec-
; tive address) instruction. Then we use a MOVE.B instruction to move the value from (a0) to d2. Why MOVE.B rather than MOVE.L?
; Because GPTFLG1 is an 8-bit register. I got burned by this, so remember: for an 8-bit register use MOVE.B; for a 16-bit register
; use MOVE.W; and for a 32-bit register use MOVE.L.
;-----------------------------------------------------------------------------------------------------------------------------------
_gpt_clr_flag:

    link       a6, #-16                ; Create stack frame and allocate room for d0-d2 and a0
    movem.l    d0-d2/a0, (a7)          ; Save d0-d2 and a0

; GPT_GPTFLG1 |= 1 << p_pin
                                       ; d1 <- 1 (hint: MOVEQ.L)
	moveq.l		#1, d1
                                       ; d1 <- 1 << p_pin (hint: LSL.L)
	lsl.l		d0, d1
                                       ; a0 <- &GPT_GPTFLG1 (hint: LEA and use absolute addressing for the reg)
	lea		GPT_GPTFLG1, a0
                                       ; d2 <- GPT_GPTFLG1 (hint: MOVE.B)
	move.b		(a0), d2
                                       ; d2 <- GPT_GPTFLG1 | (1 << p_pin) (hint: OR.L)
	or.l		d1, d2
                                       ; GPT_GPTFLG1 = GPT_GPTFLG1 & (1 << p_pin) (hint: MOVE.B)
	move.b		d2, (a0)

    movem.l    (a7), d0-d2/a0          ; Restore d0-d2 and a0
    unlk       a6                      ; Destroy stack frame
    rts                                ; Return

;-----------------------------------------------------------------------------------------------------------------------------------
; FUNCTION: __declspec(register_abi) void gpt_disable()
;
; INPUT PARAMS
; None
;
; DESCRIPTION
; Disables the GPT module.
;
; RETURNS
; Nothing
;
; REGISTER USAGE
; d0, a0
;-----------------------------------------------------------------------------------------------------------------------------------
_gpt_disable:
; GPT_GPTSCR1 = 0x00 
                                        ; d0 <- 0 (hint: MOVEQ.L)
	moveq.l		#0, d0
                                        ; a0 <- &GPT_GPTSCR1 (hint: LEA)
	lea		GPT_GPTSCR1, a0
                                        ; GPT_GPTSCR = 0 (hint: MOVE.B)
	move.b		d0, (a0)
                                        ; return
	rts

;-----------------------------------------------------------------------------------------------------------------------------------
; FUNCTION: __declspec(register_abi) void gpt_enable()
;
; INPUT PARAMS
; None
;
; DESCRIPTION
; Enables the GPT module.
;
; RETURNS
; Nothing
;
; REGISTER USAGE
; d0, a0
;-----------------------------------------------------------------------------------------------------------------------------------
_gpt_enable:
; GPT_GPTSCR1 = 0x80
                                        ; d0 <- 0x80 (hint: MOVE.L)
	move.l		#$80, d0
                                        ; a0 <- &GPT_GPTSCR1 (hint: LEA)
	lea		GPT_GPTSCR1, a0
                                        ; GPT_GPTSCR1 = 0x80 (hint: MOVE.B)
	move.b		d0, (a0)
                                        ; Return
	rts

;-----------------------------------------------------------------------------------------------------------------------------------
; FUNCTION: __declspec(register_abi) void gpt_incap_config(gpt_pin p_pin, gpt_incap_edge p_incap_edge)
;
; INPUT PARAMS
; p_pin         d0
; p_incap_edge  d1
;
; DESCRIPTION
; Initializes pin p_pin of the GPT module for the input capture mode. The input capture edge is specified by p_incap_edge. See the
; enumerated type for gpt_incap_edge in gpt.h and gpt.inc. 
;
; RETURNS
; Nothing
;
; REGISTER USAGE
; d0-d4, a0
;
; SAVES AND RESTORES
; d3-d4
;
; NOTE
; In register_abi, the first three integer parameters as passed in d0, d1, and 2; consequently, d0 contains parameter p_pin and d1
; contains parameter p_incap_edge. In ColdFire, data registers d0-d2 and address registers a0-a1 are "scratch" registers, i.e.,
; they may be modified by the callee function without; if those registers contain values that the caller function does not want
; to be modified by the callee, then it is the responsibility of the caller to save those registers before calling the callee.
;
; On the other hand, data registers d3-d7 and address registers a2-a5 cannot be changed by the callee unless the callee first
; saves the current contents of registers to be used on the stack and restores them before returning. To summarize:
;
; Data Registers     Caller                             Callee
; d0-d2              Must save before calling callee    May modify without saving and restoring
; d3-d7              Does not have to save              Must be saved and restored
;
; Address Registers  Caller                             Callee
; a0-a1              Must save before calling callee    May modify without saving and restoring
; a2-a5              Does not have to save              Must be saved and restored
;-----------------------------------------------------------------------------------------------------------------------------------
_gpt_incap_config:

                                       ; Create stack frame and allocate 2 longwords on stack (hint: LINK)
	link		a6, #-8
                                       ; Push d3 and d4 (actually pushes d4 first) (hint: see MOVEM.L in _gpt_clr_flag)
	movem.l		d3/d4, (a7)
   
; gpt_disable()
                                       ; Allocate 2 longwords on stack so we can save d0-d1 (hint: ADDA.L or SUBA.L)
	adda.l		#-8, a7
                                       ; Push d0-d1 (hint: MOVEM.L)
	movem.l		d0/d1, (a7)
                                       ; Call _gpt_disable
	jsr        	_gpt_disable                  
                                       ; Restore d0-d1 (hint: MOVEM.L) (Note: allocd room on stack for d0-d1 is deallocd by UNLK)
	movem.l		(a7), d0/d1
	

; GPTIOS &= ~(1 << p_pin)
                                       ; d3 <- 1 (hint: MOVEQ.L)
	moveq.l		#1, d3
                                       ; d3 <- 1 << p_pin (hint: LSL.L)
	lsl.l		d0, d3
                                       ; d3 <- ~(1 << p_pin) (hint: NOT.L)
	not.l		d3
                                       ; a0 <- &GPT_GPTIOS (hint: LEA)
	lea		GPT_GPTIOS, a0
                                       ; d4 <- GPT_GPTIOS (hint: MOVE.B)
	move.b		(a0), d4
                                       ; d4 <- GPT_GPTIOS & ~(1 << p_pin) (hint: AND.L)
	and.l		d3, d4
                                       ; GPTIOS &= ~(1 << p_pin) (hint: MOVE.B)
	move.b		d4, (a0)
    
; GPTCTL2 &= ~(0x03 << (2 * p_pin)
                                       ; d4 <- p_pin (hint: MOVE.L)
	move.l		d0, d4
                                       ; d4 <- 2 * p_pin (hint: LSL.L)
	lsl.l		#2, d4
                                       ; d3 <- 0x03 (hint: MOVEQ.L)
	moveq.l		#$3, d3
                                       ; d3 <- 0x03 << (2 * p_pin) (hint: LSL.L)
	lsl.l		d4, d3
                                       ; d3 <- ~(0x03 << (2 * p_pin)) (hint: NOT.L)
	not.l		d3
                                       ; a0 <- &GPT_GPTCTL2 (hint: LEA)
	lea		GPT_GPTCTL2, a0
                                       ; d4 <- GPT_GPTCTL2 (hint: MOVE.B)
	move.b		(a0), d4
                                       ; d3 <- GPT_GPTCTL2 & ~(0x03 << (2 * p_pin)) (hint: AND.L)
	and.l		d4, d3
                                       ; GPTCTL2 &= ~(0x03 << (2 * p_pin)) (hint: MOVE.B)
	move.b		d3, (a0)

; GPTCTL2 |= p_incap_edge << (2 * p_pin)
                                       ; d4 <- p_pin (hint: MOVE.L)
	move.l		d0, d4
                                       ; d4 <- 2 * p_pin (hint: LSL.L)
	lsl.l		#1, d4
                                       ; d3 <- p_incap_edge (hint MOVE.L)
	move.l		d1, d3
                                       ; d3 <- p_incap_edge << (2 * p_pin) (hint: LSL.L)
	lsl.l		d4, d3
                                       ; d4 <- GPT_GPTCTL2 (hint: MOVE.B)
	move.b		GPT_GPTCTL2, d4
                                       ; d3 <- GPT_GPTCTL2 | p_incap_edge << (2 * p_pin) (hint: OR.L)
	or.l		d4, d3 
                                       ; GPTCTL2 |= p_incap_edge << (2 * p_pin) (hint: MOVE.B)
	move.b		d3, (a0)

; GPTIE |= 1 << p_pin
                                       ; d3 <- 1 (hint: MOVEQ.L)
	moveq.l		#1, d3
                                       ; d3 <- 1 << p_pin (hint: LSL.L)
	lsl.l		d0, d3
                                       ; a0 <- &GPT_GPTIE (hint: LEA)
	lea		GPT_GPTIE, a0
                                       ; d4 <- GPT_GPTIE (hint: MOVE.B)
	move.b		(a0), d4
                                       ; d4 <- GPT_GPTIE | 1 << p_pin (hint: OR.L)
	or.l		d3, d4
                                       ; GPTIE |= 1 << p_pin (hint: MOVE.B)
	move.b		d4, (a0)
    
; GPTFLG1 |= 1 << p_pin
                                       ; a0 <- &GPT_GPTFLG1 (hint: LEA)
	lea		GPT_GPTFLG1, a0
                                       ; d4 <- GPT_GPTFLG1 (hint: MOVE.B)
	move.b		(a0), d4
                                       ; d4 <- GPT_GPTFLG1 | 1 << p_pin (hint: OR.L)
	or.l		d3, d4
                                       ; GPTFLG1 |= 1 << p_pin (hint: MOVE.B)
	move.b		d4, (a0)
    
; GPTDDR &= ~(1 << p_pin)
                                       ; d3 <- ~(1 << p_pin) (hint: NOT.L)
	not.l		d3
                                       ; a0 <- &GPT_GPTDDR (hint: LEA)
	lea		GPT_GPTDDR, a0
                                       ; d4 <- GPT_GPTDDR (hint: MOVE.B)
	move.b		(a0), d4
                                       ; d4 <- GPT_GPTDDR & ~(1 << p_pin) (hint: AND.L)
	and.l		d3, d4
                                       ; GPTDDR &= ~(1 << p_pin) (hint: MOVE.B)
	move.b		d4, (a0)
    
  
                                       ; Restore d3-d4 (hint: MOVEM.L)
	movem.l		(a7), d3/d4
                                       ; Destroy stack fraome (hint: UNLK)
	unlk 		a6
                                       ; Return
	rts