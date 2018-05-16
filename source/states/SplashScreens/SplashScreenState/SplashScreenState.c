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

#include <Game.h>
#include <Camera.h>
#include <MessageDispatcher.h>
#include <SplashScreenState.h>
#include <KeypadManager.h>


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

static void SplashScreenState::onFadeInComplete(SplashScreenState this, Object eventFirer);
static void SplashScreenState::onFadeOutComplete(SplashScreenState this, Object eventFirer);



//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void SplashScreenState::constructor(SplashScreenState this)
{
	Base::constructor();

	this->stageDefinition = NULL;
}

// class's destructor
void SplashScreenState::destructor(SplashScreenState this)
{
	// destroy the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// state's enter
void SplashScreenState::enter(SplashScreenState this, void* owner)
{
	// call base
	Base::enter(this, owner);

	if(this->stageDefinition)
	{
		GameState::loadStage(__SAFE_CAST(GameState, this), this->stageDefinition, NULL, true);
	}

	SplashScreenState::print(this);

	// start fade in effect in 1 ms, because a full render cycle is needed to put everything in place
	MessageDispatcher::dispatchMessage(1, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game::getInstance()), kScreenStarted, NULL);

	Game::disableKeypad(Game::getInstance());
}

// state's exit
void SplashScreenState::exit(SplashScreenState this, void* owner)
{
	// call base
	Base::exit(this, owner);

	// destroy the state
	__DELETE(this);
}

// state's resume
void SplashScreenState::resume(SplashScreenState this, void* owner)
{
	Base::resume(this, owner);

	SplashScreenState::print(this);

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

	// start a fade in effect
	Camera::startEffect(Camera::getInstance(), kFadeIn, __FADE_DELAY);

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

void SplashScreenState::processUserInput(SplashScreenState this, UserInput userInput)
{
	if(userInput.pressedKey & ~K_PWR)
	{
		SplashScreenState::processInput(this, userInput.pressedKey);
	}
}

// state's handle message
bool SplashScreenState::processMessage(SplashScreenState this, void* owner __attribute__ ((unused)), Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kScreenStarted:

			// start fade in effect
			Camera::startEffect(Camera::getInstance(),
				kFadeTo, // effect type
				0, // initial delay (in ms)
				NULL, // target brightness
				__FADE_DELAY, // delay between fading steps (in ms)
				(void (*)(Object, Object))SplashScreenState::onFadeInComplete, // callback function
				__SAFE_CAST(Object, this) // callback scope
			);

			break;
	}

	return false;
}

void SplashScreenState::processInput(SplashScreenState this, u32 pressedKey __attribute__ ((unused)))
{
	SplashScreenState::loadNextState(this);
}

void SplashScreenState::print(SplashScreenState this __attribute__ ((unused)))
{
}

void SplashScreenState::setNextState(SplashScreenState this, GameState nextState)
{
	this->nextState = nextState;
}

void SplashScreenState::loadNextState(SplashScreenState this)
{
	// disable user input
	Game::disableKeypad(Game::getInstance());

	// start fade out effect
	Brightness brightness = (Brightness){0, 0, 0};
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		&brightness, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))SplashScreenState::onFadeOutComplete, // callback function
		__SAFE_CAST(Object, this) // callback scope
	);
}

// handle event
static void SplashScreenState::onFadeInComplete(SplashScreenState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "SplashScreenState::onFadeInComplete: null this");

	// enable user input
	Game::enableKeypad(Game::getInstance());
}

// handle event
static void SplashScreenState::onFadeOutComplete(SplashScreenState this, Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "SplashScreenState::onFadeOutComplete: null this");

	// change to next stage
	Game::changeState(Game::getInstance(), this->nextState);
}
