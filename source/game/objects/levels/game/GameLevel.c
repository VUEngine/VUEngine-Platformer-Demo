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

#include <GameLevel.h>
#include <TitleScreen.h>
#include <objects.h>
#include <macros.h>

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 												PROTOTYPES
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

static void GameLevel_destructor(GameLevel this);

// class's constructor
static void GameLevel_constructor(GameLevel this);

// state's enter
static void GameLevel_enter(GameLevel this, void* owner);

// state's execute
static void GameLevel_execute(GameLevel this, void* owner);

// state's enter
static void GameLevel_exit(GameLevel this, void* owner);

// state's execute
static void GameLevel_pause(GameLevel this, void* owner){}

// state's execute
static void GameLevel_resume(GameLevel this, void* owner){}

// state's on message
static int GameLevel_handleMessage(GameLevel this, void* owner, Telegram telegram);

// handle event
static void GameLevel_onSecondChange(GameLevel this);

/* ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * 											CLASS'S DEFINITION
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------
 */

__CLASS_DEFINITION(GameLevel);


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
__SINGLETON_DYNAMIC(GameLevel);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's constructor
static void GameLevel_constructor(GameLevel this){
		
	__CONSTRUCT_BASE(Level);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class's destructor
static void GameLevel_destructor(GameLevel this){
	
	// destroy base
	__SINGLETON_DESTROY(Level);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's enter
static void GameLevel_enter(GameLevel this, void* owner){
	
	Optical optical = Game_getOptical(Game_getInstance());
	optical.verticalViewPointCenter = ITOFIX19_13(112 + 112/2);
	Game_setOptical(Game_getInstance(), optical);

	//load stage
	Level_loadStage((Level)this, (StageDefinition*)&LEVEL_0_0_0_ST, true, false);

	// playing by default
	this->mode = kPaused;
	
	// show up level after a little bit
	MessageDispatcher_dispatchMessage(500, (Object)this, (Object)Game_getInstance(), kSetUpLevel, NULL);

	Clock_reset(Game_getInGameClock(Game_getInstance()));
	Clock_print(Game_getInGameClock(Game_getInstance()), 42, 27);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's execute
static void GameLevel_execute(GameLevel this, void* owner){
	
	// call base
	Level_execute((Level)this, owner);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's exit 
static void GameLevel_exit(GameLevel this, void* owner){
	
	Object_removeEventListener((Object)Game_getInGameClock(Game_getInstance()), (Object)this, (void (*)(Object))GameLevel_onSecondChange, __EVENT_SECOND_CHANGED);

	// make a fade in
	Screen_FXFadeOut(Screen_getInstance(), FADE_DELAY);

	// destroy the state
	__DELETE(this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// state's on message
static int GameLevel_handleMessage(GameLevel this, void* owner, Telegram telegram){

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
			Object_addEventListener((Object)Game_getInGameClock(Game_getInstance()), (Object)this, (void (*)(Object))GameLevel_onSecondChange, __EVENT_SECOND_CHANGED);
			
			// start physical simulation again
			PhysicalWorld_start(PhysicalWorld_getInstance());

			// tell any interested entity
			Level_propagateMessage((Level)this, kStartLevel);

			this->mode = kPlaying;
			break;

		case kHideStartUpMessage:
			
			Printing_text("               ", 21, 6);
			break;
			
		case kKeyPressed:	
			
			// update level's stage
			if(kPlaying == this->mode){
				
				return Level_handleMessage((Level)this, owner, telegram);
			}
			
			if(kPaused == this->mode){
				
				return true;
			}
			
			break;
			
		case kKeyUp:
		case kKeyHold:
			
			return Level_handleMessage((Level)this, owner, telegram);
			break;

		case kHeroDied:	
			
			Game_changeState(Game_getInstance(), (State)TitleScreen_getInstance());
			return true;
			break;			
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// handle event
static void GameLevel_onSecondChange(GameLevel this) {
	
	Clock_print(Game_getInGameClock(Game_getInstance()), 42, 27);
}
