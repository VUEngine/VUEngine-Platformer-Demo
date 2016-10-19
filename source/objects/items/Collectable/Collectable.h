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

#ifndef COLLECTABLE_H_
#define COLLECTABLE_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AnimatedInGameEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Collectable_METHODS(ClassName)																	\
	    AnimatedInGameEntity_METHODS(ClassName)														    \
		__VIRTUAL_DEC(ClassName, void, collect);														\

#define Collectable_SET_VTABLE(ClassName)																\
        AnimatedInGameEntity_SET_VTABLE(ClassName)														\
        __VIRTUAL_SET(ClassName, Collectable, setExtraInfo);											\
        __VIRTUAL_SET(ClassName, Collectable, handleMessage);											\
        __VIRTUAL_SET(ClassName, Collectable, ready);													\
        __VIRTUAL_SET(ClassName, Collectable, collect);													\

__CLASS(Collectable);

#define Collectable_ATTRIBUTES																			\
        /* it is derived from */																		\
        AnimatedInGameEntity_ATTRIBUTES																	\
        /* the item's id number in the current stage */													\
        u8 itemNumber;																					\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(Collectable, AnimatedInGameEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name);

void Collectable_constructor(Collectable this, AnimatedInGameEntityDefinition* definition, s16 id, s16 internalId, const char* const name);
void Collectable_destructor(Collectable this);
void Collectable_collect(Collectable this);
bool Collectable_handleMessage(Collectable this, Telegram telegram);
void Collectable_ready(Collectable this, u32 recursive);
void Collectable_removeFromStage(Collectable this);
void Collectable_setExtraInfo(Collectable this, void* extraInfo);


#endif
