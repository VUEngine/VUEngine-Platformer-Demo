/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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
#include <Box.h>
#include <PhysicalWorld.h>
#include <Hint.h>
#include <Hero.h>
#include "Door.h"
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------




//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other



// class's constructor
void Door::constructor(Door this, AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(animatedEntityDefinition, id, internalId, name);

	// init class variables
	this->destinationDefinition = NULL;
}

// class's destructor
void Door::destructor(Door this)
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// get destination
StageEntryPointDefinition* Door::getExtraInfo(Door this)
{
	ASSERT(this, "Door::setExtraInfo: null this");

	return this->destinationDefinition;
}

// set destination
void Door::setExtraInfo(Door this, void* extraInfo)
{
	ASSERT(this, "Door::setExtraInfo: null this");

	this->destinationDefinition = (StageEntryPointDefinition*)extraInfo;
}

// ready
void Door::ready(Door this, bool recursive __attribute__ ((unused)))
{
	ASSERT(this, "Door::ready: null this");

	// call base
	Base::ready(this, recursive);

	if(Door::hasDestination(this))
	{
		AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, this), "Open");
	}
	else
	{
		AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, this), "Closed");
	}
}

// class's handle message
bool Door::handleMessage(Door this, Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kHeroEnterDoor:

			if(Door::hasDestination(this))
			{
				PlatformerLevelState::enterStage(PlatformerLevelState::getInstance(), this->destinationDefinition);
				return true;
			}
			break;
	}

	return false;
}

bool Door::hasDestination(Door this)
{
	return NULL != this->destinationDefinition;
}

void Door::onOverlapping(Door this)
{
	// first contact with hero?
	if(Door::hasDestination(this))
	{
		Door::setOverlapping(this);
	}
}

void Door::setOverlapping(Door this __attribute__ ((unused)))
{
}

void Door::unsetOverlapping(Door this __attribute__ ((unused)))
{
}

bool Door::canEnter(Door this)
{
	return Door::hasDestination(this);
}

u32 Door::getHintType(Door this __attribute__ ((unused)))
{
	return kEnterHint;
}
