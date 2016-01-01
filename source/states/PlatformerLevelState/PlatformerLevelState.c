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
#include <CustomScreenMovementManager.h>


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

	this->platformerStageDefinition = (PlatformerStageDefinition*)&LEVEL_1_MAIN_ST;

	this->heroLastPosition.x = 0;
	this->heroLastPosition.y = 0;
	this->heroLastPosition.z = 0;
	
	this->isExitingRoom = false;
	
	// set the custom movement screen manager now
	Screen_setScreenMovementManager(Screen_getInstance(), __SAFE_CAST(ScreenMovementManager, CustomScreenMovementManager_getInstance()));
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
	Game_disableKeypad(Game_getInstance());

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
		GameState_loadStage(__SAFE_CAST(GameState, this), (StageDefinition*)&(this->platformerStageDefinition->stageDefinition), entityNamesToIgnore, false);

		Container hero = Container_getChildByName(__SAFE_CAST(Container, this->stage), HERO_NAME, true);

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

			hero = __SAFE_CAST(Container, Stage_addPositionedEntity(this->stage, &positionedEntity, true));
			
			// make sure that the streaming doesn't load the hero again
			Stage_registerEntityId(this->stage, Container_getId(hero), &HERO_AC);
		}
		else
		{
			Actor_setPosition(__SAFE_CAST(Actor, hero), &this->heroLastPosition);
		}
		
		this->isExitingRoom = false;
	}
	else
	{
		GameState_loadStage(__SAFE_CAST(GameState, this), (StageDefinition*)&(this->platformerStageDefinition->stageDefinition), entityNamesToIgnore, true);
	}
	
	__DELETE(entityNamesToIgnore);

	// playing by default
	PlatformerLevelState_setModeToPaused(this);
	
	// show up level after a little bit
	MessageDispatcher_dispatchMessage(1000, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kSetUpLevel, NULL);

	// reset clock
	Game_startClocks(Game_getInstance());
		
	// render gui values
    Object_fireEvent(__SAFE_CAST(Object, this), EVENT_LEVEL_ENTER);
}

// state's exit
static void PlatformerLevelState_exit(PlatformerLevelState this, void* owner)
{
	// make a fade out
	Screen_startEffect(Screen_getInstance(), kFadeOut, FADE_DELAY);
	
	// call base
	GameState_exit(__SAFE_CAST(GameState, this), owner);
}

static void PlatformerLevelState_suspend(PlatformerLevelState this, void* owner)
{
	// pause physical simulations
	Game_pauseInGameClock(Game_getInstance(), true);
	Game_pausePhysics(Game_getInstance(), true);

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

	GameState_suspend(__SAFE_CAST(GameState, this), owner);
}

