/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef DOOR_H_
#define DOOR_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AnimatedEntity.h>
#include <PlatformerLevelState.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

#define DOOR_OVERLAPPING_CHECK_DELAY	250


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef const AnimatedEntitySpec DoorSpec;
typedef const DoorSpec DoorROMSpec;

class Door : AnimatedEntity
{
	/* destination of door */
	StageEntryPointSpec* destinationSpec;

	void constructor(AnimatedEntitySpec* animatedEntitySpec, int16 internalId, const char* const name);
	StageEntryPointSpec* getExtraInfo();
	void onOverlapping();
	virtual bool hasDestination();
	virtual void setOverlapping();
	virtual void unsetOverlapping();
	virtual bool canEnter();
	virtual uint32 getHintType();
	override void setExtraInfo(void* extraInfo);
	override void ready(bool recursive);
	override bool handleMessage(Telegram telegram);
}


#endif
