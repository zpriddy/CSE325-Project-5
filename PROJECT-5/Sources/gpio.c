/*
 * gpio.c
 *
 *  Created on: Nov 18, 2013
 *      Author: zpriddy
 */

//*******************************************************************************************************
// gpio.c
//
// DESCRIPTION:
//
// AUTHORS:
//  Abdulla Al Braiki (ayalbrai@asu.edu)
//  Zachary Priddy (zpriddy@asu.edu)
//
// Computer Science & Engineering
// Arizona State University
// Tempe, AZ 85287-8809
// 
//********************************************************************************************************
#include "common.h"

const uint32 IPSBAR = 0x40000000;
const uint32 GPIO_BASE = IPSBAR + 0x00100000;
const uint32 GPIO_DDR_BASE = GPIO_BASE + 0x18;
const uint32 GPIO_SET_BASE = GPIO_BASE + 0x30;
const uint32 GPIO_CLR_BASE = GPIO_BASE + 0x48;
const uint32 GPIO_PAR_BASE = GPIO_BASE + 0x60;
const uint32 GPIO_PORT_TC = 0x0F;
const uint32 GPIO_PORT_DD = 0x14;
const uint32 GPIO_FUNCT_GPIO = 0x00;
const uint32 GPIO_FUNCT_PRIM = 0x01;
const uint32 GPIO_FUNCT_SEC = 0x02;
const uint32 GPIO_FUNCT_TERT = 0x03;
const uint32 GPIO_DATA_DIR_IN = 0x00;
const uint32 GPIO_DATA_DIR_OUT = 0x01;

#define GPIO_SET(n) (*(vuint8 *)(GPIO_SET_BASE + (n)))
#define GPIO_DDR(n) (*(vuint8 *)(GPIO_DDR_BASE + (n)))
#define GPIO_CLR(n) (*(vuint8 *)(GPIO_CLR_BASE + (n)))
#define GPIO_PAR(n) (*(vuint8 *)(GPIO_PAR_BASE + (n)))

//------------------------------------------------------------------------------------

//Accesses the SETn (n = p_port) register and returns the state of pin p_pin (0 or 1) in bit 0 of the return value.
gpio_pin_state_t gpio_port_get_pin_state(gpio_port_t p_port, gpio_pin_t p_pin) {
    int state = (GPIO_SET(p_port) >> p_pin) & 0x1;
    return (gpio_pin_state_t) state;
}

void gpio_port_init(gpio_port_t p_port, gpio_pin_t p_pin, gpio_funct_t p_funct, gpio_data_dir_t p_data_dir,
 gpio_pin_state_t p_state) {
    switch (p_port) {
    case gpio_port_dd:
        GPIO_PAR(p_port) &= ~(0x01 << (p_pin));
        GPIO_PAR(p_port) |= (p_funct << (p_pin));
        break;
    case gpio_port_ub:
    case gpio_port_ua:
    case gpio_port_tc:
        GPIO_PAR(p_port) &= ~(0x03 << (p_pin * 2));
        GPIO_PAR(p_port) |= (p_funct << (p_pin * 2));
        break;
    case gpio_port_ta:
        GPIO_PAR(p_port) &= ~(0x03 << (p_pin * 2));
        GPIO_PAR(p_port) |= (p_funct << (p_pin * 2));
        break;
    case gpio_port_an:
    	GPIO_PAR(p_port) &= ~(0x01 << (p_pin));
    	GPIO_PAR(p_port) |= (p_funct << (p_pin));
    	break;
   
    	
    
    	
    }
    if (p_funct == gpio_funct_gpio) {
        if (p_data_dir == gpio_data_dir_in)
            GPIO_DDR(p_port) &= ~(0x01 << p_pin);
        else
            GPIO_DDR(p_port) |= (0x01 << p_pin);
    }
    if (p_data_dir == gpio_data_dir_out)
        gpio_port_set_pin_state(p_port, p_pin, p_state);
}

void gpio_port_set_pin_state(gpio_port_t p_port, gpio_pin_t p_pin, gpio_pin_state_t p_state) {
    if (p_state)
        GPIO_SET(p_port) = 1 << p_pin;
    else
        GPIO_CLR(p_port) = (uint8) ~(0x01 << p_pin);
}

