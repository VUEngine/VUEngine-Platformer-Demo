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
#include "GoalDoor.h"
#include <PlatformerLevelState.h>
#include <LevelDoneScreenState.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(GoalDoor, Door);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(GoalDoor, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name)
__CLASS_NEW_END(GoalDoor, animatedInGameEntityDefinition, id, name);

// class's constructor
void GoalDoor_constructor(GoalDoor this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(Door, animatedInGameEntityDefinition, id, name);
}

// class's destructor
void GoalDoor_destructor(GoalDoor this)
{
	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// ready
void GoalDoor_ready(Door this)
{
	ASSERT(this, "GoalDoor::ready: null this");

    AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "Goal");
}

bool GoalDoor_hasDestination(Door this __attribute__ ((unused)))
{
	return true;
}

// state's handle message
bool GoalDoor_handleMessage(GoalDoor this, Telegram telegram)
{
	switch(Telegram_getMessage(telegram))
    {
		case kHeroEnterDoor:

			Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, LevelDoneScreenState_getInstance()));
			return true;
			break;
	}

	return Door_handleMessage(__SAFE_CAST(Door, this), telegram);
}

bool GoalDoor_canEnter(GoalDoor this __attribute__ ((unused)))
{
	return true;
}
