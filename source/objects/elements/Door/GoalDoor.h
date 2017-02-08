/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2017 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef GOAL_DOOR_H_
#define GOAL_DOOR_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Door.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define GoalDoor_METHODS(ClassName)																		\
		Door_METHODS(ClassName)																			\

#define GoalDoor_SET_VTABLE(ClassName)																	\
		Door_SET_VTABLE(ClassName)																		\
		__VIRTUAL_SET(ClassName, GoalDoor, handleMessage);												\
		__VIRTUAL_SET(ClassName, GoalDoor, ready);														\
		__VIRTUAL_SET(ClassName, GoalDoor, hasDestination);												\
		__VIRTUAL_SET(ClassName, GoalDoor, canEnter);													\

__CLASS(GoalDoor);

#define GoalDoor_ATTRIBUTES																				\
		/* it is derived from */																		\
		Door_ATTRIBUTES																					\


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(GoalDoor, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name);

void GoalDoor_constructor(GoalDoor this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name);
void GoalDoor_destructor(GoalDoor this);
bool GoalDoor_handleMessage(GoalDoor this, Telegram telegram);
void GoalDoor_ready(Door this, u32 recursive);
bool GoalDoor_hasDestination(Door this);
bool GoalDoor_canEnter(GoalDoor this);


#endif
