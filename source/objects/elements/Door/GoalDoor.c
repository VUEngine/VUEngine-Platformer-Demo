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

#include <GameEvents.h>
#include <Game.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Box.h>
#include <PhysicalWorld.h>
#include <Camera.h>
#include <EventManager.h>
#include <GoalDoor.h>
#include <PlatformerLevelState.h>
#include <LevelDoneScreenState.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void GoalDoor::constructor(AnimatedEntitySpec* animatedEntitySpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor(animatedEntitySpec, internalId, name);
}

// class's destructor
void GoalDoor::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// ready
void GoalDoor::ready(bool recursive __attribute__ ((unused)))
{
	// call base
	Base::ready(this, recursive);

	AnimatedEntity::playAnimation(this, "Goal");
}

bool GoalDoor::hasDestination()
{
	return true;
}

// state's handle message
bool GoalDoor::handleMessage(Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kMessageHeroEnterDoor:
		{
			// disable user input
			Game::disableKeypad(Game::getInstance());

			// fade out screen
			Brightness brightness = (Brightness){0, 0, 0};
			Camera::startEffect(Camera::getInstance(),
				kFadeTo, // effect type
				0, // initial delay (in ms)
				&brightness, // target brightness
				__FADE_DELAY, // delay between fading steps (in ms)
				(void (*)(Object, Object))GoalDoor::onFadeOutComplete, // callback function
				Object::safeCast(this) // callback scope
			);

			return true;
			break;
		}
	}

	return Base::handleMessage(this, telegram);
}

bool GoalDoor::canEnter()
{
	return true;
}

// handle event
void GoalDoor::onFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	// announce level completion
	Object::fireEvent(EventManager::getInstance(), kEventLevelCompleted);

	// switch to next screen
	Game::changeState(Game::getInstance(), GameState::safeCast(LevelDoneScreenState::getInstance()));
}
