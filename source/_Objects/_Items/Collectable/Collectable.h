/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef COLLECTABLE_H_
#define COLLECTABLE_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <AnimatedEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef const AnimatedEntitySpec CollectableSpec;
typedef const CollectableSpec CollectableROMSpec;

class Collectable : AnimatedEntity
{
	void constructor(CollectableSpec* collectableSpec, int16 internalId, const char* const name);
	virtual void collect();
	override bool handleMessage(Telegram telegram);
}


#endif
