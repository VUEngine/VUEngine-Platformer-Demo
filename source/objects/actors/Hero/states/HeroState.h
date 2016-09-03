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

#ifndef HERO_STATE_H_
#define HERO_STATE_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <State.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define HeroState_METHODS(ClassName)																		\
	    State_METHODS(ClassName)																		\
		__VIRTUAL_DEC(ClassName, void, onKeyPressed, void* owner);										\
		__VIRTUAL_DEC(ClassName, void, onKeyReleased, void* owner);										\
		__VIRTUAL_DEC(ClassName, void, onKeyHold, void* owner);										    \

// declare the virtual methods which are redefined
#define HeroState_SET_VTABLE(ClassName)																	\
        State_SET_VTABLE(ClassName)																		\

__CLASS(HeroState);

#define HeroState_ATTRIBUTES																				\
        /* inherits */																					\
        State_ATTRIBUTES																				\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

void HeroState_constructor(HeroState this);
void HeroState_destructor(HeroState this);


#endif
