/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev
 * jorgech3@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
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
__CLASS_NEW_DEFINITION(CogWheel, InanimatedInGameEntityDefinition* inanimatedInGameEntityDefinition, int ID)
__CLASS_NEW_END(CogWheel, inanimatedInGameEntityDefinition, ID);

// class's constructor
void CogWheel_constructor(CogWheel this, InanimatedInGameEntityDefinition* inanimatedInGameEntityDefinition, int ID)
{
	// construct base
	__CONSTRUCT_BASE(inanimatedInGameEntityDefinition, ID);
	
	if(this->shape)
	{
		Shape_setCheckForCollisions(__GET_CAST(Shape, this->shape), false);
	}
}

// class's destructor
void CogWheel_destructor(CogWheel this)
{
    // discard pending moving messages
    MessageDispatcher_discardDelayedMessages(MessageDispatcher_getInstance(), kCogWheelMove);

	// delete the super object
	__DESTROY_BASE;
}

// ready method
void CogWheel_ready(CogWheel this)
{
	ASSERT(this, "CogWheel::ready: null this");

	Entity_ready(__GET_CAST(Entity, this));
	
	// start moving
	MessageDispatcher_dispatchMessage(COG_WHEEL_ROTATION_DELAY, __GET_CAST(Object, this), __GET_CAST(Object, this), kCogWheelMove, NULL);
	
	// must make sure that the shape is updated
	if(this->shape)
	{
		CollisionManager_shapeStartedMoving(CollisionManager_getInstance(), this->shape);
	}
}

// state's on message
bool CogWheel_handleMessage(CogWheel this, Telegram telegram)
{
	switch (Telegram_getMessage(telegram))
    {
		case kCogWheelMove:

            CogWheel_rotate(this);
			break;
	}
	
	return false;
}

// rotate cogwheel
static void CogWheel_rotate(CogWheel this)
{
	this->transform.localRotation.z += 1;
	Container_setLocalRotation(__GET_CAST(Container, this), &this->transform.localRotation);

    // send delayed message to itself to trigger next movement
    MessageDispatcher_dispatchMessage(COG_WHEEL_ROTATION_DELAY, __GET_CAST(Object, this), __GET_CAST(Object, this), kCogWheelMove, NULL);
}

// resume after pause
void CogWheel_resume(CogWheel this)
{
	ASSERT(this, "Entity::resume: null this");

	Entity_resume(__GET_CAST(Entity, this));

    // send delayed message to itself to trigger next movement
    MessageDispatcher_dispatchMessage(COG_WHEEL_ROTATION_DELAY, __GET_CAST(Object, this), __GET_CAST(Object, this), kCogWheelMove, NULL);
}

// does it move?
bool CogWheel_moves(CogWheel this)
{
	ASSERT(this, "CogWheel::moves: null this");

	return true;
}
