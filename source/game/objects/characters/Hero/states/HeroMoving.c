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

#include "HeroMoving.h"
#include "HeroIdle.h"
#include "../Hero.h"

#include <PlatformerLevelState.h>
#include <MessageDispatcher.h>


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void HeroMoving_constructor(HeroMoving this);
void HeroMoving_destructor(HeroMoving this);
void HeroMoving_enter(HeroMoving this, void* owner);
void HeroMoving_execute(HeroMoving this, void* owner);
void HeroMoving_exit(HeroMoving this, void* owner);
bool HeroMoving_handleMessage(HeroMoving this, void* owner, Telegram telegram);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(HeroMoving);
__SINGLETON(HeroMoving);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void HeroMoving_constructor(HeroMoving this)
{
	// construct base
	__CONSTRUCT_BASE(State);
	
	this->mustCheckDirection = false;
	this->bouncing = false;
}

// class's destructor
void HeroMoving_destructor(HeroMoving this)
{
	// destroy base
	__SINGLETON_DESTROY(State);
}

// state's enter
void HeroMoving_enter(HeroMoving this, void* owner)
{
	// start moving (animations, etc)
	// correct gap accorging to animation
	Hero_setGap((Hero)owner);

	this->mustCheckDirection = false;
#ifdef __DEBUG
	Printing_text(Printing_getInstance(), "HeroMoving::enter   ", 0, (__SCREEN_HEIGHT >> 3) - 2, NULL);
#endif
}

// state's execute
void HeroMoving_execute(HeroMoving this, void* owner)
{
}

// state's exit
void HeroMoving_exit(HeroMoving this, void* owner)
{
	Hero_disableBoost((Hero)owner);
}

// state's on message
bool HeroMoving_handleMessage(HeroMoving this, void* owner, Telegram telegram)
{
	switch (Telegram_getMessage(telegram))
    {
		case kKeyPressed:

			{
				u16 pressedKey = *((u16*)Telegram_getExtraInfo(telegram));

				// check direction
				if ((K_LL | K_LR ) & pressedKey)
                {
					Hero_checkDirection((Hero)owner, pressedKey, "Walk");					
				}
				else if ((K_LU | K_LD ) & pressedKey)
                {
					Hero_checkDirection((Hero)owner, pressedKey, "Walk");					
				}

				// check if jump
				if (K_A & pressedKey)
                {
					Hero_jump((Hero)owner, false, !this->bouncing);			
				}

				// check if in front of door and possibly enter it
				
				// TODO: should only be able to enter the door when idle right?
				/*
				if (K_LU & pressedKey)
                {
					if (Hero_isOverlappingDoor((Hero)owner)) 
					{
						Hero_enterDoor((Hero)owner);
					}
				}
				*/
			}

			return true;
			break;
			
		case kKeyUp:
			{
				u16 releasedKey = *((u16*)Telegram_getExtraInfo(telegram));

				if ((K_LL | K_LR) & releasedKey)
                {
					Velocity velocity = Body_getVelocity(Actor_getBody((Actor)owner));
					
					if (0 < abs(velocity.x))
                    {
						Hero_stopMovement((Hero)owner);		
					}
					else
                    {
						StateMachine_swapState(Actor_getStateMachine((Actor) owner), (State)HeroIdle_getInstance());					
					}
				}

				if ((K_LU | K_LD) & releasedKey)
                {
					Velocity velocity = Body_getVelocity(Actor_getBody((Actor)owner));
					
					if (0 < abs(velocity.z))
                    {
						Hero_stopMovement((Hero)owner);		
					}
					else
                    {
						StateMachine_swapState(Actor_getStateMachine((Actor) owner), (State)HeroIdle_getInstance());					
					}
				}

				if (K_B & releasedKey)
                {
					Hero_disableBoost((Hero)owner);
				}
			}
			break;
	
		case kKeyHold:
			{
				u16 holdKey = *((u16*)Telegram_getExtraInfo(telegram));

				if (K_B & holdKey)
                {
					Hero_enableBoost((Hero)owner);
				}

				// check direction
				if ((K_LL | K_LR ) & holdKey)
                {
					Hero_addForce((Hero)owner, this->mustCheckDirection, __XAXIS);					
					this->mustCheckDirection = false;
				}
				else if ((K_LU | K_LD ) & holdKey)
                {
					Hero_addForce((Hero)owner, this->mustCheckDirection, __ZAXIS);					
					this->mustCheckDirection = false;
				}
			}
			break;

		case kBodyStoped:
			
			Hero_stopMovingOnAxis((Hero)owner, *(int*)Telegram_getExtraInfo(telegram));
			break;

		case kBodyStartedMoving:

			{
				int axis = *(int*)Telegram_getExtraInfo(telegram);
				// start movement
				Hero_startedMovingOnAxis((Hero)owner, axis);
			}
			break;

		case kBodyChangedDirection:

			Hero_startedMovingOnAxis((Hero)owner, *(int*)Telegram_getExtraInfo(telegram));
			break;

		case kBodyBounced:
			
			this->mustCheckDirection = true;
			this->bouncing = true;
			MessageDispatcher_dispatchMessage(100, (Object)this, (Object)owner, kDisallowJumpOnBouncing, NULL);
			return true;
			break;
			
		case kDisallowJumpOnBouncing:
			
			this->bouncing = false;
			break;
			
		case kCollision:

			return Hero_processCollision((Hero)owner, telegram);
			break;

        case kCheckForOverlappingDoor:

            if (!Hero_isOverlappingDoor((Hero)owner)) 
            {
                Hero_resetCurrentlyOverlappingDoor((Hero)owner);
            }
            else
            {
                // remind hero to check again in 100 milliseconds
                MessageDispatcher_dispatchMessage(100, (Object)owner, (Object)owner, kCheckForOverlappingDoor, NULL);
            }
            break;
	}
	return false;
}