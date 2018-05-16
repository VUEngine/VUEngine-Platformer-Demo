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
#include <I18n.h>
#include <Utilities.h>
#include <Languages.h>
#include <SplashScreenState.h>
#include <AutoPauseSelectScreenState.h>
#include <LangSelectScreenState.h>
#include <TitleScreenState.h>
#include <KeypadManager.h>
#include "OptionsScreenState.h"


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef EMPTY_STAGE_ST;


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void OptionsScreenState::constructor(OptionsScreenState this);
static void OptionsScreenState::print(OptionsScreenState this);
static void OptionsScreenState::onFadeInComplete(OptionsScreenState this, Object eventFirer);
static void OptionsScreenState::onExitFadeOutComplete(OptionsScreenState this, Object eventFirer);
static void OptionsScreenState::onOptionSelectedFadeOutComplete(OptionsScreenState this, Object eventFirer);
static void OptionsScreenState::onOptionAutoPauseSelect(OptionsScreenState this);
static void OptionsScreenState::onOptionLanguageSelect(OptionsScreenState this);



//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void __attribute__ ((noinline)) OptionsScreenState::constructor(OptionsScreenState this)
{
	Base::constructor();

	// init members
	this->optionsSelector = __NEW(OptionsSelector, 1, 2, NULL);
	OptionsScreenState::setNextState(this, __SAFE_CAST(GameState, TitleScreenState::getInstance()));
}

// class's destructor
void OptionsScreenState::destructor(OptionsScreenState this)
{
	__DELETE(this->optionsSelector);

	// destroy base
	__SINGLETON_DESTROY;
}

// state's enter
void OptionsScreenState::enter(OptionsScreenState this, void* owner __attribute__ ((unused)))
{
	// call base
	Base::enter(this, owner);

	// load stage
	GameState::loadStage(__SAFE_CAST(GameState, this), (StageDefinition*)&EMPTY_STAGE_ST, NULL, true);

	// print options
	OptionsScreenState::print(this);

	// disable user input
	Game::disableKeypad(Game::getInstance());

	// fade in screen
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))OptionsScreenState::onFadeInComplete, // callback function
		__SAFE_CAST(Object, this) // callback scope
	);
}

// state's exit
void OptionsScreenState::exit(OptionsScreenState this, void* owner __attribute__ ((unused)))
{
	// call base
	Base::exit(this, owner);
}

// set next state
void OptionsScreenState::setNextState(OptionsScreenState this, GameState nextState)
{
	this->nextState = nextState;
}

// print level stats
static void OptionsScreenState::print(OptionsScreenState this __attribute__ ((unused)))
{
	ASSERT(this, "OptionsScreenState::print: null this");

	// title
	const char* strOptionsTitle = I18n::getText(I18n::getInstance(), STR_OPTIONS);
	const char* strOptionsTitleFont = "LargeFont";
	FontSize strOptionsTextSize = Printing::getTextSize(Printing::getInstance(), strOptionsTitle, strOptionsTitleFont);
	Printing::text(
		Printing::getInstance(),
		Utilities::toUppercase(strOptionsTitle),
		((__SCREEN_WIDTH_IN_CHARS) - strOptionsTextSize.x) >> 1,
		8,
		strOptionsTitleFont
	);

	// menu
	VirtualList options = __NEW(VirtualList);
	Option* option = NULL;

	option = __NEW_BASIC(Option);
	option->value = (char*)I18n::getText(I18n::getInstance(), STR_AUTOMATIC_PAUSE);
	option->type = kString;
	option->callback = (void (*)(Object))OptionsScreenState::onOptionAutoPauseSelect;
	option->callbackScope = __SAFE_CAST(Object, this);
	VirtualList::pushBack(options, option);

	option = __NEW_BASIC(Option);
	option->value = (char*)I18n::getText(I18n::getInstance(), STR_LANGUAGE);
	option->type = kString;
	option->callback = (void (*)(Object))OptionsScreenState::onOptionLanguageSelect;
	option->callbackScope = __SAFE_CAST(Object, this);
	VirtualList::pushBack(options, option);

	OptionsSelector::setOptions(this->optionsSelector, options);
	__DELETE(options);

	OptionsSelector::printOptions(
		this->optionsSelector,
		((__SCREEN_WIDTH_IN_CHARS) - strOptionsTextSize.x) >> 1,
		11
	);

	// buttons
	const char* strSelect = I18n::getText(I18n::getInstance(), STR_SELECT);
	FontSize strSelectSize = Printing::getTextSize(Printing::getInstance(), strSelect, NULL);
	const char* strBack = I18n::getText(I18n::getInstance(), STR_BACK);

	u8 strSelectXPos = ((__SCREEN_WIDTH_IN_CHARS) - strOptionsTextSize.x) >> 1;
	u8 strBackXPos = strSelectXPos + strSelectSize.x + 2;

	Printing::text(Printing::getInstance(), __CHAR_A_BUTTON, strSelectXPos, 15, NULL);
	Printing::text(Printing::getInstance(), strSelect, strSelectXPos + 1, 15, NULL);
	Printing::text(Printing::getInstance(), __CHAR_B_BUTTON, strBackXPos, 15, NULL);
	Printing::text(Printing::getInstance(), strBack, strBackXPos + 1, 15, NULL);
}

