/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Game.h>
#include <PhysicalWorld.h>
#include "Clouds.h"


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Clouds, Entity);


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Clouds, CloudsDefinition* cloudsDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(Clouds, cloudsDefinition, id, internalId, name);

// class's constructor
void Clouds_constructor(Clouds this, CloudsDefinition* cloudsDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(Entity, &cloudsDefinition->EntityDefinition, id, internalId, name);

	this->displacement = __PIXELS_TO_METERS(cloudsDefinition->displacement);
}

// class's destructor
void Clouds_destructor(Clouds this)
{
	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// whether it is visible
bool Clouds_isVisible(Clouds this __attribute__ ((unused)), int pad __attribute__ ((unused)), bool recursive __attribute__ ((unused)))
{
	ASSERT(this, "Clouds::isVisible: null this");

	// always return true so the Clouds is never unloaded from the stage when it is not visible on screen
	return true;
}

// state's handle message
void Clouds_update(Clouds this, u32 elapsedTime __attribute__ ((unused)))
{
	ASSERT(this, "Clouds::update: null this");

	// get local position of clouds and subtract defined displacement from x value
	Vector3D offset = this->transformation.localPosition;
	offset.x -= __FIX10_6_MULT(this->displacement, elapsedTime);

	// update clouds' position
	Container_setLocalPosition(__SAFE_CAST(Container, this), &offset);
}

