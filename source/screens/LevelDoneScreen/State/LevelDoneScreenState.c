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
#include "LevelDoneScreenState.h"


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void LevelDoneScreenState_destructor(LevelDoneScreenState this);
static void LevelDoneScreenState_constructor(LevelDoneScreenState this);
static void LevelDoneScreenState_enter(LevelDoneScreenState this, void* owner);
static void LevelDoneScreenState_print(LevelDoneScreenState this);
static void LevelDoneScreenState_exit(LevelDoneScreenState this, void* owner);
static bool LevelDoneScreenState_handleMessage(LevelDoneScreenState this, void* owner, Telegram telegram);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(LevelDoneScreenState, GameState);
__SINGLETON_DYNAMIC(LevelDoneScreenState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void LevelDoneScreenState_constructor(LevelDoneScreenState this)
{
	__CONSTRUCT_BASE();
}

// class's destructor
static void LevelDoneScreenState_destructor(LevelDoneScreenState this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
static void LevelDoneScreenState_enter(LevelDoneScreenState this, void* owner)
{
	// load stage
	GameState_loadStage(__SAFE_CAST(GameState, this), (StageDefinition*)&LEVEL_DONE_SCREEN_ST, NULL, true);

	LevelDoneScreenState_print(this);

	ProgressManager_reset(ProgressManager_getInstance());

    Game_enableKeypad(Game_getInstance());

    Screen_startEffect(Screen_getInstance(), kFadeIn, FADE_DELAY);
}

// state's exit
static void LevelDoneScreenState_exit(LevelDoneScreenState this, void* owner)
{
	// make a fade out
	Screen_startEffect(Screen_getInstance(), kFadeOut, FADE_DELAY);

	// destroy the state
	__DELETE(this);
}

// print level stats
static void LevelDoneScreenState_print(LevelDoneScreenState this)
{
	ASSERT(this, "LevelDoneScreenState::print: null this");

    u8 numberOfCollectedCoins = ProgressManager_getNumberOfCollectedCoins(ProgressManager_getInstance());

    // "level completed/conquered"
    char* strLevelDone = I18n_getText(I18n_getInstance(), STR_LEVEL_DONE);
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
static bool LevelDoneScreenState_handleMessage(LevelDoneScreenState this, void* owner, Telegram telegram)
{
	// process message
	switch(Telegram_getMessage(telegram))
    {
		case kKeyPressed:

            Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, OverworldState_getInstance()));
			return true;
			break;
	}

	return false;
}