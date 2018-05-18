/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <string.h>
#include <stddef.h>

#include <Game.h>
#include <I18n.h>
#include <Error.h>
#include <GameEvents.h>
#include <ProgressManager.h>
#include <SRAMManager.h>
#include <EventManager.h>
#include <Utilities.h>
#include <macros.h>
#include <AutoPauseScreenState.h>
#include <gameDebugConfig.h>


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void ProgressManager::constructor()
{
	// construct base object
	Base::constructor();

	// init class variables
	this->sramAvailable = false;
	ProgressManager::resetCurrentLevelProgress(this);

	// init progress
	ProgressManager::initialize(this);

	// add event listeners
	Object eventManager = __SAFE_CAST(Object, EventManager::getInstance());
	Object::addEventListener(__SAFE_CAST(Object, PlatformerLevelState::getClock(PlatformerLevelState::getInstance())), __SAFE_CAST(Object, this), (EventListener)ProgressManager::onSecondChange, kEventSecondChanged);
	Object::addEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager::onHitTaken, kEventHitTaken);
	Object::addEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager::onKeyTaken, kEventKeyTaken);
	Object::addEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager::onPowerUp, kEventPowerUp);
	Object::addEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager::onLevelStarted, kEventLevelStarted);
	Object::addEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager::onCheckpointLoaded, kEventCheckpointLoaded);
	Object::addEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager::onLevelCompleted, kEventLevelCompleted);
}

// class's destructor
void ProgressManager::destructor()
{
	ASSERT(EventManager::getInstance(), "ProgressManager::destructor: null eventManager");

	// remove event listeners
	Object eventManager = __SAFE_CAST(Object, EventManager::getInstance());
	Object::removeEventListener(__SAFE_CAST(Object, PlatformerLevelState::getClock(PlatformerLevelState::getInstance())), __SAFE_CAST(Object, this), (EventListener)ProgressManager::onSecondChange, kEventSecondChanged);
	Object::removeEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager::onHitTaken, kEventHitTaken);
	Object::removeEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager::onKeyTaken, kEventKeyTaken);
	Object::removeEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager::onPowerUp, kEventPowerUp);
	Object::removeEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager::onLevelStarted, kEventLevelStarted);
	Object::removeEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager::onCheckpointLoaded, kEventCheckpointLoaded);
	Object::removeEventListener(eventManager, __SAFE_CAST(Object, this), (EventListener)ProgressManager::onLevelCompleted, kEventLevelCompleted);

	// destroy base
	Base::destructor();
}

void ProgressManager::resetHeroState()
{
	this->heroCurrentEnergy = HERO_INITIAL_ENERGY;
	this->heroCurrentPowerUp = kPowerUpNone;
}

void ProgressManager::resetCurrentLevelProgress()
{
	ProgressManager::resetHeroState(this);

	this->heroHasKey = false;
	this->currentLevelTime = 0;
	this->collectedItems = 0;
	this->collectedCoins[0] = 0;
	this->collectedCoins[1] = 0;

	this->checkpointHeroHasKey = false;
	this->checkpointCurrentLevelTime = 0;
	this->checkpointCollectedItems = 0;
	this->checkpointCollectedCoins[0] = 0;
	this->checkpointCollectedCoins[1] = 0;

#ifdef GOD_MODE
	this->heroHasKey = true;
#endif
}

// write then immediately read save stamp to validate sram
bool ProgressManager::verifySaveStamp()
{
	char saveStamp[SAVE_STAMP_LENGTH];

	// write save stamp
	SRAMManager::save(SRAMManager::getInstance(), (BYTE*)SAVE_STAMP, offsetof(struct SaveData, saveStamp), sizeof(saveStamp));

	// read save stamp
	SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&saveStamp, offsetof(struct SaveData, saveStamp), sizeof(saveStamp));

	return !strncmp(saveStamp, SAVE_STAMP, SAVE_STAMP_LENGTH);
}

u32 ProgressManager::computeChecksum()
{
	u32 crc32 = ~0;

	// iterate over whole save data, starting right after the previously saved checksum
	int i = (offsetof(struct SaveData, checksum) + sizeof(crc32));
	for(; i < (int)sizeof(SaveData); i++)
	{
		// get the current byte
		u8 currentByte;
		SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&currentByte, i, sizeof(currentByte));

		// loop over all bits of the current byte and add to checksum
		u8 bit = 0;
		for(; bit < sizeof(currentByte); bit++)
		{
			if((crc32 & 1) != GET_BIT(currentByte, bit))
			{
				crc32 = (crc32 >> 1) ^ 0xEDB88320;
			}
			else
			{
				crc32 = (crc32 >> 1);
			}
		}
	}

	return ~crc32;
}

