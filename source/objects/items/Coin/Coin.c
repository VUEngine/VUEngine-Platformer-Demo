/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev
 * jorgech3@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
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

extern AnimatedInGameEntityROMDef OBJECT_COIN_SILHOUETTE_AG;


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
    if (UserDataManager_getCoinStatus(UserDataManager_getInstance(), "Coin 001"))
    {
        animatedInGameEntityDefinition = (AnimatedInGameEntityDefinition*)&OBJECT_COIN_SILHOUETTE_AG;
        this->taken = true;
    }
    else
    {
        this->taken = false;
    }

	// construct base
	__CONSTRUCT_BASE(animatedInGameEntityDefinition, id, name);

	// register a shape for collision detection
	if(!this->taken)
	{
	    this->shape = CollisionManager_registerShape(CollisionManager_getInstance(), __GET_CAST(SpatialObject, this), kCuboid);
    }
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

	switch (Telegram_getMessage(telegram))
    {
		case kTakeCoin:

			Coin_removeFromStage(this);
			break;
	}
	
	return false;
}

void Coin_initialize(Coin this)
{
	ASSERT(this, "Coin::initialize: null this");

    //if (UserDataManager_getCoinStatus(UserDataManager_getInstance(), "Coin 001"))
    //{
    //}

	AnimatedInGameEntity_initialize(__GET_CAST(AnimatedInGameEntity, this));
}

void Coin_removeFromStage(Coin this)
{
	ASSERT(this, "Coin::removeFromStage: null this");

	Container_deleteMyself(__GET_CAST(Container, this));
    Shape_setActive(this->shape, false);
}