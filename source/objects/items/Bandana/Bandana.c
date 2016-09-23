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

#include <GameEvents.h>
#include <Game.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Cuboid.h>
#include <PhysicalWorld.h>
#include <SoundManager.h>

#include <objects.h>
#include "Bandana.h"

#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 											 CLASS' MACROS
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Bandana, AnimatedInGameEntity);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void Bandana_removeFromStage(Bandana this);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Bandana, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name)
__CLASS_NEW_END(Bandana, animatedInGameEntityDefinition, id, name);

// class's constructor
void Bandana_constructor(Bandana this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name)
{
	ASSERT(this, "Bandana::constructor: null this");

	// construct base
	__CONSTRUCT_BASE(AnimatedInGameEntity, animatedInGameEntityDefinition, id, name);

	// register a shape for collision detection
	this->shape = CollisionManager_registerShape(Game_getCollisionManager(Game_getInstance()), __SAFE_CAST(SpatialObject, this), kCuboid);
}

// class's destructor
void Bandana_destructor(Bandana this)
{
	ASSERT(this, "Bandana::destructor: null this");

	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// state's handle message
bool Bandana_handleMessage(Bandana this, Telegram telegram)
{
	ASSERT(this, "Bandana::handleMessage: null this");

    extern const u16 COLLECT_SND[];

	switch(Telegram_getMessage(telegram))
    {
		case kItemTaken:

            SoundManager_playFxSound(SoundManager_getInstance(), COLLECT_SND, this->transform.globalPosition);
            Shape_setActive(this->shape, false);
            MessageDispatcher_dispatchMessage(__GAME_FRAME_DURATION, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kTakeBandana, NULL);
            break;

        case kTakeBandana:

			Bandana_removeFromStage(this);
			break;
	}

	return false;
}

void Bandana_removeFromStage(Bandana this)
{
	ASSERT(this, "Bandana::removeFromStage: null this");

	// play collect sound
	Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), kEventPowerUp);

	Container_deleteMyself(__SAFE_CAST(Container, this));
}
