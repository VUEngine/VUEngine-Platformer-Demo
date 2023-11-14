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
#include <CollisionManager.h>
#include <Optics.h>
#include <PhysicalWorld.h>
#include <PlatformerLevelState.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Telegram.h>
#include "CannonBall.h"


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void CannonBall::constructor(CannonBallSpec* cannonBallSpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor((ActorSpec*)cannonBallSpec, internalId, name);

	// I start my life hidden
	this->hidden = true;
}

// class's constructor
void CannonBall::destructor()
{
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), ListenerObject::safeCast(this), kMessageCannonBallCheckDisplacement);

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// start moving
void CannonBall::startMovement()
{
	Vector3D velocity = {0, 0, __I_TO_FIX10_6(-8)};

	Actor::moveUniformly(this, &velocity);

	// show me
	Entity::show(this);

	MessageDispatcher::dispatchMessage(CannonBall_DISPLACEMENT_CHECK_DELAY, ListenerObject::safeCast(this), ListenerObject::safeCast(this), kMessageCannonBallCheckDisplacement, NULL);
}

// move back to cannon
void CannonBall::stop(uint16 axis __attribute__((unused)))
{
	// stop movement
	Actor::stopAllMovement(this);

	// set back local position
	Vector3D position = {0, 0, __PIXELS_TO_METERS(SORT_INCREMENT)};
	Actor::setLocalPosition(this, &position);

	// hide me
	Entity::hide(this);
}

void CannonBall::checkIfDistanceTraveled()
{
	if(this->transformation.globalPosition.z <= __PIXELS_TO_METERS(CannonBall_MINIMUM_Z_VALUE))
	{
		CannonBall::stop(this, __ALL_AXIS);
	}
	else
	{
		MessageDispatcher::dispatchMessage(CannonBall_DISPLACEMENT_CHECK_DELAY, ListenerObject::safeCast(this), ListenerObject::safeCast(this), kMessageCannonBallCheckDisplacement, NULL);
	}
}

// state's handle message
bool CannonBall::handleMessage(Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kMessageCannonShoot:

			CannonBall::startMovement(this);
			break;

		case kMessageCannonBallCheckDisplacement:

			CannonBall::checkIfDistanceTraveled(this);
			break;
	}

	return false;
}


