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
#include "KeyDoor.h"
#include <PlatformerLevelState.h>
#include <LevelDoneScreenState.h>
#include <ProgressManager.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(KeyDoor, Door);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(KeyDoor, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(KeyDoor, animatedInGameEntityDefinition, id, internalId, name);

// class's constructor
void KeyDoor_constructor(KeyDoor this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(Door, animatedInGameEntityDefinition, id, internalId, name);
}

// class's destructor
void KeyDoor_destructor(KeyDoor this)
{
	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// ready
void KeyDoor_ready(KeyDoor this, u32 recursive __attribute__ ((unused)))
{
	ASSERT(this, "KeyDoor::ready: null this");

	// call base
	AnimatedInGameEntity_ready(__SAFE_CAST(AnimatedInGameEntity, this), recursive);

	AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Key");
}

bool KeyDoor_hasDestination(KeyDoor this __attribute__ ((unused)))
{
	return true;
}

void KeyDoor_setOverlapping(KeyDoor this)
{
	if(ProgressManager_heroHasKey(ProgressManager_getInstance())) {
		AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Opening");
	}

	Door_setOverlapping(__SAFE_CAST(Door, this));
}

void KeyDoor_unsetOverlapping(KeyDoor this)
{

	if(ProgressManager_heroHasKey(ProgressManager_getInstance())) {
		AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Closing");
	}

	Door_unsetOverlapping(__SAFE_CAST(Door, this));
}

bool KeyDoor_canEnter(KeyDoor this __attribute__ ((unused)))
{
	return ProgressManager_heroHasKey(ProgressManager_getInstance());
}

u32 KeyDoor_getHintType(KeyDoor this __attribute__ ((unused)))
{
	if(ProgressManager_heroHasKey(ProgressManager_getInstance()))
	{
		return kEnterHint;
	}
	else
	{
		return kKeyHint;
	}
}
