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
#include "Lava.h"

#include <PlatformerLevelState.h>


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
__CLASS_NEW_DEFINITION(Lava, InanimatedInGameEntityDefinition* inanimatedInGameEntityDefinition, int id, const char* const name)
__CLASS_NEW_END(Lava, inanimatedInGameEntityDefinition, id, name);

// class's constructor
void Lava_constructor(Lava this, InanimatedInGameEntityDefinition* inanimatedInGameEntityDefinition, int id, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(inanimatedInGameEntityDefinition, id, name);
	
	if(this->shape)
	{
		Shape_setCheckForCollisions(__SAFE_CAST(Shape, this->shape), false);
	}
}

// class's destructor
void Lava_destructor(Lava this)
{
    // discard pending delayed messages
    MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kLavaMove);

	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// start moving
void Lava_startMoving(Lava this)
{
	ASSERT(this, "Lava::startMoving: null this");

	// start moving
	MessageDispatcher_dispatchMessage(LAVA_MOVE_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kLavaMove, NULL);
	
	// must make sure that the shape is updated
	if(this->shape)
	{
		CollisionManager_shapeStartedMoving(Game_getCollisionManager(Game_getInstance()), this->shape);
	}
}

// whether it is visible
bool Lava_isVisible(Lava this, int pad, bool recursive)
{
	ASSERT(this, "Lava::isVisible: null this");

    // always return true so the Lava is never unloaded from the stage when it is not visible on screen
	return true;
}

// state's handle message
bool Lava_handleMessage(Lava this, Telegram telegram)
{
	switch(Telegram_getMessage(telegram))
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
    // get local position of lava and subtract 1 from y value
    VBVec3D offset = *Container_getLocalPosition(__SAFE_CAST(Container, this));
    offset.y -= ITOFIX19_13(1);

    // update lava's position
   __VIRTUAL_CALL(void, Container, setLocalPosition, __SAFE_CAST(Container, this), &offset);

    // send delayed message to self to trigger next movement
    MessageDispatcher_dispatchMessage(LAVA_MOVE_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kLavaMove, NULL);
}

// does it move?
bool Lava_moves(Lava this)
{
	ASSERT(this, "Lava::moves: null this");

	return true;
}