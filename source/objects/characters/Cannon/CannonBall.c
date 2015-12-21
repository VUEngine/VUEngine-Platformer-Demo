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
#include <MessageDispatcher.h>
#include <Cuboid.h>
#include <PhysicalWorld.h>
#include <UserDataManager.h>
#include <Container.h>

#include <objects.h>
#include "CannonBall.h"

#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(CannonBall, AnimatedInGameEntity);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void CannonBall_move(CannonBall this);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(CannonBall, InanimatedInGameEntityDefinition* inanimatedInGameEntityDefinition, int id, const char* const name)
__CLASS_NEW_END(CannonBall, inanimatedInGameEntityDefinition, id, name);

// class's constructor
void CannonBall_constructor(CannonBall this, InanimatedInGameEntityDefinition* inanimatedInGameEntityDefinition, int id, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(inanimatedInGameEntityDefinition, id, name);

	// register a shape for collision detection
    this->shape = CollisionManager_registerShape(CollisionManager_getInstance(), __SAFE_CAST(SpatialObject, this), kCuboid);

	// must make sure that the shape is updated
	CollisionManager_shapeStartedMoving(CollisionManager_getInstance(), this->shape);

	// start moving
    CannonBall_move(this);
}

// class's destructor
void CannonBall_destructor(CannonBall this)
{
	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

void CannonBall_removeFromStage(CannonBall this)
{
	ASSERT(this, "CannonBall::removeFromStage: null this");

	Container_deleteMyself(__SAFE_CAST(Container, this));
    Shape_setActive(this->shape, false);
}

// state's on message
bool CannonBall_handleMessage(CannonBall this, Telegram telegram)
{
	ASSERT(this, "CannonBall::handleMessage: null this");

	switch(Telegram_getMessage(telegram))
    {
		case kMove:

            CannonBall_move(this);
			break;
	}
	
	return false;
}

// move cannon ball
void CannonBall_move(CannonBall this)
{
    // get local position of cannon ball
    VBVec3D localPosition = *Container_getLocalPosition(__SAFE_CAST(Container, this));

    if (FIX19_13TOI(localPosition.z) < CANNON_BALL_MINIMUM_Z_POSITION)
    {
        //CannonBall_removeFromStage(this);
    }
    else
    {
        // substract offset from local position z value
        localPosition.z -= ITOFIX19_13(CANNON_BALL_Z_OFFSET_PER_CYCLE);

        // update cannon ball's position
        __VIRTUAL_CALL(void, Container, setLocalPosition, __SAFE_CAST(Container, this), &localPosition);

        // send delayed message to self to trigger next movement
        MessageDispatcher_dispatchMessage(CANNON_BALL_MOVE_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kMove, NULL);
    }
}