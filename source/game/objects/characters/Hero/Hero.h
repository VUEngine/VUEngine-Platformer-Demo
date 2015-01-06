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

#ifndef HERO_H_
#define HERO_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Actor.h>
#include <Door.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Hero_METHODS															\
	Actor_METHODS;

#define Hero_SET_VTABLE(ClassName)												\
	Actor_SET_VTABLE(ClassName);												\
	__VIRTUAL_SET(ClassName, Hero, die);										\
	__VIRTUAL_SET(ClassName, Hero, takeHitFrom);								\
	__VIRTUAL_SET(ClassName, Hero, doMessage);									\

__CLASS(Hero);

#define Hero_ATTRIBUTES															\
																				\
	/* it is derivated from */													\
	Actor_ATTRIBUTES															\
																				\
	/* time when an event ocurred*/												\
	u32 actionTime;																\
																				\
	/* hold object */															\
	Actor holdObject;															\
																				\
	/* hero has energy	*/														\
	s8 energy;																	\
																				\
	/* which layer I'm */														\
	u8 layer;																	\
																				\
	/* Am I jumping over z */													\
	bool movingOverZ;																\
																				\
	/* boost flag */															\
	bool boost;																	\
																				\
	/* number of collected coins */												\
	u8 coins;																	\
																				\
	/* number of collected keys */												\
	u8 keys;																	\
																				\
	/* number of lifes */														\
	u8 lifes;																	\
																				\
	/* a reference to the last door the hero passed */    						\
	Door currentlyOverlappingDoor;														\
																				\
	/* flag for hint currently shown */											\
	bool isShowingHint;															\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

Hero Hero_getInstance();

__CLASS_NEW_DECLARE(Hero, __PARAMETERS(ActorDefinition* animatedEntityDefinition, int ID));

void Hero_constructor(Hero this, ActorDefinition* definition, int ID);
void Hero_destructor(Hero this);
void Hero_addForce(Hero this, int changedDirection, int axis);
void Hero_stopMovement(Hero this);
void Hero_startedMovingOnAxis(Hero this, int axis);
bool Hero_stopMovingOnAxis(Hero this, int axis);
void Hero_move(Hero this);
void Hero_jump(Hero this, int changeState, int checkIfYMovement);
void Hero_addMomentumToJump(Hero this);
void Hero_checkDirection(Hero this, u16 currentPressedKey, char * animation);
void Hero_takeHitFrom(Hero this, Actor other);
void Hero_disableBoost(Hero this);
void Hero_enableBoost(Hero this);
void Hero_setActionTime(Hero this, u32 time);
u32 Hero_getActionTime(Hero this);
void Hero_pickupObject(Hero this, Actor object);
bool Hero_isOverlappingDoor(Hero this);
void Hero_resetCurrentlyOverlappingDoor(Hero this);
void Hero_enterDoor(Hero this);
void Hero_showEnterHint(Hero this);
void Hero_hideHint(Hero this);
void Hero_fallDead(Hero this);
bool Hero_isMovingOverZ(Hero this);
void Hero_setMovingOverZ(Hero this, int  state);
void Hero_updateHoldObjectPosition(Hero this);
void Hero_lookFront(Hero this);
void Hero_lookBack(Hero this);
void Hero_setGap(Hero this);
void Hero_lookSide(Hero this);
void Hero_throwObject(Hero this);
void Hero_die(Hero this);
void Hero_determineLayer(Hero this);
void Hero_resetActionTime(Hero this);
void Hero_win(Hero this);
void Hero_moveOnWin(Hero this);
void Hero_collectKey(Hero this);
u8 Hero_getKeys(Hero this);
void Hero_collectCoin(Hero this);
u8 Hero_getCoins(Hero this);
u8 Hero_getLifes(Hero this);
Door Hero_getCurrentlyOverlappingDoor(Hero this);
void Hero_setCurrentlyOverlappingDoor(Hero this, Door door);
int Hero_processCollision(Hero this, Telegram telegram);
int Hero_doMessage(Hero this, int message);


#endif