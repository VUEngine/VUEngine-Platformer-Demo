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
#include "Clouds.h"


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Clouds, Image);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void Clouds_move(Clouds this);


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
	__CONSTRUCT_BASE(&cloudsDefinition->imageDefinition, id, name);
	
	this->displacement = cloudsDefinition->displacement;
}

// class's destructor
void Clouds_destructor(Clouds this)
{
	// delete the super object
	__DESTROY_BASE;
}

// whether it is visible
bool Clouds_isVisible(Clouds this, int pad)
{
	ASSERT(this, "Clouds::isVisible: null this");

    // always return true so the Clouds is never unloaded from the stage when it is not visible on screen
	return true;
}

// state's on message
void Clouds_update(Clouds this)
{
	ASSERT(this, "Clouds::update: null this");

	Container_update(__SAFE_CAST(Container, this));

    // get local position of clouds and substract defined displacement from x value
    VBVec3D offset = *Container_getLocalPosition(__GET_CAST(Container, this));
    offset.x -= FIX19_13_MULT(this->displacement, ITOFIX19_13(Clock_getElapsedTime(Game_getInGameClock(Game_getInstance()))));

    // update clouds' position
    Container_setLocalPosition(__GET_CAST(Container, this), &offset);
}

// does it move?
bool Clouds_moves(Clouds this)
{
	ASSERT(this, "Clouds::moves: null this");

	return true;
}

