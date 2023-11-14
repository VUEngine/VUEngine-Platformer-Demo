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

#include "HeroIdle.h"
#include "HeroMoving.h"
#include "../Hero.h"

#include <PlatformerLevelState.h>
#include <MessageDispatcher.h>
#include <KeypadManager.h>
#include <Telegram.h>
#include <debugUtilities.h>

#ifdef __DEBUG
//#include "../../levels/game/GameLevel.h"
#endif


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void HeroIdle::constructor()
{
	// construct base
	Base::constructor();
}

// class's destructor
void HeroIdle::destructor()
{
	// destroy base
	Base::destructor();
}

// state's enter
void HeroIdle::enter(void* owner)
{
	// show animation
	AnimatedEntity::playAnimation(owner, "Idle");

	// start sleeping after 6 seconds of inactivity
	MessageDispatcher::dispatchMessage(HERO_SLEEP_DELAY, ListenerObject::safeCast(this), ListenerObject::safeCast(owner), kMessageHeroSleep, NULL);

#ifdef __DEBUG
	Printing::text(Printing::getInstance(), "HeroIdle   ", 38, (__SCREEN_HEIGHT_IN_CHARS) - 1, "Platformer");
#endif

	KeypadManager::registerInput(KeypadManager::getInstance(), __KEY_PRESSED | __KEY_RELEASED | __KEY_HOLD);
}

// state's exit
void HeroIdle::exit(void* owner __attribute__ ((unused)))
{
	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), ListenerObject::safeCast(this), kMessageHeroSleep);
}

// state's handle message
bool HeroIdle::processMessage(void* owner, Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kMessageBodyStartedMoving:

			Hero::startedMovingOnAxis(owner, *(uint16*)Telegram::getExtraInfo(telegram));
			break;

		case kMessageBodyStopped:

			return true;
			break;

		case kMessageHeroSleep:

			AnimatedEntity::playAnimation(owner, "Sleep");
			return true;
			break;
	}

	return false;
}

void HeroIdle::onKeyPressed(void* owner, const UserInput* userInput)
{
	if(K_B & userInput->pressedKey)
	{
		Hero::enableBoost(owner);
	}

	// check if in front of door and possibly enter it
	if(K_LU & userInput->pressedKey)
	{
		Hero::lookBack(owner);

		if(NULL != Hero::getOverlappedDoor(owner))
		{
			if(Door::canEnter(Hero::getOverlappedDoor(owner)))
			{
				Hero::enterDoor(owner);
				return;
			}
		}
	}

	if((K_LL | K_LR | K_A) & userInput->pressedKey)
	{
		Vector3D acceleration =
		{
			K_LL & userInput->pressedKey ? __I_TO_FIX10_6(-1) : K_LR & userInput->pressedKey ? __1I_FIX10_6 : 0,
			K_A & userInput->pressedKey ? __I_TO_FIX10_6(-1) : 0,
			0,
		};

		if(K_A & userInput->pressedKey)
		{
			Hero::jump(owner, true);
		}

		if((K_LL | K_LR) & (userInput->pressedKey | userInput->holdKey))
		{
			if(Actor::canMoveTowards(owner, acceleration))
			{
				Hero::checkDirection(owner, userInput->pressedKey, "Idle");

				Hero::startedMovingOnAxis(owner, __X_AXIS);
			}
		}

		return;
	}


	if(K_LU & userInput->pressedKey)
	{
		Hero::checkDirection(owner, userInput->pressedKey, "Back");

		return;
	}

	if(K_LD & userInput->pressedKey)
	{
		Hero::checkDirection(owner, userInput->pressedKey, "Front");

		return;
	}
}

void HeroIdle::onKeyReleased(void* owner, const UserInput* userInput)
{
	if(K_B & userInput->releasedKey)
	{
		Hero::disableBoost(owner);
	}
}

void HeroIdle::onKeyHold(void* owner, const UserInput* userInput)
{
	if((K_LL | K_LR) & userInput->holdKey)
	{
		Vector3D direction =
		{
			K_LL & userInput->holdKey ? __I_TO_FIX10_6(-1) : K_LR & userInput->holdKey ? __I_TO_FIX10_6(1) : 0,
			K_A & userInput->holdKey ? __I_TO_FIX10_6(-1) : 0,
			0,
		};

		if(Actor::canMoveTowards(owner, direction))
		{
			Hero::checkDirection(owner, userInput->holdKey, "Idle");

			Hero::startedMovingOnAxis(owner, __X_AXIS);
		}
	}
}
