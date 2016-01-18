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
#include <screens.h>
#include <macros.h>
#include <PlatformerLevelState.h>
#include <Languages.h>


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
	GameState_loadStage(__SAFE_CAST(GameState, this), (StageDefinition*)&PAUSE_SCREEN_ST, NULL, true);

	// show up level after a little bit
	MessageDispatcher_dispatchMessage(1, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kLevelSetUp, NULL);

    Printing_text(Printing_getInstance(), I18n_getText(I18n_getInstance(), STR_PAUSE), 21, 16, "GUIFont");

    Screen_startEffect(Screen_getInstance(), kFadeIn, FADE_DELAY);
}

// state's execute
static void PauseScreenState_execute(PauseScreenState this, void* owner)
{
}

// state's exit
static void PauseScreenState_exit(PauseScreenState this, void* owner)
{
	// make a fade out
	Screen_startEffect(Screen_getInstance(), kFadeOut, FADE_DELAY);

	// destroy the state
	__DELETE(this);
}

// state's handle message
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
					Game_unpause(Game_getInstance(), __SAFE_CAST(GameState, this));
				}
			}
			return true;
			break;
	}

	return false;
}