/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <VUEngine.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Box.h>
#include <PhysicalWorld.h>
#include "CogWheel.h"
#include <PlatformerLevelState.h>
#include <EventManager.h>
#include <GameEvents.h>
#include <Telegram.h>
#include <debugUtilities.h>


#undef COG_WHEEL_ROTATION_DELAY
#define COG_WHEEL_ROTATION_DELAY 50


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void CogWheel::constructor(EntitySpec* entitySpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor(entitySpec, internalId, name);
}

// class's destructor
void CogWheel::destructor()
{
	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), ListenerObject::safeCast(this), kMessageCogWheelMove);

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
	MessageDispatcher::dispatchMessage(COG_WHEEL_ROTATION_DELAY, ListenerObject::safeCast(this), ListenerObject::safeCast(this), kMessageCogWheelMove, NULL);

	// listen for the shake end event
	ListenerObject::addEventListener(ListenerObject::safeCast(EventManager::getInstance()), ListenerObject::safeCast(this), (EventListener)CogWheel::onShakeCompleted, kEventShakeCompleted);

	this->transformation.localScale = (Scale){__F_TO_FIX7_9(0.60f), __F_TO_FIX7_9(0.60f), __F_TO_FIX7_9(0.60f)};

	Entity::setLocalRotation(this, &this->transformation.localRotation);
}

// state's handle message
bool CogWheel::handleMessage(Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kMessageCogWheelMove:

			CogWheel::applyRotation(this);
			break;

		case kMessageCogWheelStop:

			CogWheel::stop(this);
			break;
	}

	return false;
}

// rotate cogwheel
void CogWheel::applyRotation()
{
	Rotation localRotation = this->transformation.localRotation;
	localRotation.z += 1;

	Entity::setLocalRotation(this, &localRotation);

	// send delayed message to self to trigger next movement
	MessageDispatcher::dispatchMessage(COG_WHEEL_ROTATION_DELAY, ListenerObject::safeCast(this), ListenerObject::safeCast(this), kMessageCogWheelMove, NULL);
}

// stop cogwheel
void CogWheel::stop()
{
	// stop listening for the shake end event
	ListenerObject::removeEventListener(EventManager::getInstance(), ListenerObject::safeCast(this), (EventListener)CogWheel::onShakeCompleted, kEventShakeCompleted);

	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), ListenerObject::safeCast(this), kMessageCogWheelMove);

	// change sprite's mode
//	Sprite::setMode(Sprite::safeCast(VirtualList::front(this->sprites)), __WORLD_ON, __WORLD_BGMAP);
}

void CogWheel::onShakeCompleted(Object eventFirer __attribute__ ((unused)))
{
	// stop moving
	MessageDispatcher::dispatchMessage(1, ListenerObject::safeCast(this), ListenerObject::safeCast(this), kMessageCogWheelStop, NULL);
}


