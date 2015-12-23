/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev <jorgech3@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation; either version 3 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program. If not,
 * see <http://www.gnu.org/licenses/>.
 */

#ifndef HERO_H_
#define HERO_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Actor.h>
#include <Door.h>
#include <HideLayer.h>
#include <ParticleSystem.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												MACROS
//---------------------------------------------------------------------------------------------------------

#define HERO_NAME               "John Hero"
#define HERO_FLASH_PALETTE      3
#define HERO_FLASH_DURATION     3000
#define HERO_FLASH_INTERVAL     100


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Hero_METHODS															\
	Actor_METHODS;

#define Hero_SET_VTABLE(ClassName)												\
	Actor_SET_VTABLE(ClassName);												\
	__VIRTUAL_SET(ClassName, Hero, ready);										\
	__VIRTUAL_SET(ClassName, Hero, die);										\
	__VIRTUAL_SET(ClassName, Hero, takeHitFrom);								\
	__VIRTUAL_SET(ClassName, Hero, doMessage);									\
	__VIRTUAL_SET(ClassName, Hero, handleMessage);								\
	__VIRTUAL_SET(ClassName, Hero, suspend);									\
	__VIRTUAL_SET(ClassName, Hero, resume);										\

__CLASS(Hero);

#define Hero_ATTRIBUTES															\
																				\
	/* it is derived from */													\
	Actor_ATTRIBUTES															\
																				\
	/* a reference to the last door the hero passed */    						\
	Door currentlyOverlappingDoor;												\
	                                                                            \
	/* a reference to the last hide layer the hero passed */    				\
	HideLayer currentlyOverlappingHideLayer;									\
																				\
	/* the currently shown hint entity */										\
	Entity currentHint;															\
																				\
	/* feet dust */																\
	ParticleSystem feetDust;													\
																				\
	/* bounding box to control camera's movement */								\
	Entity cameraBoudingBox;													\
																				\
	/* used to know if gap must be changed */									\
	Direction inputDirection;													\
																				\
	/* hero has energy	*/														\
	s8 energy;																	\
																				\
	/* boost flag */															\
	bool boost;																	\
																				\
	/* number of collected coins */												\
	u8 coins;																	\
																				\
	/* flag for collected key */												\
	bool hasKey;																\
																				\
	/* flag for collected bandana */											\
	bool hasBandana;															\
																				\
	/* flag for invincible mode (after being hit) */							\
	bool invincible;															\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

Hero Hero_getInstance();

__CLASS_NEW_DECLARE(Hero, ActorDefinition* animatedEntityDefinition, int id, const char* const name);

void Hero_constructor(Hero this, ActorDefinition* definition, int id, const char* const name);
void Hero_destructor(Hero this);
void Hero_ready(Hero this);
void Hero_addForce(Hero this, int changedDirection, int axis);
void Hero_stopAddingForce(Hero this);
void Hero_startedMovingOnAxis(Hero this, int axis);
bool Hero_stopMovingOnAxis(Hero this, int axis);
void Hero_move(Hero this);
void Hero_jump(Hero this, int changeState, int checkIfYMovement);
void Hero_addMomentumToJump(Hero this);
void Hero_checkDirection(Hero this, u16 currentPressedKey, char * animation);
void Hero_synchronizeDirectionWithVelocity(Hero this);
void Hero_takeHitFrom(Hero this, Actor other, bool pause);
void Hero_flash(Hero this);
void Hero_toggleFlashPalette(Hero this);
void Hero_resetPalette(Hero this);
void Hero_disableBoost(Hero this);
void Hero_enableBoost(Hero this);
bool Hero_isOverlappingDoor(Hero this);
bool Hero_isOverlappingHideLayer(Hero this);
void Hero_enterDoor(Hero this);
void Hero_showHint(Hero this, char* hintName);
void Hero_hideHint(Hero this);
void Hero_lookFront(Hero this);
void Hero_lookBack(Hero this);
void Hero_die(Hero this);
void Hero_collectKey(Hero this);
bool Hero_hasKey(Hero this);
void Hero_collectBandana(Hero this);
bool Hero_hasBandana(Hero this);
u8 Hero_getCoins(Hero this);
u8 Hero_getEnergy(Hero this);
void Hero_setInvincible(Hero this, bool invincible);
bool Hero_isInvincible(Hero this);
Door Hero_getCurrentlyOverlappingDoor(Hero this);
HideLayer Hero_getCurrentlyOverlappingHideLayer(Hero this);
void Hero_setCurrentlyOverlappingDoor(Hero this, Door door);
void Hero_setCurrentlyOverlappingHideLayer(Hero this, HideLayer hideLayer);
void Hero_resetCurrentlyOverlappingDoor(Hero this);
void Hero_resetCurrentlyOverlappingHideLayer(Hero this);
int Hero_processCollision(Hero this, Telegram telegram);
bool Hero_handleMessage(Hero this, Telegram telegram);
int Hero_doMessage(Hero this, int message);
void Hero_suspend(Hero this);
void Hero_resume(Hero this);
void Hero_setCameraTrigger(Hero this);


#endif