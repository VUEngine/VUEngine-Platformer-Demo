/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef PAUSE_SCREEN_STATE_H_
#define PAUSE_SCREEN_STATE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <GameState.h>
#include <OptionsSelector.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

enum PauseScreenModes
{
	kPauseScreenModeShowOptions,
	kPauseScreenModeShowConfirmQuit
};

enum PauseScreenOptions
{
	kPauseScreenOptionContinue,
	kPauseScreenOptionOptions,
	kPauseScreenOptionQuitLevel
};


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------



singleton class PauseScreenState : GameState
{
	uint8 mode;
	OptionsSelector optionsSelector;

	static PauseScreenState getInstance(void);
	override void enter(void* owner);
	override void exit(void* owner);
	override void processUserInput(UserInput userInput);
}


#endif
