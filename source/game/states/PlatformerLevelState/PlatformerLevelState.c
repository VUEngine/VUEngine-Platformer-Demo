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
static void PlatformerLevelState_pause(PlatformerLevelState this, void* owner) {}
static void PlatformerLevelState_resume(PlatformerLevelState this, void* owner) {}
static int PlatformerLevelState_handleMessage(PlatformerLevelState this, void* owner, Telegram telegram);
static void PlatformerLevelState_onSecondChange(PlatformerLevelState this);
static void PlatformerLevelState_onCoinTaken(PlatformerLevelState this);


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
	GameState_loadStage((GameState)this, (StageDefinition*)this->stageDefinition, true, true);

	// playing by default
	this->mode = kPaused;
	
	// show up level after a little bit
	MessageDispatcher_dispatchMessage(1000, (Object)this, (Object)Game_getInstance(), kSetUpLevel, NULL);

	// reset clock and render time
	Clock_reset(Game_getInGameClock(Game_getInstance()));
	Clock_print(Game_getInGameClock(Game_getInstance()), 42, 26);
	
	// render gui values
	Printing_int(Hero_getLifes(Hero_getInstance()), 4, 26);
	Printing_int(Hero_getCoins(Hero_getInstance()), 10, 26);
	Printing_text("1-1", 35, 26);
}

// state's execute
static void PlatformerLevelState_execute(PlatformerLevelState this, void* owner)
{
	// call base
	GameState_execute((GameState)this, owner);
}

// state's exit
static void PlatformerLevelState_exit(PlatformerLevelState this, void* owner)
{
	Object_removeEventListener((Object)Game_getInGameClock(Game_getInstance()), (Object)this, (void (*)(Object))PlatformerLevelState_onSecondChange, __EVENT_SECOND_CHANGED);
	Object_removeEventListener((Object)this, (Object)this, (void (*)(Object))PlatformerLevelState_onCoinTaken, EVENT_COIN_TAKEN);

	// make a fade in
	Screen_FXFadeOut(Screen_getInstance(), FADE_DELAY);
	
	// call base
	GameState_exit((GameState)this, owner);
}

// state's on message
static int PlatformerLevelState_handleMessage(PlatformerLevelState this, void* owner, Telegram telegram)
{
	// process message
	switch(Telegram_getMessage(telegram))
    {
		case kSetUpLevel:

			// make a little bit of physical simulations so each entity is placed at the floor
			Clock_start(Game_getInGameClock(Game_getInstance()));
	
			// print level descriptor
			char* levelName = I18n_getText(I18n_getInstance(), STR_LEVEL_1_1_NAME);
			Printing_text("LEVEL 1-1", 20, 5);
			
			Printing_text("\"", 17, 6);
			Printing_text(levelName, 18, 6);
			Printing_text("\"", 18 + strlen(levelName), 6);
	
			// start physical simulation again
			PhysicalWorld_start(PhysicalWorld_getInstance());

			// pause physical simulations
			Clock_pause(Game_getInGameClock(Game_getInstance()), true);

			// tell any interested entity
			GameState_propagateMessage((GameState)this, kSetUpLevel);

			// account for any entity's tranform modification during their initialization
			GameState_transform((GameState)this);
			
			// show level after 0.5 second
			MessageDispatcher_dispatchMessage(500, (Object)this, (Object)Game_getInstance(), kStartLevel, NULL);

			this->mode = kShowingUp;
			break;

		case kStartLevel:

			// fade screen
			Screen_FXFadeIn(Screen_getInstance(), FADE_DELAY);

			// erase message in 1 second
			MessageDispatcher_dispatchMessage(2000, (Object)this, (Object)Game_getInstance(), kHideLevelMessage, NULL);
			
			// reset clock and restart
			Clock_reset(Game_getInGameClock(Game_getInstance()));
			Clock_start(Game_getInGameClock(Game_getInstance()));
			Object_addEventListener((Object)Game_getInGameClock(Game_getInstance()), (Object)this, (void (*)(Object))PlatformerLevelState_onSecondChange, __EVENT_SECOND_CHANGED);
			
			// add events
			Object_addEventListener((Object)this, (Object)this, (void (*)(Object))PlatformerLevelState_onCoinTaken, EVENT_COIN_TAKEN);
			
			// start physical simulation again
			PhysicalWorld_start(PhysicalWorld_getInstance());

			// tell any interested entity
			GameState_propagateMessage((GameState)this, kStartLevel);

			this->mode = kPlaying;
			break;

		case kHideLevelMessage:

			Printing_text("                                                ", 0, 5);
			Printing_text("                                                ", 0, 6);

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
static void PlatformerLevelState_onSecondChange(PlatformerLevelState this)
{
	Clock_print(Game_getInGameClock(Game_getInstance()), 42, 26);
}

// handle event
static void PlatformerLevelState_onCoinTaken(PlatformerLevelState this)
{
	Printing_int(Hero_getCoins(Hero_getInstance()), 10, 26);
}

// set the next state to load
void PlatformerLevelState_setStage(PlatformerLevelState this, StageROMDef* stageDefinition)
{
	this->stageDefinition = stageDefinition;
}

void PlatformerLevelState_goToLevel1_1Room1() 
{
	PlatformerLevelState this = PlatformerLevelState_getInstance();
	this->stageDefinition = &LEVEL_1_1_ROOM_1_ST;
	Game_changeState(Game_getInstance(), (State)this);
}

void PlatformerLevelState_goToLevel1_1Room2() 
{
	PlatformerLevelState this = PlatformerLevelState_getInstance();
	this->stageDefinition = &LEVEL_1_1_ROOM_2_ST;
	Game_changeState(Game_getInstance(), (State)this);
}

void PlatformerLevelState_goToLevel1_2Room1() 
{
	PlatformerLevelState this = PlatformerLevelState_getInstance();
	this->stageDefinition = &LEVEL_1_2_ROOM_1_ST;
	Game_changeState(Game_getInstance(), (State)this);
}

void PlatformerLevelState_goToLevel1_3Room1() 
{
	PlatformerLevelState this = PlatformerLevelState_getInstance();
	this->stageDefinition = &LEVEL_1_3_ROOM_1_ST;
	Game_changeState(Game_getInstance(), (State)this);
}
