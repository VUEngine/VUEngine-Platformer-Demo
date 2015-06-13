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

#include <EnemyDead.h>
#include <Hero.h>

#include "SawBlade.h"
#include "states/SawBladeIdle.h"
#include "states/SawBladeMoving.h"


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
__CLASS_NEW_DEFINITION(SawBlade, SawBladeDefinition* sawBladeDefinition, int id, const char* const name)
__CLASS_NEW_END(SawBlade, sawBladeDefinition, id, name);

// class's constructor
void SawBlade_constructor(SawBlade this, SawBladeDefinition* sawBladeDefinition, int id, const char* const name)
{
	ASSERT(this, "SawBlade::constructor: null this");

	// construct base
	__CONSTRUCT_BASE((ActorDefinition*)&sawBladeDefinition->actorDefinition, id, name);

	// register a shape for collision detection
	SawBlade_registerShape(this);

	// register a body for physics
	this->body = PhysicalWorld_registerBody(PhysicalWorld_getInstance(), __GET_CAST(SpatialObject, this), sawBladeDefinition->actorDefinition.mass);

	Body_stopMovement(this->body, (__XAXIS | __YAXIS | __ZAXIS));
	
	// save over which axis I'm going to move
	this->axis = sawBladeDefinition->axis;
	
	// set movement direction;
	this->movementDirection = sawBladeDefinition->direction;

	// set movement radius;
	this->radius = sawBladeDefinition->radius;
	
	switch(this->axis)
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

	Entity_ready(__GET_CAST(Entity, this));
	
	StateMachine_swapState(this->stateMachine, __GET_CAST(State, SawBladeMoving_getInstance()));
}

// register a shape with the collision detection system
void SawBlade_registerShape(SawBlade this)
{
	ASSERT(this, "SawBlade::registerShape: null this");

	// register a shape for collision detection
	this->shape = CollisionManager_registerShape(CollisionManager_getInstance(), __GET_CAST(SpatialObject, this), kCuboid);
	
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
	InGameEntity inGameEntity = __GET_CAST(InGameEntity,  Telegram_getExtraInfo(telegram));

	switch(message)
    {
		case kCollision:

			switch(InGameEntity_getInGameType(inGameEntity))
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
	StateMachine_swapState(this->stateMachine, __GET_CAST(State, EnemyDead_getInstance()));
}

// set  position
void SawBlade_setLocalPosition(SawBlade this, const VBVec3D* position)
{
	// set my position
	Actor_setLocalPosition(__GET_CAST(Actor, this), position);
	
	// save initial position
	switch(this->axis)
    {
		case __XAXIS:

			this->initialPosition = position->x;
			break;
			
		case __YAXIS:
			
			this->initialPosition = position->y;
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
	int displacement = this->radius;

	// update position
	switch(this->axis)
    {
		case __XAXIS:

			switch(this->direction.x)
            {
				case __LEFT:

					{
						// check position
						if(this->transform.globalPosition.x < this->initialPosition - displacement)
                        {
							// stop moving
							Actor_stopMovement(__GET_CAST(Actor, this));

							// change direction
							this->direction.x = __RIGHT;

							// start action time
							this->actionTime = Clock_getTime(Game_getInGameClock(Game_getInstance()));

							// set position
							this->transform.localPosition.x = this->initialPosition - displacement;
						}
					}
					break;

				case __RIGHT:

					{
						// check position
						if(this->transform.globalPosition.x > this->initialPosition + displacement)
                        {
							// stop moving
							Actor_stopMovement(__GET_CAST(Actor, this));

							// change direction
							this->direction.x = __LEFT;

							// start action time
							this->actionTime = Clock_getTime(Game_getInGameClock(Game_getInstance()));

							// set position
							this->transform.localPosition.x = this->initialPosition;
						}
					}
					break;

			}
			break;
			
		case __YAXIS:
			
			switch(this->direction.y)
            {
				case __UP:

					{	
						// check position
						if(this->transform.globalPosition.y < this->initialPosition - displacement)
                        {
							// stop moving
							Actor_stopMovement(__GET_CAST(Actor, this));

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
						if(this->transform.globalPosition.y > this->initialPosition + displacement)
                        {
							// stop moving
							Actor_stopMovement(__GET_CAST(Actor, this));
							
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
}

// start moving
void SawBlade_startMovement(SawBlade this)
{
	switch(this->axis)
    {
		case __XAXIS:

			{
				Velocity velocity =
                {
					((int)ITOFIX19_13(10) * this->direction.x),
					0,
					0,
				};

				Body_moveUniformly(this->body, velocity);
			}
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
