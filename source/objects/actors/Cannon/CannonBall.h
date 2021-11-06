/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef CannonBall_H_
#define CannonBall_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Actor.h>
#include <macros.h>
#include <Actor.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define CannonBall_MINIMUM_Z_VALUE				-64
#define CannonBall_DISPLACEMENT_CHECK_DELAY	500


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef const ActorSpec CannonBallSpec;
typedef const CannonBallSpec CannonBallROMSpec;

class CannonBall : Actor
{
	void constructor(CannonBallSpec* cannonBallSpec, int16 internalId, const char* const name);
	void startMovement();
	void checkPosition();
	override bool handleMessage(Telegram telegram);
}

#endif
