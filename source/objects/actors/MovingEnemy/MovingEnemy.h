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

#ifndef MOVING_ENEMY_H_
#define MOVING_ENEMY_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <macros.h>
#include <Enemy.h>


//---------------------------------------------------------------------------------------------------------
// 												MACROS
//---------------------------------------------------------------------------------------------------------

#define MOVING_ENTITY_WAIT_DELAY 1000


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define MovingEnemy_METHODS																				\
	Enemy_METHODS;

#define MovingEnemy_SET_VTABLE(ClassName)																\
	Enemy_SET_VTABLE(ClassName);																		\
	__VIRTUAL_SET(ClassName, MovingEnemy, takeHit);														\
	__VIRTUAL_SET(ClassName, MovingEnemy, setLocalPosition);											\
	__VIRTUAL_SET(ClassName, MovingEnemy, getAxisFreeForMovement);										\
	__VIRTUAL_SET(ClassName, MovingEnemy, ready);														\
	
__CLASS(MovingEnemy);

#define MovingEnemy_ATTRIBUTES																			\
																										\
	/* it is derived from */																			\
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
typedef struct MovingEnemyDefinition
{
	// It has a Character in the beginning
	ActorDefinition actorDefinition;

	// movement radius
	int radius;
	
	// on which axis it moves
	u8 axis;
	
	// movement direction
	s8 direction;
	
} MovingEnemyDefinition;

typedef const MovingEnemyDefinition MovingEnemyROMDef;


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

// allocator
__CLASS_NEW_DECLARE(MovingEnemy, MovingEnemyDefinition* MovingEnemyDefinition, int id, const char* const name);

void MovingEnemy_constructor(MovingEnemy this, MovingEnemyDefinition* MovingEnemyDefinition, int id, const char* const name);
void MovingEnemy_destructor(MovingEnemy this);
void MovingEnemy_ready(MovingEnemy this);
void MovingEnemy_registerShape(MovingEnemy this);
void MovingEnemy_unregisterShape(MovingEnemy this);
void MovingEnemy_takeHit(MovingEnemy this, int axis, s8 direction);
void MovingEnemy_setLocalPosition(MovingEnemy this, const VBVec3D* position);
int MovingEnemy_getAxisFreeForMovement(MovingEnemy this);
void MovingEnemy_move(MovingEnemy this);
void MovingEnemy_startMovement(MovingEnemy this);


#endif