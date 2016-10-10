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

#ifndef COIN_H_
#define COIN_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Collectable.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Coin_METHODS(ClassName)																			\
    	Collectable_METHODS(ClassName)																	\

#define Coin_SET_VTABLE(ClassName)																		\
        Collectable_SET_VTABLE(ClassName)																\
        __VIRTUAL_SET(ClassName, Coin, ready);															\
        __VIRTUAL_SET(ClassName, Coin, collect);														\

__CLASS(Coin);

#define Coin_ATTRIBUTES																					\
        /* it is derived from */																		\
        Collectable_ATTRIBUTES																			\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(Coin, AnimatedInGameEntityDefinition* animatedEntityDefinition, int id, const char* const name);

void Coin_constructor(Coin this, AnimatedInGameEntityDefinition* definition, int id, const char* const name);
void Coin_destructor(Coin this);
void Coin_ready(Coin this, u32 recursive);
void Coin_collect(Coin this);


#endif
