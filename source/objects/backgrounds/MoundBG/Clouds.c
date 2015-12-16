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
#include "Clouds.h"

#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Clouds, InanimatedInGameEntity);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void Clouds_move(Clouds this);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Clouds, InanimatedInGameEntityDefinition* inanimatedInGameEntityDefinition, int id, const char* const name)
__CLASS_NEW_END(Clouds, inanimatedInGameEntityDefinition, id, name);

// class's constructor
void Clouds_constructor(Clouds this, InanimatedInGameEntityDefinition* inanimatedInGameEntityDefinition, int id, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(inanimatedInGameEntityDefinition, id, name);
	
	if(this->shape)
	{
		Shape_setCheckForCollisions(__GET_CAST(Shape, this->shape), false);
	}

	Clouds_startMoving(this);
}

// class's destructor
void Clouds_destructor(Clouds this)
{
    // discard pending moving messages
    MessageDispatcher_discardDelayedMessages(MessageDispatcher_getInstance(), kMove);

	// delete the super object
	__DESTROY_BASE;
}

// start moving
void Clouds_startMoving(Clouds this)
{
	ASSERT(this, "Clouds::startMoving: null this");

	// start moving
	MessageDispatcher_dispatchMessage(CLOUDS_MOVE_DELAY, __GET_CAST(Object, this), __GET_CAST(Object, this), kMove, NULL);
	
	// must make sure that the shape is updated
	if(this->shape)
	{
		CollisionManager_shapeStartedMoving(CollisionManager_getInstance(), this->shape);
	}
}

// whether it is visible
bool Clouds_isVisible(Clouds this, int pad)
{
	ASSERT(this, "Clouds::isVisible: null this");

    // always return true so the Clouds is never unloaded from the stage when it is not visible on screen
	return true;
}

// state's on message
bool Clouds_handleMessage(Clouds this, Telegram telegram)
{
	switch(Telegram_getMessage(telegram))
    {
		case kMove:

            Clouds_move(this);
			break;
	}
	
	return false;
}

// move clouds to the left
void Clouds_move(Clouds this)
{
    // get local position of clouds and substract 1 from x value
    VBVec3D offset = *Container_getLocalPosition(__GET_CAST(Container, this));
    offset.x -= ITOFIX19_13(1);

    // update clouds's position
    Container_setLocalPosition(__GET_CAST(Container, this), &offset);

    // send delayed message to self to trigger next movement
    MessageDispatcher_dispatchMessage(CLOUDS_MOVE_DELAY, __GET_CAST(Object, this), __GET_CAST(Object, this), kMove, NULL);
}

// resume after pause
void Clouds_resume(Clouds this)
{
	ASSERT(this, "Entity::resume: null this");

	Entity_resume(__GET_CAST(Entity, this));

    // send delayed message to itself to trigger next movement
    MessageDispatcher_dispatchMessage(CLOUDS_MOVE_DELAY, __GET_CAST(Object, this), __GET_CAST(Object, this), kMove, NULL);
}

// does it move?
bool Clouds_moves(Clouds this)
{
	ASSERT(this, "Clouds::moves: null this");

	return true;
}

