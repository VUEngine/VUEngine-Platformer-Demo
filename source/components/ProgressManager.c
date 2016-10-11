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
bool ProgressManager_verifySaveStamp(ProgressManager this);
static void ProgressManager_initialize(ProgressManager this);
static void ProgressManager_onSecondChange(ProgressManager this, Object eventFirer);
static void ProgressManager_onHitTaken(ProgressManager this, Object eventFirer);
static void ProgressManager_onKeyTaken(ProgressManager this, Object eventFirer);
static void ProgressManager_onPowerUp(ProgressManager this, Object eventFirer);
static void ProgressManager_onLevelStarted(ProgressManager this, Object eventFirer);
static void ProgressManager_onLevelCompleted(ProgressManager this, Object eventFirer);


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

	ProgressManager_reset(this);

	ProgressManager_initialize(this);

    Object eventManager = __SAFE_CAST(Object, EventManager_getInstance());

    // add event listeners
	Object_addEventListener(__SAFE_CAST(Object, PlatformerLevelState_getClock(PlatformerLevelState_getInstance())), __SAFE_CAST(Object, this), (EventListener)ProgressManager_onSecondChange, kEventSecondChanged);
	Object_addEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager_onHitTaken, kEventHitTaken);
	Object_addEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager_onKeyTaken, kEventKeyTaken);
	Object_addEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager_onPowerUp, kEventPowerUp);
	Object_addEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager_onLevelStarted, kEventLevelStarted);
	Object_addEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager_onLevelCompleted, kEventLevelCompleted);
}

// class's destructor
void ProgressManager_destructor(ProgressManager this)
{
	ASSERT(this, "ProgressManager::destructor: null this");
	ASSERT(EventManager_getInstance(), "ProgressManager::destructor: null eventManager");

    Object eventManager = __SAFE_CAST(Object, EventManager_getInstance());

    // remove event listeners
    Object_removeEventListener(__SAFE_CAST(Object, PlatformerLevelState_getClock(PlatformerLevelState_getInstance())), __SAFE_CAST(Object, this), (EventListener)ProgressManager_onSecondChange, kEventSecondChanged);
	Object_removeEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager_onHitTaken, kEventHitTaken);
	Object_removeEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager_onKeyTaken, kEventKeyTaken);
    Object_removeEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager_onPowerUp, kEventPowerUp);
    Object_removeEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager_onLevelStarted, kEventLevelStarted);
    Object_removeEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager_onLevelCompleted, kEventLevelCompleted);

	// destroy base
	__SINGLETON_DESTROY;
}

void ProgressManager_reset(ProgressManager this)
{
	this->heroCurrentEnergy = HERO_INITIAL_ENERGY;
	this->heroCurrentPowerUp = kPowerUpNone;
	this->heroHasKey = false;
	this->heroHasUsedKey = false;
	this->currentLevelTime = 0;
	this->collectedItems = 0;
	this->collectedCoins[0] = 0;
	this->collectedCoins[1] = 0;
}

// verify save stamp in sram
// returns true if saved string matches the expected string, false otherwise
bool ProgressManager_verifySaveStamp(ProgressManager this __attribute__ ((unused)))
{
	char saveStamp[SAVE_STAMP_LENGTH];
	SRAMManager_read(SRAMManager_getInstance(), (BYTE*)&saveStamp, offsetof(struct UserData, saveStamp), sizeof(saveStamp));

	return !strncmp(saveStamp, SAVE_STAMP, SAVE_STAMP_LENGTH);
}

static void ProgressManager_initialize(ProgressManager this __attribute__ ((unused)))
{
	ASSERT(this, "ProgressManager::initialize: null this");

	if(!ProgressManager_verifySaveStamp(this))
	{
		// if no previous save could be verified, completely erase sram to start clean
		SRAMManager_clear(SRAMManager_getInstance());

		// write save stamp
		char saveStamp[SAVE_STAMP_LENGTH];
		SRAMManager_save(SRAMManager_getInstance(), (BYTE*)SAVE_STAMP, offsetof(struct UserData, saveStamp), sizeof(saveStamp));
	}
}

u8 ProgressManager_getCurrentLevelNumberOfCollectedCoins(ProgressManager this)
{
	ASSERT(this, "ProgressManager::getNumberOfCollectedCoins: null this");

	u8 numberOfCollectedCoins = 0;
	for(int i = 0; i < COINS_PER_LEVEL; i++)
	{
	    numberOfCollectedCoins += GET_BIT(this->collectedCoins[i >> 5], i);
	}

	return numberOfCollectedCoins;
}


