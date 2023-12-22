/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <string.h>
#include <stddef.h>

#include <VUEngine.h>
#include <I18n.h>
#include <Error.h>
#include <GameEvents.h>
#include <ProgressManager.h>
#include <SRAMManager.h>
#include <EventManager.h>
#include <Utilities.h>
#include <macros.h>
#include <Hero.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void ProgressManager::constructor()
{
	// construct base object
	Base::constructor();

	// init class variables
	ProgressManager::resetCurrentLevelProgress(this);

	// add event listeners
	ListenerObject eventManager = ListenerObject::safeCast(EventManager::getInstance());
	ListenerObject::addEventListener(Object::safeCast(PlatformerLevelState::getClock(PlatformerLevelState::getInstance())), ListenerObject::safeCast(this), (EventListener)ProgressManager::onSecondChange, kEventSecondChanged);
	ListenerObject::addEventListener(eventManager, ListenerObject::safeCast(this), (EventListener)ProgressManager::onHitTaken, kEventHitTaken);
	ListenerObject::addEventListener(eventManager, ListenerObject::safeCast(this), (EventListener)ProgressManager::onKeyTaken, kEventKeyTaken);
	ListenerObject::addEventListener(eventManager, ListenerObject::safeCast(this), (EventListener)ProgressManager::onPowerUp, kEventPowerUp);
	ListenerObject::addEventListener(eventManager, ListenerObject::safeCast(this), (EventListener)ProgressManager::onLevelStarted, kEventLevelStarted);
	ListenerObject::addEventListener(eventManager, ListenerObject::safeCast(this), (EventListener)ProgressManager::onCheckpointLoaded, kEventCheckpointLoaded);
	ListenerObject::addEventListener(eventManager, ListenerObject::safeCast(this), (EventListener)ProgressManager::onLevelCompleted, kEventLevelCompleted);
}

// class's destructor
void ProgressManager::destructor()
{
	ASSERT(EventManager::getInstance(), "ProgressManager::destructor: null eventManager");

	// remove event listeners
	ListenerObject eventManager = ListenerObject::safeCast(EventManager::getInstance());
	ListenerObject::removeEventListener(Object::safeCast(PlatformerLevelState::getClock(PlatformerLevelState::getInstance())), ListenerObject::safeCast(this), (EventListener)ProgressManager::onSecondChange, kEventSecondChanged);
	ListenerObject::removeEventListener(eventManager, ListenerObject::safeCast(this), (EventListener)ProgressManager::onHitTaken, kEventHitTaken);
	ListenerObject::removeEventListener(eventManager, ListenerObject::safeCast(this), (EventListener)ProgressManager::onKeyTaken, kEventKeyTaken);
	ListenerObject::removeEventListener(eventManager, ListenerObject::safeCast(this), (EventListener)ProgressManager::onPowerUp, kEventPowerUp);
	ListenerObject::removeEventListener(eventManager, ListenerObject::safeCast(this), (EventListener)ProgressManager::onLevelStarted, kEventLevelStarted);
	ListenerObject::removeEventListener(eventManager, ListenerObject::safeCast(this), (EventListener)ProgressManager::onCheckpointLoaded, kEventCheckpointLoaded);
	ListenerObject::removeEventListener(eventManager, ListenerObject::safeCast(this), (EventListener)ProgressManager::onLevelCompleted, kEventLevelCompleted);

	// destroy base
	Base::destructor();
}

int ProgressManager::getSaveDataSize()
{
	return (int)sizeof(GameSaveData);
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

void ProgressManager::clearProgress()
{
	if(this->sramAvailable)
	{
		SRAMManager::clear(SRAMManager::getInstance(), offsetof(struct GameSaveData, numberOfCompletedLevels), ProgressManager::getSaveDataSize(this));
	}
}

bool ProgressManager::hasProgress()
{
	uint8 numberOfCompletedLevels = 0;

	if(this->sramAvailable)
	{
		SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&numberOfCompletedLevels, offsetof(struct GameSaveData, numberOfCompletedLevels), sizeof(numberOfCompletedLevels));
	}

	return (numberOfCompletedLevels > 0);
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

uint8 ProgressManager::getCurrentLevelNumberOfCollectedCoins()
{
	uint8 numberOfCollectedCoins = 0;
	for(int i = 0; i < COINS_PER_LEVEL; i++)
	{
		numberOfCollectedCoins += GET_BIT(this->collectedCoins[i >> 5], i);
	}

	return numberOfCollectedCoins;
}

uint32 ProgressManager::getCurrentLevelBestTime()
{
	return this->currentLevelBestTime;
}

uint16 ProgressManager::getTotalNumberOfCollectedCoins()
{
	uint16 numberOfCollectedCoins = 0;
	if(this->sramAvailable)
	{
		SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&numberOfCollectedCoins, offsetof(struct GameSaveData, numberOfCollectedCoins), sizeof(numberOfCollectedCoins));
	}

	return numberOfCollectedCoins;
}

