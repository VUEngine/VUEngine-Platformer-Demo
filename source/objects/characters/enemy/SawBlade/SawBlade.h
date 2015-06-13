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
#include <Enemy.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define SawBlade_METHODS															\
	Enemy_METHODS;

#define SawBlade_SET_VTABLE(ClassName)												\
	Enemy_SET_VTABLE(ClassName);													\
	__VIRTUAL_SET(ClassName, SawBlade, die);										\
	__VIRTUAL_SET(ClassName, SawBlade, takeHit);									\
	__VIRTUAL_SET(ClassName, SawBlade, setLocalPosition);							\
	__VIRTUAL_SET(ClassName, SawBlade, getAxisFreeForMovement);						\
	__VIRTUAL_SET(ClassName, SawBlade, ready);										\
	
__CLASS(SawBlade);

#define SawBlade_ATTRIBUTES															\
																					\
	/* it is derivated from */														\
	Enemy_ATTRIBUTES																\
																					\
	/* save my initial position */													\
	int initialPosition;															\
																					\
	/* movement radius */															\
    int radius;																		\
																					\
	/* movement axis */																\
	u8 axis: 4;																		\
																					\
	/* movement direction */														\
	s8 movementDirection: 2;														\

// definition in ROM memory
typedef struct SawBladeDefinition
{
	// It has a Character in the beginning
	ActorDefinition actorDefinition;

	// movement radius
	int radius;
	
	// on which axis it moves
	u8 axis;
	
	// movement direction
	s8 direction;
	
} SawBladeDefinition;

typedef const SawBladeDefinition SawBladeROMDef;


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

// allocator
__CLASS_NEW_DECLARE(SawBlade, SawBladeDefinition* sawBladeDefinition, int id, const char* const name);

void SawBlade_constructor(SawBlade this, SawBladeDefinition* sawBladeDefinition, int id, const char* const name);
void SawBlade_destructor(SawBlade this);
void SawBlade_ready(SawBlade this);
void SawBlade_registerShape(SawBlade this);
void SawBlade_unregisterShape(SawBlade this);
bool SawBlade_processCollision(SawBlade this, Telegram telegram);
void SawBlade_takeHit(SawBlade this, int axis, s8 direction);
void SawBlade_die(SawBlade this);
void SawBlade_setLocalPosition(SawBlade this, const VBVec3D* position);
int SawBlade_getAxisFreeForMovement(SawBlade this);
void SawBlade_move(SawBlade this);
void SawBlade_startMovement(SawBlade this);


#endif