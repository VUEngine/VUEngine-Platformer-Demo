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
#include <VirtualNode.h>
#include <VirtualList.h>
#include <Sprite.h>

#include <objects.h>
#include "TransparentAnimatedInGameEntity.h"


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(TransparentAnimatedInGameEntity, AnimatedInGameEntity);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(TransparentAnimatedInGameEntity, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(TransparentAnimatedInGameEntity, animatedInGameEntityDefinition, id, internalId, name);

// class's constructor
void TransparentAnimatedInGameEntity_constructor(TransparentAnimatedInGameEntity this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	ASSERT(this, "TransparentAnimatedInGameEntity::constructor: null this");

	// construct base
	__CONSTRUCT_BASE(AnimatedInGameEntity, animatedInGameEntityDefinition, id, internalId, name);

	// init members
	this->visible = true;
}

// class's destructor
void TransparentAnimatedInGameEntity_destructor(TransparentAnimatedInGameEntity this)
{
	ASSERT(this, "TransparentAnimatedInGameEntity::destructor: null this");

	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

void TransparentAnimatedInGameEntity_update(TransparentAnimatedInGameEntity this, u32 elapsedTime)
{
	ASSERT(this, "TransparentAnimatedInGameEntity::update: null this");

	AnimatedInGameEntity_update(__SAFE_CAST(AnimatedInGameEntity, this), elapsedTime);

	VirtualNode node = VirtualList_begin(this->sprites);

	if(this->visible)
	{
		for(; node; node = VirtualNode_getNext(node))
		{
			__VIRTUAL_CALL(Sprite, hide, __SAFE_CAST(Sprite, VirtualNode_getData(node)));
		}
	}
	else
	{
		for(; node; node = VirtualNode_getNext(node))
		{
			__VIRTUAL_CALL(Sprite, show, __SAFE_CAST(Sprite, VirtualNode_getData(node)));
		}
	}

	this->visible = !this->visible;
}
