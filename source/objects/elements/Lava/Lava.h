/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef LAVA_H_
#define LAVA_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Entity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define LAVA_MOVE_DELAY 	50


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef const EntitySpec LavaSpec;
typedef const LavaSpec LavaROMSpec;

class Lava : Entity
{
	void constructor(EntitySpec* spec, int16 internalId, const char* const name);
	void startMoving();
	override bool handleMessage(Telegram telegram);
}


#endif
