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
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Cuboid.h>
#include <PhysicalWorld.h>

#include <objects.h>
#include "TransparentImage.h"


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(TransparentImage, Image);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(TransparentImage, ImageDefinition* imageDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(TransparentImage, imageDefinition, id, internalId, name);

// class's constructor
void TransparentImage_constructor(TransparentImage this, ImageDefinition* imageDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(Image, imageDefinition, id, internalId, name);

	// init members
	this->visible = true;
}

// class's destructor
void TransparentImage_destructor(TransparentImage this)
{
	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

void TransparentImage_update(TransparentImage this)
{
	ASSERT(this, "TransparentImage::update: null this");

	if(this->visible)
	{
		Entity_hide(__SAFE_CAST(Entity, this));
	}
	else
	{
		Entity_show(__SAFE_CAST(Entity, this));
	}

	this->visible = !this->visible;
}
