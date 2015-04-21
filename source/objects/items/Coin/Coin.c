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
#include <Screen.h>
#include <Cuboid.h>
#include <PhysicalWorld.h>

#include <objects.h>
#include "Coin.h"
#include "CoinManager.h"

#include <PlatformerLevelState.h>


//---------------------------------------------------------------------------------------------------------
// 											 CLASS'S MACROS
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
// 											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

__CLASS_DEFINITION(Coin, AnimatedInGameEntity);


//---------------------------------------------------------------------------------------------------------
// 												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void Coin_removeFromStage(Coin this, Object eventFirer);


//---------------------------------------------------------------------------------------------------------
// 												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// always call these two macros next to each other
__CLASS_NEW_DEFINITION(Coin, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int ID)
__CLASS_NEW_END(Coin, animatedInGameEntityDefinition, ID);

// class's constructor
void Coin_constructor(Coin this, AnimatedInGameEntityDefinition* animatedInGameEntityDefinition, int ID)
{
	// construct base
	__CONSTRUCT_BASE(animatedInGameEntityDefinition, ID);

	// register a shape for collision detection
	this->shape = CollisionManager_registerShape(CollisionManager_getInstance(), __UPCAST(Entity, this), kCuboid);
}

// class's destructor
void Coin_destructor(Coin this)
{
	CoinManager_removeCoin(CoinManager_getInstance(), this);

	// delete the super object
	__DESTROY_BASE;
}

// initialize method
void Coin_initialize(Coin this)
{
	AnimatedInGameEntity_initialize(__UPCAST(AnimatedInGameEntity, this));

	CoinManager_registerCoin(CoinManager_getInstance(), this);
}

// state's on message
bool Coin_handleMessage(Coin this, Telegram telegram)
{
	switch (Telegram_getMessage(telegram))
    {
		case kTakeCoin:

			AnimatedInGameEntity_playAnimation(__UPCAST(AnimatedInGameEntity, this), "Taken");
			Shape_setActive(this->shape, false);
			break;
	}
	
	return false;
}

void Coin_removeFromStage(Coin this, Object eventFirer)
{
	Stage_removeEntity(Game_getStage(Game_getInstance()), __UPCAST(Entity, this), true);
}