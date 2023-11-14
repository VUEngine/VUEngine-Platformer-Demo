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
#include <PhysicalWorld.h>
#include <I18n.h>
#include <AutomaticPauseScreenState.h>
#include <KeypadManager.h>
#include <Languages.h>
#include <Utilities.h>
#include <Printing.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMSpec PauseScreenStage;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void AutomaticPauseScreenState::constructor()
{
	Base::constructor();
}

// class's destructor
void AutomaticPauseScreenState::destructor()
{
	// destroy base
	Base::destructor();
}

// state's enter
void AutomaticPauseScreenState::enter(void* owner __attribute__ ((unused)))
{
	// load stage
	GameState::loadStage(this, (StageSpec*)&PauseScreenStage, NULL, true, false);

	// print text
	const char* strAutomaticPauseTitle = I18n::getText(I18n::getInstance(), kStringAutomaticPauseTitle);
	const char* strAutomaticPauseTitleFont = "AstonishSExt";
	const char* strAutomaticPauseText = I18n::getText(I18n::getInstance(), kStringAutomaticPauseBody);
	FontSize strAutomaticPauseSize = Printing::getTextSize(Printing::getInstance(), strAutomaticPauseTitle, strAutomaticPauseTitleFont);
	FontSize strAutomaticPauseTextSize = Printing::getTextSize(Printing::getInstance(), strAutomaticPauseText, "Platformer");

	uint8 strHeaderXPos = ((__HALF_SCREEN_WIDTH_IN_CHARS) - (strAutomaticPauseSize.x >> 1));
	Printing::text(
		Printing::getInstance(),
		Utilities::toUppercase(strAutomaticPauseTitle),
		strHeaderXPos,
		14,
		strAutomaticPauseTitleFont
	);

	uint8 strTextXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (strAutomaticPauseTextSize.x >> 1);
	Printing::text(Printing::getInstance(), strAutomaticPauseText, strTextXPos, 15 + strAutomaticPauseSize.y, "Platformer");

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
		(EventListener)AutomaticPauseScreenState::onFadeInComplete, // callback function
		Object::safeCast(this) // callback scope
	);
}

// state's exit
void AutomaticPauseScreenState::exit(void* owner __attribute__ ((unused)))
{
	// call base
	Base::exit(this, owner);
}

void AutomaticPauseScreenState::processUserInput(const UserInput*  userInput)
{
	if(K_STA & userInput->pressedKey)
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
			(EventListener)AutomaticPauseScreenState::onFadeOutComplete, // callback function
			Object::safeCast(this) // callback scope
		);
	}
}

// handle event
void AutomaticPauseScreenState::onFadeInComplete(Object eventFirer __attribute__ ((unused)))
{
	// re-enable user input
	VUEngine::enableKeypad(VUEngine::getInstance());
}

// handle event
void AutomaticPauseScreenState::onFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	// re-enable user input
	VUEngine::enableKeypad(VUEngine::getInstance());

	// resume game
	VUEngine::unpause(VUEngine::getInstance(), GameState::safeCast(this));
}
