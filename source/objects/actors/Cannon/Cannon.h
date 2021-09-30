/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef CANNON_H_
#define CANNON_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AnimatedEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define CANNON_INITIAL_SHOOT_DELAY 	2000
#define CANNON_SHOOT_DELAY 			5000


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef const AnimatedEntitySpec CannonSpec;
typedef const CannonSpec CannonROMSpec;

class Cannon : AnimatedEntity
{
	void constructor(AnimatedEntitySpec* spec, int16 internalId, const char* const name);
	void shoot();
	void spawnCannonBall();
	override bool handleMessage(Telegram telegram);
	override void ready(bool recursive);
}


#endif
