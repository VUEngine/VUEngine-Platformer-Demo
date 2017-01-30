/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2017 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef HERO_H_
#define HERO_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Actor.h>
#include <Door.h>
#include <ParticleSystem.h>
#include <ProgressManager.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												MACROS
//---------------------------------------------------------------------------------------------------------

#define HERO_NAME               "John Hero"
#define HERO_INITIAL_ENERGY  	3

#define HERO_FLASH_PALETTE      3
#define HERO_FLASH_DURATION     2000
#define HERO_FLASH_INTERVAL     100

enum HeroPowerUps
{
	kPowerUpNone,
	kPowerUpBandana,
};


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

#define Hero_METHODS(ClassName)																			\
    	Actor_METHODS(ClassName)																	    \

#define Hero_SET_VTABLE(ClassName)																		\
        Actor_SET_VTABLE(ClassName)																	    \
        __VIRTUAL_SET(ClassName, Hero, ready);															\
        __VIRTUAL_SET(ClassName, Hero, update);															\
        __VIRTUAL_SET(ClassName, Hero, takeHitFrom);													\
        __VIRTUAL_SET(ClassName, Hero, handlePropagatedMessage);										\
        __VIRTUAL_SET(ClassName, Hero, handleMessage);													\
        __VIRTUAL_SET(ClassName, Hero, suspend);														\
        __VIRTUAL_SET(ClassName, Hero, resume);															\
        __VIRTUAL_SET(ClassName, Hero, updateSurroundingFriction);										\
        __VIRTUAL_SET(ClassName, Hero, getAxisAllowedForBouncing);										\
        __VIRTUAL_SET(ClassName, Hero, collisionsProcessingDone);										\
        __VIRTUAL_SET(ClassName, Hero, getAxisForFlipping);										        \

__CLASS(Hero);

#define Hero_ATTRIBUTES																					\
        /* it is derived from */																		\
        Actor_ATTRIBUTES																				\
        /* a reference to the last door the hero passed */    											\
        Door currentlyOverlappedDoor;																	\
        /* hint entity */																				\
        Entity hint;																					\
        /* feet dust */																					\
        ParticleSystem feetDust;																		\
        /* bounding box to control camera's movement */													\
        Entity cameraBoundingBox;																		\
        /* used to know if gap must be changed */														\
        Direction inputDirection;																		\
        /* hero has energy	*/																			\
        u8 energy;																						\
        /* boost flag */																				\
        bool boost;																						\
        /* number of collected coins */																	\
        u8 coins;																						\
        /* flag for collected key */																	\
        bool hasKey;																					\
        /* currently active power-up */																	\
        u8 powerUp;																						\
        /* number of jumps performed (for double jump) */												\
        s8 jumps;																						\
        /* flag for invincible mode (after being hit) */												\
        bool invincible;																				\


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

Hero Hero_getInstance();

__CLASS_NEW_DECLARE(Hero, ActorDefinition* animatedEntityDefinition, s16 id, s16 internalId, const char* const name);

void Hero_constructor(Hero this, ActorDefinition* definition, s16 id, s16 internalId, const char* const name);
void Hero_destructor(Hero this);
void Hero_ready(Hero this, u32 recursive);
void Hero_addForce(Hero this, int axis);
void Hero_stopAddingForce(Hero this);
void Hero_startedMovingOnAxis(Hero this, int axis);
bool Hero_stopMovingOnAxis(Hero this, int axis);
void Hero_move(Hero this);
void Hero_jump(Hero this, bool checkIfYMovement);
void Hero_addMomentumToJump(Hero this);
void Hero_checkDirection(Hero this, u32 currentPressedKey, char * animation);
void Hero_synchronizeDirectionWithVelocity(Hero this);
void Hero_takeHitFrom(Hero this, InGameEntity inGameEntity, int energyToReduce, bool pause, bool invincibleWins, bool alignToEnemy);
void Hero_flash(Hero this);
void Hero_toggleFlashPalette(Hero this);
void Hero_resetPalette(Hero this);
void Hero_disableBoost(Hero this);
void Hero_enableBoost(Hero this);
Door Hero_getOverlappedDoor(Hero this);
void Hero_enterDoor(Hero this);
void Hero_showHint(Hero this, u32 hintType);
void Hero_hideHint(Hero this);
void Hero_lookFront(Hero this);
void Hero_lookBack(Hero this);
void Hero_die(Hero this);
void Hero_collectKey(Hero this);
bool Hero_hasKey(Hero this);
void Hero_collectPowerUp(Hero this, u8 powerUp);
u8 Hero_getPowerUp(Hero this);
u8 Hero_getEnergy(Hero this);
void Hero_setInvincible(Hero this, bool invincible);
bool Hero_isInvincible(Hero this);
int Hero_processCollision(Hero this, Telegram telegram);
bool Hero_handleMessage(Hero this, Telegram telegram);
bool Hero_handlePropagatedMessage(Hero this, int message);
void Hero_suspend(Hero this);
void Hero_resume(Hero this);
void Hero_lockCameraTriggerMovement(Hero this, u8 axisToLockUp, bool locked);
void Hero_updateSurroundingFriction(Hero this);
u8 Hero_getAxisAllowedForBouncing(Hero this);
void Hero_getOutOfDoor(Hero this, VBVec3D* outOfDoorPosition);
void Hero_update(Hero this, u32 elapsedTime);
bool Hero_isAboveEntity(Hero this, Entity entity);
void Hero_collisionsProcessingDone(Hero this, VirtualList collidingSpatialObjects);
u32 Hero_getAxisForFlipping(Hero this);
void Hero_onPowerUpTransitionComplete(Hero this, Object eventFirer);


#endif
