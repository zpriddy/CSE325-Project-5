//*******************************************************************************************************
// gpio.h
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


#ifndef GPIO_H_
#define GPIO_H_

#include <support_common.h>
#include "common.h"

//int gpio_port_get_pin_state(int p_port, int p_pin);
//void gpio_port_init(int p_port, int p_pin, int p_funct, int p_data_dir, int p_state);
//void gpio_port_set_pin_state(int p_port, int p_pin, int p_state);

typedef enum {
    gpio_data_dir_in  = 0,  // Input pin
    gpio_data_dir_out = 1,  // Output pin
    gpio_data_dir_x   = 2   // Don't care
} gpio_data_dir_t;
typedef enum {
    gpio_funct_gpio      = 0x00,
    gpio_funct_primary   = 0x01,
    gpio_funct_secondary = 0x02,
    gpio_funct_tertiary  = 0x03
} gpio_funct_t;
typedef enum {
    gpio_pin_0     = 0,
    gpio_pin_1     = 1,
    gpio_pin_2     = 2,
    gpio_pin_3     = 3,
    gpio_pin_4     = 4,
    gpio_pin_5     = 5,
    gpio_pin_6     = 6,
    gpio_pin_7     = 7,
    
    uc_led_1       = 0,
    uc_led_2       = 1,
    uc_led_3       = 2,
    uc_led_4       = 3,
    
    uc_dipsw_1     = 4,
    uc_dipsw_2     = 5,
    uc_dipsw_3     = 6,
    uc_dipsw_4     = 7,
    
    rgb_led_1_comm = 4,
    rgb_led_2_comm = 6,
    rgb_led_3_comm = 7,
    
    pwm_4_pin      = 2,
    pwm_5_pin      = 2,
    pwm_6_pin      = 3,
    
    pwm_red_pin    = 2,
    pwm_green_pin  = 2,
    pwm_blue_pin   = 3,
    
    uc_pb_1        = 0,
    uc_pb_2        = 1
    
} gpio_pin_t;
typedef enum {
    gpio_pin_state_high = 1,  // High
    gpio_pin_state_low  = 0,  // Low
    gpio_pin_state_x    = 2
} gpio_pin_state_t;
typedef enum {
    gpio_port_an   = 0x0A,
    gpio_port_as   = 0x0B,
    gpio_port_dd   = 0x14,
    gpio_port_nq   = 0x08,
    gpio_port_qs   = 0x0C,
    gpio_port_ta   = 0x0E,
    gpio_port_tc   = 0x0F,
    gpio_port_te   = 0x00,
    gpio_port_tf   = 0x01,
    gpio_port_tg   = 0x02,
    gpio_port_th   = 0x03,
    gpio_port_ti   = 0x04,
    gpio_port_tj   = 0x06,
    gpio_port_ua   = 0x11,
    gpio_port_ub   = 0x12,
    gpio_port_uc   = 0x13,
    
    rgb_comm_port  = 0x0A,
    
    pwm_4_port     = 0x0F,
    pwm_5_port     = 0x0E,
    pwm_6_port     = 0x0F,
    
    pwm_red_port   = 0x0F,
    pwm_green_port = 0x0E,
    pwm_blue_port  = 0x0F
} gpio_port_t;

//================================================================================================================
// Public Function Declarations
//================================================================================================================
//----------------------------------------------------------------------------------------------------------------
// FUNCTION: gpio_port_get_pin_state()
//
// DESCRIPTION
// Accesses the SETn (n = p_port) register and returns the state of pin p_pin (0 or 1) in bit 0 of the return
// value.
//----------------------------------------------------------------------------------------------------------------
gpio_pin_state_t gpio_port_get_pin_state(gpio_port_t p_port, gpio_pin_t p_pin);
//----------------------------------------------------------------------------------------------------------------
// FUNCTION: gpio_port_init()
//
// DESCRIPTION
// Initializes pin p_pin of GPIO port p_port so the pin's function is p_funct (0, 1, 2, or 3). If the pin is
// configured for GPIO mode (p_funct = 3), set the data direction to p_data_dir (0 = output, 1 = input) and the
// initial state of the pin to p_state (0 or 1). If the pin is not configured for the GPIO function, then the
// parameters p_data_dir and p_state are not used, so any value could be passed for those parameters.
//----------------------------------------------------------------------------------------------------------------
void gpio_port_init(gpio_port_t p_port, gpio_pin_t p_pin, gpio_funct_t p_funct, gpio_data_dir_t p_data_dir,gpio_pin_state_t p_state);
//----------------------------------------------------------------------------------------------------------------
// FUNCTION: gpio_port_set_pin_state()
//
// DESCRIPTION
// Sets the state of p_pin of port p_port to p_state (gpio_pin_state_high or gpio_pin_state_low).
//----------------------------------------------------------------------------------------------------------------
void gpio_port_set_pin_state(gpio_port_t p_port, gpio_pin_t p_pin, gpio_pin_state_t p_state);


#endif // GPIO_H_