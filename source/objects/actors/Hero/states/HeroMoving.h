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

#ifndef HERO_MOVING_H_
#define HERO_MOVING_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <HeroState.h>
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define HeroMoving_METHODS(ClassName)																	\
    	HeroState_METHODS(ClassName)																	\

// declare the virtual methods which are redefined
#define HeroMoving_SET_VTABLE(ClassName)																\
        HeroState_SET_VTABLE(ClassName)																	\
        __VIRTUAL_SET(ClassName, HeroMoving, enter);													\
        __VIRTUAL_SET(ClassName, HeroMoving, processMessage);                           				\
        __VIRTUAL_SET(ClassName, HeroMoving, onKeyPressed);	                                            \
        __VIRTUAL_SET(ClassName, HeroMoving, onKeyReleased);	                                            \
        __VIRTUAL_SET(ClassName, HeroMoving, onKeyHold);	                                                \

#define HeroMoving_ATTRIBUTES																			\
        /* inherits */																					\
        HeroState_ATTRIBUTES																			\
        /* flag to allow jump on bouncing */															\
        bool bouncing;																					\

 __CLASS(HeroMoving);


enum HeroMovingMessages
{
	 kDisallowJumpOnBouncing = kLastPlatformerMessage + 1,
};


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

HeroMoving HeroMoving_getInstance();

void HeroMoving_onKeyPressed(HeroMoving this, void* owner);
void HeroMoving_onKeyReleased(HeroMoving this, void* owner);
void HeroMoving_onKeyHold(HeroMoving this, void* owner);

#endif
