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
#include "KeyDoor.h"
#include <PlatformerLevelState.h>
#include <LevelDoneScreenState.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(KeyDoor, Door);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
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
