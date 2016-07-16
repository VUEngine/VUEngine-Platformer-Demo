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

#ifndef CANNON_BALL_IDLE_H_
#define CANNON_BALL_IDLE_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <StateMachine.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define CannonBallIdle_METHODS(ClassName)																\
	    State_METHODS(ClassName);																		\

// declare the virtual methods which are redefined
#define CannonBallIdle_SET_VTABLE(ClassName)															\
        State_SET_VTABLE(ClassName)																		\
        __VIRTUAL_SET(ClassName, CannonBallIdle, enter);												\
        __VIRTUAL_SET(ClassName, CannonBallIdle, execute);												\
        __VIRTUAL_SET(ClassName, CannonBallIdle, exit);													\
        __VIRTUAL_SET(ClassName, CannonBallIdle, processMessage);                                       \

__CLASS(CannonBallIdle);

#define CannonBallIdle_ATTRIBUTES																		\
        /* inherits */																					\
        State_ATTRIBUTES																				\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

CannonBallIdle CannonBallIdle_getInstance();


#endif