static void PlatformerLevelState_resume(PlatformerLevelState this, void* owner)
{
	GameState_resume(__SAFE_CAST(GameState, this), owner);

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

	// render gui values
    Object_fireEvent(__SAFE_CAST(Object, this), EVENT_LEVEL_RESUME);

	// make a fade in
    Screen_startEffect(Screen_getInstance(), kFadeIn, FADE_DELAY);
	
	// tell any interested entity
	GameState_propagateMessage(__SAFE_CAST(GameState, this), kResumeLevel);

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
	Game_pauseInGameClock(Game_getInstance(), false);
	Game_pausePhysics(Game_getInstance(), false);

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
	
	            if((*platformerStageDefinition).name)
	            {
				    char* strLevelName = I18n_getText(I18n_getInstance(), (int)(*platformerStageDefinition).name);
	                Printing_text(Printing_getInstance(), "\"", 17, 6, "GUIFont");
	                Printing_text(Printing_getInstance(), strLevelName, 18, 6, "GUIFont");
	                Printing_text(Printing_getInstance(), "\"", 18 + strlen(strLevelName), 6, "GUIFont");

                    if((*platformerStageDefinition).identifier)
                    {
                        char* strLevel = I18n_getText(I18n_getInstance(), STR_LEVEL);
                        char* strLevelName = (*platformerStageDefinition).identifier;
                        Printing_text(Printing_getInstance(), strLevel, 20, 5, NULL);
                        Printing_text(Printing_getInstance(), strLevelName, 21 + strlen(strLevel), 5, NULL);
                    }
	            }
	
				// tell any interested entity
				GameState_propagateMessage(__SAFE_CAST(GameState, this), kSetUpLevel);
	
				// account for any entity's tranform modification during their initialization
				GameState_transform(__SAFE_CAST(GameState, this));
				
				// show level after 0.5 second
				MessageDispatcher_dispatchMessage(500, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kStartLevel, NULL);
	
				this->mode = kShowingUp;
			}
			break;

		case kStartLevel:

			// fade screen
		    Screen_startEffect(Screen_getInstance(), kFadeIn, FADE_DELAY);

			// erase message in 1 second
			MessageDispatcher_dispatchMessage(2000, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kHideLevelMessage, NULL);
			
			// reset clock and restart
			Clock_reset(Game_getInGameClock(Game_getInstance()));
			//Clock_start(Game_getInGameClock(Game_getInstance()));

			// tell any interested entity
			GameState_propagateMessage(__SAFE_CAST(GameState, this), kStartLevel);

			// restart clock
			// pause physical simulations
			Game_startInGameClock(Game_getInstance());

        	PlatformerLevelState_setModeToPlaying(this);
        	
        	Game_enableKeypad(Game_getInstance());

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
					SplashScreenState_setNextstate(__SAFE_CAST(SplashScreenState, AdjustmentScreenState_getInstance()), NULL);
					Game_pause(Game_getInstance(), __SAFE_CAST(GameState, AdjustmentScreenState_getInstance()));
					break;
            	}
				else if(K_STA & pressedKey)
                {
                    // pause screen
					PlatformerLevelState_setModeToPaused(this);
                    Game_pause(Game_getInstance(), __SAFE_CAST(GameState, PauseScreenState_getInstance()));
                    break;
                }
				
				Object_fireEvent(__SAFE_CAST(Object, this), EVENT_KEY_PRESSED);
			}
			return true;
			break;

		case kKeyReleased:

			if(kPlaying == this->mode)
            {
				Object_fireEvent(__SAFE_CAST(Object, this), EVENT_KEY_RELEASED);
			}
			return true;
			break;
			
		case kKeyHold:
			
			if(kPlaying == this->mode)
            {
				Object_fireEvent(__SAFE_CAST(Object, this), EVENT_KEY_HOLD);
			}
			return true;
			break;

		case kHeroDied:	
			
			Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, TitleScreenState_getInstance()));
			return true;
			break;
	}

	return false;
}

// set the next state to load
void PlatformerLevelState_setStage(PlatformerLevelState this, PlatformerStageDefinition* platformerStageDefinition)
{
	this->platformerStageDefinition = platformerStageDefinition;
}

// get current stage's definition
PlatformerStageDefinition* PlatformerLevelState_getStage(PlatformerLevelState this)
{
	return this->platformerStageDefinition;
}

// start a given level
void PlatformerLevelState_goToLevel(PlatformerStageDefinition* platformerStageDefinition)
{
	PlatformerLevelState this = PlatformerLevelState_getInstance();
	this->platformerStageDefinition = platformerStageDefinition;
	Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, this));
}

// start a given room
void PlatformerLevelState_enterRoom(PlatformerStageDefinition* platformerStageDefinition)
{
	PlatformerLevelState this = PlatformerLevelState_getInstance();

	// save hero's actual position
	Hero hero = __SAFE_CAST(Hero, Container_getChildByName(__SAFE_CAST(Container, this->stage), HERO_NAME, false));
	ASSERT(hero, "PlatformerLevelState::enterRoom: hero not found");

	if(hero)
	{
		this->heroLastPosition = *Container_getLocalPosition(__SAFE_CAST(Container, hero));
		this->isExitingRoom = false;
	}

	this->platformerStageDefinition = platformerStageDefinition;
	
	Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, this));
}

// exit a given room
void PlatformerLevelState_exitRoom(PlatformerStageDefinition* platformerStageDefinition)
{
	PlatformerLevelState this = PlatformerLevelState_getInstance();
	this->platformerStageDefinition = platformerStageDefinition;
	this->isExitingRoom = true;
	Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, this));
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