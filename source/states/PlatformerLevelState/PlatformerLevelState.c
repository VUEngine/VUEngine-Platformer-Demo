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
#include <Screen.h>
#include <Printing.h>
#include <MessageDispatcher.h>
#include <PhysicalWorld.h>
#include <I18n.h>
#include <PlatformerLevelState.h>
#include <AdjustmentScreenState.h>
#include <TitleScreenState.h>
#include <PauseScreenState.h>
#include <Hero.h>
#include "../stages/stages.h"
#include <macros.h>
#include <Languages.h>
#include <objects.h>
#include <UserDataManager.h>



//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void PlatformerLevelState_constructor(PlatformerLevelState this);
static void PlatformerLevelState_destructor(PlatformerLevelState this);
static void PlatformerLevelState_enter(PlatformerLevelState this, void* owner);
static void PlatformerLevelState_exit(PlatformerLevelState this, void* owner);
static void PlatformerLevelState_suspend(PlatformerLevelState this, void* owner);
static void PlatformerLevelState_resume(PlatformerLevelState this, void* owner);
static bool PlatformerLevelState_handleMessage(PlatformerLevelState this, void* owner, Telegram telegram);
static void PlatformerLevelState_getEntityNamesToIngnore(PlatformerLevelState this, VirtualList entityNamesToIgnore);
static void PlatformerLevelState_onSecondChange(PlatformerLevelState this, Object eventFirer);
static void PlatformerLevelState_onHitTaken(PlatformerLevelState this, Object eventFirer);
static void PlatformerLevelState_onCoinTaken(PlatformerLevelState this, Object eventFirer);
static void PlatformerLevelState_onKeyTaken(PlatformerLevelState this, Object eventFirer);
void PlatformerLevelState_printEnergy(PlatformerLevelState this);
void PlatformerLevelState_printCoins(PlatformerLevelState this);
void PlatformerLevelState_printKey(PlatformerLevelState this);
void PlatformerLevelState_printLevel(PlatformerLevelState this);
void PlatformerLevelState_setModeToPaused(PlatformerLevelState this);
void PlatformerLevelState_setModeToPlaying(PlatformerLevelState this);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(PlatformerLevelState, GameState);
__SINGLETON(PlatformerLevelState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void PlatformerLevelState_constructor(PlatformerLevelState this)
{
	__CONSTRUCT_BASE();

	this->platformerStageDefinition = (PlatformerStageDefinition*)&LEVEL_1_MAIN_1_MAIN_1_ST;

	this->heroLastPosition.x = 0;
	this->heroLastPosition.y = 0;
	this->heroLastPosition.z = 0;
	
	this->isExitingRoom = false;
}

// class's destructor
static void PlatformerLevelState_destructor(PlatformerLevelState this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

static void PlatformerLevelState_getEntityNamesToIngnore(PlatformerLevelState this, VirtualList entityNamesToIgnore)
{
	ASSERT(entityNamesToIgnore, "PlatformerLevelState::getEntityNamesToIngnore: null entityNamesToIgnore");

	/*
	int i = 0;
	for(;this->platformerStageDefinition->stageDefinition.entities[i].entityDefinition; i++)
	{
		if(UserDataManager_getCoinStatus(UserDataManager_getInstance(), this->platformerStageDefinition->stageDefinition.entities[i].name))
		{
			VirtualList_pushBack(entityNamesToIgnore, this->platformerStageDefinition->stageDefinition.entities[i].name);
		}
	}
	*/
}

// state's enter
static void PlatformerLevelState_enter(PlatformerLevelState this, void* owner)
{
	VirtualList entityNamesToIgnore = __NEW(VirtualList);
	PlatformerLevelState_getEntityNamesToIngnore(this, entityNamesToIgnore);
	
	// check if exiting room
	if(this->isExitingRoom)
	{
		VBVec3D screenPosition = 
		{
			this->heroLastPosition.x - ITOFIX19_13(__SCREEN_WIDTH >> 1),
			this->heroLastPosition.y - ITOFIX19_13(__SCREEN_HEIGHT >> 1),
			this->heroLastPosition.z
		};
		
		// set world's limits
		Screen_setStageSize(Screen_getInstance(), this->platformerStageDefinition->stageDefinition.size);

		// must set the screen's position before loading the stage
		Screen_setPosition(Screen_getInstance(), screenPosition);
	    
		// load stage
		GameState_loadStage(__GET_CAST(GameState, this), (StageDefinition*)&(this->platformerStageDefinition->stageDefinition), entityNamesToIgnore, false);

		Container hero = Container_getChildByName(__GET_CAST(Container, this->stage), HERO_NAME, true);

		if(!hero)
		{
			PositionedEntity positionedEntity =
			{
				&HERO_AC, 				
				{
					this->heroLastPosition.x, 
					this->heroLastPosition.y, 
					this->heroLastPosition.z
				}, 
				HERO_NAME, 
				NULL, 
				NULL,
				false
			};

			hero = __GET_CAST(Container, Stage_addPositionedEntity(this->stage, &positionedEntity, true));
			
			// make sure that the streaming doesn't load the hero again
			Stage_registerEntityId(this->stage, Container_getId(hero), &HERO_AC);
		}
		else
		{
			Actor_setPosition(__GET_CAST(Actor, hero), &this->heroLastPosition);
		}
		
		this->isExitingRoom = false;
	}
	else
	{
		GameState_loadStage(__GET_CAST(GameState, this), (StageDefinition*)&(this->platformerStageDefinition->stageDefinition), entityNamesToIgnore, true);
	}
	
	__DELETE(entityNamesToIgnore);

	// playing by default
	PlatformerLevelState_setModeToPaused(this);
	
	// show up level after a little bit
	MessageDispatcher_dispatchMessage(500, __GET_CAST(Object, this), __GET_CAST(Object, Game_getInstance()), kSetUpLevel, NULL);

	// reset clock and render time
	Clock_reset(Game_getInGameClock(Game_getInstance()));
	Clock_print(Game_getInGameClock(Game_getInstance()), 42, 26, "GUIFont");
	
	// make a little bit of physical simulations so each entity is placed at the floor
	Clock_start(Game_getInGameClock(Game_getInstance()));
		
	// render gui values
	PlatformerLevelState_printEnergy(this);
	PlatformerLevelState_printCoins(this);
	PlatformerLevelState_printKey(this);
	PlatformerLevelState_printLevel(this);
}

// state's exit
static void PlatformerLevelState_exit(PlatformerLevelState this, void* owner)
{
	Object_removeEventListener(__GET_CAST(Object, Game_getInGameClock(Game_getInstance())), __GET_CAST(Object, this), (void (*)(Object, Object))PlatformerLevelState_onSecondChange, __EVENT_SECOND_CHANGED);
	Object_removeEventListener(__GET_CAST(Object, this), __GET_CAST(Object, this), (void (*)(Object, Object))PlatformerLevelState_onHitTaken, EVENT_HIT_TAKEN);
	Object_removeEventListener(__GET_CAST(Object, this), __GET_CAST(Object, this), (void (*)(Object, Object))PlatformerLevelState_onCoinTaken, EVENT_COIN_TAKEN);
	Object_removeEventListener(__GET_CAST(Object, this), __GET_CAST(Object, this), (void (*)(Object, Object))PlatformerLevelState_onKeyTaken, EVENT_KEY_TAKEN);

	// make a fade in
	Screen_startEffect(Screen_getInstance(), kFadeOut, FADE_DELAY);
	
	// call base
	GameState_exit(__GET_CAST(GameState, this), owner);
}

static void PlatformerLevelState_suspend(PlatformerLevelState this, void* owner)
{
	// pause physical simulations
	Clock_pause(Game_getInGameClock(Game_getInstance()), true);

#ifdef __DEBUG_TOOLS
	if(!Game_isEnteringSpecialMode(Game_getInstance()))
#endif
#ifdef __STAGE_EDITOR
	if(!Game_isEnteringSpecialMode(Game_getInstance()))
#endif
#ifdef __ANIMATION_EDITOR
	if(!Game_isEnteringSpecialMode(Game_getInstance()))
#endif
	// make a fade in
    Screen_startEffect(Screen_getInstance(), kFadeOut, FADE_DELAY);

	GameState_suspend(__GET_CAST(GameState, this), owner);
}

static void PlatformerLevelState_resume(PlatformerLevelState this, void* owner)
{
	GameState_resume(__GET_CAST(GameState, this), owner);

#ifdef __DEBUG_TOOLS
	if(!Game_isExitingSpecialMode(Game_getInstance()))
	{
#endif
#ifdef __STAGE_EDITOR
	if(!Game_isExitingSpecialMode(Game_getInstance()))
	{
#endif
#ifdef __ANIMATION_EDITOR
	if(!Game_isExitingSpecialMode(Game_getInstance()))
	{
#endif
	
	// reprint info
	Clock_print(Game_getInGameClock(Game_getInstance()), 42, 26, "GUIFont");
	
	// render gui values
	PlatformerLevelState_printEnergy(this);
	PlatformerLevelState_printCoins(this);
	PlatformerLevelState_printKey(this);
	PlatformerLevelState_printLevel(this);

	// make a fade in
    Screen_startEffect(Screen_getInstance(), kFadeIn, FADE_DELAY >> 1);
	
	// tell any interested entity
	GameState_propagateMessage(__GET_CAST(GameState, this), kResumeLevel);

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

	PlatformerLevelState_setModeToPlaying(this);
}

// state's on message
static bool PlatformerLevelState_handleMessage(PlatformerLevelState this, void* owner, Telegram telegram)
{
	// process message
	switch(Telegram_getMessage(telegram))
    {
		case kSetUpLevel:

			{
				// print level name
	            PlatformerStageDefinition* platformerStageDefinition = this->platformerStageDefinition;
	
	            if((*platformerStageDefinition).identifier)
	            {
				    char* strLevel = I18n_getText(I18n_getInstance(), STR_LEVEL);
				    char* strLevelName = (*platformerStageDefinition).identifier;
	                Printing_text(Printing_getInstance(), strLevel, 20, 5, NULL);
	                Printing_text(Printing_getInstance(), strLevelName, 21 + strlen(strLevel), 5, NULL);
	            }
	
	            if((*platformerStageDefinition).name)
	            {
				    char* strLevelName = I18n_getText(I18n_getInstance(), (int)(*platformerStageDefinition).name);
	                Printing_text(Printing_getInstance(), "\"", 17, 6, "GUIFont");
	                Printing_text(Printing_getInstance(), strLevelName, 18, 6, "GUIFont");
	                Printing_text(Printing_getInstance(), "\"", 18 + strlen(strLevelName), 6, "GUIFont");
	            }
	
				// tell any interested entity
				GameState_propagateMessage(__GET_CAST(GameState, this), kSetUpLevel);
	
				// account for any entity's tranform modification during their initialization
				GameState_transform(__GET_CAST(GameState, this));
				
				// show level after 0.5 second
				MessageDispatcher_dispatchMessage(500, __GET_CAST(Object, this), __GET_CAST(Object, Game_getInstance()), kStartLevel, NULL);
	
				this->mode = kShowingUp;
			}
			break;

		case kStartLevel:

			// fade screen
		    Screen_startEffect(Screen_getInstance(), kFadeIn, FADE_DELAY);

			// erase message in 1 second
			MessageDispatcher_dispatchMessage(2000, __GET_CAST(Object, this), __GET_CAST(Object, Game_getInstance()), kHideLevelMessage, NULL);
			
			// reset clock and restart
			Clock_reset(Game_getInGameClock(Game_getInstance()));
			//Clock_start(Game_getInGameClock(Game_getInstance()));
			
			// want to know when the second has changed
			Object_addEventListener(__GET_CAST(Object, Game_getInGameClock(Game_getInstance())), __GET_CAST(Object, this), (void (*)(Object, Object))PlatformerLevelState_onSecondChange, __EVENT_SECOND_CHANGED);
			
			// add events
			Object_addEventListener(__GET_CAST(Object, this), __GET_CAST(Object, this), (void (*)(Object, Object))PlatformerLevelState_onHitTaken, EVENT_HIT_TAKEN);
			Object_addEventListener(__GET_CAST(Object, this), __GET_CAST(Object, this), (void (*)(Object, Object))PlatformerLevelState_onCoinTaken, EVENT_COIN_TAKEN);
			Object_addEventListener(__GET_CAST(Object, this), __GET_CAST(Object, this), (void (*)(Object, Object))PlatformerLevelState_onKeyTaken, EVENT_KEY_TAKEN);

			// tell any interested entity
			GameState_propagateMessage(__GET_CAST(GameState, this), kStartLevel);

			// restart clock
			// pause physical simulations
			Clock_reset(Game_getInGameClock(Game_getInstance()));
			//Clock_start(Game_getInGameClock(Game_getInstance()));

        	PlatformerLevelState_setModeToPlaying(this);
			break;

		case kHideLevelMessage:

			Printing_text(Printing_getInstance(), "                                                ", 0, 5, NULL);
			Printing_text(Printing_getInstance(), "                                                ", 0, 6, NULL);
			Printing_text(Printing_getInstance(), "                                                ", 0, 7, NULL);
			break;
			
		case kKeyPressed:

			if(kPlaying == this->mode)
            {
				u16 pressedKey = *((u16*)Telegram_getExtraInfo(telegram));

				if(K_SEL & pressedKey)
				{
    				// adjustment screen
	                PlatformerLevelState_setModeToPaused(this);
					SplashScreenState_setNextstate(__GET_CAST(SplashScreenState, AdjustmentScreenState_getInstance()), NULL);
					Game_pause(Game_getInstance(), __GET_CAST(GameState, AdjustmentScreenState_getInstance()));
					break;
            	}
				else if(K_STA & pressedKey)
                {
                    // pause screen
					PlatformerLevelState_setModeToPaused(this);
                    Game_pause(Game_getInstance(), __GET_CAST(GameState, PauseScreenState_getInstance()));
                    break;
                }
				
				Object_fireEvent(__GET_CAST(Object, this), EVENT_KEY_PRESSED);
			}
			return true;
			break;

		case kKeyReleased:

			if(kPlaying == this->mode)
            {
				Object_fireEvent(__GET_CAST(Object, this), EVENT_KEY_RELEASED);
			}
			return true;
			break;
			
		case kKeyHold:
			
			if(kPlaying == this->mode)
            {
				Object_fireEvent(__GET_CAST(Object, this), EVENT_KEY_HOLD);
			}
			return true;
			break;

		case kHeroDied:	
			
			Game_changeState(Game_getInstance(), __GET_CAST(GameState, TitleScreenState_getInstance()));
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
static void PlatformerLevelState_onHitTaken(PlatformerLevelState this, Object eventFirer)
{
	PlatformerLevelState_printEnergy(this);
}

// handle event
static void PlatformerLevelState_onCoinTaken(PlatformerLevelState this, Object eventFirer)
{
	PlatformerLevelState_printCoins(this);
}

// handle event
static void PlatformerLevelState_onKeyTaken(PlatformerLevelState this, Object eventFirer)
{
	PlatformerLevelState_printKey(this);
}

// print hero's energy to gui
void PlatformerLevelState_printEnergy(PlatformerLevelState this)
{
	Printing_text(Printing_getInstance(), "\x7B\x7B\x7B", 4, 26, "GUIFont");
    u8 i;
	for(i=0; i < Hero_getEnergy(Hero_getInstance()); i++)
	{
    	Printing_text(Printing_getInstance(), "\x60", 4+i, 26, "GUIFont");
	}
}

// print number of coins to gui
void PlatformerLevelState_printCoins(PlatformerLevelState this)
{
    u8 coins = Hero_getCoins(Hero_getInstance());
    u8 printPos = 13;
	Printing_text(Printing_getInstance(), "000/100", 11, 26, "GUIFont");
    if(coins >= 10)
    {
        printPos--;
    }
    if(coins >= 100)
    {
        printPos--;
    }
    Printing_int(Printing_getInstance(), coins, printPos, 26, "GUIFont");
}

// print keys icon to gui
void PlatformerLevelState_printKey(PlatformerLevelState this)
{
    if(Hero_hasKey(Hero_getInstance())) {
	    Printing_text(Printing_getInstance(), "\x7E\x7F", 24, 26, "GUIFont");
    }
    else
    {
	    Printing_text(Printing_getInstance(), "  ", 24, 26, "GUIFont");
    }
}

// print current level to gui
void PlatformerLevelState_printLevel(PlatformerLevelState this)
{
	Printing_text(Printing_getInstance(), (*this->platformerStageDefinition).identifier, 35, 26, "GUIFont");
}

// set the next state to load
void PlatformerLevelState_setStage(PlatformerLevelState this, PlatformerStageDefinition* platformerStageDefinition)
{
	this->platformerStageDefinition = platformerStageDefinition;
}

// start a given level
void PlatformerLevelState_goToLevel(PlatformerStageDefinition* platformerStageDefinition)
{
	PlatformerLevelState this = PlatformerLevelState_getInstance();
	this->platformerStageDefinition = platformerStageDefinition;
	Game_changeState(Game_getInstance(), __GET_CAST(GameState, this));
}

// start a given room
void PlatformerLevelState_enterRoom(PlatformerStageDefinition* platformerStageDefinition)
{
	PlatformerLevelState this = PlatformerLevelState_getInstance();

	// save hero's actual position
	Hero hero = __GET_CAST(Hero, Container_getChildByName(__GET_CAST(Container, this->stage), HERO_NAME, false));
	ASSERT(hero, "PlatformerLevelState::enterRoom: hero not found");

	if(hero)
	{
		this->heroLastPosition = *Container_getLocalPosition(__GET_CAST(Container, hero));
		this->isExitingRoom = false;
	}

	this->platformerStageDefinition = platformerStageDefinition;
	
	Game_changeState(Game_getInstance(), __GET_CAST(GameState, this));
}

// exit a given room
void PlatformerLevelState_exitRoom(PlatformerStageDefinition* platformerStageDefinition)
{
	PlatformerLevelState this = PlatformerLevelState_getInstance();
	this->platformerStageDefinition = platformerStageDefinition;
	this->isExitingRoom = true;
	Game_changeState(Game_getInstance(), __GET_CAST(GameState, this));
}

// set paused mode
void PlatformerLevelState_setModeToPaused(PlatformerLevelState this)
{
	this->mode = kPaused;
}

// set kplaying mode
void PlatformerLevelState_setModeToPlaying(PlatformerLevelState this)
{
	this->mode = kPlaying;
}