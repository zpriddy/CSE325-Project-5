;***********************************************************************************************************************************
; FILE: int.inc
;
; DESCRIPTION
; Contains function and constant declarations for functions defined in int.s.
;
; AUTHORS
; Kevin R. Burger (burgerk@asu.edu)
; Computer Science & Engineering
; Arizona State University
; Tempe, AZ 85287-8809
; http://www.devlang.com
;***********************************************************************************************************************************

;===================================================================================================================================
; Public Constants
;===================================================================================================================================

adca_int_src:        .equ 49
adca_int_lvl:        .equ  2
adca_int_pri:        .equ  7

adcb_int_src:        .equ 50
adcb_int_lvl:        .equ  2
adcb_int_pri:        .equ  6

dtim0_int_src:       .equ 19
dtim0_int_lvl:       .equ  6
dtim0_int_pri:       .equ  7

dtim1_int_src:       .equ 20
dtim1_int_lvl:       .equ  6
dtim1_int_pri:       .equ  6

dtim2_int_src:       .equ 21
dtim2_int_lvl:       .equ  6
dtim2_int_pri:       .equ  5

dtim3_int_src:       .equ 22
dtim3_int_lvl:       .equ  6
dtim3_int_pri:       .equ  4

gpt0_int_src:        .equ 44
gpt0_int_level:      .equ  4
gpt0_int_priority:   .equ  7

gpt1_int_src:        .equ 45
gpt1_int_level:      .equ  4
gpt1_int_priority:   .equ  6

i2c0_int_src:        .equ 17
i2c0_int_lvl:        .equ  5
i2c0_int_pri:        .equ  7

i2c1_int_src:        .equ 62
i2c1_int_lvl:        .equ  5
i2c1_int_pri:        .equ  6

pit0_int_src:        .equ 55
pit0_int_lvl:        .equ  6
pit0_int_pri:        .equ  3

pit1_int_src:        .equ 56
pit1_int_lvl:        .equ  6
pit1_int_pri:        .equ  2

qspi_int_src:        .equ 18
qspi_int_lvl:        .equ  5
qspi_int_pri:        .equ  5

uart0_int_src:       .equ 13
uart0_int_lvl:       .equ  5
uart0_int_pri:       .equ  4

uart1_int_src:       .equ 14
uart1_int_lvl:       .equ  5
uart1_int_pri:       .equ  3

uart2_int_src:       .equ 15
uart2_int_lvl:       .equ  5
uart2_int_pri:       .equ  2

;=================================================================================================================
; Public Function Declarations
;=================================================================================================================
.extern _int_config
.extern _int_inhibit_all
.extern _int_mask_src
.extern _int_unmask_src
.extern _int_uninhibit_all