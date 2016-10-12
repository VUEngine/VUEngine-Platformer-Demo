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
#include <EventManager.h>
#include <CollisionManager.h>
#include <MessageDispatcher.h>
#include <Cuboid.h>
#include <PhysicalWorld.h>
#include <ProgressManager.h>
#include <Container.h>
#include <SoundManager.h>

#include <objects.h>
#include "Coin.h"

#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 											 CLASS' MACROS
//---------------------------------------------------------------------------------------------------------

extern AnimatedInGameEntityROMDef COIN_SILHOUETTE_AG;
extern AnimatedInGameEntityROMDef COIN_BACK_SILHOUETTE_AG;


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Coin, Collectable);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Coin, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name)
__CLASS_NEW_END(Coin, animatedInGameEntityDefinition, id, name);

// class's constructor
void Coin_constructor(Coin this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int id, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(Collectable, animatedInGameEntityDefinition, id, name);
}

// class's destructor
void Coin_destructor(Coin this)
{
	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// setExtraInfo method
void Coin_setExtraInfo(Coin this, void* extraInfo)
{
	ASSERT(this, "Coin::setExtraInfo: null this");

	Collectable_setExtraInfo(__SAFE_CAST(Collectable, this), extraInfo);

    // if coin has already been collected, show silhouette representation
    if(ProgressManager_getCoinStatus(ProgressManager_getInstance(), this->itemNumber))
    {
        AnimatedInGameEntityDefinition* animatedInGameEntityDefinition = this->animatedInGameEntityDefinition;

        if((AnimatedInGameEntityDefinition*)&COIN_BACK_AG == animatedInGameEntityDefinition)
        {
            animatedInGameEntityDefinition = (AnimatedInGameEntityDefinition*)&COIN_BACK_SILHOUETTE_AG;
        }
        else
        {
            animatedInGameEntityDefinition = (AnimatedInGameEntityDefinition*)&COIN_SILHOUETTE_AG;
        }

        AnimatedInGameEntity_setDefinition(__SAFE_CAST(AnimatedInGameEntity, this), animatedInGameEntityDefinition);
    }
}

void Coin_collect(Coin this)
{
	ASSERT(this, "Collectable::collect: null this");

	// "collect" coin if it wasn't already
    if(!ProgressManager_getCoinStatus(ProgressManager_getInstance(), this->itemNumber))
    {
        // set coin status to taken
        ProgressManager_setCoinStatus(ProgressManager_getInstance(), this->itemNumber, true);

        // fire "taken" event
        Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), kEventCoinTaken);
    }
}
