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
#include <Printing.h>
#include <Screen.h>
#include <MessageDispatcher.h>
#include <PrecautionScreenState.h>
#include <AutomaticPauseSelectionScreenState.h>
#include <stages.h>
#include <macros.h>
#include <I18n.h>
#include <lang.h>


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void PrecautionScreenState_destructor(PrecautionScreenState this);
static void PrecautionScreenState_constructor(PrecautionScreenState this);
static void PrecautionScreenState_enter(PrecautionScreenState this, void* owner);
static void PrecautionScreenState_execute(PrecautionScreenState this, void* owner);
static void PrecautionScreenState_exit(PrecautionScreenState this, void* owner);
static void PrecautionScreenState_resume(PrecautionScreenState this, void* owner);
static bool PrecautionScreenState_handleMessage(PrecautionScreenState this, void* owner, Telegram telegram);
static void PrecautionScreenState_processInput(PrecautionScreenState this, u16 pressedKey);
static void PrecautionScreenState_print(PrecautionScreenState this);
void PrecautionScreenState_setNextstate(PrecautionScreenState this, GameState nextState);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(PrecautionScreenState);
__SINGLETON_DYNAMIC(PrecautionScreenState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void PrecautionScreenState_constructor(PrecautionScreenState this)
{
	PrecautionScreenState_setNextstate(this, (GameState)AutomaticPauseSelectionScreenState_getInstance());
	this->stageDefinition = (StageDefinition*)&PRECAUTION_SCREEN_ST;

	__CONSTRUCT_BASE(GameState);
}

// class's destructor
static void PrecautionScreenState_destructor(PrecautionScreenState this)
{
	// destroy base
	__SINGLETON_DESTROY(GameState);
}

// state's enter
static void PrecautionScreenState_enter(PrecautionScreenState this, void* owner)
{
	GameState_loadStage((GameState)this, this->stageDefinition, true, true);

    PrecautionScreenState_print(this);

	Screen_FXFadeIn(Screen_getInstance(), 16);
}

// state's execute
static void PrecautionScreenState_execute(PrecautionScreenState this, void* owner)
{
 	// call base
	GameState_execute((GameState)this, owner);
}

// state's exit
static void PrecautionScreenState_exit(PrecautionScreenState this, void* owner)
{
	Screen_FXFadeOut(Screen_getInstance(), 16);

	// destroy the state
	__DELETE(this);
}

// state's resume
static void PrecautionScreenState_resume(PrecautionScreenState this, void* owner)
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
	Screen_FXFadeIn(Screen_getInstance(), 16 >> 1);

#ifdef __DEBUG_TOOLS
	}
#endif
#ifdef __STAGE_EDITOR
	}
#endif
#ifdef __ANIMATION_EDITOR
	}
#endif

    PrecautionScreenState_print(this);
}

// state's on message
static bool PrecautionScreenState_handleMessage(PrecautionScreenState this, void* owner, Telegram telegram)
{
	switch (Telegram_getMessage(telegram))
	{
		case kKeyPressed:
		{
            u16 pressedKey = *((u16*)Telegram_getExtraInfo(telegram));

            PrecautionScreenState_processInput(PrecautionScreenState_getInstance(), pressedKey);
        }
        break;
	}

	return false;
}

static void PrecautionScreenState_processInput(PrecautionScreenState this, u16 pressedKey)
{
	Game_changeState(Game_getInstance(), this->nextState);
}

static void PrecautionScreenState_print(PrecautionScreenState this)
{
    Printing_text(Printing_getInstance(), I18n_getText(I18n_getInstance(), STR_PRECAUTION), 8, 6, NULL);
}

void PrecautionScreenState_setNextstate(PrecautionScreenState this, GameState nextState)
{
	this->nextState = nextState;
}