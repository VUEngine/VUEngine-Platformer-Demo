
/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef AWESOME_CLOUD_H_
#define AWESOME_CLOUD_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Entity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

#define AWESOME_CLOUD_Y_MOVEMENT_STEP 8


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

typedef struct AwesomeCloudSpec
{
	EntitySpec entitySpec;

	/// Rotation around x axis
	int16 rotation;

}AwesomeCloudSpec;

typedef const AwesomeCloudSpec AwesomeCloudROMSpec;

class AwesomeCloud : Entity
{
	AwesomeCloudSpec* awesomeCloudSpec;

	void constructor(AwesomeCloudSpec* AwesomeCloudSpec, int16 internalId, const char* const name);
	override void ready(bool recursive);
//	override void update(uint32 elapsedTime);
}


#endif
