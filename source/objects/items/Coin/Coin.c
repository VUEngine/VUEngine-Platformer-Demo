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
#include <UserDataManager.h>
#include <Container.h>

#include <objects.h>
#include "Coin.h"

#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 											 CLASS'S MACROS
//---------------------------------------------------------------------------------------------------------

extern AnimatedInGameEntityROMDef COIN_SILHOUETTE_AG;


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
	this->taken = &COIN_SILHOUETTE_AG == animatedInGameEntityDefinition || UserDataManager_getCoinStatus(UserDataManager_getInstance(), name);
    if(this->taken)
    {
        animatedInGameEntityDefinition = (AnimatedInGameEntityDefinition*)&COIN_SILHOUETTE_AG;
    }

	// construct base
	__CONSTRUCT_BASE(animatedInGameEntityDefinition, id, name);

	// register a shape for collision detection
    this->shape = CollisionManager_registerShape(CollisionManager_getInstance(), __GET_CAST(SpatialObject, this), kCuboid);
}

// class's destructor
void Coin_destructor(Coin this)
{
	// delete the super object
	__DESTROY_BASE;
}

// state's on message
bool Coin_handleMessage(Coin this, Telegram telegram)
{
	ASSERT(this, "Coin::handleMessage: null this");

	switch(Telegram_getMessage(telegram))
    {
		case kTakeCoin:

			Coin_removeFromStage(this);
			break;
	}
	
	return false;
}

void Coin_removeFromStage(Coin this)
{
	ASSERT(this, "Coin::removeFromStage: null this");

	Container_deleteMyself(__GET_CAST(Container, this));
    Shape_setActive(this->shape, false);
}

bool Coin_taken(Coin this)
{
	ASSERT(this, "Coin::Coin_taken: null this");

	return this->taken;
}