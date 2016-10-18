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
#include <MessageDispatcher.h>
#include <CollisionManager.h>
#include <Optics.h>
#include <PhysicalWorld.h>
#include <MessageDispatcher.h>
#include <Prototypes.h>
#include <PlatformerLevelState.h>
#include <debugUtilities.h>


#include "MovingEntity.h"


//---------------------------------------------------------------------------------------------------------
// 											 CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(MovingEntity, Actor);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void MovingEntity_registerShape(MovingEntity this);


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
	__CONSTRUCT_BASE(Actor, (ActorDefinition*)&movingEntityDefinition->actorDefinition, id, name);

	this->movingEntityDefinition = movingEntityDefinition;

	this->initialPosition = 0;

	// register a shape for collision detection
	MovingEntity_registerShape(this);

	switch(this->movingEntityDefinition->axis)
    {
		case __XAXIS:

			this->direction.x = this->movingEntityDefinition->direction;
			break;

		case __YAXIS:

			this->direction.y = this->movingEntityDefinition->direction;
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

// set definition
void MovingEntity_setDefinition(MovingEntity this, MovingEntityDefinition* movingEntityDefinition)
{
	ASSERT(this, "MovingEntity::setDefinition: null this");
	ASSERT(movingEntityDefinition, "MovingEntity::setDefinition: null definition");

	// save definition
	this->movingEntityDefinition = movingEntityDefinition;

	Actor_setDefinition(__SAFE_CAST(Actor, this), &movingEntityDefinition->actorDefinition);
}

// register a shape with the collision detection system
static void MovingEntity_registerShape(MovingEntity this)
{
	ASSERT(this, "MovingEntity::registerShape: null this");

	// register a shape for collision detection
	this->shape = CollisionManager_registerShape(Game_getCollisionManager(Game_getInstance()), __SAFE_CAST(SpatialObject, this), kCuboid);
}

// ready method
void MovingEntity_ready(MovingEntity this, u32 recursive)
{
	ASSERT(this, "MovingEntity::ready: null this");

	// register a body for physics
	this->body = PhysicalWorld_registerBody(Game_getPhysicalWorld(Game_getInstance()), (BodyAllocator)__TYPE(Body), __SAFE_CAST(SpatialObject, this), this->movingEntityDefinition->actorDefinition.mass);
	Body_setElasticity(this->body, this->movingEntityDefinition->actorDefinition.elasticity);
	Body_stopMovement(this->body, (__XAXIS | __YAXIS | __ZAXIS));

	// call base
	AnimatedInGameEntity_ready(__SAFE_CAST(AnimatedInGameEntity, this), recursive);

	MovingEntity_startMovement(this);
}

// update method
void MovingEntity_update(MovingEntity this, u32 elapsedTime)
{
	ASSERT(this, "MovingEntity::update: null this");

	Actor_update(__SAFE_CAST(Actor, this), elapsedTime);

    if(Body_isAwake(this->body))
    {
    	MovingEntity_checkDisplacement(this);
    }
}

bool MovingEntity_handleMessage(MovingEntity this, Telegram telegram)
{
	ASSERT(this, "MovingEntity::handleMessage: null this");

	switch(Telegram_getMessage(telegram))
    {
		case kMovingEntityStartMoving:
            {
                VBVec3D position = this->transform.globalPosition;

            	switch(this->movingEntityDefinition->axis)
                {
            		case __XAXIS:
                        position.x = this->initialPosition + this->movingEntityDefinition->maximumDisplacement * this->direction.x;
                        break;

            		case __YAXIS:
                        position.y = this->initialPosition + this->movingEntityDefinition->maximumDisplacement * this->direction.y;
                        break;
                }

                Actor_setPosition(__SAFE_CAST(Actor, this), &position);
            }

        	MovingEntity_startMovement(this);
        	return true;
			break;
	}

	return false;
}

// unregister the shape with the collision detection system
void MovingEntity_unregisterShape(MovingEntity this)
{
	ASSERT(this, "MovingEntity::unregisterShape: null this");

	Shape_setActive(this->shape, false);
}

// tell me I've been hit
void MovingEntity_takeHit(MovingEntity this __attribute__ ((unused)), int axis __attribute__ ((unused)), s8 direction __attribute__ ((unused)))
{
}

// set position
void MovingEntity_setLocalPosition(MovingEntity this, const VBVec3D* position)
{
	// set my position
	Actor_setLocalPosition(__SAFE_CAST(Actor, this), position);

	// save initial position
	switch(this->movingEntityDefinition->axis)
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
int MovingEntity_getAxisFreeForMovement(MovingEntity this __attribute__ ((unused)))
{
	return 0;
}

void MovingEntity_checkDisplacement(MovingEntity this)
{
	// update position
	switch(this->movingEntityDefinition->axis)
    {
		case __XAXIS:
			{
				fix19_13 distance = __ABS((this->transform.globalPosition.x - this->initialPosition));

				if(distance > this->movingEntityDefinition->maximumDisplacement)
				{
					// make sure that I don't get stuck moving back and forth
                	Body_stopMovement(this->body, (__XAXIS | __YAXIS | __ZAXIS));

                    MessageDispatcher_dispatchMessage(this->movingEntityDefinition->idleDuration, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kMovingEntityStartMoving, NULL);
				}
			}
			break;

		case __YAXIS:
			{
				fix19_13 distance = __ABS((this->transform.globalPosition.y - this->initialPosition));

				if(distance > this->movingEntityDefinition->maximumDisplacement)
				{
					// make sure that I don't get stuck moving back and forth
                	Body_stopMovement(this->body, (__XAXIS | __YAXIS | __ZAXIS));

                    MessageDispatcher_dispatchMessage(this->movingEntityDefinition->idleDuration, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kMovingEntityStartMoving, NULL);
				}
			}
			break;
    }
}

// start moving
void MovingEntity_startMovement(MovingEntity this)
{
	switch(this->movingEntityDefinition->axis)
    {
		case __XAXIS:

			switch(this->direction.x)
            {
				case __LEFT:

					this->direction.x = __RIGHT;
					break;

				case __RIGHT:

					this->direction.x = __LEFT;
					break;
            }

			{
				Velocity velocity =
                {
					((int)this->movingEntityDefinition->velocity * this->direction.x),
					0,
					0,
				};

				Body_moveUniformly(this->body, velocity);
			}
			break;

		case __YAXIS:

			switch(this->direction.y)
            {
				case __UP:

					this->direction.y = __DOWN;
					break;

				case __DOWN:

					this->direction.y = __UP;
					break;
            }

			{
				Velocity velocity =
                {
					0,
					((int)this->movingEntityDefinition->velocity * this->direction.y),
					0,
				};

				Body_moveUniformly(this->body, velocity);
			}
			break;
	}
}

// stop moving
void MovingEntity_stopMovement(MovingEntity this)
{
	// stop moving
	Actor_stopMovement(__SAFE_CAST(Actor, this), false);

	MessageDispatcher_dispatchMessage(this->movingEntityDefinition->idleDuration, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kMovingEntityStartMovement, NULL);
}
