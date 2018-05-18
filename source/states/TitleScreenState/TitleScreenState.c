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
#include <TitleScreenState.h>
#include <Hero.h>
#include <ParticleSystem.h>
#include <PlatformerLevelState.h>
#include <AdjustmentScreenState.h>
#include <OptionsScreenState.h>
#include <CustomCameraMovementManager.h>
#include <ProgressManager.h>
#include <EventManager.h>
#include <OverworldState.h>
#include <KeyPadManager.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef TITLE_SCREEN_STAGE_ST;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void TitleScreenState::constructor()
{
	Base::constructor();

	// init members
	this->mode = kTitleScreenModeShowPressStart;
	this->optionsSelector = NULL;
}

// class's destructor
void TitleScreenState::destructor()
{
	if(this->optionsSelector)
	{
		__DELETE(this->optionsSelector);
	}

	// destroy base
	Base::destructor();
}

// state's enter
void TitleScreenState::enter(void* owner)
{
	// reset mode
	this->mode = kTitleScreenModeShowPressStart;

	// add event listener for "press start" message
	Object::addEventListener(__SAFE_CAST(Object, Game::getUpdateClock(Game::getInstance())), __SAFE_CAST(Object, this), (EventListener)TitleScreenState::onSecondChange, kEventSecondChanged);

	// call base
	Base::enter(this, owner);

	// disable user input
	Game::disableKeypad(Game::getInstance());

	// load stage
	GameState::loadStage(__SAFE_CAST(GameState, this), (StageDefinition*)&TITLE_SCREEN_STAGE_ST, NULL, true);

	if(this->optionsSelector)
	{
		__DELETE(this->optionsSelector);
	}

	// create and populate main menu
	VirtualList options = __NEW(VirtualList);
	if(ProgressManager::hasProgress(ProgressManager::getInstance()))
	{
		this->optionsSelector = __NEW(OptionsSelector, 3, 1, NULL);
		Option* option = NULL;

		option = __NEW_BASIC(Option);
		option->value = (char*)I18n::getText(I18n::getInstance(), STR_CONTINUE);
		option->type = kString;
		option->callback = NULL;
		option->callbackScope = NULL;
		VirtualList::pushBack(options, option);

		option = __NEW_BASIC(Option);
		option->value = (char*)I18n::getText(I18n::getInstance(), STR_OPTIONS);
		option->type = kString;
		option->callback = NULL;
		option->callbackScope = NULL;
		VirtualList::pushBack(options, option);

		option = __NEW_BASIC(Option);
		option->value = (char*)I18n::getText(I18n::getInstance(), STR_NEW_GAME);
		option->type = kString;
		option->callback = NULL;
		option->callbackScope = NULL;
		VirtualList::pushBack(options, option);

		FontSize strContinueSize = Printing::getTextSize(Printing::getInstance(), I18n::getText(I18n::getInstance(), STR_CONTINUE), NULL);
		FontSize strOptionsSize = Printing::getTextSize(Printing::getInstance(), I18n::getText(I18n::getInstance(), STR_OPTIONS), NULL);
		FontSize strNewGameSize = Printing::getTextSize(Printing::getInstance(), I18n::getText(I18n::getInstance(), STR_NEW_GAME), NULL);
		u8 width = (strContinueSize.x > strOptionsSize.x) ? strContinueSize.x : strOptionsSize.x;
		width = (width > strNewGameSize.x) ? width : strNewGameSize.x;
		OptionsSelector::setColumnWidth(this->optionsSelector, width + 1);
	}
	else
	{
		this->optionsSelector = __NEW(OptionsSelector, 2, 1, NULL);
		Option* option = NULL;

		option = __NEW_BASIC(Option);
		option->value = (char*)I18n::getText(I18n::getInstance(), STR_NEW_GAME);
		option->type = kString;
		option->callback = NULL;
		option->callbackScope = NULL;
		VirtualList::pushBack(options, option);

		option = __NEW_BASIC(Option);
		option->value = (char*)I18n::getText(I18n::getInstance(), STR_OPTIONS);
		option->type = kString;
		option->callback = NULL;
		option->callbackScope = NULL;
		VirtualList::pushBack(options, option);

		FontSize strOptionsSize = Printing::getTextSize(Printing::getInstance(), I18n::getText(I18n::getInstance(), STR_OPTIONS), NULL);
		FontSize strNewGameSize = Printing::getTextSize(Printing::getInstance(), I18n::getText(I18n::getInstance(), STR_NEW_GAME), NULL);
		u8 width = (strOptionsSize.x > strNewGameSize.x) ? strOptionsSize.x : strNewGameSize.x;
		OptionsSelector::setColumnWidth(this->optionsSelector, width + 1);
	}

	OptionsSelector::setOptions(this->optionsSelector, options);
	__DELETE(options);

	// make a little bit of physical simulations so each entity is placed at the floor
	GameState::startClocks(__SAFE_CAST(GameState, this));

	// show up level after a little delay
	MessageDispatcher::dispatchMessage(500, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game::getInstance()), kLevelSetUp, NULL);
}