void ProgressManager::writeChecksum()
{
	u32 checksum = ProgressManager::computeChecksum(this);
	SRAMManager::save(SRAMManager::getInstance(), (BYTE*)&checksum, offsetof(struct SaveData, checksum), sizeof(checksum));
}

bool ProgressManager::verifyChecksum()
{
	u32 computedChecksum = ProgressManager::computeChecksum(this);
	u32 savedChecksum = 0;
	SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&savedChecksum, offsetof(struct SaveData, checksum), sizeof(savedChecksum));

	return (computedChecksum == savedChecksum);
}

void ProgressManager::clearProgress()
{
	if(this->sramAvailable)
	{
		SRAMManager::clear(SRAMManager::getInstance(), offsetof(struct SaveData, numberOfCompletedLevels), (int)sizeof(SaveData));
	}
}

bool ProgressManager::hasProgress()
{
	u8 numberOfCompletedLevels = 0;

	if(this->sramAvailable)
	{
		SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&numberOfCompletedLevels, offsetof(struct SaveData, numberOfCompletedLevels), sizeof(numberOfCompletedLevels));
	}

	return (numberOfCompletedLevels > 0);
}

void ProgressManager::initialize()
{
	// verify sram validity
	if(ProgressManager::verifySaveStamp(this))
	{
		// set sram available flag
		this->sramAvailable = true;

		// verify saved progress presence and integrity
		if(!ProgressManager::verifyChecksum(this))
		{
			// if no previous save could be verified, completely erase sram to start clean
			SRAMManager::clear(SRAMManager::getInstance(), 0, (int)sizeof(SaveData));

			// write checksum
			ProgressManager::writeChecksum(this);
		}

		// load and set active language
		I18n::setActiveLanguage(I18n::getInstance(), ProgressManager::getLanguage(this));

		// load and set auto pause state
		Game::setAutomaticPauseState(Game::getInstance(), ProgressManager::getAutomaticPauseStatus(this)
			? __SAFE_CAST(GameState, AutoPauseScreenState::getInstance())
			: NULL
		);
	}
}

void ProgressManager::setCheckPointData()
{
	this->checkpointHeroHasKey = this->heroHasKey;
	this->checkpointCurrentLevelTime = this->currentLevelTime;
	this->checkpointCollectedItems = this->collectedItems;
	this->checkpointCollectedCoins[0] = this->collectedCoins[0];
	this->checkpointCollectedCoins[1] = this->collectedCoins[1];
}

void ProgressManager::loadCheckPointData()
{
	this->heroHasKey = this->checkpointHeroHasKey;
	this->currentLevelTime = this->checkpointCurrentLevelTime;
	this->collectedItems = this->checkpointCollectedItems;
	this->collectedCoins[0] = this->checkpointCollectedCoins[0];
	this->collectedCoins[1] = this->checkpointCollectedCoins[1];
}

u8 ProgressManager::getCurrentLevelNumberOfCollectedCoins()
{
	u8 numberOfCollectedCoins = 0;
	for(int i = 0; i < COINS_PER_LEVEL; i++)
	{
		numberOfCollectedCoins += GET_BIT(this->collectedCoins[i >> 5], i);
	}

	return numberOfCollectedCoins;
}

u32 ProgressManager::getCurrentLevelBestTime()
{
	return this->currentLevelBestTime;
}

u16 ProgressManager::getTotalNumberOfCollectedCoins()
{
	u16 numberOfCollectedCoins = 0;
	if(this->sramAvailable)
	{
		SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&numberOfCollectedCoins, offsetof(struct SaveData, numberOfCollectedCoins), sizeof(numberOfCollectedCoins));
	}

	return numberOfCollectedCoins;
}

u8 ProgressManager::getLanguage()
{
	u8 languageId = 0;
	if(this->sramAvailable)
	{
		SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&languageId, offsetof(struct SaveData, languageId), sizeof(languageId));
	}

	return languageId;
}

void ProgressManager::setLanguage(u8 languageId)
{
	if(this->sramAvailable)
	{
		// write language
		SRAMManager::save(SRAMManager::getInstance(), (BYTE*)&languageId, offsetof(struct SaveData, languageId), sizeof(languageId));

		// write checksum
		ProgressManager::writeChecksum(this);
	}
}

