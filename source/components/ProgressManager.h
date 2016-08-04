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

// declare a ProgressManager
__CLASS(ProgressManager);

#define ProgressManager_ATTRIBUTES																		\
        /* super's attributes */																		\
        Object_ATTRIBUTES																				\
        /* hero's current energy */																		\
        u8 heroCurrentEnergy;																			\
        /* hero's currently active power-up */															\
        u8 heroCurrentPowerUp;																			\
        /* flag that tells if the hero has collected the current level's key */							\
        bool heroHasKey;																				\
        /* flag that tells if the hero has already used the current level's key */						\
        bool heroHasUsedKey;																			\


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define COIN_NAME_LENGTH		10
#define STAGE_NAME_LENGTH		20
#define SAVE_STAMP_LENGTH		20
#define TOTAL_COINS_IN_GAME		64
#define SAVE_STAMP				"GameSaved"

typedef struct CoinStatus
{
	char name[COIN_NAME_LENGTH];
	bool taken;
} CoinStatus;

typedef struct UserData
{
	// flag to know if there is data saved
	u32 saveStamp[SAVE_STAMP_LENGTH];

	// number of coins
	int numberOfCollectedCoins;
	CoinStatus coinStatus[TOTAL_COINS_IN_GAME];

} UserData;


//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

ProgressManager ProgressManager_getInstance();

void ProgressManager_destructor(ProgressManager this);
void ProgressManager_reset(ProgressManager this);
int ProgressManager_getNumberOfCollectedCoins(ProgressManager this);
void ProgressManager_setNumberOfCollectedCoins(ProgressManager this, int numberOfCollectedCoins);
bool ProgressManager_getCoinStatus(ProgressManager this, const char* coinName);
bool ProgressManager_setCoinStatus(ProgressManager this, char* coinName, bool status);
u8 ProgressManager_getHeroCurrentEnergy(ProgressManager this);
u8 ProgressManager_getHeroCurrentPowerUp(ProgressManager this);
bool ProgressManager_heroHasKey(ProgressManager this);
bool ProgressManager_heroHasUsedKey(ProgressManager this);


#endif
