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
#include <Utilities.h>
#include <I18n.h>
#include <AutoPauseSelectScreenState.h>
#include <VBJaEngineScreenState.h>
#include <AutoPauseScreenState.h>
#include <Languages.h>
#include <KeyPadManager.h>
#include <ProgressManager.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef EMPTY_ST;


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void AutoPauseSelectScreenState_destructor(AutoPauseSelectScreenState this);
static void AutoPauseSelectScreenState_constructor(AutoPauseSelectScreenState this);
static void AutoPauseSelectScreenState_print(AutoPauseSelectScreenState this);
static void AutoPauseSelectScreenState_renderSelection(AutoPauseSelectScreenState this);
static void AutoPauseSelectScreenState_processInput(AutoPauseSelectScreenState this, u32 pressedKey);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(AutoPauseSelectScreenState, SplashScreenState);
__SINGLETON_DYNAMIC(AutoPauseSelectScreenState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void __attribute__ ((noinline)) AutoPauseSelectScreenState_constructor(AutoPauseSelectScreenState this)
{
	__CONSTRUCT_BASE(SplashScreenState);

	SplashScreenState_setNextState(__SAFE_CAST(SplashScreenState, this), __SAFE_CAST(GameState, VBJaEngineScreenState_getInstance()));
	this->stageDefinition = (StageDefinition*)&EMPTY_ST;
    this->selection = true;
}

// class's destructor
static void AutoPauseSelectScreenState_destructor(AutoPauseSelectScreenState this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

static void AutoPauseSelectScreenState_print(AutoPauseSelectScreenState this)
{
    this->selection = ProgressManager_getAutomaticPauseStatus(ProgressManager_getInstance());

    const char* strAutomaticPauseTitle = I18n_getText(I18n_getInstance(), STR_AUTOMATIC_PAUSE);
    const char* strAutomaticPauseTitleFont = "LargeFont";
    Size strAutomaticPauseSize = Printing_getTextSize(Printing_getInstance(), strAutomaticPauseTitle, strAutomaticPauseTitleFont);

    const char* strAutomaticPauseExplanation = I18n_getText(I18n_getInstance(), STR_AUTOMATIC_PAUSE_EXPLANATION);
    Size strAutomaticPauseExplanationSize = Printing_getTextSize(Printing_getInstance(), strAutomaticPauseExplanation, NULL);

    u8 strHeaderXPos = (__SCREEN_WIDTH >> 4) - (strAutomaticPauseSize.x >> 1);
    Printing_text(
    	Printing_getInstance(),
    	Utilities_toUppercase(strAutomaticPauseTitle),
    	strHeaderXPos,
    	8,
    	strAutomaticPauseTitleFont
	);

    u8 strExplanationXPos = (__SCREEN_WIDTH >> 4) - (strAutomaticPauseExplanationSize.x >> 1);
    Printing_text(Printing_getInstance(), strAutomaticPauseExplanation, strExplanationXPos, 9 + strAutomaticPauseSize.y, NULL);

    AutoPauseSelectScreenState_renderSelection(this);
}

static void AutoPauseSelectScreenState_renderSelection(AutoPauseSelectScreenState this)
{
    const char* strOn = I18n_getText(I18n_getInstance(), STR_ON);
    const char* strOff = I18n_getText(I18n_getInstance(), STR_OFF);

    // get strings and determine sizes
    Size strOnSize = Printing_getTextSize(Printing_getInstance(), strOn, NULL);
    Size strOffSize = Printing_getTextSize(Printing_getInstance(), strOff, NULL);
    u8 selectionStart = (48 - (strOnSize.x + __OPTIONS_GAP + strOffSize.x)) >> 1;

    // clear options area
    Printing_text(Printing_getInstance(), "                                                ", 0, __OPTIONS_Y_POS, NULL);
    Printing_text(Printing_getInstance(), "                                                ", 0, __OPTIONS_Y_POS + 1, NULL);
    Printing_text(Printing_getInstance(), "                                                ", 0, __OPTIONS_Y_POS + 2, NULL);
    if(strOnSize.y > 1) {
        Printing_text(Printing_getInstance(), "                                                ", 0, __OPTIONS_Y_POS + 3, NULL);
        if(strOnSize.y > 2) {
            Printing_text(Printing_getInstance(), "                                                ", 0, __OPTIONS_Y_POS + 4, NULL);
            if(strOnSize.y > 3) {
                Printing_text(Printing_getInstance(), "                                                ", 0, __OPTIONS_Y_POS + 5, NULL);
            }
        }
    }

    // print options
    Printing_text(Printing_getInstance(), strOn, selectionStart, __OPTIONS_Y_POS + 1, NULL);
    Printing_text(Printing_getInstance(), strOff, selectionStart + 3 + strOnSize.x, __OPTIONS_Y_POS + 1, NULL);

    // print selector
    u8 optionStart = this->selection ? selectionStart : selectionStart + __OPTIONS_GAP + strOnSize.x;
    u8 optionEnd = this->selection ? optionStart + strOnSize.x : optionStart + strOffSize.x;
    optionStart--;
    Printing_text(Printing_getInstance(), "\x03\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08", optionStart, __OPTIONS_Y_POS, NULL);
    Printing_text(Printing_getInstance(), "\x04               ", optionEnd, __OPTIONS_Y_POS, NULL);
    Printing_text(Printing_getInstance(), "\x07", optionStart, __OPTIONS_Y_POS + 1, NULL);
    Printing_text(Printing_getInstance(), "\x07", optionEnd, __OPTIONS_Y_POS + 1, NULL);
    if(strOnSize.y > 1) {
        Printing_text(Printing_getInstance(), "\x07", optionStart, __OPTIONS_Y_POS + 2, NULL);
        Printing_text(Printing_getInstance(), "\x07", optionEnd, __OPTIONS_Y_POS + 2, NULL);
        if(strOnSize.y > 2) {
            Printing_text(Printing_getInstance(), "\x07", optionStart, __OPTIONS_Y_POS + 3, NULL);
            Printing_text(Printing_getInstance(), "\x07", optionEnd, __OPTIONS_Y_POS + 3, NULL);
            if(strOnSize.y > 3) {
                Printing_text(Printing_getInstance(), "\x07", optionStart, __OPTIONS_Y_POS + 4, NULL);
                Printing_text(Printing_getInstance(), "\x07", optionEnd, __OPTIONS_Y_POS + 4, NULL);
            }
        }
    }
    Printing_text(Printing_getInstance(), "\x05\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08", optionStart, __OPTIONS_Y_POS + 1 + strOnSize.y, NULL);
    Printing_text(Printing_getInstance(), "\x06               ", optionEnd, __OPTIONS_Y_POS + 1 + strOnSize.y, NULL);
}

void AutoPauseSelectScreenState_processInput(AutoPauseSelectScreenState this, u32 pressedKey)
{
	if((pressedKey & K_LL) || (pressedKey & K_LR))
	{
	    this->selection = !this->selection;
	    AutoPauseSelectScreenState_renderSelection(this);
	}
	else if((pressedKey & K_A) || (pressedKey & K_STA))
	{
		Game_setAutomaticPauseState(Game_getInstance(), this->selection
			? __SAFE_CAST(GameState, AutoPauseScreenState_getInstance())
			: NULL
		);
	    ProgressManager_setAutomaticPauseStatus(ProgressManager_getInstance(), (bool)this->selection);
	    SplashScreenState_loadNextState(__SAFE_CAST(SplashScreenState, this));
	}
}
