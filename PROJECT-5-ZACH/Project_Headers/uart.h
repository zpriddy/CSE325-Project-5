/*
 * uart.h
 *
 *  Created on: Nov 12, 2013
 *      Author: brianblanchard
 */

#ifndef UART_H_
#define UART_H_
#include "int.h"

typedef enum {
	even_parity = 0x0,
	odd_parity = 0x1,
	no_parity = 0x4
} parity;

typedef enum {
	five_bits = 5,
	six_bits = 6,
	seven_bits = 7,
	eight_bits = 3
} bits_per_character;

typedef enum {
	sb_0 = 0x0000,
	sb_1 = 0x0001,
	sb_2 = 0x0010,
	sb_3 = 0x0011,
	sb_4 = 0x0100,
	sb_5 = 0x0101,
	sb_6 = 0x0110,
	sb_7 = 0x0111,
	sb_8 = 0x1000,
	sb_9 = 0x1001,
	sb_10 = 0x1010,
	sb_11 = 0x1011,
	sb_12 = 0x1100,
	sb_13 = 0x1101,
	sb_14 = 0x1110,
	sb_15 = 0x1111
} sb_field;

typedef enum {
	stop_bits_1 = 1,
	stop_bits_2 = 2
} stop_bits;

typedef enum {
	uart_0,
	uart_1,
	uart_2
} uart;

void uart_channel_init(int, int, parity, bits_per_character, stop_bits, int, int, int_isr);
void uart_channel_enable(uart);
char uart_channel_getchar(uart);
void uart_channel_disable(uart);

#endif /* UART_H_ */