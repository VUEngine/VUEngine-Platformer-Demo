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



/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												INCLUDES
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

#include "HeroMoving.h"
#include "HeroIdle.h"
#include "Hero.h"

#include <GameLevel.h>
#include <MessageDispatcher.h>


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												PROTOTYPES
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */


// class's constructor
void HeroMoving_constructor(HeroMoving this);

// class's destructor
void HeroMoving_destructor(HeroMoving this);

// state's enter
void HeroMoving_enter(HeroMoving this, void* owner);

// state's execute
void HeroMoving_execute(HeroMoving this, void* owner);

// state's exit
void HeroMoving_exit(HeroMoving this, void* owner);

// state's on message
u16 HeroMoving_handleMessage(HeroMoving this, void* owner, Telegram telegram);


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 											CLASS'S DEFINITION
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

__CLASS_DEFINITION(HeroMoving);

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												CLASS'S METHODS
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
__SINGLETON(HeroMoving);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's constructor
void HeroMoving_constructor(HeroMoving this){

	// construct base
	__CONSTRUCT_BASE(State);
	
	this->mustCheckDirection = false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's destructor
void HeroMoving_destructor(HeroMoving this){

	// destroy base
	__SINGLETON_DESTROY(State);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's enter
void HeroMoving_enter(HeroMoving this, void* owner){
	
	// not in bridge
	//Hero_setBridge((Hero)owner, NULL);

	// start moving (animations, etc)
	// correct gap accorging to animation
	Hero_setGap((Hero)owner);

	this->mustCheckDirection = false;

#ifdef __DEBUG
	Printing_text("HeroMoving::enter   ", 0, (__SCREEN_HEIGHT >> 3) - 1);
#endif
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's execute
void HeroMoving_execute(HeroMoving this, void* owner){
	
	// update movement
	//Hero_move((Hero) owner);

	//Body_printPhysics(Actor_getBody((Actor)owner), 1, 3);

	Hero_checkIfDied((Hero)owner);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's exit 
void HeroMoving_exit(HeroMoving this, void* owner){
	
	Hero_disableBoost((Hero)owner);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's on message
u16 HeroMoving_handleMessage(HeroMoving this, void* owner, Telegram telegram){

	switch(Telegram_getMessage(telegram)){

		// if the botton of the screen has been reached
		case kFloorReached:
	
			//Hero_fallDead((Hero)owner);

			//Actor_stopMovement(owner, __YAXIS);
			break;
			
		case kKeyPressed:
			{
				u16 pressedKey = *((u16*)Telegram_getExtraInfo(telegram));

				// check direction
				if((K_LL | K_LR ) & pressedKey){
					
					Hero_checkDirection((Hero)owner, pressedKey, "Walk");					
				}

				// check if jump
				if(K_A & pressedKey){
					
					Hero_jump((Hero)owner, false);			
				}
			}		

			return true;
			break;
			
		case kKeyUp:
			{
				u16 releasedKey = *((u16*)Telegram_getExtraInfo(telegram));

				if((K_LL | K_LR) & releasedKey){
	
					Velocity velocity = Body_getVelocity(Actor_getBody((Actor)owner));
					
					if (0 < abs(velocity.x)){
						
						Hero_stopMoving((Hero)owner);		
					}
					else {
						
						StateMachine_swapState(Actor_getStateMachine((Actor) owner), (State)HeroIdle_getInstance());					
					}
				}
				
				if(K_B & releasedKey){
					
					Hero_disableBoost((Hero)owner);
				}
			}
			break;
	
		case kKeyHold:
			{
				u16 holdKey = *((u16*)Telegram_getExtraInfo(telegram));

				// check direction
				if((K_LL | K_LR ) & holdKey){
					
					Hero_keepMoving((Hero)owner, this->mustCheckDirection);					
					this->mustCheckDirection = false;
				}
				
				if(K_B & holdKey){
					
					Hero_enableBoost((Hero)owner);
				}
			}
			break;

		case kBodyStoped:

			Hero_stopMovingOnAxis((Hero)owner, *(int*)Telegram_getExtraInfo(telegram));
			break;

		case kBodyStartedMoving:

			// start movement
			Hero_startedMovingOnAxis((Hero)owner, *(int*)Telegram_getExtraInfo(telegram));
			break;

		case kBodyChangedDirection:
			
			Hero_startedMovingOnAxis((Hero)owner, *(int*)Telegram_getExtraInfo(telegram));
			break;

		case kBodyBounced:
			
			this->mustCheckDirection = true;
			return true;
			break;

		case kCollision:
		{
			VirtualList collidingObjects = (VirtualList)Telegram_getExtraInfo(telegram);
			ASSERT(collidingObjects, "HeroMoving::handleMessage: null collidingObjects");

			VirtualNode node = NULL;
			
			for(node = VirtualList_begin(collidingObjects); node; node = VirtualNode_getNext(node)){
			
				InGameEntity inGameEntity = (InGameEntity)VirtualNode_getData(node);
				
				switch(InGameEntity_getInGameType(inGameEntity)){
										
					case kCoin:

						Hero_collectCoin((Hero)owner);
						MessageDispatcher_dispatchMessage(0, (Object)this, (Object)inGameEntity, kTakeCoin, NULL);
						return true;
						break;
				}
							
			}
//			return Hero_processCollision((Hero)owner, telegram);	
			return false;
		}
			break;

			

			
	}
	return false;
	
}

