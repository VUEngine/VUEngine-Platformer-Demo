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
#include <Hint.h>
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
	__CONSTRUCT_BASE(AnimatedInGameEntity, animatedInGameEntityDefinition, id, name);

	// register a shape for collision detection
	this->shape = CollisionManager_registerShape(Game_getCollisionManager(Game_getInstance()), __SAFE_CAST(SpatialObject, this), kCuboid);

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
StageEntryPointDefinition* Door_getExtraInfo(Door this)
{
	ASSERT(this, "Door::setExtraInfo: null this");

	return this->destinationDefinition;
}

// set destination
void Door_setExtraInfo(Door this, void* extraInfo)
{
	ASSERT(this, "Door::setExtraInfo: null this");

	this->destinationDefinition = (StageEntryPointDefinition*)extraInfo;
}

// ready
void Door_ready(Door this)
{
	ASSERT(this, "Door::ready: null this");

    if(__VIRTUAL_CALL(bool, Door, hasDestination, this))
    {
        AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Open");
    }
    else
    {
        AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Closed");
    }
}

// class's handle message
bool Door_handleMessage(Door this, Telegram telegram)
{
	switch(Telegram_getMessage(telegram))
    {
        case kHeroCheckOverlapping:

            if(Door_checkStillOverlapping(this))
            {
                // delayed check if still overlapped by hero
                MessageDispatcher_dispatchMessage(DOOR_OVERLAPPING_CHECK_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroCheckOverlapping, NULL);
            }

            return true;
            break;

		case kHeroEnterDoor:

			if(__VIRTUAL_CALL(bool, Door, hasDestination, this))
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

void Door_onOverlapping(Door this)
{
    // first contact with hero?
    if(!Door_isOverlapping(this) && __VIRTUAL_CALL(bool, Door, hasDestination, this, this))
    {
        MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Hero_getInstance()), kHeroStartOverlapping, NULL);

	    __VIRTUAL_CALL(void, Door, setOverlapping, this);
    }
}

void Door_setOverlapping(Door this)
{
	this->currentlyOverlappingHero = true;

    // delayed check if still overlapped by hero
    MessageDispatcher_dispatchMessage(DOOR_OVERLAPPING_CHECK_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroCheckOverlapping, NULL);
}

void Door_unsetOverlapping(Door this)
{
    this->currentlyOverlappingHero = false;

    // inform the hero
    MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Hero_getInstance()), kHeroEndOverlapping, NULL);
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
	    __VIRTUAL_CALL(void, Door, unsetOverlapping, this);
	}

	return this->currentlyOverlappingHero;
}

bool Door_canEnter(Door this)
{
	return __VIRTUAL_CALL(bool, Door, hasDestination, this);
}

u8 Door_getHintType(Door this)
{
	return kEnterHint;
}
