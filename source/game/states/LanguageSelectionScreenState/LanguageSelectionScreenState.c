/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev
 * jorgech3@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <string.h>

#include <Game.h>
#include <Screen.h>
#include <Printing.h>
#include <MessageDispatcher.h>
#include <LanguageSelectionScreenState.h>
#include <VBJaEngineSplashScreenState.h>
#include <stages.h>
#include <macros.h>
#include <I18n.h>
#include <text.h>


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void LanguageSelectionScreenState_destructor(LanguageSelectionScreenState this);
static void LanguageSelectionScreenState_constructor(LanguageSelectionScreenState this);
static void LanguageSelectionScreenState_enter(LanguageSelectionScreenState this, void* owner);
static void LanguageSelectionScreenState_execute(LanguageSelectionScreenState this, void* owner);
static void LanguageSelectionScreenState_exit(LanguageSelectionScreenState this, void* owner);
static void LanguageSelectionScreenState_resume(LanguageSelectionScreenState this, void* owner);
static bool LanguageSelectionScreenState_handleMessage(LanguageSelectionScreenState this, void* owner, Telegram telegram);
static void LanguageSelectionScreenState_processInput(LanguageSelectionScreenState this, u16 pressedKey);
static void LanguageSelectionScreenState_print(LanguageSelectionScreenState this);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(LanguageSelectionScreenState);
__SINGLETON_DYNAMIC(LanguageSelectionScreenState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void LanguageSelectionScreenState_constructor(LanguageSelectionScreenState this)
{
    u8 activeLanguage = I18n_getActiveLanguage(I18n_getInstance());
	this->languageSelector = __NEW(OptionsSelector, __ARGUMENTS(1, 8, "\x10", kString));

	VirtualList languageNames = __NEW(VirtualList);

	int i = 0;
	for (;  i < I18n_getLanguageCount(I18n_getInstance()); i++)
	{
		I18n_setActiveLanguage(I18n_getInstance(), i);
		VirtualList_pushBack(languageNames, I18n_getActiveLanguageName(I18n_getInstance()));
	}

	I18n_setActiveLanguage(I18n_getInstance(), activeLanguage);

    OptionsSelector_setOptions(this->languageSelector, languageNames);
	__DELETE(languageNames);

	__CONSTRUCT_BASE(GameState);
}

// class's destructor
static void LanguageSelectionScreenState_destructor(LanguageSelectionScreenState this)
{
	if (this->languageSelector)
	{
		__DELETE(this->languageSelector);
	}

	// destroy base
	__SINGLETON_DESTROY(GameState);
}

// state's enter
static void LanguageSelectionScreenState_enter(LanguageSelectionScreenState this, void* owner)
{
	GameState_loadStage((GameState)this, (StageDefinition*)&EMPTY_ST, true, true);

	LanguageSelectionScreenState_print(this);
	
	Screen_FXFadeIn(Screen_getInstance(), FADE_DELAY);
}

// state's execute
static void LanguageSelectionScreenState_execute(LanguageSelectionScreenState this, void* owner)
{
 	// call base
	GameState_execute((GameState)this, owner);
}

// state's exit
static void LanguageSelectionScreenState_exit(LanguageSelectionScreenState this, void* owner)
{
	Screen_FXFadeOut(Screen_getInstance(), FADE_DELAY);

	// destroy the state
	__DELETE(this);
}

// state's resume
static void LanguageSelectionScreenState_resume(LanguageSelectionScreenState this, void* owner)
{
	GameState_resume((GameState)this, owner);
	
#ifdef __DEBUG_TOOLS
	if (!Game_isExitingSpecialMode(Game_getInstance()))
	{
#endif
#ifdef __STAGE_EDITOR
	if (!Game_isExitingSpecialMode(Game_getInstance()))
	{
#endif
#ifdef __ANIMATION_EDITOR
	if (!Game_isExitingSpecialMode(Game_getInstance()))
	{
#endif
	
	// make a fade in
	Screen_FXFadeIn(Screen_getInstance(), FADE_DELAY >> 1);

#ifdef __DEBUG_TOOLS
	}
#endif
#ifdef __STAGE_EDITOR
	}
#endif
#ifdef __ANIMATION_EDITOR
	}
#endif
	
	LanguageSelectionScreenState_print(this);
}

// state's on message
static bool LanguageSelectionScreenState_handleMessage(LanguageSelectionScreenState this, void* owner, Telegram telegram)
{
	switch (Telegram_getMessage(telegram))
	{
		case kKeyPressed:
		{
            u16 pressedKey = *((u16*)Telegram_getExtraInfo(telegram));

            LanguageSelectionScreenState_processInput(LanguageSelectionScreenState_getInstance(), pressedKey);
        }
        break;
	}

	return false;
}

static void LanguageSelectionScreenState_processInput(LanguageSelectionScreenState this, u16 pressedKey)
{
	if (pressedKey & K_LU)
	{
		OptionsSelector_selectPrevious(this->languageSelector);
	}
	else if (pressedKey & K_LD)
	{
		OptionsSelector_selectNext(this->languageSelector);
	}
	else if (pressedKey & K_A)
	{
	    I18n_setActiveLanguage(I18n_getInstance(), OptionsSelector_getSelectedOption(this->languageSelector));
	    Game_changeState(Game_getInstance(), (GameState)VBJaEngineSplashScreenState_getInstance());
	}
}

static void LanguageSelectionScreenState_print(LanguageSelectionScreenState this)
{
    char* strHeader = I18n_getText(I18n_getInstance(), STR_LANGUAGE_SELECT);
    u8 strHeaderXPos = (48 - strlen(strHeader)) >> 1;

    Printing_text(Printing_getInstance(), strHeader, strHeaderXPos, 8, "GUIFont");

	OptionsSelector_showOptions(this->languageSelector, strHeaderXPos, 11);
}
