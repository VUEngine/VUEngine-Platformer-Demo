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

#ifndef SAW_BLADE_H_
#define SAW_BLADE_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Actor.h>

#include <macros.h>
#include "../Enemy.h"


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define SAW_BLADE_ATTACK_DISTANCE	6400

#define SAW_BLADEELOCITY_Y			ITOFIX19_13(20)
#define SAW_BLADE_ACCELERATION_Y	ITOFIX19_13(0)

#define SAW_BLADE_WAIT_DELAY		1500

#define SawBlade_METHODS															\
	Enemy_METHODS;

#define SawBlade_SET_VTABLE(ClassName)												\
	Enemy_SET_VTABLE(ClassName);													\
	__VIRTUAL_SET(ClassName, SawBlade, die);										\
	__VIRTUAL_SET(ClassName, SawBlade, takeHit);									\
	__VIRTUAL_SET(ClassName, SawBlade, setLocalPosition);							\
	__VIRTUAL_SET(ClassName, SawBlade, getAxisFreeForMovement);						\
	__VIRTUAL_SET(ClassName, SawBlade, initialize);									\
	
__CLASS(SawBlade);

#define SawBlade_ATTRIBUTES															\
																					\
	/* it is derivated from */														\
	Enemy_ATTRIBUTES																\
																					\
	/* save my initial position */													\
	int initialPosition;															\
																					\
	/* movement axis */																\
	u8 axis: 4;																		\
																					\
	/* movement direction */														\
	s8 movementDirection: 2;														\

// definition in ROM memory
typedef const struct SawBladeDefinition
{
	// It has a Character in the beginning
	ActorDefinition actorDefinition;
	
	// on which axis it moves
	u8 axis;
	
	// movement direction
	s8 direction;
	
}SawBladeDefinition;


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

// allocator
__CLASS_NEW_DECLARE(SawBlade , SawBladeDefinition* sawBladeDefinition, int ID);

//class's constructor
void SawBlade_constructor(SawBlade this, SawBladeDefinition* sawBladeDefinition, int ID);

// class's constructor
void SawBlade_destructor(SawBlade this);

// initialize method
void SawBlade_initialize(SawBlade this, const PositionedEntity* positionedEntity);

// register a shape with the collision detection system
void SawBlade_registerShape(SawBlade this);

// unregister the shape with the collision detection system
void SawBlade_unregisterShape(SawBlade this);

// process a collision
bool SawBlade_processCollision(SawBlade this, Telegram telegram);

// tell me I've been hit
void SawBlade_takeHit(SawBlade this, int axis, s8 direction);

// die
void SawBlade_die(SawBlade this);

// set  position
void SawBlade_setLocalPosition(SawBlade this, VBVec3D position);

// retrieve axis free for movement
int SawBlade_getAxisFreeForMovement(SawBlade this);

// update movement
void SawBlade_move(SawBlade this);

// start moving
void SawBlade_startMovement(SawBlade this);

#endif