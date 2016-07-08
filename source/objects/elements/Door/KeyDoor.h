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

#ifndef KEY_DOOR_H_
#define KEY_DOOR_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Door.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define KeyDoor_METHODS																					\
	Door_METHODS;																						\

#define KeyDoor_SET_VTABLE(ClassName)																	\
	Door_SET_VTABLE(ClassName);																			\
	__VIRTUAL_SET(ClassName, KeyDoor, ready);															\
	__VIRTUAL_SET(ClassName, KeyDoor, hasDestination);													\
	__VIRTUAL_SET(ClassName, KeyDoor, setOverlapping);													\
	__VIRTUAL_SET(ClassName, KeyDoor, unsetOverlapping);												\
	__VIRTUAL_SET(ClassName, KeyDoor, canEnter);														\
	__VIRTUAL_SET(ClassName, KeyDoor, getHintType);														\

__CLASS(KeyDoor);

#define KeyDoor_ATTRIBUTES																				\
																										\
	/* it is derived from */																			\
	Door_ATTRIBUTES																						\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(KeyDoor, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name);

void KeyDoor_constructor(KeyDoor this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name);
void KeyDoor_destructor(KeyDoor this);
void KeyDoor_ready(KeyDoor this);
bool KeyDoor_hasDestination(KeyDoor this);
void KeyDoor_setOverlapping(KeyDoor this);
void KeyDoor_unsetOverlapping(KeyDoor this);
bool KeyDoor_canEnter(KeyDoor this);
u8 KeyDoor_getHintType(KeyDoor this);


#endif