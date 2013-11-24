//*******************************************************************************************************
// dtim.c
//
// DESCRIPTION:
//
// AUTHORS:
// 	Abdulla Al Braiki (ayalbrai@asu.edu)
//	Zachary Priddy (zpriddy@asu.edu)
//
// Computer Science & Engineering
// Arizona State University
// Tempe, AZ 85287-8809
// 
//********************************************************************************************************


#include "dtim.h"
#include "support_common.h"



/*The input parameter p_msecs is the number of milliseconds to delay. It is a 32-bit unsigned integer, so the range for
p_msecs would normally be [1, 232-1]. Since there are 1000 µs in 1 ms, this function passes 1000 ◊ p_msecs to dtim0_
busy_delay_us(). But, in order to avoid overflow when multiplying p_msecs by 1000, we must ensure that p_msecs =
4,294,967, so the real range for p_msecs is [1, 4294967]. If you pass in a value for p_msecs larger than 4,294,967 the timer
delay function will not operate correctly, so don't do that. By the way, 4,294,967 ms is approximately 4,295 sec which is
approximately 71:35 minutes.*/
void dtim0_busy_delay_ms(int p_msecs)
{
    if(p_msecs <= 4294967)
        dtim0_busy_delay_us(1000*p_msecs);
}

//The input parameter p_usecs is the number of microseconds to delay. It is a 32-bit unsigned integer, so the range for
//p_usecs is [1, 232 - 1].
void dtim0_busy_delay_us(int p_usecs)
{
	// Reset timer counter
	MCF_DTIM0_DTCN = 0;
	
	// Set reference register timeout
	MCF_DTIM0_DTRR = MCF_DTIM_DTRR_REF((uint32)(p_usecs-1));
	
	// Output reference, clear any pending DMA requests
	MCF_DTIM0_DTER |= MCF_DTIM_DTER_REF;
	
	// Enables the counter
	MCF_DTIM0_DTMR |= MCF_DTIM_DTMR_RST;
	
	while( MCF_DTIM0_DTER != (0x2)) {
			// Spin until the flag is set
	}
}


//Initializes the DTIM0 timer as described in the Lecture 5 notes.
void dtim0_init()
{
    // Set reset bit then clear it
    MCF_DTIM0_DTMR |= MCF_DTIM_DTMR_RST;
    MCF_DTIM0_DTMR &= ~(MCF_DTIM_DTMR_RST);
    
    /*MCF_DTIM0_DTMR = MCF_DTIM_DTMR_PS(79)
            | MCF_DTIM_DTMR_CE(MCF_DTIM_DTMR_CE_NONE)  // Capture Edge = Neither rising or falling
            | MCF_DTIM_DTMR_CLK_DIV16 // Divide by 16 (n = 4. 2^4)
            | MCF_DTIM_DTMR_FRR; // Free Run (keep counting even when reference register has been passed)*/
    MCF_DTIM0_DTMR = 0x4F0A;
    MCF_DTIM0_DTER |= MCF_DTIM_DTER_REF | MCF_DTIM_DTER_CAP; // Event Register is setup for reference and capture events
    MCF_DTIM0_DTRR = MCF_DTIM_DTRR_REF(0); // Clear reference register
    MCF_DTIM0_DTCR = MCF_DTIM_DTCR_CAP(0); // Clear capture register. Capture is count at which the reference register was met
    MCF_DTIM0_DTCN = MCF_DTIM_DTCN_CNT(0); // Clear counter register
    MCF_DTIM0_DTXMR = 0x40;
}
