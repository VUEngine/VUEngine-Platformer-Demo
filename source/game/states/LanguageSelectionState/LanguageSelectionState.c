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
#include <LanguageSelectionState.h>
#include <stages.h>
#include <macros.h>
#include <I18n.h>
#include <text.h>


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void LanguageSelectionState_destructor(LanguageSelectionState this);
static void LanguageSelectionState_constructor(LanguageSelectionState this);
static void LanguageSelectionState_enter(LanguageSelectionState this, void* owner);
static void LanguageSelectionState_execute(LanguageSelectionState this, void* owner);
static void LanguageSelectionState_exit(LanguageSelectionState this, void* owner);
static bool LanguageSelectionState_handleMessage(LanguageSelectionState this, void* owner, Telegram telegram);
static void LanguageSelectionState_processInput(LanguageSelectionState this, u16 pressedKey);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(LanguageSelectionState);
__SINGLETON_DYNAMIC(LanguageSelectionState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void LanguageSelectionState_constructor(LanguageSelectionState this)
{
	this->languageSelector = __NEW(OptionsSelector, __ARGUMENTS(1, 8, "\x10", kString));

	VirtualList languageNames = __NEW(VirtualList);

	int i = 0;
	for (;  i < I18n_getLanguageCount(I18n_getInstance()); i++)
	{
		I18n_setLanguage(I18n_getInstance(), i);
		VirtualList_pushBack(languageNames, I18n_getActiveLanguageName(I18n_getInstance()));
	}

    OptionsSelector_setOptions(this->languageSelector, languageNames);
	__DELETE(languageNames);

	__CONSTRUCT_BASE(GameState);
}

// class's destructor
static void LanguageSelectionState_destructor(LanguageSelectionState this)
{
	if (this->languageSelector)
	{
		__DELETE(this->languageSelector);
	}

	// destroy base
	__SINGLETON_DESTROY(GameState);
}

// state's enter
static void LanguageSelectionState_enter(LanguageSelectionState this, void* owner)
{
	GameState_loadStage((GameState)this, (StageDefinition*)&EMPTY_ST, true, true);

    char* strHeader = I18n_getText(I18n_getInstance(), STR_LANGUAGE_SELECT);
    u8 strHeaderXPos = (48 - strlen(strHeader)) >> 1;

    Printing_text(Printing_getInstance(), strHeader, strHeaderXPos, 8, "GUIFont");

	OptionsSelector_showOptions(this->languageSelector, strHeaderXPos, 11);

	Screen_FXFadeIn(Screen_getInstance(), FADE_DELAY);
}

// state's execute
static void LanguageSelectionState_execute(LanguageSelectionState this, void* owner)
{
 	// call base
	GameState_execute((GameState)this, owner);
}

// state's exit
static void LanguageSelectionState_exit(LanguageSelectionState this, void* owner)
{
	Screen_FXFadeOut(Screen_getInstance(), FADE_DELAY);

	// destroy the state
	__DELETE(this);
}

// state's on message
static bool LanguageSelectionState_handleMessage(LanguageSelectionState this, void* owner, Telegram telegram)
{
	switch (Telegram_getMessage(telegram))
	{
		case kKeyPressed:
		{
            u16 pressedKey = *((u16*)Telegram_getExtraInfo(telegram));

            LanguageSelectionState_processInput(LanguageSelectionState_getInstance(), pressedKey);
        }
        break;
	}

	return false;
}

static void LanguageSelectionState_processInput(LanguageSelectionState this, u16 pressedKey)
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
	    I18n_setLanguage(I18n_getInstance(), OptionsSelector_getSelectedOption(this->languageSelector));
	    Game_changeState(Game_getInstance(), (State)TitleScreenState_getInstance());
	}
}