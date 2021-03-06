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
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void TestCogWheel::constructor(EntitySpec* EntitySpec, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(EntitySpec, internalId, name);
}

// class's destructor
void TestCogWheel::destructor()
{
	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kMessageCogWheelMove);

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// ready method
void TestCogWheel::ready(bool recursive)
{
	// call base
	Base::ready(this, recursive);

	// start moving
	MessageDispatcher::dispatchMessage(2000, Object::safeCast(this), Object::safeCast(this), kMessageCogWheelMove, NULL);

	// listen for the shake end event
	Object::addEventListener(Object::safeCast(EventManager::getInstance()), Object::safeCast(this), (EventListener)TestCogWheel::onShakeCompleted, kEventShakeCompleted);

	this->transformation.localRotation.z = 32;
	Entity::setLocalRotation(this, &this->transformation.localRotation);

//	Shape::show(VirtualList::front(this->shapes));
//	Shape::show(VirtualList::back(this->shapes));
}

// state's handle message
bool TestCogWheel::handleMessage(Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kMessageCogWheelMove:

			TestCogWheel::rotate(this);
			break;

		case kMessageCogWheelStop:

			TestCogWheel::stop(this);
			break;
	}

	return false;
}

// rotate cogwheel
void TestCogWheel::rotate()
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
	Entity::setLocalRotation(this, &this->transformation.localRotation);

	// send delayed message to self to trigger next movement
	MessageDispatcher::dispatchMessage(COG_WHEEL_ROTATION_DELAY, Object::safeCast(this), Object::safeCast(this), kMessageCogWheelMove, NULL);
}

// stop cogwheel
void TestCogWheel::stop()
{
	// stop listening for the shake end event
	Object::removeEventListener(EventManager::getInstance(), Object::safeCast(this), (EventListener)TestCogWheel::onShakeCompleted, kEventShakeCompleted);

	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kMessageCogWheelMove);

	// change sprite's mode
//	Sprite::setMode(Sprite::safeCast(VirtualList::front(this->sprites)), __WORLD_ON, __WORLD_BGMAP);
}

void TestCogWheel::onShakeCompleted(Object eventFirer __attribute__ ((unused)))
{
	// stop moving
	MessageDispatcher::dispatchMessage(1, Object::safeCast(this), Object::safeCast(this), kMessageCogWheelStop, NULL);
}


