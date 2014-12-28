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

#ifndef HERO_MOVING_H_
#define HERO_MOVING_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <StateMachine.h>
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define HeroMoving_METHODS														\
	State_METHODS;									

// declare the virtual methods which are redefined
#define HeroMoving_SET_VTABLE(ClassName)										\
	State_SET_VTABLE(ClassName)													\
	__VIRTUAL_SET(ClassName, HeroMoving, enter);								\
	__VIRTUAL_SET(ClassName, HeroMoving, execute);								\
	__VIRTUAL_SET(ClassName, HeroMoving, exit);									\
	__VIRTUAL_SET(ClassName, HeroMoving, handleMessage);						\

#define HeroMoving_ATTRIBUTES													\
																				\
	/* inherits */																\
	State_ATTRIBUTES															\
																				\
	/* check direction flag */													\
	bool mustCheckDirection;														\
																				\
	/* flag to allow jump on bouncing */										\
	bool bouncing;																\

 __CLASS(HeroMoving);


enum HeroMovingMessages
{
	 kDisallowJumpOnBouncing = kLastPlatformerMessage + 1,
};


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

// setup the init focus screen
HeroMoving HeroMoving_getInstance();


#endif