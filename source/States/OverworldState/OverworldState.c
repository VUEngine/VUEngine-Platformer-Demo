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
#include <OverworldState.h>
#include <TitleScreenState.h>
#include <Hero.h>
#include <ParticleSystem.h>
#include <PlatformerLevelState.h>
#include <AdjustmentScreenState.h>
#include <PlatformerCameraMovementManager.h>
#include <ProgressManager.h>
#include <EventManager.h>
#include <KeypadManager.h>
#include <SoundManager.h>
#include <Printing.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMSpec Overworld1Stage;


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
	VUEngine::disableKeypad(VUEngine::getInstance());

	// load stage
	GameState::loadStage(this, (StageSpec*)&Overworld1Stage, NULL, true, false);

	// make a little bit of physical simulations so each entity is placed at the floor
	GameState::startClocks(this);

	// tell any interested entity
	GameState::propagateMessage(this, kMessageLevelSetUp);

	OverworldState::print(this);

	// fade in screen after a little delay
	Camera::startEffect(Camera::getInstance(), kHide);
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		250, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(EventListener)OverworldState::onFadeInComplete, // callback function
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
void OverworldState::suspend(void* owner)
{
	// pause physical simulations
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

// print gui
void OverworldState::print()
{
	Printing::setWorldCoordinates(Printing::getInstance(), 0, 0, PRINTING_LAYER_Z_COORDINATE, PRINTING_LAYER_PARALLAX);

	// coins
	uint8 coins = ProgressManager::getTotalNumberOfCollectedCoins(ProgressManager::getInstance());
	Printing::int32(Printing::getInstance(), coins, 4, 26, "AstonishSExt");

	// level name
	Printing::text(Printing::getInstance(), I18n::getText(I18n::getInstance(), kStringLevel1Name), 16, 26, "AstonishSExt");
	Printing::text(Printing::getInstance(), "1-1", 12, 26, "AstonishSExt");
}

void OverworldState::processUserInput(UserInput userInput)
{
	if((K_STA & userInput.pressedKey) || (K_A & userInput.pressedKey))
	{
		// disable user input
		VUEngine::disableKeypad(VUEngine::getInstance());

		// start a fade out effect
		Brightness brightness = (Brightness){0, 0, 0};
		Camera::startEffect(Camera::getInstance(),
			kFadeTo, // effect type
			0, // initial delay (in ms)
			&brightness, // target brightness
			__FADE_DELAY, // delay between fading steps (in ms)
			(EventListener)OverworldState::onStartLevelFadeOutComplete, // callback function
			Object::safeCast(this) // callback scope
		);

		// play sound
/*		extern SoundSpec OPTION_CONFIRM_SND;
		Vector3D position = Vector3D::getFromPixelVector((PixelVector){192, 112, 0, 0});
		SoundManager::playSound(SoundManager::getInstance(), &OPTION_CONFIRM_SND, kPlayAll, (const Vector3D*)&position, kSoundPlaybackNormal, NULL, NULL);
*/
	}
	else if(K_B & userInput.pressedKey)
	{
		// disable user input
		VUEngine::disableKeypad(VUEngine::getInstance());

		// start a fade out effect
		Brightness brightness = (Brightness){0, 0, 0};
		Camera::startEffect(Camera::getInstance(),
			kFadeTo, // effect type
			0, // initial delay (in ms)
			&brightness, // target brightness
			__FADE_DELAY, // delay between fading steps (in ms)
			(EventListener)OverworldState::onReturnToTitleFadeOutComplete, // callback function
			Object::safeCast(this) // callback scope
		);
	}
}

// handle event
void OverworldState::onFadeInComplete(Object eventFirer __attribute__ ((unused)))
{
	// tell any interested entity
	GameState::propagateMessage(this, kMessageLevelStarted);

	// enable user input
	VUEngine::enableKeypad(VUEngine::getInstance());
}

// handle event
void OverworldState::onStartLevelFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	// load platformer level
	extern PlatformerLevelSpec Level1;
	PlatformerLevelState::startLevel(PlatformerLevelState::getInstance(), &Level1);
}

// handle event
void OverworldState::onReturnToTitleFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	// load title screen state
	VUEngine::changeState(VUEngine::getInstance(), GameState::safeCast(TitleScreenState::getInstance()));
}
