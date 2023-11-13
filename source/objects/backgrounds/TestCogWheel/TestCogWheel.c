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
void TestCogWheel::constructor(EntitySpec* EntitySpec, int16 internalId, const char* const name)
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
	MessageDispatcher::dispatchMessage(2000, ListenerObject::safeCast(this), ListenerObject::safeCast(this), kMessageCogWheelMove, NULL);

	// listen for the shake end event
	ListenerObject::addEventListener(ListenerObject::safeCast(EventManager::getInstance()), ListenerObject::safeCast(this), (EventListener)TestCogWheel::onShakeCompleted, kEventShakeCompleted);

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

			TestCogWheel::applyRotation(this);
			break;

		case kMessageCogWheelStop:

			TestCogWheel::stop(this);
			break;
	}

	return false;
}

// rotate cogwheel
void TestCogWheel::applyRotation()
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
	ListenerObject::removeEventListener(EventManager::getInstance(), ListenerObject::safeCast(this), (EventListener)TestCogWheel::onShakeCompleted, kEventShakeCompleted);

	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), ListenerObject::safeCast(this), kMessageCogWheelMove);

	// change sprite's mode
//	Sprite::setMode(Sprite::safeCast(VirtualList::front(this->sprites)), __WORLD_ON, __WORLD_BGMAP);
}

void TestCogWheel::onShakeCompleted(Object eventFirer __attribute__ ((unused)))
{
	// stop moving
	MessageDispatcher::dispatchMessage(1, ListenerObject::safeCast(this), ListenerObject::safeCast(this), kMessageCogWheelStop, NULL);
}


