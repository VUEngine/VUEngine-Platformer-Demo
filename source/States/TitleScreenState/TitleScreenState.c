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
#include <Languages.h>
#include <PhysicalWorld.h>
#include <TitleScreenState.h>
#include <Hero.h>
#include <ParticleSystem.h>
#include <PlatformerLevelState.h>
#include <OptionsScreenState.h>
#include <PlatformerCameraMovementManager.h>
#include <ProgressManager.h>
#include <EventManager.h>
#include <OverworldState.h>
#include <KeypadManager.h>
#include <Printing.h>
#include <SoundManager.h>
#include <VirtualList.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMSpec TitleScreenStage;


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
		delete this->optionsSelector;
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
	ListenerObject::addEventListener(ListenerObject::safeCast(VUEngine::getUpdateClock(VUEngine::getInstance())), ListenerObject::safeCast(this), (EventListener)TitleScreenState::onSecondChange, kEventSecondChanged);

	// call base
	Base::enter(this, owner);

	// disable user input
	VUEngine::disableKeypad(VUEngine::getInstance());

	// load stage
	GameState::loadStage(this, (StageSpec*)&TitleScreenStage, NULL, true, false);

	if(this->optionsSelector)
	{
		delete this->optionsSelector;
	}

	// create and populate main menu
	VirtualList options = new VirtualList();
	if(ProgressManager::hasProgress(ProgressManager::getInstance()))
	{
		this->optionsSelector = new OptionsSelector(3, 1, "Platformer", NULL, NULL);
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
		option->value = (char*)I18n::getText(I18n::getInstance(), kStringNewGame);
		option->type = kString;
		option->callback = NULL;
		option->callbackScope = NULL;
		VirtualList::pushBack(options, option);

		FontSize strContinueSize = Printing::getTextSize(Printing::getInstance(), I18n::getText(I18n::getInstance(), kStringContinue), "Platformer");
		FontSize strOptionsSize = Printing::getTextSize(Printing::getInstance(), I18n::getText(I18n::getInstance(), kStringOptions), "Platformer");
		FontSize strNewGameSize = Printing::getTextSize(Printing::getInstance(), I18n::getText(I18n::getInstance(), kStringNewGame), "Platformer");
		uint8 width = (strContinueSize.x > strOptionsSize.x) ? strContinueSize.x : strOptionsSize.x;
		width = (width > strNewGameSize.x) ? width : strNewGameSize.x;
		OptionsSelector::setColumnWidth(this->optionsSelector, width + 1);
	}
	else
	{
		this->optionsSelector = new OptionsSelector(2, 1, "Platformer", NULL, NULL);
		Option* option = NULL;

		option = new Option;
		option->value = (char*)I18n::getText(I18n::getInstance(), kStringNewGame);
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

		FontSize strOptionsSize = Printing::getTextSize(Printing::getInstance(), I18n::getText(I18n::getInstance(), kStringOptions), "Platformer");
		FontSize strNewGameSize = Printing::getTextSize(Printing::getInstance(), I18n::getText(I18n::getInstance(), kStringNewGame), "Platformer");
		uint8 width = (strOptionsSize.x > strNewGameSize.x) ? strOptionsSize.x : strNewGameSize.x;
		OptionsSelector::setColumnWidth(this->optionsSelector, width + 1);
	}

	OptionsSelector::setOptions(this->optionsSelector, options);
	delete options;

	// make a little bit of physical simulations so each entity is placed at the floor
	GameState::startClocks(this);

	// tell any interested entity
	GameState::propagateMessage(this, kMessageLevelSetUp);

	// fade in screen after a little delay
	Camera::startEffect(Camera::getInstance(), kHide);
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		250, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(EventListener)TitleScreenState::onFadeInComplete, // callback function
		Object::safeCast(this) // callback scope
	);

#ifdef __ENABLE_PROFILER
	VUEngine::startProfiling(VUEngine::getInstance());
