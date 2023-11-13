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

#include <VUEngine.h>
#include <Camera.h>
#include <CameraEffectManager.h>
#include <MessageDispatcher.h>
#include <I18n.h>
#include <PhysicalWorld.h>
#include <PauseScreenState.h>
#include <Hero.h>
#include <OverworldState.h>
#include <OptionsScreenState.h>
#include <PlatformerLevelState.h>
#include <Languages.h>
#include <KeypadManager.h>
#include <SoundManager.h>
#include <Utilities.h>
#include <VirtualList.h>
#include <Printing.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMSpec PauseScreenStage;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void PauseScreenState::constructor()
{
	Base::constructor();

	// init members
	this->mode = kPauseScreenModeShowOptions;
	this->optionsSelector = new OptionsSelector(1, 3, "Platformer", NULL, NULL);
}

// class's destructor
void PauseScreenState::destructor()
{
	delete this->optionsSelector;

	// destroy base
	Base::destructor();
}

// state's enter
void PauseScreenState::enter(void* owner __attribute__ ((unused)))
{
	// call base
	Base::enter(this, owner);

	// load stage
	GameState::loadStage(this, (StageSpec*)&PauseScreenStage, NULL, true, false);

	// print pause text
	const char* strPause = I18n::getText(I18n::getInstance(), kStringPause);
	const char* strPauseFont = "AstonishSExt";
	FontSize strPauseSize = Printing::getTextSize(Printing::getInstance(), strPause, strPauseFont);
	Printing::text(
		Printing::getInstance(),
		Utilities::toUppercase(strPause),
		(((__SCREEN_WIDTH_IN_CHARS) - strPauseSize.x) >> 1),
		14,
		strPauseFont
	);

	// show menu
	VirtualList options = new VirtualList();
	Option* option = NULL;

	option = new Option;
	option->value = (char*)I18n::getText(I18n::getInstance(), kStringContinue);
	option->type = kString;
	option->callback = NULL;
	option->callbackScope = NULL;
	VirtualList::pushBack(options, option);

	option = new Option;
	option->value = (char*)I18n::getText(I18n::getInstance(), kStringOptions);
	option->type = kString;
	option->callback = NULL;
	option->callbackScope = NULL;
	VirtualList::pushBack(options, option);

	option = new Option;
	option->value = (char*)I18n::getText(I18n::getInstance(), kStringQuitLevel);
	option->type = kString;
	option->callback = NULL;
	option->callbackScope = NULL;
	VirtualList::pushBack(options, option);

	OptionsSelector::setOptions(this->optionsSelector, options);
	delete options;

	OptionsSelector::printOptions(
		this->optionsSelector,
		(((__SCREEN_WIDTH_IN_CHARS) - strPauseSize.x) >> 1) - 1,
		17,
		kOptionsAlignLeft, 0
	);

	// disable user input
	VUEngine::disableKeypad(VUEngine::getInstance());

	// start clocks to start animations
	GameState::startClocks(this);

	// fade in screen
	Camera::startEffect(Camera::getInstance(), kHide);
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))PauseScreenState::onFadeInComplete, // callback function
		Object::safeCast(this) // callback scope
	);

	this->mode = kPauseScreenModeShowOptions;
}

// state's exit
void PauseScreenState::exit(void* owner __attribute__ ((unused)))
{
	// call base
	Base::exit(this, owner);
}

