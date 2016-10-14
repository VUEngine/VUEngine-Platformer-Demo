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
#include <screens.h>
#include <AutoPauseScreenState.h>
#include <KeyPadManager.h>
#include <Languages.h>
#include <Utilities.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void AutoPauseScreenState_destructor(AutoPauseScreenState this);
static void AutoPauseScreenState_constructor(AutoPauseScreenState this);
static void AutoPauseScreenState_enter(AutoPauseScreenState this, void* owner);
static void AutoPauseScreenState_exit(AutoPauseScreenState this, void* owner);
static bool AutoPauseScreenState_processMessage(AutoPauseScreenState this, void* owner, Telegram telegram);
static void AutoPauseScreenState_onFadeOutComplete(AutoPauseScreenState this, Object eventFirer);
static void AutoPauseScreenState_onFadeInComplete(AutoPauseScreenState this, Object eventFirer);


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
static void AutoPauseScreenState_enter(AutoPauseScreenState this, void* owner __attribute__ ((unused)))
{
	// load stage
	GameState_loadStage(__SAFE_CAST(GameState, this), (StageDefinition*)&PAUSE_SCREEN_ST, NULL, true);

    // print text
    const char* strAutomaticPauseTitle = I18n_getText(I18n_getInstance(), STR_AUTOMATIC_PAUSE);
    const char* strAutomaticPauseTitleFont = "LargeFont";
    const char* strAutomaticPauseText = I18n_getText(I18n_getInstance(), STR_AUTOMATIC_PAUSE_TEXT);
    Size strAutomaticPauseSize = Printing_getTextSize(Printing_getInstance(), strAutomaticPauseTitle, strAutomaticPauseTitleFont);
    Size strAutomaticPauseTextSize = Printing_getTextSize(Printing_getInstance(), strAutomaticPauseText, NULL);

    u8 strHeaderXPos = ((__SCREEN_WIDTH >> 4) - (strAutomaticPauseSize.x >> 1));
    Printing_text(
    	Printing_getInstance(),
    	Utilities_toUppercase(strAutomaticPauseTitle),
    	strHeaderXPos,
    	14,
    	strAutomaticPauseTitleFont
	);

    u8 strTextXPos = (__SCREEN_WIDTH >> 4) - (strAutomaticPauseTextSize.x >> 1);
    Printing_text(Printing_getInstance(), strAutomaticPauseText, strTextXPos, 15 + strAutomaticPauseSize.y, NULL);

	// disable user input
    Game_disableKeypad(Game_getInstance());

	// start clocks to start animations
	GameState_startClocks(__SAFE_CAST(GameState, this));

    // fade in screen
    Screen_startEffect(Screen_getInstance(),
        kFadeTo, // effect type
        0, // initial delay (in ms)
        NULL, // target brightness
        __FADE_DELAY, // delay between fading steps (in ms)
        (void (*)(Object, Object))AutoPauseScreenState_onFadeInComplete, // callback function
        __SAFE_CAST(Object, this) // callback scope
    );
}

// state's exit
static void AutoPauseScreenState_exit(AutoPauseScreenState this __attribute__ ((unused)), void* owner __attribute__ ((unused)))
{
	// call base
	GameState_exit(__SAFE_CAST(GameState, this), owner);
}

// state's handle message
static bool AutoPauseScreenState_processMessage(AutoPauseScreenState this, void* owner __attribute__ ((unused)), Telegram telegram)
{
	// process message
	switch(Telegram_getMessage(telegram))
    {
		case kKeyPressed:
			{
				u32 pressedKey = *((u32*)Telegram_getExtraInfo(telegram));

				if(K_STA & pressedKey)
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
						(void (*)(Object, Object))AutoPauseScreenState_onFadeOutComplete, // callback function
						__SAFE_CAST(Object, this) // callback scope
					);
				}
			}
			return true;
			break;
	}

	return false;
}

// handle event
static void AutoPauseScreenState_onFadeInComplete(AutoPauseScreenState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "AutoPauseScreenState::onFadeOutComplete: null this");

    Game_enableKeypad(Game_getInstance());
}

// handle event
static void AutoPauseScreenState_onFadeOutComplete(AutoPauseScreenState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "AutoPauseScreenState::onFadeOutComplete: null this");

	// re-enable user input
	Game_enableKeypad(Game_getInstance());

	// resume game
    Game_unpause(Game_getInstance(), __SAFE_CAST(GameState, this));
}
