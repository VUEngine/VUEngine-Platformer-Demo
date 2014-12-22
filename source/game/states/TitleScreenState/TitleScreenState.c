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
#include <TitleScreenState.h>
#include <TitleScreenState.h>
#include <Hero.h>
#include "../stages/stages.h"
#include <macros.h>
#include <text.h>
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void TitleScreenState_destructor(TitleScreenState this);
static void TitleScreenState_constructor(TitleScreenState this);
static void TitleScreenState_enter(TitleScreenState this, void* owner);
static void TitleScreenState_execute(TitleScreenState this, void* owner);
static void TitleScreenState_exit(TitleScreenState this, void* owner);
static int TitleScreenState_handleMessage(TitleScreenState this, void* owner, Telegram telegram);
void TitleScreenState_printLevelSelectMessage(TitleScreenState this);


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
	Optical optical = Game_getOptical(Game_getInstance());
	optical.verticalViewPointCenter = ITOFIX19_13(112 + 112/2);
	Game_setOptical(Game_getInstance(), optical);

	//load stage
	GameState_loadStage((GameState)this, (StageDefinition*)&TITLE_SCREEN_ST, true, true);

	// show up level after a little bit
	MessageDispatcher_dispatchMessage(1000, (Object)this, (Object)Game_getInstance(), kSetUpLevel, NULL);

	// reset clock
	Clock_reset(Game_getInGameClock(Game_getInstance()));
}

// state's execute
static void TitleScreenState_execute(TitleScreenState this, void* owner)
{
    Door doorLastPassed = Hero_getDoorLastPassed(Hero_getInstance());

    // display level name if in front of a door
    if (
        (doorLastPassed != NULL) &&
        __VIRTUAL_CALL(int, Shape, overlaps, Entity_getShape((Entity)Hero_getInstance()), __ARGUMENTS(Entity_getShape((Entity)doorLastPassed)))
    )
    {
        /*
        StageDefinition stageDefiniton = (StageDefinition)Door_getExtraInfo(doorLastPassed);
        char* strLevelName = stageDefiniton.name;
        Printing_text("                                                ", 0, 26);
        Printing_text(strLevelName, (48 - strlen(strLevelName)) >> 1, 26);
        */

        // print level name
        // TODO: use stageDefinition
        char* strLevelIdentifier = &LEVEL_1_1_ROOM_1_ST.identifier;
        char* strLevelName = &LEVEL_1_1_ROOM_1_ST.name;
        int levelIdentifierLength = strlen(strLevelIdentifier);
        int levelNameLength = strlen(strLevelName);
        int levelNameTotalLength = levelIdentifierLength + levelNameLength + 4;
        int printingStart = (48 - levelNameTotalLength) >> 1;

        Printing_text("                                                ", 0, 26);
        Printing_text(strLevelIdentifier, printingStart, 26);
        Printing_text(": \"", printingStart + levelIdentifierLength, 26);
        Printing_text(strLevelName, printingStart + levelIdentifierLength + 3, 26);
        Printing_text("\"", printingStart + levelNameTotalLength - 1, 26);
    }
    else
    {
        TitleScreenState_printLevelSelectMessage(this);
    }

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

// print the "please select a leve" text
void TitleScreenState_printLevelSelectMessage(TitleScreenState this)
{
    char* strSelectLevel = I18n_getText(I18n_getInstance(), STR_SELECT_LEVEL);
    Printing_text("                                                ", 0, 26);
    Printing_text(strSelectLevel, (48 - strlen(strSelectLevel)) >> 1, 26);
}