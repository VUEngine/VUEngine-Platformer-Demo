/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef PROGRESS_MANAGER_H_
#define PROGRESS_MANAGER_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <SaveDataManager.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 											TYPE DEFINITIONS
//---------------------------------------------------------------------------------------------------------

typedef struct LevelStatus
{
	// flag that tells whether the level was ever completed
	uint8 levelCompleted;

	// number of collected coins in this level
	uint8 numberOfCollectedCoins;

	// the best time the level was ever completed in
	uint32 bestTime;

	// bitstrings that hold collected coin flags
	// 0 = not collected, 1 = collected
	uint32 collectedCoins[2];

} LevelStatus;

// this struct is never instantiated, its sole purpose is to determine offsets of its members.
// therefore it acts as kind of like a map of sram content.
typedef struct GameSaveData
{
	// save data handled by base class
	SaveData baseSaveData;

	// total number of completed levels
	uint8 numberOfCompletedLevels;

	// total number of collected coins
	uint16 numberOfCollectedCoins;

	// completion statuses for every level in the game
	LevelStatus levelStatuses[LEVELS_IN_GAME];

} GameSaveData;


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

singleton class ProgressManager : SaveDataManager
{
	// time in current level
	uint32 currentLevelTime;
	// time in current level at last checkpoint
	uint32 checkpointCurrentLevelTime;
	// best time in current level
	uint32 currentLevelBestTime;
	// bitstrings that hold collected coin flags
	uint32 collectedCoins[2];
	// bitstrings that hold collected coin flags at last checkpoint
	uint32 checkpointCollectedCoins[2];
	// bitstring that holds collected item flags
	uint16 collectedItems;
	// bitstring that holds collected item flags at last checkpoint
	uint16 checkpointCollectedItems;
	// flag that tells if the hero has collected the current level's key
	bool heroHasKey;
	// flag that tells if the hero has collected the current level's key at last checkpoint
	bool checkpointHeroHasKey;
	// hero's current energy
	uint8 heroCurrentEnergy;
	// hero's currently active power-up
	uint8 heroCurrentPowerUp;

	static ProgressManager getInstance();
	void clearProgress();
	bool getCoinStatus(uint16 itemNumber);
	uint32  getCurrentLevelBestTime();
	uint8   getCurrentLevelNumberOfCollectedCoins();
	uint32  getCurrentLevelTime();
	uint8   getHeroCurrentEnergy();
	uint8   getHeroCurrentPowerUp();
	bool getItemStatus(uint16 itemNumber);
	override int getSaveDataSize();
	uint16  getTotalNumberOfCollectedCoins();
	bool hasProgress();
	bool heroHasKey();
	void loadCheckPointData();
	override void restoreSettings();
	void setCheckPointData();
	bool setCoinStatus(uint16 itemNumber, bool taken);
	bool setItemStatus(uint16 itemNumber, bool taken);
	void resetCurrentLevelProgress();
}


#endif
