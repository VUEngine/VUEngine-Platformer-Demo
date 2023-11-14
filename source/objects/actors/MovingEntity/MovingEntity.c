/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <VUEngine.h>
#include <MessageDispatcher.h>
#include <CollisionManager.h>
#include <Optics.h>
#include <PhysicalWorld.h>
#include <MessageDispatcher.h>
#include <PlatformerLevelState.h>
#include <Telegram.h>
#include <debugUtilities.h>


#include "MovingEntity.h"


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void MovingEntity::constructor(MovingEntitySpec* movingEntitySpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor((ActorSpec*)&movingEntitySpec->actorSpec, internalId, name);

	this->movingEntitySpec = movingEntitySpec;

	this->initialPosition = 0;

	NormalizedDirection normalizedDirection =
	{
		__RIGHT, __DOWN, __FAR
	};

	switch(this->movingEntitySpec->axis)
	{
		case __X_AXIS:

			normalizedDirection.x = this->movingEntitySpec->normalizedDirection;
			break;

		case __Y_AXIS:

			normalizedDirection.y = this->movingEntitySpec->normalizedDirection;
			break;
	}

	Entity::setNormalizedDirection(this, normalizedDirection);
}

// class's constructor
void MovingEntity::destructor()
{
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), ListenerObject::safeCast(this), kMessageMovingEntityStartMoving);
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), ListenerObject::safeCast(this), kMessageMovingEntityCheckDirection);

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}
/*
// set spec
void MovingEntity::setSpec(void* movingEntitySpec)
{
	ASSERT(movingEntitySpec, "MovingEntity::setSpec: null spec");

	// save spec
	this->movingEntitySpec = movingEntitySpec;

	Base::setSpec(this, &((MovingEntitySpec*)movingEntitySpec)->actorSpec);
}
*/

// ready method
void MovingEntity::ready(bool recursive)
{
	// call base
	Base::ready(this, recursive);

	// save initial position
	switch(this->movingEntitySpec->axis)
	{
		case __X_AXIS:

			this->initialPosition = this->transformation.globalPosition.x;
			break;

		case __Y_AXIS:

			this->initialPosition = this->transformation.globalPosition.y;
			break;
	}

	MovingEntity::startMovement(this);
}

bool MovingEntity::handleMessage(Telegram telegram)
{
	NormalizedDirection normalizedDirection = Entity::getNormalizedDirection(this);

	switch(Telegram::getMessage(telegram))
	{
		case kMessageMovingEntityCheckDirection:

			if(Body::isAwake(this->body))
			{
				MovingEntity::checkDisplacement(this);
			}
			break;

		case kMessageMovingEntityStartMoving:
			{
				Vector3D position = this->transformation.globalPosition;

				switch(this->movingEntitySpec->axis)
				{
					case __X_AXIS:
						position.x = this->initialPosition + this->movingEntitySpec->maximumDisplacement * normalizedDirection.x;
						break;

					case __Y_AXIS:
						position.y = this->initialPosition + this->movingEntitySpec->maximumDisplacement * normalizedDirection.y;
						break;
				}

				Actor::setPosition(this, &position);
			}

			MovingEntity::startMovement(this);
			return true;
			break;
	}

	return false;
}

// tell me I've been hit
void MovingEntity::takeHit(uint16 axis __attribute__ ((unused)), int8 direction __attribute__ ((unused)))
{
}

void MovingEntity::checkDisplacement()
{
	// update position
	switch(this->movingEntitySpec->axis)
	{
		case __X_AXIS:
			{
				fix10_6 distance = __ABS((this->transformation.globalPosition.x - this->initialPosition));

				if(distance > this->movingEntitySpec->maximumDisplacement)
				{
					// make sure that I don't get stuck moving back and forth
					Body::stopMovement(this->body, (__X_AXIS | __Y_AXIS | __Z_AXIS));

					MessageDispatcher::dispatchMessage(this->movingEntitySpec->idleDuration, ListenerObject::safeCast(this), ListenerObject::safeCast(this), kMessageMovingEntityStartMoving, NULL);
				}
				else
				{
					MessageDispatcher::dispatchMessage(MOVING_ENTITY_DIRECTION_CHECK_DELAY, ListenerObject::safeCast(this), ListenerObject::safeCast(this), kMessageMovingEntityCheckDirection, NULL);
				}
			}
			break;

		case __Y_AXIS:
			{
				fix10_6 distance = __ABS((this->transformation.globalPosition.y - this->initialPosition));

				if(distance > this->movingEntitySpec->maximumDisplacement)
				{
					// make sure that I don't get stuck moving back and forth
					Body::stopMovement(this->body, (__X_AXIS | __Y_AXIS | __Z_AXIS));

					MessageDispatcher::dispatchMessage(this->movingEntitySpec->idleDuration, ListenerObject::safeCast(this), ListenerObject::safeCast(this), kMessageMovingEntityStartMoving, NULL);
				}
				else
				{
					MessageDispatcher::dispatchMessage(MOVING_ENTITY_DIRECTION_CHECK_DELAY, ListenerObject::safeCast(this), ListenerObject::safeCast(this), kMessageMovingEntityCheckDirection, NULL);
				}
			}
			break;
	}
}

// start moving
void MovingEntity::startMovement()
{
	NormalizedDirection normalizedDirection = Entity::getNormalizedDirection(this);

	switch(this->movingEntitySpec->axis)
	{
		case __X_AXIS:

			switch(normalizedDirection.x)
			{
				case __LEFT:

					normalizedDirection.x = __RIGHT;
					break;

				case __RIGHT:

					normalizedDirection.x = __LEFT;
					break;
			}

			{
				Vector3D velocity =
				{
					((int)this->movingEntitySpec->velocity * normalizedDirection.x),
					0,
					0,
				};

				Body::moveUniformly(this->body, velocity);
			}
			break;

		case __Y_AXIS:

			switch(normalizedDirection.y)
			{
				case __UP:

					normalizedDirection.y = __DOWN;
					break;

				case __DOWN:

					normalizedDirection.y = __UP;
					break;
			}

			{
				Vector3D velocity =
				{
					0,
					((int)this->movingEntitySpec->velocity * normalizedDirection.y),
					0,
				};

				Body::moveUniformly(this->body, velocity);
			}
			break;
	}

	MessageDispatcher::dispatchMessage(MOVING_ENTITY_DIRECTION_CHECK_DELAY, ListenerObject::safeCast(this), ListenerObject::safeCast(this), kMessageMovingEntityCheckDirection, NULL);
}
