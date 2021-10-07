/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef OVERWORLD_STATE_H_
#define OVERWORLD_STATE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <GameState.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

dynamic_singleton class OverworldState : GameState
{
	static OverworldState getInstance(void);
	override void enter(void* owner);
	override void exit(void* owner);
	override void resume(void* owner);
	override void suspend(void* owner);
	override void processUserInput(UserInput userInput);
}


#endif
