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
#include "CogWheel.h"
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
void CogWheel::constructor(EntitySpec* EntitySpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor(EntitySpec, internalId, name);
}

// class's destructor
void CogWheel::destructor()
{
	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kMessageCogWheelMove);

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// ready method
void CogWheel::ready(bool recursive)
{
	// call base
	Base::ready(this, recursive);

	// start moving
	MessageDispatcher::dispatchMessage(COG_WHEEL_ROTATION_DELAY, Object::safeCast(this), Object::safeCast(this), kMessageCogWheelMove, NULL);

	// listen for the shake end event
	Object::addEventListener(Object::safeCast(EventManager::getInstance()), Object::safeCast(this), (EventListener)CogWheel::onShakeCompleted, kEventShakeCompleted);

	this->transformation.localScale = (Scale){__F_TO_FIX7_9(0.60f), __F_TO_FIX7_9(0.60f), __F_TO_FIX7_9(0.60f)};

	Entity::setLocalRotation(this, &this->transformation.localRotation);
}

// state's handle message
bool CogWheel::handleMessage(Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kMessageCogWheelMove:

			CogWheel::rotate(this);
			break;

		case kMessageCogWheelStop:

			CogWheel::stop(this);
			break;
	}

	return false;
}

// rotate cogwheel
void CogWheel::rotate()
{
	Rotation localRotation = this->transformation.localRotation;
	localRotation.z += 1;

	Entity::setLocalRotation(this, &localRotation);

	// send delayed message to self to trigger next movement
	MessageDispatcher::dispatchMessage(COG_WHEEL_ROTATION_DELAY, Object::safeCast(this), Object::safeCast(this), kMessageCogWheelMove, NULL);
}

// stop cogwheel
void CogWheel::stop()
{
	// stop listening for the shake end event
	Object::removeEventListener(EventManager::getInstance(), Object::safeCast(this), (EventListener)CogWheel::onShakeCompleted, kEventShakeCompleted);

	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kMessageCogWheelMove);

	// change sprite's mode
//	Sprite::setMode(Sprite::safeCast(VirtualList::front(this->sprites)), __WORLD_ON, __WORLD_BGMAP);
}

void CogWheel::onShakeCompleted(Object eventFirer __attribute__ ((unused)))
{
	// stop moving
	MessageDispatcher::dispatchMessage(1, Object::safeCast(this), Object::safeCast(this), kMessageCogWheelStop, NULL);
}


