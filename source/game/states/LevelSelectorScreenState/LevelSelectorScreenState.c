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
#include <LevelSelectorScreenState.h>
#include <TitleScreenState.h>
#include <Hero.h>
#include "../stages/stages.h"
#include <macros.h>
#include <text.h>
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void LevelSelectorScreenState_destructor(LevelSelectorScreenState this);
static void LevelSelectorScreenState_constructor(LevelSelectorScreenState this);
static void LevelSelectorScreenState_enter(LevelSelectorScreenState this, void* owner);
static void LevelSelectorScreenState_execute(LevelSelectorScreenState this, void* owner);
static void LevelSelectorScreenState_exit(LevelSelectorScreenState this, void* owner);
static int LevelSelectorScreenState_handleMessage(LevelSelectorScreenState this, void* owner, Telegram telegram);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(LevelSelectorScreenState);
__SINGLETON_DYNAMIC(LevelSelectorScreenState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void LevelSelectorScreenState_constructor(LevelSelectorScreenState this)
{
	__CONSTRUCT_BASE(GameState);
}

// class's destructor
static void LevelSelectorScreenState_destructor(LevelSelectorScreenState this)
{
	// destroy base
	__SINGLETON_DESTROY(GameState);
}

// state's enter
static void LevelSelectorScreenState_enter(LevelSelectorScreenState this, void* owner)
{
	Optical optical = Game_getOptical(Game_getInstance());
	optical.verticalViewPointCenter = ITOFIX19_13(112 + 112/2);
	Game_setOptical(Game_getInstance(), optical);

	//load stage
	GameState_loadStage((GameState)this, (StageDefinition*)&LEVEL_SELECTOR_ST, true, true);

	// show up level after a little bit
	MessageDispatcher_dispatchMessage(1000, (Object)this, (Object)Game_getInstance(), kSetUpLevel, NULL);

	// reset clock and render time
	Clock_reset(Game_getInGameClock(Game_getInstance()));
	
	Printing_text("   AWESOME", 16, 4);
	Printing_text("LEVEL SELECTOR", 16, 5);
}

// state's execute
static void LevelSelectorScreenState_execute(LevelSelectorScreenState this, void* owner)
{
	// call base
	GameState_execute((GameState)this, owner);
}

// state's exit
static void LevelSelectorScreenState_exit(LevelSelectorScreenState this, void* owner)
{
	// make a fade in
	Screen_FXFadeOut(Screen_getInstance(), FADE_DELAY);

	// destroy the state
	__DELETE(this);
}

// state's on message
static int LevelSelectorScreenState_handleMessage(LevelSelectorScreenState this, void* owner, Telegram telegram)
{
	// process message
	switch(Telegram_getMessage(telegram))
    {
		case kSetUpLevel:

			// make a little bit of physical simulations so each entity is placed at the floor
			Clock_start(Game_getInGameClock(Game_getInstance()));
	
			// start physical simulation again
			PhysicalWorld_start(PhysicalWorld_getInstance());

			// pause physical simulations
			Clock_pause(Game_getInGameClock(Game_getInstance()), true);

			// account for any entity's tranform modification during their initialization
			GameState_transform((GameState)this);
			
			// show level after 0.5 second
			MessageDispatcher_dispatchMessage(500, (Object)this, (Object)Game_getInstance(), kStartLevel, NULL);
			break;

		case kStartLevel:

			// fade screen
			Screen_FXFadeIn(Screen_getInstance(), FADE_DELAY);

			// reset clock and restart
			Clock_reset(Game_getInGameClock(Game_getInstance()));
			Clock_start(Game_getInGameClock(Game_getInstance()));
			
			// start physical simulation again
			PhysicalWorld_start(PhysicalWorld_getInstance());

			// tell any interested entity
			GameState_propagateMessage((GameState)this, kStartLevel);
			break;

		case kKeyPressed:

			Object_fireEvent((Object)this, EVENT_KEY_PRESSED);
			return true;
			break;

		case kKeyUp:

			Object_fireEvent((Object)this, EVENT_KEY_RELEASED);
			return true;
			break;
			
		case kKeyHold:
			
			Object_fireEvent((Object)this, EVENT_KEY_HOLD);
			return true;
			break;
	}

	return false;
}

// go to level
void LevelSelectorScreenState_goToLevel1_1()
{
	PlatformerLevelState_setStage(PlatformerLevelState_getInstance(), &LEVEL_1_1_ROOM_1_ST);
	Game_changeState(Game_getInstance(), (State)PlatformerLevelState_getInstance());
}

// go to level
void LevelSelectorScreenState_goToLevel1_2()
{
	PlatformerLevelState_setStage(PlatformerLevelState_getInstance(), &LEVEL_1_2_ROOM_1_ST);
	Game_changeState(Game_getInstance(), (State)PlatformerLevelState_getInstance());
}

// go to level
void LevelSelectorScreenState_goToLevel1_3()
{
	PlatformerLevelState_setStage(PlatformerLevelState_getInstance(), &LEVEL_1_3_ROOM_1_ST);
	Game_changeState(Game_getInstance(), (State)PlatformerLevelState_getInstance());
}

