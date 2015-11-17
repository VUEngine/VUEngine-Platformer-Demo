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
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define PlatformerLevelState_METHODS											\
	GameState_METHODS;									

// declare the virtual methods which are redefined
#define PlatformerLevelState_SET_VTABLE(ClassName)								\
	GameState_SET_VTABLE(ClassName)												\
	__VIRTUAL_SET(ClassName, PlatformerLevelState, enter);						\
	__VIRTUAL_SET(ClassName, PlatformerLevelState, exit);						\
	__VIRTUAL_SET(ClassName, PlatformerLevelState, suspend);					\
	__VIRTUAL_SET(ClassName, PlatformerLevelState, resume);						\
	__VIRTUAL_SET(ClassName, PlatformerLevelState, handleMessage);				\


__CLASS(PlatformerLevelState);

#define PlatformerLevelState_ATTRIBUTES											\
																				\
	/* inherits */																\
	GameState_ATTRIBUTES														\
																				\
	/* the stage to load */														\
	PlatformerStageDefinition* platformerStageDefinition;						\
																				\
	/* hero's last position for when exiting a room */							\
	VBVec3D heroLastPosition;													\
																				\
	/* flag to know if exiting a room */										\
	bool isExitingRoom;															\
																				\
	/* to allow moving the screen */											\
	u8 mode: 4;																	\


//---------------------------------------------------------------------------------------------------------
// 										   MACROS
//---------------------------------------------------------------------------------------------------------

#define EVENT_KEY_PRESSED		"keyDown"
#define EVENT_KEY_RELEASED		"keyUp"
#define EVENT_KEY_HOLD			"keyHold"

#define EVENT_COIN_TAKEN		"CoinTaken"
#define EVENT_KEY_TAKEN			"KeyTaken"


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S ROM DECLARATION
//---------------------------------------------------------------------------------------------------------

// defines a game world in ROM memory
typedef struct PlatformerStageDefinition
{
	// stage's definition
	StageDefinition stageDefinition;

	// stages's identifier
	void* identifier;

	// stages's name
	void* name;

} PlatformerStageDefinition;

typedef const PlatformerStageDefinition PlatformerStageROMDef;


enum PlatformerLevelStateMessageTypes
{
	kHeroDied = kLastEngineMessage + 1,
	kHeroFall,
	kSetUpLevel,
	kStartLevel,
	kResumeLevel,
	kHideLevelMessage,
	kTakeCoin,
	kTakeKey,
	kLavaTriggerStart,
	kLavaTriggerEnd,
	kLavaMove,
	kCogWheelMove,
	kCannonShoot,
	kCannonHideSmoke,
	kCannonBallMove,
	kEnterDoor,
	kOpenDoor,
	kCloseDoor,
    kCheckForOverlappingDoor,
    kStopFeetDust,
    kSuspend,

	// don't remove me
	kLastPlatformerMessage
};


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

// setup the init focus screen
PlatformerLevelState PlatformerLevelState_getInstance(void);
void PlatformerLevelState_setStage(PlatformerLevelState this, PlatformerStageDefinition* platformerStageDefinition);
void PlatformerLevelState_goToLevel(PlatformerStageDefinition* platformerStageDefinition);
void PlatformerLevelState_setModeToPaused(PlatformerLevelState this);
void PlatformerLevelState_setModeToPlaying(PlatformerLevelState this);
void PlatformerLevelState_enterRoom(PlatformerStageDefinition* platformerStageDefinition);
void PlatformerLevelState_exitRoom(PlatformerStageDefinition* platformerStageDefinition);


#endif