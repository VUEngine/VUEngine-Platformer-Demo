/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
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
void Door::constructor(AnimatedEntitySpec* animatedEntitySpec, int16 internalId, const char* const name)
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

uint32 Door::getHintType()
{
	return kEnterHint;
}