bool ProgressManager::getAutomaticPauseStatus()
{
	u8 autoPauseStatus = 0;
	if(this->sramAvailable)
	{
		SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&autoPauseStatus, offsetof(struct SaveData, autoPauseStatus), sizeof(autoPauseStatus));
	}

	return !autoPauseStatus;
}

void ProgressManager::setAutomaticPauseStatus(u8 autoPauseStatus)
{
	if(this->sramAvailable)
	{
		// we save the inverted status, so that 0 = enabled, 1 = disabled.
		// that way, a blank value means enabled, which is the standard setting.
		autoPauseStatus = !autoPauseStatus;

		// write auto pause status
		SRAMManager::save(SRAMManager::getInstance(), (BYTE*)&autoPauseStatus, offsetof(struct SaveData, autoPauseStatus), sizeof(autoPauseStatus));

		// write checksum
		ProgressManager::writeChecksum(this);
	}
}

bool ProgressManager::getCoinStatus(u16 id)
{
	if(id > 0 && id <= COINS_PER_LEVEL)
	{
		return GET_BIT(this->collectedCoins[(id - 1) >> 5], (id - 1));
	}

	return false;
}

bool ProgressManager::setCoinStatus(u16 id, bool taken)
{
	if(id > 0 && id <= COINS_PER_LEVEL)
	{
		if(taken)
		{
			SET_BIT(this->collectedCoins[(id - 1) >> 5], (id - 1));
		}
		else
		{
			CLEAR_BIT(this->collectedCoins[(id - 1) >> 5], (id - 1));
		}

		return true;
	}

	return false;
}

bool ProgressManager::getItemStatus(u16 id)
{
	if(id > 0 && id <= sizeof(this->collectedItems))
	{
		return GET_BIT(this->collectedItems, (id - 1));
	}

	return false;
}

bool ProgressManager::setItemStatus(u16 id, bool taken)
{
	if(id > 0 && id <= sizeof(this->collectedItems))
	{
		if(taken)
		{
			SET_BIT(this->collectedItems, (id - 1));
		}
		else
		{
			CLEAR_BIT(this->collectedItems, (id - 1));
		}

		return true;
	}

	return false;
}

void ProgressManager::loadLevelStatus(u8 levelId)
{
	u16 currentLevelOffset = 0;

	// reset all unsaved progress for current level
	ProgressManager::resetCurrentLevelProgress(this);

	if(this->sramAvailable)
	{
		// determine offset of current level in sram
		currentLevelOffset = offsetof(struct SaveData, levelStatuses) + ((levelId - 1) * sizeof(struct LevelStatus));

		// load collected coin flags
		SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&this->collectedCoins[0], currentLevelOffset + offsetof(struct LevelStatus, collectedCoins[0]), sizeof(this->collectedCoins[0]));
		SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&this->collectedCoins[1], currentLevelOffset + offsetof(struct LevelStatus, collectedCoins[1]), sizeof(this->collectedCoins[1]));

		// load best time
		SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&this->currentLevelBestTime, currentLevelOffset + offsetof(struct LevelStatus, bestTime), sizeof(this->currentLevelBestTime));
	}
}

