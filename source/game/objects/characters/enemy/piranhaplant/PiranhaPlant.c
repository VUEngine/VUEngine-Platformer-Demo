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

#include "PiranhaPlant.h"
#include "PiranhaPlantIdle.h"
#include "PiranhaPlantMoving.h"
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


// PiranhaPlant.c

// A PiranhaPlant!
__CLASS_DEFINITION(PiranhaPlant); 

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
// always call these to macros next to each other
__CLASS_NEW_DEFINITION(PiranhaPlant, __PARAMETERS(PiranhaPlantDefinition* piranhaPlantDefinition, int ID))
__CLASS_NEW_END(PiranhaPlant, __ARGUMENTS(piranhaPlantDefinition, ID));

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's conctructor
void PiranhaPlant_constructor(PiranhaPlant this, PiranhaPlantDefinition* piranhaPlantDefinition, int ID){
	
	// construct base
	__CONSTRUCT_BASE(Enemy, __ARGUMENTS((ActorDefinition*)&piranhaPlantDefinition->actorDefinition, ID));

	// initialize me as walking
	StateMachine_swapState(this->stateMachine, (State)PiranhaPlantIdle_getInstance());
	
	// register a shape for collision detection
	PiranhaPlant_registerShape(this);

	// register a body for physics
	this->body = PhysicalWorld_registerBody(PhysicalWorld_getInstance(), (Actor)this, 0);
	Body_stopMovement(this->body, (__XAXIS | __YAXIS | __ZAXIS));

	// save over which axis I'm going to move
	this->axis = piranhaPlantDefinition->axis;
	
	// set movement direction;
	this->movementDirection = piranhaPlantDefinition->direction;
	
	switch(this->axis){
		
		case __XAXIS:

			this->direction.x = piranhaPlantDefinition->direction;			
			break;
			
		case __YAXIS:
			
			this->direction.y = piranhaPlantDefinition->direction;
			break;			
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's conctructor
void PiranhaPlant_destructor(PiranhaPlant this){

	// delete the super object
	__DESTROY_BASE(Enemy);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// register a shape with the collision detection system
void PiranhaPlant_registerShape(PiranhaPlant this){

	// register a shape for collision detection
	this->shape = CollisionManager_registerShape(CollisionManager_getInstance(), (InGameEntity)this, kCuboid);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// unregister the shape with the collision detection system
void PiranhaPlant_unregisterShape(PiranhaPlant this){

	Shape_setActive(this->shape, false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// process a collision
u8 PiranhaPlant_processCollision(PiranhaPlant this, Telegram telegram){
	
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
void PiranhaPlant_takeHit(PiranhaPlant this, int axis, s8 direction){
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// die 
void PiranhaPlant_die(PiranhaPlant this){
	
	// must unregister the shape for collision detections
	Shape_setActive(this->shape, false);

	// now change state to dead
	StateMachine_swapState(this->stateMachine, (State)EnemyDead_getInstance());
	
	// set state
	//this->inGameState = kDead;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// set  position
void PiranhaPlant_setLocalPosition(PiranhaPlant this, VBVec3D position){
	
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
int PiranhaPlant_getAxisFreeForMovement(PiranhaPlant this){

	return 0;// ((__XAXIS & ~(__XAXIS & movingState) )|(__ZAXIS & ~(__ZAXIS & movingState)));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// update movement
void PiranhaPlant_move(PiranhaPlant this){

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
	if(!(this->axis & Actor_isMoving((Actor)this))){
		
		// check if must stop go idle
		if(!displacement){
			
			// check if mario distance to the plant is out of range
			if(PIRANHA_PLANT_ATTACK_DISTANCE < Optics_lengthSquared3D(
					Entity_getPosition((Entity)this), Entity_getPosition((Entity)Hero_getInstance()))
			){
				StateMachine_swapState(this->stateMachine, (State)PiranhaPlantIdle_getInstance());
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
// start moving
void PiranhaPlant_startMovement(PiranhaPlant this){
	
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
			//		PIRANHA_PLANT_VELOCITY_Y, PIRANHA_PLANT_ACCELERATION_Y);
			
			
			break;			
	}
	
	this->actionTime = 0;
}
