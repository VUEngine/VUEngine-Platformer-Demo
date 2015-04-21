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

#ifndef DOOR_H_
#define DOOR_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AnimatedInGameEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Door_METHODS															\
	AnimatedInGameEntity_METHODS;
	

#define Door_SET_VTABLE(ClassName)												\
	AnimatedInGameEntity_SET_VTABLE(ClassName);									\
	__VIRTUAL_SET(ClassName, Door, setExtraInfo);								\
	__VIRTUAL_SET(ClassName, Door, handleMessage);

__CLASS(Door);

#define Door_ATTRIBUTES															\
																				\
	/* it is derivated from */													\
	AnimatedInGameEntity_ATTRIBUTES												\
																				\
	/* destination of door */													\
	void (*destination)(void);													\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(Door, AnimatedInGameEntityDefinition* animatedEntityDefinition, int ID);

void Door_constructor(Door this, AnimatedInGameEntityDefinition* definition, int ID);
void Door_destructor(Door this);
void* Door_getExtraInfo(Door this);
void Door_setExtraInfo(Door this, void* extraInfo);
bool Door_handleMessage(Door this, Telegram telegram);
bool Door_hasDestination(Door this);

#endif