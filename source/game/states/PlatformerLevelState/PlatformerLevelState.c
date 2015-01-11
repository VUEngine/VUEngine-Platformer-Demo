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
#include <PlatformerLevelState.h>
#include <TitleScreenState.h>
#include <PauseScreenState.h>
#include <Hero.h>
#include "../stages/stages.h"
#include <macros.h>
#include <text.h>


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void PlatformerLevelState_constructor(PlatformerLevelState this);
static void PlatformerLevelState_destructor(PlatformerLevelState this);
static void PlatformerLevelState_enter(PlatformerLevelState this, void* owner);
static void PlatformerLevelState_execute(PlatformerLevelState this, void* owner);
static void PlatformerLevelState_exit(PlatformerLevelState this, void* owner);
static void PlatformerLevelState_pause(PlatformerLevelState this, void* owner);
static void PlatformerLevelState_resume(PlatformerLevelState this, void* owner);
static bool PlatformerLevelState_handleMessage(PlatformerLevelState this, void* owner, Telegram telegram);
static void PlatformerLevelState_onSecondChange(PlatformerLevelState this, Object eventFirer);
static void PlatformerLevelState_onCoinTaken(PlatformerLevelState this, Object eventFirer);
static void PlatformerLevelState_onKeyTaken(PlatformerLevelState this, Object eventFirer);
void PlatformerLevelState_printLifes(PlatformerLevelState this);
void PlatformerLevelState_printCoins(PlatformerLevelState this);
void PlatformerLevelState_printKeys(PlatformerLevelState this);
void PlatformerLevelState_printLevel(PlatformerLevelState this);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(PlatformerLevelState);
__SINGLETON(PlatformerLevelState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void PlatformerLevelState_constructor(PlatformerLevelState this)
{
	__CONSTRUCT_BASE(GameState);

	this->stageDefinition = &LEVEL_1_1_ROOM_1_ST;

//	this->stageDefinition = &TEST_LEVEL_ST;
}

// class's destructor
static void PlatformerLevelState_destructor(PlatformerLevelState this)
{
	// destroy base
	__SINGLETON_DESTROY(GameState);
}

// state's enter
static void PlatformerLevelState_enter(PlatformerLevelState this, void* owner)
{
	Optical optical = Game_getOptical(Game_getInstance());
	optical.verticalViewPointCenter = ITOFIX19_13(112 + 112/2);
	Game_setOptical(Game_getInstance(), optical);

	//load stage
	GameState_loadStage((GameState)this, (StageDefinition*)this->stageDefinition, true, false);

	// playing by default
	this->mode = kPaused;
	
	// show up level after a little bit
	MessageDispatcher_dispatchMessage(1000, (Object)this, (Object)Game_getInstance(), kSetUpLevel, NULL);

	// reset clock and render time
	Clock_reset(Game_getInGameClock(Game_getInstance()));
	Clock_print(Game_getInGameClock(Game_getInstance()), 42, 26, "GUIFont");
	
	// make a little bit of physical simulations so each entity is placed at the floor
	Clock_start(Game_getInGameClock(Game_getInstance()));
	PhysicalWorld_start(PhysicalWorld_getInstance());

	// render gui values
	PlatformerLevelState_printLifes(this);
	PlatformerLevelState_printCoins(this);
	PlatformerLevelState_printKeys(this);
	PlatformerLevelState_printLevel(this);
}

// state's execute
static void PlatformerLevelState_execute(PlatformerLevelState this, void* owner)
{
	// call base
	GameState_execute((GameState)this, owner);
	//SpriteManager_print(SpriteManager_getInstance(), 1, 7);
}

// state's exit
static void PlatformerLevelState_exit(PlatformerLevelState this, void* owner)
{
	Object_removeEventListener((Object)Game_getInGameClock(Game_getInstance()), (Object)this, (void (*)(Object))PlatformerLevelState_onSecondChange, __EVENT_SECOND_CHANGED);
	Object_removeEventListener((Object)this, (Object)this, (void (*)(Object))PlatformerLevelState_onCoinTaken, EVENT_COIN_TAKEN);
	Object_removeEventListener((Object)this, (Object)this, (void (*)(Object))PlatformerLevelState_onKeyTaken, EVENT_KEY_TAKEN);

	// make a fade in
	Screen_FXFadeOut(Screen_getInstance(), FADE_DELAY);
	
	// call base
	GameState_exit((GameState)this, owner);
}

static void PlatformerLevelState_pause(PlatformerLevelState this, void* owner)
{
	// pause physical simulations
	Clock_pause(Game_getInGameClock(Game_getInstance()), true);

#ifdef __DEBUG_TOOLS
	if (!Game_isEnteringSpecialMode(Game_getInstance()))
#endif
#ifdef __STAGE_EDITOR
	if (!Game_isEnteringSpecialMode(Game_getInstance()))
#endif
#ifdef __ANIMATION_EDITOR
	if (!Game_isEnteringSpecialMode(Game_getInstance()))
#endif
	// make a fade in
	Screen_FXFadeOut(Screen_getInstance(), FADE_DELAY >> 1);

	GameState_pause((GameState)this, owner);
}

static void PlatformerLevelState_resume(PlatformerLevelState this, void* owner)
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
	
	// reprint info
	Clock_print(Game_getInGameClock(Game_getInstance()), 42, 26, "GUIFont");
	
	// render gui values
	PlatformerLevelState_printLifes(this);
	PlatformerLevelState_printCoins(this);
	PlatformerLevelState_printKeys(this);
	PlatformerLevelState_printLevel(this);

	// make a fade in
	Screen_FXFadeIn(Screen_getInstance(), FADE_DELAY >> 1);
	
	// tell any interested entity
	GameState_propagateMessage((GameState)this, kResumeLevel);
#ifdef __DEBUG_TOOLS
	}
