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
#include <MessageDispatcher.h>
#include <PhysicalWorld.h>
#include <I18n.h>
#include <AutoPauseScreenState.h>
#include <KeyPadManager.h>
#include <Languages.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef EMPTY_ST;


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void AutoPauseScreenState_destructor(AutoPauseScreenState this);
static void AutoPauseScreenState_constructor(AutoPauseScreenState this);
static void AutoPauseScreenState_enter(AutoPauseScreenState this, void* owner);
static void AutoPauseScreenState_exit(AutoPauseScreenState this, void* owner);
static bool AutoPauseScreenState_processMessage(AutoPauseScreenState this, void* owner, Telegram telegram);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(AutoPauseScreenState, GameState);
__SINGLETON(AutoPauseScreenState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void __attribute__ ((noinline)) AutoPauseScreenState_constructor(AutoPauseScreenState this)
{
	__CONSTRUCT_BASE(GameState);
}

// class's destructor
static void AutoPauseScreenState_destructor(AutoPauseScreenState this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
static void AutoPauseScreenState_enter(AutoPauseScreenState this, void* owner)
{
	// load stage
	GameState_loadStage(__SAFE_CAST(GameState, this), (StageDefinition*)&EMPTY_ST, NULL, true);

    // print text
    char* strAutomaticPause = I18n_getText(I18n_getInstance(), STR_AUTOMATIC_PAUSE);
    char* strAutomaticPauseText = I18n_getText(I18n_getInstance(), STR_AUTOMATIC_PAUSE_TEXT);
    Size strAutomaticPauseSize = Printing_getTextSize(Printing_getInstance(), strAutomaticPause, "GUIFont");
    Size strAutomaticPauseTextSize = Printing_getTextSize(Printing_getInstance(), strAutomaticPauseText, NULL);

    u8 strHeaderXPos = ((__SCREEN_WIDTH >> 4) - (strAutomaticPauseSize.x >> 1));
    Printing_text(Printing_getInstance(), strAutomaticPause, strHeaderXPos, 10, "GUIFont");

    u8 strTextXPos = (__SCREEN_WIDTH >> 4) - (strAutomaticPauseTextSize.x >> 1);
    Printing_text(Printing_getInstance(), strAutomaticPauseText, strTextXPos, 11 + strAutomaticPauseSize.y, NULL);

    Screen_startEffect(Screen_getInstance(), kFadeIn, FADE_DELAY);
}

// state's exit
static void AutoPauseScreenState_exit(AutoPauseScreenState this, void* owner)
{
	// make a fade out
	Screen_startEffect(Screen_getInstance(), kFadeOut, FADE_DELAY);
}

// state's handle message
static bool AutoPauseScreenState_processMessage(AutoPauseScreenState this, void* owner, Telegram telegram)
{
	// process message
	switch(Telegram_getMessage(telegram))
    {
		case kKeyPressed:
			{
				u16 pressedKey = *((u16*)Telegram_getExtraInfo(telegram));

				if(K_STA & pressedKey)
				{
					Game_unpause(Game_getInstance(), __SAFE_CAST(GameState, this));
				}
			}
			return true;
			break;
	}

	return false;
}
