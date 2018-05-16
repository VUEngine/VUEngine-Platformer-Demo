/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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
#include <Box.h>
#include <PhysicalWorld.h>
#include "Lava.h"
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------




//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void Lava::moveUpwards(Lava this);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other



// class's constructor
void Lava::constructor(Lava this, EntityDefinition* inanimatedEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(inanimatedEntityDefinition, id, internalId, name);
}

// class's destructor
void Lava::destructor(Lava this)
{
	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), __SAFE_CAST(Object, this), kLavaMove);

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// start moving
void Lava::startMoving(Lava this)
{
	ASSERT(this, "Lava::startMoving: null this");

	// start moving
	MessageDispatcher::dispatchMessage(LAVA_MOVE_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kLavaMove, NULL);

	// must make sure that the shape is updated
	Entity::informShapesThatStartedMoving(__SAFE_CAST(Entity, this));
}

// whether it is visible
bool Lava::isVisible(Lava this __attribute__ ((unused)), int pad __attribute__ ((unused)), bool recursive __attribute__ ((unused)))
{
	ASSERT(this, "Lava::isVisible: null this");

	// always return true so the Lava is never unloaded from the stage when it is not visible on screen
	return true;
}

// state's handle message
bool Lava::handleMessage(Lava this, Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kLavaMove:

			Lava::moveUpwards(this);
			break;
	}

	return false;
}

// move lava up
void Lava::moveUpwards(Lava this)
{
	// get local position of lava and subtract 1 from y value
	Vector3D offset = *Container::getLocalPosition(__SAFE_CAST(Container, this));
	offset.y -= __PIXELS_TO_METERS(1);

	// update lava's position
	Container::setLocalPosition(__SAFE_CAST(Container, this), &offset);

	// send delayed message to self to trigger next movement
	MessageDispatcher::dispatchMessage(LAVA_MOVE_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kLavaMove, NULL);
}
