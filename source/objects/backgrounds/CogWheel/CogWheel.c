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

#include <objects.h>
#include "CogWheel.h"

#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define COG_WHEEL_ROTATION_DELAY 500


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(CogWheel, InanimatedInGameEntity);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void CogWheel_rotate(CogWheel this);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(CogWheel, InanimatedInGameEntityDefinition* inanimatedInGameEntityDefinition, int id, const char* const name)
__CLASS_NEW_END(CogWheel, inanimatedInGameEntityDefinition, id, name);

// class's constructor
void CogWheel_constructor(CogWheel this, InanimatedInGameEntityDefinition* inanimatedInGameEntityDefinition, int id, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(inanimatedInGameEntityDefinition, id, name);
	
	if(this->shape)
	{
		Shape_setCheckForCollisions(__SAFE_CAST(Shape, this->shape), false);
	}
}

// class's destructor
void CogWheel_destructor(CogWheel this)
{
    // discard pending moving messages
    MessageDispatcher_discardDelayedMessages(MessageDispatcher_getInstance(), kMove);

	// delete the super object
	__DESTROY_BASE;
}

// ready method
void CogWheel_ready(CogWheel this)
{
	ASSERT(this, "CogWheel::ready: null this");

	Entity_ready(__SAFE_CAST(Entity, this));
	
	// start moving
	MessageDispatcher_dispatchMessage(COG_WHEEL_ROTATION_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kMove, NULL);
	
	// must make sure that the shape is updated
	if(this->shape)
	{
		CollisionManager_shapeStartedMoving(CollisionManager_getInstance(), this->shape);
	}
}

// state's on message
bool CogWheel_handleMessage(CogWheel this, Telegram telegram)
{
	switch(Telegram_getMessage(telegram))
    {
		case kMove:

            CogWheel_rotate(this);
			break;
	}
	
	return false;
}

// rotate cogwheel
static void CogWheel_rotate(CogWheel this)
{
	this->transform.localRotation.z += 1;
	Container_setLocalRotation(__SAFE_CAST(Container, this), &this->transform.localRotation);

    // send delayed message to itself to trigger next movement
    MessageDispatcher_dispatchMessage(COG_WHEEL_ROTATION_DELAY, __SAFE_CAST(Object, this), __GET_CAST(Object, this), kMove, NULL);
}

// resume after pause
void CogWheel_resume(CogWheel this)
{
	ASSERT(this, "Entity::resume: null this");

	Entity_resume(__SAFE_CAST(Entity, this));

    // send delayed message to itself to trigger next movement
    MessageDispatcher_dispatchMessage(COG_WHEEL_ROTATION_DELAY, __SAFE_CAST(Object, this), __GET_CAST(Object, this), kMove, NULL);
}

// does it move?
bool CogWheel_moves(CogWheel this)
{
	ASSERT(this, "CogWheel::moves: null this");

	return true;
}
