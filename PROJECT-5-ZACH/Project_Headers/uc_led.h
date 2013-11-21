//*******************************************************************************************************
// uc_led.h
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
#ifndef UC_LED_H_
#define UC_LED_H_


void uc_led_all_off();
void uc_led_all_on();
void uc_led_init();
void uc_led_off(gpio_pin_t p_led);
void uc_led_on(gpio_pin_t p_led);
void uc_led_toggle(gpio_pin_t p_led);
void uc_led_on_num(gpio_pin_t p_led);
void uc_led_dis_bin(int b_num);
void uc_led_dis_bin_rev(int b_num);

#endif // UC_LED_H_