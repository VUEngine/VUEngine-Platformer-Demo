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
#include "Key.h"

#include <PlatformerLevelState.h>
#include <PostProcessingEffects.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Key, AnimatedInGameEntity);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void Key_removeFromStage(Key this);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Key, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name)
__CLASS_NEW_END(Key, animatedInGameEntityDefinition, id, name);

// class's constructor
void Key_constructor(Key this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name)
{
	ASSERT(this, "Key::constructor: null this");

	// construct base
	__CONSTRUCT_BASE(AnimatedInGameEntity, animatedInGameEntityDefinition, id, name);

	// register a shape for collision detection
	this->shape = CollisionManager_registerShape(Game_getCollisionManager(Game_getInstance()), __SAFE_CAST(SpatialObject, this), kCuboid);
}

// class's destructor
void Key_destructor(Key this)
{
	ASSERT(this, "Key::destructor: null this");

    // remove post processing effect
    Game_removePostProcessingEffect(Game_getInstance(), PostProcessingEffects_haloEmitter, __SAFE_CAST(SpatialObject, this));

	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

void Key_ready(Key this, u32 recursive)
{
	ASSERT(this, "Key::ready: null this");

    Entity_ready(__SAFE_CAST(Entity, this), recursive);

    // add post processing effect to make key emit "halos"
    Game_addPostProcessingEffect(Game_getInstance(), PostProcessingEffects_haloEmitter, __SAFE_CAST(SpatialObject, this));
}

// state's handle message
bool Key_handleMessage(Key this, Telegram telegram)
{
	ASSERT(this, "Key::handleMessage: null this");

	switch(Telegram_getMessage(telegram))
    {
		case kItemTaken:

			Key_removeFromStage(this);
			break;
	}

	return false;
}

void Key_removeFromStage(Key this)
{
	ASSERT(this, "Key::removeFromStage: null this");

	Container_deleteMyself(__SAFE_CAST(Container, this));
}
