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
#include <Container.h>
#include <Stage.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Box.h>
#include <Camera.h>
#include <PhysicalWorld.h>
#include <Lava.h>
#include <CustomCameraEffectManager.h>
#include "LavaTrigger.h"
#include <PlatformerLevelState.h>
#include <EventManager.h>
#include <GameEvents.h>
#include <SoundManager.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern const u16 CRUMBLE_SND[];


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void LavaTrigger::constructor(EntitySpec* inanimatedEntitySpec, s16 id, s16 internalId, const char* const name)
{
	// construct base
	Base::constructor(inanimatedEntitySpec, id, internalId, name);
}

// class's destructor
void LavaTrigger::destructor()
{
	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kLavaTriggerEnd);

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// state's handle message
bool LavaTrigger::handleMessage(Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kLavaTriggerStart:

			LavaTrigger::triggerEventStart(this);
			break;

		case kLavaTriggerEnd:

			LavaTrigger::triggerEventEnd(this);
			break;
	}

	return false;
}

void LavaTrigger::triggerEventStart()
{
	// set level mode to paused so that player can't move
	PlatformerLevelState platformerState = (PlatformerLevelState)Game::getCurrentState(Game::getInstance());
	PlatformerLevelState::setModeToPaused(platformerState);

	// initialize a dramatic screen shake effect
	Camera::startEffect(Camera::getInstance(), kShake, 2000);

	// play sound
	Vector3D position = {192, 112, 0};
	SoundManager::playFxSound(SoundManager::getInstance(), CRUMBLE_SND, position);

	// remind myself to stop the trigger event soon
	MessageDispatcher::dispatchMessage(3000, Object::safeCast(this), Object::safeCast(this), kLavaTriggerEnd, NULL);

	// deactivate shape so I won't get triggered again
	Entity::enableShapes(this, false);
}

void LavaTrigger::triggerEventEnd()
{
	// get lava entity from stage and start its movement
	Lava lava = (Lava)Container::getChildByName(Container::safeCast(Game::getStage(Game::getInstance())), "Lava", true);
	Lava::startMoving(lava);

	// release player
	PlatformerLevelState platformerState = (PlatformerLevelState)Game::getCurrentState(Game::getInstance());
	PlatformerLevelState::setModeToPlaying(platformerState);

	// tell anyone interested about
	Object::fireEvent(EventManager::getInstance(), kEventShakeCompleted);

	// remove me from stage so I don't waste resources
	Container::deleteMyself(this);
}
