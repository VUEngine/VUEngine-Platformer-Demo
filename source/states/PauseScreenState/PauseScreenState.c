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
#include <I18n.h>
#include <PhysicalWorld.h>
#include <PauseScreenState.h>
#include <Hero.h>
#include <macros.h>
#include <OverworldState.h>
#include <OptionsScreenState.h>
#include <PlatformerLevelState.h>
#include <Languages.h>
#include <KeyPadManager.h>
#include <Utilities.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef PAUSE_SCREEN_ST;


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void PauseScreenState_destructor(PauseScreenState this);
static void PauseScreenState_constructor(PauseScreenState this);
static void PauseScreenState_enter(PauseScreenState this, void* owner);
static void PauseScreenState_exit(PauseScreenState this, void* owner);
static bool PauseScreenState_processMessage(PauseScreenState this, void* owner, Telegram telegram);
static void PauseScreenState_onFadeInComplete(PauseScreenState this, Object eventFirer);
static void PauseScreenState_onFadeOutComplete(PauseScreenState this, Object eventFirer);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(PauseScreenState, GameState);
__SINGLETON_DYNAMIC(PauseScreenState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void __attribute__ ((noinline)) PauseScreenState_constructor(PauseScreenState this)
{
	__CONSTRUCT_BASE(GameState);

	// init members
	this->mode = kPauseScreenModeShowOptions;
	this->optionsSelector = __NEW(OptionsSelector, 1, 3, NULL);
}

// class's destructor
static void PauseScreenState_destructor(PauseScreenState this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
static void PauseScreenState_enter(PauseScreenState this, void* owner __attribute__ ((unused)))
{
	// call base
	GameState_enter(__SAFE_CAST(GameState, this), owner);

	// load stage
	GameState_loadStage(__SAFE_CAST(GameState, this), (StageDefinition*)&PAUSE_SCREEN_ST, NULL, true);

	// show up level after a little delay
	MessageDispatcher_dispatchMessage(1, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kLevelSetUp, NULL);

	// print pause text
	const char* strPause = I18n_getText(I18n_getInstance(), STR_PAUSE);
	const char* strPauseFont = "LargeFont";
	Size strPauseSize = Printing_getTextSize(Printing_getInstance(), strPause, strPauseFont);
	Printing_text(
		Printing_getInstance(),
		Utilities_toUppercase(strPause),
		(((__SCREEN_WIDTH >> 3) - strPauseSize.x) >> 1),
		14,
		strPauseFont
	);

	// show menu
	VirtualList options = __NEW(VirtualList);
    Option* option = NULL;

    option = __NEW_BASIC(Option);
    option->value = (char*)I18n_getText(I18n_getInstance(), STR_CONTINUE);
    option->type = kString;
    option->callback = NULL;
    option->callbackScope = NULL;
    VirtualList_pushBack(options, option);

    option = __NEW_BASIC(Option);
    option->value = (char*)I18n_getText(I18n_getInstance(), STR_OPTIONS);
    option->type = kString;
    option->callback = NULL;
    option->callbackScope = NULL;
    VirtualList_pushBack(options, option);

    option = __NEW_BASIC(Option);
    option->value = (char*)I18n_getText(I18n_getInstance(), STR_QUIT_LEVEL);
    option->type = kString;
    option->callback = NULL;
    option->callbackScope = NULL;
    VirtualList_pushBack(options, option);

	OptionsSelector_setOptions(this->optionsSelector, options);
	__DELETE(options);

	OptionsSelector_printOptions(
		this->optionsSelector,
		(((__SCREEN_WIDTH >> 3) - strPauseSize.x) >> 1) - 1,
		17
	);

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
		(void (*)(Object, Object))PauseScreenState_onFadeInComplete, // callback function
		__SAFE_CAST(Object, this) // callback scope
	);
}

// state's exit
static void PauseScreenState_exit(PauseScreenState this, void* owner __attribute__ ((unused)))
{
	// destroy the state
	__DELETE(this);
}

// state's handle message
static bool PauseScreenState_processMessage(PauseScreenState this, void* owner __attribute__ ((unused)), Telegram telegram)
{
	// process message
	switch(Telegram_getMessage(telegram))
	{
		case kKeyPressed:
			{
				u32 pressedKey = *((u32*)Telegram_getExtraInfo(telegram));

				if((K_STA & pressedKey) || (K_A & pressedKey))
				{
					if(this->mode == kPauseScreenModeShowOptions)
					{
						int selectedOption = OptionsSelector_getSelectedOption(this->optionsSelector);

						switch(selectedOption)
						{
							case kPauseScreenOptionContinue:
							case kPauseScreenOptionOptions:

								// disable user input
								Game_disableKeypad(Game_getInstance());

								// fade out screen
								Brightness brightness = (Brightness){0, 0, 0};
								Screen_startEffect(Screen_getInstance(),
									kFadeTo, // effect type
									0, // initial delay (in ms)
									&brightness, // target brightness
									__FADE_DELAY, // delay between fading steps (in ms)
									(void (*)(Object, Object))PauseScreenState_onFadeOutComplete, // callback function
									__SAFE_CAST(Object, this) // callback scope
								);

								break;

							case kPauseScreenOptionQuitLevel:
							{
								// print confirmation message
								const char* strYes = I18n_getText(I18n_getInstance(), STR_YES);
								Size strYesSize = Printing_getTextSize(Printing_getInstance(), strYes, NULL);
								const char* strNo = I18n_getText(I18n_getInstance(), STR_NO);
								const char* strAreYouSure = I18n_getText(I18n_getInstance(), STR_ARE_YOU_SURE);
								const char* strPause = I18n_getText(I18n_getInstance(), STR_PAUSE);
								const char* strPauseFont = "LargeFont";
								Size strPauseSize = Printing_getTextSize(Printing_getInstance(), strPause, strPauseFont);

								u8 strXPos = ((__SCREEN_WIDTH >> 3) - strPauseSize.x) >> 1;
								u8 strNoXPos = strXPos + strYesSize.x + 2;

								Printing_text(Printing_getInstance(), strAreYouSure, strXPos, 21, NULL);
								Printing_text(Printing_getInstance(), __CHAR_A_BUTTON, strXPos, 22, NULL);
								Printing_text(Printing_getInstance(), strYes, strXPos + 1, 22, NULL);
								Printing_text(Printing_getInstance(), __CHAR_B_BUTTON, strNoXPos, 22, NULL);
								Printing_text(Printing_getInstance(), strNo, strNoXPos + 1, 22, NULL);

								// set mode accordingly
								this->mode = kPauseScreenModeShowConfirmQuit;
								break;
							}
						}
					}
					else if(this->mode == kPauseScreenModeShowConfirmQuit)
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
							(void (*)(Object, Object))PauseScreenState_onFadeOutComplete, // callback function
							__SAFE_CAST(Object, this) // callback scope
						);
					}
				}
				else if((this->mode == kPauseScreenModeShowConfirmQuit) && (pressedKey & K_B))
				{
					// remove confirmation message
					Printing_text(Printing_getInstance(), "                                                ", 0, 21, NULL);
					Printing_text(Printing_getInstance(), "                                                ", 0, 22, NULL);

					// set mode back to main menu
					this->mode = kPauseScreenModeShowOptions;
				}
				else if((this->mode == kPauseScreenModeShowOptions) && ((pressedKey & K_LU) || (pressedKey & K_RU)))
				{
					OptionsSelector_selectPrevious(this->optionsSelector);
				}
				else if((this->mode == kPauseScreenModeShowOptions) && ((pressedKey & K_LD) || (pressedKey & K_RD)))
				{
					OptionsSelector_selectNext(this->optionsSelector);
				}
			}
			return true;
			break;
	}

	return false;
}

// handle event
static void PauseScreenState_onFadeInComplete(PauseScreenState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "PauseScreenState::onFadeInComplete: null this");

	Game_enableKeypad(Game_getInstance());
}

// handle event
static void PauseScreenState_onFadeOutComplete(PauseScreenState this, Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "PauseScreenState::onFadeOutComplete: null this");

	// re-enable user input
	Game_enableKeypad(Game_getInstance());

	// switch state according to selection
	int selectedOption = OptionsSelector_getSelectedOption(this->optionsSelector);
	switch(selectedOption)
	{
		case kPauseScreenOptionContinue:

			// resume game
			Game_unpause(Game_getInstance(), __SAFE_CAST(GameState, this));
			break;

		case kPauseScreenOptionOptions:

			// switch to options state
			OptionsScreenState_setNextState(OptionsScreenState_getInstance(), __SAFE_CAST(GameState, this));
			Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, OptionsScreenState_getInstance()));
			break;

		case kPauseScreenOptionQuitLevel:

			// switch to overworld after deleting paused game state
    		Game_cleanAndChangeState(Game_getInstance(), __SAFE_CAST(GameState, OverworldState_getInstance()));

			break;
	}
}
