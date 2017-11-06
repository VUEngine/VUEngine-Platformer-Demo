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
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Game.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Cuboid.h>
#include <PhysicalWorld.h>
#include <Hint.h>
#include <Hero.h>
#include "Door.h"
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Door, AnimatedEntity);


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

bool Door_checkStillOverlapping(Door this);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Door, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(Door, animatedEntityDefinition, id, internalId, name);

// class's constructor
void Door_constructor(Door this, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(AnimatedEntity, animatedEntityDefinition, id, internalId, name);

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
void Door_ready(Door this, bool recursive __attribute__ ((unused)))
{
	ASSERT(this, "Door::ready: null this");

	// call base
	__CALL_BASE_METHOD(AnimatedEntity, ready, this, recursive);

	if(__VIRTUAL_CALL(Door, hasDestination, this))
	{
		AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Open");
	}
	else
	{
		AnimatedEntity_playAnimation(__SAFE_CAST(AnimatedEntity, this), "Closed");
	}
}

void Door_resume(Door this)
{
	__CALL_BASE_METHOD(AnimatedEntity, resume, this);

	MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kHeroCheckOverlapping);
	MessageDispatcher_dispatchMessage(DOOR_OVERLAPPING_CHECK_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroCheckOverlapping, NULL);
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

			if(__VIRTUAL_CALL(Door, hasDestination, this))
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
	if(!Door_isOverlapping(this) && __VIRTUAL_CALL(Door, hasDestination, this))
	{
		MessageDispatcher_dispatchMessage(0, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Hero_getInstance()), kHeroStartOverlapping, NULL);

		__VIRTUAL_CALL(Door, setOverlapping, this);
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
	CollisionInformation collisionInformation = __VIRTUAL_CALL(Shape, overlaps, VirtualList_front(Entity_getShapes(__SAFE_CAST(Entity, Hero_getInstance()))), VirtualList_front(this->shapes));

	// check if hero has recently overlapped door and is still doing so
	if(this->currentlyOverlappingHero && !collisionInformation.shape)
	{
		__VIRTUAL_CALL(Door, unsetOverlapping, this);
	}

	return this->currentlyOverlappingHero;
}

bool Door_canEnter(Door this)
{
	return __VIRTUAL_CALL(Door, hasDestination, this);
}

u32 Door_getHintType(Door this __attribute__ ((unused)))
{
	return kEnterHint;
}