void ProgressManager::persistLevelStatus(u8 levelId)
{
	if(this->sramAvailable)
	{
		u8 i, numberOfCollectedCoins, levelCompleted, totalNumberOfCompletedLevels;
		u16 currentLevelOffset, totalNumberOfCollectedCoins;

		// determine offset of current level in sram
		currentLevelOffset = offsetof(struct SaveData, levelStatuses) + ((levelId - 1) * sizeof(struct LevelStatus));

		// save collected coin flags
		SRAMManager::save(SRAMManager::getInstance(), (BYTE*)&this->collectedCoins[0], currentLevelOffset + offsetof(struct LevelStatus, collectedCoins[0]), sizeof(this->collectedCoins[0]));
		SRAMManager::save(SRAMManager::getInstance(), (BYTE*)&this->collectedCoins[1], currentLevelOffset + offsetof(struct LevelStatus, collectedCoins[1]), sizeof(this->collectedCoins[1]));

		// save number of collected coins
		numberOfCollectedCoins = ProgressManager::getCurrentLevelNumberOfCollectedCoins(this);
		SRAMManager::save(SRAMManager::getInstance(), (BYTE*)&numberOfCollectedCoins, currentLevelOffset + offsetof(struct LevelStatus, numberOfCollectedCoins), sizeof(numberOfCollectedCoins));

		// save level completed flag
		levelCompleted = 1;
		SRAMManager::save(SRAMManager::getInstance(), (BYTE*)&levelCompleted, currentLevelOffset + offsetof(struct LevelStatus, levelCompleted), sizeof(levelCompleted));

		// save new best time, if it's the first time beating this level or if time beats the previous time
		if(!this->currentLevelBestTime || (this->currentLevelBestTime > this->currentLevelTime))
		{
			SRAMManager::save(SRAMManager::getInstance(), (BYTE*)&this->currentLevelTime, currentLevelOffset + offsetof(struct LevelStatus, bestTime), sizeof(this->currentLevelTime));
		}

		// determine and save total number of collected coins and completed levels
		numberOfCollectedCoins = 0;
		totalNumberOfCollectedCoins = 0;
		levelCompleted = 0;
		totalNumberOfCompletedLevels = 0;
		for(i = 0; i < LEVELS_IN_GAME; i++)
		{
			currentLevelOffset = offsetof(struct SaveData, levelStatuses) + (i * sizeof(struct LevelStatus));

			// collected coins
			SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&numberOfCollectedCoins, currentLevelOffset + offsetof(struct LevelStatus, numberOfCollectedCoins), sizeof(numberOfCollectedCoins));
			totalNumberOfCollectedCoins += numberOfCollectedCoins;

			// level completed
			SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&levelCompleted, currentLevelOffset + offsetof(struct LevelStatus, levelCompleted), sizeof(levelCompleted));
			if(levelCompleted > 0)
			{
				totalNumberOfCompletedLevels++;
			}
		}
		SRAMManager::save(SRAMManager::getInstance(), (BYTE*)&totalNumberOfCompletedLevels, offsetof(struct SaveData, numberOfCompletedLevels), sizeof(totalNumberOfCompletedLevels));
		SRAMManager::save(SRAMManager::getInstance(), (BYTE*)&totalNumberOfCollectedCoins, offsetof(struct SaveData, numberOfCollectedCoins), sizeof(totalNumberOfCollectedCoins));

		// write checksum
		ProgressManager::writeChecksum(this);
	}
}

// get hero's current energy
u8 ProgressManager::getHeroCurrentEnergy()
{
	return this->heroCurrentEnergy;
}

// get hero's current power-up
u8 ProgressManager::getHeroCurrentPowerUp()
{
	return this->heroCurrentPowerUp;
}

bool ProgressManager::heroHasKey()
{
	return this->heroHasKey;
}

// get current level time
u32 ProgressManager::getCurrentLevelTime()
{
	return this->currentLevelTime;
}

// handle event
void ProgressManager::onSecondChange(Object eventFirer __attribute__ ((unused)))
{
	this->currentLevelTime = Clock::getTime(PlatformerLevelState::getClock(PlatformerLevelState::getInstance()));
}

// handle event
void ProgressManager::onHitTaken(Object eventFirer __attribute__ ((unused)))
{
	this->heroCurrentEnergy = Hero::getEnergy(Hero::getInstance());
}

// handle event
void ProgressManager::onKeyTaken(Object eventFirer __attribute__ ((unused)))
{
	this->heroHasKey = true;
}

// handle event
void ProgressManager::onPowerUp(Object eventFirer __attribute__ ((unused)))
{
	this->heroCurrentPowerUp = Hero::getPowerUp(Hero::getInstance());
}

// handle event
void ProgressManager::onLevelStarted(Object eventFirer __attribute__ ((unused)))
{
	PlatformerLevelDefinition* platformerLevelDefinition = PlatformerLevelState::getCurrentLevelDefinition(PlatformerLevelState::getInstance());

	ProgressManager::loadLevelStatus(this, platformerLevelDefinition->id);
}

// handle event
void ProgressManager::onCheckpointLoaded(Object eventFirer __attribute__ ((unused)))
{
	ProgressManager::resetHeroState(this);
	ProgressManager::loadCheckPointData(this);
}

// handle event
void ProgressManager::onLevelCompleted(Object eventFirer __attribute__ ((unused)))
{
	PlatformerLevelDefinition* platformerLevelDefinition = PlatformerLevelState::getCurrentLevelDefinition(PlatformerLevelState::getInstance());

	ProgressManager::persistLevelStatus(this, platformerLevelDefinition->id);
}
