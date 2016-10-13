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

#ifndef HERO_IDLE_H_
#define HERO_IDLE_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <HeroState.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define HeroIdle_METHODS(ClassName)																		\
	    HeroState_METHODS(ClassName)																    \

// declare the virtual methods which are redefined
#define HeroIdle_SET_VTABLE(ClassName)																	\
        HeroState_SET_VTABLE(ClassName)																	\
        __VIRTUAL_SET(ClassName, HeroIdle, enter);														\
        __VIRTUAL_SET(ClassName, HeroIdle, exit);														\
        __VIRTUAL_SET(ClassName, HeroIdle, processMessage);	                                            \
        __VIRTUAL_SET(ClassName, HeroIdle, onKeyPressed);	                                            \
        __VIRTUAL_SET(ClassName, HeroIdle, onKeyReleased);	                                            \
        __VIRTUAL_SET(ClassName, HeroIdle, onKeyHold);	                                                \

__CLASS(HeroIdle);

#define HeroIdle_ATTRIBUTES																				\
        /* inherits */																					\
        HeroState_ATTRIBUTES																			\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

HeroIdle HeroIdle_getInstance();

void HeroIdle_onKeyPressed(HeroIdle this, void* owner);
void HeroIdle_onKeyReleased(HeroIdle this, void* owner);
void HeroIdle_onKeyHold(HeroIdle this, void* owner);


#endif
