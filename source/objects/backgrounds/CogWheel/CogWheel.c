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
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(CogWheel, Image);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void CogWheel_rotate(CogWheel this);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(CogWheel, ImageDefinition* imageDefinition, s16 id, const char* const name)
__CLASS_NEW_END(CogWheel, imageDefinition, id, name);

// class's constructor
void CogWheel_constructor(CogWheel this, ImageDefinition* imageDefinition, s16 id, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(Image, imageDefinition, id, name);
}

// class's destructor
void CogWheel_destructor(CogWheel this)
{
    // discard pending delayed messages
    MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kCogWheelMove);

	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// ready method
void CogWheel_ready(CogWheel this, u32 recursive)
{
	ASSERT(this, "CogWheel::ready: null this");

	Entity_ready(__SAFE_CAST(Entity, this), recursive);

	// start moving
	MessageDispatcher_dispatchMessage(COG_WHEEL_ROTATION_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCogWheelMove, NULL);
}

// state's handle message
bool CogWheel_handleMessage(CogWheel this, Telegram telegram)
{
	switch(Telegram_getMessage(telegram))
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
	Container_setLocalRotation(__SAFE_CAST(Container, this), &this->transform.localRotation);

    // send delayed message to self to trigger next movement
    MessageDispatcher_dispatchMessage(COG_WHEEL_ROTATION_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCogWheelMove, NULL);
}
