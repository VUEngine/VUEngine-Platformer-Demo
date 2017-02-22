/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2017 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <string.h>

#include <Game.h>
#include <Screen.h>
#include <Printing.h>
#include <MessageDispatcher.h>
#include <I18n.h>
#include <Languages.h>
#include <PhysicalWorld.h>
#include <OverworldState.h>
#include <TitleScreenState.h>
#include <Hero.h>
#include <ParticleSystem.h>
#include <PlatformerLevelState.h>
#include <AdjustmentScreenState.h>
#include <CustomScreenMovementManager.h>
#include <ProgressManager.h>
#include <EventManager.h>
#include <KeyPadManager.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef OVERWORLD1_STAGE_ST;


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void OverworldState_destructor(OverworldState this);
static void OverworldState_constructor(OverworldState this);
static void OverworldState_enter(OverworldState this, void* owner);
static void OverworldState_execute(OverworldState this, void* owner);
static void OverworldState_exit(OverworldState this, void* owner);
static void OverworldState_resume(OverworldState this, void* owner);
static void OverworldState_suspend(OverworldState this, void* owner);
static void OverworldState_onUserInput(OverworldState this, Object eventFirer);
static bool OverworldState_processMessage(OverworldState this, void* owner, Telegram telegram);
static void OverworldState_onFadeInComplete(OverworldState this, Object eventFirer);
static void OverworldState_onStartLevelFadeOutComplete(OverworldState this, Object eventFirer);
static void OverworldState_onReturnToTitleFadeOutComplete(OverworldState this, Object eventFirer);


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(OverworldState, GameState);
__SINGLETON_DYNAMIC(OverworldState);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void __attribute__ ((noinline)) OverworldState_constructor(OverworldState this)
{
	__CONSTRUCT_BASE(GameState);
}

// class's destructor
static void OverworldState_destructor(OverworldState this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
static void OverworldState_enter(OverworldState this, void* owner)
{
	// call base
	GameState_enter(__SAFE_CAST(GameState, this), owner);

	// disable user input
	Game_disableKeypad(Game_getInstance());

	// load stage
	GameState_loadStage(__SAFE_CAST(GameState, this), (StageDefinition*)&OVERWORLD1_STAGE_ST, NULL, true);

	// make a little bit of physical simulations so each entity is placed at the floor
	GameState_startClocks(__SAFE_CAST(GameState, this));

	// show up level after a little delay
	MessageDispatcher_dispatchMessage(500, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kLevelSetUp, NULL);
}

// state's execute
static void OverworldState_execute(OverworldState this, void* owner)
{
	// call base
	GameState_execute(__SAFE_CAST(GameState, this), owner);
}

// state's exit
static void OverworldState_exit(OverworldState this, void* owner)
{
	Object_removeEventListener(__SAFE_CAST(Object, Game_getInstance()), __SAFE_CAST(Object, this), (EventListener)OverworldState_onUserInput, kEventUserInput);

	// call base
	GameState_exit(__SAFE_CAST(GameState, this), owner);

	// destroy the state
	__DELETE(this);
}

// state's resume
static void OverworldState_resume(OverworldState this, void* owner)
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
	Screen_startEffect(Screen_getInstance(), kFadeIn, __FADE_DELAY);

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
static void OverworldState_suspend(OverworldState this, void* owner)
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
	Screen_startEffect(Screen_getInstance(), kFadeOut, __FADE_DELAY);

	GameState_suspend(__SAFE_CAST(GameState, this), owner);
}

// print gui
static void OverworldState_print(OverworldState this __attribute__ ((unused)))
{
	ASSERT(this, "OverworldState::print: null this");

	// coins
	u8 coins = ProgressManager_getTotalNumberOfCollectedCoins(ProgressManager_getInstance());
	Printing_int(Printing_getInstance(), coins, 4, 26, "GuiFont");

	// level name
	Printing_text(Printing_getInstance(), I18n_getText(I18n_getInstance(), STR_LEVEL_1_NAME), 16, 26, "GuiFont");
	Printing_text(Printing_getInstance(), "1-1", 12, 26, "GuiFont");
}

static void OverworldState_onUserInput(OverworldState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	u32 pressedKey = KeypadManager_getUserInput(KeypadManager_getInstance()).pressedKey;

	if((K_STA & pressedKey) || (K_A & pressedKey))
	{
		// disable user input
		Game_disableKeypad(Game_getInstance());

		// start a fade out effect
		Brightness brightness = (Brightness){0, 0, 0};
		Screen_startEffect(Screen_getInstance(),
			kFadeTo, // effect type
			0, // initial delay (in ms)
			&brightness, // target brightness
			__FADE_DELAY, // delay between fading steps (in ms)
			(void (*)(Object, Object))OverworldState_onStartLevelFadeOutComplete, // callback function
			__SAFE_CAST(Object, this) // callback scope
		);

	} else if(K_B & pressedKey) {

		// disable user input
		Game_disableKeypad(Game_getInstance());

		// start a fade out effect
		Brightness brightness = (Brightness){0, 0, 0};
		Screen_startEffect(Screen_getInstance(),
			kFadeTo, // effect type
			0, // initial delay (in ms)
			&brightness, // target brightness
			__FADE_DELAY, // delay between fading steps (in ms)
			(void (*)(Object, Object))OverworldState_onReturnToTitleFadeOutComplete, // callback function
			__SAFE_CAST(Object, this) // callback scope
		);
	}
}

// state's handle message
static bool OverworldState_processMessage(OverworldState this, void* owner __attribute__ ((unused)), Telegram telegram)
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

			OverworldState_print(this);

			// fade in screen
			Screen_startEffect(Screen_getInstance(),
				kFadeTo, // effect type
				0, // initial delay (in ms)
				NULL, // target brightness
				__FADE_DELAY, // delay between fading steps (in ms)
				(void (*)(Object, Object))OverworldState_onFadeInComplete, // callback function
				__SAFE_CAST(Object, this) // callback scope
			);

			break;
	}

	return false;
}

// handle event
static void OverworldState_onFadeInComplete(OverworldState this, Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "OverworldState::onFadeInComplete: null this");

	// tell any interested entity
	GameState_propagateMessage(__SAFE_CAST(GameState, this), kLevelStarted);

	// enable user input
	Game_enableKeypad(Game_getInstance());

	Object_addEventListener(__SAFE_CAST(Object, Game_getInstance()), __SAFE_CAST(Object, this), (EventListener)OverworldState_onUserInput, kEventUserInput);
}

// handle event
static void OverworldState_onStartLevelFadeOutComplete(OverworldState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "OverworldState::onFadeOutComplete: null this");

	// load platformer level
	extern PlatformerLevelDefinition LEVEL_1_LV;
	PlatformerLevelState_startLevel(PlatformerLevelState_getInstance(), &LEVEL_1_LV);
}

// handle event
static void OverworldState_onReturnToTitleFadeOutComplete(OverworldState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "OverworldState::onFadeOutComplete: null this");

	// load title screen state
	Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, TitleScreenState_getInstance()));
}
