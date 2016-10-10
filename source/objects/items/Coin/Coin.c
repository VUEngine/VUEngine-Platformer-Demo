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
    // if coin has already been collected, only show silhouette representation
    if(ProgressManager_getCoinStatus(ProgressManager_getInstance(), this->itemNumber))
    {
        if((AnimatedInGameEntityDefinition*)&COIN_BACK_AG == animatedInGameEntityDefinition)
        {
            animatedInGameEntityDefinition = (AnimatedInGameEntityDefinition*)&COIN_BACK_SILHOUETTE_AG;
        }
        else
        {
            animatedInGameEntityDefinition = (AnimatedInGameEntityDefinition*)&COIN_SILHOUETTE_AG;
        }
    }

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

// ready method
void Coin_ready(Coin this, u32 recursive)
{
	ASSERT(this, "Coin::ready: null this");

    // if coin has already been collected, show silhouette representation
    /*
    if(ProgressManager_getCoinStatus(ProgressManager_getInstance(), this->itemNumber))
    {
	    CharSet charSet = Texture_getCharSet(Sprite_getTexture(__SAFE_CAST(Sprite, VirtualList_front(this->sprites))), true);

	    CharSetDefinition* charSetDefinition = (CharSet_getCharSetDefinition(charSet) == &COIN_BACK_CH)
			? &COIN_BACK_SILHOUETTE_CH
			: &COIN_SILHOUETTE_CH;

	    CharSet_setCharSetDefinition(charSet, charSetDefinition);
		CharSet_rewrite(charSet);
    }
    */

	// call base method to start animation
	AnimatedInGameEntity_ready(__SAFE_CAST(AnimatedInGameEntity, this), recursive);
}

void Coin_collect(Coin this)
{
	ASSERT(this, "Collectable::collect: null this");

	// "collect" coin if it wasn't already
    if(!ProgressManager_getCoinStatus(ProgressManager_getInstance(), this->itemNumber))
    {
        // increment the number of collected coins
        int numberOfCollectedCoins = ProgressManager_getNumberOfCollectedCoins(ProgressManager_getInstance());
        numberOfCollectedCoins++;
        ProgressManager_setTotalNumberOfCollectedCoins(ProgressManager_getInstance(), numberOfCollectedCoins);

        // set coin status to taken
        ProgressManager_setCoinStatus(ProgressManager_getInstance(), this->itemNumber, true);

        // fire "taken" event
        Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), kEventCoinTaken);
    }
}
