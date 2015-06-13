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

#ifndef CANNON_BALL_H_
#define CANNON_BALL_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <InanimatedInGameEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define CANNON_BALL_MOVE_DELAY 100
#define CANNON_BALL_Z_OFFSET_PER_CYCLE 5
#define CANNON_BALL_MINIMUM_Z_POSITION -80


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define CannonBall_METHODS														\
	InanimatedInGameEntity_METHODS;
	

#define CannonBall_SET_VTABLE(ClassName)										\
	InanimatedInGameEntity_SET_VTABLE(ClassName);								\
	__VIRTUAL_SET(ClassName, CannonBall, handleMessage);						\

__CLASS(CannonBall);

#define CannonBall_ATTRIBUTES													\
																				\
	/* it is derivated from */													\
	InanimatedInGameEntity_ATTRIBUTES											\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

__CLASS_NEW_DECLARE(CannonBall, InanimatedInGameEntityDefinition* inanimatedEntityDefinition, int id, const char* const name);

void CannonBall_constructor(CannonBall this, InanimatedInGameEntityDefinition* inanimatedEntityDefinition, int id, const char* const name);
void CannonBall_destructor(CannonBall this);
bool CannonBall_handleMessage(CannonBall this, Telegram telegram);


#endif