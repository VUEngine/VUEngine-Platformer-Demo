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
#include <Cuboid.h>
#include <PhysicalWorld.h>
#include <MessageDispatcher.h>
#include <objects.h>
#include "HideLayer.h"
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(HideLayer, AnimatedInGameEntity);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

bool HideLayer_checkStillOverlapping(HideLayer this);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(HideLayer, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name)
__CLASS_NEW_END(HideLayer, animatedInGameEntityDefinition, id, name);

// class's constructor
void HideLayer_constructor(HideLayer this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(AnimatedInGameEntity, animatedInGameEntityDefinition, id, name);

	// register a shape for collision detection
	this->shape = CollisionManager_registerShape(Game_getCollisionManager(Game_getInstance()), __SAFE_CAST(SpatialObject, this), kCuboid);

    // init class variables
	this->currentlyOverlappingHero = false;
}

// class's destructor
void HideLayer_destructor(HideLayer this)
{
	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// class's handle message
bool HideLayer_handleMessage(HideLayer this, Telegram telegram)
{
	switch(Telegram_getMessage(telegram))
    {
        case kHeroCheckOverlapping:

            if(HideLayer_checkStillOverlapping(this))
            {
                // delayed check if still overlapping hero
                MessageDispatcher_dispatchMessage(HIDE_LAYER_OVERLAPPING_CHECK_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroCheckOverlapping, NULL);
            }

            return true;
            break;
	}

	return false;
}

void HideLayer_setOverlapping(HideLayer this)
{
	this->currentlyOverlappingHero = true;

    AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "ToTransparent");
}

void HideLayer_onToTransparentAnimationComplete(HideLayer this)
{
    // delayed check if still overlapping hero
    MessageDispatcher_dispatchMessage(HIDE_LAYER_OVERLAPPING_CHECK_DELAY, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kHeroCheckOverlapping, NULL);
}

bool HideLayer_isOverlapping(HideLayer this)
{
	return this->currentlyOverlappingHero;
}

bool HideLayer_checkStillOverlapping(HideLayer this)
{
	// check if hero has recently overlapped door and is still doing so
	if(
		this->currentlyOverlappingHero &&
		!__VIRTUAL_CALL(int, Shape, overlaps, Entity_getShape(__SAFE_CAST(Entity, Hero_getInstance())), Entity_getShape(__SAFE_CAST(Entity, this)))
	)
	{
		this->currentlyOverlappingHero = false;

        AnimatedInGameEntity_playAnimation(__SAFE_CAST(AnimatedInGameEntity, this), "ToSolid");
	}

	return this->currentlyOverlappingHero;
}
