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

#ifndef LAVA_H_
#define LAVA_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <InanimatedInGameEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Lava_METHODS															\
	InanimatedInGameEntity_METHODS;
	

#define Lava_SET_VTABLE(ClassName)												\
	InanimatedInGameEntity_SET_VTABLE(ClassName);								\
	__VIRTUAL_SET(ClassName, Lava, initialize);									\
	__VIRTUAL_SET(ClassName, Lava, handleMessage);								\
    __VIRTUAL_SET(ClassName, Lava, isVisible);									\
    __VIRTUAL_SET(ClassName, Lava, resume);										\
	__VIRTUAL_SET(ClassName, Lava, moves);										\

__CLASS(Lava);

#define Lava_ATTRIBUTES															\
																				\
	/* it is derivated from */													\
	InanimatedInGameEntity_ATTRIBUTES											\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(Lava, InanimatedInGameEntityDefinition* animatedEntityDefinition, int ID);

void Lava_constructor(Lava this, InanimatedInGameEntityDefinition* definition, int ID);
void Lava_destructor(Lava this);
void Lava_initialize(Lava this);
bool Lava_handleMessage(Lava this, Telegram telegram);
bool Lava_isVisible(Lava this, int pad);
void Lava_resume(Lava this);
bool Lava_moves(Lava this);


#endif