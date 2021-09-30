/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef COLLISION_H_
#define COLLISION_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Entity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef const EntitySpec CollisionSpec;
typedef const CollisionSpec CollisionROMSpec;

class Collision : Entity
{
	void constructor(EntitySpec* inGameEntitySpec, int16 internalId, const char* const name);
	override void setExtraInfo(void* extraInfo);
	override void initialTransform(Transformation* environmentTransform, uint32 recursive);
}


#endif
