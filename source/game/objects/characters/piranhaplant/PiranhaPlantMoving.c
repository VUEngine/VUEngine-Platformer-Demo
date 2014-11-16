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


#include "PiranhaPlantMoving.h"
#include "PiranhaPlantIdle.h"
#include "../enemy/EnemyDead.h"
#include "PiranhaPlant.h"
#include "../hero/Hero.h"


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												PROTOTYPES
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */


// class's constructor
void PiranhaPlantMoving_constructor(PiranhaPlantMoving this);

// class's destructor
void PiranhaPlantMoving_destructor(PiranhaPlantMoving this);

// state's enter
void PiranhaPlantMoving_enter(PiranhaPlantMoving this, void* owner);

// state's execute
void PiranhaPlantMoving_execute(PiranhaPlantMoving this, void* owner);

// state's enter
void PiranhaPlantMoving_exit(PiranhaPlantMoving this, void* owner);

// state's on message
u16 PiranhaPlantMoving_handleMessage(PiranhaPlantMoving this, void* owner, Telegram telegram);


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 											CLASS'S DEFINITION
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

__CLASS_DEFINITION(PiranhaPlantMoving);

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												CLASS'S METHODS
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
__SINGLETON(PiranhaPlantMoving);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's constructor
void PiranhaPlantMoving_constructor(PiranhaPlantMoving this){

	// construct base
	__CONSTRUCT_BASE(State);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's destructor
void PiranhaPlantMoving_destructor(PiranhaPlantMoving this){

	// destroy base
	__SINGLETON_DESTROY(State);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's enter
void PiranhaPlantMoving_enter(PiranhaPlantMoving this, void* owner){
	
	// do not move
	//Actor_stopMovement((Actor)owner, __XAXIS | __YAXIS | __ZAXIS);
	
	PiranhaPlant_startMovement((PiranhaPlant)owner);
	
	Actor_playAnimation((Actor)owner, "Bite");
	Printing_text("PiranhaPlant Bite", 0, 8);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's execute
void PiranhaPlantMoving_execute(PiranhaPlantMoving this, void* owner){
	
	// if not waiting
	if(!Enemy_getActionTime((Enemy)owner)){
	
		// update movement
		PiranhaPlant_move((PiranhaPlant)owner);		
	}
	else{
		
		// if wait time elapsed
		if(PIRANHA_PLANT_WAIT_DELAY < Clock_getTime(_inGameClock) - Enemy_getActionTime((Enemy)owner)){
			
			// start movement in opposite direction
			PiranhaPlant_startMovement((PiranhaPlant)owner);
		}
	}
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's exit 
void PiranhaPlantMoving_exit(PiranhaPlantMoving this, void* owner){
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's on message
u16 PiranhaPlantMoving_handleMessage(PiranhaPlantMoving this, void* owner, Telegram telegram){

	int message = Telegram_getMessage(telegram);
	
	switch(message){

		case kCollision:
		{
			VirtualList collidingObjects = (VirtualList)Telegram_getExtraInfo(telegram);

			VirtualNode node = NULL;
			
			// this will place the shape in the owner's position
			for(node = VirtualList_begin(collidingObjects); node; node = VirtualNode_getNext(node)){
			
				InGameEntity inGameEntity = (InGameEntity)VirtualNode_getData(node);
				
				switch(InGameEntity_getInGameType(inGameEntity)){
				
					case kHero:
							// ok, i hit him
							//Hero_takeHit((Mario)inGameEntity, Entity_getPosition((Entity)owner));
							
						return true;
						break;
						
					case kSolid:
						
						return true;
						break;
				}
							
			}
		}
			break;
	}

	return false;
}

