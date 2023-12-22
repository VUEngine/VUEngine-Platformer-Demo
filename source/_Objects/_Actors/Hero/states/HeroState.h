/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef HERO_STATE_H_
#define HERO_STATE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <State.h>
#include <KeypadManager.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

class HeroState : State
{
	void constructor();

	virtual void onKeyPressed(void* owner, const UserInput* userInput) = 0;
	virtual void onKeyReleased(void* owner, const UserInput* userInput) = 0;
	virtual void onKeyHold(void* owner, const UserInput* userInput);
}


#endif
