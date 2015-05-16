/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev
 * jorgech3@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef EXIT_DOOR_H_
#define EXIT_DOOR_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Door.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define ExitRoomDoor_METHODS													\
	Door_METHODS;
	

#define ExitRoomDoor_SET_VTABLE(ClassName)										\
	Door_SET_VTABLE(ClassName);													\
	__VIRTUAL_SET(ClassName, ExitRoomDoor, handleMessage);

__CLASS(ExitRoomDoor);

#define ExitRoomDoor_ATTRIBUTES												\
																				\
	/* it is derivated from */													\
	Door_ATTRIBUTES																\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(ExitRoomDoor, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name);

void ExitRoomDoor_constructor(ExitRoomDoor this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name);
void ExitRoomDoor_destructor(ExitRoomDoor this);
bool ExitRoomDoor_handleMessage(ExitRoomDoor this, Telegram telegram);

#endif