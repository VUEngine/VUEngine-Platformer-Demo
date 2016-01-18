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

__CLASS_DEFINITION(HeroMoving, State);
__SINGLETON(HeroMoving);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void HeroMoving_constructor(HeroMoving this)
{
	// construct base
	__CONSTRUCT_BASE();
	
	this->mustCheckDirection = false;
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
void HeroMoving_enter(HeroMoving this, void* owner)
{
	this->mustCheckDirection = false;

#ifndef __DEBUG
	Printing_text(Printing_getInstance(), "HeroMoving::enter   ", 0, (__SCREEN_HEIGHT >> 3) - 2, NULL);
#endif
}

// state's execute
void HeroMoving_execute(HeroMoving this, void* owner)
{
	Printing_text(Printing_getInstance(), __GET_CLASS_NAME(Container_getParent(owner)), 10, 12, NULL);
//	Body_printPhysics(Actor_getBody(owner), 1, 7);
}

// state's exit
void HeroMoving_exit(HeroMoving this, void* owner)
{
}

// state's handle message
bool HeroMoving_handleMessage(HeroMoving this, void* owner, Telegram telegram)
{
	switch(Telegram_getMessage(telegram))
    {
		case kKeyPressed:
			{
				u16 pressedKey = *((u16*)Telegram_getExtraInfo(telegram));

				if(K_B & pressedKey)
                {
					Hero_enableBoost((Hero)owner);
				}

				// check direction
				if((K_LL | K_LR ) & pressedKey)
				{
			 		Acceleration acceleration =
			 	    {
			 	    	K_LL & pressedKey? ITOFIX19_13(-1) : K_LR & pressedKey? ITOFIX19_13(1): 0,
			 	    	0,
			 	    	0,
			 		};

			 		if(__XAXIS & Actor_canMoveOverAxis(__SAFE_CAST(Actor, owner), &acceleration))
			 		{
						Hero_addForce((Hero)owner, this->mustCheckDirection, __XAXIS);					
						this->mustCheckDirection = false;
			 		}

			 		Hero_checkDirection((Hero)owner, pressedKey, "Walk");	
				}
				else if(K_LU & pressedKey)
				{
					if(Hero_isOverlappingDoor((Hero)owner))
					{
						Hero_enterDoor((Hero)owner);
						return true;
					}
				}

				if(K_A & pressedKey)
                {
					Hero_jump((Hero)owner, false, !this->bouncing);			
				}
			}

			return true;
			break;
			
		case kKeyReleased:
			{
				u16 releasedKey = *((u16*)Telegram_getExtraInfo(telegram));
				u16 holdKey = KeypadManager_getHoldKey(KeypadManager_getInstance());

				if(K_B & releasedKey)
                {
					Hero_disableBoost((Hero)owner);
				}

				if(((K_LL | K_LR) & releasedKey) && ((K_LL | K_LR) & holdKey))
				{
					if(!((K_LL & holdKey) && ( K_LR & holdKey)))
					{
						Hero_checkDirection((Hero)owner, holdKey, "Walk");	
						return true;
					}
				}
				
				if(((K_LL | K_LR) & releasedKey) && !((K_LL | K_LR) & holdKey))
                {
					Velocity velocity = Body_getVelocity(Actor_getBody(__SAFE_CAST(Actor, owner)));

					if(abs(velocity.x))
                    {
						Hero_stopAddingForce((Hero)owner);		
					}
					else if(!abs(velocity.y))
                    {
						StateMachine_swapState(Actor_getStateMachine(__SAFE_CAST(Actor, owner)), __SAFE_CAST(State, HeroIdle_getInstance()));
					}
				}
			}
			break;
			
		case kKeyHold:
			{
				u16 holdKey = *((u16*)Telegram_getExtraInfo(telegram));

				// check direction
				if((K_LL | K_LR ) & holdKey)
                {
//					Hero_checkDirection((Hero)owner, holdKey, "Walk");	

//					Velocity velocity = Body_getVelocity(Actor_getBody(__SAFE_CAST(Actor, owner)));

		//			if(__XAXIS & Body_isMoving(Actor_getBody(__SAFE_CAST(Actor, owner))))
                    {
						Hero_addForce((Hero)owner, this->mustCheckDirection, __XAXIS);					
                    }
					
					this->mustCheckDirection = false;
				}
				else if((K_LU | K_LD ) & holdKey)
                {
					//Hero_addForce((Hero)owner, this->mustCheckDirection, __ZAXIS);					
					//this->mustCheckDirection = false;
				}
			}
			break;

		case kBodyStopped:
			
			Hero_stopMovingOnAxis((Hero)owner, *(int*)Telegram_getExtraInfo(telegram));
			return true;
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
			MessageDispatcher_dispatchMessage(100, __SAFE_CAST(Object, this), __SAFE_CAST(Object, owner), kDisallowJumpOnBouncing, NULL);
			return true;
			break;
			
		case kDisallowJumpOnBouncing:
			
			this->bouncing = false;
			break;
			
		case kCollision:

			return Hero_processCollision((Hero)owner, telegram);
			break;

	}
	return false;
}