/*
 * uart.c
 *
 *  Created on: Nov 12, 2013
 *      Author: brianblanchard
 */

#include "common.h"

/*******************************************
* const definitions
********************************************/
const uint32 IPSBAR_UART 				 = 0x40000000;
const uint32 IPSBAR_OFFSET               = IPSBAR_UART + 0x0000200; // QUESTION: IPSBAR not the same for different registers

#define UART_UMR(n)		   (*(vuint8 *) (IPSBAR_OFFSET + 40*(n))) // UMR1 & UMR2 registers are addressed at the same offset from IPSBAR

int_isr g_uart_callback = 0;



//=====================================
// Private function protoypes
//=====================================
__declspec(interrupt) void uart1_isr();
static void uart_ucr_misc_reset();

//=====================================
// Function Delcarations
//=====================================
void uart_channel_init(int p_n, int p_baud_rate, parity p_parity, bits_per_character p_bits, stop_bits p_stop_bits,
					   int p_level, int p_priority, int_isr p_uart_callback) {

	// Not sure if callback would be passed here

	g_uart_callback = p_uart_callback;
	

	/* Initialize GPIO port, in page 9 of the lecture 20 notes,
	RE: Initialize GPIO port UA (if n = 0) or UB (n = 1) or UC (n = 2)
	pins 0-3 for the primary function. Four function calls, for all four pins?

	*/
	switch(p_n) {
		case 0:
			gpio_port_init(gpio_port_ua, gpio_pin_0, gpio_funct_primary, gpio_data_dir_x, gpio_pin_state_x);
			gpio_port_init(gpio_port_ua, gpio_pin_1, gpio_funct_primary, gpio_data_dir_x, gpio_pin_state_x);
			gpio_port_init(gpio_port_ua, gpio_pin_2, gpio_funct_primary, gpio_data_dir_x, gpio_pin_state_x);
			gpio_port_init(gpio_port_ua, gpio_pin_3, gpio_funct_primary, gpio_data_dir_x, gpio_pin_state_x);
			break;
		case 1:
			gpio_port_init(gpio_port_ub, gpio_pin_0, gpio_funct_primary, gpio_data_dir_x, gpio_pin_state_x);
			gpio_port_init(gpio_port_ub, gpio_pin_1, gpio_funct_primary, gpio_data_dir_x, gpio_pin_state_x);
			gpio_port_init(gpio_port_ub, gpio_pin_2, gpio_funct_primary, gpio_data_dir_x, gpio_pin_state_x);
			gpio_port_init(gpio_port_ub, gpio_pin_3, gpio_funct_primary, gpio_data_dir_x, gpio_pin_state_x);
			break;
		case 2:
			gpio_port_init(gpio_port_uc, gpio_pin_0, gpio_funct_primary, gpio_data_dir_x, gpio_pin_state_x);
			gpio_port_init(gpio_port_uc, gpio_pin_1, gpio_funct_primary, gpio_data_dir_x, gpio_pin_state_x);
			gpio_port_init(gpio_port_uc, gpio_pin_2, gpio_funct_primary, gpio_data_dir_x, gpio_pin_state_x);
			gpio_port_init(gpio_port_uc, gpio_pin_3, gpio_funct_primary, gpio_data_dir_x, gpio_pin_state_x);
			break;
	}

	// Reset the rcvr by writing 010 to UCRn[MISC]
	MCF_UART_UCR(p_n) = (uint8)(0x2 << 4); // write 010 to bits [4:6]

	// Reset the xmtr by writing 011 to UCRn[MISC]
	MCF_UART_UCR(p_n) = (uint8)(0x3 << 4); // write 011 to bits [4:6]

	// Set the rcvr/xmtr clocks to the prescaled system clock by writing 1101 to UCSRn[RCS] and 1101 to UCSRn[TCS]
	MCF_UART_UCSR(p_n) = (uint8)(0xDD); // write 1101 to UCSRn[RCS]

	// Make the mode register pointer point to UMR1 by writing 001 to UCRn[MISC]
	MCF_UART_UCR(p_n) = (uint8)(0x01 << 4); // write 001 to bits [4:6]

	/*INIT UMR1n and UMR2n*/

	MCF_UART1_UMR = (uint8)((p_parity << 2) | p_bits);
	MCF_UART1_UMR = (uint8)(8*p_stop_bits - 1);

	/*END UMR */

	int x = p_baud_rate;
	//UGB1 MSB of Divider
	MCF_UART_UBG1(p_n) |= (uint8)(0x20);

	//UGB2 LSB of Divider
	MCF_UART_UBG2(p_n) |= (uint8)(0x8D);

	//Configure interrupts
	MCF_UART_UIMR(p_n) |= (uint8)(0x02);

	int int_src = 13 + p_n;
	int_config(int_src, p_level, p_priority, uart1_isr);
	int_unmask_src(int_src);

	uart_channel_enable(uart_1);
}

/* Provides a function that enables UART 1 to start listening for a packet. */

void uart_channel_enable(uart p_uart) {
	MCF_UART_UCR(p_uart) = (uint8)(0x01);
}

/* Provides an ISR which gets called when a character is received. Call a user callback function (in xfersong module) */

__declspec(interrupt) void uart1_isr() {
    if (g_uart_callback != 0) {
    	g_uart_callback(); // receiver_isr(); Receiver FIFO full or character was received.
    }
}


/* Provides a function to read and return the character received by the receiver
 (this will be called by a function in the
xfersong module). */

/* NOTE: SWOOPED from uart_support.c, we can change return data type if need be. */
char uart_channel_getchar (uart p_uart) {
    return (char)MCF_UART_URB(p_uart);
}

/* Provides a function that disables UART 2 to stop listening for a packet. */
