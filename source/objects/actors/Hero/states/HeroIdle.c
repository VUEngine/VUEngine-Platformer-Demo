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
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include "HeroIdle.h"
#include "HeroMoving.h"
#include "../Hero.h"

#include <PlatformerLevelState.h>
#include <MessageDispatcher.h>
#include <KeyPadManager.h>
#include <Printing.h>

#ifdef __DEBUG
//#include "../../levels/game/GameLevel.h"
#endif


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void HeroIdle_constructor(HeroIdle this);
void HeroIdle_destructor(HeroIdle this);
void HeroIdle_enter(HeroIdle this, void* owner);
void HeroIdle_exit(HeroIdle this, void* owner);
bool HeroIdle_processMessage(HeroIdle this, void* owner, Telegram telegram);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(HeroIdle, HeroState);
__SINGLETON(HeroIdle);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void __attribute__ ((noinline)) HeroIdle_constructor(HeroIdle this)
{
	// construct base
	__CONSTRUCT_BASE(HeroState);
}

// class's destructor
void HeroIdle_destructor(HeroIdle this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
void HeroIdle_enter(HeroIdle this __attribute__ ((unused)), void* owner)
{
    // show animation
    AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, owner), "Idle");

    // start sleeping after 6 seconds of inactivity
    MessageDispatcher_dispatchMessage(6000, __SAFE_CAST(Object, this), __SAFE_CAST(Object, owner), kHeroSleep, NULL);

#ifdef __DEBUG
	Printing_text(Printing_getInstance(), "HeroIdle::enter   ", 0, (__SCREEN_HEIGHT >> 3) - 2, NULL);
#endif
}

// state's exit
void HeroIdle_exit(HeroIdle this, void* owner __attribute__ ((unused)))
{
    // discard pending delayed messages
    MessageDispatcher_discardDelayedMessagesFromSender(MessageDispatcher_getInstance(), __SAFE_CAST(Object, this), kHeroSleep);
}

// state's handle message
bool HeroIdle_processMessage(HeroIdle this __attribute__ ((unused)), void* owner, Telegram telegram)
{
	switch(Telegram_getMessage(telegram))
    {
		case kCollision:

			return Hero_processCollision(__SAFE_CAST(Hero, owner), telegram);
			break;

		case kBodyStartedMoving:

			Hero_startedMovingOnAxis(__SAFE_CAST(Hero, owner), *(int*)Telegram_getExtraInfo(telegram));
			break;

		case kBodyStopped:

			return true;
			break;

		case kHeroSleep:

			AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, owner), "Sleep");
            return true;
			break;
	}

	return false;
}

void HeroIdle_onKeyPressed(HeroIdle this __attribute__ ((unused)), void* owner)
{
	u32 pressedKey = KeypadManager_getPressedKey(KeypadManager_getInstance());

    if(K_B & pressedKey)
    {
        Hero_enableBoost(__SAFE_CAST(Hero, owner));
    }

    // check if in front of door and possibly enter it
    if(K_LU & pressedKey)
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

    if((K_LL | K_LR | K_A) & pressedKey)
    {
        Acceleration acceleration =
        {
            K_LL & pressedKey ? ITOFIX19_13(-1) : K_LR & pressedKey ? __1I_FIX19_13 : 0,
            K_A & pressedKey ? ITOFIX19_13(-1) : 0,
            0,
        };

        if(__XAXIS & Actor_canMoveOverAxis(__SAFE_CAST(Actor, owner), &acceleration))
        {
            Hero_checkDirection(__SAFE_CAST(Hero, owner), pressedKey, "Idle");

            Hero_startedMovingOnAxis(__SAFE_CAST(Hero, owner), __XAXIS);

            if(K_A & pressedKey)
            {
                Hero_jump(__SAFE_CAST(Hero, owner), true);
            }
        }

        return;
    }


    if(K_LU & pressedKey)
    {
        Hero_checkDirection(__SAFE_CAST(Hero, owner), pressedKey, "Back");

        return;
    }

    if(K_LD & pressedKey)
    {
        Hero_checkDirection(__SAFE_CAST(Hero, owner), pressedKey, "Front");

        return;
    }
}

void HeroIdle_onKeyReleased(HeroIdle this __attribute__ ((unused)), void* owner)
{
	u32 releasedKey = KeypadManager_getReleasedKey(KeypadManager_getInstance());

    if(K_B & releasedKey)
    {
        Hero_disableBoost(__SAFE_CAST(Hero, owner));
    }
}

void HeroIdle_onKeyHold(HeroIdle this __attribute__ ((unused)), void* owner)
{
	u32 holdKey = KeypadManager_getHoldKey(KeypadManager_getInstance());

    if((K_LL | K_LR) & holdKey)
    {
        Acceleration acceleration =
        {
            K_LL & holdKey ? ITOFIX19_13(-1) : K_LR & holdKey ? __1I_FIX19_13 : 0,
            K_A & holdKey ? ITOFIX19_13(-1) : 0,
            0,
        };

        if(__XAXIS & Actor_canMoveOverAxis(__SAFE_CAST(Actor, owner), &acceleration))
        {
            Hero_checkDirection(__SAFE_CAST(Hero, owner), holdKey, "Idle");

            Hero_startedMovingOnAxis(__SAFE_CAST(Hero, owner), __XAXIS);
        }
    }
}
