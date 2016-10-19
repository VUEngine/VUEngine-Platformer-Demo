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

#ifndef KEY_H_
#define KEY_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Item.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Key_METHODS(ClassName)																			\
	Item_METHODS(ClassName)																				\

#define Key_SET_VTABLE(ClassName)																		\
	Item_SET_VTABLE(ClassName)																			\
	__VIRTUAL_SET(ClassName, Key, ready);																\
	__VIRTUAL_SET(ClassName, Key, collect);																\

__CLASS(Key);

#define Key_ATTRIBUTES																					\
	/* it is derived from */																			\
	Item_ATTRIBUTES																						\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(Key, AnimatedInGameEntityDefinition* animatedEntityDefinition, int id, const char* const name);

void Key_constructor(Key this, AnimatedInGameEntityDefinition* definition, int id, const char* const name);
void Key_destructor(Key this);
void Key_ready(Key this, u32 recursive);
void Key_collect(Key this);


#endif
