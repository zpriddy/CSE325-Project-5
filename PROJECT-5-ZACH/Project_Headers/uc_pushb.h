//*******************************************************************************************************
// uc_pushb.h
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
//#include "int.h"

#ifndef UC_PUSHB_H_
#define UC_PUSHB_H_


typedef enum {
	uc_pushb_1 = 1,
	uc_pushb_2 = 2
} uc_pushb;

void uc_pushb_init(int_isr p_pb1_callback, int_isr p_pb2_callback); 
void uc_pushb_debounce(gpio_pin_t p_pin);


__declspec(interrupt) void uc_pushb1_isr();
__declspec(interrupt) void uc_pushb2_isr();

#endif /* UC_PUSHB_H_ */