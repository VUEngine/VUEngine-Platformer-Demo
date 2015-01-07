/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev
 * jorgech3@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include "HeroIdle.h"
#include "HeroMoving.h"
#include "../Hero.h"

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
bool HeroIdle_handleMessage(HeroIdle this, void* owner, Telegram telegram);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(HeroIdle);
__SINGLETON(HeroIdle);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void HeroIdle_constructor(HeroIdle this)
{
	// construct base
	__CONSTRUCT_BASE(State);
}

// class's destructor
void HeroIdle_destructor(HeroIdle this)
{
	// destroy base
//	__SINGLETON_DESTROY(State);
}

// state's enter
void HeroIdle_enter(HeroIdle this, void* owner)
{
	// make sure it's not moving anymore
	Actor_stopMovement((Actor)owner);
	
	// reset timer for blinking
	Hero_resetActionTime((Hero)owner);

    // show animation
    AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)owner, "Idle");
	
	AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)owner, "Idle");

	Hero_resetActionTime((Hero)owner);

	Hero_setGap((Hero)owner);
	
#ifdef __DEBUG
	Printing_text(Printing_getInstance(), "HeroIdle::enter   ", 0, (__SCREEN_HEIGHT >> 3) - 2, NULL);
#endif
}

// state's execute
void HeroIdle_execute(HeroIdle this, void* owner)
{
	if (!Hero_isOverlappingDoor((Hero)owner)) {
		Hero_resetCurrentlyOverlappingDoor((Hero)owner);
	}
}

// state's exit
void HeroIdle_exit(HeroIdle this, void* owner)
{
}

// state's on message
bool HeroIdle_handleMessage(HeroIdle this, void* owner, Telegram telegram)
{
	switch (Telegram_getMessage(telegram))
    {
		case kCollision:

			return false;
			// process the collision
//			return Hero_processCollision((Hero)owner, telegram);
			break;

		case kBodyStartedMoving:

			Hero_startedMovingOnAxis((Hero)owner, *(int*)Telegram_getExtraInfo(telegram));
			break;

		case kKeyPressed:

			{
				u16 pressedKey = *((u16*)Telegram_getExtraInfo(telegram));

				// check if in front of door and possibly enter it
				if (K_LU & pressedKey)
				{
					if (Hero_isOverlappingDoor(Hero_getInstance())) {
						Hero_enterDoor(Hero_getInstance());
					}
				}
			}

		case kKeyHold:

			{
				u16 pressedKey = *((u16*)Telegram_getExtraInfo(telegram));

				if ((K_LL | K_LR | K_A) & pressedKey)
                {
                    Hero_checkDirection((Hero)owner, pressedKey, "Idle");

                    Hero_startedMovingOnAxis((Hero)owner, __XAXIS);

                    if (K_A & pressedKey )
                    {
                        Hero_jump((Hero)owner, true, true);
                    }

                    return true;
                    break;
				}

				if ((K_LU | K_LD) & pressedKey)
                {
                    Hero_checkDirection((Hero)owner, pressedKey, "Idle");

                    Hero_startedMovingOnAxis((Hero)owner, __ZAXIS);

                    if (K_A & pressedKey )
                    {
                        Hero_jump((Hero)owner, true, true);
                    }

                    return true;
                    break;
				}
			}
			break;
	}
	return false;
}