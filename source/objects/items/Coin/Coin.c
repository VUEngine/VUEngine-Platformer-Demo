/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2017 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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
#include "Coin.h"
#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
//											DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern EntityDefinition LEVEL_1_HOUSE_IM;
extern AnimatedInGameEntityROMDef COIN_BACK_AG;
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
__CLASS_NEW_DEFINITION(Coin, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name)
__CLASS_NEW_END(Coin, animatedInGameEntityDefinition, id, internalId, name);

// class's constructor
void Coin_constructor(Coin this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base
	__CONSTRUCT_BASE(Collectable, animatedInGameEntityDefinition, id, internalId, name);
}

// class's destructor
void Coin_destructor(Coin this)
{
	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// initialize method
void Coin_initialize(Coin this, u32 recursive)
{
	ASSERT(this, "Coin::initialize: null this");

    // if coin has already been collected, show silhouette representation
    if(ProgressManager_getCoinStatus(ProgressManager_getInstance(), this->id))
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

    Entity_initialize(__SAFE_CAST(Entity, this), recursive);
}

void Coin_collect(Coin this)
{
	ASSERT(this, "Collectable::collect: null this");

	// "collect" coin if it wasn't already
    if(!ProgressManager_getCoinStatus(ProgressManager_getInstance(), this->id))
    {
        // set coin status to taken
        ProgressManager_setCoinStatus(ProgressManager_getInstance(), this->id, true);

        // fire "taken" event
        Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), kEventCoinTaken);
    }
}
