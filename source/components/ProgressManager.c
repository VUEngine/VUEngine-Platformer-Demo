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


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <string.h>
#include <stddef.h>

#include <GameEvents.h>
#include <ProgressManager.h>
#include <SRAMManager.h>
#include <EventManager.h>
#include <Utilities.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(ProgressManager, Object);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void ProgressManager_constructor(ProgressManager this);
static void ProgressManager_initialize(ProgressManager this);
static void ProgressManager_onHitTaken(ProgressManager this, Object eventFirer);
static void ProgressManager_onKeyTaken(ProgressManager this, Object eventFirer);
static void ProgressManager_onPowerUp(ProgressManager this, Object eventFirer);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// it's a singleton
__SINGLETON(ProgressManager);

// class's constructor
static void __attribute__ ((noinline)) ProgressManager_constructor(ProgressManager this)
{
	ASSERT(this, "ProgressManager::constructor: null this");

	// construct base object
	__CONSTRUCT_BASE(Object);

	ProgressManager_initialize(this);

	ProgressManager_reset(this);

    Object eventManager = __SAFE_CAST(Object, EventManager_getInstance());

    // add event listeners
	Object_addEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager_onHitTaken, kEventHitTaken);
	Object_addEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager_onKeyTaken, kEventKeyTaken);
	Object_addEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager_onPowerUp, kEventPowerUp);
}

// class's destructor
void ProgressManager_destructor(ProgressManager this)
{
	ASSERT(this, "ProgressManager::destructor: null this");
	ASSERT(EventManager_getInstance(), "ProgressManager::destructor: null eventManager");

    Object eventManager = __SAFE_CAST(Object, EventManager_getInstance());

    // remove event listeners
	Object_removeEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager_onHitTaken, kEventHitTaken);
	Object_removeEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager_onKeyTaken, kEventKeyTaken);
    Object_removeEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager_onPowerUp, kEventPowerUp);

	// destroy base
	__SINGLETON_DESTROY;
}

void ProgressManager_reset(ProgressManager this)
{
	this->heroCurrentEnergy = HERO_INITIAL_ENERGY;
	this->heroCurrentPowerUp = kPowerUpNone;
	this->heroHasKey = false;
	this->heroHasUsedKey = false;
}

static void ProgressManager_initialize(ProgressManager this __attribute__ ((unused)))
{
	ASSERT(this, "ProgressManager::initialize: null this");

	char saveStamp[SAVE_STAMP_LENGTH];
	SRAMManager_read(SRAMManager_getInstance(), (BYTE*)&saveStamp, offsetof(struct UserData, saveStamp), sizeof(saveStamp));

	if(strncmp(saveStamp, SAVE_STAMP, SAVE_STAMP_LENGTH))
	{
		strncpy(saveStamp, SAVE_STAMP, SAVE_STAMP_LENGTH);
		SRAMManager_save(SRAMManager_getInstance(), (BYTE*)&saveStamp, offsetof(struct UserData, saveStamp), sizeof(saveStamp));

		int numberOfCollectedCoins = 0;
		SRAMManager_save(SRAMManager_getInstance(), (BYTE*)&numberOfCollectedCoins, offsetof(struct UserData, numberOfCollectedCoins), sizeof(numberOfCollectedCoins));

		int coin = 1;
		for(; coin <= TOTAL_COINS_IN_GAME; coin++)
		{
			CoinStatus coinStatus;
			coinStatus.taken = false;
			strncpy(coinStatus.name, "Coin ", COIN_NAME_LENGTH);
			strncat(coinStatus.name, Utilities_itoa(coin, 10, 2), COIN_NAME_LENGTH);
			SRAMManager_save(SRAMManager_getInstance(), (BYTE*)&coinStatus, offsetof(struct UserData, coinStatus) + sizeof(CoinStatus) * coin, sizeof(coinStatus));
		}
	}
}

int ProgressManager_getNumberOfCollectedCoins(ProgressManager this __attribute__ ((unused)))
{
	ASSERT(this, "ProgressManager::getNumberOfCollectedCoins: null this");

	int numberOfCollectedCoins;
	SRAMManager_read(SRAMManager_getInstance(), (BYTE*)&numberOfCollectedCoins, offsetof(struct UserData, numberOfCollectedCoins), sizeof(numberOfCollectedCoins));
	return numberOfCollectedCoins;
}

void ProgressManager_setNumberOfCollectedCoins(ProgressManager this __attribute__ ((unused)), int numberOfCollectedCoins)
{
	ASSERT(this, "ProgressManager::setNumberOfCollectedCoins: null this");

	SRAMManager_save(SRAMManager_getInstance(), (BYTE*)&numberOfCollectedCoins, offsetof(struct UserData, numberOfCollectedCoins), sizeof(numberOfCollectedCoins));
}

bool ProgressManager_getCoinStatus(ProgressManager this __attribute__ ((unused)), const char* coinName)
{
	ASSERT(this, "ProgressManager::getCoinStatus: null this");

	if(coinName)
	{
		int coin = 1;
		for(; coin <= TOTAL_COINS_IN_GAME; coin++)
		{
			CoinStatus coinStatus;
			SRAMManager_read(SRAMManager_getInstance(), (BYTE*)&coinStatus, offsetof(struct UserData, coinStatus) + sizeof(CoinStatus) * coin, sizeof(coinStatus));

			if(coinName && !strncmp(coinStatus.name, coinName, COIN_NAME_LENGTH))
			{
				return coinStatus.taken;
			}
		}
	}

	return false;
}

bool ProgressManager_setCoinStatus(ProgressManager this __attribute__ ((unused)), char* coinName, bool taken)
{
	ASSERT(this, "ProgressManager::setCoinStatus: null this");

	int coin = 1;
	for(; coin <= TOTAL_COINS_IN_GAME; coin++)
	{
		CoinStatus coinStatus;
		SRAMManager_read(SRAMManager_getInstance(), (BYTE*)&coinStatus, offsetof(struct UserData, coinStatus) + sizeof(CoinStatus) * coin, sizeof(coinStatus));

		if(!strncmp(coinStatus.name, coinName, COIN_NAME_LENGTH))
		{
			coinStatus.taken = taken;
			SRAMManager_save(SRAMManager_getInstance(), (BYTE*)&coinStatus, offsetof(struct UserData, coinStatus) + sizeof(CoinStatus) * coin, sizeof(coinStatus));
			return true;
		}
	}

	return false;
}

// get hero's current energy
u8 ProgressManager_getHeroCurrentEnergy(ProgressManager this)
{
	return this->heroCurrentEnergy;
}

// get hero's current power-up
u8 ProgressManager_getHeroCurrentPowerUp(ProgressManager this)
{
	return this->heroCurrentPowerUp;
}

bool ProgressManager_heroHasKey(ProgressManager this)
{
	return this->heroHasKey;
}

bool ProgressManager_heroHasUsedKey(ProgressManager this)
{
	return this->heroHasUsedKey;
}

// handle event
static void ProgressManager_onHitTaken(ProgressManager this, Object eventFirer __attribute__ ((unused)))
{
	this->heroCurrentEnergy = Hero_getEnergy(Hero_getInstance());
}

// handle event
static void ProgressManager_onKeyTaken(ProgressManager this, Object eventFirer __attribute__ ((unused)))
{
	this->heroHasKey = true;
}

// handle event
static void ProgressManager_onPowerUp(ProgressManager this, Object eventFirer __attribute__ ((unused)))
{
	this->heroCurrentPowerUp = Hero_getPowerUp(Hero_getInstance());
}
