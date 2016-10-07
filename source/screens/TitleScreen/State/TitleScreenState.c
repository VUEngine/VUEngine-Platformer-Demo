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
#include <Printing.h>
#include <MessageDispatcher.h>
#include <I18n.h>
#include <Languages.h>
#include <PhysicalWorld.h>
#include <TitleScreenState.h>
#include <Hero.h>
#include <screens.h>
#include <macros.h>
#include <ParticleSystem.h>
#include <PlatformerLevelState.h>
#include <AdjustmentScreenState.h>
#include <CustomScreenMovementManager.h>
#include <ProgressManager.h>
#include <EventManager.h>
#include <OverworldState.h>
#include <KeyPadManager.h>


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
static bool TitleScreenState_processMessage(TitleScreenState this, void* owner, Telegram telegram);
static void TitleScreenState_showMessage(TitleScreenState this);
static void TitleScreenState_hideMessage(TitleScreenState this);
static void TitleScreenState_onSecondChange(TitleScreenState this, Object eventFirer);
static void TitleScreenState_onFadeInComplete(TitleScreenState this, Object eventFirer);
static void TitleScreenState_onFadeOutComplete(TitleScreenState this, Object eventFirer);


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(TitleScreenState, GameState);
__SINGLETON_DYNAMIC(TitleScreenState);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void __attribute__ ((noinline)) TitleScreenState_constructor(TitleScreenState this)
{
	__CONSTRUCT_BASE(GameState);
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
	Object_addEventListener(__SAFE_CAST(Object, Game_getUpdateClock(Game_getInstance())), __SAFE_CAST(Object, this), (EventListener)TitleScreenState_onSecondChange, kEventSecondChanged);

	// call base
	GameState_enter(__SAFE_CAST(GameState, this), owner);

    // disable user input
	Game_disableKeypad(Game_getInstance());

    // sample code that shows how to ignore selected entities when loading a stage
	VirtualList entityNamesToIgnore = __NEW(VirtualList);
	VirtualList_pushBack(entityNamesToIgnore, "IgnoreMeDoor");
	VirtualList_pushBack(entityNamesToIgnore, "IgnoreMeCoin");

	// load stage
	GameState_loadStage(__SAFE_CAST(GameState, this), (StageDefinition*)&TITLE_SCREEN_ST, entityNamesToIgnore, true);

	__DELETE(entityNamesToIgnore);

	// sample code to show how to animate multiple sprites at the same time by just playing an animation in a single
	// entity when various share the same __ANIMATED_SHARED charset
	/*
	if(Container_getChildByName(__SAFE_CAST(Container, this->stage), "DummyHero", true))
	{
		AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, Container_getChildByName(__SAFE_CAST(Container, this->stage), "DummyHero", true)), "Idle");
	}
	*/

	// make a little bit of physical simulations so each entity is placed at the floor
	GameState_startClocks(__SAFE_CAST(GameState, this));

	// show up level after a little delay
	MessageDispatcher_dispatchMessage(500, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kLevelSetUp, NULL);
}

// state's execute
static void TitleScreenState_execute(TitleScreenState this, void* owner)
{
	// call base
	GameState_execute(__SAFE_CAST(GameState, this), owner);
}

// state's exit
static void TitleScreenState_exit(TitleScreenState this, void* owner)
{
	// call base
	GameState_exit(__SAFE_CAST(GameState, this), owner);

	// destroy the state
	__DELETE(this);
}

// state's resume
static void TitleScreenState_resume(TitleScreenState this, void* owner)
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

	// tell any interested entity
	GameState_propagateMessage(__SAFE_CAST(GameState, this), kLevelResumed);

	// make a fade in
    Screen_startEffect(Screen_getInstance(), kFadeIn, __FADE_DURATION);

	// pause physical simulations
	GameState_pausePhysics(__SAFE_CAST(GameState, this), false);

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

	// pause physical simulations
	GameState_pausePhysics(__SAFE_CAST(GameState, this), true);

#ifdef __DEBUG_TOOLS
	if(!Game_isEnteringSpecialMode(Game_getInstance()))
#endif
#ifdef __STAGE_EDITOR
	if(!Game_isEnteringSpecialMode(Game_getInstance()))