void OptionsScreenState::processUserInput(OptionsScreenState this, UserInput userInput)
{
	if((userInput.pressedKey & K_A) || (userInput.pressedKey & K_STA))
	{
		// disable user input
		Game::disableKeypad(Game::getInstance());

		// fade out screen
		Brightness brightness = (Brightness){0, 0, 0};
		Camera::startEffect(Camera::getInstance(),
			kFadeTo, // effect type
			0, // initial delay (in ms)
			&brightness, // target brightness
			__FADE_DELAY, // delay between fading steps (in ms)
			(void (*)(Object, Object))OptionsScreenState::onOptionSelectedFadeOutComplete, // callback function
			__SAFE_CAST(Object, this) // callback scope
		);
	}
	else if((userInput.pressedKey & K_B) || (userInput.pressedKey & K_SEL))
	{
		// disable user input
		Game::disableKeypad(Game::getInstance());

		// fade out screen
		Brightness brightness = (Brightness){0, 0, 0};
		Camera::startEffect(Camera::getInstance(),
			kFadeTo, // effect type
			0, // initial delay (in ms)
			&brightness, // target brightness
			__FADE_DELAY, // delay between fading steps (in ms)
			(void (*)(Object, Object))OptionsScreenState::onExitFadeOutComplete, // callback function
			__SAFE_CAST(Object, this) // callback scope
		);
	}
	else if((userInput.pressedKey & K_LU) || (userInput.pressedKey & K_RU))
	{
		OptionsSelector::selectPrevious(this->optionsSelector);
	}
	else if((userInput.pressedKey & K_LD) || (userInput.pressedKey & K_RD))
	{
		OptionsSelector::selectNext(this->optionsSelector);
	}
}

// handle event
static void OptionsScreenState::onFadeInComplete(OptionsScreenState this __attribute__ ((unused)), Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "OptionsScreenState::onOptionSelectedFadeOutComplete: null this");

	Game::enableKeypad(Game::getInstance());
}

static void OptionsScreenState::onExitFadeOutComplete(OptionsScreenState this, Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "OptionsScreenState::onExitFadeOutComplete: null this");

	// switch to next screen
	Game::changeState(Game::getInstance(), this->nextState);
}

static void OptionsScreenState::onOptionSelectedFadeOutComplete(OptionsScreenState this, Object eventFirer __attribute__ ((unused)))
{
	ASSERT(this, "OptionsScreenState::onOptionSelectedFadeOutComplete: null this");

	OptionsSelector::doCurrentSelectionCallback(this->optionsSelector);
}

static void OptionsScreenState::onOptionAutoPauseSelect(OptionsScreenState this)
{
	ASSERT(this, "OptionsScreenState::onOptionAutoPauseSelect: null this");

	SplashScreenState::setNextState(__SAFE_CAST(SplashScreenState, AutoPauseSelectScreenState::getInstance()), __SAFE_CAST(GameState, this));
	Game::changeState(Game::getInstance(), __SAFE_CAST(GameState, AutoPauseSelectScreenState::getInstance()));
}

static void OptionsScreenState::onOptionLanguageSelect(OptionsScreenState this)
{
	ASSERT(this, "OptionsScreenState::onOptionLanguageSelect: null this");

	SplashScreenState::setNextState(__SAFE_CAST(SplashScreenState, LangSelectScreenState::getInstance()), __SAFE_CAST(GameState, this));
	Game::changeState(Game::getInstance(), __SAFE_CAST(GameState, LangSelectScreenState::getInstance()));
}
