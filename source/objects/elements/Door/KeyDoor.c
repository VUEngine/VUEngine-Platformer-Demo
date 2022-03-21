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
#include "KeyDoor.h"
#include <PlatformerLevelState.h>
#include <LevelDoneScreenState.h>
#include <Hero.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void KeyDoor::constructor(AnimatedEntitySpec* animatedEntitySpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor(animatedEntitySpec, internalId, name);
}

// class's destructor
void KeyDoor::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// ready
void KeyDoor::ready(bool recursive __attribute__ ((unused)))
{
	// call base
	Base::ready(this, recursive);

	AnimatedEntity::playAnimation(this, "Key");
}

bool KeyDoor::hasDestination()
{
	return true;
}

void KeyDoor::setOverlapping()
{
	if(Hero::hasKey(Hero::getInstance()))
	{
		AnimatedEntity::playAnimation(this, "Opening");
	}

	Base::setOverlapping(this);
}

void KeyDoor::unsetOverlapping()
{
	if(Hero::hasKey(Hero::getInstance()))
	{
		AnimatedEntity::playAnimation(this, "Closing");
	}

	Base::unsetOverlapping(this);
}

bool KeyDoor::canEnter()
{
	return Hero::hasKey(Hero::getInstance());
}

uint32 KeyDoor::getHintType()
{
	if(Hero::hasKey(Hero::getInstance()))
	{
		return kEnterHint;
	}
	else
	{
		return kTypeKeyHint;
	}
}
