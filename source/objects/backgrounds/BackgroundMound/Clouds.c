/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Game.h>
#include <PhysicalWorld.h>
#include "Clouds.h"


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void Clouds::constructor(CloudsSpec* cloudsSpec, int16 internalId, const char* const name)
{
	// construct base
	Base::constructor(&cloudsSpec->EntitySpec, internalId, name);

	this->dontStreamOut = true;
	this->displacement = __PIXELS_TO_METERS(cloudsSpec->displacement);
}

// class's destructor
void Clouds::destructor()
{
	// delete the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

// state's handle message
void Clouds::update(uint32 elapsedTime __attribute__ ((unused)))
{
	// get local position of clouds and subtract defined displacement from x value
	Vector3D offset = this->transformation.localPosition;
	offset.x -= __FIX10_6_MULT(this->displacement, elapsedTime);

	// update clouds' position
	Container::setLocalPosition(this, &offset);
}

