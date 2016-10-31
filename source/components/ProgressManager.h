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

#ifndef PROGRESS_MANAGER_H_
#define PROGRESS_MANAGER_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Object.h>
#include <Hero.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define ProgressManager_METHODS(ClassName)																\
    	Object_METHODS(ClassName)																		\

// declare the virtual methods which are redefined
#define ProgressManager_SET_VTABLE(ClassName)															\
    	Object_SET_VTABLE(ClassName)																	\

// declare class
__CLASS(ProgressManager);

// declare class attributes
#define ProgressManager_ATTRIBUTES																		\
        /* super's attributes */																		\
        Object_ATTRIBUTES																				\
        /* hero's current energy */																		\
        u8 heroCurrentEnergy;																			\
        /* hero's currently active power-up */															\
        u8 heroCurrentPowerUp;																			\
        /* flag that tells if the hero has collected the current level's key */							\
        bool heroHasKey;																				\
        /* bitstring that holds collected item flags */													\
        u16 collectedItems;																				\
        /* time in current level */																		\
        u32 currentLevelTime;																			\
        /* best time in current level */																\
        u32 currentLevelBestTime;																		\
        /* bitstrings that hold collected coin flags */													\
        u32 collectedCoins[2];																			\


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define SAVE_STAMP								"VBJaEPlD"
#define SAVE_STAMP_LENGTH						8

typedef struct LevelStatus
{
	// flag that tells whether the level was ever completed
	u8 levelCompleted;

    // number of collected coins in this level
    u8 numberOfCollectedCoins;

	// the best time the level was ever completed in
	u32 bestTime;

    // bitstrings that hold collected coin flags
    // 0 = not collected, 1 = collected
    u32 collectedCoins[2];

} LevelStatus;

// this struct is never instantiated, its sole purpose is to determine offsets of its members.
// therefore it acts as kind of like a map of sram content.
typedef struct SaveData
{
	// flag to know if there is data saved
	u8 saveStamp[SAVE_STAMP_LENGTH];

	// checksum over sram content to prevent save data manipulation
	u32 checksum;

	// active language id
	u8 languageId;

	// auto pause status (0: on, 1: off)
	u8 autoPauseStatus;

	// total number of completed levels
	u8 numberOfCompletedLevels;

	// total number of collected coins
	u16 numberOfCollectedCoins;

	// completion statuses for every level in the game
	LevelStatus levelStatuses[LEVELS_IN_GAME];

} SaveData;


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

ProgressManager ProgressManager_getInstance();

void ProgressManager_clearProgress(ProgressManager this);
void ProgressManager_destructor(ProgressManager this);
bool ProgressManager_getAutomaticPauseStatus(ProgressManager this);
bool ProgressManager_getCoinStatus(ProgressManager this, u16 itemNumber);
u32  ProgressManager_getCurrentLevelBestTime(ProgressManager this);
u8   ProgressManager_getCurrentLevelNumberOfCollectedCoins(ProgressManager this);
u32  ProgressManager_getCurrentLevelTime(ProgressManager this);
u8   ProgressManager_getHeroCurrentEnergy(ProgressManager this);
u8   ProgressManager_getHeroCurrentPowerUp(ProgressManager this);
bool ProgressManager_getItemStatus(ProgressManager this, u16 itemNumber);
u8   ProgressManager_getLanguage(ProgressManager this);
u16  ProgressManager_getTotalNumberOfCollectedCoins(ProgressManager this);
bool ProgressManager_hasProgress(ProgressManager this);
bool ProgressManager_heroHasKey(ProgressManager this);
void ProgressManager_setAutomaticPauseStatus(ProgressManager this, u8 automaticPause);
bool ProgressManager_setCoinStatus(ProgressManager this, u16 itemNumber, bool taken);
bool ProgressManager_setItemStatus(ProgressManager this, u16 itemNumber, bool taken);
void ProgressManager_setLanguage(ProgressManager this, u8 language);
void ProgressManager_resetCurrentLevelProgress(ProgressManager this);


#endif
