/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef OPTIONS_SCREEN_STATE_H_
#define OPTIONS_SCREEN_STATE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <GameState.h>
#include <OptionsSelector.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------



singleton class OptionsScreenState : GameState
{
	GameState nextState;
	OptionsSelector optionsSelector;

	static OptionsScreenState getInstance(void);
	void setNextState(GameState nextState);
	override void enter(void* owner);
	override void exit(void* owner);
	override void processUserInput(UserInput userInput);
}


#endif
