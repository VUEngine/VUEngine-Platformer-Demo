/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev <jorgech3@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation; either version 3 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program. If not,
 * see <http://www.gnu.org/licenses/>.
 */

#ifndef CANNON_BALL_MOVING_H_
#define CANNON_BALL_MOVING_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <StateMachine.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define CannonBallMoving_METHODS																		\
	State_METHODS;																						\

// declare the virtual methods which are redefined
#define CannonBallMoving_SET_VTABLE(ClassName)															\
	State_SET_VTABLE(ClassName)																			\
	__VIRTUAL_SET(ClassName, CannonBallMoving, enter);													\
	__VIRTUAL_SET(ClassName, CannonBallMoving, execute);												\
	__VIRTUAL_SET(ClassName, CannonBallMoving, exit);													\
	__VIRTUAL_SET(ClassName, CannonBallMoving, handleMessage);											\

__CLASS(CannonBallMoving);

#define CannonBallMoving_ATTRIBUTES																		\
																										\
	/* inherits */																						\
	State_ATTRIBUTES																					\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

CannonBallMoving CannonBallMoving_getInstance();


#endif