u16 ProgressManager_getTotalNumberOfCollectedCoins(ProgressManager this __attribute__ ((unused)))
{
	ASSERT(this, "ProgressManager::getNumberOfCollectedCoins: null this");

	u16 numberOfCollectedCoins;
	SRAMManager_read(SRAMManager_getInstance(), (BYTE*)&numberOfCollectedCoins, offsetof(struct UserData, numberOfCollectedCoins), sizeof(numberOfCollectedCoins));
	return numberOfCollectedCoins;
}

void ProgressManager_setTotalNumberOfCollectedCoins(ProgressManager this __attribute__ ((unused)), int numberOfCollectedCoins)
{
	ASSERT(this, "ProgressManager::setNumberOfCollectedCoins: null this");

	SRAMManager_save(SRAMManager_getInstance(), (BYTE*)&numberOfCollectedCoins, offsetof(struct UserData, numberOfCollectedCoins), sizeof(numberOfCollectedCoins));
}

u8 ProgressManager_getLanguage(ProgressManager this __attribute__ ((unused)))
{
	ASSERT(this, "ProgressManager::getLanguage: null this");

	u8 languageId;
	SRAMManager_read(SRAMManager_getInstance(), (BYTE*)&languageId, offsetof(struct UserData, languageId), sizeof(languageId));
	return languageId;
}

void ProgressManager_setLanguage(ProgressManager this __attribute__ ((unused)), u8 languageId)
{
	ASSERT(this, "ProgressManager::setLanguage: null this");

	SRAMManager_save(SRAMManager_getInstance(), (BYTE*)&languageId, offsetof(struct UserData, languageId), sizeof(languageId));
}

bool ProgressManager_getAutomaticPauseStatus(ProgressManager this __attribute__ ((unused)))
{
	ASSERT(this, "ProgressManager::getAutomaticPause: null this");

	u8 autoPauseStatus;
	SRAMManager_read(SRAMManager_getInstance(), (BYTE*)&autoPauseStatus, offsetof(struct UserData, autoPauseStatus), sizeof(autoPauseStatus));
	return !autoPauseStatus;
}

void ProgressManager_setAutomaticPauseStatus(ProgressManager this __attribute__ ((unused)), u8 autoPauseStatus)
{
	ASSERT(this, "ProgressManager::setAutomaticPause: null this");

	// we save the inverted status, so that 0 = enabled, 1 = disabled.
	// that way, a blank value means enabled, which is the standard setting.
	autoPauseStatus = !autoPauseStatus;

	SRAMManager_save(SRAMManager_getInstance(), (BYTE*)&autoPauseStatus, offsetof(struct UserData, autoPauseStatus), sizeof(autoPauseStatus));
}

bool ProgressManager_getCoinStatus(ProgressManager this __attribute__ ((unused)), u8 itemNumber)
{
	ASSERT(this, "ProgressManager::getCoinStatus: null this");

	if(itemNumber > 0 && itemNumber <= COINS_PER_LEVEL)
	{
		return GET_BIT(this->collectedCoins[(itemNumber - 1) >> 5], (itemNumber - 1));
	}

	return false;
}

bool ProgressManager_setCoinStatus(ProgressManager this __attribute__ ((unused)), u8 itemNumber, bool taken)
{
	ASSERT(this, "ProgressManager::setCoinStatus: null this");

	if(itemNumber > 0 && itemNumber <= COINS_PER_LEVEL)
	{
		if(taken)
		{
			SET_BIT(this->collectedCoins[(itemNumber - 1) >> 5], (itemNumber - 1));
		}
		else
		{
			CLEAR_BIT(this->collectedCoins[(itemNumber - 1) >> 5], (itemNumber - 1));
		}

/*
int f;
for(f=0; f<32; f++)
{
	Printing_int(Printing_getInstance(), GET_BIT(this->collectedCoins[0], f), f, 1, NULL);
	Printing_int(Printing_getInstance(), GET_BIT(this->collectedCoins[1], f), f, 2, NULL);
}
for(f=0; f<16; f++)
{
	Printing_int(Printing_getInstance(), GET_BIT(this->collectedItems, f), f, 3, NULL);
}
*/

		return true;
	}

	return false;
}

bool ProgressManager_getItemStatus(ProgressManager this __attribute__ ((unused)), u8 itemNumber)
{
	ASSERT(this, "ProgressManager::getItemStatus: null this");

	if(itemNumber > 0 && itemNumber <= COINS_PER_LEVEL)
	{
		return GET_BIT(this->collectedItems, (itemNumber - 1));
	}

	return false;
}

bool ProgressManager_setItemStatus(ProgressManager this __attribute__ ((unused)), u8 itemNumber, bool taken)
{
	ASSERT(this, "ProgressManager::setItemStatus: null this");

	if(itemNumber > 0 && itemNumber <= sizeof(this->collectedItems))
	{
		if(taken)
		{
			SET_BIT(this->collectedItems, (itemNumber - 1));
		}
		else
		{
			CLEAR_BIT(this->collectedItems, (itemNumber - 1));
		}

		return true;
	}

	return false;
}