void PauseScreenState::processUserInput(UserInput userInput)
{
	if((K_STA & userInput.pressedKey) || (K_A & userInput.pressedKey))
	{
		if(this->mode == kPauseScreenModeShowOptions)
		{
			int selectedOption = OptionsSelector::getSelectedOption(this->optionsSelector);

			switch(selectedOption)
			{
				case kPauseScreenOptionContinue:
				case kPauseScreenOptionOptions:

					// disable user input
					VUEngine::disableKeypad(VUEngine::getInstance());

					// fade out screen
					Brightness brightness = (Brightness){0, 0, 0};
					Camera::startEffect(Camera::getInstance(),
						kFadeTo, // effect type
						0, // initial delay (in ms)
						&brightness, // target brightness
						__FADE_DELAY, // delay between fading steps (in ms)
						(void (*)(Object, Object))PauseScreenState::onFadeOutComplete, // callback function
						Object::safeCast(this) // callback scope
					);

					// play sound
					PauseScreenState::playConfirmSound(this);

					break;

				case kPauseScreenOptionQuitLevel:
				{
					// print confirmation message
					const char* strYes = I18n::getText(I18n::getInstance(), kStringYes);
					FontSize strYesSize = Printing::getTextSize(Printing::getInstance(), strYes, "Platformer");
					const char* strNo = I18n::getText(I18n::getInstance(), kStringNo);
					const char* strAreYouSure = I18n::getText(I18n::getInstance(), kStringAreYouSure);
					const char* strPause = I18n::getText(I18n::getInstance(), kStringPause);
					const char* strPauseFont = "AstonishSExt";
					FontSize strPauseSize = Printing::getTextSize(Printing::getInstance(), strPause, strPauseFont);

					uint8 strXPos = ((__SCREEN_WIDTH_IN_CHARS) - strPauseSize.x) >> 1;
					uint8 strNoXPos = strXPos + strYesSize.x + 2;

					Printing::text(Printing::getInstance(), strAreYouSure, strXPos, 21, "Platformer");
					Printing::text(Printing::getInstance(), __CHAR_A_BUTTON, strXPos, 22, "Platformer");
					Printing::text(Printing::getInstance(), strYes, strXPos + 1, 22, "Platformer");
					Printing::text(Printing::getInstance(), __CHAR_B_BUTTON, strNoXPos, 22, "Platformer");
					Printing::text(Printing::getInstance(), strNo, strNoXPos + 1, 22, "Platformer");

					// set mode accordingly
					this->mode = kPauseScreenModeShowConfirmQuit;

					// play sound
					PauseScreenState::playConfirmSound(this);

					break;
				}
			}
		}
		else if(this->mode == kPauseScreenModeShowConfirmQuit)
		{
			// disable user input
			VUEngine::disableKeypad(VUEngine::getInstance());

			// fade out screen
			Brightness brightness = (Brightness){0, 0, 0};
			Camera::startEffect(Camera::getInstance(),
				kFadeTo, // effect type
				0, // initial delay (in ms)
				&brightness, // target brightness
				__FADE_DELAY, // delay between fading steps (in ms)
				(void (*)(Object, Object))PauseScreenState::onFadeOutComplete, // callback function
				Object::safeCast(this) // callback scope
			);

			// play sound
			PauseScreenState::playConfirmSound(this);
		}
	}
	else if((this->mode == kPauseScreenModeShowConfirmQuit) && (userInput.pressedKey & K_B))
	{
		// remove confirmation message
		Printing::text(Printing::getInstance(), "												", 0, 21, "Platformer");
		Printing::text(Printing::getInstance(), "												", 0, 22, "Platformer");

		// set mode back to main menu
		this->mode = kPauseScreenModeShowOptions;
	}
	else if((this->mode == kPauseScreenModeShowOptions) && ((userInput.pressedKey & K_LU) || (userInput.pressedKey & K_RU)))
	{
		OptionsSelector::selectPrevious(this->optionsSelector);
		PauseScreenState::playMenuSound(this);
	}
	else if((this->mode == kPauseScreenModeShowOptions) && ((userInput.pressedKey & K_LD) || (userInput.pressedKey & K_RD)))
	{
		OptionsSelector::selectNext(this->optionsSelector);
		PauseScreenState::playMenuSound(this);
	}
}

void PauseScreenState::playMenuSound()
{
/*	extern Sound OPTION_SELECT_SND;
	Vector3D position = Vector3D::getFromPixelVector((PixelVector){192, 112, 0, 0});
	SoundManager::playSound(SoundManager::getInstance(), &OPTION_SELECT_SND, kPlayAll, (const Vector3D*)&position, kSoundWrapperPlaybackNormal, NULL, NULL);
	*/
}

void PauseScreenState::playConfirmSound()
{
/*	extern Sound OPTION_CONFIRM_SND;
	Vector3D position = Vector3D::getFromPixelVector((PixelVector){192, 112, 0, 0});
	SoundManager::playSound(SoundManager::getInstance(), &OPTION_CONFIRM_SND, kPlayAll, (const Vector3D*)&position, kSoundWrapperPlaybackNormal, NULL, NULL);
*/
}

// handle event
void PauseScreenState::onFadeInComplete(Object eventFirer __attribute__ ((unused)))
{
	VUEngine::enableKeypad(VUEngine::getInstance());
}

// handle event
void PauseScreenState::onFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	// re-enable user input
	VUEngine::enableKeypad(VUEngine::getInstance());

	// switch state according to selection
	int selectedOption = OptionsSelector::getSelectedOption(this->optionsSelector);
	switch(selectedOption)
	{
		case kPauseScreenOptionContinue:

			// resume game
			VUEngine::unpause(VUEngine::getInstance(), GameState::safeCast(this));
			break;

		case kPauseScreenOptionOptions:

			// switch to options state
			OptionsScreenState::setNextState(OptionsScreenState::getInstance(), GameState::safeCast(this));
			VUEngine::changeState(VUEngine::getInstance(), GameState::safeCast(OptionsScreenState::getInstance()));
			break;

		case kPauseScreenOptionQuitLevel:

			// switch to overworld after deleting paused game state
			VUEngine::cleanAndChangeState(VUEngine::getInstance(), GameState::safeCast(OverworldState::getInstance()));

			break;
	}
}
