/* VbJaEngine: bitmap graphics engine for the Nintendo Virtual Boy 
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

#include "MarioMoving.h"
#include "MarioIdle.h"
#include "Mario.h"

#include <GameLevel.h>


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												PROTOTYPES
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */


// class's constructor
void MarioMoving_constructor(MarioMoving this);

// class's destructor
void MarioMoving_destructor(MarioMoving this);

// state's enter
void MarioMoving_enter(MarioMoving this, void* owner);

// state's execute
void MarioMoving_execute(MarioMoving this, void* owner);

// state's exit
void MarioMoving_exit(MarioMoving this, void* owner);

// state's on message
u16 MarioMoving_handleMessage(MarioMoving this, void* owner, Telegram telegram);


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 											CLASS'S DEFINITION
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

__CLASS_DEFINITION(MarioMoving);

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												CLASS'S METHODS
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
__SINGLETON(MarioMoving);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's constructor
void MarioMoving_constructor(MarioMoving this){

	// construct base
	__CONSTRUCT_BASE(State);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's destructor
void MarioMoving_destructor(MarioMoving this){

	// destroy base
	__SINGLETON_DESTROY(State);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's enter
void MarioMoving_enter(MarioMoving this, void* owner){
	
	// not in bridge
	//Mario_setBridge((Mario)owner, NULL);

	// start moving (animations, etc)
	// correct gap accorging to animation
	Mario_setGap((Mario)owner);

	// start moving (animations, etc)
	Mario_startMoving((Mario)owner);
	
	Printing_text("Moving   ", 0, 27);
	Printing_text("       ", 1, 10);

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's execute
void MarioMoving_execute(MarioMoving this, void* owner){
	
	// update movement
	//Mario_move((Mario) owner);

	//Body_printPhysics(Actor_getBody((Actor)owner), 1, 3);

	Mario_checkIfDied((Mario)owner);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's exit 
void MarioMoving_exit(MarioMoving this, void* owner){
	
	Mario_disableBoost((Mario)owner);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's on message
u16 MarioMoving_handleMessage(MarioMoving this, void* owner, Telegram telegram){

	switch(Telegram_getMessage(telegram)){

		// if the botton of the screen has been reached
		case kFloorReached:
	
			//Mario_fallDead((Mario)owner);

			//Actor_stopMovement(owner, __YAXIS);
			break;
			
		case kKeyPressed:
			{
				u16 pressedKey = *((u16*)Telegram_getExtraInfo(telegram));

				// check direction
				if((K_LL | K_LR ) & pressedKey){
					
					Mario_checkDirection((Mario)owner, pressedKey);					
				}

				// check if jump
				if(K_A & pressedKey){
					
					Mario_jump((Mario)owner, false);			
				}
			}			
			return true;
			break;
			
		case kKeyUp:
			{
				u16 releasedKey = *((u16*)Telegram_getExtraInfo(telegram));

				if(K_LL & releasedKey){
	
					Velocity velocity = Body_getVelocity(Actor_getBody((Actor)owner));
					
					if ( 0 > velocity.x){
						
						Mario_stopMoving((Mario)owner);		
					}
				}
				else if(K_LR & releasedKey){
	
					Velocity velocity = Body_getVelocity(Actor_getBody((Actor)owner));
					
					if ( 0 < velocity.x){
						
						Mario_stopMoving((Mario)owner);		
					}
				}
				
				if(K_B & releasedKey){
					
					Mario_disableBoost((Mario)owner);
				}
			}
			break;
	
		case kKeyHold:
			{
				u16 holdKey = *((u16*)Telegram_getExtraInfo(telegram));

				// check direction
				if((K_LL | K_LR ) & holdKey){
					
					Mario_keepMoving((Mario)owner);					
				}
				
				if(K_B & holdKey){
					
					Mario_enableBoost((Mario)owner);
				}
			}
			break;

		case kBodyStoped:
			
			return Mario_stopMovingOnAxis((Mario)owner, *(int*)Telegram_getExtraInfo(telegram), true);
			break;

		case kBodyStartedMoving:

			// start movement
			return Mario_startedMovingOnAxis((Mario)owner, *(int*)Telegram_getExtraInfo(telegram), false);
			break;

		case kBodyChangedDirection:
			
			return Mario_startedMovingOnAxis((Mario)owner, *(int*)Telegram_getExtraInfo(telegram), false);
			break;
		case kCollision:

//			StateMachine_swapState(Actor_getStateMachine((Actor) owner), (State)MarioIdle_getInstance());					

			return false;
//			return Mario_processCollision((Mario)owner, telegram);				
			break;
			

			
	}
	return false;
	
}