bool ProgressManager::getCoinStatus(uint16 id)
{
	if(id > 0 && id <= COINS_PER_LEVEL)
	{
		return GET_BIT(this->collectedCoins[(id - 1) >> 5], (id - 1));
	}

	return false;
}

bool ProgressManager::setCoinStatus(uint16 id, bool taken)
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

bool ProgressManager::getItemStatus(uint16 id)
{
	if(id > 0 && id <= sizeof(this->collectedItems))
	{
		return GET_BIT(this->collectedItems, (id - 1));
	}

	return false;
}

bool ProgressManager::setItemStatus(uint16 id, bool taken)
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

void ProgressManager::loadLevelStatus(uint8 levelId)
{
	uint16 currentLevelOffset = 0;

	// reset all unsaved progress for current level
	ProgressManager::resetCurrentLevelProgress(this);

	if(this->sramAvailable)
	{
		// determine offset of current level in sram
		currentLevelOffset = offsetof(struct GameSaveData, levelStatuses) + ((levelId - 1) * sizeof(struct LevelStatus));

		// load collected coin flags
		SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&this->collectedCoins[0], currentLevelOffset + offsetof(struct LevelStatus, collectedCoins[0]), sizeof(this->collectedCoins[0]));
		SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&this->collectedCoins[1], currentLevelOffset + offsetof(struct LevelStatus, collectedCoins[1]), sizeof(this->collectedCoins[1]));

		// load best time
		SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&this->currentLevelBestTime, currentLevelOffset + offsetof(struct LevelStatus, bestTime), sizeof(this->currentLevelBestTime));
	}
}

void ProgressManager::persistLevelStatus(uint8 levelId)
{
	if(this->sramAvailable)
	{
		uint8 i, numberOfCollectedCoins, levelCompleted, totalNumberOfCompletedLevels;
		uint16 currentLevelOffset, totalNumberOfCollectedCoins;

		// determine offset of current level in sram
		currentLevelOffset = offsetof(struct GameSaveData, levelStatuses) + ((levelId - 1) * sizeof(struct LevelStatus));

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
			currentLevelOffset = offsetof(struct GameSaveData, levelStatuses) + (i * sizeof(struct LevelStatus));

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
		SRAMManager::save(SRAMManager::getInstance(), (BYTE*)&totalNumberOfCompletedLevels, offsetof(struct GameSaveData, numberOfCompletedLevels), sizeof(totalNumberOfCompletedLevels));
		SRAMManager::save(SRAMManager::getInstance(), (BYTE*)&totalNumberOfCollectedCoins, offsetof(struct GameSaveData, numberOfCollectedCoins), sizeof(totalNumberOfCollectedCoins));

		// write checksum
		SaveDataManager::writeChecksum(this);
	}
}

// get hero's current energy
uint8 ProgressManager::getHeroCurrentEnergy()
{
	return this->heroCurrentEnergy;
}

// get hero's current power-up
uint8 ProgressManager::getHeroCurrentPowerUp()
{
	return this->heroCurrentPowerUp;
}

bool ProgressManager::heroHasKey()
{
	return this->heroHasKey;
}

// get current level time
uint32 ProgressManager::getCurrentLevelTime()
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
	PlatformerLevelSpec* platformerLevelSpec = PlatformerLevelState::getCurrentLevelSpec(PlatformerLevelState::getInstance());

	ProgressManager::loadLevelStatus(this, platformerLevelSpec->id);
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
	PlatformerLevelSpec* platformerLevelSpec = PlatformerLevelState::getCurrentLevelSpec(PlatformerLevelState::getInstance());

	ProgressManager::persistLevelStatus(this, platformerLevelSpec->id);
}
