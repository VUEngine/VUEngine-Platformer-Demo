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

#include <VUEngine.h>
#include <ProgressManager.h>
#include <AutomaticPauseManager.h>
#include <I18n.h>
#include <PrecautionScreenState.h>
#include <LanguageSelectionScreenState.h>
#include <TitleScreenState.h>
#include <AutomaticPauseScreenState.h>
#include <AdjustmentScreenState.h>
#include <AutomaticPauseSelectionScreenState.h>
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
//											GAME'S MAIN LOOP
//---------------------------------------------------------------------------------------------------------

int game(void)
{
	// initialize plugins
	AutomaticPauseManager::setAutomaticPauseState(AutomaticPauseManager::getInstance(), GameState::safeCast(AutomaticPauseScreenState::getInstance()));
	AutomaticPauseManager::setAutomaticPauseDelay(AutomaticPauseManager::getInstance(), 15);
	AutomaticPauseManager::setActive(AutomaticPauseManager::getInstance(), ProgressManager::getAutomaticPauseStatus(ProgressManager::getInstance()));
	I18n::setActiveLanguage(I18n::getInstance(), ProgressManager::getLanguage(ProgressManager::getInstance()));


	SplashScreenState::setNextState(
		SplashScreenState::safeCast(PrecautionScreenState::getInstance()),
		GameState::safeCast(AdjustmentScreenState::getInstance())
	);
	SplashScreenState::setNextState(
		SplashScreenState::safeCast(AdjustmentScreenState::getInstance()),
		GameState::safeCast(AutomaticPauseSelectionScreenState::getInstance())
	);
	SplashScreenState::setNextState(
		SplashScreenState::safeCast(AutomaticPauseSelectionScreenState::getInstance()),
		GameState::safeCast(LanguageSelectionScreenState::getInstance())
	);
	SplashScreenState::setNextState(
		SplashScreenState::safeCast(LanguageSelectionScreenState::getInstance()),
		GameState::safeCast(TitleScreenState::getInstance())
	);

	// start the game
	VUEngine::start(VUEngine::getInstance(), GameState::safeCast(PrecautionScreenState::getInstance()));

	// end program
	return true;
}
