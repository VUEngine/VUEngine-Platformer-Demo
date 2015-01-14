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
static void TitleScreenState_resume(TitleScreenState this, void* owner);
static bool TitleScreenState_handleMessage(TitleScreenState this, void* owner, Telegram telegram);


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
    this->lastLevelSelectLabel = "";

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

	// make a little bit of physical simulations so each entity is placed at the floor
	Clock_start(Game_getInGameClock(Game_getInstance()));
	PhysicalWorld_start(PhysicalWorld_getInstance());

	// show up level after a little bit
	MessageDispatcher_dispatchMessage(1000, (Object)this, (Object)Game_getInstance(), kSetUpLevel, NULL);

	// reset clock
	Clock_reset(Game_getInGameClock(Game_getInstance()));
}

// state's execute
static void TitleScreenState_execute(TitleScreenState this, void* owner)
{
    Door currentlyOverlappingDoor = Hero_getCurrentlyOverlappingDoor(Hero_getInstance());
    char* strLevelSelectLabel = "";

    // display level name if in front of a door
    if (currentlyOverlappingDoor != NULL)
    {
        StageDefinition* stageDefinition = Door_getExtraInfo(currentlyOverlappingDoor);
        strLevelSelectLabel = I18n_getText(I18n_getInstance(), (int)(*stageDefinition).name);
    }

    if (0 != strcmp(this->lastLevelSelectLabel, strLevelSelectLabel))
    {
        Printing_text(Printing_getInstance(), "                                                ", 0, 26, "GUIFont");
        Printing_text(Printing_getInstance(), strLevelSelectLabel, (48 - strlen(strLevelSelectLabel)) >> 1, 26, "GUIFont");
        this->lastLevelSelectLabel = strLevelSelectLabel;
    }

	// call base
	GameState_execute((GameState)this, owner);
}

// state's exit
static void TitleScreenState_exit(TitleScreenState this, void* owner)
{
	// make a fade out
	Screen_FXFadeOut(Screen_getInstance(), FADE_DELAY);

	// destroy the state
	__DELETE(this);
}

// state's resume
static void TitleScreenState_resume(TitleScreenState this, void* owner)
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
	
	// tell any interested entity
	GameState_propagateMessage((GameState)this, kResumeLevel);

	// make a fade in
	Screen_FXFadeIn(Screen_getInstance(), FADE_DELAY >> 1);

#ifdef __DEBUG_TOOLS
	}
#endif
#ifdef __STAGE_EDITOR
	}
#endif
#ifdef __ANIMATION_EDITOR
	}
#endif
}

// state's on message
static bool TitleScreenState_handleMessage(TitleScreenState this, void* owner, Telegram telegram)
{
	// process message
	switch (Telegram_getMessage(telegram))
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