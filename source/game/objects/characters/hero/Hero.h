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
#ifndef MARIO_H_
#define MARIO_H_

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												INCLUDES
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

#include <Actor.h>

#include <macros.h>



/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 											CLASS'S DECLARATION
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */



#define Hero_METHODS							\
	Actor_METHODS;
	

#define Hero_SET_VTABLE(ClassName)							\
	Actor_SET_VTABLE(ClassName);							\
	__VIRTUAL_SET(ClassName, Hero, die);					\
	__VIRTUAL_SET(ClassName, Hero, doKeyPressed);			\
	__VIRTUAL_SET(ClassName, Hero, doKeyUp);				\
	__VIRTUAL_SET(ClassName, Hero, doKeyHold);				\
	__VIRTUAL_SET(ClassName, Hero, takeHitFrom);			\

// A Hero!
__CLASS(Hero);

#define Hero_ATTRIBUTES								\
													\
	/* it is derivated from */						\
	Actor_ATTRIBUTES								\
													\
	/* mario has energy	*/							\
	int energy;										\
													\
	/* time when an event ocurred*/					\
	u32 actionTime;									\
													\
	/* hold object */								\
	Actor holdObject;								\
													\
	/* which layer I'm */							\
	u8 layer;										\
													\
	/* Am I jumping over z */						\
	u8 movingOverZ;									\
													\
	/* boost flag */								\
	u8 boost;										\
													\
	/* number of collected coins */					\
	u8 coins;										\


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 										PUBLIC INTERFACE
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

// there can only be one mario instantiated
Hero Hero_getInstance();

// allocator
__CLASS_NEW_DECLARE(Hero, __PARAMETERS(ActorDefinition* animatedEntityDefinition, int ID));

// class's constructor
void Hero_constructor(Hero this, ActorDefinition* definition, int ID);

// class's conctructor
void Hero_destructor(Hero this);

// keep movement
void Hero_keepMoving(Hero this, int changedDirection);

// stop moving
void Hero_stopMoving(Hero this);

// started moving over axis
void Hero_startedMovingOnAxis(Hero this, int axis);

// stop moving over axis
int Hero_stopMovingOnAxis(Hero this, int axis);

// update movement
void Hero_move(Hero this);

// make him jump
void Hero_jump(Hero this, int changeState);

// keep adding force to jump
void Hero_addMomentumToJump(Hero this);

// check direction
void Hero_checkDirection(Hero this, u16 currentPressedKey, char * animation);

// process a collision
int  Hero_processCollision(Hero this, Telegram telegram);

// recieve a hit
void Hero_takeHitFrom(Hero this, Actor other);

// react to a collision with a koopa
//int Hero_isHitByEnemy(Hero this, Enemy enemy, int axis);

// disable boost
void Hero_disableBoost(Hero this);

// enable boost
void Hero_enableBoost(Hero this);

// set action time
void Hero_setActionTime(Hero this, u32 time);

// retrieve action time
u32 Hero_getActionTime(Hero this);

// pickup an object
void Hero_pickupObject(Hero this, Actor object);

// check if player wants to jump over z axis
int Hero_checkIfZJump(Hero this);

// Hero falled 
void Hero_fallDead(Hero this);

// was jumping over z?
int  Hero_isMovingOverZ(Hero this);

// set jumping over z status
void Hero_setMovingOverZ(Hero this, int  state);

// set hold object's position 
void Hero_updateHoldObjectPosition(Hero this);

// make mario to look to the player
void Hero_lookFront(Hero this);

// make mario to look away the player
void Hero_lookBack(Hero this);

// set  graphical gap
void Hero_setGap(Hero this);

// make mario to look to the side
void Hero_lookSide(Hero this);

// check if must thrown an object
void Hero_throwObject(Hero this);

// die mario
void Hero_die(Hero this);

// check if must move over a bridge
void Hero_checkIfBridge(Hero this, int  keyPressed);

// update movement over the bridge
void Hero_moveOnBridge(Hero this);

// set bridge

// determine which layer I'm
void Hero_determineLayer(Hero this);

// clear the actionTime
void Hero_resetActionTime(Hero this);

// goal reached
void Hero_win(Hero this);

// goal reached
void Hero_moveOnWin(Hero this);

// process user input
int Hero_doKeyPressed(Hero this, int pressedKey);

// process user input
int Hero_doKeyUp(Hero this, int pressedKey);

// process user input
int Hero_doKeyHold(Hero this, int pressedKey);

// check if dead
void Hero_checkIfDied(Hero this);

// check if dead
void Hero_collectCoin(Hero this);

#endif /*MARIOLOGIC_H*/
