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
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Game.h>
#include <CollisionManager.h>
#include <Optics.h>
#include <PhysicalWorld.h>
#include <Prototypes.h>
#include <PlatformerLevelState.h>
#include <CollisionManager.h>

#include "CannonBall.h"


//---------------------------------------------------------------------------------------------------------
// 											 CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(CannonBall, Actor);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(CannonBall, ActorDefinition* definition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(CannonBall, definition, id, internalId, name);

// class's constructor
void CannonBall_constructor(CannonBall this, ActorDefinition* definition, s16 id, s16 internalId, const char* const name)
{
	ASSERT(this, "CannonBall::constructor: null this");

	// construct base
	__CONSTRUCT_BASE(Actor, definition, id, internalId, name);

	// register a shape for collision detection
	CannonBall_registerShape(this);

	// register a body for physics
	this->body = PhysicalWorld_registerBody(Game_getPhysicalWorld(Game_getInstance()), (BodyAllocator)__TYPE(Body), __SAFE_CAST(SpatialObject, this), definition->mass);

	// I start my life hidden
    this->hidden = true;
}

// class's constructor
void CannonBall_destructor(CannonBall this)
{
	ASSERT(this, "CannonBall::destructor: null this");

	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// ready method
void CannonBall_ready(CannonBall this, u32 recursive)
{
	ASSERT(this, "CannonBall::ready: null this");

	// call base
	AnimatedInGameEntity_ready(__SAFE_CAST(AnimatedInGameEntity, this), recursive);

	CannonBall_startMovement(this);
}

void CannonBall_update(CannonBall this, u32 elapsedTime)
{
	ASSERT(this, "CannonBall::udpate: null this");

    Actor_update(__SAFE_CAST(Actor, this), elapsedTime);

    if(Body_isMoving(this->body) && this->transform.globalPosition.z <= ITOFIX19_13(CANNON_BALL_MINIMUM_Z_VALUE))
    {
        // set state to idle
        CannonBall_stopMovement(this);
    }
}

// register a shape with the collision detection system
void CannonBall_registerShape(CannonBall this)
{
	ASSERT(this, "CannonBall::registerShape: null this");

	// register a shape for collision detection
	this->shape = CollisionManager_registerShape(Game_getCollisionManager(Game_getInstance()), __SAFE_CAST(SpatialObject, this), kCuboid);
}

// unregister the shape with the collision detection system
void CannonBall_unregisterShape(CannonBall this)
{
	ASSERT(this, "CannonBall::unregisterShape: null this");

	Shape_setActive(this->shape, false);
}

// tell me I've been hit

// retrieve axis free for movement
int CannonBall_getAxisFreeForMovement(CannonBall this __attribute__ ((unused)))
{
	return __ZAXIS;
}

// start moving
void CannonBall_startMovement(CannonBall this)
{
	Velocity velocity = {0, 0, ITOFIX19_13(-128)};

	Actor_moveUniformly(__SAFE_CAST(Actor, this), &velocity);

    // show me
	Entity_show(__SAFE_CAST(Entity, this));
}

// move back to cannon
void CannonBall_stopMovement(CannonBall this)
{
    // stop movement
    Actor_stopMovement(__SAFE_CAST(Actor, this), false);

    // set back local position
    VBVec3D position = {0, 0, FTOFIX19_13(-SORT_INCREMENT)};
    Actor_setLocalPosition(__SAFE_CAST(Actor, this), &position);

    // hide me
    Entity_hide(__SAFE_CAST(Entity, this));
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
	}

	return false;
}


