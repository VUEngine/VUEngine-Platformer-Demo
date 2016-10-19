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

#include <GameEvents.h>
#include <Game.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Cuboid.h>
#include <PhysicalWorld.h>
#include <SoundManager.h>
#include <EventManager.h>
#include <ProgressManager.h>

#include <objects.h>
#include "Item.h"

#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Item, Collectable);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void Item_collect(Item this);
void Item_removeFromStage(Item this);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Item, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(Item, animatedInGameEntityDefinition, id, internalId, name);

// class's constructor
void Item_constructor(Item this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	ASSERT(this, "Item::constructor: null this");

	// construct base
	__CONSTRUCT_BASE(Collectable, animatedInGameEntityDefinition, id, internalId, name);
}

// class's destructor
void Item_destructor(Item this)
{
	ASSERT(this, "Item::destructor: null this");

	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// ready method
void Item_ready(Item this, u32 recursive)
{
	ASSERT(this, "Item::ready: null this");

    // if item has already been collected, remove it
    if(ProgressManager_getItemStatus(ProgressManager_getInstance(), this->itemNumber))
    {
        Collectable_removeFromStage(__SAFE_CAST(Collectable, this));
    }
    else
    {
        // call base method to start animation
        Collectable_ready(__SAFE_CAST(Collectable, this), recursive);
    }
}

void Item_collect(Item this)
{
	ASSERT(this, "Item::collect: null this");

    // set item status to taken
    ProgressManager_setItemStatus(ProgressManager_getInstance(), this->itemNumber, true);
}
