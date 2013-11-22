/*
 * user.h
 *
 *  Created on: Nov 21, 2013
 *      Author: zpriddy
 */

#ifndef USER_H_
#define USER_H_

typedef enum
{
	transfer_mode 	= 0,
	play_mode		= 1,
	idle_mode		= 2
}mode_t;

typedef enum
{
	playing_mode = 0,
	pause_mode = 1
} play_t;

#endif /* USER_H_ */
