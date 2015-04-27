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

//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Game.h>
#include <CollisionManager.h>
#include <Optics.h>
#include <PhysicalWorld.h>
#include <Prototypes.h>

#include "SawBlade.h"
#include "states/SawBladeIdle.h"
#include "states/SawBladeMoving.h"
#include "../states/EnemyDead.h"
#include "../../Hero/Hero.h"


//---------------------------------------------------------------------------------------------------------
// 											 CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(SawBlade, Enemy);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(SawBlade, SawBladeDefinition* sawBladeDefinition, int ID)
__CLASS_NEW_END(SawBlade, sawBladeDefinition, ID);

// class's constructor
void SawBlade_constructor(SawBlade this, SawBladeDefinition* sawBladeDefinition, int ID)
{
	ASSERT(this, "SawBlade::constructor: null this");

	// construct base
	__CONSTRUCT_BASE((ActorDefinition*)&sawBladeDefinition->actorDefinition, ID);

	// register a shape for collision detection
	SawBlade_registerShape(this);

	// register a body for physics
	this->body = PhysicalWorld_registerBody(PhysicalWorld_getInstance(), __UPCAST(SpatialObject, this), 0);

	Body_stopMovement(this->body, (__XAXIS | __YAXIS | __ZAXIS));
	
	// save over which axis I'm going to move
	this->axis = sawBladeDefinition->axis;
	
	// set movement direction;
	this->movementDirection = sawBladeDefinition->direction;
	
	switch (this->axis)
    {
		case __XAXIS:

			this->direction.x = sawBladeDefinition->direction;			
			break;
			
		case __YAXIS:

			this->direction.y = sawBladeDefinition->direction;
			break;			
	}
}

// class's constructor
void SawBlade_destructor(SawBlade this)
{
	ASSERT(this, "SawBlade::destructor: null this");

	// delete the super object
	__DESTROY_BASE;
}

// ready method
void SawBlade_ready(SawBlade this)
{
	ASSERT(this, "SawBlade::ready: null this");

	Entity_ready(__UPCAST(Entity, this));
	
	StateMachine_swapState(this->stateMachine, __UPCAST(State, SawBladeMoving_getInstance()));
}

// register a shape with the collision detection system
void SawBlade_registerShape(SawBlade this)
{
	ASSERT(this, "SawBlade::registerShape: null this");

	// register a shape for collision detection
	this->shape = CollisionManager_registerShape(CollisionManager_getInstance(), __UPCAST(SpatialObject, this), kCuboid);
	
	// don't check collisions agains other objects
	Shape_setCheckForCollisions(this->shape, false);
}

// unregister the shape with the collision detection system
void SawBlade_unregisterShape(SawBlade this)
{
	ASSERT(this, "SawBlade::unregisterShape: null this");

	Shape_setActive(this->shape, false);
}

// process a collision
bool SawBlade_processCollision(SawBlade this, Telegram telegram)
{
	ASSERT(this, "SawBlade::processCollision: null this");

	int message = Telegram_getMessage(telegram);
	InGameEntity inGameEntity = __UPCAST(InGameEntity,  Telegram_getExtraInfo(telegram));
	
	switch (message)
    {
		case kCollision:
			
			switch (InGameEntity_getInGameType(inGameEntity))
            {
				case kHero:

					// tell hero to take a hit
					//Hero_takeHit((Hero)inGameEntity, this->transform.globalPosition);
					break;
			}
	}

	return false;
}

// tell me I've been hit
void SawBlade_takeHit(SawBlade this, int axis, s8 direction)
{
}

// die
void SawBlade_die(SawBlade this)
{
	// must unregister the shape for collision detections
	Shape_setActive(this->shape, false);

	// now change state to dead
	StateMachine_swapState(this->stateMachine, __UPCAST(State, EnemyDead_getInstance()));
}

// set  position
void SawBlade_setLocalPosition(SawBlade this, VBVec3D position)
{
	// set my position
	Actor_setLocalPosition(__UPCAST(Actor, this), position);
	
	// save initial position
	switch (this->axis)
    {
		case __XAXIS:

			this->initialPosition = position.x;
			break;
			
		case __YAXIS:
			
			this->initialPosition = position.y;
			break;			
	}
}

// retrieve axis free for movement
int SawBlade_getAxisFreeForMovement(SawBlade this)
{
	return 0;// ((__XAXIS & ~(__XAXIS & movingState) )|(__ZAXIS & ~(__ZAXIS & movingState)));
}

// update movement
void SawBlade_move(SawBlade this)
{
	int displacement = ITOFIX19_13(44);
	
	// update position
	switch (this->axis)
    {
		case __XAXIS:

			break;
			
		case __YAXIS:
			
			switch (this->direction.y)
            {
				case __UP:

					{	
						// check position
						if (this->transform.globalPosition.y < this->initialPosition - displacement)
                        {
							// stop moving
							Actor_stopMovement(__UPCAST(Actor, this));
							
							// change direction
							this->direction.y = __DOWN;
							
							// start action time
							this->actionTime = Clock_getTime(Game_getInGameClock(Game_getInstance()));
							
							// set position
							this->transform.localPosition.y = this->initialPosition - displacement;
						}
					}
					break;
					
				case __DOWN:

					{
						// check position
						if (this->transform.globalPosition.y > this->initialPosition)
                        {
							// stop moving
							Actor_stopMovement(__UPCAST(Actor, this));
							
							// change direction
							this->direction.y = __UP;
							
							// start action time
							this->actionTime = Clock_getTime(Game_getInGameClock(Game_getInstance()));
							
							// set position
							this->transform.localPosition.y = this->initialPosition;
						}
					}
					break;
					
			}
			break;			
	}
/*
	// if I've been stopped
	if (false && !(this->axis & Actor_isMoving(__UPCAST(Actor, this))))
    {
		// check if must stop go idle
		if (!displacement)
        {
			// check if hero distance to the plant is out of range
			if (SAW_BLADE_ATTACK_DISTANCE < Optics_lengthSquared3D(
					Entity_getPosition(__UPCAST(Entity, this)), Entity_getPosition(__UPCAST(Entity, Hero_getInstance())))
			)
            {
				StateMachine_swapState(this->stateMachine, __UPCAST(State, SawBladeIdle_getInstance()));
			}
		}
	}
	*/
}

// start moving
void SawBlade_startMovement(SawBlade this)
{
	switch (this->axis)
    {
		case __XAXIS:

			break;
			
		case __YAXIS:
			
			{
				Velocity velocity =
                {
					0,
					((int)ITOFIX19_13(10) * this->direction.y),
					0,
				};
				
				Body_moveUniformly(this->body, velocity);
			}
			break;			
	}
	
	this->actionTime = 0;
}
