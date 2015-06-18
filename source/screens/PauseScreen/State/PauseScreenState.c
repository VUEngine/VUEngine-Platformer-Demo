/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev <jorgech3@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if not,
 * write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
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
#include <screens.h>
#include <macros.h>
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void PauseScreenState_destructor(PauseScreenState this);
static void PauseScreenState_constructor(PauseScreenState this);
static void PauseScreenState_enter(PauseScreenState this, void* owner);
static void PauseScreenState_execute(PauseScreenState this, void* owner);
static void PauseScreenState_exit(PauseScreenState this, void* owner);
static bool PauseScreenState_handleMessage(PauseScreenState this, void* owner, Telegram telegram);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(PauseScreenState, GameState);
__SINGLETON_DYNAMIC(PauseScreenState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void PauseScreenState_constructor(PauseScreenState this)
{
	__CONSTRUCT_BASE();
}

// class's destructor
static void PauseScreenState_destructor(PauseScreenState this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
static void PauseScreenState_enter(PauseScreenState this, void* owner)
{
	// load stage
	GameState_loadStage(__GET_CAST(GameState, this), (StageDefinition*)&PAUSE_SCREEN_ST, NULL, true);

	// show up level after a little bit
	MessageDispatcher_dispatchMessage(10000, __GET_CAST(Object, this), __GET_CAST(Object, Game_getInstance()), kSetUpLevel, NULL);

    Printing_text(Printing_getInstance(), "                                                ", 0, 26, "GUIFont");
    Printing_text(Printing_getInstance(), "PAUSED", ((__SCREEN_WIDTH >> 3) >> 1) - 3, 20, "GUIFont");

    Screen_startEffect(Screen_getInstance(), kFadeIn, FADE_DELAY >> 1);
}

// state's execute
static void PauseScreenState_execute(PauseScreenState this, void* owner)
{
}

// state's exit
static void PauseScreenState_exit(PauseScreenState this, void* owner)
{
	// make a fade out
	Screen_startEffect(Screen_getInstance(), kFadeOut, FADE_DELAY >> 1);

	// destroy the state
	__DELETE(this);
}

// state's on message
static bool PauseScreenState_handleMessage(PauseScreenState this, void* owner, Telegram telegram)
{
	// process message
	switch(Telegram_getMessage(telegram))
    {
		case kKeyPressed:
			{
				u16 pressedKey = *((u16*)Telegram_getExtraInfo(telegram));
		
				// check direction
				if(K_STA & pressedKey)
				{
					Game_unpause(Game_getInstance(), __GET_CAST(GameState, this));
				}
			}
			return true;
			break;
	}

	return false;
}