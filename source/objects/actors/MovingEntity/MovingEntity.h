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


//---------------------------------------------------------------------------------------------------------
// 												MACROS
//---------------------------------------------------------------------------------------------------------

#define MOVING_ENTITY_WAIT_DELAY 1000


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define MovingEntity_METHODS																			\
	Actor_METHODS;

#define MovingEntity_SET_VTABLE(ClassName)																\
	Actor_SET_VTABLE(ClassName);																		\
	__VIRTUAL_SET(ClassName, MovingEntity, die);														\
	__VIRTUAL_SET(ClassName, MovingEntity, setLocalPosition);											\
	__VIRTUAL_SET(ClassName, MovingEntity, getAxisFreeForMovement);										\
	__VIRTUAL_SET(ClassName, MovingEntity, ready);														\
	
__CLASS(MovingEntity);

#define MovingEntity_ATTRIBUTES																			\
																										\
	/* it is derivated from */																			\
	Actor_ATTRIBUTES																					\
																										\
	/* save my initial position */																		\
	int initialPosition;																				\
																										\
	/* definition pointer */																			\
	MovingEntityDefinition* movingEntityDefinition;														\


// definition in ROM memory
typedef struct MovingEntityDefinition
{
	// It has a Character in the beginning
	ActorDefinition actorDefinition;

	// velocity
	fix19_13 velocity;
	
	// maximum deviation from initial position
	fix19_13 maximumDisplacement;
	
	// time to rest idle
	u16 idleDuration;
	
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
void MovingEntity_setLocalPosition(MovingEntity this, const VBVec3D* position);
int MovingEntity_getAxisFreeForMovement(MovingEntity this);
void MovingEntity_startMovement(MovingEntity this);
void MovingEntity_stopMovement(MovingEntity this);
void MovingEntity_die(MovingEntity this);
void MovingEntity_checkDisplacement(MovingEntity this);


#endif