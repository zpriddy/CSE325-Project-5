;***********************************************************************************************************************************
; FILE: global.inc
;
; DESCRIPTION
; Global declarations for macros, functions, and constants.
;
; AUTHORS
; Kevin R. Burger (burgerk@asu.edu)
; Computer Science & Engineering
; Arizona State University
; Tempe, AZ 85287-8809
; http://kevin.floorsoup.com
;***********************************************************************************************************************************

;===================================================================================================================================
; Assembler Macros
;
; [Ref: ARM, Ch. 4] Most assembly languages permit the programmer to declare macros which are kinda like inline functions. Now,
; before I explain CodeWarrior macros in more detail, let me explain what an inline function is.
;
; int cube(int x)
; {
;     return x * x * x;
; }
;
; int f(int x, int y)
; {
;     cube(x) + cube(y);
; }
; 
; Here would  be the ColdFire assembly code for these functions (using the standard_abi calling convention) without inlining,
; 
; _cube:                                                         Clocks          Bytes
;     link       a6, #0        ; Create stack frame              2               4
;     move.l     8(a6), d0     ; d0 <- x                         2               4
;     move.l     d0, d1        ; d1 <- x                         1               2
;     muls.l     d0, d0        ; d0 <- x^2                       18              4
;     muls.l     d1, d0        ; d0 <- x^3                       18              4
;     unlk       a6            ; Destroy stack frame             2               2
;     rts                                                        5 (48 clocks)   2 (22 bytes)
;  
; _f:                                                            Clocks          Bytes
;     link       a6, #0        ; Create stack frame              2               4
;     move.l     8(a6), -(a7)  ; Push x                          2               4
;     jsr        _cube         ; d0 <- x^3                       3 + 48          6
;     move.l     d0, d2        ; d2 <- x^3                       1               2
;     move.l     12(a6), -(a7) ; Push y                          2               4
;     jsr        _cube         ; d0 <- y^3                       3 + 48          6   
;     add.l      d2, d0        ; d0 <- x^3 + y^3                 1               2
;     unlk       a6            ; Destroy stack frame             2               2 
;     rts                                                        5 (117 clocks)  2 (32 bytes)
; 
; Therefore, f(x, y) will take at least 117 clocks (I say at least, because of the timing assumptions discussed in Section 9.1 of
; the IMUM). Note the number of bytes for cube() and f() is 54. Now, the code with inlining,
;
; _f:                                                            Clocks          Bytes
;     link       a6, #0        ; Create stack frame              2               4
;     move.l     8(a6), d0     ; d0 <- x                         2               4
;     move.l     d0, d1        ; d1 <- x                         1               2
;     muls.l     d0, d0        ; d0 <- x^2                       18              4
;     muls.l     d1, d0        ; d0 <- x^3                       18              4
;     move.l     d0, d2        ; d2 <- x^3                       1               2
;     move.l     12(a6), d0    ; d0 <- y                         2               4
;     move.l     d0, d1        ; d1 <- y                         1               2
;     muls.l     d0, d0        ; d0 <- y^2                       18              4
;     muls.l     d1, d0        ; d0 <- y^3                       18              4
;     add.l      d2, d0        ; d0 <- x^3 + y^3                 1               2
;     unlk       a6            ; Destroy stack frame             2               2
;     rts                                                        5 (89 clocks)   2 (42 bytes)
; 
; Inlining cube() reduce the execution time of f() from 117 to 89 clocks, a savings of 28 clocks which is almost 24%. The saved
; clock cycles are the ones that involved: pushing the parameters on the stack, calling the function, creating and destroying
; the stack frame, and returning from the function. And that is only one function in what could be a very large program. So
; imagine the savings if we inlined every function! Well, that *would* speed things up. However, you might have overlooked the
; column labeled Bytes. In the non-inlined version of the code, the size of f() was 32 bytes, but in the inlined code it was 42
; bytes, so f() is larger. In general, injudicious use of inlining can cause code bloat; once again we see a common tradeoff in
; computing: you can often trade space for time or vice versa.
;
; Note: if you are astute, you might observe that in the non-inlined version the total size of cube() and f() combined is 54 bytes,
; whereas in the inlined version, cube() disappears and the total size of the code is only 42 bytes. So, the inlined version of
; cube() results in code that is both smaller and faster, which goes to show that whoever wrote the code this way didn't have a
; good understanding of computer architecture!
;
; Of course, this happens in this case because cube() is a reasonably small function and we only called it twice. In general,
; inlining works best when the inlined function is not too large and is not called too many times. Generally, C and C++ compilers
; will perform automatic inlining of functions for you, i.e., if you enable that option.
;
; Now, getting back to macros. In CodeWarrior, the general syntax for declaring a macro is,
;
; name: .macro [ args, ... ]
;     instructions
; .endm
;
; Macro arguments are like function parameters, they are just a placeholder for some "value" that will be used with the macro when
; it is expanded. Let's take an example,
;
; _f:
;     link      a6, #0
;     move      8(a6), d0
;     ...
;     push      d0
;     ...
;     pop       d3
;     ...
;     rts
;
; When push is expanded, "value" becomes d0, and the instructions for the macro are inserted directly into the code at that point,
;
; _f:
;     link      a6, #0
;     move      8(a6), d0
;     ...
;     move.l    d0, -(a7)  ; Push Macro expanded here
;     ...
;     move.l    (a7)+, d1  ; Pop macro expanded here
;     ...
;     rts
;
; Macros are incredibly useful in assembly language programming. Judicious use can make the code more readable, and they can make
; more complex tasks -- that would normally take several instructions -- simpler to write.
;===================================================================================================================================

;-----------------------------------------------------------------------------------------------------------------------------------
; Macro:       dec
; Args:        Dx
; Description: Decrements the Dx register.
; Usage:       dec d0  ; d0 <- d0 - 1
;-----------------------------------------------------------------------------------------------------------------------------------
dec: .macro dreg
    subq.l     #1, dreg
.endm

;-----------------------------------------------------------------------------------------------------------------------------------
; Macro:       inc
; Args:        Dx
; Description: Increments the Dx register.
; Usage:       inc d2  ; d2 <- d2 + 1
;-----------------------------------------------------------------------------------------------------------------------------------
inc: .macro dreg
    addq.l     #1, dreg
.endm

;-----------------------------------------------------------------------------------------------------------------------------------
; Macro:       pop
; Args:        Dx
; Description: Pops the top value on the stack into Dx.
; Usage:       pop d3  ; d3 <- mem[a7]; a7 <- a7 + 4
;-----------------------------------------------------------------------------------------------------------------------------------
pop: .macro dreg
    move.l    (a7)+, dreg
.endm

;-----------------------------------------------------------------------------------------------------------------------------------
; Macro:       push
; Args:        Dx
; Description: Pushes the value in Dx onto the stack.
; Usage:       push d5  ; a7 <- a7 - 4; mem[a7] <- d5; 
;-----------------------------------------------------------------------------------------------------------------------------------
push: .macro value
    move.l    value, -(a7)
.endm

;===================================================================================================================================
; EQUATES
;===================================================================================================================================

;-----------------------------------------------------------------------------------------------------------------------------------
; IPSBAR is the Internal Peripheral Space, a 1 GB region of memory where the ColdFire internal peripherals are accessible. IPSBAR is
; a ColdFire system register that contains the address of IPS. The linker command file specifies that IPSBAR is 0x4000_0000.
;-----------------------------------------------------------------------------------------------------------------------------------
IPSBAR:      .equ $40000000