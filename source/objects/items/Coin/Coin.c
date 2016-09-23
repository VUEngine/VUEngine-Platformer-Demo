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

__CLASS_DEFINITION(Coin, AnimatedInGameEntity);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void Coin_removeFromStage(Coin this);


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
    if(
        //&COIN_SILHOUETTE_AG == animatedInGameEntityDefinition ||
        //&COIN_BACK_SILHOUETTE_AG == animatedInGameEntityDefinition ||
        ProgressManager_getCoinStatus(ProgressManager_getInstance(), name)
    )
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
	__CONSTRUCT_BASE(AnimatedInGameEntity, animatedInGameEntityDefinition, id, name);

	// register a shape for collision detection
    this->shape = CollisionManager_registerShape(Game_getCollisionManager(Game_getInstance()), __SAFE_CAST(SpatialObject, this), kCuboid);
}

// class's destructor
void Coin_destructor(Coin this)
{
	// delete the super object
	// must always be called at the end of the destructor
	__DESTROY_BASE;
}

// state's handle message
bool Coin_handleMessage(Coin this, Telegram telegram)
{
	ASSERT(this, "Coin::handleMessage: null this");

	switch(Telegram_getMessage(telegram))
    {
		case kItemTaken:

            Shape_setActive(this->shape, false);
            MessageDispatcher_dispatchMessage(1, __SAFE_CAST(Object, this), __SAFE_CAST(Object, this), kTakeCoin, NULL);
            break;

        case kTakeCoin:

			Coin_removeFromStage(this);
			break;
	}

	return false;
}

void Coin_removeFromStage(Coin this)
{
	ASSERT(this, "Coin::removeFromStage: null this");

    if(!ProgressManager_getCoinStatus(ProgressManager_getInstance(), Container_getName(__SAFE_CAST(Container, this))))
    {
        // increment the number of collected coins
        int numberOfCollectedCoins = ProgressManager_getNumberOfCollectedCoins(ProgressManager_getInstance());
        numberOfCollectedCoins++;
        ProgressManager_setNumberOfCollectedCoins(ProgressManager_getInstance(), numberOfCollectedCoins);

        // set coin status to taken
        ProgressManager_setCoinStatus(ProgressManager_getInstance(), Container_getName(__SAFE_CAST(Container, this)), true);

        // fire "taken" event
        Object_fireEvent(__SAFE_CAST(Object, EventManager_getInstance()), kEventCoinTaken);

        extern const u16 COLLECT_SND[];

        // play collect sound
        SoundManager_playFxSound(SoundManager_getInstance(), COLLECT_SND, this->transform.globalPosition);
    }

	Container_deleteMyself(__SAFE_CAST(Container, this));
}
