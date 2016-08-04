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

#ifndef MOVING_ENTITY_MOVING_H_
#define MOVING_ENTITY_MOVING_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <StateMachine.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define MovingEntityMoving_METHODS(ClassName)															\
	    State_METHODS(ClassName)																		\

// declare the virtual methods which are redefined
#define MovingEntityMoving_SET_VTABLE(ClassName)														\
        State_SET_VTABLE(ClassName)																		\
        __VIRTUAL_SET(ClassName, MovingEntityMoving, enter);											\
        __VIRTUAL_SET(ClassName, MovingEntityMoving, execute);											\
        __VIRTUAL_SET(ClassName, MovingEntityMoving, exit);												\
        __VIRTUAL_SET(ClassName, MovingEntityMoving, processMessage);                                   \

__CLASS(MovingEntityMoving);

#define MovingEntityMoving_ATTRIBUTES																	\
        /* inherits */																					\
        State_ATTRIBUTES																				\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

MovingEntityMoving MovingEntityMoving_getInstance();


#endif
