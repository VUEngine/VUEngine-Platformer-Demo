/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef TITLE_SCREEN_STATE_H_
#define TITLE_SCREEN_STATE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <GameState.h>
#include <OptionsSelector.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

enum TitleScreenModes
{
	kTitleScreenModeShowPressStart,
	kTitleScreenModeShowOptions,
	kTitleScreenModeShowConfirmNewGame
};

enum TitleScreenOptions
{
	kTitleScreenOptionContinue,
	kTitleScreenOptionOptions,
	kTitleScreenOptionNewGame
};


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

singleton class TitleScreenState : GameState
{
	uint8 mode;
	OptionsSelector optionsSelector;

	static TitleScreenState getInstance(void);
	override void enter(void* owner);
	override void exit(void* owner);
	override void resume(void* owner);
	override void suspend(void* owner);
	override void processUserInput(UserInput userInput);
}


#endif
