//*******************************************************************************************************
// pit.h
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
// Date: Oct 24, 2013
// 
//********************************************************************************************************

#ifndef PIT_H_
#define PIT_H_

#include "int.h"

typedef enum
{
	pit_timer_0 = 0,
	pit_timer_1 = 1
}pit_timer_t;

typedef enum
{
	pit_flg_high = 1,
	pit_flg_low  = 0
}pit_flg;

void pit0_init(int_isr p_callback, int p_scaler);
void pit0_enable();
void pit0_disable();
void pit0_clr_flg();
void pit1_init(int_isr p_callback, int p_scaler);
void pit1_enable();
void pit1_disable();
void pit1_clr_flg();


__declspec(interrupt) void pit_0_handler(void);
__declspec(interrupt) void pit_1_handler(void);
#endif /* PIT_H_ */
