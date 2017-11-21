/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2017 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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

#include "HeroMoving.h"
#include "HeroIdle.h"
#include "../Hero.h"

#include <PlatformerLevelState.h>
#include <MessageDispatcher.h>
#include <KeypadManager.h>
#include <debugUtilities.h>


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void HeroMoving_constructor(HeroMoving this);
void HeroMoving_destructor(HeroMoving this);
void HeroMoving_enter(HeroMoving this, void* owner);
void HeroMoving_execute(HeroMoving this, void* owner);
bool HeroMoving_processMessage(HeroMoving this, void* owner, Telegram telegram);


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(HeroMoving, HeroState);
__SINGLETON(HeroMoving);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void __attribute__ ((noinline)) HeroMoving_constructor(HeroMoving this)
{
	// construct base
	__CONSTRUCT_BASE(HeroState);

	this->bouncing = false;
}

// class's destructor
void HeroMoving_destructor(HeroMoving this)
{
	// discard pending delayed messages
	MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kDisallowJumpOnBouncing);

	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
void HeroMoving_enter(HeroMoving this __attribute__ ((unused)), void* owner)
{
	u32 holdKey = KeypadManager_getHoldKey(KeypadManager_getInstance());

	if(K_B & holdKey)
	{
		Hero_enableBoost(__SAFE_CAST(Hero, owner));
	}

#ifdef __DEBUG
	Printing_text(Printing_getInstance(), "HeroMoving", 38, (__SCREEN_HEIGHT_IN_CHARS) - 1, NULL);
#endif

	KeypadManager_registerInput(KeypadManager_getInstance(), __KEY_PRESSED | __KEY_RELEASED);
}

void HeroMoving_execute(HeroMoving this __attribute__ ((unused)), void* owner)
{
	// check direction
	Hero_addForce(__SAFE_CAST(Hero, owner), __X_AXIS, false);
}

// state's handle message
bool HeroMoving_processMessage(HeroMoving this __attribute__ ((unused)), void* owner, Telegram telegram)
{
	switch(Telegram_getMessage(telegram))
	{
		case kBodyStopped:

			Hero_stopMovingOnAxis(__SAFE_CAST(Hero, owner), *(int*)Telegram_getExtraInfo(telegram));
			return true;
			break;

		case kBodyStartedMoving:

			// start movement
			Hero_startedMovingOnAxis(__SAFE_CAST(Hero, owner), *(int*)Telegram_getExtraInfo(telegram));
			break;

		case kBodyBounced:

			//Hero_bounce(__SAFE_CAST(Hero, owner), true);
			return false;
			break;
	}

	return false;
}

void HeroMoving_onKeyPressed(HeroMoving this __attribute__ ((unused)), void* owner, const UserInput* userInput)
{
	if(K_B & userInput->pressedKey)
	{
		Hero_enableBoost(__SAFE_CAST(Hero, owner));
	}

	if(K_A & userInput->pressedKey)
	{
		Hero_jump(__SAFE_CAST(Hero, owner), !this->bouncing);
	}

	// check direction
	if((K_LL | K_LR ) & (userInput->pressedKey | userInput->holdKey))
	{
		Acceleration acceleration =
		{
			K_LL & userInput->pressedKey? __I_TO_FIX19_13(-1) : K_LR & userInput->pressedKey? __1I_FIX19_13: 0,
			0,
			0,
		};

		if(__X_AXIS & Actor_canMoveTowards(__SAFE_CAST(Actor, owner), acceleration))
		{
			Hero_addForce(__SAFE_CAST(Hero, owner), __X_AXIS, true);
		}

		Hero_checkDirection(__SAFE_CAST(Hero, owner), userInput->pressedKey, "Walk");
	}
	else if(K_LU & userInput->pressedKey)
	{
		Hero_lookBack(__SAFE_CAST(Hero, owner));

		if(NULL != Hero_getOverlappedDoor(__SAFE_CAST(Hero, owner)))
		{
			if(__VIRTUAL_CALL(Door, canEnter, Hero_getOverlappedDoor(__SAFE_CAST(Hero, owner))))
			{
				Hero_enterDoor(__SAFE_CAST(Hero, owner));
				return;
			}
		}
	}
}

void HeroMoving_onKeyReleased(HeroMoving this __attribute__ ((unused)), void* owner, const UserInput* userInput)
{
	if(K_B & userInput->releasedKey)
	{
		Hero_disableBoost(__SAFE_CAST(Hero, owner));
	}

	if((K_LL | K_LR) & userInput->releasedKey)
	{
		Hero_stopAddingForce(__SAFE_CAST(Hero, owner));
/*		Velocity velocity = Actor_getVelocity(__SAFE_CAST(Actor, owner));

		if(__ABS(velocity.x))
		{
		}
		else if(!__ABS(velocity.y))
		{
			StateMachine_swapState(Actor_getStateMachine(__SAFE_CAST(Actor, owner)), __SAFE_CAST(State, HeroIdle_getInstance()));
		}
		*/
	}
}

