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
#include "KeyDoor.h"
#include <PlatformerLevelState.h>
#include <LevelDoneScreenState.h>
#include <ProgressManager.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void KeyDoor::constructor(AnimatedEntityDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(animatedEntityDefinition, id, internalId, name);
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
	if(ProgressManager::heroHasKey(ProgressManager::getInstance()))
	{
		AnimatedEntity::playAnimation(this, "Opening");
	}

	Base::setOverlapping(this);
}

void KeyDoor::unsetOverlapping()
{
	if(ProgressManager::heroHasKey(ProgressManager::getInstance()))
	{
		AnimatedEntity::playAnimation(this, "Closing");
	}

	Base::unsetOverlapping(this);
}

bool KeyDoor::canEnter()
{
	return ProgressManager::heroHasKey(ProgressManager::getInstance());
}

u32 KeyDoor::getHintType()
{
	if(ProgressManager::heroHasKey(ProgressManager::getInstance()))
	{
		return kEnterHint;
	}
	else
	{
		return kKeyHint;
	}
}
