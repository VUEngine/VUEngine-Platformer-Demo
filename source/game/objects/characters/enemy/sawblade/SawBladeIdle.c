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

#include <Optics.h>

#include "SawBladeIdle.h"
#include "SawBladeMoving.h"
#include "SawBlade.h"
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
void SawBladeIdle_constructor(SawBladeIdle this);

// class's destructor
void SawBladeIdle_destructor(SawBladeIdle this);

// state's enter
void SawBladeIdle_enter(SawBladeIdle this, void* owner);

// state's execute
void SawBladeIdle_execute(SawBladeIdle this, void* owner);

// state's enter
void SawBladeIdle_exit(SawBladeIdle this, void* owner);

// state's on message
u16 SawBladeIdle_handleMessage(SawBladeIdle this, void* owner, Telegram telegram);


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 											CLASS'S DEFINITION
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

__CLASS_DEFINITION(SawBladeIdle);

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												CLASS'S METHODS
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
__SINGLETON(SawBladeIdle);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's constructor
void SawBladeIdle_constructor(SawBladeIdle this){

	// construct base
	__CONSTRUCT_BASE(State);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's destructor
void SawBladeIdle_destructor(SawBladeIdle this){

	// destroy base
	__SINGLETON_DESTROY(State);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's enter
void SawBladeIdle_enter(SawBladeIdle this, void* owner){
	
	// do not move
//	Actor_stopMovement((Actor)owner, __XAXIS | __YAXIS | __ZAXIS);

	AnimatedInGameEntity_playAnimation((AnimatedInGameEntity)owner, "Idle");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's execute
void SawBladeIdle_execute(SawBladeIdle this, void* owner){
	/*
	// if not waiting
	if(!Enemy_getActionTime((Enemy)owner)){
	
		// update movement
		SawBlade_move((SawBlade)owner);		
	}
	else{
		
		// if wait time elapsed
		if(SAW_BLADE_WAIT_DELAY < Clock_getTime(Game_getInGameClock(Game_getInstance())) - Enemy_getActionTime((Enemy)owner)){
			
			// start movement in opposite direction
			SawBlade_startMovement((SawBlade)owner);
		}
	}
*/
	// check if mario distance to the plant is within range
	/*if(SAW_BLADE_ATTACK_DISTANCE > Optics_lengthSquared3D(
			Entity_getPosition((Entity)owner), Entity_getPosition((Entity)Hero_getInstance()))
	){
		StateMachine_swapState(Actor_getStateMachine((Actor)owner), (State)SawBladeMoving_getInstance());
	}*/
	StateMachine_swapState(Actor_getStateMachine((Actor)owner), (State)SawBladeMoving_getInstance());
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's exit 
void SawBladeIdle_exit(SawBladeIdle this, void* owner){
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's on message
u16 SawBladeIdle_handleMessage(SawBladeIdle this, void* owner, Telegram telegram){

	return false;
}
