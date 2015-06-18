/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev <jorgech3@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if not,
 * write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef USER_DATA_MANAGER_H_
#define USER_DATA_MANAGER_H_


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Object.h>


//---------------------------------------------------------------------------------------------------------
// 												MACROS
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// declare the virtual methods
#define UserDataManager_METHODS													\
    	Object_METHODS															\

// declare the virtual methods which are redefined
#define UserDataManager_SET_VTABLE(ClassName)									\
    	Object_SET_VTABLE(ClassName)											\

// declare a UserDataManager
__CLASS(UserDataManager);


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define COIN_NAME_LENGTH		10
#define STAGE_NAME_LENGTH		20
#define SAVE_STAMP_LENGTH		20
#define TOTAL_COINS_IN_GAME		100
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
	
	// current level status (for loading rooms within rooms)
	VBVec3D heroLastPosition;
	char lastStageName[STAGE_NAME_LENGTH];
	bool isExitingRoom;
	
} UserData;

//---------------------------------------------------------------------------------------------------------
// 										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

UserDataManager UserDataManager_getInstance();

void UserDataManager_destructor(UserDataManager this);
int UserDataManager_getNumberOfCollectedCoins(UserDataManager this);
void UserDataManager_setNumberOfCollectedCoins(UserDataManager this, int numberOfCollectedCoins);
bool UserDataManager_getCoinStatus(UserDataManager this, const char* coinName);
bool UserDataManager_setCoinStatus(UserDataManager this, char* coinName, bool status);


#endif