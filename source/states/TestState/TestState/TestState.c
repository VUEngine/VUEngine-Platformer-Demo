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
#include <Camera.h>
#include <MessageDispatcher.h>
#include <I18n.h>
#include <Languages.h>
#include <PhysicalWorld.h>
#include <TestState.h>
#include <TitleScreenState.h>
#include <Hero.h>
#include <ParticleSystem.h>
#include <PlatformerLevelState.h>
#include <AdjustmentScreenState.h>
#include <CustomCameraMovementManager.h>
#include <ProgressManager.h>
#include <EventManager.h>
#include <KeyPadManager.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef TEST_STAGE_ST;


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void TestState_destructor(TestState this);
static void TestState_constructor(TestState this);
static void TestState_enter(TestState this, void* owner);
static void TestState_exit(TestState this, void* owner);
static void TestState_resume(TestState this, void* owner);
static void TestState_suspend(TestState this, void* owner);
static bool TestState_processMessage(TestState this, void* owner, Telegram telegram);
static void TestState_onFadeInComplete(TestState this, Object eventFirer);
static void TestState_onStartLevelFadeOutComplete(TestState this, Object eventFirer);
static void TestState_onReturnToTitleFadeOutComplete(TestState this, Object eventFirer);


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(TestState, GameState);
__SINGLETON_DYNAMIC(TestState);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
static void __attribute__ ((noinline)) TestState_constructor(TestState this)
{
	__CONSTRUCT_BASE(GameState);
}

// class's destructor
static void TestState_destructor(TestState this)
{
	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
static void TestState_enter(TestState this, void* owner)
{
	// call base
	__CALL_BASE_METHOD(GameState, enter, this, owner);

	// disable user input
	Game_disableKeypad(Game_getInstance());

	// load stage
	GameState_loadStage(__SAFE_CAST(GameState, this), (StageDefinition*)&TEST_STAGE_ST, NULL, true);

	// make a little bit of physical simulations so each entity is placed at the floor
	GameState_startClocks(__SAFE_CAST(GameState, this));

	// show up level after a little delay
	MessageDispatcher_dispatchMessage(500, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game_getInstance()), kLevelSetUp, NULL);
}

// state's exit
static void TestState_exit(TestState this, void* owner)
{
	// call base
	__CALL_BASE_METHOD(GameState, exit, this, owner);

	// destroy the state
	__DELETE(this);
}

// state's resume
static void TestState_resume(TestState this, void* owner)
{
	__CALL_BASE_METHOD(GameState, resume, this, owner);

#ifdef __DEBUG_TOOLS
	if(!Game_isExitingSpecialMode(Game_getInstance()))
	{
#endif
#ifdef __STAGE_EDITOR
	if(!Game_isExitingSpecialMode(Game_getInstance()))
	{
#endif
#ifdef __ANIMATION_INSPECTOR
	if(!Game_isExitingSpecialMode(Game_getInstance()))
	{
#endif

	// tell any interested entity
	GameState_propagateMessage(__SAFE_CAST(GameState, this), kLevelResumed);

	// make a fade in
	Camera_startEffect(Camera_getInstance(), kFadeIn, __FADE_DELAY);

	// pause physical simulations
	GameState_pausePhysics(__SAFE_CAST(GameState, this), false);

#ifdef __DEBUG_TOOLS
	}
#endif
#ifdef __STAGE_EDITOR
	}
#endif
#ifdef __ANIMATION_INSPECTOR
	}
#endif
}

// state's suspend
static void TestState_suspend(TestState this, void* owner)
{
	// pause physical simulations
	GameState_pausePhysics(__SAFE_CAST(GameState, this), true);

#ifdef __DEBUG_TOOLS
	if(!Game_isEnteringSpecialMode(Game_getInstance()))
#endif
#ifdef __STAGE_EDITOR
	if(!Game_isEnteringSpecialMode(Game_getInstance()))
#endif
#ifdef __ANIMATION_INSPECTOR
	if(!Game_isEnteringSpecialMode(Game_getInstance()))
#endif

	// make a fade out
	Camera_startEffect(Camera_getInstance(), kFadeOut, __FADE_DELAY);

	__CALL_BASE_METHOD(GameState, suspend, this, owner);
}

// print gui
static void TestState_print(TestState this __attribute__ ((unused)))
{
	ASSERT(this, "TestState::print: null this");

	// coins
	u8 coins = ProgressManager_getTotalNumberOfCollectedCoins(ProgressManager_getInstance());
	Printing_int(Printing_getInstance(), coins, 4, 26, "GuiFont");

	// level name
	Printing_text(Printing_getInstance(), I18n_getText(I18n_getInstance(), STR_LEVEL_1_NAME), 16, 26, "GuiFont");
	Printing_text(Printing_getInstance(), "1-1", 12, 26, "GuiFont");
}

void TestState_processUserInput(TestState this, UserInput userInput)
{
	if((K_STA & userInput.pressedKey) || (K_A & userInput.pressedKey))
	{
		// disable user input
		Game_disableKeypad(Game_getInstance());

		// start a fade out effect
		Brightness brightness = (Brightness){0, 0, 0};
		Camera_startEffect(Camera_getInstance(),
			kFadeTo, // effect type
			0, // initial delay (in ms)
			&brightness, // target brightness
			__FADE_DELAY, // delay between fading steps (in ms)
			(void (*)(Object, Object))TestState_onStartLevelFadeOutComplete, // callback function
			__SAFE_CAST(Object, this) // callback scope
		);

	} else if(K_B & userInput.pressedKey) {

		// disable user input
		Game_disableKeypad(Game_getInstance());

		// start a fade out effect
		Brightness brightness = (Brightness){0, 0, 0};
		Camera_startEffect(Camera_getInstance(),
			kFadeTo, // effect type
			0, // initial delay (in ms)
			&brightness, // target brightness
			__FADE_DELAY, // delay between fading steps (in ms)
			(void (*)(Object, Object))TestState_onReturnToTitleFadeOutComplete, // callback function
			__SAFE_CAST(Object, this) // callback scope
		);
	}
}

// state's handle message
static bool TestState_processMessage(TestState this, void* owner __attribute__ ((unused)), Telegram telegram)
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

			TestState_print(this);

			// fade in screen
			Camera_startEffect(Camera_getInstance(),
				kFadeTo, // effect type
				0, // initial delay (in ms)
				NULL, // target brightness
				__FADE_DELAY, // delay between fading steps (in ms)
				(void (*)(Object, Object))TestState_onFadeInComplete, // callback function
				__SAFE_CAST(Object, this) // callback scope
			);

			break;
	}

	return false;
}

// handle event
static void TestState_onFadeInComplete(TestState this, Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "TestState::onFadeInComplete: null this");

	// tell any interested entity
	GameState_propagateMessage(__SAFE_CAST(GameState, this), kLevelStarted);

	// enable user input
	Game_enableKeypad(Game_getInstance());
}

// handle event
static void TestState_onStartLevelFadeOutComplete(TestState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "TestState::onFadeOutComplete: null this");

	// load platformer level
	extern PlatformerLevelDefinition LEVEL_1_LV;
	PlatformerLevelState_startLevel(PlatformerLevelState_getInstance(), &LEVEL_1_LV);
}

// handle event
static void TestState_onReturnToTitleFadeOutComplete(TestState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "TestState::onFadeOutComplete: null this");

	// load title screen state
	Game_changeState(Game_getInstance(), __SAFE_CAST(GameState, TitleScreenState_getInstance()));
}
