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

#ifndef DOOR_H_
#define DOOR_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AnimatedInGameEntity.h>
#include <PlatformerLevelState.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												MACROS
//---------------------------------------------------------------------------------------------------------

#define DOOR_OVERLAPPING_CHECK_DELAY  100


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Door_METHODS(ClassName)																			\
        AnimatedInGameEntity_METHODS(ClassName)														\
        __VIRTUAL_DEC(ClassName, bool, hasDestination);													\
        __VIRTUAL_DEC(ClassName, void, setOverlapping);													\
        __VIRTUAL_DEC(ClassName, void, unsetOverlapping);												\
        __VIRTUAL_DEC(ClassName, bool, canEnter);														\
        __VIRTUAL_DEC(ClassName, u8, getHintType);														\

#define Door_SET_VTABLE(ClassName)																		\
        AnimatedInGameEntity_SET_VTABLE(ClassName)														\
        __VIRTUAL_SET(ClassName, Door, setExtraInfo);													\
        __VIRTUAL_SET(ClassName, Door, ready);															\
        __VIRTUAL_SET(ClassName, Door, handleMessage);													\
        __VIRTUAL_SET(ClassName, Door, hasDestination);													\
        __VIRTUAL_SET(ClassName, Door, setOverlapping);													\
        __VIRTUAL_SET(ClassName, Door, unsetOverlapping);												\
        __VIRTUAL_SET(ClassName, Door, canEnter);														\
        __VIRTUAL_SET(ClassName, Door, getHintType);													\

__CLASS(Door);

#define Door_ATTRIBUTES																					\
        /* it is derived from */																		\
        AnimatedInGameEntity_ATTRIBUTES																	\
        /* destination of door */																		\
        StageEntryPointDefinition* destinationDefinition;										    	\
        /* is door currently being overlapped by hero? */												\
        bool currentlyOverlappingHero;																	\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(Door, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name);

void Door_constructor(Door this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name);
void Door_destructor(Door this);
StageEntryPointDefinition* Door_getExtraInfo(Door this);
void Door_setExtraInfo(Door this, void* extraInfo);
void Door_ready(Door this);
bool Door_handleMessage(Door this, Telegram telegram);
bool Door_hasDestination(Door this);
void Door_onOverlapping(Door this);
void Door_setOverlapping(Door this);
void Door_unsetOverlapping(Door this);
bool Door_isOverlapping(Door this);
bool Door_canEnter(Door this);
u8 Door_getHintType(Door this);


#endif
