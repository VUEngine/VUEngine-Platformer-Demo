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
#include "Door.h"

#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 											 CLASS'S MACROS
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Door, AnimatedInGameEntity);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Door, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name)
__CLASS_NEW_END(Door, animatedInGameEntityDefinition, id, name);

// class's constructor
void Door_constructor(Door this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(animatedInGameEntityDefinition, id, name);

	// register a shape for collision detection
	this->shape = CollisionManager_registerShape(CollisionManager_getInstance(), __GET_CAST(SpatialObject, this), kCuboid);

	this->destination = NULL;
}

// class's destructor
void Door_destructor(Door this)
{
	// delete the super object
	__DESTROY_BASE;
}

// get destination
void* Door_getExtraInfo(Door this)
{
	ASSERT(this, "Door::setExtraInfo: null this");
	
	return this->destination;
}

// set destination
void Door_setExtraInfo(Door this, void* extraInfo)
{
	ASSERT(this, "Door::setExtraInfo: null this");

	this->destination = (void (*)(void))extraInfo;
}

// state's on message
bool Door_handleMessage(Door this, Telegram telegram)
{
	switch(Telegram_getMessage(telegram))
    {
		case kEnterDoor:

			if(Door_hasDestination(this))
			{
				PlatformerLevelState_goToLevel((PlatformerStageDefinition*)this->destination);
				return true;
			}
			break;

		case kOpenDoor:

			if(Door_hasDestination(this))
			{
				AnimatedInGameEntity_playAnimation(__GET_CAST(AnimatedInGameEntity, this), "Opening");
			}
			break;
			
		case kCloseDoor:

			if(Door_hasDestination(this))
			{
				AnimatedInGameEntity_playAnimation(__GET_CAST(AnimatedInGameEntity, this), "Closing");
			}
			break;
	}
	
	return false;
}

bool Door_hasDestination(Door this)
{
	return NULL != this->destination;
}