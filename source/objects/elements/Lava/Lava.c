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
#include "Lava.h"
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Lava, InanimatedInGameEntity);


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void Lava_moveUpwards(Lava this);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Lava, InanimatedInGameEntityDefinition* inanimatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(Lava, inanimatedInGameEntityDefinition, id, internalId, name);

// class's constructor
void Lava_constructor(Lava this, InanimatedInGameEntityDefinition* inanimatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(InanimatedInGameEntity, inanimatedInGameEntityDefinition, id, internalId, name);
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
bool Lava_isVisible(Lava this __attribute__ ((unused)), int pad __attribute__ ((unused)), bool recursive __attribute__ ((unused)))
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
	offset.y -= __1I_FIX19_13;

	// update lava's position
	__VIRTUAL_CALL(Container, setLocalPosition, __SAFE_CAST(Container, this), &offset);

	// send delayed message to self to trigger next movement
	MessageDispatcher_dispatchMessage(LAVA_MOVE_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kLavaMove, NULL);
}

// does it move?
bool Lava_moves(Lava this __attribute__ ((unused)))
{
	ASSERT(this, "Lava::moves: null this");

	return true;
}
