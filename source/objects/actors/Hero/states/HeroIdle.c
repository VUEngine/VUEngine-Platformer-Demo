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
void HeroIdle_execute(HeroIdle this, void* owner);
void HeroIdle_exit(HeroIdle this, void* owner);
bool HeroIdle_processMessage(HeroIdle this, void* owner, Telegram telegram);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(HeroIdle, State);
__SINGLETON(HeroIdle);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void __attribute__ ((noinline)) HeroIdle_constructor(HeroIdle this)
{
	// construct base
	__CONSTRUCT_BASE(State);
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
	// make sure it's not moving anymore
	Actor_stopMovement(__SAFE_CAST(Actor, owner));

    // show animation
    AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, owner), "Idle");

#ifdef __DEBUG
	Printing_text(Printing_getInstance(), "HeroIdle::enter   ", 0, (__SCREEN_HEIGHT >> 3) - 2, NULL);
#endif
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

		case kKeyPressed:

			{
				u16 pressedKey = *((u16*)Telegram_getExtraInfo(telegram));

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
						    return true;
					    }
					}
				}

				if((K_LL | K_LR | K_A) & pressedKey)
                {
			 		Acceleration acceleration =
			 	    {
			 	    	K_LL & pressedKey? ITOFIX19_13(-1) : K_LR & pressedKey? ITOFIX19_13(1): 0,
			 	    	K_A & pressedKey? ITOFIX19_13(-1): 0,
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

                    return true;
				}


				if(K_LU & pressedKey)
                {
                    Hero_checkDirection(__SAFE_CAST(Hero, owner), pressedKey, "Back");

                    return true;
				}

				if(K_LD & pressedKey)
                {
                    Hero_checkDirection(__SAFE_CAST(Hero, owner), pressedKey, "Front");

                    return true;
				}
			}
			break;

		case kKeyReleased:
			{
				u16 releasedKey = *((u16*)Telegram_getExtraInfo(telegram));

				if(K_B & releasedKey)
                {
					Hero_disableBoost(__SAFE_CAST(Hero, owner));
				}

			}
			break;

		case kKeyHold:

			{
				u16 holdKey = *((u16*)Telegram_getExtraInfo(telegram));

				if((K_LL | K_LR) & holdKey)
                {
			 		Acceleration acceleration =
			 	    {
			 	    	K_LL & holdKey ? ITOFIX19_13(-1) : K_LR & holdKey ? ITOFIX19_13(1): 0,
			 	    	K_A & holdKey ? ITOFIX19_13(-1): 0,
			 	    	0,
			 		};

			 		if(__XAXIS & Actor_canMoveOverAxis(__SAFE_CAST(Actor, owner), &acceleration))
			 		{
	                    Hero_checkDirection(__SAFE_CAST(Hero, owner), holdKey, "Idle");

	                    Hero_startedMovingOnAxis(__SAFE_CAST(Hero, owner), __XAXIS);

	                    return true;
			 		}
				}
			}
			break;
	}

	return false;
//	return Hero_processMessage(__SAFE_CAST(Hero, owner), telegram);
}
