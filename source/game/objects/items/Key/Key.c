/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev
 * jorgech3@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Game.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Screen.h>
#include <Cuboid.h>
#include <PhysicalWorld.h>

#include <objects.h>
#include "Key.h"
#include "KeyManager.h"

#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 											 CLASS'S MACROS
//---------------------------------------------------------------------------------------------------------


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
__CLASS_NEW_DEFINITION(Key, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int ID)
__CLASS_NEW_END(Key, animatedInGameEntityDefinition, ID);

// class's constructor
void Key_constructor(Key this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int ID)
{
	// construct base
	__CONSTRUCT_BASE(animatedInGameEntityDefinition, ID);

	// register a shape for collision detection
	this->shape = CollisionManager_registerShape(CollisionManager_getInstance(), __UPCAST(Entity, this), kCuboid);
}

// class's destructor
void Key_destructor(Key this)
{
	KeyManager_removeKey(KeyManager_getInstance(), this);

	// delete the super object
	__DESTROY_BASE;
}

// initialize method
void Key_initialize(Key this)
{
	AnimatedInGameEntity_initialize(__UPCAST(AnimatedInGameEntity, this));

	KeyManager_registerKey(KeyManager_getInstance(), this);
}

// state's on message
bool Key_handleMessage(Key this, Telegram telegram)
{
	switch (Telegram_getMessage(telegram))
    {
		case kTakeKey:

			Key_removeFromStage(this);
			break;
	}
	
	return false;
}

void Key_removeFromStage(Key this)
{
	Stage_removeEntity(Game_getStage(Game_getInstance()), __UPCAST(Entity, this), true);
}