#endif
#ifdef __STAGE_EDITOR
	}
#endif
#ifdef __ANIMATION_EDITOR
	}
#endif
	
	// pause physical simulations
	Clock_pause(Game_getInGameClock(Game_getInstance()), false);
	
	this->mode = kPlaying;
}

// state's on message
static bool PlatformerLevelState_handleMessage(PlatformerLevelState this, void* owner, Telegram telegram)
{
	// process message
	switch (Telegram_getMessage(telegram))
    {
		case kSetUpLevel:

			{
				// print level name
	            StageDefinition* stageDefinition = this->stageDefinition;
	
	            if ((*stageDefinition).identifier)
	            {
				    char* strLevel = I18n_getText(I18n_getInstance(), STR_LEVEL);
				    char* strLevelName = (*stageDefinition).identifier;
	                Printing_text(Printing_getInstance(), strLevel, 20, 5, NULL);
	                Printing_text(Printing_getInstance(), strLevelName, 21 + strlen(strLevel), 5, NULL);
	            }
	
	            if ((*stageDefinition).name)
	            {
				    char* strLevelName = I18n_getText(I18n_getInstance(), (int)(*stageDefinition).name);
	                Printing_text(Printing_getInstance(), "\"", 17, 6, NULL);
	                Printing_text(Printing_getInstance(), strLevelName, 18, 6, NULL);
	                Printing_text(Printing_getInstance(), "\"", 18 + strlen(strLevelName), 6, NULL);
	            }
	
	
				// tell any interested entity
				GameState_propagateMessage((GameState)this, kSetUpLevel);
	
				// account for any entity's tranform modification during their initialization
				GameState_transform((GameState)this);
				
				// show level after 0.5 second
				MessageDispatcher_dispatchMessage(500, (Object)this, (Object)Game_getInstance(), kStartLevel, NULL);
	
				this->mode = kShowingUp;
			}
			break;

		case kStartLevel:

			// fade screen
			Screen_FXFadeIn(Screen_getInstance(), FADE_DELAY);

			// erase message in 1 second
			MessageDispatcher_dispatchMessage(2000, (Object)this, (Object)Game_getInstance(), kHideLevelMessage, NULL);
			
			// reset clock and restart
			Clock_reset(Game_getInGameClock(Game_getInstance()));
			Clock_start(Game_getInGameClock(Game_getInstance()));
			
			// want to know when the second has changed
			Object_addEventListener((Object)Game_getInGameClock(Game_getInstance()), (Object)this, (void (*)(Object))PlatformerLevelState_onSecondChange, __EVENT_SECOND_CHANGED);
			
			// add events
			Object_addEventListener((Object)this, (Object)this, (void (*)(Object))PlatformerLevelState_onCoinTaken, EVENT_COIN_TAKEN);
			Object_addEventListener((Object)this, (Object)this, (void (*)(Object))PlatformerLevelState_onKeyTaken, EVENT_KEY_TAKEN);

			// start physical simulation again
			PhysicalWorld_start(PhysicalWorld_getInstance());

			// tell any interested entity
			GameState_propagateMessage((GameState)this, kStartLevel);

			// restart clock
			// pause physical simulations
			Clock_reset(Game_getInGameClock(Game_getInstance()));
			Clock_start(Game_getInGameClock(Game_getInstance()));

			this->mode = kPlaying;
			break;

		case kHideLevelMessage:

			Printing_text(Printing_getInstance(), "                                                ", 0, 5, NULL);
			Printing_text(Printing_getInstance(), "                                                ", 0, 6, NULL);
			break;
			
		case kKeyPressed:

			if (kPlaying == this->mode)
            {
				Object_fireEvent((Object)this, EVENT_KEY_PRESSED);
			}
			return true;
			break;

		case kKeyUp:

			if (kPlaying == this->mode)
            {
				u16 releasedKey = *((u16*)Telegram_getExtraInfo(telegram));
	
				// check direction
				if (K_STA & releasedKey)
				{
					this->mode = kPaused;
					Game_pause(Game_getInstance(), (GameState)PauseScreenState_getInstance());
					break;
            	}

				Object_fireEvent((Object)this, EVENT_KEY_RELEASED);
			}
			return true;
			break;
			
		case kKeyHold:
			
			if (kPlaying == this->mode)
            {
				Object_fireEvent((Object)this, EVENT_KEY_HOLD);
			}
			return true;
			break;

		case kHeroDied:	
			
			Game_changeState(Game_getInstance(), (State)TitleScreenState_getInstance());
			return true;
			break;
	}

	return false;
}

