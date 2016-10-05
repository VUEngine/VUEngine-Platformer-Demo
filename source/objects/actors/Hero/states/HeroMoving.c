/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev <jorgech3@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation; either version 3 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program. If not,
 * see <http://www.gnu.org/licenses/>.
 */


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include "HeroMoving.h"
#include "HeroIdle.h"
#include "../Hero.h"

#include <PlatformerLevelState.h>
#include <MessageDispatcher.h>
#include <KeyPadManager.h>
#include <Printing.h>


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void HeroMoving_constructor(HeroMoving this);
void HeroMoving_destructor(HeroMoving this);
void HeroMoving_enter(HeroMoving this, void* owner);
void HeroMoving_exit(HeroMoving this, void* owner);
bool HeroMoving_processMessage(HeroMoving this, void* owner, Telegram telegram);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(HeroMoving, HeroState);
__SINGLETON(HeroMoving);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
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
	Printing_text(Printing_getInstance(), "HeroMoving::enter   ", 0, (__SCREEN_HEIGHT >> 3) - 2, NULL);
#endif
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
			{
				int axis = *(int*)Telegram_getExtraInfo(telegram);
				// start movement
				Hero_startedMovingOnAxis(__SAFE_CAST(Hero, owner), axis);
			}
			break;

		case kBodyChangedDirection:

			Hero_startedMovingOnAxis(__SAFE_CAST(Hero, owner), *(int*)Telegram_getExtraInfo(telegram));
			break;

		case kBodyBounced:

			this->bouncing = true;
			MessageDispatcher_dispatchMessage(100, __SAFE_CAST(Object, this), __SAFE_CAST(Object, owner), kDisallowJumpOnBouncing, NULL);
			return true;
			break;

		case kDisallowJumpOnBouncing:

			this->bouncing = false;
			break;

		case kCollision:

			return Hero_processCollision(__SAFE_CAST(Hero, owner), telegram);
			break;

	}

	return false;
}

void HeroMoving_onKeyPressed(HeroMoving this __attribute__ ((unused)), void* owner)
{
	u32 pressedKey = KeypadManager_getPressedKey(KeypadManager_getInstance());

    if(K_B & pressedKey)
    {
        Hero_enableBoost(__SAFE_CAST(Hero, owner));
    }

    // check direction
    if((K_LL | K_LR ) & pressedKey)
    {
        Acceleration acceleration =
        {
            K_LL & pressedKey? ITOFIX19_13(-1) : K_LR & pressedKey? __1I_FIX19_13: 0,
            0,
            0,
        };

        if(__XAXIS & Actor_canMoveOverAxis(__SAFE_CAST(Actor, owner), &acceleration))
        {
            Hero_addForce(__SAFE_CAST(Hero, owner), __XAXIS);
        }

        Hero_checkDirection(__SAFE_CAST(Hero, owner), pressedKey, "Walk");
    }
    else if(K_LU & pressedKey)
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

    if(K_A & pressedKey)
    {
        Hero_jump(__SAFE_CAST(Hero, owner), !this->bouncing);
    }
}

void HeroMoving_onKeyReleased(HeroMoving this __attribute__ ((unused)), void* owner)
{
	u32 releasedKey = KeypadManager_getReleasedKey(KeypadManager_getInstance());
    u32 holdKey = KeypadManager_getHoldKey(KeypadManager_getInstance());

    if(K_B & releasedKey)
    {
        Hero_disableBoost(__SAFE_CAST(Hero, owner));
    }

    if(((K_LL | K_LR) & releasedKey) && ((K_LL | K_LR) & holdKey))
    {
        if(!((K_LL & holdKey) && ( K_LR & holdKey)))
        {
            Hero_checkDirection(__SAFE_CAST(Hero, owner), holdKey, "Walk");
            return;
        }
    }

    if(((K_LL | K_LR) & releasedKey) && !((K_LL | K_LR) & holdKey))
    {
        Velocity velocity = Actor_getVelocity(__SAFE_CAST(Actor, owner));

        if(__ABS(velocity.x))
        {
            Hero_stopAddingForce(__SAFE_CAST(Hero, owner));
        }
        else if(!__ABS(velocity.y))
        {
            StateMachine_swapState(Actor_getStateMachine(__SAFE_CAST(Actor, owner)), __SAFE_CAST(State, HeroIdle_getInstance()));
        }
    }
}

void HeroMoving_onKeyHold(HeroMoving this __attribute__ ((unused)), void* owner)
{
	u32 holdKey = KeypadManager_getHoldKey(KeypadManager_getInstance());

    // check direction
    if((K_LL | K_LR ) & holdKey)
    {
        Hero_addForce(__SAFE_CAST(Hero, owner), __XAXIS);
    }
}
