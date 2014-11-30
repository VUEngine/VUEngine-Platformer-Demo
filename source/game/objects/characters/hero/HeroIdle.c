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

#include "HeroIdle.h"
#include "HeroMoving.h"
#include "Hero.h"

#ifdef __DEBUG

//#include "../../levels/game/GameLevel.h"
#endif

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												PROTOTYPES
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */


// class's constructor
static void HeroIdle_constructor(HeroIdle this);

// class's destructor
void HeroIdle_destructor(HeroIdle this);

// state's enter
void HeroIdle_enter(HeroIdle this, void* owner);

// state's execute
void HeroIdle_execute(HeroIdle this, void* owner);

// state's exit
void HeroIdle_exit(HeroIdle this, void* owner);

// state's on message
u16 HeroIdle_handleMessage(HeroIdle this, void* owner, Telegram telegram);

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 											CLASS'S DEFINITION
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

__CLASS_DEFINITION(HeroIdle);

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												CLASS'S METHODS
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
__SINGLETON(HeroIdle);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's constructor
void HeroIdle_constructor(HeroIdle this){

	// construct base
	__CONSTRUCT_BASE(State);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's destructor
void HeroIdle_destructor(HeroIdle this){

	// destroy base
//	__SINGLETON_DESTROY(State);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's enter
void HeroIdle_enter(HeroIdle this, void* owner){
	
	// make sure it's not moving anymore 
	Actor_stopMovement((Actor)owner);
	
	// reset timer for blinking
	Hero_resetActionTime((Hero)owner);
	
	if(Hero_isMovingOverZ((Hero)owner)){
		
		if(__NEAR == InGameEntity_getDirection((InGameEntity)owner).z){

			// show animation
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)owner, "Front");
		}
		else{
			
			// show animation
			AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)owner, "Back");
			
		}
	}
	else{
	
		// show animation
		AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)owner, "Idle");
	}
	
	AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)owner, "Idle");

	Hero_resetActionTime((Hero)owner);

	Hero_setGap((Hero)owner);
	
#ifdef __DEBUG
	Printing_text("HeroIde::enter   ", 0, (__SCREEN_HEIGHT >> 3) - 1);
#endif
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's execute
void HeroIdle_execute(HeroIdle this, void* owner){
	
	/*
	if(!Hero_isMovingOverZ((Hero)owner)){
		
		
		// if up key pressed
		if(!((K_LU | K_LD) & vbKeyPressed())){
	
			// make mario to look to the side
			Hero_lookSide((Hero)owner);
		}
	}
	
	if(!(K_B & vbKeyPressed())){
		
		// check if must thrown an object
		//Hero_throwObject((Hero)owner);
	}
	*/
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's exit 
void HeroIdle_exit(HeroIdle this, void* owner){
	
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's on message
u16 HeroIdle_handleMessage(HeroIdle this, void* owner, Telegram telegram){

	switch(Telegram_getMessage(telegram)){
	
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

				if((K_LL | K_LR | K_A) & pressedKey){
	
						/* 
						if((K_LR & pressedKey ) && (K_LL & pressedKey )){
						
							return true;
						}
	*/
						Hero_checkDirection((Hero)owner, pressedKey, "Idle");					
	
						Hero_startedMovingOnAxis((Hero)owner, __XAXIS);
						
						if(K_A & pressedKey ){

							Hero_jump((Hero)owner, true);
						}

						return true;
						break;
				}

				// if up key pressed
				if(K_LU & pressedKey){
	
					// make mario to look to the player
					Hero_lookBack((Hero)owner);
	
					// check if there is a bridge
					Hero_checkIfBridge((Hero)owner, K_LU);
	
					// check if there is a bridge
					Hero_checkIfBridge((Hero)owner, K_LU);
					/*
					vbjPrintInt(doPower(4,2), 1, 16);
					vbjPrintInt(doPower1(4,2), 5, 16);
					vbjPrintInt(doPower(4,3), 1, 17);
					vbjPrintInt(doPower1(4,3), 5, 17);
					*/
					/*
					{
						int i,j = 1;
						int baseLimit = 5;
						int maxPower = 5;
						int distance = 10;
						int initBase = 2;
						for(i= initBase;i <= baseLimit; i++){
							
							for(j = 1;j <= maxPower; j++){
								int powerA = power(i, j);
								int powerB = power1(i, j);
								Printing_int(i, (i - initBase)* distance, j+2);
								Printing_text("^", (i - initBase)* distance + 1, j+2);
								Printing_int(j, (i - initBase)* distance + 2, j+2);
								Printing_text("=", (i - initBase)* distance + 3, j+2);
								Printing_int(powerA, (i - initBase)* distance + 4, j+2);
								Printing_text("|", (i - initBase)* distance + 4 + Utilities_intLength(powerA), j+2);
								Printing_int(powerB, (i - initBase)* distance + 4 + Utilities_intLength(powerA) + 1, j+2);
							}
						}
					}
					*/


					return true;
				}
				
				// if up key pressed
				if(K_LD & pressedKey){
	
					// make mario to look away the player
					Hero_lookFront((Hero)owner);
	
					// check if there is a bridge
					Hero_checkIfBridge((Hero)owner, K_LD);
	
					// check if there is a bridge
					Hero_checkIfBridge((Hero)owner, K_LD);
	
					return true;
				}	
	
				/*
				{
					int alpha = 0;
					// if up key pressed
					if(K_LT & pressedKey){
						
						alpha--;
						if(alpha < 0){
							alpha = 511;
						}
						//Sprite_rotate(Entity_getSprite((Entity)owner), alpha);
						
					}
					
					// if up key pressed
					if(K_RT & pressedKey){
						alpha++;
						if(alpha > 511){
							alpha = 0;
						}				
						//Sprite_rotate(Entity_getSprite((Entity)owner), alpha);
						
					}
				}
				*/
			}
			break;
	}
	return false;
}

