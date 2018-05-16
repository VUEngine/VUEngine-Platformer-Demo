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
void CannonBall::constructor(CannonBall this, CannonBallDefinition* cannonBallDefinition, s16 id, s16 internalId, const char* const name)
{
	ASSERT(this, "CannonBall::constructor: null this");

	// construct base
	Base::constructor((ActorDefinition*)cannonBallDefinition, id, internalId, name);

	// I start my life hidden
	this->hidden = true;
}

// class's constructor
void CannonBall::destructor(CannonBall this)
{
	ASSERT(this, "CannonBall::destructor: null this");

	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), __SAFE_CAST(Object, this), kCannonBallCheckDisplacement);

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// start moving
void CannonBall::startMovement(CannonBall this)
{
	Velocity velocity = {0, 0, __I_TO_FIX10_6(-8)};

	Actor::moveUniformly(__SAFE_CAST(Actor, this), &velocity);

	// show me
	Entity::show(__SAFE_CAST(Entity, this));

	MessageDispatcher::dispatchMessage(CANNON_BALL_DISPLACEMENT_CHECK_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCannonBallCheckDisplacement, NULL);
}

// move back to cannon
void CannonBall::stopMovement(CannonBall this)
{
	// stop movement
	Actor::stopAllMovement(__SAFE_CAST(Actor, this));

	// set back local position
	Vector3D position = {0, 0, __F_TO_FIX10_6(-SORT_INCREMENT)};
	Actor::setLocalPosition(__SAFE_CAST(Actor, this), &position);

	// hide me
	Entity::hide(__SAFE_CAST(Entity, this));
}

static void CannonBall::checkIfDistanceTraveled(CannonBall this)
{
	if(this->transformation.globalPosition.z <= __PIXELS_TO_METERS(CANNON_BALL_MINIMUM_Z_VALUE))
	{
		CannonBall::stopMovement(this);
	}
	else
	{
		MessageDispatcher::dispatchMessage(CANNON_BALL_DISPLACEMENT_CHECK_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCannonBallCheckDisplacement, NULL);
	}
}

// state's handle message
bool CannonBall::handleMessage(CannonBall this, Telegram telegram)
{
	ASSERT(this, "CannonBall::handleMessage: null this");

	switch(Telegram::getMessage(telegram))
	{
		case kCannonShoot:

			CannonBall::startMovement(this);
			break;

		case kCannonBallCheckDisplacement:

			CannonBall::checkIfDistanceTraveled(this);
			break;
	}

	return false;
}


