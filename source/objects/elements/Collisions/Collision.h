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

#ifndef COLLISION_H_
#define COLLISION_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <InanimatedInGameEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Collision_METHODS(ClassName)																	\
    	InanimatedInGameEntity_METHODS(ClassName)														\

#define Collision_SET_VTABLE(ClassName)																	\
        InanimatedInGameEntity_SET_VTABLE(ClassName)													\
        __VIRTUAL_SET(ClassName, Collision, setExtraInfo);												\

__CLASS(Collision);

#define Collision_ATTRIBUTES																			\
        InanimatedInGameEntity_ATTRIBUTES																\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(Collision, InanimatedInGameEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name);

void Collision_constructor(Collision this, InanimatedInGameEntityDefinition* definition, s16 id, s16 internalId, const char* const name);
void Collision_destructor(Collision this);
void Collision_setExtraInfo(Collision this, void* extraInfo);


#endif
