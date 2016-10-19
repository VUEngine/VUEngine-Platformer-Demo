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