#endif
#ifdef __ANIMATION_EDITOR
	if(!Game_isEnteringSpecialMode(Game_getInstance()))
#endif

	// make a fade out
    Screen_startEffect(Screen_getInstance(), kFadeOut, __FADE_DURATION);

	GameState_suspend(__SAFE_CAST(GameState, this), owner);
}

static void TitleScreenState_showMessage(TitleScreenState this __attribute__ ((unused)))
{
	ASSERT(this, "TitleScreenState::showMessage: null this");

    const char* strPressStartButton = I18n_getText(I18n_getInstance(), STR_PRESS_START_BUTTON);
    Size strPressStartButtonSize = Printing_getTextSize(Printing_getInstance(), strPressStartButton, NULL);
    u8 strXPos = (__SCREEN_WIDTH >> 4) - (strPressStartButtonSize.x >> 1);
    Printing_text(Printing_getInstance(), strPressStartButton, strXPos, 26, NULL);
}

static void TitleScreenState_hideMessage(TitleScreenState this __attribute__ ((unused)))
{
	ASSERT(this, "TitleScreenState::hideMessage: null this");

    Printing_text(Printing_getInstance(), "                                           ", 0, 26, NULL);
}

// state's handle message
static bool TitleScreenState_processMessage(TitleScreenState this, void* owner __attribute__ ((unused)), Telegram telegram)
{
	// process message
	switch(Telegram_getMessage(telegram))
    {
		case kLevelSetUp:

			// tell any interested entity
			GameState_propagateMessage(__SAFE_CAST(GameState, this), kLevelSetUp);

			// show level after a little delay
			MessageDispatcher_dispatchMessage(500, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kLevelStarted, NULL);
			break;

		case kLevelStarted:

			// fade in screen
            Screen_startEffect(Screen_getInstance(),
                kFadeTo, // effect type
                0, // initial delay (in ms)
                NULL, // target brightness
                __FADE_DELAY, // delay between fading steps (in ms)
                (void (*)(Object, Object))TitleScreenState_onFadeInComplete, // callback function
                __SAFE_CAST(Object, this) // callback scope
            );

			break;

		case kKeyPressed:
		{
			u32 pressedKey = *((u32*)Telegram_getExtraInfo(telegram));

			if(K_STA & pressedKey)
			{
                // disable blinking "press start button"
                Object_removeEventListener(__SAFE_CAST(Object, Game_getUpdateClock(Game_getInstance())), __SAFE_CAST(Object, this), (void (*)(Object, Object))TitleScreenState_onSecondChange, kEventSecondChanged);
                TitleScreenState_hideMessage(this);

                // disable user input
                Game_disableKeypad(Game_getInstance());

			    // fade out screen
                Brightness brightness = (Brightness){0, 0, 0};
                Screen_startEffect(Screen_getInstance(),
                    kFadeTo, // effect type
                    0, // initial delay (in ms)
                    &brightness, // target brightness
                    __FADE_DELAY, // delay between fading steps (in ms)
                    (void (*)(Object, Object))TitleScreenState_onFadeOutComplete, // callback function
                    __SAFE_CAST(Object, this) // callback scope
                );
			}
		}
			break;
	}

	return false;
}

// handle event
static void TitleScreenState_onSecondChange(TitleScreenState this, Object eventFirer __attribute__ ((unused)))
{
    if((Clock_getSeconds(Game_getUpdateClock(Game_getInstance())) % 2) == 0)
    {
        TitleScreenState_showMessage(this);
    }
    else
    {
        TitleScreenState_hideMessage(this);
    }
}

// handle event
static void TitleScreenState_onFadeInComplete(TitleScreenState this, Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "TitleScreenState::onFadeInComplete: null this");

    // tell any interested entity
    GameState_propagateMessage(__SAFE_CAST(GameState, this), kLevelStarted);

    // enable user input
    Game_enableKeypad(Game_getInstance());
}

// handle event
static void TitleScreenState_onFadeOutComplete(TitleScreenState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "TitleScreenState::onFadeOutComplete: null this");

    // swtich to next screen
    Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, OverworldState_getInstance()));
}
