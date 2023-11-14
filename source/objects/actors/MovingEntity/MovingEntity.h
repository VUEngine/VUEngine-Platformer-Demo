/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef MOVING_ENTITY_H_
#define MOVING_ENTITY_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Actor.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

#define MOVING_ENTITY_WAIT_DELAY				1000
#define MOVING_ENTITY_DIRECTION_CHECK_DELAY		75


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

// spec in ROM memory
typedef struct MovingEntitySpec
{
	// It has a Character in the beginning
	ActorSpec actorSpec;

	// velocity
	fix10_6 velocity;

	// maximum deviation from initial position
	fix10_6 maximumDisplacement;

	// time to rest idle
	uint16 idleDuration;

	// on which axis it moves
	uint8 axis;

	// movement direction
	int8 normalizedDirection;

	// axis on which synchronize shape with direction
	uint16 axisForShapeSyncWithDirection;

} MovingEntitySpec;

typedef const MovingEntitySpec MovingEntityROMSpec;

class MovingEntity : Actor
{
	/* save my initial position */
	int initialPosition;
	/* spec pointer */
	MovingEntitySpec* movingEntitySpec;

	void constructor(MovingEntitySpec* MovingEntitySpec, int16 internalId, const char* const name);
	void startMovement();
	void checkDisplacement();
	override void ready(bool recursive);
	override bool handleMessage(Telegram telegram);
}


#endif
