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

#define MARIO_VELOCITY_X			ITOFIX19_13(7)
#define MARIO__BOOST_VELOCITY_X		ITOFIX19_13(9)

#define MARIO_NORMAL_JUMP_FORCE		ITOFIX19_13(-350)
#define MARIO_BOOST_JUMP_FORCE		ITOFIX19_13(-425)


#define MARIO_VELOCITY_Y		FTOFIX19_13(-6.0f)
#define MARIO_ACCELERATION_X	ITOFIX19_13(10)
#define MARIO_ACCELERATION_Y	ITOFIX19_13(0)

#define MARIO_VELOCITY_Z		ITOFIX19_13(175)
#define MARIO_ACCELERATION_Z	ITOFIX19_13(0)

#define MARIO_SPEED_MULTIPLIER_X	FTOFIX19_13(1.5f)
#define MARIO_SPEED_MULTIPLIER_Y	FTOFIX19_13(1.2f)

// time to wait after a hit, to die
#define MARIO_TIME_TO_DIE		500	// miliseconds

#define MARIO_HOLD_OBJECT_X		10
#define MARIO_HOLD_OBJECT_Y		0
#define MARIO_HOLD_OBJECT_Z		1

#define MARIO_WIN_DELAY			1800


#define MARIO_BLINK_DELAY		2000

#define MARIO_DISPLACEMENT_ON_BRIDGE	FTOFIX19_13(2.0f / __FPS_ANIM_FACTOR)

#define Mario_METHODS							\
	Actor_METHODS;
	

#define Mario_SET_VTABLE(ClassName)							\
	Actor_SET_VTABLE(ClassName);							\
	__VIRTUAL_SET(ClassName, Mario, die);					\
	__VIRTUAL_SET(ClassName, Mario, doKeyPressed);			\
	__VIRTUAL_SET(ClassName, Mario, doKeyUp);				\
	__VIRTUAL_SET(ClassName, Mario, doKeyHold);				\
	__VIRTUAL_SET(ClassName, Mario, takeHitFrom);			\

// A Mario!
__CLASS(Mario);

#define Mario_ATTRIBUTES							\
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
	int layer;										\
													\
	/* Am I jumping over z */						\
	int movingOverZ;								\
													\
	/* boost flag */								\
	u8 boost;										\


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 										PUBLIC INTERFACE
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

// there can only be one mario instantiated
Mario Mario_getInstance();

// allocator
__CLASS_NEW_DECLARE(Mario, __PARAMETERS(ActorDefinition* animatedEntityDefinition, int ID));

// class's constructor
void Mario_constructor(Mario this, ActorDefinition* definition, int ID);

// class's conctructor
void Mario_destructor(Mario this);

// start movement
void Mario_startMoving(Mario this);

// keep movement
void Mario_keepMoving(Mario this);

// stop moving
void Mario_stopMoving(Mario this);

// started moving over axis
int Mario_startedMovingOnAxis(Mario this, int axis, int changeState);

// stop moving over axis
int Mario_stopMovingOnAxis(Mario this, int axis, int changeState);

// update movement
void Mario_move(Mario this);

// make him jump
void Mario_jump(Mario this, int changeState);

// keep adding force to jump
void Mario_addMomentumToJump(Mario this);

// check direction
void Mario_checkDirection(Mario this, u16 currentPressedKey);

// process a collision
int  Mario_processCollision(Mario this, Telegram telegram);

// recieve a hit
void Mario_takeHitFrom(Mario this, Actor other);

// react to a collision with a koopa
//int Mario_isHitByEnemy(Mario this, Enemy enemy, int axis);

// disable boost
void Mario_disableBoost(Mario this);

// enable boost
void Mario_enableBoost(Mario this);

// set action time
void Mario_setActionTime(Mario this, u32 time);

// retrieve action time
u32 Mario_getActionTime(Mario this);

// pickup an object
void Mario_pickupObject(Mario this, Actor object);

// check if player wants to jump over z axis
int Mario_checkIfZJump(Mario this);

// Mario falled 
void Mario_fallDead(Mario this);

// called when blink animation is done
void Mario_blinkDone(Mario this);

// was jumping over z?
int  Mario_isMovingOverZ(Mario this);

// set jumping over z status
void Mario_setMovingOverZ(Mario this, int  state);

// set hold object's position 
void Mario_updateHoldObjectPosition(Mario this);

// make mario to look to the player
void Mario_lookFront(Mario this);

// make mario to look away the player
void Mario_lookBack(Mario this);

// set  graphical gap
void Mario_setGap(Mario this);

// make mario to look to the side
void Mario_lookSide(Mario this);

// check if must thrown an object
void Mario_throwObject(Mario this);

// die mario
void Mario_die(Mario this);

// check if must move over a bridge
void Mario_checkIfBridge(Mario this, int  keyPressed);

// update movement over the bridge
void Mario_moveOnBridge(Mario this);

// set bridge

// determine which layer I'm
void Mario_determineLayer(Mario this);

// clear the actionTime
void Mario_resetActionTime(Mario this);

// goal reached
void Mario_win(Mario this);

// goal reached
void Mario_moveOnWin(Mario this);

// process user input
int Mario_doKeyPressed(Mario this, int pressedKey);

// process user input
int Mario_doKeyUp(Mario this, int pressedKey);

// process user input
int Mario_doKeyHold(Mario this, int pressedKey);

// check if dead
void Mario_checkIfDied(Mario this);

#endif /*MARIOLOGIC_H*/
