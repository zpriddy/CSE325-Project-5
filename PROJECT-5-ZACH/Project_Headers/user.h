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
	playing = 0,
	paused 	= 1,
	restart = 2
	
}play_t;

typedef enum
{
	transfer_idle = 0,
	transfer_in_progress = 1
}transfer_mode_t;

#endif /* USER_H_ */