// handle event
static void PlatformerLevelState_onSecondChange(PlatformerLevelState this, Object eventFirer)
{
	Clock_print(Game_getInGameClock(Game_getInstance()), 42, 26, "GUIFont");
}

// handle event
static void PlatformerLevelState_onCoinTaken(PlatformerLevelState this, Object eventFirer)
{
	PlatformerLevelState_printCoins(this);
}

// handle event
static void PlatformerLevelState_onKeyTaken(PlatformerLevelState this, Object eventFirer)
{
	PlatformerLevelState_printKeys(this);
}

// print number of lifes to gui
void PlatformerLevelState_printLifes(PlatformerLevelState this)
{
	Printing_int(Printing_getInstance(), Hero_getLifes(Hero_getInstance()), 4, 26, "GUIFont");
}

// print number of coins to gui
void PlatformerLevelState_printCoins(PlatformerLevelState this)
{
	Printing_int(Printing_getInstance(), Hero_getCoins(Hero_getInstance()), 10, 26, "GUIFont");
}

// print number of keys to gui
void PlatformerLevelState_printKeys(PlatformerLevelState this)
{
	Printing_int(Printing_getInstance(), Hero_getKeys(Hero_getInstance()), 16, 26, "GUIFont");
}

// print current level to gui
void PlatformerLevelState_printLevel(PlatformerLevelState this)
{
	Printing_text(Printing_getInstance(), (*this->stageDefinition).identifier, 35, 26, "GUIFont");
}

// set the next state to load
void PlatformerLevelState_setStage(PlatformerLevelState this, StageDefinition* stageDefinition)
{
	this->stageDefinition = stageDefinition;
}

// start a given level
void PlatformerLevelState_goToLevel(StageDefinition* stageDefinition)
{
	PlatformerLevelState this = PlatformerLevelState_getInstance();
	this->stageDefinition = stageDefinition;
	Game_changeState(Game_getInstance(), (State)this);
}