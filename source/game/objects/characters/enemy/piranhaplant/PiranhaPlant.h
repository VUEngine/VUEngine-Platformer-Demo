/* VbJaEngine: bitmap graphics engine for the Nintendo Virtual Boy 
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
#ifndef PIRANHA_PLANT_H_
#define PIRANHA_PLANT_H_

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												INCLUDES
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

#include <Actor.h>

#include <macros.h>
#include "../enemy/Enemy.h"

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 											CLASS'S DECLARATION
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

#define PIRANHA_PLANT_ATTACK_DISTANCE		6400

#define PIRANHA_PLANT_VELOCITY_Y		ITOFIX19_13(20)
#define PIRANHA_PLANT_ACCELERATION_Y	ITOFIX19_13(0)

#define PIRANHA_PLANT_WAIT_DELAY		1500

#define PiranhaPlant_METHODS							\
	Enemy_METHODS;
	
	

#define PiranhaPlant_SET_VTABLE(ClassName)								\
	Enemy_SET_VTABLE(ClassName);										\
	__VIRTUAL_SET(ClassName, PiranhaPlant, die);						\
	__VIRTUAL_SET(ClassName, PiranhaPlant, takeHit);					\
	__VIRTUAL_SET(ClassName, PiranhaPlant, setLocalPosition);			\
	__VIRTUAL_SET(ClassName, PiranhaPlant, getAxisFreeForMovement);
	
	

// A Decoration which represents a generic object inside a Stage
__CLASS(PiranhaPlant);

#define PiranhaPlant_ATTRIBUTES						\
													\
	/* it is derivated from */						\
	Enemy_ATTRIBUTES								\
													\
	/* save my initial position */					\
	int initialPosition;							\
													\
	/* movement axis */								\
	u8 axis: 4;										\
													\
	/* movement direction */						\
	s8 movementDirection: 2;



// definition in ROM memory
typedef const struct PiranhaPlantDefinition{

	// It has a Characterat the beggining
	ActorDefinition actorDefinition;
	
	// on which axis it moves
	u8 axis;
	
	// movement direction
	s8 direction;
	
}PiranhaPlantDefinition;

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 										PUBLIC INTERFACE
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

// allocator
__CLASS_NEW_DECLARE(PiranhaPlant , __PARAMETERS(PiranhaPlantDefinition* piranhaPlantDefinition, int ID));

//class's conctructor
void PiranhaPlant_constructor(PiranhaPlant this, PiranhaPlantDefinition* piranhaPlantDefinition, int ID);

// class's conctructor
void PiranhaPlant_destructor(PiranhaPlant this);

// register a shape with the collision detection system
void PiranhaPlant_registerShape(PiranhaPlant this);

// unregister the shape with the collision detection system
void PiranhaPlant_unregisterShape(PiranhaPlant this);

// process a collision
u8 PiranhaPlant_processCollision(PiranhaPlant this, Telegram telegram);

// tell me I've been hit
void PiranhaPlant_takeHit(PiranhaPlant this, int axis, s8 direction);

// die 
void PiranhaPlant_die(PiranhaPlant this);

// set  position
void PiranhaPlant_setLocalPosition(PiranhaPlant this, VBVec3D position);

// retrieve axis free for movement
int PiranhaPlant_getAxisFreeForMovement(PiranhaPlant this);

// update movement
void PiranhaPlant_move(PiranhaPlant this);

// start moving
void PiranhaPlant_startMovement(PiranhaPlant this);


#endif /* PIRANHAPLANT_H_*/