/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev <jorgech3@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation; either version 3 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program. If not,
 * see <http://www.gnu.org/licenses/>.
 */


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Game.h>
#include <PhysicalWorld.h>
#include "Clouds.h"


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Clouds, Image);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Clouds, CloudsDefinition* cloudsDefinition, int id, const char* const name)
__CLASS_NEW_END(Clouds, cloudsDefinition, id, name);

// class's constructor
void Clouds_constructor(Clouds this, CloudsDefinition* cloudsDefinition, int id, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(Image, &cloudsDefinition->imageDefinition, id, name);

	this->displacement = cloudsDefinition->displacement;
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
    VBVec3D offset = this->transform.localPosition;
    offset.x -= FIX19_13_MULT(this->displacement, PhysicalWorld_getElapsedTime(Game_getPhysicalWorld(Game_getInstance())));

    // update clouds' position
    Container_setLocalPosition(__SAFE_CAST(Container, this), &offset);
}

// does it move?
bool Clouds_moves(Clouds this __attribute__ ((unused)))
{
	ASSERT(this, "Clouds::moves: null this");

	return true;
}

