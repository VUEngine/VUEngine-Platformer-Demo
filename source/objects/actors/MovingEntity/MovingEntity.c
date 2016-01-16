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

#include "MovingEntity.h"
#include "states/MovingEntityIdle.h"
#include "states/MovingEntityMoving.h"


//---------------------------------------------------------------------------------------------------------
// 											 CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(MovingEntity, Enemy);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(MovingEntity, MovingEntityDefinition* MovingEntityDefinition, int id, const char* const name)
__CLASS_NEW_END(MovingEntity, MovingEntityDefinition, id, name);

// class's constructor
void MovingEntity_constructor(MovingEntity this, MovingEntityDefinition* movingEntityDefinition, int id, const char* const name)
{
	ASSERT(this, "MovingEntity::constructor: null this");

	// construct base
	__CONSTRUCT_BASE((ActorDefinition*)&movingEntityDefinition->actorDefinition, id, name);

	// register a shape for collision detection
	MovingEntity_registerShape(this);

	// register a body for physics
	this->body = PhysicalWorld_registerBody(PhysicalWorld_getInstance(), __SAFE_CAST(SpatialObject, this), movingEntityDefinition->actorDefinition.mass);
	Body_setElasticity(this->body, movingEntityDefinition->actorDefinition.elasticity);
	Body_stopMovement(this->body, (__XAXIS | __YAXIS | __ZAXIS));
	
	// save over which axis I'm going to move
	this->axis = movingEntityDefinition->axis;
	
	// set movement direction;
	this->movementDirection = movingEntityDefinition->direction;

	// set movement radius;
	this->radius = movingEntityDefinition->radius;
	
	switch(this->axis)
    {
		case __XAXIS:

			this->direction.x = movingEntityDefinition->direction;
			break;
			
		case __YAXIS:

			this->direction.y = movingEntityDefinition->direction;
			break;			
	}
}

// class's constructor
void MovingEntity_destructor(MovingEntity this)
{
	ASSERT(this, "MovingEntity::destructor: null this");

	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// ready method
void MovingEntity_ready(MovingEntity this)
{
	ASSERT(this, "MovingEntity::ready: null this");

	Entity_ready(__SAFE_CAST(Entity, this));
	
	StateMachine_swapState(this->stateMachine, __SAFE_CAST(State, MovingEntityMoving_getInstance()));
}

// register a shape with the collision detection system
void MovingEntity_registerShape(MovingEntity this)
{
	ASSERT(this, "MovingEntity::registerShape: null this");

	// register a shape for collision detection
	this->shape = CollisionManager_registerShape(CollisionManager_getInstance(), __SAFE_CAST(SpatialObject, this), kCuboid);
	
	// don't check collisions agains other objects
	Shape_setCheckForCollisions(this->shape, false);
}

// unregister the shape with the collision detection system
void MovingEntity_unregisterShape(MovingEntity this)
{
	ASSERT(this, "MovingEntity::unregisterShape: null this");

	Shape_setActive(this->shape, false);
}

// tell me I've been hit
void MovingEntity_takeHit(MovingEntity this, int axis, s8 direction)
{
}

// die
void MovingEntity_die(MovingEntity this)
{
	// must unregister the shape for collision detections
	Shape_setActive(this->shape, false);

	// now change state to dead
	StateMachine_swapState(this->stateMachine, __SAFE_CAST(State, EnemyDead_getInstance()));
}

// set position
void MovingEntity_setLocalPosition(MovingEntity this, const VBVec3D* position)
{
	// set my position
	Actor_setLocalPosition(__SAFE_CAST(Actor, this), position);
	
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
int MovingEntity_getAxisFreeForMovement(MovingEntity this)
{
	return 0;// ((__XAXIS & ~(__XAXIS & movingState) )|(__ZAXIS & ~(__ZAXIS & movingState)));
}

// update movement
void MovingEntity_move(MovingEntity this)
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
							Actor_stopMovement(__SAFE_CAST(Actor, this));

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
							Actor_stopMovement(__SAFE_CAST(Actor, this));

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
							Actor_stopMovement(__SAFE_CAST(Actor, this));

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
							Actor_stopMovement(__SAFE_CAST(Actor, this));
							
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
void MovingEntity_startMovement(MovingEntity this)
{
	switch(this->axis)
    {
		case __XAXIS:

			{
				Velocity velocity =
                {
					((int)ITOFIX19_13(20) * this->direction.x),
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
