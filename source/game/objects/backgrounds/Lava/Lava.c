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
#include "Lava.h"

#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define LAVA_MOVE_DELAY 300


//---------------------------------------------------------------------------------------------------------
// 											 CLASS'S MACROS
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Lava, InanimatedInGameEntity);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void Lava_moveUpwards(Lava this);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Lava, InanimatedInGameEntityDefinition* animatedInGameEntityDefinition, int ID)
__CLASS_NEW_END(Lava, animatedInGameEntityDefinition, ID);

// class's constructor
void Lava_constructor(Lava this, InanimatedInGameEntityDefinition* animatedInGameEntityDefinition, int ID)
{
	// construct base
	__CONSTRUCT_BASE(animatedInGameEntityDefinition, ID);

	// register a shape for collision detection
	this->shape = CollisionManager_registerShape(CollisionManager_getInstance(), __UPCAST(Entity, this), kCuboid);
}

// class's destructor
void Lava_destructor(Lava this)
{
    // discard pending moving messages
    MessageDispatcher_discardDelayedMessages(MessageDispatcher_getInstance(), kLavaMove);

	// delete the super object
	__DESTROY_BASE;
}

// initialize method
void Lava_initialize(Lava this)
{
	Entity_initialize(__UPCAST(Entity, this));
	
	// start moving
	MessageDispatcher_dispatchMessage(LAVA_MOVE_DELAY, __UPCAST(Object, this), __UPCAST(Object, this), kLavaMove, NULL);
}

// whether it is visible
bool Lava_isVisible(Lava this, int pad)
{
	ASSERT(this, "Lava::isVisible: null this");

    // always return true so the Lava is never unloaded from the stage when it is not visible on screen
	return true;
}

// state's on message
bool Lava_handleMessage(Lava this, Telegram telegram)
{
	switch (Telegram_getMessage(telegram))
    {
		case kLavaMove:

            Lava_moveUpwards(this);
			break;
	}
	
	return false;
}

// move lava up
void Lava_moveUpwards(Lava this)
{
    // get local position of lava and substract 1 from y value
    VBVec3D offset = Entity_getLocalPosition(__UPCAST(Entity, this));
    offset.y -= ITOFIX19_13(1);

    // update lava's position
    Entity_setLocalPosition(__UPCAST(Entity, this), offset);

    // send delayed message to itself to trigger next movement
    MessageDispatcher_dispatchMessage(LAVA_MOVE_DELAY, __UPCAST(Object, this), __UPCAST(Object, this), kLavaMove, NULL);
}

// resume after pause
void Lava_resume(Lava this)
{
	ASSERT(this, "Entity::resume: null this");

	Entity_resume(__UPCAST(Entity, this));

    // send delayed message to itself to trigger next movement
    MessageDispatcher_dispatchMessage(LAVA_MOVE_DELAY, __UPCAST(Object, this), __UPCAST(Object, this), kLavaMove, NULL);
}
