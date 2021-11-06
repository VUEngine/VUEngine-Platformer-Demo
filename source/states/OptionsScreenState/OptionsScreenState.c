/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
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
#include <AutomaticPauseSelectionScreenState.h>
#include <LanguageSelectionScreenState.h>
#include <TitleScreenState.h>
#include <KeypadManager.h>
#include <SoundManager.h>
#include "OptionsScreenState.h"


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMSpec EmptyStage;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void OptionsScreenState::constructor()
{
	Base::constructor();

	// init members
	this->optionsSelector = new OptionsSelector(1, 2, NULL);
	OptionsScreenState::setNextState(this, GameState::safeCast(TitleScreenState::getInstance()));
}

// class's destructor
void OptionsScreenState::destructor()
{
	delete this->optionsSelector;

	// destroy base
	Base::destructor();
}

// state's enter
void OptionsScreenState::enter(void* owner __attribute__ ((unused)))
{
	// call base
	Base::enter(this, owner);

	// load stage
	GameState::loadStage(this, (StageSpec*)&EmptyStage, NULL, true, false);

	// print options
	OptionsScreenState::print(this);

	// start clocks to start animations
	GameState::startClocks(this);

	// disable user input
	Game::disableKeypad(Game::getInstance());

	// fade in screen
	Camera::startEffect(Camera::getInstance(), kHide);
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))OptionsScreenState::onFadeInComplete, // callback function
		Object::safeCast(this) // callback scope
	);
}

// state's exit
void OptionsScreenState::exit(void* owner __attribute__ ((unused)))
{
	// call base
	Base::exit(this, owner);
}

// set next state
void OptionsScreenState::setNextState(GameState nextState)
{
	this->nextState = nextState;
}

// print level stats
void OptionsScreenState::print()
{
	// title
	const char* strOptionsTitle = I18n::getText(I18n::getInstance(), kStringOptions);
	const char* strOptionsTitleFont = "AstonishSExt";
	FontSize strOptionsTextSize = Printing::getTextSize(Printing::getInstance(), strOptionsTitle, strOptionsTitleFont);
	Printing::text(
		Printing::getInstance(),
		Utilities::toUppercase(strOptionsTitle),
		((__SCREEN_WIDTH_IN_CHARS) - strOptionsTextSize.x) >> 1,
		8,
		strOptionsTitleFont
	);

	// menu
	VirtualList options = new VirtualList();
	Option* option = NULL;

	option = new Option;
	option->value = (char*)I18n::getText(I18n::getInstance(), kStringAutomaticPause);
	option->type = kString;
	option->callback = (void (*)(Object))OptionsScreenState::onOptionAutomaticPauseSelect;
	option->callbackScope = Object::safeCast(this);
	VirtualList::pushBack(options, option);

	option = new Option;
	option->value = (char*)I18n::getText(I18n::getInstance(), kStringLanguage);
	option->type = kString;
	option->callback = (void (*)(Object))OptionsScreenState::onOptionLanguageSelect;
	option->callbackScope = Object::safeCast(this);
	VirtualList::pushBack(options, option);

	OptionsSelector::setOptions(this->optionsSelector, options);
	delete options;

	OptionsSelector::printOptions(
		this->optionsSelector,
		((__SCREEN_WIDTH_IN_CHARS) - strOptionsTextSize.x) >> 1,
		11
	);

	// buttons
	const char* strSelect = I18n::getText(I18n::getInstance(), kStringSelect);
	FontSize strSelectSize = Printing::getTextSize(Printing::getInstance(), strSelect, "Platformer");
	const char* strBack = I18n::getText(I18n::getInstance(), kStringBack);

	uint8 strSelectXPos = ((__SCREEN_WIDTH_IN_CHARS) - strOptionsTextSize.x) >> 1;
	uint8 strBackXPos = strSelectXPos + strSelectSize.x + 2;

	Printing::text(Printing::getInstance(), __CHAR_A_BUTTON, strSelectXPos, 15, "Platformer");
	Printing::text(Printing::getInstance(), strSelect, strSelectXPos + 1, 15, "Platformer");
	Printing::text(Printing::getInstance(), __CHAR_B_BUTTON, strBackXPos, 15, "Platformer");
	Printing::text(Printing::getInstance(), strBack, strBackXPos + 1, 15, "Platformer");
}

void OptionsScreenState::processUserInput(UserInput userInput)
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
			Object::safeCast(this) // callback scope
		);

		OptionsScreenState::playConfirmSound(this);
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
			Object::safeCast(this) // callback scope
		);
	}
	else if((userInput.pressedKey & K_LU) || (userInput.pressedKey & K_RU))
	{
		OptionsSelector::selectPrevious(this->optionsSelector);
		OptionsScreenState::playMenuSound(this);
	}
	else if((userInput.pressedKey & K_LD) || (userInput.pressedKey & K_RD))
	{
		OptionsSelector::selectNext(this->optionsSelector);
		OptionsScreenState::playMenuSound(this);
	}
}

void OptionsScreenState::playMenuSound()
{
/*	extern Sound OPTION_SELECT_SND;
	Vector3D position = Vector3D::getFromPixelVector((PixelVector){192, 112, 0, 0});
	SoundManager::playSound(SoundManager::getInstance(), &OPTION_SELECT_SND, kPlayAll, (const Vector3D*)&position, kSoundWrapperPlaybackNormal, NULL, NULL);
	*/
}

void OptionsScreenState::playConfirmSound()
{
/*	extern Sound OPTION_CONFIRM_SND;
	Vector3D position = Vector3D::getFromPixelVector((PixelVector){192, 112, 0, 0});
	SoundManager::playSound(SoundManager::getInstance(), &OPTION_CONFIRM_SND, kPlayAll, (const Vector3D*)&position, kSoundWrapperPlaybackNormal, NULL, NULL);
	*/
}

// handle event
void OptionsScreenState::onFadeInComplete(Object eventFirer __attribute__ ((unused)))
{
	Game::enableKeypad(Game::getInstance());
}

void OptionsScreenState::onExitFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	// switch to next screen
	Game::changeState(Game::getInstance(), this->nextState);
}

void OptionsScreenState::onOptionSelectedFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	OptionsSelector::doCurrentSelectionCallback(this->optionsSelector);
}

void OptionsScreenState::onOptionAutomaticPauseSelect()
{
	SplashScreenState::setNextState(SplashScreenState::safeCast(AutomaticPauseSelectionScreenState::getInstance()), GameState::safeCast(this));
	Game::changeState(Game::getInstance(), GameState::safeCast(AutomaticPauseSelectionScreenState::getInstance()));
}

void OptionsScreenState::onOptionLanguageSelect()
{
	SplashScreenState::setNextState(SplashScreenState::safeCast(LanguageSelectionScreenState::getInstance()), GameState::safeCast(this));
	Game::changeState(Game::getInstance(), GameState::safeCast(LanguageSelectionScreenState::getInstance()));
}
