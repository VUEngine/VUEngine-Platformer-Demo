/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef GOAL_DOOR_H_
#define GOAL_DOOR_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Door.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef const DoorSpec GoalDoorSpec;
typedef const GoalDoorSpec GoalDoorROMSpec;

class GoalDoor : Door
{
	void constructor(AnimatedEntitySpec* animatedEntitySpec, int16 internalId, const char* const name);
	override bool handleMessage(Telegram telegram);
	override void ready(bool recursive);
	override bool hasDestination();
	override bool canEnter();
}


#endif
