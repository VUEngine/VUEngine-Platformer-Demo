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
#include <AutomaticPauseSelectionScreenState.h>
#include <AutomaticPauseScreenState.h>
#include <LanguageSelectionScreenState.h>
#include <stages.h>
#include <macros.h>
#include <I18n.h>
#include <lang.h>


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void AutomaticPauseSelectionScreenState_destructor(AutomaticPauseSelectionScreenState this);
static void AutomaticPauseSelectionScreenState_constructor(AutomaticPauseSelectionScreenState this);
static void AutomaticPauseSelectionScreenState_enter(AutomaticPauseSelectionScreenState this, void* owner);
static void AutomaticPauseSelectionScreenState_execute(AutomaticPauseSelectionScreenState this, void* owner);
static void AutomaticPauseSelectionScreenState_exit(AutomaticPauseSelectionScreenState this, void* owner);
static void AutomaticPauseSelectionScreenState_resume(AutomaticPauseSelectionScreenState this, void* owner);
static bool AutomaticPauseSelectionScreenState_handleMessage(AutomaticPauseSelectionScreenState this, void* owner, Telegram telegram);
static void AutomaticPauseSelectionScreenState_print(AutomaticPauseSelectionScreenState this);
static void AutomaticPauseSelectionScreenState_renderSelection(AutomaticPauseSelectionScreenState this);
static void AutomaticPauseSelectionScreenState_processInput(AutomaticPauseSelectionScreenState this, u16 pressedKey);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(AutomaticPauseSelectionScreenState);
__SINGLETON_DYNAMIC(AutomaticPauseSelectionScreenState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void AutomaticPauseSelectionScreenState_constructor(AutomaticPauseSelectionScreenState this)
{
	AutomaticPauseSelectionScreenState_setNextstate(this, (GameState)LanguageSelectionScreenState_getInstance());
	this->stageDefinition = (StageDefinition*)&EMPTY_ST;
    this->selection = true;

	__CONSTRUCT_BASE(GameState);
}

// class's destructor
static void AutomaticPauseSelectionScreenState_destructor(AutomaticPauseSelectionScreenState this)
{	// destroy base
	__SINGLETON_DESTROY(GameState);
}

// state's enter
static void AutomaticPauseSelectionScreenState_enter(AutomaticPauseSelectionScreenState this, void* owner)
{
	GameState_loadStage((GameState)this, this->stageDefinition, true, true);

	AutomaticPauseSelectionScreenState_print(this);

	Screen_FXFadeIn(Screen_getInstance(), FADE_DELAY);
}

// state's execute
static void AutomaticPauseSelectionScreenState_execute(AutomaticPauseSelectionScreenState this, void* owner)
{
 	// call base
	GameState_execute((GameState)this, owner);
}

// state's exit
static void AutomaticPauseSelectionScreenState_exit(AutomaticPauseSelectionScreenState this, void* owner)
{
	Screen_FXFadeOut(Screen_getInstance(), FADE_DELAY);

	// destroy the state
	__DELETE(this);
}

// state's resume
static void AutomaticPauseSelectionScreenState_resume(AutomaticPauseSelectionScreenState this, void* owner)
{
	GameState_resume((GameState)this, owner);
	
	AutomaticPauseSelectionScreenState_print(this);
}

// state's on message
static bool AutomaticPauseSelectionScreenState_handleMessage(AutomaticPauseSelectionScreenState this, void* owner, Telegram telegram)
{
	switch (Telegram_getMessage(telegram))
	{
		case kKeyPressed:
		{
            u16 pressedKey = *((u16*)Telegram_getExtraInfo(telegram));

            AutomaticPauseSelectionScreenState_processInput(AutomaticPauseSelectionScreenState_getInstance(), pressedKey);
        }
        break;
	}

	return false;
}

static void AutomaticPauseSelectionScreenState_print(AutomaticPauseSelectionScreenState this)
{
    char* strHeader = I18n_getText(I18n_getInstance(), STR_AUTOMATIC_PAUSE);
    u8 strHeaderXPos = (48 - strlen(strHeader)) >> 1;
    Printing_text(Printing_getInstance(), strHeader, strHeaderXPos, 8, "GUIFont");

    Printing_text(Printing_getInstance(), I18n_getText(I18n_getInstance(), STR_AUTOMATIC_PAUSE_EXPLANATION), 8, 11, NULL);

    AutomaticPauseSelectionScreenState_renderSelection(this);
}

static void AutomaticPauseSelectionScreenState_renderSelection(AutomaticPauseSelectionScreenState this)
{
    // get strings and determine lengths
    char* strOn = I18n_getText(I18n_getInstance(), STR_ON);
    char* strOff = I18n_getText(I18n_getInstance(), STR_OFF);
    u8 strOnLength = strlen(strOn);
    u8 strOffLength = strlen(strOff);
    u8 optionsGap = 3;
    u8 selectionStart = (48 - (strOnLength + optionsGap + strOffLength)) >> 1;

    // clear options area
    Printing_text(Printing_getInstance(), "                                                ", 0, 16, NULL);
    Printing_text(Printing_getInstance(), "                                                ", 0, 17, NULL);
    Printing_text(Printing_getInstance(), "                                                ", 0, 18, NULL);

    // print options
    Printing_text(Printing_getInstance(), strOn, selectionStart, 17, NULL);
    Printing_text(Printing_getInstance(), strOff, selectionStart + 3 + strOnLength, 17, NULL);

    // print selector
    u8 optionStart = this->selection ? selectionStart - 1 : selectionStart - 1 + optionsGap + strOnLength;
    u8 optionEnd = this->selection ? optionStart + 1 + strOnLength : optionStart + 1 + strOffLength;
    Printing_text(Printing_getInstance(), "\x02\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07", optionStart, 16, NULL);
    Printing_text(Printing_getInstance(), "\x03               ", optionEnd, 16, NULL);
    Printing_text(Printing_getInstance(), "\x06", optionStart, 17, NULL);
    Printing_text(Printing_getInstance(), "\x06", optionEnd, 17, NULL);
    Printing_text(Printing_getInstance(), "\x04\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07\x07", optionStart, 18, NULL);
    Printing_text(Printing_getInstance(), "\x05               ", optionEnd, 18, NULL);
}

static void AutomaticPauseSelectionScreenState_processInput(AutomaticPauseSelectionScreenState this, u16 pressedKey)
{
	if ((pressedKey & K_LL) || (pressedKey & K_LR))
	{
	    this->selection = !this->selection;
	    AutomaticPauseSelectionScreenState_renderSelection(this);
	}
	else if ((pressedKey & K_A) || (pressedKey & K_STA))
	{
		Game_setAutomaticPauseState(Game_getInstance(), this->selection ? (GameState)AutomaticPauseScreenState_getInstance() : NULL);
	    Game_changeState(Game_getInstance(), this->nextState);
	}
}

void AutomaticPauseSelectionScreenState_setNextstate(AutomaticPauseSelectionScreenState this, GameState nextState)
{
    this->nextState = nextState;
}