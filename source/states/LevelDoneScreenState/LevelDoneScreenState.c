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

#include <Game.h>
#include <Camera.h>
#include <I18n.h>
#include <Languages.h>
#include <PlatformerLevelState.h>
#include <OverworldState.h>
#include <ProgressManager.h>
#include <KeypadManager.h>
#include "LevelDoneScreenState.h"


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMSpec LEVEL_DONE_SCREEN_STAGE_ST;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void LevelDoneScreenState::constructor()
{
	Base::constructor();
}

// class's destructor
void LevelDoneScreenState::destructor()
{
	// destroy base
	Base::destructor();
}

// state's enter
void LevelDoneScreenState::enter(void* owner __attribute__ ((unused)))
{
	// call base
	Base::enter(this, owner);

	// load stage
	GameState::loadStage(this, (StageSpec*)&LEVEL_DONE_SCREEN_STAGE_ST, NULL, true, false);

	// print stats
	LevelDoneScreenState::print(this);

	// disable user input
	Game::disableKeypad(Game::getInstance());

	// start clocks to start animations
	GameState::startClocks(this);

	// fade in screen
	Camera::startEffect(Camera::getInstance(), kHide);
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))LevelDoneScreenState::onFadeInComplete, // callback function
		Object::safeCast(this) // callback scope
	);
}

// state's exit
void LevelDoneScreenState::exit(void* owner __attribute__ ((unused)))
{
	// call base
	Base::exit(this, owner);

	// destroy the state
	delete this;
}

// print level stats
void LevelDoneScreenState::print()
{
	uint8 numberOfCollectedCoins = ProgressManager::getCurrentLevelNumberOfCollectedCoins(ProgressManager::getInstance());

	// "level completed/conquered"
	const char* strLevelDone = I18n::getText(I18n::getInstance(), kStringLevelDone);
	if(numberOfCollectedCoins == 64)
	{
		strLevelDone = I18n::getText(I18n::getInstance(), kStringLevelConquered);
	}
	FontSize strLevelDoneSize = Printing::getTextSize(Printing::getInstance(), strLevelDone, "AstonishSExt");
	uint8 strHeaderXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (strLevelDoneSize.x >> 1);
	Printing::text(Printing::getInstance(), strLevelDone, strHeaderXPos, 9, "AstonishSExt");

	// number of coins
	Printing::text(Printing::getInstance(), "00/64", 22, 13, "Platformer");
	uint8 numberPrintPos = (numberOfCollectedCoins < 10) ? 23 : 22;
	Printing::int32(Printing::getInstance(), numberOfCollectedCoins, numberPrintPos, 13, "Platformer");

	// print time
	Clock inGameClock = PlatformerLevelState::getClock(PlatformerLevelState::getInstance());
	Clock::print(inGameClock, 22, 15, "Platformer");

	// if new best time, print label (do not if first time beating level)
	uint32 bestTime = ProgressManager::getCurrentLevelBestTime(ProgressManager::getInstance());
	if(Clock::getTime(inGameClock) < bestTime)
	{
		Printing::text(Printing::getInstance(), I18n::getText(I18n::getInstance(), kStringNewBest), 22, 16, "Platformer");
	}
}

void LevelDoneScreenState::processUserInput(UserInput userInput)
{
	if(userInput.pressedKey)
	{
		// disable user input
		Game::disableKeypad(Game::getInstance());

		// fade out screen
		Brightness brightness = (Brightness){0, 0, 0};
		Camera::startEffect(Camera::getInstance(),
			kFadeTo, // effect type
			0, // initial delay (in ms)
			&brightness, // target brightness@
			__FADE_DELAY, // delay between fading steps (in ms)
			(void (*)(Object, Object))LevelDoneScreenState::onFadeOutComplete, // callback function
			Object::safeCast(this) // callback scope
		);
	}
}

// handle event
void LevelDoneScreenState::onFadeInComplete(Object eventFirer __attribute__ ((unused)))
{
	Game::enableKeypad(Game::getInstance());
}

// handle event
void LevelDoneScreenState::onFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	// switch to next screen
	Game::changeState(Game::getInstance(), GameState::safeCast(OverworldState::getInstance()));
}
