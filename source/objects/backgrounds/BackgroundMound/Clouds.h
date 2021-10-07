/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef CLOUDS_H_
#define CLOUDS_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Entity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define CLOUDS_MOVE_DELAY 100


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef struct CloudsSpec
{
	// it has an Entity at the beginning
	EntitySpec EntitySpec;

	// displacement per cycle in pixels
	int16 displacement;

} CloudsSpec;

typedef const CloudsSpec CloudsROMSpec;

class Clouds : Entity
{
	/* displacement per cycle */
	fix10_6 displacement;

	void constructor(CloudsSpec* cloudsSpec, int16 internalId, const char* const name);
	override void update(uint32 elapsedTime);
}


#endif
