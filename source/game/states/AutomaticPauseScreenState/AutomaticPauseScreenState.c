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
#include <PhysicalWorld.h>
#include <AutomaticPauseScreenState.h>
#include <Hero.h>
#include "../stages/stages.h"
#include <macros.h>
#include <text.h>
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void AutomaticPauseScreenState_destructor(AutomaticPauseScreenState this);
static void AutomaticPauseScreenState_constructor(AutomaticPauseScreenState this);
static void AutomaticPauseScreenState_enter(AutomaticPauseScreenState this, void* owner);
static void AutomaticPauseScreenState_execute(AutomaticPauseScreenState this, void* owner);
static void AutomaticPauseScreenState_exit(AutomaticPauseScreenState this, void* owner);
static bool AutomaticPauseScreenState_handleMessage(AutomaticPauseScreenState this, void* owner, Telegram telegram);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(AutomaticPauseScreenState);
__SINGLETON(AutomaticPauseScreenState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void AutomaticPauseScreenState_constructor(AutomaticPauseScreenState this)
{
	__CONSTRUCT_BASE(GameState);
}

// class's destructor
static void AutomaticPauseScreenState_destructor(AutomaticPauseScreenState this)
{
	// destroy base
	__SINGLETON_DESTROY(GameState);
}

// state's enter
static void AutomaticPauseScreenState_enter(AutomaticPauseScreenState this, void* owner)
{
	Optical optical = Game_getOptical(Game_getInstance());
	optical.verticalViewPointCenter = ITOFIX19_13(112 + 112/2);
	Game_setOptical(Game_getInstance(), optical);

	//load stage
	GameState_loadStage((GameState)this, (StageDefinition*)&AUTOMATIC_PAUSE_SCREEN_ST, true, true);

	// show up level after a little bit
	MessageDispatcher_dispatchMessage(10000, (Object)this, (Object)Game_getInstance(), kSetUpLevel, NULL);

    Printing_text(Printing_getInstance(), "                                                ", 0, 26, "GUIFont");
    Printing_text(Printing_getInstance(), "REST FOR A WHILE!", ((__SCREEN_WIDTH >> 3) >> 1) - 3, 20, "GUIFont");

	Screen_FXFadeIn(Screen_getInstance(), FADE_DELAY >> 1);
}

// state's exit
static void AutomaticPauseScreenState_exit(AutomaticPauseScreenState this, void* owner)
{
	// make a fade out
	Screen_FXFadeOut(Screen_getInstance(), FADE_DELAY >> 1);
}

// state's on message
static bool AutomaticPauseScreenState_handleMessage(AutomaticPauseScreenState this, void* owner, Telegram telegram)
{
	// process message
	switch (Telegram_getMessage(telegram))
    {
		case kKeyUp:
			{
				u16 releasedKey = *((u16*)Telegram_getExtraInfo(telegram));
		
				// check direction
				if (K_STA & releasedKey)
				{
					Game_unpause(Game_getInstance(), (GameState)this);
				}
			}
			return true;
			break;
	}

	return false;
}