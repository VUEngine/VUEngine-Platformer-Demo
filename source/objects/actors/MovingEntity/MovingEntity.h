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

#ifndef MOVING_ENTITY_H_
#define MOVING_ENTITY_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Actor.h>
#include <macros.h>
#include <Enemy.h>


//---------------------------------------------------------------------------------------------------------
// 												MACROS
//---------------------------------------------------------------------------------------------------------

#define MOVING_ENTITY_WAIT_DELAY 1000


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define MovingEntity_METHODS																			\
	Enemy_METHODS;

#define MovingEntity_SET_VTABLE(ClassName)																\
	Enemy_SET_VTABLE(ClassName);																		\
	__VIRTUAL_SET(ClassName, MovingEntity, die);														\
	__VIRTUAL_SET(ClassName, MovingEntity, takeHit);													\
	__VIRTUAL_SET(ClassName, MovingEntity, setLocalPosition);											\
	__VIRTUAL_SET(ClassName, MovingEntity, getAxisFreeForMovement);										\
	__VIRTUAL_SET(ClassName, MovingEntity, ready);														\
	
__CLASS(MovingEntity);

#define MovingEntity_ATTRIBUTES																			\
																										\
	/* it is derivated from */																			\
	Enemy_ATTRIBUTES																					\
																										\
	/* save my initial position */																		\
	int initialPosition;																				\
																										\
	/* movement radius */																				\
    int radius;																							\
																										\
	/* movement axis */																					\
	u8 axis: 4;																							\
																										\
	/* movement direction */																			\
	s8 movementDirection: 2;																			\

// definition in ROM memory
typedef struct MovingEntityDefinition
{
	// It has a Character in the beginning
	ActorDefinition actorDefinition;

	// movement radius
	int radius;
	
	// on which axis it moves
	u8 axis;
	
	// movement direction
	s8 direction;
	
} MovingEntityDefinition;

typedef const MovingEntityDefinition MovingEntityROMDef;


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

// allocator
__CLASS_NEW_DECLARE(MovingEntity, MovingEntityDefinition* MovingEntityDefinition, int id, const char* const name);

void MovingEntity_constructor(MovingEntity this, MovingEntityDefinition* MovingEntityDefinition, int id, const char* const name);
void MovingEntity_destructor(MovingEntity this);
void MovingEntity_ready(MovingEntity this);
void MovingEntity_registerShape(MovingEntity this);
void MovingEntity_unregisterShape(MovingEntity this);
void MovingEntity_takeHit(MovingEntity this, int axis, s8 direction);
void MovingEntity_die(MovingEntity this);
void MovingEntity_setLocalPosition(MovingEntity this, const VBVec3D* position);
int MovingEntity_getAxisFreeForMovement(MovingEntity this);
void MovingEntity_move(MovingEntity this);
void MovingEntity_startMovement(MovingEntity this);


#endif