/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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
#include <OverworldState.h>
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

extern StageROMDef OVERWORLD1_STAGE_ST;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void OverworldState::constructor()
{
	Base::constructor();
}

// class's destructor
void OverworldState::destructor()
{
	// destroy base
	Base::destructor();
}

// state's enter
void OverworldState::enter(void* owner)
{
	// call base
	Base::enter(this, owner);

	// disable user input
	Game::disableKeypad(Game::getInstance());

	// load stage
	GameState::loadStage(this, (StageDefinition*)&OVERWORLD1_STAGE_ST, NULL, true);

	// make a little bit of physical simulations so each entity is placed at the floor
	GameState::startClocks(this);

	// tell any interested entity
	GameState::propagateMessage(this, kLevelSetUp);

	OverworldState::print(this);

	// fade in screen after a little delay
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		250, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))OverworldState::onFadeInComplete, // callback function
		Object::safeCast(this) // callback scope
	);
}

// state's exit
void OverworldState::exit(void* owner)
{
	// call base
	Base::exit(this, owner);

	// destroy the state
	delete this;
}

// state's resume
void OverworldState::resume(void* owner)
{
	Base::resume(this, owner);

#ifdef __DEBUG_TOOLS
	if(!Game::isExitingSpecialMode(Game::getInstance()))
	{
#endif
#ifdef __STAGE_EDITOR
	if(!Game::isExitingSpecialMode(Game::getInstance()))
	{
#endif
#ifdef __ANIMATION_INSPECTOR
	if(!Game::isExitingSpecialMode(Game::getInstance()))
	{
#endif

	// tell any interested entity
	GameState::propagateMessage(this, kLevelResumed);

	// make a fade in
	Camera::startEffect(Camera::getInstance(), kFadeIn, __FADE_DELAY);

	// pause physical simulations
	GameState::pausePhysics(this, false);

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
void OverworldState::suspend(void* owner)
{
	// pause physical simulations
	GameState::pausePhysics(this, true);

#ifdef __DEBUG_TOOLS
	if(!Game::isEnteringSpecialMode(Game::getInstance()))
#endif
#ifdef __STAGE_EDITOR
	if(!Game::isEnteringSpecialMode(Game::getInstance()))
#endif
#ifdef __ANIMATION_INSPECTOR
	if(!Game::isEnteringSpecialMode(Game::getInstance()))
#endif

	// make a fade out
	Camera::startEffect(Camera::getInstance(), kFadeOut, __FADE_DELAY);

	Base::suspend(this, owner);
}

// print gui
void OverworldState::print()
{
	// coins
	u8 coins = ProgressManager::getTotalNumberOfCollectedCoins(ProgressManager::getInstance());
	Printing::int(Printing::getInstance(), coins, 4, 26, "GuiFont");

	// level name
	Printing::text(Printing::getInstance(), I18n::getText(I18n::getInstance(), STR_LEVEL_1_NAME), 16, 26, "GuiFont");
	Printing::text(Printing::getInstance(), "1-1", 12, 26, "GuiFont");
}

void OverworldState::processUserInput(UserInput userInput)
{
	if((K_STA & userInput.pressedKey) || (K_A & userInput.pressedKey))
	{
		// disable user input
		Game::disableKeypad(Game::getInstance());

		// start a fade out effect
		Brightness brightness = (Brightness){0, 0, 0};
		Camera::startEffect(Camera::getInstance(),
			kFadeTo, // effect type
			0, // initial delay (in ms)
			&brightness, // target brightness
			__FADE_DELAY, // delay between fading steps (in ms)
			(void (*)(Object, Object))OverworldState::onStartLevelFadeOutComplete, // callback function
			Object::safeCast(this) // callback scope
		);

	} else if(K_B & userInput.pressedKey) {		// disable user input
		Game::disableKeypad(Game::getInstance());

		// start a fade out effect
		Brightness brightness = (Brightness){0, 0, 0};
		Camera::startEffect(Camera::getInstance(),
			kFadeTo, // effect type
			0, // initial delay (in ms)
			&brightness, // target brightness
			__FADE_DELAY, // delay between fading steps (in ms)
			(void (*)(Object, Object))OverworldState::onReturnToTitleFadeOutComplete, // callback function
			Object::safeCast(this) // callback scope
		);
	}
}

// handle event
void OverworldState::onFadeInComplete(Object eventFirer __attribute__ ((unused)))
{
	// tell any interested entity
	GameState::propagateMessage(this, kLevelStarted);

	// enable user input
	Game::enableKeypad(Game::getInstance());
}

// handle event
void OverworldState::onStartLevelFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	// load platformer level
	extern PlatformerLevelDefinition LEVEL_1_LV;
	PlatformerLevelState::startLevel(PlatformerLevelState::getInstance(), &LEVEL_1_LV);
}

// handle event
void OverworldState::onReturnToTitleFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	// load title screen state
	Game::changeState(Game::getInstance(), GameState::safeCast(TitleScreenState::getInstance()));
}
