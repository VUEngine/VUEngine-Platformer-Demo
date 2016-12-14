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

#ifndef TRANSPARENT_ANIMATED_IN_GAME_ENTITY_H_
#define TRANSPARENT_ANIMATED_IN_GAME_ENTITY_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AnimatedInGameEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define TransparentAnimatedInGameEntity_METHODS(ClassName)												\
    	AnimatedInGameEntity_METHODS(ClassName)															\

#define TransparentAnimatedInGameEntity_SET_VTABLE(ClassName)											\
        AnimatedInGameEntity_SET_VTABLE(ClassName)														\
        __VIRTUAL_SET(ClassName, TransparentAnimatedInGameEntity, update);								\

__CLASS(TransparentAnimatedInGameEntity);

#define TransparentAnimatedInGameEntity_ATTRIBUTES														\
        AnimatedInGameEntity_ATTRIBUTES																	\
        bool visible;																					\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(TransparentAnimatedInGameEntity, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name);

void TransparentAnimatedInGameEntity_constructor(TransparentAnimatedInGameEntity this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name);
void TransparentAnimatedInGameEntity_destructor(TransparentAnimatedInGameEntity this);
void TransparentAnimatedInGameEntity_update(TransparentAnimatedInGameEntity this, u32 elapsedTime);


#endif
