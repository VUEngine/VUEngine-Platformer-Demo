/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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
#include <CollisionManager.h>
#include <Optics.h>
#include <PhysicalWorld.h>
#include <PlatformerLevelState.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include "CannonBall.h"


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void CannonBall::constructor(CannonBallSpec* cannonBallSpec, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor((ActorSpec*)cannonBallSpec, internalId, name);

	// I start my life hidden
	this->hidden = true;
}

// class's constructor
void CannonBall::destructor()
{
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kMessageCannonBallCheckDisplacement);

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// start moving
void CannonBall::startMovement()
{
	Velocity velocity = {0, 0, __I_TO_FIX10_6(-8)};

	Actor::moveUniformly(this, &velocity);

	// show me
	Entity::show(this);

	MessageDispatcher::dispatchMessage(CANNON_BALL_DISPLACEMENT_CHECK_DELAY, Object::safeCast(this), Object::safeCast(this), kMessageCannonBallCheckDisplacement, NULL);
}

// move back to cannon
void CannonBall::stop(u16 axis __attribute__((unused)))
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
	if(this->transformation.globalPosition.z <= __PIXELS_TO_METERS(CANNON_BALL_MINIMUM_Z_VALUE))
	{
		CannonBall::stop(this, __ALL_AXIS);
	}
	else
	{
		MessageDispatcher::dispatchMessage(CANNON_BALL_DISPLACEMENT_CHECK_DELAY, Object::safeCast(this), Object::safeCast(this), kMessageCannonBallCheckDisplacement, NULL);
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


