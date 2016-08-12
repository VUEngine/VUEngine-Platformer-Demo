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

#ifndef CANNON_BALL_H_
#define CANNON_BALL_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Actor.h>
#include <macros.h>
#include <Actor.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define CANNON_BALL_MINIMUM_Z_VALUE -64


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define CannonBall_METHODS(ClassName)																	\
    	Actor_METHODS(ClassName)																		\

#define CannonBall_SET_VTABLE(ClassName)																\
        Actor_SET_VTABLE(ClassName)																	    \
        __VIRTUAL_SET(ClassName, CannonBall, getAxisFreeForMovement);									\
        __VIRTUAL_SET(ClassName, CannonBall, ready);													\

__CLASS(CannonBall);

#define CannonBall_ATTRIBUTES																			\
																										\
	/* it is derived from */																			\
	Actor_ATTRIBUTES																					\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

// allocator
__CLASS_NEW_DECLARE(CannonBall, ActorDefinition* definition, int id, const char* const name);

void CannonBall_constructor(CannonBall this, ActorDefinition* definition, int id, const char* const name);
void CannonBall_destructor(CannonBall this);
void CannonBall_ready(CannonBall this);
void CannonBall_registerShape(CannonBall this);
void CannonBall_unregisterShape(CannonBall this);
int CannonBall_getAxisFreeForMovement(CannonBall this);
void CannonBall_startMovement(CannonBall this);
void CannonBall_stopMovement(CannonBall this);
void CannonBall_checkPosition(CannonBall this);


#endif
