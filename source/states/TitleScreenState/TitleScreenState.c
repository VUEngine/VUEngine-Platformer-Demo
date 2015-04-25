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
#include <PlatformerLevelState.h>
#include <VBJaEAdjustmentScreenState.h>


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
	Optical optical = Game_getOptical(Game_getInstance());
	optical.verticalViewPointCenter = ITOFIX19_13(112 + 112/2);
	Game_setOptical(Game_getInstance(), optical);

	const char* name1 = "IgnoreMeDoor";
	const char* name2 = "IgnoreMeCoin";
	VirtualList entityNamesToIgnore = __NEW(VirtualList);
	VirtualList_pushBack(entityNamesToIgnore, name1);
	VirtualList_pushBack(entityNamesToIgnore, name2);
	
	//load stage
	GameState_loadStage(__UPCAST(GameState, this), (StageDefinition*)&TITLE_SCREEN_ST, entityNamesToIgnore, false);

	__DELETE(entityNamesToIgnore);
	
	// sample code to show how to animate multiple sprites at the same time
	// buy just playing an animation in a single entity when varios share
	// the same __ANIMATED_SHARED CharSet
	if(Container_getChildByName(__UPCAST(Container, this->stage), "DummyHero"))
	{
		AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, Container_getChildByName(__UPCAST(Container, this->stage), "DummyHero")), "Idle");
	}

	// make a little bit of physical simulations so each entity is placed at the floor
	Clock_start(Game_getInGameClock(Game_getInstance()));
	PhysicalWorld_start(PhysicalWorld_getInstance());
	PhysicalWorld_setFriction(PhysicalWorld_getInstance(), FTOFIX19_13(0.01f));
	Acceleration gravity =
    {
        ITOFIX19_13(0),
        ITOFIX19_13(4000),
        ITOFIX19_13(0)
    };
	PhysicalWorld_setGravity(PhysicalWorld_getInstance(), gravity);

	// show up level after a little bit
	MessageDispatcher_dispatchMessage(1000, __UPCAST(Object, this), __UPCAST(Object, Game_getInstance()), kSetUpLevel, NULL);

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
	GameState_execute(__UPCAST(GameState, this), owner);
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
	GameState_resume(__UPCAST(GameState, this), owner);

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
	GameState_propagateMessage(__UPCAST(GameState, this), kResumeLevel);

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
			//Clock_pause(Game_getInGameClock(Game_getInstance()), true);

			// account for any entity's tranform modification during their initialization
			GameState_transform(__UPCAST(GameState, this));
			
			// show level after 0.5 second
			MessageDispatcher_dispatchMessage(500, __UPCAST(Object, this), __UPCAST(Object, Game_getInstance()), kStartLevel, NULL);
			break;

		case kStartLevel:

			// fade screen
			Screen_FXFadeIn(Screen_getInstance(), FADE_DELAY);

			// reset clock and restart
//			Clock_reset(Game_getInGameClock(Game_getInstance()));
//			Clock_start(Game_getInGameClock(Game_getInstance()));
			
			// start physical simulation again
			PhysicalWorld_start(PhysicalWorld_getInstance());

			// tell any interested entity
			GameState_propagateMessage(__UPCAST(GameState, this), kStartLevel);
			break;

		case kKeyPressed:
			{
	            u16 pressedKey = *((u16*)Telegram_getExtraInfo(telegram));
	
	            if (K_SEL & pressedKey)
	            {
	                // adjustment screen
					SplashScreenState_setNextstate(__UPCAST(SplashScreenState, VBJaEAdjustmentScreenState_getInstance()), NULL);
	                Game_pause(Game_getInstance(), __UPCAST(GameState, VBJaEAdjustmentScreenState_getInstance()));
	                break;
	            }
			}
			
			Object_fireEvent(__UPCAST(Object, this), EVENT_KEY_PRESSED);
			return true;
			break;

		case kKeyReleased:
		
			Object_fireEvent(__UPCAST(Object, this), EVENT_KEY_RELEASED);
			return true;
			break;

		case kKeyHold:
			
			Object_fireEvent(__UPCAST(Object, this), EVENT_KEY_HOLD);
			return true;
			break;
	}

	return false;
}