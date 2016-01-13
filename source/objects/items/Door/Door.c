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
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Door, AnimatedInGameEntity);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

bool Door_checkStillOverlapping(Door this);


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
	this->shape = CollisionManager_registerShape(CollisionManager_getInstance(), __SAFE_CAST(SpatialObject, this), kCuboid);

    // init class variables
	this->destinationDefinition = NULL;
	this->currentlyOverlappingHero = false;
}

// class's destructor
void Door_destructor(Door this)
{
	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// get destination
PlatformerStageEntryPointDefinition* Door_getExtraInfo(Door this)
{
	ASSERT(this, "Door::setExtraInfo: null this");

	return this->destinationDefinition;
}

// set destination
void Door_setExtraInfo(Door this, void* extraInfo)
{
	ASSERT(this, "Door::setExtraInfo: null this");

	this->destinationDefinition = (PlatformerStageEntryPointDefinition*)extraInfo;
}

// state's handle message
bool Door_handleMessage(Door this, Telegram telegram)
{
	switch(Telegram_getMessage(telegram))
    {
        case kCheckOverlapping:

            if(Door_checkStillOverlapping(this))
            {
                // check if still overlapping hero in 100 milliseconds
                MessageDispatcher_dispatchMessage(100, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCheckOverlapping, NULL);
            }

            return true;
            break;

		case kEnterDoor:

			if(Door_hasDestination(this))
			{
				PlatformerLevelState_enterStage(PlatformerLevelState_getInstance(), this->destinationDefinition);
				return true;
			}
			break;
	}

	return false;
}

bool Door_hasDestination(Door this)
{
	return NULL != this->destinationDefinition;
}

void Door_setOverlapping(Door this)
{
	this->currentlyOverlappingHero = true;

    if(Door_hasDestination(this))
    {
        AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Opening");
    }

    // check if still overlapping hero in 100 milliseconds
    MessageDispatcher_dispatchMessage(100, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCheckOverlapping, NULL);
}

bool Door_isOverlapping(Door this)
{
	return this->currentlyOverlappingHero;
}

bool Door_checkStillOverlapping(Door this)
{
	// check if hero has recently overlapped door and is still doing so
	if(
		this->currentlyOverlappingHero &&
		!__VIRTUAL_CALL(int, Shape, overlaps, Entity_getShape(__SAFE_CAST(Entity, Hero_getInstance())), Entity_getShape(__SAFE_CAST(Entity, this)))
	)
	{
		this->currentlyOverlappingHero = false;

        // inform the hero
        MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Hero_getInstance()), kEndOverlapping, NULL);

        if(Door_hasDestination(this))
        {
            AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Closing");
        }
	}

	return this->currentlyOverlappingHero;
}