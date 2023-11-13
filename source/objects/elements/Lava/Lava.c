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
#include "Lava.h"
#include <PlatformerLevelState.h>

//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void Lava::constructor(EntitySpec* inanimatedEntitySpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor(inanimatedEntitySpec, internalId, name);

	this->dontStreamOut = true;
}

// class's destructor
void Lava::destructor()
{
	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kMessageLavaMove);

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// start moving
void Lava::startMoving()
{
	// start moving
	MessageDispatcher::dispatchMessage(LAVA_MOVE_DELAY, ListenerObject::safeCast(this), ListenerObject::safeCast(this), kMessageLavaMove, NULL);

	// must make sure that the shape is updated
	Entity::activeCollisionChecks(this, true);
}

// state's handle message
bool Lava::handleMessage(Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kMessageLavaMove:

			Lava::moveUpwards(this);
			break;
	}

	return false;
}

// move lava up
void Lava::moveUpwards()
{
	// get local position of lava and subtract 1 from y value
	Vector3D offset = *Container::getLocalPosition(this);
	offset.y -= __PIXELS_TO_METERS(1);

	// update lava's position
	Container::setLocalPosition(this, &offset);

	// send delayed message to self to trigger next movement
	MessageDispatcher::dispatchMessage(LAVA_MOVE_DELAY, ListenerObject::safeCast(this), ListenerObject::safeCast(this), kMessageLavaMove, NULL);
}