#endif
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
	if(!VUEngine::isExitingSpecialMode(VUEngine::getInstance()))
	{
#endif
#ifdef __STAGE_EDITOR
	if(!VUEngine::isExitingSpecialMode(VUEngine::getInstance()))
	{
#endif
#ifdef __ANIMATION_INSPECTOR
	if(!VUEngine::isExitingSpecialMode(VUEngine::getInstance()))
	{
#endif

	// tell any interested entity
	GameState::propagateMessage(this, kMessageLevelResumed);

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
void TitleScreenState::suspend(void* owner)
{	// pause physical simulations
	GameState::pausePhysics(this, true);

#ifdef __DEBUG_TOOLS
	if(!VUEngine::isEnteringSpecialMode(VUEngine::getInstance()))
#endif
#ifdef __STAGE_EDITOR
	if(!VUEngine::isEnteringSpecialMode(VUEngine::getInstance()))
#endif
#ifdef __ANIMATION_INSPECTOR
	if(!VUEngine::isEnteringSpecialMode(VUEngine::getInstance()))
#endif

	// make a fade out
	Camera::startEffect(Camera::getInstance(), kFadeOut, __FADE_DELAY);

	Base::suspend(this, owner);
}

void TitleScreenState::showMessage()
{
	const char* strPressStartButton = I18n::getText(I18n::getInstance(), kStringPressStartButton);
	FontSize strPressStartButtonSize = Printing::getTextSize(Printing::getInstance(), strPressStartButton, "Platformer");
	uint8 strXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (strPressStartButtonSize.x >> 1);
	Printing::text(Printing::getInstance(), strPressStartButton, strXPos, 26, "Platformer");
}

void TitleScreenState::hideMessage()
{
	Printing::text(Printing::getInstance(), "                                                ", 0, 25, "Platformer");
	Printing::text(Printing::getInstance(), "                                                ", 0, 26, "Platformer");
	Printing::text(Printing::getInstance(), "                                                ", 0, 27, "Platformer");
}

void TitleScreenState::processUserInput(UserInput userInput)
{
	if((K_STA & userInput.pressedKey) || (K_A & userInput.pressedKey))
	{
		switch(this->mode)
		{
			case kTitleScreenModeShowPressStart:
			{
				// disable flashing "press start button"
				ListenerObject::removeEventListener(ListenerObject::safeCast(VUEngine::getUpdateClock(VUEngine::getInstance())), ListenerObject::safeCast(this), (EventListener)TitleScreenState::onSecondChange, kEventSecondChanged);
				TitleScreenState::hideMessage(this);

				// print options
				OptionsSelector::printOptions(
					this->optionsSelector,
					1 + (((__SCREEN_WIDTH_IN_CHARS) - OptionsSelector::getWidth(this->optionsSelector)) >> 1),
					26,
					kOptionsAlignLeft, 0
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
						VUEngine::disableKeypad(VUEngine::getInstance());

						// fade out screen
						Brightness brightness = (Brightness){0, 0, 0};
						Camera::startEffect(Camera::getInstance(),
							kFadeTo, // effect type
							0, // initial delay (in ms)
							&brightness, // target brightness
							__FADE_DELAY, // delay between fading steps (in ms)
							(EventListener)TitleScreenState::onFadeOutComplete, // callback function
							Object::safeCast(this) // callback scope
						);

						// play sound
						TitleScreenState::playConfirmSound(this);

						break;

					case kTitleScreenOptionNewGame:

						// remove main menu
						TitleScreenState::hideMessage(this);

						// set mode to new game confirm
						this->mode = kTitleScreenModeShowConfirmNewGame;

						// print warning
						const char* strNewGameConfirm = I18n::getText(I18n::getInstance(), kStringProgressWillBeErased);
						FontSize strNewGameConfirmSize = Printing::getTextSize(Printing::getInstance(), strNewGameConfirm, "Platformer");
						uint8 strNewGameConfirmXPos = (((__SCREEN_WIDTH_IN_CHARS) - strNewGameConfirmSize.x) >> 1);
						const char* strAreYouSure = I18n::getText(I18n::getInstance(), kStringAreYouSure);
						FontSize strAreYouSureSize = Printing::getTextSize(Printing::getInstance(), strAreYouSure, "Platformer");
						uint8 strAreYouSureXPos = (((__SCREEN_WIDTH_IN_CHARS) - strAreYouSureSize.x) >> 1);
						Printing::text(
							Printing::getInstance(),
							strNewGameConfirm,
							strNewGameConfirmXPos,
							25,
							"Platformer"
						);
						Printing::text(
							Printing::getInstance(),
							strAreYouSure,
							strAreYouSureXPos,
							26,
							"Platformer"
						);

						// print warning options
						const char* strYes = I18n::getText(I18n::getInstance(), kStringYes);
						FontSize strYesSize = Printing::getTextSize(Printing::getInstance(), strYes, "Platformer");
						const char* strNo = I18n::getText(I18n::getInstance(), kStringNo);
						FontSize strNoSize = Printing::getTextSize(Printing::getInstance(), strNo, "Platformer");

						uint8 strYesXPos = ((__SCREEN_WIDTH_IN_CHARS) - (strYesSize.x + strNoSize.x + 3)) >> 1;
						uint8 strNoXPos = strYesXPos + strYesSize.x + 2;

						Printing::text(Printing::getInstance(), __CHAR_A_BUTTON, strYesXPos - 1, 27, "Platformer");
						Printing::text(Printing::getInstance(), strYes, strYesXPos, 27, "Platformer");
						Printing::text(Printing::getInstance(), __CHAR_B_BUTTON, strNoXPos - 1, 27, "Platformer");
						Printing::text(Printing::getInstance(), strNo, strNoXPos, 27, "Platformer");

						break;
				}

				break;
			}
			case kTitleScreenModeShowConfirmNewGame:
			{
				// clear progress
				ProgressManager::clearProgress(ProgressManager::getInstance());

				// disable user input
				VUEngine::disableKeypad(VUEngine::getInstance());

				// fade out screen
				Brightness brightness = (Brightness){0, 0, 0};
				Camera::startEffect(Camera::getInstance(),
					kFadeTo, // effect type
					0, // initial delay (in ms)
					&brightness, // target brightness
					__FADE_DELAY, // delay between fading steps (in ms)
					(EventListener)TitleScreenState::onFadeOutComplete, // callback function
					Object::safeCast(this) // callback scope
				);

				break;
			}
		}
	}
	else if((this->mode == kTitleScreenModeShowOptions) && ((userInput.pressedKey & K_LL) || (userInput.pressedKey & K_RL)))
	{
		OptionsSelector::selectPrevious(this->optionsSelector);
		TitleScreenState::playMenuSound(this);
	}
	else if((this->mode == kTitleScreenModeShowOptions) && ((userInput.pressedKey & K_LR) || (userInput.pressedKey & K_RR)))
	{
		OptionsSelector::selectNext(this->optionsSelector);
		TitleScreenState::playMenuSound(this);
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
			26,
			kOptionsAlignLeft, 0
		);

		// set mode to showing options
		this->mode = kTitleScreenModeShowOptions;
	}
}

void TitleScreenState::playMenuSound()
{
/*	extern SoundSpec OPTION_SELECT_SND;
	Vector3D position = Vector3D::getFromPixelVector((PixelVector){192, 112, 0, 0});
	SoundManager::playSound(SoundManager::getInstance(), &OPTION_SELECT_SND, kPlayAll, (const Vector3D*)&position, kSoundPlaybackNormal, NULL, NULL);
	*/
}

void TitleScreenState::playConfirmSound()
{
/*	extern SoundSpec OPTION_CONFIRM_SND;
	Vector3D position = Vector3D::getFromPixelVector((PixelVector){192, 112, 0, 0});
	SoundManager::playSound(SoundManager::getInstance(), &OPTION_CONFIRM_SND, kPlayAll, (const Vector3D*)&position, kSoundPlaybackNormal, NULL, NULL);
	*/
}

// handle event
void TitleScreenState::onSecondChange(Object eventFirer __attribute__ ((unused)))
{
	if((Clock::getSeconds(VUEngine::getUpdateClock(VUEngine::getInstance())) % 2) == 0)
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
	GameState::propagateMessage(this, kMessageLevelStarted);

	// enable user input
	VUEngine::enableKeypad(VUEngine::getInstance());
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
			VUEngine::changeState(VUEngine::getInstance(), GameState::safeCast(OverworldState::getInstance()));

			break;

		case kTitleScreenOptionOptions:

			// switch to options screen
			OptionsScreenState::setNextState(OptionsScreenState::getInstance(), GameState::safeCast(this));
			VUEngine::changeState(VUEngine::getInstance(), GameState::safeCast(OptionsScreenState::getInstance()));

			break;
	}
}
