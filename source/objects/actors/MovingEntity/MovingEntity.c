/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2017 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
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
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(MovingEntity, Actor);


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void MovingEntity_registerShape(MovingEntity this);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(MovingEntity, MovingEntityDefinition* MovingEntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(MovingEntity, MovingEntityDefinition, id, internalId, name);

// class's constructor
void MovingEntity_constructor(MovingEntity this, MovingEntityDefinition* movingEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	ASSERT(this, "MovingEntity::constructor: null this");

	// construct base
	__CONSTRUCT_BASE(Actor, (ActorDefinition*)&movingEntityDefinition->actorDefinition, id, internalId, name);

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

	MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kMovingEntityStartMoving);
	MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kMovingEntityCheckDirection);

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

bool MovingEntity_handleMessage(MovingEntity this, Telegram telegram)
{
	ASSERT(this, "MovingEntity::handleMessage: null this");

	switch(Telegram_getMessage(telegram))
	{
		case kMovingEntityCheckDirection:

			if(Body_isAwake(this->body))
			{
				MovingEntity_checkDisplacement(this);
			}
			break;

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
				else
				{
					MessageDispatcher_dispatchMessage(MOVING_ENTITY_DIRECTION_CHECK_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kMovingEntityCheckDirection, NULL);
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
				else
				{
					MessageDispatcher_dispatchMessage(MOVING_ENTITY_DIRECTION_CHECK_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kMovingEntityCheckDirection, NULL);
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

	MessageDispatcher_dispatchMessage(MOVING_ENTITY_DIRECTION_CHECK_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kMovingEntityCheckDirection, NULL);
}
