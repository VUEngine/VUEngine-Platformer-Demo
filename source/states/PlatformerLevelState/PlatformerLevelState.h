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

#ifndef PLATFORMER_LEVEL_STATE_H_
#define PLATFORMER_LEVEL_STATE_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <GameState.h>




//---------------------------------------------------------------------------------------------------------
// 												DEFINES
//---------------------------------------------------------------------------------------------------------

enum PlatformerLevelModes
{
	kPlaying = 1,
	kShowingUp,
	kPaused,
};


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define PlatformerLevelState_METHODS(ClassName)															\
	    GameState_METHODS(ClassName)																	\

// declare the virtual methods which are redefined
#define PlatformerLevelState_SET_VTABLE(ClassName)														\
        GameState_SET_VTABLE(ClassName)																	\
        __VIRTUAL_SET(ClassName, PlatformerLevelState, enter);											\
        __VIRTUAL_SET(ClassName, PlatformerLevelState, exit);											\
        __VIRTUAL_SET(ClassName, PlatformerLevelState, suspend);										\
        __VIRTUAL_SET(ClassName, PlatformerLevelState, resume);											\
        __VIRTUAL_SET(ClassName, PlatformerLevelState, processMessage);                                 \

__CLASS(PlatformerLevelState);

#define PlatformerLevelState_ATTRIBUTES																	\
        /* inherits */																					\
        GameState_ATTRIBUTES																			\
        /* the current loaded level */																	\
        PlatformerLevelDefinition* currentLevel;														\
        /* the current loaded entry point */															\
        StageEntryPointDefinition* currentStageEntryPoint;												\
        /* to allow moving the screen */																\
        u8 mode;																						\
        /* in-game clock */																				\
        Clock clock;																					\


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S ROM DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef struct StageEntryPointDefinition
{
	// the stage to load
	StageDefinition* stageDefinition;

	// name of the entity to start at
	char* destinationName;

    // offset from entry point (x, y, z)
    VBVec3D offset;

} StageEntryPointDefinition;

typedef const StageEntryPointDefinition StageEntryPointROMDef;


typedef struct PlatformerLevelDefinition
{
	// starting entry point
	StageEntryPointDefinition* entryPoint;

    // id
    u8 id;

	// identifier
	void* identifier;

	// name
	void* name;

} PlatformerLevelDefinition;

typedef const PlatformerLevelDefinition PlatformerLevelROMDef;


enum PlatformerLevelStateMessageTypes
{
	kLevelSetUp = kLastEngineMessage + 1,
	kLevelStarted,
	kLevelResumed,
	kHeroResumePhysics,
	kHideLevelMessage,
	kHeroDied,
	kHeroFall,
	kHeroEnterDoor,
    kHeroStopFeetDust,
    kHeroStopInvincibility,
    kHeroFlash,
	kItemTaken,
	kTakeKey,
	kTakeCoin,
	kTakeBandana,
	kRemoveFromStage,
	kLavaTriggerStart,
	kLavaTriggerEnd,
	kCogWheelMove,
	kLavaMove,
	kCannonShoot,
    kHeroCheckOverlapping,
    kHeroStartOverlapping,
    kHeroEndOverlapping,
    kMovingEntityStartMovement,

	// don't remove me
	kLastPlatformerMessage
};


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

PlatformerLevelState PlatformerLevelState_getInstance(void);

Clock PlatformerLevelState_getClock(PlatformerLevelState this);
PlatformerLevelDefinition* PlatformerLevelState_getCurrentLevelDefinition(PlatformerLevelState this);
void PlatformerLevelState_startLevel(PlatformerLevelState this, PlatformerLevelDefinition* platformerLevelDefinition);
void PlatformerLevelState_enterStage(PlatformerLevelState this, StageEntryPointDefinition* entryPointDefinition);
void PlatformerLevelState_setModeToPaused(PlatformerLevelState this);
void PlatformerLevelState_setModeToPlaying(PlatformerLevelState this);


#endif
