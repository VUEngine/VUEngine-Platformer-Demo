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

extern StageROMDef LEVEL_DONE_SCREEN_STAGE_ST;


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void LevelDoneScreenState::constructor(LevelDoneScreenState this);
void LevelDoneScreenState::print(LevelDoneScreenState this);
static void LevelDoneScreenState::onFadeInComplete(LevelDoneScreenState this, Object eventFirer);
static void LevelDoneScreenState::onFadeOutComplete(LevelDoneScreenState this, Object eventFirer);



//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void __attribute__ ((noinline)) LevelDoneScreenState::constructor(LevelDoneScreenState this)
{
	Base::constructor();
}

// class's destructor
void LevelDoneScreenState::destructor(LevelDoneScreenState this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
void LevelDoneScreenState::enter(LevelDoneScreenState this, void* owner __attribute__ ((unused)))
{
	// call base
	Base::enter(this, owner);

	// load stage
	GameState::loadStage(__SAFE_CAST(GameState, this), (StageDefinition*)&LEVEL_DONE_SCREEN_STAGE_ST, NULL, true);

	// print stats
	LevelDoneScreenState::print(this);

	// disable user input
	Game::disableKeypad(Game::getInstance());

	// start clocks to start animations
	GameState::startClocks(__SAFE_CAST(GameState, this));

	// fade in screen
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))LevelDoneScreenState::onFadeInComplete, // callback function
		__SAFE_CAST(Object, this) // callback scope
	);
}

// state's exit
void LevelDoneScreenState::exit(LevelDoneScreenState this, void* owner __attribute__ ((unused)))
{
	// call base
	Base::exit(this, owner);

	// destroy the state
	__DELETE(this);
}

// print level stats
void LevelDoneScreenState::print(LevelDoneScreenState this __attribute__ ((unused)))
{
	ASSERT(this, "LevelDoneScreenState::print: null this");

	u8 numberOfCollectedCoins = ProgressManager::getCurrentLevelNumberOfCollectedCoins(ProgressManager::getInstance());

	// "level completed/conquered"
	const char* strLevelDone = I18n::getText(I18n::getInstance(), STR_LEVEL_DONE);
	if(numberOfCollectedCoins == 64)
	{
		strLevelDone = I18n::getText(I18n::getInstance(), STR_LEVEL_CONQUERED);
	}
	FontSize strLevelDoneSize = Printing::getTextSize(Printing::getInstance(), strLevelDone, "GuiFont");
	u8 strHeaderXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (strLevelDoneSize.x >> 1);
	Printing::text(Printing::getInstance(), strLevelDone, strHeaderXPos, 9, "GuiFont");

	// number of coins
	Printing::text(Printing::getInstance(), "00/64", 22, 13, NULL);
	u8 numberPrintPos = (numberOfCollectedCoins < 10) ? 23 : 22;
	Printing::int(Printing::getInstance(), numberOfCollectedCoins, numberPrintPos, 13, NULL);

	// print time
	Clock inGameClock = PlatformerLevelState::getClock(PlatformerLevelState::getInstance());
	Clock::print(inGameClock, 22, 15, NULL);

	// if new best time, print label (do not if first time beating level)
	u32 bestTime = ProgressManager::getCurrentLevelBestTime(ProgressManager::getInstance());
	if(Clock::getTime(inGameClock) < bestTime)
	{
		Printing::text(Printing::getInstance(), I18n::getText(I18n::getInstance(), STR_NEW_BEST), 22, 16, NULL);
	}
}

void LevelDoneScreenState::processUserInput(LevelDoneScreenState this, UserInput userInput)
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
			&brightness, // target brightness
			__FADE_DELAY, // delay between fading steps (in ms)
			(void (*)(Object, Object))LevelDoneScreenState::onFadeOutComplete, // callback function
			__SAFE_CAST(Object, this) // callback scope
		);
	}
}

// handle event
static void LevelDoneScreenState::onFadeInComplete(LevelDoneScreenState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "LevelDoneScreenState::onFadeOutComplete: null this");

	Game::enableKeypad(Game::getInstance());
}

// handle event
static void LevelDoneScreenState::onFadeOutComplete(LevelDoneScreenState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "LevelDoneScreenState::onFadeOutComplete: null this");

	// switch to next screen
	Game::changeState(Game::getInstance(), __SAFE_CAST(GameState, OverworldState::getInstance()));
}
