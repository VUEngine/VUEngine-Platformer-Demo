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
#include <Utilities.h>
#include <Languages.h>
#include <screens.h>
#include <macros.h>
#include <SplashScreenState.h>
#include <AutoPauseSelectScreenState.h>
#include <LangSelectScreenState.h>
#include <TitleScreenState.h>
#include <KeyPadManager.h>
#include "OptionsScreenState.h"


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef EMPTY_ST;


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void OptionsScreenState_destructor(OptionsScreenState this);
static void OptionsScreenState_constructor(OptionsScreenState this);
static void OptionsScreenState_enter(OptionsScreenState this, void* owner);
static void OptionsScreenState_print(OptionsScreenState this);
static void OptionsScreenState_exit(OptionsScreenState this, void* owner);
static bool OptionsScreenState_processMessage(OptionsScreenState this, void* owner, Telegram telegram);
static void OptionsScreenState_onFadeInComplete(OptionsScreenState this, Object eventFirer);
static void OptionsScreenState_onExitFadeOutComplete(OptionsScreenState this, Object eventFirer);
static void OptionsScreenState_onOptionSelectedFadeOutComplete(OptionsScreenState this, Object eventFirer);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(OptionsScreenState, GameState);
__SINGLETON_DYNAMIC(OptionsScreenState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void __attribute__ ((noinline)) OptionsScreenState_constructor(OptionsScreenState this)
{
	__CONSTRUCT_BASE(GameState);

	// init members
	this->optionsSelector = NULL;
	OptionsScreenState_setNextState(this, __SAFE_CAST(GameState, TitleScreenState_getInstance()));
}

// class's destructor
static void OptionsScreenState_destructor(OptionsScreenState this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
static void OptionsScreenState_enter(OptionsScreenState this, void* owner __attribute__ ((unused)))
{
	// call base
	GameState_enter(__SAFE_CAST(GameState, this), owner);

	// load stage
    GameState_loadStage(__SAFE_CAST(GameState, this), (StageDefinition*)&EMPTY_ST, NULL, true);

	// print options
	OptionsScreenState_print(this);

	// disable user input
    Game_disableKeypad(Game_getInstance());

    // fade in screen
    Screen_startEffect(Screen_getInstance(),
        kFadeTo, // effect type
        0, // initial delay (in ms)
        NULL, // target brightness
        __FADE_DELAY, // delay between fading steps (in ms)
        (void (*)(Object, Object))OptionsScreenState_onFadeInComplete, // callback function
        __SAFE_CAST(Object, this) // callback scope
    );
}

// state's exit
static void OptionsScreenState_exit(OptionsScreenState this, void* owner __attribute__ ((unused)))
{
	// call base
	GameState_exit(__SAFE_CAST(GameState, this), owner);

	// destroy the state
	__DELETE(this);
}

// set next state
void OptionsScreenState_setNextState(OptionsScreenState this, GameState nextState)
{
    this->nextState = nextState;
}

// print level stats
static void OptionsScreenState_print(OptionsScreenState this __attribute__ ((unused)))
{
	ASSERT(this, "OptionsScreenState::print: null this");

	// title
    const char* strOptionsTitle = I18n_getText(I18n_getInstance(), STR_OPTIONS);
    const char* strOptionsTitleFont = "LargeFont";
    Size strOptionsTextSize = Printing_getTextSize(Printing_getInstance(), strOptionsTitle, strOptionsTitleFont);
    Printing_text(
        Printing_getInstance(),
        Utilities_toUppercase(strOptionsTitle),
        ((__SCREEN_WIDTH >> 3) - strOptionsTextSize.x) >> 1,
        8,
        strOptionsTitleFont
    );

	// menu
    this->optionsSelector = __NEW(OptionsSelector, 1, 2, "\xB", kString, NULL);
	VirtualList options = __NEW(VirtualList);

	VirtualList_pushBack(options, I18n_getText(I18n_getInstance(), STR_AUTOMATIC_PAUSE));
	VirtualList_pushBack(options, I18n_getText(I18n_getInstance(), STR_LANGUAGE));

	OptionsSelector_setOptions(this->optionsSelector, options);
	__DELETE(options);

	OptionsSelector_printOptions(
		this->optionsSelector,
        ((__SCREEN_WIDTH >> 3) - strOptionsTextSize.x) >> 1,
		11
	);

    // buttons
    const char* strSelect = I18n_getText(I18n_getInstance(), STR_SELECT);
    Size strSelectSize = Printing_getTextSize(Printing_getInstance(), strSelect, NULL);
    const char* strBack = I18n_getText(I18n_getInstance(), STR_BACK);

    u8 strSelectXPos = ((__SCREEN_WIDTH >> 3) - strOptionsTextSize.x) >> 1;
    u8 strBackXPos = strSelectXPos + strSelectSize.x + 2;

    Printing_text(Printing_getInstance(), "\x13", strSelectXPos, 15, NULL);
    Printing_text(Printing_getInstance(), strSelect, strSelectXPos + 1, 15, NULL);
    Printing_text(Printing_getInstance(), "\x14", strBackXPos, 15, NULL);
    Printing_text(Printing_getInstance(), strBack, strBackXPos + 1, 15, NULL);
}

// state's handle message
static bool OptionsScreenState_processMessage(OptionsScreenState this __attribute__ ((unused)), void* owner __attribute__ ((unused)), Telegram telegram)
{
	// process message
	switch(Telegram_getMessage(telegram))
    {
		case kKeyPressed:
		{
            u32 pressedKey = *((u32*)Telegram_getExtraInfo(telegram));

			if((pressedKey & K_A) || (pressedKey & K_STA))
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
                    (void (*)(Object, Object))OptionsScreenState_onOptionSelectedFadeOutComplete, // callback function
                    __SAFE_CAST(Object, this) // callback scope
                );

                break;
            }
			else if((pressedKey & K_B) || (pressedKey & K_SEL))
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
                    (void (*)(Object, Object))OptionsScreenState_onExitFadeOutComplete, // callback function
                    __SAFE_CAST(Object, this) // callback scope
                );
            }
            else if((pressedKey & K_LU) || (pressedKey & K_RU))
            {
                OptionsSelector_selectPrevious(this->optionsSelector);
            }
            else if((pressedKey & K_LD) || (pressedKey & K_RD))
            {
                OptionsSelector_selectNext(this->optionsSelector);
            }

            return true;
            break;
		}
	}

	return false;
}

