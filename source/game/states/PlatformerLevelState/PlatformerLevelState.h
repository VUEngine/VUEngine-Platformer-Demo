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
	__VIRTUAL_SET(ClassName, PlatformerLevelState, execute);					\
	__VIRTUAL_SET(ClassName, PlatformerLevelState, exit);						\
	__VIRTUAL_SET(ClassName, PlatformerLevelState, pause);						\
	__VIRTUAL_SET(ClassName, PlatformerLevelState, resume);						\
	__VIRTUAL_SET(ClassName, PlatformerLevelState, handleMessage);				\


__CLASS(PlatformerLevelState);

#define PlatformerLevelState_ATTRIBUTES											\
																				\
	/* inherits */																\
	GameState_ATTRIBUTES														\
																				\
	/* the stage to load */														\
	StageDefinition* stageDefinition;											\
																				\
	/* to allow moving the screen */											\
	u8 mode: 4;																	\
	
enum PlatformerLevelStateMessageTypes
{
	kHeroDied = kLastEngineMessage + 1,
	kHeroFall,
	kSetUpLevel,
	kStartLevel,
	kHideLevelMessage,
	kTakeCoin,
	kTakeKey,
	kEnterDoor,
    kCheckForOverlappingDoor,

	// don't remove me
	kLastPlatformerMessage
};


//---------------------------------------------------------------------------------------------------------
// 										   MACROS
//---------------------------------------------------------------------------------------------------------

#define EVENT_KEY_PRESSED		"keyPressed"
#define EVENT_KEY_RELEASED		"keyReleased"
#define EVENT_KEY_HOLD			"keyHold"

#define EVENT_COIN_TAKEN		"CoinTaken"
#define EVENT_KEY_TAKEN			"KeyTaken"


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

// setup the init focus screen
PlatformerLevelState PlatformerLevelState_getInstance(void);
void PlatformerLevelState_setStage(PlatformerLevelState this, StageDefinition* stageDefinition);
void PlatformerLevelState_goToLevel(StageDefinition* stageDefinition);


#endif