/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef HERO_MOVING_H_
#define HERO_MOVING_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <HeroState.h>
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

enum HeroMovingMessages
{
	 kMessageDisallowJumpOnBouncing = kMessageLastGame + 1,
};


//---------------------------------------------------------------------------------------------------------
//										PUBLIC INTERFACE
//---------------------------------------------------------------------------------------------------------

singleton class HeroMoving : HeroState
{
	/* flag to allow jump on bouncing */
	bool bouncing;

	static HeroMoving getInstance();

	override void enter(void* owner);
	override void execute(void* owner);
	override bool processMessage(void* owner, Telegram telegram);
	override void onKeyPressed(void* owner, const UserInput* userInput);
	override void onKeyReleased(void* owner, const UserInput* userInput);
}


#endif
