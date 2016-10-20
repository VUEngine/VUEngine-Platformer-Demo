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
#include <EventManager.h>
#include <ProgressManager.h>

#include <objects.h>
#include "Collectable.h"

#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Collectable, AnimatedInGameEntity);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void Collectable_collect(Collectable this);
void Collectable_removeFromStage(Collectable this);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Collectable, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(Collectable, animatedInGameEntityDefinition, id, internalId, name);

// class's constructor
void Collectable_constructor(Collectable this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	ASSERT(this, "Collectable::constructor: null this");

	// construct base
	__CONSTRUCT_BASE(AnimatedInGameEntity, animatedInGameEntityDefinition, id, internalId, name);

	// register a shape for collision detection
	this->shape = CollisionManager_registerShape(Game_getCollisionManager(Game_getInstance()), __SAFE_CAST(SpatialObject, this), kCuboid);
}

// class's destructor
void Collectable_destructor(Collectable this)
{
	ASSERT(this, "Collectable::destructor: null this");

	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// state's handle message
bool Collectable_handleMessage(Collectable this, Telegram telegram)
{
	ASSERT(this, "Collectable::handleMessage: null this");

    extern const u16 COLLECT_SND[];

	switch(Telegram_getMessage(telegram))
    {
		case kItemTaken:

            // play collect sound
            SoundManager_playFxSound(SoundManager_getInstance(), COLLECT_SND, this->transform.globalPosition);

			// set shape to inactive so no other hits with this item can occur
            Shape_setActive(this->shape, false);

            // additional action
			__VIRTUAL_CALL(Collectable, collect, this);

            // send message to remove item in next game frame
            MessageDispatcher_dispatchMessage(__GAME_FRAME_DURATION, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kRemoveFromStage, NULL);
            break;

        case kRemoveFromStage:

			Collectable_removeFromStage(this);
			break;
	}

	return false;
}

void Collectable_collect(Collectable this __attribute__ ((unused)))
{
	ASSERT(this, "Collectable::collect: null this");
}

void Collectable_removeFromStage(Collectable this)
{
	ASSERT(this, "Collectable::removeFromStage: null this");

	Container_deleteMyself(__SAFE_CAST(Container, this));
}
