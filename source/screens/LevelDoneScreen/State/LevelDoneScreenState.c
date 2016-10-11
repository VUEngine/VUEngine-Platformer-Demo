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

#include <Game.h>
#include <Screen.h>
#include <Printing.h>
#include <I18n.h>
#include <Languages.h>
#include <screens.h>
#include <macros.h>
#include <PlatformerLevelState.h>
#include <OverworldState.h>
#include <ProgressManager.h>
#include <KeyPadManager.h>
#include "LevelDoneScreenState.h"


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void LevelDoneScreenState_destructor(LevelDoneScreenState this);
static void LevelDoneScreenState_constructor(LevelDoneScreenState this);
static void LevelDoneScreenState_enter(LevelDoneScreenState this, void* owner);
static void LevelDoneScreenState_print(LevelDoneScreenState this);
static void LevelDoneScreenState_exit(LevelDoneScreenState this, void* owner);
static bool LevelDoneScreenState_processMessage(LevelDoneScreenState this, void* owner, Telegram telegram);
static void LevelDoneScreenState_onFadeInComplete(LevelDoneScreenState this, Object eventFirer);
static void LevelDoneScreenState_onFadeOutComplete(LevelDoneScreenState this, Object eventFirer);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(LevelDoneScreenState, GameState);
__SINGLETON_DYNAMIC(LevelDoneScreenState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void __attribute__ ((noinline)) LevelDoneScreenState_constructor(LevelDoneScreenState this)
{
	__CONSTRUCT_BASE(GameState);
}

// class's destructor
static void LevelDoneScreenState_destructor(LevelDoneScreenState this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
static void LevelDoneScreenState_enter(LevelDoneScreenState this, void* owner __attribute__ ((unused)))
{
	// call base
	GameState_enter(__SAFE_CAST(GameState, this), owner);

	// load stage
	GameState_loadStage(__SAFE_CAST(GameState, this), (StageDefinition*)&LEVEL_DONE_SCREEN_ST, NULL, true);

	// print stats
	LevelDoneScreenState_print(this);

	// disable user input
    Game_disableKeypad(Game_getInstance());

    // fade in screen
    Screen_startEffect(Screen_getInstance(),
        kFadeTo, // effect type
        0, // initial delay (in ms)
        NULL, // target brightness
        __FADE_DELAY, // delay between fading steps (in ms)
        (void (*)(Object, Object))LevelDoneScreenState_onFadeInComplete, // callback function
        __SAFE_CAST(Object, this) // callback scope
    );
}

// state's exit
static void LevelDoneScreenState_exit(LevelDoneScreenState this, void* owner __attribute__ ((unused)))
{
	// destroy the state
	__DELETE(this);
}

// print level stats
static void LevelDoneScreenState_print(LevelDoneScreenState this __attribute__ ((unused)))
{
	ASSERT(this, "LevelDoneScreenState::print: null this");

    u8 numberOfCollectedCoins = ProgressManager_getCurrentLevelNumberOfCollectedCoins(ProgressManager_getInstance());

    // "level completed/conquered"
    const char* strLevelDone = I18n_getText(I18n_getInstance(), STR_LEVEL_DONE);
    if(numberOfCollectedCoins == 64)
    {
        strLevelDone = I18n_getText(I18n_getInstance(), STR_LEVEL_CONQUERED);
    }
    Size strLevelDoneSize = Printing_getTextSize(Printing_getInstance(), strLevelDone, "GUIFont");
    u8 strHeaderXPos = (__SCREEN_WIDTH >> 4) - (strLevelDoneSize.x >> 1);
    Printing_text(Printing_getInstance(), strLevelDone, strHeaderXPos, 9, "GUIFont");

    // number of coins
    Printing_text(Printing_getInstance(), "x   /64", 22, 13, NULL);
    u8 numberPrintPos = (numberOfCollectedCoins < 10) ? 25 : 24;
    Printing_int(Printing_getInstance(), numberOfCollectedCoins, numberPrintPos, 13, NULL);
}

// state's handle message
static bool LevelDoneScreenState_processMessage(LevelDoneScreenState this __attribute__ ((unused)), void* owner __attribute__ ((unused)), Telegram telegram)
{
	// process message
	switch(Telegram_getMessage(telegram))
    {
		case kKeyPressed:
		{
		    // disable user input
            Game_disableKeypad(Game_getInstance());

		    // fade out screen
            Brightness brightness = (Brightness){0, 0, 0};
            Screen_startEffect(Screen_getInstance(),
                kFadeTo, // effect type
                0, // initial delay (in ms)
                &brightness, // target brightness
                __FADE_DELAY, // delay between fading steps (in ms)
                (void (*)(Object, Object))LevelDoneScreenState_onFadeOutComplete, // callback function
                __SAFE_CAST(Object, this) // callback scope
            );

			return true;
			break;
		}
	}

	return false;
}

// handle event
static void LevelDoneScreenState_onFadeInComplete(LevelDoneScreenState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "LevelDoneScreenState::onFadeOutComplete: null this");

    Game_enableKeypad(Game_getInstance());
}

// handle event
static void LevelDoneScreenState_onFadeOutComplete(LevelDoneScreenState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "LevelDoneScreenState::onFadeOutComplete: null this");

    // switch to next screen
    Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, OverworldState_getInstance()));
}
