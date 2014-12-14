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

#include <Game.h>
#include <Screen.h>
#include <Printing.h>

#include "TitleScreenState.h"
#include <objects.h>
#include <macros.h>
#include "stages.h"

#include "PlatformerLevelState.h"


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void TitleScreenState_destructor(TitleScreenState this);
static void TitleScreenState_constructor(TitleScreenState this);
static void TitleScreenState_enter(TitleScreenState this, void* owner);
static void TitleScreenState_exit(TitleScreenState this, void* owner);
static void TitleScreenState_execute(TitleScreenState this, void* owner);
static int TitleScreenState_handleMessage(TitleScreenState this, void* owner, Telegram telegram);


//---------------------------------------------------------------------------------------------------------
// 											DECLARATIONS
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(TitleScreenState);
__SINGLETON_DYNAMIC(TitleScreenState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void TitleScreenState_constructor(TitleScreenState this)
{
	__CONSTRUCT_BASE(GameState);
}

// class's destructor
static void TitleScreenState_destructor(TitleScreenState this)
{
	// destroy base
	__SINGLETON_DESTROY(GameState);
}

// state's enter
static void TitleScreenState_enter(TitleScreenState this, void* owner)
{
	GameState_loadStage((GameState)this, (StageDefinition*)&TITLE_ST, false, true);
	
	// make a fade in
	Screen_FXFadeIn(Screen_getInstance(), FADE_DELAY);
	
	// start in game clock for animations
	Clock_start(Game_getInGameClock(Game_getInstance()));
}

// screen execute
static void TitleScreenState_execute(TitleScreenState this, void* owner)
{
	VBVec3D translation =
    {
		ITOFIX19_13(1),
		ITOFIX19_13(0),
		ITOFIX19_13(0)
	};

	Screen_move(Screen_getInstance(), translation, false);
	
	// call base
	GameState_execute((GameState)this, owner);
}

// state's exit
static void TitleScreenState_exit(TitleScreenState this, void* owner)
{
	// make a fade in
	Screen_FXFadeOut(Screen_getInstance(), FADE_DELAY);

	// destroy the state
	__DELETE(this);
}

// state's on message
static int TitleScreenState_handleMessage(TitleScreenState this, void* owner, Telegram telegram)
{
	// process message
	switch(Telegram_getMessage(telegram))
    {
		case kKeyPressed:

			{
				u16 pressedKey = *((u16*)Telegram_getExtraInfo(telegram));
	
				if (((pressedKey & K_STA) && (pressedKey & K_SEL)))
                {
					break;
				}
			}

			Game_changeState(Game_getInstance(), (State)PlatformerLevelState_getInstance());
			break;
	}

	return false;
}