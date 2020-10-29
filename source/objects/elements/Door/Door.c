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
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void Door::constructor(AnimatedEntitySpec* animatedEntitySpec, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(animatedEntitySpec, internalId, name);

	// init class variables
	this->destinationSpec = NULL;
}

// class's destructor
void Door::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// get destination
StageEntryPointSpec* Door::getExtraInfo()
{
	return this->destinationSpec;
}

// set destination
void Door::setExtraInfo(void* extraInfo)
{
	this->destinationSpec = (StageEntryPointSpec*)extraInfo;
}

// ready
void Door::ready(bool recursive __attribute__ ((unused)))
{
	// call base
	Base::ready(this, recursive);

	if(Door::hasDestination(this))
	{
		AnimatedEntity::playAnimation(this, "Open");
	}
	else
	{
		AnimatedEntity::playAnimation(this, "Closed");
	}
}

// class's handle message
bool Door::handleMessage(Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kMessageHeroEnterDoor:

			if(Door::hasDestination(this))
			{
				PlatformerLevelState::enterStage(PlatformerLevelState::getInstance(), this->destinationSpec);
				return true;
			}
			break;
	}

	return false;
}

bool Door::hasDestination()
{
	return NULL != this->destinationSpec;
}

void Door::onOverlapping()
{
	// first contact with hero?
	if(Door::hasDestination(this))
	{
		Door::setOverlapping(this);
	}
}

void Door::setOverlapping()
{
}

void Door::unsetOverlapping()
{
}

bool Door::canEnter()
{
	return Door::hasDestination(this);
}

u32 Door::getHintType()
{
	return kEnterHint;
}