void ProgressManager_loadLevelStatus(ProgressManager this, u8 levelId)
{
	ASSERT(this, "ProgressManager::persistLevelStatus: null this");

	ProgressManager_reset(this);

    u16 currentLevelOffset = offsetof(struct UserData, levelStatuses) + ((levelId - 1) * sizeof(struct LevelStatus));

	SRAMManager_read(SRAMManager_getInstance(), (BYTE*)&this->collectedCoins[0], currentLevelOffset + offsetof(struct LevelStatus, collectedCoins[0]), sizeof(this->collectedCoins[0]));
	SRAMManager_read(SRAMManager_getInstance(), (BYTE*)&this->collectedCoins[1], currentLevelOffset + offsetof(struct LevelStatus, collectedCoins[1]), sizeof(this->collectedCoins[1]));
}

void ProgressManager_persistLevelStatus(ProgressManager this, u8 levelId)
{
	ASSERT(this, "ProgressManager::persistLevelStatus: null this");

    u8 i = 0, numberOfCollectedCoins = 0, levelCompleted = 1;
	u16 currentLevelOffset = 0, totalNumberOfCollectedCoins = 0;
    u32 currentBestTime = 0;

    currentLevelOffset = offsetof(struct UserData, levelStatuses) + ((levelId - 1) * sizeof(struct LevelStatus));

	SRAMManager_save(SRAMManager_getInstance(), (BYTE*)&this->collectedCoins[0], currentLevelOffset + offsetof(struct LevelStatus, collectedCoins[0]), sizeof(this->collectedCoins[0]));
	SRAMManager_save(SRAMManager_getInstance(), (BYTE*)&this->collectedCoins[1], currentLevelOffset + offsetof(struct LevelStatus, collectedCoins[1]), sizeof(this->collectedCoins[1]));

	numberOfCollectedCoins = ProgressManager_getCurrentLevelNumberOfCollectedCoins(this);
	SRAMManager_save(SRAMManager_getInstance(), (BYTE*)&numberOfCollectedCoins, currentLevelOffset + offsetof(struct LevelStatus, numberOfCollectedCoins), sizeof(numberOfCollectedCoins));

	SRAMManager_save(SRAMManager_getInstance(), (BYTE*)&levelCompleted, currentLevelOffset + offsetof(struct LevelStatus, levelCompleted), sizeof(levelCompleted));

 	SRAMManager_read(SRAMManager_getInstance(), (BYTE*)&currentBestTime, currentLevelOffset + offsetof(struct LevelStatus, bestTime), sizeof(currentBestTime));
    if(!currentBestTime || (currentBestTime > this->currentLevelTime))
    {
	    SRAMManager_save(SRAMManager_getInstance(), (BYTE*)&this->currentLevelTime, currentLevelOffset + offsetof(struct LevelStatus, bestTime), sizeof(this->currentLevelTime));
    }

    numberOfCollectedCoins = 0;
    for(i = 0; i < LEVELS_IN_GAME; i++)
    {
        currentLevelOffset = offsetof(struct UserData, levelStatuses) + (i * sizeof(struct LevelStatus));
        SRAMManager_read(SRAMManager_getInstance(), (BYTE*)&numberOfCollectedCoins, currentLevelOffset + offsetof(struct LevelStatus, numberOfCollectedCoins), sizeof(numberOfCollectedCoins));
        totalNumberOfCollectedCoins += numberOfCollectedCoins;
    }
    ProgressManager_setTotalNumberOfCollectedCoins(this, totalNumberOfCollectedCoins);
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

// get current level time
u32 ProgressManager_getCurrentLevelTime(ProgressManager this)
{
	return this->currentLevelTime;
}

// handle event
static void ProgressManager_onSecondChange(ProgressManager this, Object eventFirer __attribute__ ((unused)))
{
	this->currentLevelTime = Clock_getTime(PlatformerLevelState_getClock(PlatformerLevelState_getInstance()));
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

// handle event
static void ProgressManager_onLevelStarted(ProgressManager this, Object eventFirer __attribute__ ((unused)))
{
    PlatformerLevelDefinition* platformerLevelDefinition = PlatformerLevelState_getCurrentLevelDefinition(PlatformerLevelState_getInstance());

	ProgressManager_loadLevelStatus(this, platformerLevelDefinition->id);
}

// handle event
static void ProgressManager_onLevelCompleted(ProgressManager this, Object eventFirer __attribute__ ((unused)))
{
    PlatformerLevelDefinition* platformerLevelDefinition = PlatformerLevelState_getCurrentLevelDefinition(PlatformerLevelState_getInstance());

	ProgressManager_persistLevelStatus(this, platformerLevelDefinition->id);
}
