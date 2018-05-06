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


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(CogWheel, Entity);


#undef COG_WHEEL_ROTATION_DELAY
#define COG_WHEEL_ROTATION_DELAY 50


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void CogWheel_onShakeCompleted(CogWheel this, Object eventFirer);
static void CogWheel_rotate(CogWheel this);
static void CogWheel_stop(CogWheel this);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(CogWheel, EntityDefinition* EntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(CogWheel, EntityDefinition, id, internalId, name);

// class's constructor
void CogWheel_constructor(CogWheel this, EntityDefinition* EntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base_constructor(this, EntityDefinition, id, internalId, name);
}

// class's destructor
void CogWheel_destructor(CogWheel this)
{
	// discard pending delayed messages
	MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kCogWheelMove);

	// delete the super object
	// must always be called at the end of the destructor
	Base_destructor();
}

// ready method
void CogWheel_ready(CogWheel this, bool recursive)
{
	ASSERT(this, "CogWheel::ready: null this");

	// call base
	Base_ready(this, recursive);

	// start moving
	MessageDispatcher_dispatchMessage(COG_WHEEL_ROTATION_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCogWheelMove, NULL);

	// listen for the shake end event
	Object_addEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)CogWheel_onShakeCompleted, kEventShakeCompleted);

	this->transformation.localScale = (Scale){__F_TO_FIX7_9(0.60f), __F_TO_FIX7_9(0.60f), __F_TO_FIX7_9(0.60f)};

	Entity_setLocalRotation(__SAFE_CAST(Entity, this), &this->transformation.localRotation);}

// state's handle message
bool CogWheel_handleMessage(CogWheel this, Telegram telegram)
{
	switch(Telegram_getMessage(telegram))
	{
		case kCogWheelMove:

			CogWheel_rotate(this);
			break;

		case kCogWheelStop:

			CogWheel_stop(this);
			break;
	}

	return false;
}

// rotate cogwheel
static void CogWheel_rotate(CogWheel this)
{
	this->transformation.localRotation.z += 1;

	Entity_setLocalRotation(__SAFE_CAST(Entity, this), &this->transformation.localRotation);

	// send delayed message to self to trigger next movement
	MessageDispatcher_dispatchMessage(COG_WHEEL_ROTATION_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCogWheelMove, NULL);
}

// stop cogwheel
static void CogWheel_stop(CogWheel this)
{
	// stop listening for the shake end event
	Object_removeEventListener(__SAFE_CAST(Object, EventManager_getInstance()), __SAFE_CAST(Object, this), (EventListener)CogWheel_onShakeCompleted, kEventShakeCompleted);

	// discard pending delayed messages
	MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kCogWheelMove);

	// change sprite's mode
//	Sprite_setMode(__SAFE_CAST(Sprite, VirtualList_front(this->sprites)), __WORLD_ON, __WORLD_BGMAP);
}

static void CogWheel_onShakeCompleted(CogWheel this, Object eventFirer __attribute__ ((unused)))
{
	// stop moving
	MessageDispatcher_dispatchMessage(1, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kCogWheelStop, NULL);
}


