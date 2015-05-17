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
#include <screens.h>
#include <macros.h>
#include <ParticleSystem.h>
#include <PlatformerLevelState.h>
#include <AdjustmentScreenState.h>
#include <CustomScreenMovementManager.h>
#include <UserDataManager.h>


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void TitleScreenState_destructor(TitleScreenState this);
static void TitleScreenState_constructor(TitleScreenState this);
static void TitleScreenState_enter(TitleScreenState this, void* owner);
static void TitleScreenState_execute(TitleScreenState this, void* owner);
static void TitleScreenState_exit(TitleScreenState this, void* owner);
static void TitleScreenState_resume(TitleScreenState this, void* owner);
static void TitleScreenState_suspend(TitleScreenState this, void* owner);
static bool TitleScreenState_handleMessage(TitleScreenState this, void* owner, Telegram telegram);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(TitleScreenState, GameState);
__SINGLETON_DYNAMIC(TitleScreenState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void TitleScreenState_constructor(TitleScreenState this)
{
	__CONSTRUCT_BASE();

	this->lastLevelSelectLabel = "";
	
	// set the custom movement screen manager now
	Screen_setScreenMovementManager(Screen_getInstance(), __GET_CAST(ScreenMovementManager, CustomScreenMovementManager_getInstance()));
}

// class's destructor
static void TitleScreenState_destructor(TitleScreenState this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
static void TitleScreenState_enter(TitleScreenState this, void* owner)
{
	const char* name1 = "IgnoreMeDoor";
	const char* name2 = "IgnoreMeCoin";
	VirtualList entityNamesToIgnore = __NEW(VirtualList);
	VirtualList_pushBack(entityNamesToIgnore, name1);
	VirtualList_pushBack(entityNamesToIgnore, name2);
	
	//load stage
	GameState_loadStage(__GET_CAST(GameState, this), (StageDefinition*)&TITLE_SCREEN_ST, entityNamesToIgnore, true);

	__DELETE(entityNamesToIgnore);
	
	// sample code to show how to animate multiple sprites at the same time
	// buy just playing an animation in a single entity when varios share
	// the same __ANIMATED_SHARED CharSet
	if(Container_getChildByName(__GET_CAST(Container, this->stage), "DummyHero", true))
	{
		AnimatedInGameEntity_playAnimation(__GET_CAST(AnimatedInGameEntity, Container_getChildByName(__GET_CAST(Container, this->stage), "DummyHero", true)), "Idle");
	}

	// make a little bit of physical simulations so each entity is placed at the floor
	Clock_start(Game_getInGameClock(Game_getInstance()));

	// show up level after a little bit
	MessageDispatcher_dispatchMessage(1000, __GET_CAST(Object, this), __GET_CAST(Object, Game_getInstance()), kSetUpLevel, NULL);

	// reset clock
	Clock_reset(Game_getInGameClock(Game_getInstance()));
}

// state's execute
static void TitleScreenState_execute(TitleScreenState this, void* owner)
{
    Door currentlyOverlappingDoor = Hero_getCurrentlyOverlappingDoor(Hero_getInstance());
    char* strLevelSelectLabel = "";

    // display level name if in front of a door
    if(currentlyOverlappingDoor != NULL)
    {
        PlatformerStageDefinition* platformerStageDefinition = Door_getExtraInfo(currentlyOverlappingDoor);
        strLevelSelectLabel = I18n_getText(I18n_getInstance(), (int)(*platformerStageDefinition).name);
    }

    if(0 != strcmp(this->lastLevelSelectLabel, strLevelSelectLabel))
    {
        Printing_text(Printing_getInstance(), "                                                ", 0, 26, "GUIFont");
        Printing_text(Printing_getInstance(), strLevelSelectLabel, (48 - strlen(strLevelSelectLabel)) >> 1, 26, "GUIFont");
        this->lastLevelSelectLabel = strLevelSelectLabel;
    }

	// call base
	GameState_execute(__GET_CAST(GameState, this), owner);
}

// state's exit
static void TitleScreenState_exit(TitleScreenState this, void* owner)
{
	// make a fade out
	Screen_startEffect(Screen_getInstance(), kFadeOut, FADE_DELAY);

	// destroy the state
	__DELETE(this);
}

// state's resume
static void TitleScreenState_resume(TitleScreenState this, void* owner)
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
	
	// tell any interested entity
	GameState_propagateMessage(__GET_CAST(GameState, this), kResumeLevel);

	// make a fade in
    Screen_startEffect(Screen_getInstance(), kFadeIn, FADE_DELAY);

	// pause physical simulations
	Clock_pause(Game_getInGameClock(Game_getInstance()), false);

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

// state's suspend
static void TitleScreenState_suspend(TitleScreenState this, void* owner)
{
	GameState_suspend(__GET_CAST(GameState, this), owner);

	// pause physical simulations
	Clock_pause(Game_getInGameClock(Game_getInstance()), true);
}

// state's on message
static bool TitleScreenState_handleMessage(TitleScreenState this, void* owner, Telegram telegram)
{
	// process message
	switch(Telegram_getMessage(telegram))
    {
		case kSetUpLevel:

			// make a little bit of physical simulations so each entity is placed at the floor
			Clock_start(Game_getInGameClock(Game_getInstance()));
	
			// pause physical simulations
			//Clock_pause(Game_getInGameClock(Game_getInstance()), true);

			// account for any entity's tranform modification during their initialization
			GameState_transform(__GET_CAST(GameState, this));
			
			// show level after 0.5 second
			MessageDispatcher_dispatchMessage(500, __GET_CAST(Object, this), __GET_CAST(Object, Game_getInstance()), kStartLevel, NULL);
			break;

		case kStartLevel:

			// fade screen
		    Screen_startEffect(Screen_getInstance(), kFadeIn, FADE_DELAY);

			// reset clock and restart
//			Clock_reset(Game_getInGameClock(Game_getInstance()));
//			Clock_start(Game_getInGameClock(Game_getInstance()));
			
			// tell any interested entity
			GameState_propagateMessage(__GET_CAST(GameState, this), kStartLevel);
			break;

		case kKeyPressed:
			{
	            u16 pressedKey = *((u16*)Telegram_getExtraInfo(telegram));
	
	            if(K_SEL & pressedKey)
	            {
	                // adjustment screen
					SplashScreenState_setNextstate(__GET_CAST(SplashScreenState, AdjustmentScreenState_getInstance()), NULL);
	                Game_pause(Game_getInstance(), __GET_CAST(GameState, AdjustmentScreenState_getInstance()));
	                break;
	            }
			}
			
			Object_fireEvent(__GET_CAST(Object, this), EVENT_KEY_PRESSED);
			return true;
			break;

		case kKeyReleased:
		
			Object_fireEvent(__GET_CAST(Object, this), EVENT_KEY_RELEASED);
			return true;
			break;

		case kKeyHold:
			
			Object_fireEvent(__GET_CAST(Object, this), EVENT_KEY_HOLD);
			return true;
			break;
	}

	return false;
}