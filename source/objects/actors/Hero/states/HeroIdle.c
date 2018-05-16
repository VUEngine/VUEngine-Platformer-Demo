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

#include "HeroIdle.h"
#include "HeroMoving.h"
#include "../Hero.h"

#include <PlatformerLevelState.h>
#include <MessageDispatcher.h>
#include <KeypadManager.h>
#include <debugUtilities.h>

#ifdef __DEBUG
//#include "../../levels/game/GameLevel.h"
#endif


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void HeroIdle::constructor(HeroIdle this);
void HeroIdle::destructor(HeroIdle this);
void HeroIdle::enter(HeroIdle this, void* owner);
void HeroIdle::exit(HeroIdle this, void* owner);
bool HeroIdle::processMessage(HeroIdle this, void* owner, Telegram telegram);

//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void __attribute__ ((noinline)) HeroIdle::constructor(HeroIdle this)
{
	// construct base
	Base::constructor();
}

// class's destructor
void HeroIdle::destructor(HeroIdle this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
void HeroIdle::enter(HeroIdle this __attribute__ ((unused)), void* owner)
{
	// show animation
	AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, owner), "Idle");

	// start sleeping after 6 seconds of inactivity
	MessageDispatcher::dispatchMessage(6000, __SAFE_CAST(Object, this), __SAFE_CAST(Object, owner), kHeroSleep, NULL);

#ifdef __DEBUG
	Printing::text(Printing::getInstance(), "HeroIdle   ", 38, (__SCREEN_HEIGHT_IN_CHARS) - 1, NULL);
#endif

	KeypadManager::registerInput(KeypadManager::getInstance(), __KEY_PRESSED | __KEY_RELEASED | __KEY_HOLD);
}

// state's exit
void HeroIdle::exit(HeroIdle this, void* owner __attribute__ ((unused)))
{
	// discard pending delayed messages
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), __SAFE_CAST(Object, this), kHeroSleep);
}

// state's handle message
bool HeroIdle::processMessage(HeroIdle this __attribute__ ((unused)), void* owner, Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kBodyStartedMoving:

			Hero::startedMovingOnAxis(__SAFE_CAST(Hero, owner), *(u16*)Telegram::getExtraInfo(telegram));
			break;

		case kBodyStopped:

			return true;
			break;

		case kHeroSleep:

			AnimatedEntity::playAnimation(__SAFE_CAST(AnimatedEntity, owner), "Sleep");
			return true;
			break;
	}

	return false;
}

void HeroIdle::onKeyPressed(HeroIdle this __attribute__ ((unused)), void* owner, const UserInput* userInput)
{
	if(K_B & userInput->pressedKey)
	{
		Hero::enableBoost(__SAFE_CAST(Hero, owner));
	}

	// check if in front of door and possibly enter it
	if(K_LU & userInput->pressedKey)
	{
		Hero::lookBack(__SAFE_CAST(Hero, owner));

		if(NULL != Hero::getOverlappedDoor(__SAFE_CAST(Hero, owner)))
		{
			if(Door::canEnter(Hero::getOverlappedDoor(__SAFE_CAST(Hero, owner))))
			{
				Hero::enterDoor(__SAFE_CAST(Hero, owner));
				return;
			}
		}
	}

	if((K_LL | K_LR | K_A) & userInput->pressedKey)
	{
		Acceleration acceleration =
		{
			K_LL & userInput->pressedKey ? __I_TO_FIX10_6(-1) : K_LR & userInput->pressedKey ? __1I_FIX10_6 : 0,
			K_A & userInput->pressedKey ? __I_TO_FIX10_6(-1) : 0,
			0,
		};

		if(K_A & userInput->pressedKey)
		{
			Hero::jump(__SAFE_CAST(Hero, owner), true);
		}

		if((K_LL | K_LR) & (userInput->pressedKey | userInput->holdKey))
		{
			if(Actor::canMoveTowards(__SAFE_CAST(Actor, owner), acceleration))
			{
				Hero::checkDirection(__SAFE_CAST(Hero, owner), userInput->pressedKey, "Idle");

				Hero::startedMovingOnAxis(__SAFE_CAST(Hero, owner), __X_AXIS);
			}
		}

		return;
	}


	if(K_LU & userInput->pressedKey)
	{
		Hero::checkDirection(__SAFE_CAST(Hero, owner), userInput->pressedKey, "Back");

		return;
	}

	if(K_LD & userInput->pressedKey)
	{
		Hero::checkDirection(__SAFE_CAST(Hero, owner), userInput->pressedKey, "Front");

		return;
	}
}

void HeroIdle::onKeyReleased(HeroIdle this __attribute__ ((unused)), void* owner, const UserInput* userInput)
{
	if(K_B & userInput->releasedKey)
	{
		Hero::disableBoost(__SAFE_CAST(Hero, owner));
	}
}

void HeroIdle::onKeyHold(HeroIdle this __attribute__ ((unused)), void* owner, const UserInput* userInput)
{
    if((K_LL | K_LR) & userInput->holdKey)
    {
        Vector3D direction =
        {
            K_LL & userInput->holdKey ? __I_TO_FIX10_6(-1) : K_LR & userInput->holdKey ? __I_TO_FIX10_6(1) : 0,
            K_A & userInput->holdKey ? __I_TO_FIX10_6(-1) : 0,
            0,
        };

		if(Actor::canMoveTowards(__SAFE_CAST(Actor, owner), direction))
        {
            Hero::checkDirection(__SAFE_CAST(Hero, owner), userInput->holdKey, "Idle");

            Hero::startedMovingOnAxis(__SAFE_CAST(Hero, owner), __X_AXIS);
        }
    }
}
