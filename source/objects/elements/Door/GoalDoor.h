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

#ifndef GOAL_DOOR_H_
#define GOAL_DOOR_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Door.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define GoalDoor_METHODS(ClassName)																		\
	    Door_METHODS(ClassName);																		\

#define GoalDoor_SET_VTABLE(ClassName)																	\
        Door_SET_VTABLE(ClassName);																		\
        __VIRTUAL_SET(ClassName, GoalDoor, handleMessage);												\
        __VIRTUAL_SET(ClassName, GoalDoor, ready);														\
        __VIRTUAL_SET(ClassName, GoalDoor, hasDestination);												\
        __VIRTUAL_SET(ClassName, GoalDoor, canEnter);													\

__CLASS(GoalDoor);

#define GoalDoor_ATTRIBUTES																				\
        /* it is derived from */																		\
        Door_ATTRIBUTES																					\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(GoalDoor, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name);

void GoalDoor_constructor(GoalDoor this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name);
void GoalDoor_destructor(GoalDoor this);
bool GoalDoor_handleMessage(GoalDoor this, Telegram telegram);
void GoalDoor_ready(Door this);
bool GoalDoor_hasDestination(Door this);
bool GoalDoor_canEnter(GoalDoor this);


#endif
