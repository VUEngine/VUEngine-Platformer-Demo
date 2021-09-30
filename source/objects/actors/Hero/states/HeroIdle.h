/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef HERO_IDLE_H_
#define HERO_IDLE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <HeroState.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

singleton class HeroIdle : HeroState
{
	static HeroIdle getInstance();

	override void enter(void* owner);
	override void exit(void* owner);
	override bool processMessage(void* owner, Telegram telegram);
	override void onKeyPressed(void* owner, const UserInput* userInput);
	override void onKeyReleased(void* owner, const UserInput* userInput);
	override void onKeyHold(void* owner, const UserInput* userInput);
}


#endif
