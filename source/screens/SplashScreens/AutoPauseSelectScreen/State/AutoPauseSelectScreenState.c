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
#include <I18n.h>
#include <AutoPauseSelectScreenState.h>
#include <VBJaEngineScreenState.h>
#include <AutoPauseScreenState.h>
#include <Languages.h>


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
static void AutoPauseSelectScreenState_processInput(AutoPauseSelectScreenState this, u16 releasedKey);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(AutoPauseSelectScreenState, SplashScreenState);
__SINGLETON_DYNAMIC(AutoPauseSelectScreenState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void AutoPauseSelectScreenState_constructor(AutoPauseSelectScreenState this)
{
	__CONSTRUCT_BASE();

	SplashScreenState_setNextstate(__UPCAST(SplashScreenState, this), __UPCAST(GameState, VBJaEngineScreenState_getInstance()));
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
    char* strAutomaticPause = I18n_getText(I18n_getInstance(), STR_AUTOMATIC_PAUSE);
    char* strAutomaticPauseExplanation = I18n_getText(I18n_getInstance(), STR_AUTOMATIC_PAUSE_EXPLANATION);
    Size strAutomaticPauseSize = Printing_getTextSize(Printing_getInstance(), strAutomaticPause, "GUIFont");
    Size strAutomaticPauseExplanationSize = Printing_getTextSize(Printing_getInstance(), strAutomaticPauseExplanation, NULL);

    u8 strHeaderXPos = (__SCREEN_WIDTH >> 4) - (strAutomaticPauseSize.x >> 1);
    Printing_text(Printing_getInstance(), strAutomaticPause, strHeaderXPos, 8, "GUIFont");

    u8 strExplanationXPos = (__SCREEN_WIDTH >> 4) - (strAutomaticPauseExplanationSize.x >> 1);
    Printing_text(Printing_getInstance(), strAutomaticPauseExplanation, strExplanationXPos, 9 + strAutomaticPauseSize.y, NULL);

    AutoPauseSelectScreenState_renderSelection(this);
}

static void AutoPauseSelectScreenState_renderSelection(AutoPauseSelectScreenState this)
{
    char* strOn = I18n_getText(I18n_getInstance(), STR_ON);
    char* strOff = I18n_getText(I18n_getInstance(), STR_OFF);

    // get strings and determine sizes
    Size strOnSize = Printing_getTextSize(Printing_getInstance(), strOn, NULL);
    Size strOffSize = Printing_getTextSize(Printing_getInstance(), strOff, NULL);
    u8 optionsGap = 3;
    u8 selectionStart = (48 - (strOnSize.x + optionsGap + strOffSize.x)) >> 1;

    // clear options area
    Printing_text(Printing_getInstance(), "                                                ", 0, 16, NULL);
    Printing_text(Printing_getInstance(), "                                                ", 0, 17, NULL);
    Printing_text(Printing_getInstance(), "                                                ", 0, 18, NULL);
    if (strOnSize.y > 1) {
        Printing_text(Printing_getInstance(), "                                                ", 0, 19, NULL);
        if (strOnSize.y > 2) {
            Printing_text(Printing_getInstance(), "                                                ", 0, 20, NULL);
            if (strOnSize.y > 3) {
                Printing_text(Printing_getInstance(), "                                                ", 0, 21, NULL);
            }
        }
    }

    // print options
    Printing_text(Printing_getInstance(), strOn, selectionStart, 17, NULL);
    Printing_text(Printing_getInstance(), strOff, selectionStart + 3 + strOnSize.x, 17, NULL);

    // print selector
    u8 optionStart = this->selection ? selectionStart - 1 : selectionStart - 1 + optionsGap + strOnSize.x;
    u8 optionEnd = this->selection ? optionStart + 1 + strOnSize.x : optionStart + 1 + strOffSize.x;
    Printing_text(Printing_getInstance(), "\x03\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08", optionStart, 16, NULL);
    Printing_text(Printing_getInstance(), "\x04               ", optionEnd, 16, NULL);
    Printing_text(Printing_getInstance(), "\x07", optionStart, 17, NULL);
    Printing_text(Printing_getInstance(), "\x07", optionEnd, 17, NULL);
    if (strOnSize.y > 1) {
        Printing_text(Printing_getInstance(), "\x07", optionStart, 18, NULL);
        Printing_text(Printing_getInstance(), "\x07", optionEnd, 18, NULL);
        if (strOnSize.y > 2) {
            Printing_text(Printing_getInstance(), "\x07", optionStart, 19, NULL);
            Printing_text(Printing_getInstance(), "\x07", optionEnd, 19, NULL);
            if (strOnSize.y > 3) {
                Printing_text(Printing_getInstance(), "\x07", optionStart, 20, NULL);
                Printing_text(Printing_getInstance(), "\x07", optionEnd, 20, NULL);
            }
        }
    }
    Printing_text(Printing_getInstance(), "\x05\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08", optionStart, 17 + strOnSize.y, NULL);
    Printing_text(Printing_getInstance(), "\x06               ", optionEnd, 17 + strOnSize.y, NULL);
}

void AutoPauseSelectScreenState_processInput(AutoPauseSelectScreenState this, u16 releasedKey)
{
	if ((releasedKey & K_LL) || (releasedKey & K_LR))
	{
	    this->selection = !this->selection;
	    AutoPauseSelectScreenState_renderSelection(this);
	}
	else if ((releasedKey & K_A) || (releasedKey & K_STA))
	{
		Game_setAutomaticPauseState(Game_getInstance(), this->selection ? __UPCAST(GameState, AutoPauseScreenState_getInstance()): NULL);
	    Game_changeState(Game_getInstance(), this->nextState);
	}
}
