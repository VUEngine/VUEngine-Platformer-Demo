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


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void LavaTrigger::constructor(EntitySpec* inanimatedEntitySpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor(inanimatedEntitySpec, internalId, name);
}

// class's destructor
void LavaTrigger::destructor()
{
	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kMessageLavaTriggerEnd);

	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// state's handle message
bool LavaTrigger::handleMessage(Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kMessageLavaTriggerStart:

			LavaTrigger::triggerEventStart(this);
			break;

		case kMessageLavaTriggerEnd:

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
	extern Sound CRUMBLE_SND;
	SoundManager::playSound(SoundManager::getInstance(), &CRUMBLE_SND, kPlayAll, (const Vector3D*)&this->transformation.globalPosition, kSoundWrapperPlaybackNormal, NULL, NULL);

	// remind myself to stop the trigger event soon
	MessageDispatcher::dispatchMessage(3000, Object::safeCast(this), Object::safeCast(this), kMessageLavaTriggerEnd, NULL);

	// deactivate shape so I won't get triggered again
	Entity::allowCollisions(this, false);
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
