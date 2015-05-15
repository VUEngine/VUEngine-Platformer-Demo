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


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <string.h>

#include <UserDataManager.h>
#include <SRAMManager.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

#define UserDataManager_ATTRIBUTES												\
																				\
	/* super's attributes */													\
	Object_ATTRIBUTES;															\

// define the UserDataManager
__CLASS_DEFINITION(UserDataManager, Object);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void UserDataManager_constructor(UserDataManager this);
static void UserDataManager_initialize(UserDataManager this);


//---------------------------------------------------------------------------------------------------------
// 												GLOBALS
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// it's a singleton
__SINGLETON(UserDataManager);

// class's constructor
static void UserDataManager_constructor(UserDataManager this)
{
	ASSERT(this, "UserDataManager::constructor: null this");

	// construct base object
	__CONSTRUCT_BASE();
	
	UserDataManager_initialize(this);
}

// class's destructor
void UserDataManager_destructor(UserDataManager this)
{
	ASSERT(this, "UserDataManager::destructor: null this");

	// destroy base
	__SINGLETON_DESTROY;
}

static void UserDataManager_initialize(UserDataManager this)
{
	ASSERT(this, "UserDataManager::initialize: null this");

	char saveStamp[SAVE_STAMP_LENGTH];
	SRAMManager_read(SRAMManager_getInstance(), (BYTE*)&saveStamp, (u16*)&_userData->saveStamp, sizeof(saveStamp));
	
	if(strncmp(saveStamp, SAVE_STAMP, SAVE_STAMP_LENGTH))
	{
		strncpy(saveStamp, SAVE_STAMP, SAVE_STAMP_LENGTH);
		SRAMManager_save(SRAMManager_getInstance(), (BYTE*)&saveStamp, (u16*)&_userData->saveStamp, sizeof(saveStamp));
	
		int numberOfCollectedCoins = 0;
		SRAMManager_save(SRAMManager_getInstance(), (BYTE*)&numberOfCollectedCoins, (u16*)&(_userData->numberOfCollectedCoins), sizeof(numberOfCollectedCoins));
		
		int coin = 1;
		for(; coin <= TOTAL_COINS_IN_GAME; coin++)
		{
			CoinStatus coinStatus;
			coinStatus.taken = false;
			strncpy(coinStatus.name, "Coin ", COIN_NAME_LENGTH);
			strncat(coinStatus.name, Utilities_itoa(coin, 10, 3), COIN_NAME_LENGTH);
			SRAMManager_save(SRAMManager_getInstance(), (BYTE*)&coinStatus, (u16*)&_userData->coinStatus[coin], sizeof(coinStatus));
		}
	}
}

int UserDataManager_getNumberOfCollectedCoins(UserDataManager this)
{
	ASSERT(this, "UserDataManager::getNumberOfCollectedCoins: null this");

	int numberOfCollectedCoins;
	SRAMManager_read(SRAMManager_getInstance(), (BYTE*)&numberOfCollectedCoins, (u16*)&_userData->numberOfCollectedCoins, sizeof(numberOfCollectedCoins));
	return numberOfCollectedCoins;
}

void UserDataManager_setNumberOfCollectedCoins(UserDataManager this, int numberOfCollectedCoins)
{
	ASSERT(this, "UserDataManager::setNumberOfCollectedCoins: null this");
	
	SRAMManager_save(SRAMManager_getInstance(), (BYTE*)&numberOfCollectedCoins, (u16*)&_userData->numberOfCollectedCoins, sizeof(numberOfCollectedCoins));
}

bool UserDataManager_getCoinStatus(UserDataManager this, const char* coinName)
{
	ASSERT(this, "UserDataManager::getCoinStatus: null this");

	
	int coin = 1;
	for(; coin <= TOTAL_COINS_IN_GAME; coin++)
	{
		CoinStatus coinStatus;
		SRAMManager_read(SRAMManager_getInstance(), (BYTE*)&coinStatus, (u16*)&_userData->coinStatus[coin], sizeof(coinStatus));
		
		if(!strncmp(coinStatus.name, coinName, COIN_NAME_LENGTH))
		{
			return coinStatus.taken;
		}
	}
	
	return false;
}

bool UserDataManager_setCoinStatus(UserDataManager this, char* coinName, bool taken)
{
	ASSERT(this, "UserDataManager::setCoinStatus: null this");
	
	int coin = 1;
	for(; coin <= TOTAL_COINS_IN_GAME; coin++)
	{
		CoinStatus coinStatus;
		SRAMManager_read(SRAMManager_getInstance(), (BYTE*)&coinStatus, (u16*)&_userData->coinStatus[coin], sizeof(coinStatus));
		
		if(!strncmp(coinStatus.name, coinName, COIN_NAME_LENGTH))
		{
			coinStatus.taken = taken;
			SRAMManager_save(SRAMManager_getInstance(), (BYTE*)&coinStatus, (u16*)&_userData->coinStatus[coin], sizeof(coinStatus));
			return true;
		}
	}
	
	return false;
}
