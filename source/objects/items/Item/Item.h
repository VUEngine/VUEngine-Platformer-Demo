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

#ifndef ITEM_H_
#define ITEM_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AnimatedInGameEntity.h>
#include <Collectable.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Item_METHODS(ClassName)																			\
	    Collectable_METHODS(ClassName)														    		\

#define Item_SET_VTABLE(ClassName)																		\
        Collectable_SET_VTABLE(ClassName)																\
        __VIRTUAL_SET(ClassName, Item, collect);														\

__CLASS(Item);

#define Item_ATTRIBUTES																					\
        /* it is derived from */																		\
        Collectable_ATTRIBUTES																			\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(Item, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name);

void Item_constructor(Item this, AnimatedInGameEntityDefinition* definition, s16 id, s16 internalId, const char* const name);
void Item_destructor(Item this);
void Item_collect(Item this);


#endif
