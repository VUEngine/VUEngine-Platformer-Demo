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
#include <CollisionManager.h>
#include <Optics.h>
#include <PhysicalWorld.h>
#include <PlatformerLevelState.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>


#include "CannonBall.h"


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(CannonBall, Actor);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(CannonBall, CannonBallDefinition* cannonBallDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(CannonBall, cannonBallDefinition, id, internalId, name);

// class's constructor
void CannonBall_constructor(CannonBall this, CannonBallDefinition* cannonBallDefinition, s16 id, s16 internalId, const char* const name)
{
	ASSERT(this, "CannonBall::constructor: null this");

	// construct base
	__CONSTRUCT_BASE(Actor, (ActorDefinition*)cannonBallDefinition, id, internalId, name);

	// I start my life hidden
	this->hidden = true;
}

// class's constructor
void CannonBall_destructor(CannonBall this)
{
	ASSERT(this, "CannonBall::destructor: null this");

	MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kCannonBallCheckDisplacement);

	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// start moving
void CannonBall_startMovement(CannonBall this)
{
	Velocity velocity = {0, 0, __I_TO_FIX19_13(-128)};

	Actor_moveUniformly(__SAFE_CAST(Actor, this), &velocity);

	// show me
	Entity_show(__SAFE_CAST(Entity, this));

	MessageDispatcher_dispatchMessage(CANNON_BALL_DISPLACEMENT_CHECK_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCannonBallCheckDisplacement, NULL);
}

// move back to cannon
void CannonBall_stopMovement(CannonBall this)
{
	// stop movement
	Actor_stopAllMovement(__SAFE_CAST(Actor, this));

	// set back local position
	Vector3D position = {0, 0, __F_TO_FIX19_13(-SORT_INCREMENT)};
	Actor_setLocalPosition(__SAFE_CAST(Actor, this), &position);

	// hide me
	Entity_hide(__SAFE_CAST(Entity, this));
}

static void CannonBall_checkIfDistanceTraveled(CannonBall this)
{
	if(this->transformation.globalPosition.z <= __I_TO_FIX19_13(CANNON_BALL_MINIMUM_Z_VALUE))
	{
		CannonBall_stopMovement(this);
	}
	else
	{
		MessageDispatcher_dispatchMessage(CANNON_BALL_DISPLACEMENT_CHECK_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCannonBallCheckDisplacement, NULL);
	}
}

// state's handle message
bool CannonBall_handleMessage(CannonBall this, Telegram telegram)
{
	ASSERT(this, "CannonBall::handleMessage: null this");

	switch(Telegram_getMessage(telegram))
	{
		case kCannonShoot:

			CannonBall_startMovement(this);
			break;

		case kCannonBallCheckDisplacement:

			CannonBall_checkIfDistanceTraveled(this);
			break;
	}

	return false;
}


