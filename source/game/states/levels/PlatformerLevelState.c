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

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												INCLUDES
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

#include <Game.h>
#include <Screen.h>
#include <Printing.h>
#include <MessageDispatcher.h>
#include <PhysicalWorld.h>

#include <PlatformerLevelState.h>
#include <TitleScreenState.h>
#include "stages.h"
#include <macros.h>

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												PROTOTYPES
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

static void PlatformerLevelState_destructor(PlatformerLevelState this);

// class's constructor
static void PlatformerLevelState_constructor(PlatformerLevelState this);

// state's enter
static void PlatformerLevelState_enter(PlatformerLevelState this, void* owner);

// state's execute
static void PlatformerLevelState_execute(PlatformerLevelState this, void* owner);

// state's enter
static void PlatformerLevelState_exit(PlatformerLevelState this, void* owner);

// state's execute
static void PlatformerLevelState_pause(PlatformerLevelState this, void* owner){}

// state's execute
static void PlatformerLevelState_resume(PlatformerLevelState this, void* owner){}

// state's on message
static int PlatformerLevelState_handleMessage(PlatformerLevelState this, void* owner, Telegram telegram);

// handle event
static void PlatformerLevelState_onSecondChange(PlatformerLevelState this);

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 											CLASS'S DEFINITION
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

__CLASS_DEFINITION(PlatformerLevelState);


/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												CLASS'S METHODS
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// it's a singleton
__SINGLETON_DYNAMIC(PlatformerLevelState);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's constructor
static void PlatformerLevelState_constructor(PlatformerLevelState this){
		
	__CONSTRUCT_BASE(GameState);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's destructor
static void PlatformerLevelState_destructor(PlatformerLevelState this){
	
	// destroy base
	__SINGLETON_DESTROY(GameState);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's enter
static void PlatformerLevelState_enter(PlatformerLevelState this, void* owner){
	
	Optical optical = Game_getOptical(Game_getInstance());
	optical.verticalViewPointCenter = ITOFIX19_13(112 + 112/2);
	Game_setOptical(Game_getInstance(), optical);

	//load stage
	GameState_loadStage((GameState)this, (StageDefinition*)&LEVEL_0_0_0_ST, true, true);

	// playing by default
	this->mode = kPaused;
	
	// show up level after a little bit
	MessageDispatcher_dispatchMessage(500, (Object)this, (Object)Game_getInstance(), kSetUpLevel, NULL);

	Clock_reset(Game_getInGameClock(Game_getInstance()));
	Clock_print(Game_getInGameClock(Game_getInstance()), 42, 27);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's execute
static void PlatformerLevelState_execute(PlatformerLevelState this, void* owner){
	
	// call base
	GameState_execute((GameState)this, owner);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's exit 
static void PlatformerLevelState_exit(PlatformerLevelState this, void* owner){
	
	Object_removeEventListener((Object)Game_getInGameClock(Game_getInstance()), (Object)this, (void (*)(Object))PlatformerLevelState_onSecondChange, __EVENT_SECOND_CHANGED);

	// make a fade in
	Screen_FXFadeOut(Screen_getInstance(), FADE_DELAY);

	// destroy the state
	__DELETE(this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's on message
static int PlatformerLevelState_handleMessage(PlatformerLevelState this, void* owner, Telegram telegram){

	// process message
	switch(Telegram_getMessage(telegram)){

		case kSetUpLevel:

			// make a little bit of physical simulations so each entity is placed at the floor
			Clock_start(Game_getInGameClock(Game_getInstance()));
	
			// start physical simulation again
			PhysicalWorld_start(PhysicalWorld_getInstance());

			// show level after 0.5 second
			MessageDispatcher_dispatchMessage(500, (Object)this, (Object)Game_getInstance(), kShowUpLevel, NULL);

			this->mode = kSettingUp;
			break;	

		case kShowUpLevel:

			Printing_text("GET READY", 21, 6);

			// pause physical simulations
			Clock_pause(Game_getInGameClock(Game_getInstance()), true);
			
			// fade screen
			Screen_FXFadeIn(Screen_getInstance(), FADE_DELAY);


			// start game in 1.5 seconds
			MessageDispatcher_dispatchMessage(1500, (Object)this, (Object)Game_getInstance(), kStartLevel, NULL);

			this->mode = kShowingUp;
			break;
			
		case kStartLevel:

			Printing_text("    GO!        ", 21, 6);
			
			// erase message in 1 second
			MessageDispatcher_dispatchMessage(1000, (Object)this, (Object)Game_getInstance(), kHideStartUpMessage, NULL);
			
			// reset clock and restart
			Clock_reset(Game_getInGameClock(Game_getInstance()));
			Clock_start(Game_getInGameClock(Game_getInstance()));
			Object_addEventListener((Object)Game_getInGameClock(Game_getInstance()), (Object)this, (void (*)(Object))PlatformerLevelState_onSecondChange, __EVENT_SECOND_CHANGED);
			
			// start physical simulation again
			PhysicalWorld_start(PhysicalWorld_getInstance());

			// tell any interested entity
			GameState_propagateMessage((GameState)this, kStartLevel);

			this->mode = kPlaying;
			break;

		case kHideStartUpMessage:
			
			Printing_text("               ", 21, 6);
			break;
			
		case kKeyPressed:	
			
			// update level's stage
			if(kPlaying == this->mode){
				
				return GameState_handleMessage((GameState)this, owner, telegram);
			}
			
			if(kPaused == this->mode){
				
				return true;
			}
			
			break;
			
		case kKeyUp:
		case kKeyHold:
			
			return GameState_handleMessage((GameState)this, owner, telegram);
			break;

		case kHeroDied:	
			
			Game_changeState(Game_getInstance(), (State)TitleScreenState_getInstance());
			return true;
			break;			
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// handle event
static void PlatformerLevelState_onSecondChange(PlatformerLevelState this) {
	
	Clock_print(Game_getInGameClock(Game_getInstance()), 42, 27);
}
