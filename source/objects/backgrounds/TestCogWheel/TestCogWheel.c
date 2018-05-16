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
#include "TestCogWheel.h"
#include <PlatformerLevelState.h>
#include <EventManager.h>
#include <GameEvents.h>
#include <debugUtilities.h>


#undef COG_WHEEL_ROTATION_DELAY
#define COG_WHEEL_ROTATION_DELAY 50


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void TestCogWheel::onShakeCompleted(TestCogWheel this, Object eventFirer);
static void TestCogWheel::rotate(TestCogWheel this);
static void TestCogWheel::stop(TestCogWheel this);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void TestCogWheel::constructor(TestCogWheel this, EntityDefinition* EntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(EntityDefinition, id, internalId, name);
}

// class's destructor
void TestCogWheel::destructor(TestCogWheel this)
{
	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), __SAFE_CAST(Object, this), kCogWheelMove);

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// ready method
void TestCogWheel::ready(TestCogWheel this, bool recursive)
{
	ASSERT(this, "TestCogWheel::ready: null this");

	// call base
	Base::ready(this, recursive);

	// start moving
	MessageDispatcher::dispatchMessage(2000, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCogWheelMove, NULL);

	// listen for the shake end event
	Object::addEventListener(__SAFE_CAST(Object, EventManager::getInstance()), __SAFE_CAST(Object, this), (EventListener)TestCogWheel::onShakeCompleted, kEventShakeCompleted);

	this->transformation.localRotation.z = 32;
	Entity::setLocalRotation(__SAFE_CAST(Entity, this), &this->transformation.localRotation);

//	Shape::show(VirtualList::front(this->shapes));
//	Shape::show(VirtualList::back(this->shapes));
}

// state's handle message
bool TestCogWheel::handleMessage(TestCogWheel this, Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kCogWheelMove:

			TestCogWheel::rotate(this);
			break;

		case kCogWheelStop:

			TestCogWheel::stop(this);
			break;
	}

	return false;
}

// rotate cogwheel
static void TestCogWheel::rotate(TestCogWheel this)
{
//	Shape::show(VirtualList::front(this->shapes));
//	Shape::show(VirtualList::back(this->shapes));

	static int increment = -2;

	this->transformation.localRotation.z += increment;
/*
	if(32 < this->transformation.localRotation.z)
	{
		increment *= -1;
	}
	if(-32 > this->transformation.localRotation.z)
	{
		increment *= -1;
	}
*/
	Entity::setLocalRotation(__SAFE_CAST(Entity, this), &this->transformation.localRotation);

	// send delayed message to self to trigger next movement
	MessageDispatcher::dispatchMessage(COG_WHEEL_ROTATION_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCogWheelMove, NULL);
}

// stop cogwheel
static void TestCogWheel::stop(TestCogWheel this)
{
	// stop listening for the shake end event
	Object::removeEventListener(__SAFE_CAST(Object, EventManager::getInstance()), __SAFE_CAST(Object, this), (EventListener)TestCogWheel::onShakeCompleted, kEventShakeCompleted);

	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), __SAFE_CAST(Object, this), kCogWheelMove);

	// change sprite's mode
//	Sprite::setMode(__SAFE_CAST(Sprite, VirtualList::front(this->sprites)), __WORLD_ON, __WORLD_BGMAP);
}

static void TestCogWheel::onShakeCompleted(TestCogWheel this, Object eventFirer __attribute__ ((unused)))
{
	// stop moving
	MessageDispatcher::dispatchMessage(1, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCogWheelStop, NULL);
}