// handle event
static void OptionsScreenState_onFadeInComplete(OptionsScreenState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "OptionsScreenState::onOptionSelectedFadeOutComplete: null this");

    Game_enableKeypad(Game_getInstance());
}

static void OptionsScreenState_onExitFadeOutComplete(OptionsScreenState this, Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "OptionsScreenState::onExitFadeOutComplete: null this");

    // switch to next screen
    Game_changeState(Game_getInstance(), this->nextState);
}

static void OptionsScreenState_onOptionSelectedFadeOutComplete(OptionsScreenState this, Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "OptionsScreenState::onOptionSelectedFadeOutComplete: null this");

    // switch state according to selection
    int selectedOption = OptionsSelector_getSelectedOption(this->optionsSelector);
    switch(selectedOption)
    {
        case kOptionsScreenOptionAutoPauseSelectScreen:

	        SplashScreenState_setNextState(__SAFE_CAST(SplashScreenState, AutoPauseSelectScreenState_getInstance()), __SAFE_CAST(GameState, this));
            Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, AutoPauseSelectScreenState_getInstance()));
            break;

        case kOptionsScreenOptionLanguage:

	        SplashScreenState_setNextState(__SAFE_CAST(SplashScreenState, LangSelectScreenState_getInstance()), __SAFE_CAST(GameState, this));
            Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, LangSelectScreenState_getInstance()));
            break;
    }
}
