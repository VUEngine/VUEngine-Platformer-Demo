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
#include <Screen.h>
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

__CLASS_DEFINITION(Door);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Door, __PARAMETERS(AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int ID))
__CLASS_NEW_END(Door, __ARGUMENTS(animatedInGameEntityDefinition, ID));

// class's constructor
void Door_constructor(Door this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int ID)
{
	// construct base
	__CONSTRUCT_BASE(AnimatedInGameEntity, __ARGUMENTS(animatedInGameEntityDefinition, ID));

	// register a shape for collision detection
	this->shape = CollisionManager_registerShape(CollisionManager_getInstance(), (Entity)this, kCuboid);

	this->destination = NULL;
}

// class's destructor
void Door_destructor(Door this)
{
	// delete the super object
	__DESTROY_BASE(AnimatedInGameEntity);
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
	switch (Telegram_getMessage(telegram))
    {
		case kEnterDoor:

			if (Door_hasDestination(this))
			{
				PlatformerLevelState_goToLevel((StageDefinition*)this->destination);
				return true;
			}
			break;

		case kOpenDoor:

			if (Door_hasDestination(this))
			{
				AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Opening");
			}
			break;
			
		case kCloseDoor:

			if (Door_hasDestination(this))
			{
				AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)this, "Closing");
			}
			break;
	}
	
	return false;
}

bool Door_hasDestination(Door this)
{
	return NULL != this->destination;
}