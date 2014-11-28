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

#include <Game.h>
#include <CollisionManager.h>
#include <Optics.h>
#include <PhysicalWorld.h>
#include <Prototypes.h>

#include "SawBlade.h"
#include "SawBladeIdle.h"
#include "SawBladeMoving.h"
#include "../enemy/EnemyDead.h"
#include "../Hero/Hero.h"


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 											 CLASS'S DEFINITION
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

__CLASS_DEFINITION(SawBlade); 


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												PROTOTYPES
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */




/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												CLASS'S METHODS
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// always call these two macros next to each other
__CLASS_NEW_DEFINITION(SawBlade, __PARAMETERS(SawBladeDefinition* sawBladeDefinition, int ID))
__CLASS_NEW_END(SawBlade, __ARGUMENTS(sawBladeDefinition, ID));

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's conctructor
void SawBlade_constructor(SawBlade this, SawBladeDefinition* sawBladeDefinition, int ID){
	
	// construct base
	__CONSTRUCT_BASE(Enemy, __ARGUMENTS((ActorDefinition*)&sawBladeDefinition->actorDefinition, ID));

	// initialize me as walking
	StateMachine_swapState(this->stateMachine, (State)SawBladeMoving_getInstance());
	
	// register a shape for collision detection
	SawBlade_registerShape(this);

	// register a body for physics
	this->body = PhysicalWorld_registerBody(PhysicalWorld_getInstance(), (Actor)this, 0);
	Body_stopMovement(this->body, (__XAXIS | __YAXIS | __ZAXIS));

	// save over which axis I'm going to move
	this->axis = sawBladeDefinition->axis;
	
	// set movement direction;
	this->movementDirection = sawBladeDefinition->direction;
	
	switch(this->axis){
		
		case __XAXIS:

			this->direction.x = sawBladeDefinition->direction;			
			break;
			
		case __YAXIS:
			
			this->direction.y = sawBladeDefinition->direction;
			break;			
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's conctructor
void SawBlade_destructor(SawBlade this){

	// delete the super object
	__DESTROY_BASE(Enemy);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// register a shape with the collision detection system
void SawBlade_registerShape(SawBlade this){

	// register a shape for collision detection
	this->shape = CollisionManager_registerShape(CollisionManager_getInstance(), (Entity)this, kCuboid);
	
	// don't check collisions agains other objects
	Shape_setCheckForCollisions(this->shape, false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// unregister the shape with the collision detection system
void SawBlade_unregisterShape(SawBlade this){

	Shape_setActive(this->shape, false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// process a collision
u8 SawBlade_processCollision(SawBlade this, Telegram telegram){
	
	int message = Telegram_getMessage(telegram);
	InGameEntity inGameEntity = (InGameEntity) Telegram_getExtraInfo(telegram);
	
	switch(message){

		case kCollision:
			
			switch(InGameEntity_getInGameType(inGameEntity)){
			
				case kHero:

					// tell mario to take a hit
					//Hero_takeHit((Hero)inGameEntity, this->transform.globalPosition);
					break;
			}
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// tell me I've been hit
void SawBlade_takeHit(SawBlade this, int axis, s8 direction){
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// die 
void SawBlade_die(SawBlade this){
	
	// must unregister the shape for collision detections
	Shape_setActive(this->shape, false);

	// now change state to dead
	StateMachine_swapState(this->stateMachine, (State)EnemyDead_getInstance());
	
	// set state
	//this->inGameState = kDead;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// set  position
void SawBlade_setLocalPosition(SawBlade this, VBVec3D position){
	
	// set my position
	Actor_setLocalPosition((Actor)this, position);
	
	// save initial position
	switch(this->axis){
		
		case __XAXIS:

			this->initialPosition = position.x;
						
			break;
			
		case __YAXIS:
			
			this->initialPosition = position.y;
			break;			
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// retrieve axis free for movement
int SawBlade_getAxisFreeForMovement(SawBlade this){

	return 0;// ((__XAXIS & ~(__XAXIS & movingState) )|(__ZAXIS & ~(__ZAXIS & movingState)));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// update movement
void SawBlade_move(SawBlade this){

	int displacement = 0;
	
	// update position
	switch(this->axis){
		
		case __XAXIS:
			break;
			
		case __YAXIS:
			
			switch(this->direction.y){
				
				case __UP:
					{
						
						if(__UP == this->movementDirection){
							
							displacement = ITOFIX19_13(Entity_getHeight((Entity)this));
						}
						
						// check position
						if(this->transform.globalPosition.y < this->initialPosition - displacement){
							
							// stop moving
							Actor_stopMovement((Actor)this);
							
							// change direction
							this->direction.y = __DOWN;
							
							// start action time
							this->actionTime = Clock_getTime(Game_getInGameClock(Game_getInstance()));
							
							// set position
							this->transform.localPosition.y = this->initialPosition - displacement;
						}
					}
					break;
					
				case __DOWN:

					{
						if(__DOWN == this->movementDirection){
							
							displacement = ITOFIX19_13(Entity_getHeight((Entity)this));
						}
						
						// check position
						if(this->transform.globalPosition.y > this->initialPosition + displacement){
							
							// stop moving
							Actor_stopMovement((Actor)this);
							
							// change direction
							this->direction.y = __UP;
							
							// start action time
							this->actionTime = Clock_getTime(Game_getInGameClock(Game_getInstance()));
							
							// set position
							this->transform.localPosition.y = this->initialPosition + displacement;
						}
					}
					break;
					
			}
			break;			
	}

	// if I've been stopped
	if(false && !(this->axis & Actor_isMoving((Actor)this))){
		
		// check if must stop go idle
		if(!displacement){
			
			// check if mario distance to the plant is out of range
			if(SAW_BLADE_ATTACK_DISTANCE < Optics_lengthSquared3D(
					Entity_getPosition((Entity)this), Entity_getPosition((Entity)Hero_getInstance()))
			){
				StateMachine_swapState(this->stateMachine, (State)SawBladeIdle_getInstance());
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
// start moving
void SawBlade_startMovement(SawBlade this){
	
	switch(this->axis){
		
		case __XAXIS:
			break;
			
		case __YAXIS:
			
			{
				Velocity velocity = {
					0,
					((int)ITOFIX19_13(1) * this->direction.y),
					0,
				};
				
				Body_moveUniformly(this->body, velocity);
			}
			// move over y axis
			//Actor_startMovement((Actor)this, __YAXIS, ~(__ACCELMOVEY | __RETARMOVEY),
			//		SAW_BLADEELOCITY_Y, SAW_BLADE_ACCELERATION_Y);
			
			
			break;			
	}
	
	this->actionTime = 0;
}