// state's exit
void TitleScreenState::exit(void* owner)
{
	// call base
	Base::exit(this, owner);
}

// state's resume
void TitleScreenState::resume(void* owner)
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
	GameState::propagateMessage(__SAFE_CAST(GameState, this), kLevelResumed);

	// make a fade in
	Camera::startEffect(Camera::getInstance(), kFadeIn, __FADE_DELAY);

	// pause physical simulations
	GameState::pausePhysics(__SAFE_CAST(GameState, this), false);

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
void TitleScreenState::suspend(void* owner)
{	// pause physical simulations
	GameState::pausePhysics(__SAFE_CAST(GameState, this), true);

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

void TitleScreenState::showMessage()
{
	const char* strPressStartButton = I18n::getText(I18n::getInstance(), STR_PRESS_START_BUTTON);
	FontSize strPressStartButtonSize = Printing::getTextSize(Printing::getInstance(), strPressStartButton, NULL);
	u8 strXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (strPressStartButtonSize.x >> 1);
	Printing::text(Printing::getInstance(), strPressStartButton, strXPos, 26, NULL);
}

void TitleScreenState::hideMessage()
{
	Printing::text(Printing::getInstance(), "                                                ", 0, 25, NULL);
	Printing::text(Printing::getInstance(), "                                                ", 0, 26, NULL);
	Printing::text(Printing::getInstance(), "                                                ", 0, 27, NULL);
}

void TitleScreenState::processUserInput(UserInput userInput)
{
	if((K_STA & userInput.pressedKey) || (K_A & userInput.pressedKey))
	{
		switch(this->mode)
		{
			case kTitleScreenModeShowPressStart:
			{
				// disable blinking "press start button"
				Object::removeEventListener(__SAFE_CAST(Object, Game::getUpdateClock(Game::getInstance())), __SAFE_CAST(Object, this), (void (*)(Object, Object))TitleScreenState::onSecondChange, kEventSecondChanged);
				TitleScreenState::hideMessage(this);

				// print options
				OptionsSelector::printOptions(
					this->optionsSelector,
					1 + (((__SCREEN_WIDTH_IN_CHARS) - OptionsSelector::getWidth(this->optionsSelector)) >> 1),
					26
				);

				// set mode to showing options
				this->mode = kTitleScreenModeShowOptions;

				break;
			}
			case kTitleScreenModeShowOptions:
			{
				int selectedOption = OptionsSelector::getSelectedOption(this->optionsSelector);

				switch(selectedOption)
				{
					case kTitleScreenOptionContinue:
					case kTitleScreenOptionOptions:

						// disable user input
						Game::disableKeypad(Game::getInstance());

						// fade out screen
						Brightness brightness = (Brightness){0, 0, 0};
						Camera::startEffect(Camera::getInstance(),
							kFadeTo, // effect type
							0, // initial delay (in ms)
							&brightness, // target brightness
							__FADE_DELAY, // delay between fading steps (in ms)
							(void (*)(Object, Object))TitleScreenState::onFadeOutComplete, // callback function
							__SAFE_CAST(Object, this) // callback scope
						);

						break;

					case kTitleScreenOptionNewGame:

						// remove main menu
						TitleScreenState::hideMessage(this);

						// set mode to new game confirm
						this->mode = kTitleScreenModeShowConfirmNewGame;

						// print warning
						const char* strNewGameConfirm = I18n::getText(I18n::getInstance(), STR_PROGRESS_WILL_BE_ERASED);
						FontSize strNewGameConfirmSize = Printing::getTextSize(Printing::getInstance(), strNewGameConfirm, NULL);
						u8 strNewGameConfirmXPos = (((__SCREEN_WIDTH_IN_CHARS) - strNewGameConfirmSize.x) >> 1);
						const char* strAreYouSure = I18n::getText(I18n::getInstance(), STR_ARE_YOU_SURE);
						FontSize strAreYouSureSize = Printing::getTextSize(Printing::getInstance(), strAreYouSure, NULL);
						u8 strAreYouSureXPos = (((__SCREEN_WIDTH_IN_CHARS) - strAreYouSureSize.x) >> 1);
						Printing::text(
							Printing::getInstance(),
							strNewGameConfirm,
							strNewGameConfirmXPos,
							25,
							NULL
						);
						Printing::text(
							Printing::getInstance(),
							strAreYouSure,
							strAreYouSureXPos,
							26,
							NULL
						);

						// print warning options
						const char* strYes = I18n::getText(I18n::getInstance(), STR_YES);
						FontSize strYesSize = Printing::getTextSize(Printing::getInstance(), strYes, NULL);
						const char* strNo = I18n::getText(I18n::getInstance(), STR_NO);
						FontSize strNoSize = Printing::getTextSize(Printing::getInstance(), strNo, NULL);

						u8 strYesXPos = ((__SCREEN_WIDTH_IN_CHARS) - (strYesSize.x + strNoSize.x + 3)) >> 1;
						u8 strNoXPos = strYesXPos + strYesSize.x + 2;

						Printing::text(Printing::getInstance(), __CHAR_A_BUTTON, strYesXPos - 1, 27, NULL);
						Printing::text(Printing::getInstance(), strYes, strYesXPos, 27, NULL);
						Printing::text(Printing::getInstance(), __CHAR_B_BUTTON, strNoXPos - 1, 27, NULL);
						Printing::text(Printing::getInstance(), strNo, strNoXPos, 27, NULL);

						break;
				}

				break;
			}
			case kTitleScreenModeShowConfirmNewGame:
			{
				// clear progress
				ProgressManager::clearProgress(ProgressManager::getInstance());

				// disable user input
				Game::disableKeypad(Game::getInstance());

				// fade out screen
				Brightness brightness = (Brightness){0, 0, 0};
				Camera::startEffect(Camera::getInstance(),
					kFadeTo, // effect type
					0, // initial delay (in ms)
					&brightness, // target brightness
					__FADE_DELAY, // delay between fading steps (in ms)
					(void (*)(Object, Object))TitleScreenState::onFadeOutComplete, // callback function
					__SAFE_CAST(Object, this) // callback scope
				);

				break;
			}
		}
	}
	else if((this->mode == kTitleScreenModeShowOptions) && ((userInput.pressedKey & K_LL) || (userInput.pressedKey & K_RL)))
	{
		OptionsSelector::selectPrevious(this->optionsSelector);
	}
	else if((this->mode == kTitleScreenModeShowOptions) && ((userInput.pressedKey & K_LR) || (userInput.pressedKey & K_RR)))
	{
		OptionsSelector::selectNext(this->optionsSelector);
	}
	else if((this->mode == kTitleScreenModeShowConfirmNewGame) && (userInput.pressedKey & K_B))
	{
		// remove message
		TitleScreenState::hideMessage(this);

		// print options
		OptionsSelector::setSelectedOption(this->optionsSelector, kTitleScreenOptionContinue);
		OptionsSelector::printOptions(
			this->optionsSelector,
			1 + (((__SCREEN_WIDTH_IN_CHARS) - OptionsSelector::getWidth(this->optionsSelector)) >> 1),
			26
		);

		// set mode to showing options
		this->mode = kTitleScreenModeShowOptions;
	}
}
// state's handle message
bool TitleScreenState::processMessage(void* owner __attribute__ ((unused)), Telegram telegram)
{
	// process message
	switch(Telegram::getMessage(telegram))
	{
		case kLevelSetUp:

			// tell any interested entity
			GameState::propagateMessage(__SAFE_CAST(GameState, this), kLevelSetUp);

			// show level after a little delay
			MessageDispatcher::dispatchMessage(500, __SAFE_CAST(Object, this), __SAFE_CAST(Object, Game::getInstance()), kLevelStarted, NULL);
			break;

		case kLevelStarted:

			// fade in screen
			Camera::startEffect(Camera::getInstance(),
				kFadeTo, // effect type
				0, // initial delay (in ms)
				NULL, // target brightness
				__FADE_DELAY, // delay between fading steps (in ms)
				(void (*)(Object, Object))TitleScreenState::onFadeInComplete, // callback function
				__SAFE_CAST(Object, this) // callback scope
			);

			break;
	}

	return false;
}

// handle event
void TitleScreenState::onSecondChange(Object eventFirer __attribute__ ((unused)))
{
	if((Clock::getSeconds(Game::getUpdateClock(Game::getInstance())) % 2) == 0)
	{
		TitleScreenState::showMessage(this);
	}
	else
	{
		TitleScreenState::hideMessage(this);
	}
}

// handle event
void TitleScreenState::onFadeInComplete(Object eventFirer __attribute__ ((unused)))
{
	// tell any interested entity
	GameState::propagateMessage(__SAFE_CAST(GameState, this), kLevelStarted);

	// enable user input
	Game::enableKeypad(Game::getInstance());
}

// handle event
void TitleScreenState::onFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	int selectedOption = OptionsSelector::getSelectedOption(this->optionsSelector);

	switch(selectedOption)
	{
		case kTitleScreenOptionContinue:
		case kTitleScreenOptionNewGame:

			// switch to overworld
			Game::changeState(Game::getInstance(), __SAFE_CAST(GameState, OverworldState::getInstance()));

			break;

		case kTitleScreenOptionOptions:

			// switch to options screen
			OptionsScreenState::setNextState(OptionsScreenState::getInstance(), __SAFE_CAST(GameState, this));
			Game::changeState(Game::getInstance(), __SAFE_CAST(GameState, OptionsScreenState::getInstance()));

			break;
	}
}
